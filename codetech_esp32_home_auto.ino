#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define RELAY 23

BLECharacteristic *pCharacteristic;

#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "abcd1234-5678-1234-5678-123456789abc"

class MyCallbacks: public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string rxValue = pCharacteristic->getValue();

    if (rxValue.length() > 0)
    {
      Serial.print("Received: ");
      Serial.println(rxValue.c_str());

      if (rxValue == "1")
      {
        digitalWrite(RELAY, LOW);   // ON
      }
      else if (rxValue == "0")
      {
        digitalWrite(RELAY, HIGH);  // OFF
      }
    }
  }
};

void setup()
{
  Serial.begin(115200);

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH); // OFF initially

  BLEDevice::init("ESP32_Home_Automation");

  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();

  Serial.println("BLE Ready...");
}

void loop()
{
}