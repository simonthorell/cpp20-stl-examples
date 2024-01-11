#include "sensor_data/sensor_data_manager.h"
#include <iostream>

//=============================================================================
// Constructor: SensorDataManager
// Description: Initializes the SensorDataManager with a vector of SensorData.
//=============================================================================
SensorDataManager::SensorDataManager(int menuSel, uint16_t yr, uint8_t mo, uint8_t da, 
                                     float maxSp, float fuelConsFact)
    : menuSelection(menuSel), year(yr), month(mo), day(da), 
      maxSpeed(maxSp), fuelConsumptionFactor(fuelConsFact),
      processor(sensorData) {
    fillData(sensorData);
}
//=============================================================================
// Function: run
// Description: Performs the requested data processing and prints the result.
//=============================================================================
int SensorDataManager::run() {
    // Create instance of SensorDataProcessor
    SensorDataProcessor processor(sensorData);

    // Process data based on menu selection & print result
    switch (menuSelection) {
    case 1:
        std::cout << "Altitude readings: " 
                  << processor.countAltitudeData(year, month, day) 
                  << std::endl;
        break;
    case 2:
        if (processor.checkMaxSpeed(maxSpeed))
            std::cout << "Max speed reached" << std::endl;
        else
            std::cout << "Max speed not reached" << std::endl;
        break;
    case 3:
        if (processor.updateFuelConsumption(fuelConsumptionFactor))
            std::cout << "Fuel consumption updated" << std::endl;
        else
            std::cout << "Fuel consumption not updated" << std::endl;
        break;
    }

    return 0; // execution success
}