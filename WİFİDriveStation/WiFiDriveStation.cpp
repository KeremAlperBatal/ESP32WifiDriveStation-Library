#include "WiFiDriveStation.h"

WiFiServer server(80);

WiFiDriveStation::WiFiDriveStation(const char* ssid, const char* password)
  : ssid(ssid), password(password) {}

void WiFiDriveStation::begin() {
  Serial.begin(9600);

  // Start WiFi in AP mode
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP started.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Start server
  server.begin();
}

void WiFiDriveStation::update() {
  handleClient();

  // Check for mode change
  if (currentMode != previousMode) {
    initRequired = true;
    previousMode = currentMode;
  } else {
    initRequired = false;
  }

  // Call Init method when mode changes
  if (initRequired) {
    switch (currentMode) {
      case TELEOP: if (teleopInitFunc) teleopInitFunc(); break;
      case AUTONOM: if (autonomInitFunc) autonomInitFunc(); break;
      case DISABLE: if (disableInitFunc) disableInitFunc(); break;
    }
  }

  // Call Periodic method
  switch (currentMode) {
    case TELEOP: if (teleopPeriodicFunc) teleopPeriodicFunc(); break;
    case AUTONOM: if (autonomPeriodicFunc) autonomPeriodicFunc(); break;
    case DISABLE: if (disablePeriodicFunc) disablePeriodicFunc(); break;
  }
}

void WiFiDriveStation::handleClient() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("/teleop") != -1) {
    changeMode(TELEOP);
  } else if (request.indexOf("/autonom") != -1) {
    changeMode(AUTONOM);
  } else if (request.indexOf("/disable") != -1) {
    changeMode(DISABLE);
  }

  // Send response
  String html = "<h1>Control Panel</h1>"
                "<button onclick=\"location.href='/teleop'\">Teleop</button><br>"
                "<button onclick=\"location.href='/autonom'\">Autonom</button><br>"
                "<button onclick=\"location.href='/disable'\">Disable</button><br>";
  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + html);
  client.stop();
}

void WiFiDriveStation::changeMode(Mode mode) {
  currentMode = mode;
}

void WiFiDriveStation::setTeleopInitMethod(void (*initMethod)()) {
  teleopInitFunc = initMethod;
}

void WiFiDriveStation::setTeleopPeriodicMethod(void (*periodicMethod)()) {
  teleopPeriodicFunc = periodicMethod;
}

void WiFiDriveStation::setAutonomInitMethod(void (*initMethod)()) {
  autonomInitFunc = initMethod;
}

void WiFiDriveStation::setAutonomPeriodicMethod(void (*periodicMethod)()) {
  autonomPeriodicFunc = periodicMethod;
}

void WiFiDriveStation::setDisableInitMethod(void (*initMethod)()) {
  disableInitFunc = initMethod;
}

void WiFiDriveStation::setDisablePeriodicMethod(void (*periodicMethod)()) {
  disablePeriodicFunc = periodicMethod;
}
