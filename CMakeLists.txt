cmake_minimum_required(VERSION 3.28)
project(MyProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetches libcurl from github
include(FetchContent)
FetchContent_Declare(
  libcurl
  GIT_REPOSITORY https://github.com/curl/curl.git
  GIT_TAG curl-8_5_0
)
FetchContent_MakeAvailable(libcurl)

# Fetches the json library from github
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Add the subdirectories
add_subdirectory(src)
add_subdirectory(tests)

# Add compiler options
add_compile_options(
   -Werror    # Treat warnings as errors
   -Wall      # Enable all warnings
   -Wextra    # Enable extra warnings
   -pedantic  # Ensure standards-compliant code
)