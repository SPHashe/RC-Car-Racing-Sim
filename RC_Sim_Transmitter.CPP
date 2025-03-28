/*
  Module // Arduino UNO    
    GND    ->   GND
    Vcc    ->   3.3V
    CE     ->   D9
    CSN    ->   D10
    CLK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12  

  Whole Sim Code RACING SIM
 */

#include <SPI.h>                  //Radio
#include <nRF24L01.h>             //Radio
#include <RF24.h>                 //Radio
 
                  //Send Data
 struct Data
 {
  int Speed = 0;                  //Value transmitted
  int Direction = 90;
 };

                  //Global Variables
//Pins
const int FWRD = A0;             //Forward Pin 
const int RVRS = A1;             //Backwards Pin
const int WHEEL = A2;            //Steering Wheel Pin

//Radio
const uint64_t pipeOut = 0xE8E8F0F0E1LL;
RF24 radio(9, 10);               //CSN and CE
Data Send;                       //Innitialize

//Pedals
int MapFWRD = 0;
int MapRVRS = 0;

                  //Prototyoe
void SendData(int PVal);          //Radio Send
void PedalRead();                 //Read Pedals
void WheelRead();                 //Read Steering Wheel

void setup() 
{
  Serial.begin(9600);

  //Pin Innitialize
  pinMode (FWRD, INPUT);
  pinMode (RVRS, INPUT);
  pinMode (WHEEL, INPUT);

  //Radio Inntialize
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
}

void loop() 
{
  //Value read
  PedalRead();
  WheelRead();

  while (MapFWRD > 0)
  {
    PedalRead();
    SendData(MapFWRD);
  }

  MapFWRD = 0;

  while(MapRVRS < 0)
  {
  PedalRead();
  SendData(MapRVRS);
  }

  SendData(0);
}

void SendData(int PVal)
{
  WheelRead();
  Send.Speed = PVal;
  radio.write(&Send, sizeof(Data));
  Serial.println(String(Send.Speed) + "\t\t" + String(Send.Direction));
}

void PedalRead()
{
 MapFWRD = analogRead(FWRD) * 0.61;
 MapRVRS = -analogRead(RVRS) * 0.39;

 if (MapFWRD > 255)
  {
    MapFWRD = 255;
  }
}

void WheelRead()
{
  Send.Direction = map(analogRead(WHEEL), 0, 1023, 45, 135);
}
