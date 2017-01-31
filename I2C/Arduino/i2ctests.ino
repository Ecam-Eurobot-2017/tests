#include <Wire.h>
#include <Servo.h>

//address of i2c conenction
#define SLAVE_ADDRESS 0x12
int dataReceived = 0;
//init servo-motor
Servo monservo;

void setup() {
    Serial.begin(9600);
    //begin i2c connection
    Wire.begin(SLAVE_ADDRESS);
    //set function to receive data
    Wire.onReceive(receiveData);
    //set function to send data
    Wire.onRequest(sendData);
}

void loop() {
    delay(100);
}

void receiveData(int byteCount){
    while(Wire.available()) {
        //reception of data send by i2c communication with raspberry
        dataReceived = Wire.read();
        Serial.print("Donnee recue : ");
        //use data to rotate servo-motor
        monservo.write(dataReceived);
        Serial.println(dataReceived);
    }
}

void sendData(){
    //send data to raspberry by i2c communication 
    int envoi = dataReceived + 1;
    Wire.write(envoi);
}
