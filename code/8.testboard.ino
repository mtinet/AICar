/* 
*  - 통신 :  
아두이노 MEGA - 블루투스 모듈(HC-06 or HM-10)  
         RX31 - TXD  
         TX31 - RXD  
         
- 조향 :  
아두이노 UNO - 모터 드라이버(점퍼는 사진 확인 후 적용)  
         p6 - enA 
         p7 - PUL(펄스)  
         p5 - DIR(디렉션)  
모터 드라이버 - 스텝모터(2번, 5번 미사용)  
         A+ - 모터 결선 좌측 1번째  
         A- - 모터 결선 좌측 3번째  
         B+ - 모터 결선 좌측 4번째  
         B- - 모터 결선 좌측 6번째  
모터 드라이버의 점퍼를 조정해 전류를 제어할 수 있음  
모터는 K6G50C 1:50 기어박스가 포함되어 있음  
현재 세팅은 점퍼 스위치 세팅 : 110010 (피크 전류 3.2A, RMS 3.0A, 200pulse/rev)  
- 페달모드 :
아두이노 - 페달
     A0 - 노랑
     p2  - 스위치-전진
     p3  - 스위치-후진
     p4  - ground
- 구동 :  
아두이노 MEGA - 모터 드라이버  
전진후진(P10) - dir입력(모터 회전 방향)  
PWM출력(p11) - PWM입력(파워)  

*/


#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

// 스텝 모터 제어
const int enA = 6;  // 구동 여부 결정
const int stepPin = 7; // 스텝 펄스
const int dirPinLR = 5;  // 좌우 회전

const int STEPS_PER_REV = 1600; // 모터 1회전, TB6600 스텝 모터 드라이버도 1600펄스에 3.5암페어로 정함(off, on, off, off, off, off)  

int rotateLimit = 4;

// 드라이브 모터 제어
const int DIR = 10; // 파워
const int PWM = 11; // 신호 1 


const int valocity = 100;

// 페달 제어_전진, 후진 스위치 센싱
int pedalF = 2;
boolean pedalFVal = 0;

int pedalB = 3;
boolean pedalBVal = 0;

const int ground = 4;

// 페달 제어_페달 센싱
const int pedalSensor = A0;
int pedalVal = 0;

// 수동 모드, 앱 제어모드 변경, 0은 앱제어모드, 1은 수동 모드
boolean modeState = 1;

// 속도값 초기화
int i = 0;

// 입력 문자, 입력 문자 백업
char cmd = "";
char cmdM = "";

void setup() {
  //통신 설정
  Serial.begin(9600); // 시리얼 통신
  mySerial.begin(9600); // 블루투스 통신             

  // 스텝모터 핀 모드 설정
  pinMode(dirPinLR,OUTPUT);
  pinMode(stepPin,OUTPUT); 
  pinMode(enA, OUTPUT);
  digitalWrite(enA, LOW);

  // 드라이브모터 핀 모드 설정
  pinMode(PWM,OUTPUT); 
  pinMode(DIR, OUTPUT);
         
  // 페달모드 전진 후진 신호
  pinMode(pedalF, INPUT_PULLUP);
  pinMode(pedalB, INPUT_PULLUP);
  pinMode(ground, OUTPUT);
  digitalWrite(ground, LOW);

  Serial.println("AI Go-Kart is Ready!");
}

void loop() {
  //  modestate가 1이면 페달제어 모드로 수행
  if(modeState == 1) {       
    // 전진, 후진 스위치 값 저장
    pedalFVal = digitalRead(pedalF);
    pedalBVal = digitalRead(pedalB);

    // 페달값 센싱-매핑-한계범위설정
    pedalVal = analogRead(pedalSensor);
    pedalVal = map(pedalVal, 230, 850, 0, 255);
    pedalVal = constrain(pedalVal, 0, 255);

    // 페달 값 변화 시리얼 모니터링
    Serial.print(pedalFVal);
    Serial.print("  ");
    Serial.print(pedalBVal);
    Serial.print("  ");
    Serial.print(pedalVal);
    Serial.print("  ");

    // 페달 신호가 0이면 브레이킹
    if (pedalVal == 0) {
      digitalWrite(DIR,LOW);   
      analogWrite(PWM, 0);
      delay(100);
    }

    // 전진, 후진 스위치 값에 따른 페달 동작
    if (pedalFVal == 1 && pedalBVal == 0) {
      digitalWrite(DIR,HIGH); 
      analogWrite(PWM, pedalVal);
      Serial.println("RRRR");
    } else if (pedalFVal == 0 && pedalBVal == 1) {
      digitalWrite(DIR,LOW);
      analogWrite(PWM, pedalVal);
      Serial.println("FFFF");
    } else {
      digitalWrite(DIR,LOW);  
      analogWrite(PWM, 0);
      Serial.println("SSSS");
    }
  }
         
  if (Serial.available() ){        // 블루투스 통신에 데이터가 있을 경우
    cmd = Serial.read();     // 블루투스의 데이터(문자 한 글자)를 'cmd' 변수에 저장
  
    // cmd 변수의 데이터가 m이면 수동모드로, i면 앱모드로 modeState 변수의 상태를 바꿈
    if (cmd == 'm') {
      modeState = 1;
      Serial.println("input 'm'");
      Serial.println("the mode is : manual control");
    }
    
    if (cmd == 'i') {
      modeState = 0;
      Serial.println("input 'i'");
      Serial.println("the mode is : app control");
    }    
    
    // modestate가 0이면 앱제어 모드로 수행
    if (modeState == 0) {
      if (cmd == 'w' ){               // 만약 'cmd' 변수의 데이터가 q이면
        Serial.println(cmdM);
        if(cmdM == 'w'){
          forward();
        } else {
          i = 0;
          forward();
        }
        cmdM = 'w';
      } else if ( cmd == 'x') {        // 아니고 만약 'cmd' 변수의 데이터가 w면
        if(cmdM == 'x') {
          backward();
        } else {
          i = 0;
          backward();
        }
        cmdM = 'x';
      } else if ( cmd == 'a' ) {       // 아니고 만약 'cmd' 변수의 데이터가 e면
        right();
      } else if ( cmd == 'd' ) {       // 아니고 만약 'cmd' 변수의 데이터가 e면
        left();
      } else if ( cmd == 's' ) {       // 아니고 만약 'cmd' 변수의 데이터가 s면
        motorStop();
      }
    }
  }
}



void left() {
  // 조향 모터가 '반시계방향'으로 회전하도록 신호부여
  digitalWrite(dirPinLR,HIGH); 
  
  if (rotateLimit > 0) {
    // 1000마이크로초 주기로 모터 축이 1.5회전하는 코드
    // 1:50 기어박스 내장되어 있으므로, 모터 1회전에 바퀴 7.2도 회전함
    // 따라서, 모터가 1.5회전하면 바퀴가 10.8도 회전함
    for(int x = 0; x < STEPS_PER_REV*1.5; x++) {
      digitalWrite(enA,LOW);
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(500); 
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
      digitalWrite(enA,LOW);
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(500); 
    }
    rotateLimit = rotateLimit + 1;
  } else {
    rotateLimit = 7;
  }
  Serial.println(rotateLimit);
}

void forward() {
  //드라이브 모터가 앞으로 회전하도록 신호부여
  digitalWrite(DIR,HIGH); 
  analogWrite(PWM, i);

  if(i != valocity) {
    for (i = 0; i < valocity; i = i + 10) {
      analogWrite(PWM, i);
      delay(100);
    }
  }
  Serial.println("forward");
}

void motorStop() {
  digitalWrite(DIR,LOW);
  
  analogWrite(PWM, 0);
  delay(100);
  Serial.println("motorStop");
}

void backward() {
  ////드라이브 모터가 뒤로 회전하도록 신호부여
  digitalWrite(DIR,LOW); 
  analogWrite(PWM, i);
  
  if(i != valocity) {
    for (i = 0; i < valocity; i = i + 10) {
      analogWrite(PWM, i);
      delay(100);
    }
  }
  Serial.println("backward");
}
