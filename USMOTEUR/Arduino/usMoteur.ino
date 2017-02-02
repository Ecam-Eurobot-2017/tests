#include <Wire.h>

//address arduino slave
#define SLAVE_ADDR 0x04

//pins ~pwm et dir arduino to driver moteur
const byte pwm_motor1 = 6;
const byte dir_motor1 = 7;

//pins sensors
const byte trig_pin = 12;
const byte echo_pin = 11;
int return_echo;
int distance;
int dataReceived;

void setup() {
  //i2c comm
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  //set level pins
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW);

  pinMode(pwm_motor1, OUTPUT);
  pinMode(dir_motor1, OUTPUT);

  Serial.begin(9600);

  //set clock pwm arduino (31kHz). /!\ see if neccesary
  TCCR1B = TCCR1B & B11111000 | B00000001;
  TCCR2B = TCCR2B & B11111000 | B00000001;

}

void loop() {
  delay(500);
}

void receiveData(int byteCount){
  //receive data and get measure
  while(Wire.available()){
    dataReceived = Wire.read();
    if(dataReceived == 1){
      distance = getUSMeasure();
    }
    //rotate motor in a sens
    else if(dataReceived == 2){
      Serial.print("i move back");
      digitalWrite(dir_motor1, 1);
      analogWrite(pwm_motor1, 255);
    }
    //rotate motor in the other sens
    else if(dataReceived == 3){
      Serial.print("i advance");
      digitalWrite(dir_motor1, 1);
      analogWrite(pwm_motor1, 1);
    }
  }
}

void sendData(){
  //send response
  Wire.write(distance);
}

int getUSMeasure(){
  //launch a us sensor measure
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  //reception of echo
  return_echo = pulseIn(echo_pin, HIGH);
  distance = return_echo/58;
  return distance;
}
