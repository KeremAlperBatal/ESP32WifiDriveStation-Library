#ifndef WiFiDriveStation_h
#define WiFiDriveStation_h

#include <Arduino.h>
#include <WiFi.h>

class WiFiDriveStation {
  public:
    WiFiDriveStation(const char* ssid, const char* password);
    void begin();
    void update();

    // Set Init and Periodic methods
    void setTeleopInitMethod(void (*initMethod)());
    void setTeleopPeriodicMethod(void (*periodicMethod)());
    void setAutonomInitMethod(void (*initMethod)());
    void setAutonomPeriodicMethod(void (*periodicMethod)());
    void setDisableInitMethod(void (*initMethod)());
    void setDisablePeriodicMethod(void (*periodicMethod)());

  private:
    enum Mode {
      TELEOP,
      AUTONOM,
      DISABLE
    };

    Mode currentMode = DISABLE;
    Mode previousMode = DISABLE;
    bool initRequired = false;

    // Function pointers
    void (*teleopInitFunc)();
    void (*teleopPeriodicFunc)();
    void (*autonomInitFunc)();
    void (*autonomPeriodicFunc)();
    void (*disableInitFunc)();
    void (*disablePeriodicFunc)();

    // WiFi credentials
    const char* ssid;
    const char* password;

    void handleClient();
    void changeMode(Mode mode);
};

#endif
