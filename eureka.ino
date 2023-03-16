#include <ArduinoBLE.h>

BLEService leftHand("ff997f00-bf82-11ed-afa1-0242ac120002");
BLEByteCharacteristic firstNoteChar("ff997f01-bf82-11ed-afa1-0242ac120002", BLERead | BLENotify | BLEBroadcast);
BLEByteCharacteristic secondNoteChar("ff997f02-bf82-11ed-afa1-0242ac120002", BLERead | BLENotify | BLEBroadcast);
BLEByteCharacteristic thirdNoteChar("ff997f03-bf82-11ed-afa1-0242ac120002", BLERead | BLENotify | BLEBroadcast);
BLEByteCharacteristic fourthNoteChar("ff997f04-bf82-11ed-afa1-0242ac120002", BLERead | BLENotify | BLEBroadcast);
BLEByteCharacteristic changeNoteChar("ff997f05-bf82-11ed-afa1-0242ac120002", BLERead | BLENotify | BLEBroadcast);

const char firstNotePin = D2;
const char secondNotePin = D3;
const char thirdNotePin = D4;
const char fourthNotePin = D5;
const char changeNotePin = D6;
const int pressed = 0;

volatile int firstNoteState = 0;
volatile int secondNoteState = 0;
volatile int thirdNoteState = 0;
volatile int fourthNoteState = 0;
volatile int changeNoteState = 0;

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(firstNotePin, INPUT_PULLUP);
  pinMode(secondNotePin, INPUT_PULLUP);
  pinMode(thirdNotePin, INPUT_PULLUP);
  pinMode(fourthNotePin, INPUT_PULLUP);
  pinMode(changeNotePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(firstNotePin), firstNoteChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(secondNotePin), secondNoteChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(thirdNotePin), thirdNoteChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(fourthNotePin), fourthNoteChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(changeNotePin), changeNoteChange, CHANGE);

  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Nano33BLE");

  BLE.setAdvertisedService(leftHand); // Advertise service
  leftHand.addCharacteristic(firstNoteChar); // Add characteristic to service
  leftHand.addCharacteristic(secondNoteChar); // Add characteristic to service
  leftHand.addCharacteristic(thirdNoteChar); // Add characteristic to service
  leftHand.addCharacteristic(fourthNoteChar); // Add characteristic to service
  leftHand.addCharacteristic(changeNoteChar); // Add characteristic to service

  BLE.addService(leftHand); // Add service
  
  firstNoteChar.setValue('0');
  secondNoteChar.setValue('0');
  thirdNoteChar.setValue('0');
  fourthNoteChar.setValue('0');
  changeNoteChar.setValue('0');

  BLE.advertise();  // Start advertising
  Serial.print("Peripheral device MAC: ");
  Serial.println(BLE.address());
  Serial.println("Waiting for connections...");
}

void loop() {
  BLEDevice central = BLE.central();
  if (central.connected()) {
    BLE.stopAdvertise();
    digitalWrite(LED_BUILTIN, HIGH);

    if (firstNoteState == 1 && firstNoteChar.value() == '0') {
      firstNoteChar.setValue('1');
    } else if (firstNoteState == 0 && firstNoteChar.value() == '1') {
      firstNoteChar.setValue('0');
    }

    if (secondNoteState == 1 && secondNoteChar.value() == '0') {
      secondNoteChar.setValue('1');
    } else if (secondNoteState == 0 && secondNoteChar.value() == '1') {
      secondNoteChar.setValue('0');
    }

    if (thirdNoteState == 1 && thirdNoteChar.value() == '0') {
      thirdNoteChar.setValue('1');
    } else if (thirdNoteState == 0 && thirdNoteChar.value() == '1') {
      thirdNoteChar.setValue('0');
    }

    if (fourthNoteState == 1 && fourthNoteChar.value() == '0') {
      fourthNoteChar.setValue('1');
    } else if (fourthNoteState == 0 && fourthNoteChar.value() == '1') {
      fourthNoteChar.setValue('0');
    }

    if (changeNoteState == 1 && changeNoteChar.value() == '0') {
      changeNoteChar.setValue('1');
    } else if (changeNoteState == 0 && changeNoteChar.value() == '1') {
      changeNoteChar.setValue('0');
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    BLE.advertise();
  }
}

void firstNoteChange() {
  int state = digitalRead(firstNotePin);
  if (state == pressed) {
    firstNoteState = 1;
  } else if (state == !pressed) {
    firstNoteState = 0;
  }
}

void secondNoteChange() {
  int state = digitalRead(secondNotePin);
  if (state == pressed) {
    secondNoteState = 1;
  } else if (state == !pressed) {
    secondNoteState = 0;
  }
}

void thirdNoteChange() {
  int state = digitalRead(thirdNotePin);
  if (state == pressed) {
    thirdNoteState = 1;
  } else if (state == !pressed) {
    thirdNoteState = 0;
  }
}

void fourthNoteChange() {
  int state = digitalRead(fourthNotePin);
  if (state == pressed) {
    fourthNoteState = 1;
  } else if (state == !pressed) {
    fourthNoteState = 0;
  }
}

void changeNoteChange() {
  int state = digitalRead(changeNotePin);
  if (state == pressed) {
    changeNoteState = 1;
  } else if (state == !pressed) {
    changeNoteState = 0;
  }
}