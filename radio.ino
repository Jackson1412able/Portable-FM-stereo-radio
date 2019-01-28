#include <Wire.h>	//I2C COMMUNICATION
#include <radio.h>
#include <TEA5767.h>
#include "Nextion.h"
#define FIX_BAND RADIO_BAND_FM

TEA5767 radio;  //CREATE AN INSTANCE OF CLASS FOR SI4703 CHIP

float frequency = 99.80;  //DEFAULT FREQUENCY, UNIT FOR FREQUENCY IS IN KHz IN radio.h, WILL BE MULTIPLIED BY 100 TO GET TO MHz 

//FUNCTION PROTOTYPES FOR NEXTION BUTTON EVENTS
void b0PopCallback(void *ptr);
void b1PopCallback(void *ptr);
void b2PopCallback(void *ptr);
void b3PopCallback(void *ptr);

//ASSIGN NEXTION BUTTON VARIABLES TO NEXTION BUTTONS
NexButton b0 = NexButton(1, 1, "b0");
NexButton b1 = NexButton(1, 2, "b1");
NexButton b2 = NexButton(1, 6, "b2");
NexButton b3 = NexButton(1, 7, "b3");

//ASSIGN NEXTION TEXT VARIABLES TO NEXTION TEXT
NexText t0 = NexText(1, 3, "t_freq");

//PIN 10(RX) AND 11(TX) TO BE USED TO COMMUNICATE WITH NEXTION LCD
SoftwareSerial HMISerial(10, 11);

//LIST OF NEXTION BUTTONS TO BE LISTENED
NexTouch *nex_listen_list[] =
{
  &b0,
  &b1,
  &b2,
  &b3,
  NULL
};

//BUTTON B0 TO INCREASE FREQUENCY BY 0.1MHz WHEN PRESSED, IF FREQUENCY EXCEEDS 108.0MHz, FREQUENCY SET AT 76.0MHz
void b0PopCallback(void *ptr)
{
  char buffer[8] = {0};
  dbSerialPrintln("b0PopCallback");
  dbSerialPrintln(frequency);
  if ( int(frequency*100) < 10801) {
    frequency += 0.1;
    dbSerialPrintln(frequency);
    memset(buffer, 0, sizeof(buffer));
    dtostrf(frequency, 3, 1, buffer);
    t0.setText(buffer);
    radio.setBandFrequency(FIX_BAND, int(frequency * 100));
     dbSerialPrintln("a");
  } else if ( int(frequency*100)  <= 10801) {
    frequency = 76.01;
    dbSerialPrintln(frequency);
    memset(buffer, 0, sizeof(buffer));
    dtostrf(frequency, 3, 1, buffer);
    t0.setText(buffer);
    radio.setBandFrequency(FIX_BAND, int(frequency * 100));
     dbSerialPrintln("b");
  }
}

//BUTTON B1 TO DECREASE FREQUENCY BY 0.1MHz WHEN PRESSED, IF FREQUENCY SMALLER THAN 76.0MHz, FREQUENCY SET AT 108.0MHz
void b1PopCallback(void *ptr)
{
  char buffer[8] = {0};
  dbSerialPrintln("b1PopCallback");
  dbSerialPrintln(frequency);
  if ( int(frequency*100) > 7601) {
    frequency -= 0.1;
    memset(buffer, 0, sizeof(buffer));
    dtostrf(frequency, 3, 1, buffer);
    t0.setText(buffer);
    radio.setBandFrequency(FIX_BAND, int(frequency * 100));
    dbSerialPrintln("a");
  } else if ( int(frequency*100) >= 7601) {
    frequency = 108.01;
    memset(buffer, 0, sizeof(buffer));
    dtostrf(frequency, 3, 1, buffer);
    t0.setText(buffer);
    radio.setBandFrequency(FIX_BAND, int(frequency * 100));
    dbSerialPrintln("b");
  }
}

//BUTTON B2 TO DECREASE FREQUENCY BY 1.0MHz WHEN PRESSED, IF FREQUENCY SMALLER THAN 76.0MHz, FREQUENCY SET AT 108.0MHz
void b2PopCallback(void *ptr)
{
  char buffer[8] = {0};
  dbSerialPrintln("b2PopCallback");
  dbSerialPrintln(frequency);
  if ( int(frequency*100) > 7691) {
    frequency -= 1.0;
    memset(buffer, 0, sizeof(buffer));
    dtostrf(frequency, 3, 1, buffer);
    t0.setText(buffer);
    radio.setBandFrequency(FIX_BAND, int(frequency * 100));
    dbSerialPrintln("a");
  }else if ( int(frequency*100) <= 7691) {
    frequency = 108.01;
    memset(buffer, 0, sizeof(buffer));
    dtostrf(frequency, 3, 1, buffer);
    t0.setText(buffer);
    radio.setBandFrequency(FIX_BAND, int(frequency * 100));
    dbSerialPrintln("b");
  }
}

//BUTTON B3 TO INCREASE FREQUENCY BY 1.0MHz WHEN PRESSED, IF FREQUENCY EXCEEDS 108.0MHz, FREQUENCY SET AT 76.0MHz
void b3PopCallback(void *ptr)
{
  char buffer[8] = {0};
  dbSerialPrintln("b3PopCallback");
  dbSerialPrintln(frequency);
  if ( int(frequency*100) < 10711) {
    frequency += 1.0;
    dbSerialPrintln(frequency);
    memset(buffer, 0, sizeof(buffer));
    dtostrf(frequency, 3, 1, buffer);
    t0.setText(buffer);
    radio.setBandFrequency(FIX_BAND, int(frequency * 100));
    dbSerialPrintln("a");
  }else if ( int(frequency*100) >= 10711) {
    frequency = 76.01;
    dbSerialPrintln(frequency);
    memset(buffer, 0, sizeof(buffer));
    dtostrf(frequency, 3, 1, buffer);
    t0.setText(buffer);
    radio.setBandFrequency(FIX_BAND, int(frequency * 100));
    dbSerialPrintln("b");
  }
}

void setup() {
  //START SERIAL PORT
  Serial.begin(57600);
  Serial.println("Radio...");
  delay(200);

  radio.init();	//INITIALIZE RADIO
  radio.debugEnable();	//ENABLE INFORMATION TO SERIAL PORT
  radio.setBandFrequency(FIX_BAND, int(frequency * 100));	//TUNE RADIO TO 99.80MHz
  radio.setVolume(15);	//SET VOLUME
  radio.setMono(false);	//OPERATE RADIO IN STEREO MODE
  nexInit();	//INITIALIZE NEXTION LCD DISPLAY

	//ASSIGN EVENT TO NEXTION BUTTONS
  b0.attachPop(b0PopCallback);
  b1.attachPop(b1PopCallback);
  b2.attachPop(b2PopCallback);
  b3.attachPop(b3PopCallback);
}

void loop() {
  nexLoop(nex_listen_list);	//DETECT FOR ANY NEXTION TOUCHSCREEN BUTTON PRESSES
} 


