/*
 * This is a simple script that utilizes Intel's CurieBLE library for a basic BLE terminal
 */

#include <CurieBLE.h>

//----------------------------------------------------------- BLE declaring
BLEPeripheral blePeripheral;  
BLEService InitAdmin("41300000-EB90-09D7-0001-413031360000");     
BLECharacteristic Terminal("41300001-EB90-09D7-0001-413031360000", BLERead | BLEWrite | BLENotify,16);

//---------------------------------------------------------------------- Global Variables
char BLEString[32] ;

//----------------------------------------------------------------- Initialisation

void setup() 
{
  Serial.begin(9600);
  
  // Set advertised local name and service UUID: 
  blePeripheral.setLocalName("Terminal"); 

  // Add Service & Caracteristic
  blePeripheral.addAttribute(InitAdmin);
  blePeripheral.addAttribute(Terminal);

  // BLE Events
  Terminal.setEventHandler(BLEWritten, switchCharacteristicWritten);

  // begin advertising BLE service:
  blePeripheral.begin();
}

void loop() 
{
  blePeripheral.poll();
}

void switchCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  sprintf(BLEString,"%16c",NULL);
  strncpy(BLEString,(char*)Terminal.value(),Terminal.valueLength());
  Serial.println(BLEString); 
  
  Terminal.setValue("TEST");
}
