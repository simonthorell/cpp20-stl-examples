#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <ctime>
#include <vector>
#include <string>

//=============================================================================
//                          SensorType Enumeration
//=============================================================================

enum class SensorType {
	Altitude,
	SpeedInKmh,
	FuelConsumption
};

//=============================================================================
//                       SensorData Class Declaration
//=============================================================================

class SensorData {
	float value;
	SensorType sensorType;
	time_t time;
public:
	SensorType GetSensorType();
	float GetValue();
	void SetValue(float v);
	time_t GetTime();
	SensorData(SensorType sensorType, float value, time_t time);
};

//=============================================================================
//                              Utility Functions
//=============================================================================

void FillData(std::vector<SensorData> &v);
time_t CreateTime(int year, int month, int day, int hour, int minute, 
                  int second);

//=============================================================================
//                          Main Interface Functions
//=============================================================================

int sensor_data(char menuSelection);

#endif // SENSOR_DATA_H