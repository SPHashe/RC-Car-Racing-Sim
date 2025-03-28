/*
  Module // Arduino UNO    
    GND    ->   GND
    Vcc    ->   3.3V
    CE     ->   D9
    CSN    ->   D10
    CLK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12  
  RC Car // Arduino UNO
    Steer Servo -> D5
    Motor       -> D3

  Whole Sim Code RC CAR
 */

#include <SPI.h>                    //Radio
#include <nRF24L01.h>               //Radio      
#include <RF24.h>                   //Radio  
#include <Servo.h>                  //Servo

                 //Send Data
struct Data
 {
  int Speed = 0;                  //Value transmitted
  int Direction = 90;
 };

                 //Global Variables
//Pins
const int Motor = 3;

//Radio
const uint64_t pipeIn = 0xE8E8F0F0E1LL; 
RF24 radio(9, 10);                  // CSN and CE  pins
Data Sent;

//Motor
Servo MotorSpin;
Servo STEER;

                  //Prototyoe
void RecordData();
void MotorWrite();

void setup()
{  
  Serial.begin(9600); 
 
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();

  MotorSpin.attach(3);
  STEER.attach(5);
  MotorSpin.writeMicroseconds(1497);
  delay(1000);
}

void loop()
{
  RecordData();
}

void RecordData()
{
  while (radio.available() )
  {
    radio.read(&Sent, sizeof(Data));
    Serial.println(Sent.Speed);
    MotorWrite();
  }
}

void MotorWrite()
{
  MotorSpin.writeMicroseconds(1450-Sent.Speed);
  STEER.write(Sent.Direction);
}
