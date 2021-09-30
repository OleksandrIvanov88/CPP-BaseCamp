cmake_minimum_required(VERSION 3.14)

project(Weather)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


## For Release - cmake -DCMAKE_BUILD_TYPE=Release ..
## For Debug - cmake -DCMAKE_BUILD_TYPE=Debug ..
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wpedantic -pthread")

add_compile_options(
  $<$<CONFIG:DEBUG>:-DDEBUG_ERROR>
  $<$<CONFIG:DEBUG>:-g3>
  $<$<CONFIG:DEBUG>:-O0>
  $<$<CONFIG:RELEASE>:-O3>
)

find_package(Boost COMPONENTS program_options REQUIRED)

set(SOURCE_LIST
    src/sources/main.cpp 
    src/sources/application.cpp
    src/sources/client.cpp
    src/sources/network.cpp
    src/sources/weather_error.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCE_LIST}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE src/headers)

target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES})
