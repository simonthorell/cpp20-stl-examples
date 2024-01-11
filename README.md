# C++20 STL & Algorithms with unit tests

This repository is dedicated to exploring the features and capabilities of the modern C++20 Standard Template Library (STL) and various algorithms. It demonstrates practical applications and problem-solving techniques using the latest C++ standards. The project structure and initial setup were inspired by and created with [this template](https://github.com/simonthorell/cpp-cmake-googletest.git).  
If you get inspired by this repo you need to checkout the github of this incredible programmer: [Stefan Holmberg](https://github.com/aspcodenet).

## Part 1: Utilizing Algorithms

**Objective**: Count the number of sensor data registrations for Altitude on 2012-01-02.

**Approach**: We will use the code from [this gist](https://gist.github.com/aspcodenet/35b137316df262ff744e3a583bb388d0) as our starting point. The focus is on applying STL algorithms to efficiently process and count specific sensor data.

## Part 2: Algorithm Application

**Objective**: Determine if any SpeedInKmh registration has exceeded 99.9.

**Approach**: Building upon the code from [the same gist](https://gist.github.com/aspcodenet/35b137316df262ff744e3a583bb388d0), we will utilize algorithms to check for max speed registration. The console will display "Max speed reached" if any registration exceeds 99.9, otherwise, it will show "No max speed reached."

## Part 3: Algorithm Enhancement

**Objective**: Update FuelConsumption sensor data by increasing it by 75%.

**Approach**: Using the code from [here](https://gist.github.com/aspcodenet/35b137316df262ff744e3a583bb388d0), we will address the issue with the FuelConsumption sensor. Algorithms will be used to modify the data, reflecting the necessary increase.

## Part 4: Advanced Application - Queue

**Objective**: Create a healthcare center simulator.

**Approach**: This involves creating an infinite loop where a user can add a new customer to the queue or call the next customer. A customer is represented as a class with attributes like Queue Number, Name, and Arrival Time.

## Part 5: Advanced Application - Map

**Objective**: Construct an ATM system using a map.

**Approach**: The key will be the Account Number, and the value will be the balance. The system will allow creating an account, logging in, depositing, and withdrawing money.

## Part 6: Advanced Application - File Handling and Caching

**Objective:**

The objective of the `LRUCache` class is to manage hockey player data efficiently. It aims to provide quick access to player records using a Least Recently Used (LRU) caching mechanism.

**Approach:**

The `LRUCache` class achieves this by storing up to ten `HockeyPlayer` objects. It provides the method `GetPlayer(int id)` that retrieves a player by their ID. If the player is already in the cache, it is returned immediately. If not, the player is fetched from the larger dataset, added to the cache, and then returned. This method ensures that the most recently accessed players are always quickly accessible, while the cache size remains fixed and manageable.
