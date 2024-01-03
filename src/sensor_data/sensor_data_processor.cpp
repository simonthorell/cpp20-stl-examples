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
int SensorDataProcessor::countAltitudeData() {
    int altitudeDataCount = std::ranges::count_if(sensorData, [](SensorData& data) {
        return data.GetSensorType() == SensorType::Altitude 
            && data.GetTime() == CreateTime(2012, 1, 2, 1, 1, 1);
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
bool SensorDataProcessor::checkMaxSpeed() {
    // Filter to only SpeedInKmh entries exceeding 99.9, using lazy evaluation for efficiency
    auto speedReached = std::views::filter(sensorData, [](SensorData& data) {
        return data.GetSensorType() == SensorType::SpeedInKmh && data.GetValue() > 99.9;
    });
    // Return true once/if any entries exceed the max speed
    return speedReached.begin() != speedReached.end();
}

//=============================================================================
// Function: updateFuelConsumption
// Description: Updates all FuelConsumption data entries by 75%.
//=============================================================================
bool SensorDataProcessor::updateFuelConsumption() {
    // Create a view of only the FuelConsumption entries
    auto fuelConsumptionView = std::views::filter(sensorData, [](SensorData& data) {
        return data.GetSensorType() == SensorType::FuelConsumption;
    });

    // Apply the transformation to update the value in place
    std::ranges::transform(fuelConsumptionView, fuelConsumptionView.begin(), [](SensorData& data) {
        data.SetValue(data.GetValue() * 1.75f);
        return data; // The return value isn't used since we're modifying in place
    });

    // Return true if any entries were updated
    return !std::ranges::empty(fuelConsumptionView);
}