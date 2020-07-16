
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define led 6
struct SENT_REMOTE_DATA {
byte CH1_X;
byte CH1_Y;
byte CH2_X;
byte CH2_Y;
byte L1;
byte R1;
byte Analog_L;
byte Analog_R;
 }; 
SENT_REMOTE_DATA DATA;

RF24 radio(10, 9); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(DEFAULT);
  
  pinMode(12, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  DATA.CH1_X = map( analogRead(A2), 0, 1024, 0, 255);
  DATA.CH1_Y = map( analogRead(A3), 0, 1024, 0, 255);

  DATA.CH2_X = map( analogRead(A1), 0, 1024, 0, 255);
  DATA.CH2_Y = map( analogRead(A0), 0, 1024, 0, 255);

  DATA.L1 = digitalRead(4);
  DATA.R1 = digitalRead(3);
  
  DATA.Analog_L = map( analogRead(A4), 0, 1024, 0, 255);
  DATA.Analog_R = map( analogRead(A5), 0, 1024, 0, 255);
  
  radio.stopListening();
  
 
  radio.write(&DATA, sizeof(SENT_REMOTE_DATA));
  delay(10);
  /*radio.startListening();
  while (!radio.available());
  radio.read(&buttonState, sizeof(buttonState));
  if (buttonState == HIGH) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
   Serial.print("\tButton ");
   Serial.print(buttonState);
   Serial.print("\n");*/

  Serial.print(" CH1_X ");
  Serial.print(DATA.CH1_X);
  Serial.print("  CH1_Y ");
  Serial.print(DATA.CH1_Y);

  Serial.print("  CH2_X ");
  Serial.print( DATA.CH2_X );
  Serial.print("  CH2_Y ");
  Serial.print( DATA.CH2_Y );
  Serial.print("  L1 ");
  Serial.print(DATA.L1);
  Serial.print("  R1 ");
  Serial.print(DATA.R1);
  Serial.print("  Analog_L ");
  Serial.print(DATA.Analog_L );
  Serial.print("  Analog_R ");
  Serial.print(DATA.Analog_R);
  Serial.println();
}
