#include "UNO_serial.h"

UNO_Serial uno_serial = UNO_Serial();
long previousSERIAL = 0;

void setup() {
  Serial.begin(9600);
  uno_serial.serial_setup();

}

void loop() 
{ 
  unsigned long current_t = millis();

  if(current_t - previousSERIAL >= 300){       //run the Serial communication every Serial_timer value
     previousSERIAL = current_t;
     uno_serial.exchange_data_with_esp32();
  }
  
}
