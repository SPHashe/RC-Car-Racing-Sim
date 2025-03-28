# RC-Car-Racing-Sim
There are two main components, the steering wheel, and RC car code. the steering wheel is the transmitter, and RC car is the receiver code. 

# Racing Sim wiring
Pins to the Elegoo Mega: 

Wheel 	
* VCC - > 5V 
* Serial -> A8 
* Ground -> Ground 

Forward Pedal 	
* VCC -> Reverse 5V Out 
* Serial -> A1 
* Ground -> Reverse Ground 

Reverse Pedal 	
* VCC -> 5V 
* Serial -> A2 
* Ground -> Ground 

Shift Knob 	
* VCC -> 3.3V 
* Serial 1 -> Leave Disconnected 
* Serial 2 -> D13 

Radio Chip 	
* VCC -> 3.3V 
* Ground -> Ground 
* CE -> D10 
* CSN -> D11 
* SCK -> D52 
* MOSI -> D51 
* MISO -> D50 

# Brief Code Explanation 
The code uploaded onto the RC car is left short and simple to use less battery usage due to having less processing to perform. It receives the data from the RecordData(); function then remaps it for the various motors through the MotorWrite(); function. 
The code uploaded to the Racing Sim has a lot of processing due to the differences in readings from the Racing Sim. The PedalRead();, ShiftRead();, and WheelRead(); functions read each sensor currently being used. The information is then sent to the RC car through the SendData(); function.  
The radio chips use a structure to send multiple numbers at the same time. They are currently set to communicate at 250kBPS through the address 0xE8E8F0F0E1LL. It is important to ensure that the two radio chips use the same address and frequency so they can properly connect. 
Additionally, when the receiver does not find a connection for 7000 tries, it will slowly reverse on the same direction as the last input until it is back in range. 
 
# Problems 
Shifter 
 	In its most basic form, the shift knob is just two push buttons. The physical knob itself uses springs and levers to press one of the buttons whether its pushed upwards or downwards. When giving power to one wire and reading the others on a separate Arduino it worked fine reading 0s and 1s depending on which button is pressed. When adding it to the Arduino controlling the whole wheel the down shift caused inaccuracies in the pedal and steering readings. Eventually it was found that downshifting caused some sort of short circuit or large draw in current grounding everything which then caused the Arduino to fully reset itself sometimes. 
Lights 
 	Initially the lights worked perfectly fine. However, one day they just stopped working. 
Even connecting to them to a separate Arduino board just turning on the lights was not possible. The LEDs could’ve burnt out or when the shifter was resetting the board something could’ve happened causing the LEDs to stop working. 
Steering Potentiometer 
 	Over time the original potentiometer in the steering wheel started to become more and more inaccurate. The wiring connections were starting to become weak from the number of times the wheel was open and closed to fix other components within the wheel. After numerous attempts of soldering stronger connections to the potentiometer is eventually just stopped working in certain positions. The potentiometer used was a generic potentiometer so replacing it was not an issue. This just means that the electronics in the wheel is very delicate and requires us to be more careful with what we are doing. 
 	 
 
# Future Plans 
Remote Driving 
 	Now having access to more features of the Arduino IoT, it is possible to create an online platform for people to drive the car remotely. This of course includes web development and more research done on the Arduino IoT API. Additionally, research must be put into finding the best way to host this server with the least amount of delay. 
Data Analysis 
 	The next step with making this car more efficient can be adding sensors that measure speed and power consumption. This can allow us to work around problems with the components overheating and battery life concerns especially when adding more smart components to the car. This can provide thoughtful insights to consider in the future and can even benefit the design of the RC car as well. 
Autonomous Driving/ Driving Assist 
 	Adding additional sensors around the car to add driving assist features. This can be anything like detecting obstacles, blind spot indicators, parking assist, and positioning cameras around the car to generate a birds-eye view image of the car. After this the project can shift towards autonomous driving using artificial intelligence and video recognition. The car can detect lanes on a pathway, stop/yield signs, and intersection lights. 

