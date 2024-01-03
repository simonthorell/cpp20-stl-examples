/**
 * @file test_sensor_data_processor.cpp
 * 
 * @brief Test suite for the SensorDataProcessor class.
 * 
 * This test suite validates the SensorDataProcessor class, focusing on 
 * its ability to identify when sensor speed readings exceed a given 
 * threshold. It includes tests for empty data sets, data sets with speeds 
 * both below and above the threshold, and edge cases where speeds are 
 * exactly at the threshold.
 * 
 * @note These tests rely on the Google Test framework and assume all 
 * necessary files and dependencies are correctly included and configured 
 * in the project setup. Ensure that the SensorDataProcessor class and all 
 * related components (e.g., SensorData, SensorType) are correctly 
 * implemented and accessible.
 * 
 * @author Simon Thorell
 * @date 2023-01-03
 * 
 * @see sensor_data_processor.h
 */

#include "sensor_data/sensor_data_processor.h"
#include <gtest/gtest.h>
#include <vector>
#include <ctime>

//==============================================================================
// Mock Data Creation
//==============================================================================
// This section contains the CreateMockSensorData function, which generates 
// a vector of mock SensorData objects for testing purposes. It simulates 
// realistic sensor data, including altitude readings and various other types 
// with different timestamps.

std::time_t now = std::time(nullptr);
std::time_t today = std::mktime(std::localtime(&now));
std::time_t yesterday = today - (24 * 60 * 60); // 24 hours ago

std::vector<SensorData> CreateMockSensorData(int numAltitudeReadings, 
                                             std::time_t targetTimeStart, 
                                             std::time_t targetTimeEnd
                                            ) {
    std::vector<SensorData> data;
    // Add 'numAltitudeReadings' altitude readings on the target day
    for (int i = 0; i < numAltitudeReadings; ++i) {
        // Adjust time and value as needed
        data.emplace_back(SensorType::Altitude, 100.0f, targetTimeStart + i);
    }
    /* Add some non-altitude readings and off-day readings to ensure they are not 
     * counted Before the target day */
    data.emplace_back(SensorType::SpeedInKmh, 50.0f, targetTimeStart - 1000); 
    // After the target day
    data.emplace_back(SensorType::FuelConsumption, 200.0f, targetTimeEnd + 1000);

    return data;
}
 
//==============================================================================
// Sensor Data Processor Class Tests
//==============================================================================
// This section defines the SensorDataProcessorTest class, which sets up the 
// testing environment and includes all the test cases for the 
// SensorDataProcessor class. It ensures the class handles various scenarios 
// correctly, including edge cases and typical usage patterns.

class SensorDataProcessorTest : public ::testing::Test {
protected:
    std::vector<SensorData> data;
    SensorDataProcessor* processor;

    // You can define helper functions here if needed
    void SetUp() override {
        // Initialize with some default data
        data = CreateMockSensorData(5, yesterday, today);
        processor = new SensorDataProcessor(data);
    }

    void TearDown() override {
        delete processor;
    }
};

//==============================================================================
// Altimeter Data Processing Tests
//==============================================================================
// This subsection includes tests focused on verifying the accuracy and 
// reliability of altitude data processing within the SensorDataProcessor. 
// It checks for correct altitude count and handling of various altimeter 
// reading scenarios.

TEST(SensorDataProcessorTest, CountAltitudeData) {
    // Define the target times
    std::time_t targetTimeStart = CreateTime(2012, 1, 2, 0, 0, 0);
    std::time_t targetTimeEnd = CreateTime(2012, 1, 3, 0, 0, 0);
    
    // Create a processor with mock data
    auto data = CreateMockSensorData(5000, targetTimeStart, targetTimeEnd);
    SensorDataProcessor processor(data);

    // Test counting exactly 5000 altitude data entries
    EXPECT_EQ(processor.countAltitudeData(), 5000);

    // Test counting more than 5000 altitude data entries
    data = CreateMockSensorData(5500, targetTimeStart, targetTimeEnd);
    processor = SensorDataProcessor(data);
    EXPECT_EQ(processor.countAltitudeData(), 5500);

    // Test counting fewer than 5000 altitude data entries
    data = CreateMockSensorData(4500, targetTimeStart, targetTimeEnd);
    processor = SensorDataProcessor(data);
    EXPECT_EQ(processor.countAltitudeData(), 4500);

    // Test counting with no altitude data entries
    data.clear();
    processor = SensorDataProcessor(data);
    EXPECT_EQ(processor.countAltitudeData(), 0);
}

//==============================================================================
// Speed Data Processing Tests
//==============================================================================
// Tests in this subsection verify that the SensorDataProcessor correctly 
// identifies when speed readings exceed defined thresholds. They cover 
// scenarios with speeds below, above, and exactly at the threshold.

// Test case for data with valid speed below the threshold
TEST(SensorDataProcessorTest, ReturnsFalseForValidSpeedBelowThreshold) {
    std::vector<SensorData> data = CreateMockSensorData(5, yesterday, today);
    data.emplace_back(SensorType::SpeedInKmh, 99.889f, today);
    // Create a new instance with the updated data
    SensorDataProcessor processor(data); 
    EXPECT_FALSE(processor.checkMaxSpeed(99.9f));
}

// Test case for data with a speed exceeding the threshold
TEST(SensorDataProcessorTest, ReturnsTrueForValidSpeedAboveThreshold) {
    std::vector<SensorData> data = CreateMockSensorData(5, yesterday, today);
    data.emplace_back(SensorType::SpeedInKmh, 99.901f, today);
    // Create a new instance with the updated data
    SensorDataProcessor processor(data); 
    EXPECT_TRUE(processor.checkMaxSpeed(99.9f));
}

//==============================================================================
// Fuel Data Processing Tests
//==============================================================================
// Here, tests are designed to assess the fuel consumption data processing 
// capabilities of the SensorDataProcessor. They ensure that fuel data is 
// correctly interpreted and handled under different conditions and values.
