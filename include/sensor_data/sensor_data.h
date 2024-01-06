#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <ctime>
#include <vector>
#include <string>

enum class SensorType {
	Altitude,
	SpeedInKmh,
	FuelConsumption
};

class SensorData {
	float value;
	SensorType sensorType;
	time_t time;
public:
	// Constructor
	SensorData(SensorType sensorType, float value, time_t time);
	// Getter Methods
	SensorType GetSensorType();
	float GetValue();
	void SetValue(float v);
	time_t GetTime();
};

// Function prototypes
void FillData(std::vector<SensorData> &v);
time_t CreateTime(int year, int month, int day, int hour, int minute, 
                  int second);
				  
// Main function for sensor data
int sensor_data(char menuSelection);

#endif // SENSOR_DATA_H