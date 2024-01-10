#ifndef SENSOR_DATA_MANAGER_H
#define SENSOR_DATA_MANAGER_H

#include <vector>
#include <cstdint> // For fixed-width integer types

#include "sensor_data/sensor_data.h"
#include "sensor_data/sensor_data_processor.h"


class SensorDataManager {
private:
    int menuSelection;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    float maxSpeed;
    float fuelConsumptionFactor;
    std::vector<SensorData> sensorData;
    SensorDataProcessor processor;

public:
    SensorDataManager(int menuSel, uint16_t yr, uint8_t mo, uint8_t da, 
                      float maxSp, float fuelConsFact);

    int run();
};

#endif // SENSOR_DATA_MANAGER_H