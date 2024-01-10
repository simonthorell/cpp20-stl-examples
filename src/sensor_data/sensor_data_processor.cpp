#include "sensor_data/sensor_data_processor.h"
#include <iostream>
#include <algorithm>
#include <ranges>
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
    // Start of the target day (2012-01-02 00:00:00)
    std::time_t targetTimeStart = createTime(year, month, day, 0, 0, 0);
    // Start of the next day (2012-01-03 00:00:00)
    struct tm nextDay = *localtime(&targetTimeStart);
    nextDay.tm_mday += 1;  // Move to the next day
    std::time_t targetTimeEnd = mktime(&nextDay);

    int altitudeDataCount = std::ranges::count_if
                                (sensorData, [targetTimeStart, targetTimeEnd]
                                (SensorData& data) {
        std::time_t dataTime = data.getTime();
        return data.getSensorType() == SensorType::Altitude 
            && dataTime >= targetTimeStart && dataTime < targetTimeEnd;
    });
    
    // Return the amount of altitude data entries
    return altitudeDataCount;
}
//=============================================================================
// Function: checkMaxSpeed
// Description: Checks whether any SpeedInKmh data entries exceed maxSpeed 
//              Iteration stops once the first qualifying entry is found,
//              returning true. Returns false if no entries exceed this speed.
//=============================================================================
bool SensorDataProcessor::checkMaxSpeed(float maxSpeed) {
    // Filter to only SpeedInKmh entries exceeding 99.9, using lazy evaluation for efficiency
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