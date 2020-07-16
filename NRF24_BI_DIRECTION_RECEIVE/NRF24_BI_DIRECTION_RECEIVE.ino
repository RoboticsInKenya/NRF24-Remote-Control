
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#include <VNH3SP30.h>

VNH3SP30 MotorA;

#define M1_PWM 9   // pwm pin motor
#define M1_INA 42    // control pin INA
#define M1_INB 40    // control pin INB


#define button 4
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo myServo;
boolean buttonState = 0;
struct RECEIVE_REMOTE_DATA {
byte CH1_X;
byte CH1_Y;
byte CH2_X;
byte CH2_Y;
byte L1;
byte R1;
byte Analog_L;
byte Analog_R;
 }; 
RECEIVE_REMOTE_DATA DATA;

void setup() {
  pinMode(button, INPUT_PULLUP);
  myServo.attach(5);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
  Serial.begin(115200);
  MotorA.begin(M1_PWM, M1_INA, M1_INB);
}
void loop() {
analogWrite(13,DATA.Analog_R);
      int power = map(DATA.CH2_X, 68,254, -255,255);
MotorA.setSpeed(power);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      int angleV = 0;
      radio.read(&DATA, sizeof(RECEIVE_REMOTE_DATA));
      Serial_print();


     delay(10);
     
//    radio.stopListening();
//    buttonState = digitalRead(button);
//    radio.write(&buttonState, sizeof(buttonState));
  }
//Serial.println(radio.available());
 }
}
void Serial_print()
{
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
  
