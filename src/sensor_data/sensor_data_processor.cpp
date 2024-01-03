#include "sensor_data/sensor_data_processor.h"
#include <iostream>
#include <algorithm>

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
void SensorDataProcessor::countAltitudeData() {
    std::cout << "Altitude count: " << std::count_if(sensorData.begin(), sensorData.end(), [](SensorData& sd) {
        return sd.GetSensorType() == SensorType::Altitude && sd.GetTime() == CreateTime(2012, 1, 2, 1, 1, 1);
    }) << std::endl;
}

//=============================================================================
// Function: checkMaxSpeed
// Description: Checks and prints whether any SpeedInKmh data entries exceed a 
//              specified value (99.9) and prints the result.
//=============================================================================
void SensorDataProcessor::checkMaxSpeed() {
    std::cout << (std::find_if(sensorData.begin(), sensorData.end(), [](SensorData& sd) {
        return sd.GetSensorType() == SensorType::SpeedInKmh && sd.GetValue() > 99.9;
    }) != sensorData.end() ? "Max speed exceeded" : "No Max speed reached") << std::endl;
}

//=============================================================================
// Function: updateFuelConsumption
// Description: Updates all FuelConsumption data entries by 75%.
//=============================================================================
void SensorDataProcessor::updateFuelConsumption() {
    std::for_each(sensorData.begin(), sensorData.end(), [](SensorData& sd) {
			if (sd.GetSensorType() == SensorType::FuelConsumption)
				sd.SetValue(sd.GetValue() * 1.75f);
		});
		std::cout << "FuelConsumption updated" << std::endl;
}

