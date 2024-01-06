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
//              specific date (2012-01-02).
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
// Description: Checks whether any SpeedInKmh data entries exceed 99.9. Iteration
//              stops once the first qualifying entry is found, returning true.
//              If no entries exceed this speed, it returns false.
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
// Description: Updates all FuelConsumption data entries by 75%.
//=============================================================================
bool SensorDataProcessor::updateFuelConsumption(float factor) {
    // Create a view of only the FuelConsumption entries
    auto fuelConsumptionView = std::views::filter(sensorData, [](SensorData& data) {
        return data.getSensorType() == SensorType::FuelConsumption;
    });

    // Return false if there are no entries to update or if the factor is 0
    if (std::ranges::empty(fuelConsumptionView) || factor == 0) { 
        return false;
    } 

    // Apply the transformation to update the value in place
    std::ranges::transform(fuelConsumptionView, fuelConsumptionView.begin()
                                              , [factor](SensorData& data) {
        data.setValue(data.getValue() * factor);
        return data; // The return value isn't used since we're modifying in place
    });

    // Return true if any entries were updated
    return !std::ranges::empty(fuelConsumptionView);
}