/**
 * @file offboard_velocity.cpp
 * @brief Example that demonstrates offboard velocity control in local NED and
 * body coordinates
 *
 * @authors Author: Julian Oes <julian@oes.ch>,
 *                  Shakthi Prashanth <shakthi.prashanth.m@intel.com>
 * @date 2017-10-17
 */

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <thread>

#include <dronecore/action.h>
#include <dronecore/dronecore.h>
#include <dronecore/offboard.h>
#include <dronecore/telemetry.h>

using namespace dronecore;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::chrono::seconds;

#define ERROR_CONSOLE_TEXT "\033[31m"     // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m"     // Restore normal console colour

// Handles Action's result
inline void action_error_exit(ActionResult result, const std::string &message) {
  if (result != ActionResult::SUCCESS) {
    std::cerr << ERROR_CONSOLE_TEXT << message << action_result_str(result)
              << NORMAL_CONSOLE_TEXT << std::endl;
    exit(EXIT_FAILURE);
  }
}

// Handles Offboard's result
inline void offboard_error_exit(Offboard::Result result,
                                const std::string &message) {
  if (result != Offboard::Result::SUCCESS) {
    std::cerr << ERROR_CONSOLE_TEXT << message << Offboard::result_str(result)
              << NORMAL_CONSOLE_TEXT << std::endl;
    exit(EXIT_FAILURE);
  }
}

// Handles connection result
inline void connection_error_exit(ConnectionResult result,
                                  const std::string &message) {
  if (result != ConnectionResult::SUCCESS) {
    std::cerr << ERROR_CONSOLE_TEXT << message << connection_result_str(result)
              << NORMAL_CONSOLE_TEXT << std::endl;
    exit(EXIT_FAILURE);
  }
}

// Logs during Offboard control
inline void offboard_log(const std::string &offb_mode, const std::string msg) {
  std::cout << "[" << offb_mode << "] " << msg << std::endl;
}

/**
 * Does Offboard control using NED co-ordinates.
 *
 * returns true if everything went well in Offboard control, exits with a log
 * otherwise.
 */
bool offb_ctrl_ned(std::shared_ptr<dronecore::Offboard> offboard,
                   std::string &file_name, double x_gain, double y_gain,
                   double z_gain, double omega = 0) {
  const std::string offb_mode = "NED";
  // Send it once before starting offboard, otherwise it will be rejected.
  offboard->set_velocity_ned({0.0f, 0.0f, 0.0f, 0.0f});

  Offboard::Result offboard_result = offboard->start();
  offboard_error_exit(offboard_result, "Offboard start failed");
  offboard_log(offb_mode, "Offboard started");

  std::ifstream file("../data/" + file_name);
  float v_x, v_y, v_z;
  while (file >> v_x >> v_y >> v_z) {
    std::cout << v_x << " " << v_y << " " << v_z << " " << std::endl;
    for (size_t i = 0; i < 6; ++i) {
      offboard->set_velocity_ned(
          {x_gain * v_x, y_gain * v_y, -z_gain * v_z, 0.0f});
      sleep_for(milliseconds(1000 / 30));
    }
  }

  // Now, stop offboard mode.
  offboard_result = offboard->stop();
  offboard_error_exit(offboard_result, "Offboard stop failed: ");
  offboard_log(offb_mode, "Offboard stopped");

  return true;
}

/**
 * Does Offboard control using body co-ordinates.
 *
 * returns true if everything went well in Offboard control, exits with a log
 * otherwise.
 */
bool offb_ctrl_body(std::shared_ptr<dronecore::Offboard> offboard) {
  const std::string offb_mode = "BODY";

  // Send it once before starting offboard, otherwise it will be rejected.
  offboard->set_velocity_body({0.0f, 0.0f, 0.0f, 0.0f});

  Offboard::Result offboard_result = offboard->start();
  offboard_error_exit(offboard_result, "Offboard start failed: ");
  offboard_log(offb_mode, "Offboard started");

  offboard_log(offb_mode, "Turn clock-wise and climb");
  offboard->set_velocity_body({0.0f, 0.0f, -1.0f, 60.0f});
  sleep_for(seconds(5));

  offboard_log(offb_mode, "Turn back anti-clockwise");
  offboard->set_velocity_body({0.0f, 0.0f, 0.0f, -60.0f});
  sleep_for(seconds(5));

  offboard_log(offb_mode, "Wait for a bit");
  offboard->set_velocity_body({0.0f, 0.0f, 0.0f, 0.0f});
  sleep_for(seconds(2));

  offboard_log(offb_mode, "Fly a circle");
  offboard->set_velocity_body({5.0f, 0.0f, 0.0f, 30.0f});
  sleep_for(seconds(15));

  offboard_log(offb_mode, "Wait for a bit");
  offboard->set_velocity_body({0.0f, 0.0f, 0.0f, 0.0f});
  sleep_for(seconds(5));

  offboard_log(offb_mode, "Fly a circle sideways");
  offboard->set_velocity_body({0.0f, -5.0f, 0.0f, 30.0f});
  sleep_for(seconds(15));

  offboard_log(offb_mode, "Wait for a bit");
  offboard->set_velocity_body({0.0f, 0.0f, 0.0f, 0.0f});
  sleep_for(seconds(8));

  offboard_result = offboard->stop();
  offboard_error_exit(offboard_result, "Offboard stop failed: ");
  offboard_log(offb_mode, "Offboard stopped");

  return true;
}

void usage(std::string bin_name) {
  std::cout << NORMAL_CONSOLE_TEXT << "Usage : " << bin_name
            << " <connection_url>" << std::endl
            << " <file_name>" << std::endl
            << " <x_gain>" << std::endl
            << " <y_gain>" << std::endl
            << " <z_gain>" << std::endl
            << "Connection URL format should be :" << std::endl
            << " For TCP : tcp://[server_host][:server_port]" << std::endl
            << " For UDP : udp://[bind_host][:bind_port]" << std::endl
            << " For Serial : serial:///path/to/serial/dev[:baudrate]"
            << std::endl
            << "For example, to connect to the simulator use URL: udp://:14540"
            << std::endl;
}

int main(int argc, char **argv) {
  DroneCore dc;
  std::string connection_url, file_name;
  ConnectionResult connection_result;
  float x_gain, y_gain, z_gain;

  if (argc == 6) {
    connection_url = argv[1];
    file_name = argv[2];
    x_gain = std::stof(argv[3]);
    y_gain = std::stof(argv[4]);
    z_gain = std::stof(argv[5]);
    connection_result = dc.add_any_connection(connection_url);
  } else {
    usage(argv[0]);
    return 1;
  }

  if (connection_result != ConnectionResult::SUCCESS) {
    std::cout << ERROR_CONSOLE_TEXT << "Connection failed: "
              << connection_result_str(connection_result) << NORMAL_CONSOLE_TEXT
              << std::endl;
    return 1;
  }

  // Wait for the system to connect via heartbeat
  while (!dc.is_connected()) {
    std::cout << "Wait for system to connect via heartbeat" << std::endl;
    sleep_for(seconds(1));
  }

  // System got discovered.
  System &system = dc.system();
  auto action = std::make_shared<Action>(system);
  auto offboard = std::make_shared<Offboard>(system);
  auto telemetry = std::make_shared<Telemetry>(system);

  while (!telemetry->health_all_ok()) {
    std::cout << "Waiting for system to be ready" << std::endl;
    sleep_for(seconds(1));
  }
  std::cout << "System is ready" << std::endl;

  ActionResult arm_result = action->arm();
  action_error_exit(arm_result, "Arming failed");
  std::cout << "Armed" << std::endl;

  ActionResult takeoff_result = action->takeoff();
  action_error_exit(takeoff_result, "Takeoff failed");
  std::cout << "In Air..." << std::endl;
  sleep_for(seconds(5));

  //  using local NED co-ordinates
  bool ret = offb_ctrl_ned(offboard, file_name, x_gain, y_gain, z_gain);
  if (ret == false) {
    return EXIT_FAILURE;
  }

  // //  using body co-ordinates
  // ret = offb_ctrl_body(offboard);
  // if (ret == false) {
  //   return EXIT_FAILURE;
  // }

  const ActionResult land_result = action->land();
  action_error_exit(land_result, "Landing failed");

  // Check if vehicle is still in air
  while (telemetry->in_air()) {
    std::cout << "Vehicle is landing..." << std::endl;
    sleep_for(seconds(1));
  }
  std::cout << "Landed!" << std::endl;

  // We are relying on auto-disarming but let's keep watching the telemetry for
  // a bit longer.
  sleep_for(seconds(3));
  std::cout << "Finished..." << std::endl;

  return EXIT_SUCCESS;
}
