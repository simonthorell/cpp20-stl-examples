#include "sensor_data/sensor_data_processor.h"
#include <iostream>
#include <algorithm>
#include <ranges>
#include <ctime>
//=============================================================================
// Constructor: SensorDataProcessor
// Description: Initializes the SensorDataProcessor with a vector of SensorData.
//=============================================================================
SensorDataProcessor::SensorDataProcessor(const std::vector<SensorData>& data) 
    : sensorData(data) {}
//=============================================================================
// Function: countAltitudeData
// Description: Counts and returns the number of altitude data entries from a 
//              specific date given by year, month, and day parameters.
//=============================================================================
int SensorDataProcessor::countAltitudeData(uint16_t year, uint8_t month, uint8_t day) {
    std::tm timeStruct = {0, 0, 0, day, month - 1, year - 1900};
    std::time_t targetDay = std::mktime(&timeStruct);
    timeStruct.tm_mday += 1; // Increment day by 1 to get the next day
    std::time_t nextDay = std::mktime(&timeStruct);

    // Filter to only Altitude data entries in the given time range
    auto isAltitudeInTimeRange = [targetDay, nextDay] (SensorData& data) {
        std::time_t dataTime = data.getTime();
        return data.getSensorType() == SensorType::Altitude && 
               dataTime >= targetDay && dataTime < nextDay;
    };

    // Count & return the number of altitude data entries on the target day
    return std::ranges::count_if(sensorData, isAltitudeInTimeRange);
}
//=============================================================================
// Function: checkMaxSpeed
// Description: Checks whether any SpeedInKmh data entries exceed maxSpeed 
//              Iteration stops once the first qualifying entry is found,
//              returning true. Returns false if no entries exceed this speed.
//=============================================================================
bool SensorDataProcessor::checkMaxSpeed(float maxSpeed) {
    // Filter to only SpeedInKmh > maxSpeed using lazy evaluation for efficiency
    auto speedReached = std::views::filter(sensorData, [maxSpeed](SensorData& data) {
        return data.getSensorType() == SensorType::SpeedInKmh && data.getValue() > maxSpeed;
    });

    // Return true once/if any entries exceed the max speed
    return speedReached.begin() != speedReached.end();
}
//=============================================================================
// Function: updateFuelConsumption
// Description: Updates all FuelConsumption data entries by the given factor
//              in a single iteration. It only iterates if there's applicable
//              data entries and the factor is not 0 (no need to transform).
//              Returns true if transformation was applied, otherwise false.
//=============================================================================
bool SensorDataProcessor::updateFuelConsumption(float factor) {
    // Create a combined view for filtering and transforming sensor data
    auto updateView = sensorData 
        | std::views::filter([](SensorData& data) {
            return data.getSensorType() == SensorType::FuelConsumption;
        })
        | std::views::transform([factor](SensorData& data) -> SensorData& {
            data.setValue(data.getValue() * factor);
            return data; // Modifying value in place, return value not used
        });

    // Check if factor is not 0 and if any data in range to transform
    if (factor != 0 && !std::ranges::empty(updateView)) {
        return true; // Transformation was applied during iteration of view
    }

    return false; // Transformation was not applied
}