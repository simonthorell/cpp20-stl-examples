# C++20 STL & Algorithms with Unit Tests, API's and External Libraries

This repository explores the features and capabilities of the modern C++20 Standard Template Library (STL) and various algorithms, including practical applications of the NHL API and integration of external libraries such as libcurl and nlohmann/json. It demonstrates problem-solving techniques and data handling using CMake for fetching and managing external libraries. The initial project structure was created with [this template](https://github.com/simonthorell/cpp-cmake-googletest.git). For more inspiration, check out the GitHub of the incredible programmer [Stefan Holmberg](https://github.com/aspcodenet).

## Part 1: Utilizing Algorithms

**Objective**: Count the number of sensor data registrations for Altitude on specified date (2012-01-02).

**Approach**: We use code from [this gist](https://gist.github.com/aspcodenet/35b137316df262ff744e3a583bb388d0) as a starting point, focusing on applying STL algorithms to efficiently process and count specific sensor data.

## Part 2: Algorithm Application

**Objective**: Determine if any SpeedInKmh registration has exceeded specified maxSpeed (99.9).

**Approach**: Building upon the code from [the same gist](https://gist.github.com/aspcodenet/35b137316df262ff744e3a583bb388d0), we will utilize algorithms to check for max speed registration. The console will display "Max speed reached" if any registration exceeds 99.9, otherwise, it will show "No max speed reached."

## Part 3: Algorithm Enhancement

**Objective**: Update FuelConsumption sensor data by increasing it by specified factor (75%).

**Approach**: Using the code from [here](https://gist.github.com/aspcodenet/35b137316df262ff744e3a583bb388d0), we will address the issue with the FuelConsumption sensor. Algorithms will be used to modify the data, reflecting the necessary increase.

## Part 4: Advanced Application - Queue

**Objective**: Create a healthcare center simulator.

**Approach**: This involves creating an infinite loop where a user can add a new customer to the queue or call the next customer. A customer is represented as a class with attributes like Queue Number, Name, and Arrival Time.

## Part 5: Advanced Application - Map

**Objective**: Construct an ATM system using a map.

**Approach**: The key will be the Account Number, and the value will be the balance. The system will allow creating an account, logging in, depositing, and withdrawing money.

## Part 6: Advanced Application - File Handling, Caching, and NHL API Integration

**Objective**:

The objective of the `LRUCache` class is to manage hockey player data efficiently. It aims to provide quick access to player records using a Least Recently Used (LRU) caching mechanism, while integrating data from the NHL API for a comprehensive dataset.

**Approach**:

The `LRUCache` class achieves this by storing up to ten `HockeyPlayer` objects. It provides the method `GetPlayer(int id)` that retrieves a player by their ID. If the player is already in the cache, it is returned immediately. If not, the player is fetched from the larger dataset, added to the cache, and then returned. This method ensures that the most recently accessed players are always quickly accessible, while the cache size remains fixed and manageable.

### NHL API Integration:

The project integrates the NHL API to fetch real-time data on hockey players. This API provides detailed information about players, including their stats, team associations, and more. We utilize the `HockeyData` class to handle API requests and parse the received JSON data into `HockeyPlayer` objects. The API integration involves:

- Fetching player data using specific endpoints of the NHL API.
- Parsing the JSON response to extract relevant player information.
- Dynamically handling different data formats and potential `null` values in the response.

### CMake Configuration for External Libraries:

To facilitate the handling of JSON data from the NHL API, the project uses the nlohmann/json library. Additionally, network requests to the NHL API are managed using the libcurl library. The CMake configuration has been set up to fetch these external libraries. Key aspects of this configuration include:

- Utilizing `FetchContent` in CMake to download and integrate the nlohmann/json and libcurl libraries into the project.
- Setting up the appropriate `target_link_libraries` to ensure these libraries are correctly linked during compilation.
- Handling dependencies and ensuring compatibility with the C++20 standard.

This integration allows the application to seamlessly retrieve and process data from the NHL API, enhancing the project's functionality and demonstrating modern C++ development practices.

## License

This project is licensed under the MIT License.

### MIT License

Copyright (c) 2024 Simon Thorell

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.