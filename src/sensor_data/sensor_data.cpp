#include "sensor_data/sensor_data.h"
#include "sensor_data/sensor_data_processor.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstdint>
//=============================================================================
// Constructor: SensorData
// Description: Initializes a new instance of SensorData with the given type, 
//              value, and timestamp.
//=============================================================================
SensorData::SensorData(SensorType sensorType, float value, std::time_t time) {
    this->value = value;
    this->sensorType = sensorType;
    this->time = time;
}
//=============================================================================
// Getter Methods: GetSensorType, GetValue, SetValue, GetTime
// Description: Provides access to SensorData's attributes and allows value
//              modification.
//=============================================================================
SensorType SensorData::getSensorType() { return sensorType; }
float SensorData::getValue() { return value; }
void SensorData::setValue(float v) { value = v; }
std::time_t SensorData::getTime() { return time; }
//=============================================================================
// Function: FillData
// Description: Populates a vector with random sensor data readings.
//=============================================================================
void fillData(std::vector<SensorData>& v) {
	srand(std::time(NULL));

	std::time_t tid = createTime(2012, 1, 1, 1, 1, 1 );
	for (int i = 0; i < 100000; i++) {
		SensorType type = static_cast<SensorType>(rand() % 3);
		float value = 0.0f;
		if (type == SensorType::Altitude)
			value = rand() % 1000;
		else if (type == SensorType::FuelConsumption)
			value = rand() * 3.0f;
		else if (type == SensorType::SpeedInKmh)
			value = rand() % 110;
		else
		{
			value = 99;
		}
		v.push_back(SensorData(type,value,tid));
		tid = tid + rand() % 10 + 1;
	}
}
//=============================================================================
// Function: CreateTime
// Description: Constructs a time_t object representing the given date and time.
//=============================================================================
std::time_t createTime(int year, int month, int day, int hour, int minute, 
                       int second) {
	struct tm tid = { 0 };
	tid.tm_year = year-1900;
	tid.tm_mon = month - 1;
	tid.tm_mday = day;
	tid.tm_hour = hour;
	tid.tm_min = minute;
	tid.tm_sec = second;
	return mktime(&tid);
}