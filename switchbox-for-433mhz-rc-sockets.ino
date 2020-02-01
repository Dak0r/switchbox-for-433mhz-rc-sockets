/*
 * Arduino Sketch for a simple universal remote box for 433mhz sockets with 5 dip switches. 
 * House Code is hardcoded, up to 32 sockets can be controlled by entering the socket code 
 * using switches connected to pinA - pinE and pressing a button connected to pinOn or pinOff.
 * Requires RC-Switch Library (also in Arduino Lib Manager): https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>

#define pinA 2
#define pinB 3
#define pinC 4
#define pinD 5
#define pinE 6

#define pinOn 7
#define pinOff 8

#define senderPin 10
#define powerLedPin 9
#define sendLedPin 11

RCSwitch mySwitch = RCSwitch();
char socketCode[5];

void setup() {
  Serial.begin(9600);

  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  pinMode(pinC, INPUT_PULLUP);
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinD, INPUT_PULLUP);
  pinMode(pinE, INPUT_PULLUP);
  pinMode(pinOn, INPUT_PULLUP);
  pinMode(pinOff, INPUT_PULLUP);

  pinMode(powerLedPin, OUTPUT);
  pinMode(sendLedPin, OUTPUT);
  
  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(senderPin);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);

}

void loop() {


  bool bOn = digitalRead(pinA) == LOW;
  bool bOff = digitalRead(pinA) == LOW;

  if(bOn || bOff){
    digitalWrite(sendLedPin, HIGH);
    readSocketCode();
  }

  if(bOn){
    Serial.println("Will switch on");
    mySwitch.switchOn("11010", socketCode);
  }else if(bOff){
    Serial.println("Will switch off");
    mySwitch.switchOff("11010", socketCode);
  }
  if(bOn || bOff){
    delay(1000);
    digitalWrite(sendLedPin, LOW);
  }

  
  delay(50);
}

void readSocketCode(){

  bool sA = digitalRead(pinA) == LOW;
  bool sB = digitalRead(pinA) == LOW;
  bool sC = digitalRead(pinA) == LOW;
  bool sD = digitalRead(pinA) == LOW;
  bool sE = digitalRead(pinA) == LOW;
  
  sprintf(socketCode, "%c%c%c%c%c", boolToOneOrZero(sA), boolToOneOrZero(sB), boolToOneOrZero(sC), boolToOneOrZero(sD), boolToOneOrZero(sE));
}

char boolToOneOrZero(bool value){
  if(value){
    return '1';
  }else{
    return '0';
  }
}
