/*
 * Project Create2
 * Description: Sample code to control Create 2 via Bluetooth
 * Author: Brian Rashap
 * Date: 05-AUG-2021
 */

// Setup BLE UART

const size_t UART_TX_BUF_SIZE = 16;
uint8_t txBuf[UART_TX_BUF_SIZE];

// These UUIDs were defined by Nordic Semiconductor and are now the defacto standard for
// UART-like services over BLE. Many apps support the UUIDs now, like the Adafruit Bluefruit app.
const BleUuid serviceUuid("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid rxUuid("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid txUuid("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");

BleCharacteristic txCharacteristic("tx", BleCharacteristicProperty::NOTIFY, txUuid, serviceUuid);
BleCharacteristic rxCharacteristic("rx", BleCharacteristicProperty::WRITE_WO_RSP, rxUuid, serviceUuid, onDataReceived, NULL);
BleAdvertisingData data;

//Declare Roomba
#define Roomba Serial1
const int ddpin = D0;
const int speed = 500;

//Declare Global Variables

SYSTEM_MODE(SEMI_AUTOMATIC); //Using BLE and not Wifi

void setup() { 
    Serial.begin();
    waitFor(Serial.isConnected, 15000);  
    delay(2000);
 
    BLE.on();

    Serial.printf("Starting up BLE Connection \n");

    BLE.addCharacteristic(txCharacteristic);
    BLE.addCharacteristic(rxCharacteristic);
    data.appendServiceUUID(serviceUuid);
    BLE.advertise(&data);

    Serial.printf("Argon BLE Address: %s\n",BLE.address().toString().c_str());

    Roomba.begin(115200);
    pinMode(ddpin,OUTPUT);
    while(!Roomba);
    Serial.printf("Roomba Connected\n");
    delay(1000);
    wake();
    safeStart();
    wake();
    playSound(1);
    //helloWorld();
}

void loop() {}

//onDataReceived is used to recieve data from Bluefruit Connect App to control Roomba
void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context) {
    uint8_t i;

    Serial.printf("Received data from: %02X:%02X:%02X:%02X:%02X:%02X \n", peer.address()[0], peer.address()[1],peer.address()[2], peer.address()[3], peer.address()[4], peer.address()[5]);
    Serial.printf("Data from Bluefruit: %s\n",(char *)data);
    for (i = 0; i < len; i++) {
        Serial.printf("%02X",data[i]);
    }

    if((data[0] == 0x21) && (data[1] == 0x42)) {
      Serial.printf("\nI got directions\n");
      if(data[3] == 0x31) {
        switch (data[4]) {
          case 0x36:
            Serial.printf("FORWARD\n");
            drive(speed,0);
            break;
          case 0x35:
            Serial.printf("BACKWARD\n");
            drive(-speed,0);
            break;
          case 0x34:
            Serial.printf("LEFT\n");
            driveWheels(200, -200);
            break;
          case 0x33:
            Serial.printf("RIGHT\n");
            driveWheels(-200, 200);
            break;  
          case 0x3A:
            Serial.printf("RESTART\n");
            safeStart();
            break; 
          case 0x39:
            Serial.printf("DOCK\n");
            seekDock();
            break;
          case 0x38:
            Serial.printf("HELLO\n");
            helloWorld();
            break;
          case 0x37:
            Serial.printf("SOUND\n");
            playSound(1);
            break;             
          default:
            Serial.printf("Not Understood\n");
        }
      }
      else {
        stop();
      }

    }
    else {
      Serial.printf("I didn't understand that");
    }
}

void safeStart() {
  Roomba.write(0x80); // Start
  Roomba.write(0x83); // Safe Mode
}

void fullStart() {
  Roomba.write(0x80); // Start
  Roomba.write(0x84); // Full Control Mode
}

void drive(uint16_t speed, uint16_t radius) {
  Roomba.write(0x89);
  Roomba.write(speed >> 8);
  Roomba.write(speed & 0x00FF);
  Roomba.write(radius >> 8);
  Roomba.write(radius & 0x00FF);
}

void stop() {
  drive(0,0);
}

void driveWheels(int right, int left) {
  Roomba.write(0x91);
  Roomba.write(right >> 8);
  Roomba.write(right);
  Roomba.write(left >> 8);
  Roomba.write(left);
}

void playSound (int num)  {
  switch (num) { 
    case 1: 
      Roomba.write("\x8c\x01\x04\x42\x20\x3e\x20\x42\x20\x3e\x20"); // [140] [1] [4] [68] [32] ... place "start sound" in slot 1
      Roomba.write("\x8d\x01"); // [141] [1] play it (in slot 1)
      break;
 
    case 2: 
      Roomba.write("\x8c\x02\x08\x4c\x0c\x4c\x0c\x14\x0c\x4c\x0c\x14\x0c\x48\x0c\x4c\x0c");
      Roomba.write("\x8d\x02"); // play it (in slot 2)
      break;

    case 3:
      Roomba.write("\x8c\x03\x01\x48\x20"); // place "high freq sound" in slot 3
      Roomba.write("\x8d\x03"); // play it (in slot 3)
      break;
  }
}

void wake() {
  digitalWrite(ddpin, HIGH);
  delay(100);
  digitalWrite(ddpin, LOW);
  delay(500);
  digitalWrite(ddpin, HIGH);
  delay(2000);
}

void helloWorld() {
  Roomba.write(0xA4);
  Roomba.write(0x44);
  Roomba.write(0x72);
  Roomba.write(0x20);
  Roomba.write(0x42);
}

void seekDock() {
  Roomba.write(0x8F);
}
