# WiFiDriveStation Library

The `WiFiDriveStation` library is developed for ESP32-based projects to control a robot over WiFi. This library enables controlling the robot's **Teleoperation (Teleop)**, **Autonomous**, and **Disable** modes via a web server. Users can switch between modes and trigger related functions through a web browser.

## Features
- **Web-based control**: Control your robot over WiFi by running a web server.
- **Mode switching**: Switch between Teleop, Autonomous, and Disable modes.
- **Functions**: Define separate initialization (`init`) and periodic (`periodic`) functions for each mode.
- **Simple structure**: Easily control your robot with a user-friendly API.

## Requirements
- **ESP32**: This library is compatible only with ESP32-based boards.
- **WiFi Connection**: Requires connection to a WiFi network and WiFi AP mode.
- **Arduino IDE**: You need to install the Arduino IDE to use this library.

## Installation

### Installation via Arduino IDE

1. Open **Arduino IDE** and add support for **ESP32** boards:
   - In Arduino IDE, go to `File` > `Preferences`.
   - Add the following URL to the "Additional Boards Manager URLs" section:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```

2. **Select the ESP32 board**:
   - Go to `Tools` > `Board` > `ESP32 Dev Module`.

3. **Install the WiFiDriveStation Library**:
   - Download the `WiFiDriveStation` library from GitHub or add it as a ZIP file.
   - In Arduino IDE, go to `Sketch` > `Include Library` > `Add .ZIP Library...` to add the library.

## Usage

### Example Code:

```cpp
#include <WiFiDriveStation.h>

const char* ssid = "WiFi_Network_Name";        // WiFi network name
const char* password = "WiFi_Password";        // WiFi password

WiFiDriveStation driveStation(ssid, password);

void setup() {
  Serial.begin(115200);
  driveStation.begin();
  
  // Set initialization and periodic functions for Teleop mode
  driveStation.setTeleopInitMethod(teleopInit);
  driveStation.setTeleopPeriodicMethod(teleopPeriodic);
  
  // Set initialization and periodic functions for Autonomous mode
  driveStation.setAutonomInitMethod(autonomInit);
  driveStation.setAutonomPeriodicMethod(autonomPeriodic);
  
  // Set initialization and periodic functions for Disable mode
  driveStation.setDisableInitMethod(disableInit);
  driveStation.setDisablePeriodicMethod(disablePeriodic);
}

void loop() {
  // Check for incoming client requests via the web
  driveStation.update();
}

// Teleop initialization function
void teleopInit() {
  // Initialization tasks for Teleop mode
}

// Teleop periodic function
void teleopPeriodic() {
  // Periodic tasks for Teleop mode
}

// Autonomous initialization function
void autonomInit() {
  // Initialization tasks for Autonomous mode
}

// Autonomous periodic function
void autonomPeriodic() {
  // Periodic tasks for Autonomous mode
}

// Disable initialization function
void disableInit() {
  // Initialization tasks for Disable mode
}

// Disable periodic function
void disablePeriodic() {
  // Periodic tasks for Disable mode
}
```
## Functions
- **WiFiDriveStation::begin():** Starts the web server and connects the ESP32 to the WiFi network.

- **WiFiDriveStation::update():** Processes client requests from the web and calls appropriate functions based on the robot's current mode.

- **WiFiDriveStation::setTeleopInitMethod(void teleopInit):** Sets the initialization function for the Teleoperation (Teleop) mode.

- **WiFiDriveStation::setTeleopPeriodicMethod(void teleopPeriodic):** Sets the periodic function for the Teleoperation (Teleop) mode.

- **WiFiDriveStation::setAutonomInitMethod(void autonomInit):** Sets the initialization function for the Autonomous mode.

- **WiFiDriveStation::setAutonomPeriodicMethod(void autonomPeriodic):** Sets the periodic function for the Autonomous mode.

- **WiFiDriveStation::setDisableInitMethod(void disableInit)):** Sets the initialization function for the Disable mode.

- **WiFiDriveStation::setDisablePeriodicMethod(void disablePeriodic):** Sets the periodic function for the Disable mode.

## Web Interface
The WiFiDriveStation library runs a web server that lets you control the robot's mode via the following buttons:

- **Teleop:** Manually control the robot.
- **Autonom:** Switch the robot to Autonomous mode.
- **Disable:** Disable the robot.

Each button is clickable in the web browser to switch to the corresponding mode.


## License
This project is licensed under the MIT License - see the **LICENSE** file for details.

