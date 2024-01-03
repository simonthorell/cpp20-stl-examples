#ifndef SENSOR_DATA_PROCESSOR_H_
#define SENSOR_DATA_PROCESSOR_H_

#include "sensor_data.h" // Include the SensorData class
#include <vector>
#include <cstdint>

class SensorDataProcessor {
public:
    // Constructor takes a vector of SensorData
    explicit SensorDataProcessor(const std::vector<SensorData>& data);

    // Function to count altitude data
    int countAltitudeData();

    // Function to check max speed
    bool checkMaxSpeed();

    // Function to update fuel consumption
    bool updateFuelConsumption();

private:
    std::vector<SensorData> sensorData;
};

#endif // SENSOR_DATA_PROCESSOR_H_