#include <Arduino.h>

HardwareSerial& EspSerial = Serial;

void setup() {
  //start UART with ESP32
  EspSerial.begin(115200);
}

void loop() {
  //check if the ESP32 sent anything
  if (EspSerial.available()) {
    String incoming = EspSerial.readStringUntil('\n');
    
    //reply to acknowledge received
    EspSerial.print("STM32 Ack: ");
    EspSerial.println(incoming);
  }

  //heartbeat
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 2000) {
    EspSerial.println("Hello from STM32G431!");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Toggle LED
    lastTime = millis();
  }
}