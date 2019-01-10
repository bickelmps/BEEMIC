cmake_minimum_required(VERSION 2.8.12)

project(fly_mission)

if(NOT MSVC)
    add_definitions("-std=c++11 -Wall")
else()
    add_definitions("-std=c++11 -WX -W2")
    include_directories(${CMAKE_SOURCE_DIR}/../../install/include)
    link_directories(${CMAKE_SOURCE_DIR}/../../install/lib)
endif()

add_executable(beemic
    beemic.cpp
)

add_executable(beemic_vel
    beemic_vel.cpp
)

add_executable(main
    main.cpp
)

target_link_libraries(beemic
    dronecore
    dronecore_action
    dronecore_mission
    dronecore_telemetry
)

target_link_libraries(beemic_vel
    dronecore
    dronecore_action
    dronecore_offboard
    dronecore_telemetry
)
