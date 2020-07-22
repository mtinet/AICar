/* 
- 조향 :  
아두이노 UNO - 모터 드라이버(DM322E)  
         p5 - PUL(펄스)  
         p4 - DIR(디렉션)  
            - OPTO  
         5V - ENA  
모터 드라이버 - 스텝모터(2번, 5번 미사용)  
         A+ - 모터 결선 좌측 1번째  
         A- - 모터 결선 좌측 3번째  
         B+ - 모터 결선 좌측 4번째  
         B- - 모터 결선 좌측 6번째  
모터 드라이버의 점퍼를 조정해 전류를 제어할 수 있음  
모터는 K6G50C 1:50 기어박스가 포함되어 있음  
현재 세팅은 점퍼 스위치 세팅 : 111111 (피크 전류 1A, RMS 0.71A, 400pulse/rev)  
- 통신 :  
아두이노 UNO - 블루투스 모듈(HC-06)  
         p2 - TXD  
         p3 - RXD  
- 구동 :  
아두이노 UNO - 모터 드라이버  
PWM출력(p11) - PWM입력(페달)  
전진후진(P12) - dir입력(모터 회전 방향)  
*/


#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

// 스텝 모터 제어
const int dirPinLR = 6;  // 좌우 회전
const int stepPin = 5; // 스텝 펄스
const int enA = 4;  // 구동 여부 결정

const int STEPS_PER_REV = 200; // 모터 1회전 

int rotateLimit = 4;

// 드라이브 모터 제어
const int PWM = 10; // 파워
const int in1 = 11; // 신호 1 
const int in2 = 12; // 신호 2
const int vcc = 13; // 5V 확인용

const int valocity = 100;

void setup() {
  //통신 설정
  Serial.begin(9600); // 시리얼 통신
  mySerial.begin(9600); // 블루투스 통신             

  // 스텝모터 핀 모드 설정
  pinMode(dirPinLR,OUTPUT);
  pinMode(stepPin,OUTPUT); 
  pinMode(enA, OUTPUT);
  digitalWrite(enA, HIGH);


  // 드라이브모터 핀 모드 설정
  pinMode(PWM,OUTPUT);
  pinMode(in1,OUTPUT); 
  pinMode(in2, OUTPUT);
  pinMode(vcc, OUTPUT);
  digitalWrite(vcc, HIGH);
}

void loop() {
  if( mySerial.available() ){        // 블루투스 통신에 데이터가 있을 경우
    char cmd = mySerial.read();     // 블루투스의 데이터(문자 한 글자)를 'cmd' 변수에 저장
    if ( cmd == 'w' ){               // 만약 'cmd' 변수의 데이터가 q이면
      forward();
    } else if ( cmd == 'x') {        // 아니고 만약 'cmd' 변수의 데이터가 w면
      backward();
    } else if ( cmd == 'a' ) {       // 아니고 만약 'cmd' 변수의 데이터가 e면
      right();
    } else if ( cmd == 'd' ) {       // 아니고 만약 'cmd' 변수의 데이터가 e면
      left();
    } else if ( cmd == 's' ) {       // 아니고 만약 'cmd' 변수의 데이터가 s면
      motorStop();
    }
  }
}



void left() {
  // 조향 모터가 '반시계방향'으로 회전하도록 신호부여
  digitalWrite(dirPinLR,HIGH); 
  
  if (rotateLimit > 0) {
    // 500마이크로초 주기로 모터 축이 5회전하는 코드
    // 1:50 기어박스 내장되어 있으므로, 모터 1회전에 바퀴 7.2도 회전함
    // 따라서, 모터가 5회전하면 바퀴가 36도 회전함
    for(int x = 0; x < STEPS_PER_REV*1.5; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(1000); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(1000); 
    }
    rotateLimit = rotateLimit - 1;
  } else {
    rotateLimit = 0;
  }
  Serial.println(rotateLimit);
}

void right() {
  // 조향 모터가 '시계방향'으로 회전하도록 신호부여
  digitalWrite(dirPinLR,LOW); 
  
  if (rotateLimit < 7) {
    for(int x = 0; x < STEPS_PER_REV*1.5; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(1000); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(1000); 
    }
    rotateLimit = rotateLimit + 1;
  } else {
    rotateLimit = 7;
  }
  Serial.println(rotateLimit);
}

void forward() {
  //드라이브 모터가 앞으로 회전하도록 신호부여
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW); 
  for (int i = 0; i < valocity; i = i + 10) {
    analogWrite(PWM, i);
    delay(100);
  }
  Serial.println("forward");
}

void motorStop() {
  digitalWrite(in1,LOW); 
  digitalWrite(in2,LOW);
  
  analogWrite(PWM, 0);
  delay(100);
  Serial.println("motorStop");
}

void backward() {
  ////드라이브 모터가 뒤로 회전하도록 신호부여
  digitalWrite(in1,LOW); 
  digitalWrite(in2,HIGH); 
  for (int i = 0; i < valocity; i = i + 10) {
    analogWrite(PWM, i);
    delay(100);
  }
  Serial.println("backward");
}
