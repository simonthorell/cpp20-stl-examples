#include <gtest/gtest.h>

// Include Test Suites
#include "test_sensor_data_processor.cpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
