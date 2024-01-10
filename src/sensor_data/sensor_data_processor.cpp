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
// Description: Counts and prints the number of altitude data entries from a 
//              specific date given by year, month, and day parameters.
//=============================================================================
int SensorDataProcessor::countAltitudeData(uint16_t year, uint8_t month, uint8_t day) {
    std::tm timeStruct = {0, 0, 0, day, month - 1, year - 1900};
    std::time_t targetTimeStart = std::mktime(&timeStruct);
    std::time_t targetTimeEnd = targetTimeStart + 86400; // 86400 seconds in a day
    // Filter to only Altitude data entries in the given time range
    auto isAltitudeInTimeRange = [targetTimeStart, targetTimeEnd]
                                 (SensorData& data) {
        std::time_t dataTime = data.getTime();
        return data.getSensorType() == SensorType::Altitude && 
               dataTime >= targetTimeStart && dataTime < targetTimeEnd;
    };
    // Count & return the number of altitude data entries in the given time range
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
// Description: Updates all FuelConsumption data entries by the given factor.
//=============================================================================
bool SensorDataProcessor::updateFuelConsumption(float factor) {
    // Create a combined view for filtering and transforming
    auto updateView = sensorData | std::views::filter([](SensorData& data) {
        return data.getSensorType() == SensorType::FuelConsumption;
    }) | std::views::transform([factor](SensorData& data) {
        data.setValue(data.getValue() * factor);
        return data; // The return value isn't used since we're modifying in place
    });

    // Check that the factor is not 0 and there are entries to update/transform 
    if (factor != 0 && updateView.begin() != updateView.end()) {
        for (auto&& data : updateView) {} // Iterate the view to apply the transformation
        return true; // Transformation was applied
    }

    return false; // Transformation was not applied
}