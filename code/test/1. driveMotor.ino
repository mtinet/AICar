#include <SoftwareSerial.h>

// 드라이브 모터 제어
const int FB = 10; // 전진, 후진
const int PWM = 11; // 모터 회전 속도

const int valocity = 100;

void setup() {
  // 드라이브모터 핀 모드 설정
  pinMode(FB,OUTPUT);
  pinMode(PWM,OUTPUT); 
}

void loop() {
  motorStop();
  forward();
  backward();
}

void forward() {
  //드라이브 모터가 앞으로 회전하도록 신호부여
  digitalWrite(FB,HIGH); 
  analogWrite(PWM, valocity);
  delay(1000);
  Serial.println("forward");
}

void motorStop() {
  digitalWrite(FB,HIGH); 
  analogWrite(PWM, 0);
  delay(1000);
  Serial.println("motorStop");
}

void backward() {
  ////드라이브 모터가 뒤로 회전하도록 신호부여
  digitalWrite(FB,LOW); 
  analogWrite(PWM, valocity);
  delay(1000);
  Serial.println("backward");
}
