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
    int countAltitudeData(uint16_t year, uint8_t month, uint8_t day);

    // Function to check max speed
    bool checkMaxSpeed(float maxSpeed);

    // Function to update fuel consumption
    bool updateFuelConsumption(float factor);

private:
    std::vector<SensorData> sensorData;
};

#endif // SENSOR_DATA_PROCESSOR_H_