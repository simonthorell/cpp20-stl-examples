#include "sensor_data/sensor_data.h"
#include "sensor_data/sensor_data_processor.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

//=============================================================================
//                        Sensor Data Class Implementation
//=============================================================================

SensorType SensorData::GetSensorType() { return sensorType; }
float SensorData::GetValue() { return value; }
void SensorData::SetValue(float v) { value = v; }
std::time_t SensorData::GetTime() { return time; }

SensorData::SensorData(SensorType sensorType, float value, std::time_t time) {
	this->value = value;
	this->sensorType = sensorType;
	this->time = time;
}

//=============================================================================
//                       Utility Function Implementations
//=============================================================================

void FillData(std::vector<SensorData>& v) {
	srand(std::time(NULL));

	std::time_t tid = CreateTime(2012, 1, 1, 1, 1, 1 );
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

std::time_t CreateTime(int year, int month, int day, int hour, int minute, 
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

//=============================================================================
//                        Main Functions Implementations
//=============================================================================

int sensor_data(char menuSelection) {
	constexpr uint16_t YEAR = 2012;
	constexpr uint8_t MONTH = 1;
	constexpr uint8_t DAY = 2;
	constexpr float MAX_SPEED = 99.9f;
	constexpr float FUEL_CONSUMPTION_FACTOR = 1.75f;

	std::vector<SensorData> sensorData;
	FillData(sensorData);

	// Create an instance of SensorDataProcessor with the filled sensor data
	SensorDataProcessor processor(sensorData);

	// Perform the requested operation
	switch (menuSelection) {
	case '1':
		std::cout << "Altitude readings: " 
		          << processor.countAltitudeData(YEAR, MONTH, DAY) 
			      << std::endl;
		break;
	case '2':
		if (processor.checkMaxSpeed(MAX_SPEED))
			std::cout << "Max speed reached" << std::endl;
		else
			std::cout << "Max speed not reached" << std::endl;
		break;
	case '3':
		if (processor.updateFuelConsumption(FUEL_CONSUMPTION_FACTOR))
			std::cout << "Fuel consumption updated" << std::endl;
		else
			std::cout << "Fuel consumption not updated" << std::endl;
		break;
	}

	return 0; // execution success
}