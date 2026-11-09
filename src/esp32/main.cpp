#include <Arduino.h>

//pins connected to the STM32
#define STM32_RX_PIN 44 //connects to STM32 PA2(TX)
#define STM32_TX_PIN 43 //connects to STM32 PA3(RX)

//UART port 1 on ESP32
HardwareSerial StmSerial(1);

void setup() {
  //start USB serial
  Serial.begin(115200);
  
  //start UART with STM32
  StmSerial.begin(115200, SERIAL_8N1, STM32_RX_PIN, STM32_TX_PIN);
  
  delay(2000); 
  Serial.println("XIAO ESP32-S3. Listening to STM32");
}

void loop() {
  //read from STM32 and print to pc
  if (StmSerial.available()) {
    String msgFromSTM32 = StmSerial.readStringUntil('\n');
    Serial.print("[STM32] ");
    Serial.println(msgFromSTM32);
  }

  //read pc serial monitor and send to STM32
  if (Serial.available()) {
    String commandFromPC = Serial.readStringUntil('\n');
    commandFromPC.trim(); //clean up carriage returns
    
    if (commandFromPC.length() > 0) {
      Serial.print("[ESP32 Sending] ");
      Serial.println(commandFromPC);
      
      StmSerial.print(commandFromPC);
      StmSerial.print('\n');
    }
  }
}