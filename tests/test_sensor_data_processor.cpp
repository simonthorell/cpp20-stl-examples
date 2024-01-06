//==============================================================================
// SENSOR DATA TEST SUITE
//==============================================================================
#include <gtest/gtest.h>
#include <vector>
#include <ctime>
#include "sensor_data/sensor_data_processor.h"
//==============================================================================
// Mock Data Creation
// Description: This section contains the CreateTime function, which generates
//              a vector of mock SensorData objects for testing purposes. It
//              simulates realistic sensor data, including altitude readings
//              and various other types with different timestamps.
//==============================================================================
std::time_t now = std::time(nullptr);
std::time_t today = std::mktime(std::localtime(&now));
std::time_t yesterday = today - (24 * 60 * 60); // 24 hours ago

// TODO: Implement/replace with gmock?
std::vector<SensorData> createMockSensorData(int numAltitudeReadings, 
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
    // On the target day
    data.emplace_back(SensorType::FuelConsumption, 300.0f, today);
    // Add more varied fuel consumption data
    data.emplace_back(SensorType::FuelConsumption, 250.0f, today + 500);
    data.emplace_back(SensorType::FuelConsumption, 350.0f, today - 500);

    return data;
}
//==============================================================================
// SensorDataProcessorTest Class
// Description: This class defines the test fixture for the SensorDataProcessor
//              class. It sets up the testing environment and includes all the
//              test cases for the SensorDataProcessor class.
//==============================================================================
class SensorDataProcessorTest : public ::testing::Test {
protected:
    std::vector<SensorData> data;
    SensorDataProcessor* processor;

    // You can define helper functions here if needed
    void SetUp() override {
        // Initialize with some default data
        data = createMockSensorData(5, yesterday, today);
        processor = new SensorDataProcessor(data);
    }

    void TearDown() override {
        delete processor;
    }
};
//==============================================================================
// Altimeter Data Processing Tests
// Description: This subsection includes tests focused on verifying the accuracy
//              and reliability of altitude data processing within the
//              SensorDataProcessor. It checks for correct altitude count and
//              handling of various altimeter reading scenarios.
//==============================================================================
TEST(SensorDataProcessorTest, CountAltitudeData) {
    // Define target date
    constexpr u_int16_t YEAR = 2012;
    constexpr u_int8_t MONTH = 1;
    constexpr u_int8_t DAY = 2;
    // Define target start time
    std::time_t targetTimeStart = createTime(YEAR, MONTH, DAY, 0, 0, 0);
    // Define target end time
    struct tm nextDay = *localtime(&targetTimeStart);
    nextDay.tm_mday += 1;  // Move to the next day
    std::time_t targetTimeEnd = mktime(&nextDay);
    
    // Create a processor with mock data
    auto data = createMockSensorData(5000, targetTimeStart, targetTimeEnd);
    SensorDataProcessor processor(data);

    // Test counting exactly 5000 altitude data entries
    EXPECT_EQ(processor.countAltitudeData(YEAR, MONTH, DAY), 5000);

    // Test counting more than 5000 altitude data entries
    data = createMockSensorData(5500, targetTimeStart, targetTimeEnd);
    processor = SensorDataProcessor(data);
    EXPECT_EQ(processor.countAltitudeData(YEAR, MONTH, DAY), 5500);

    // Test counting fewer than 5000 altitude data entries
    data = createMockSensorData(4500, targetTimeStart, targetTimeEnd);
    processor = SensorDataProcessor(data);
    EXPECT_EQ(processor.countAltitudeData(YEAR, MONTH, DAY), 4500);

    // Test counting with no altitude data entries
    data.clear();
    processor = SensorDataProcessor(data);
    EXPECT_EQ(processor.countAltitudeData(YEAR, MONTH, DAY), 0);
}
//==============================================================================
// Speed Data Processing Tests
// Description: This subsection includes tests focused on verifying the accuracy
//              and reliability of speed data processing within the
//              SensorDataProcessor. It checks for correct speed threshold
//              handling and reporting.
//==============================================================================
// Test case for data with valid speed below the threshold
TEST(SensorDataProcessorTest, ReturnsFalseForValidSpeedBelowThreshold) {
    std::vector<SensorData> data = createMockSensorData(5, yesterday, today);
    data.emplace_back(SensorType::SpeedInKmh, 99.889f, today);
    // Create a new instance with the updated data
    SensorDataProcessor processor(data); 
    EXPECT_FALSE(processor.checkMaxSpeed(99.9f));
}

// Test case for data with a speed exceeding the threshold
TEST(SensorDataProcessorTest, ReturnsTrueForValidSpeedAboveThreshold) {
    std::vector<SensorData> data = createMockSensorData(5, yesterday, today);
    data.emplace_back(SensorType::SpeedInKmh, 99.901f, today);
    // Create a new instance with the updated data
    SensorDataProcessor processor(data); 
    EXPECT_TRUE(processor.checkMaxSpeed(99.9f));
}
//==============================================================================
// Fuel Consumption Update Tests
// Description: This subsection includes tests focused on verifying the accuracy
//              and reliability of fuel consumption data processing within the
//              SensorDataProcessor. It checks for correct fuel consumption
//              update handling and reporting.
//==============================================================================
// Test updating when fuel consumption entries are present and factor is not 0
TEST(SensorDataProcessorTest, UpdatesFuelConsumptionWhenFactorNotZero) {
    // Create mock data with some FuelConsumption entries
    std::vector<SensorData> data = createMockSensorData(5, yesterday, today);

    // Create a new instance with the mock data
    SensorDataProcessor processor(data);

    // Apply the update
    float factor = 1.75; // 175% update factor
    bool updated = processor.updateFuelConsumption(factor);
    EXPECT_TRUE(updated) << "Expected fuel consumption data to be updated.";
}

// Test that no update occurs when the factor is 0
TEST(SensorDataProcessorTest, DoesNotUpdateFuelConsumptionWhenFactorIsZero) {
    // Create mock data with some FuelConsumption entries
    std::vector<SensorData> data = createMockSensorData(5, yesterday, today);

    // Create a new instance with the mock data
    SensorDataProcessor processor(data);

    // Apply the update with a factor of 0
    float factor = 0; // 0% update factor
    bool updated = processor.updateFuelConsumption(factor);
    EXPECT_FALSE(updated) << "No fuel consumption data should be updated when factor is 0.";
}

// Test that no update occurs and returns false when there are no FuelConsumption entries
TEST(SensorDataProcessorTest, ReturnsFalseWhenNoFuelConsumptionEntries) {
    // Create mock data without any FuelConsumption entries
    std::vector<SensorData> data = createMockSensorData(5, yesterday, today);
    // Optionally remove any accidental FuelConsumption entries
    data.erase(std::remove_if(data.begin(), data.end(), [](SensorData& entry) {
        return entry.getSensorType() == SensorType::FuelConsumption;
    }), data.end());

    // Create a new instance with the mock data
    SensorDataProcessor processor(data);

    // Apply the update with any factor
    float factor = 1.25f; // The specific factor is irrelevant in this case
    bool updated = processor.updateFuelConsumption(factor);

    // Expect the function to report no updates
    EXPECT_FALSE(updated) << "Expected no updates when there are no FuelConsumption entries.";
}