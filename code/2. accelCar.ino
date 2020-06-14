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
프로그램 업로드 할 때는 반드시 블루투스 모듈을 빼놓고 해야 오류가 발생하지 않음 
softwareSerial 라이브러리에는 parseInt 함수가 없기 때문에 하드웨어 시리얼 통신인 0번, 1번 핀을 사용해야 하기 때문
아두이노 UNO - 블루투스 모듈(HC-06)  
    0번(RX) - TXD  
    1번(TX) - RXD  

- 구동 :  
아두이노 UNO - 모터 드라이버  
PWM출력(p11) - PWM입력(페달)  
전진후진(P12) - dir입력(모터 회전 방향)  
*/

// 스텝 모터 제어
const int dirPinLR = 6;  // 좌우 회전
const int stepPin = 5; // 스텝 펄스
const int enA = 4;  // 구동 여부 결정

const int STEPS_PER_REV = 400; // 모터 1회전 

// 드라이브 모터 제어
const int FB = 10; // 전진, 후진
const int PWM = 11; // 모터 회전 속도

// 상태 확인
int valocity = 0; // 속도 초기화
bool FBstate = 1; // 전진, 후진

// 조향 한계점 초기화
int leftLimit = 0;
int center = 2000;
int rightLimit = 0;

// 블루투스를 통해 들어온 값을 parseInt 함수를 사용해 x, y 값에 넣고, 이 값을 이용해 자동차를 제어함
int x = 0;
int y = 0;

void setup() {
  // 통신 설정
  Serial.begin(9600); // 시리얼 통신, 블루투스 모듈을 하드웨어 시리얼 통신 핀에 연결해서 사용함
  
  // 스텝모터 핀 모드 설정
  pinMode(dirPinLR,OUTPUT);
  pinMode(stepPin,OUTPUT); 
  pinMode(enA, OUTPUT);
  digitalWrite(enA, HIGH);

  // 드라이브모터 핀 모드 설정
  pinMode(FB,OUTPUT);
  pinMode(PWM,OUTPUT); 

  //조향 한계 설정
  leftLimit = center - STEPS_PER_REV*5;
  rightLimit = center + STEPS_PER_REV*5;
  
  // 오프닝
  Serial.println("Now Start Receive Data by parseInt..."); 
}

void loop() {
  
}

void serialEvent(){
  int x = Serial.parseInt();
  int y = Serial.parseInt();
    
  if(Serial.read() == '\n'){
    Serial.print("x : ");
    Serial.print(x);
    Serial.print("  y : ");
    Serial.print(y);
    Serial.print("    ");
  }
  moveCar(x,y);
}

void moveCar(int x, int y) {
  // 전진, 후진 제어
  if (valocity == 0) {
    if ( y < 13) {
      FBstate = HIGH;
      valocity = valocity + 10;
    } else if ( y < 17) {
      FBstate = HIGH;
    } else {
      FBstate = LOW;
      valocity = valocity + 10;
    }
    Serial.print("  stop");
    
  } else {
    if (FBstate == HIGH) {
      if ( y < 13) {
        valocity = valocity + 10;
        valocity = constrain(valocity, 0, 255);
        Serial.print("valocity : ");
        Serial.print(valocity);
        Serial.print("    forward");
        Serial.print("  acceleration");
      } else if ( y < 17) {
        valocity = constrain(valocity, 0, 255);
        Serial.print("valocity : ");
        Serial.print(valocity);
        Serial.print("    forward");
        Serial.print("  stay valocity");
      } else {
        valocity = valocity - 10;
        valocity = constrain(valocity, 0, 255);
        Serial.print("valocity : ");
        Serial.print(valocity);
        Serial.print("    forward");
        Serial.print("  deceleration");
      }
    }
    if (FBstate == LOW) {
      if ( y < 13) {
        valocity = valocity - 10;
        valocity = constrain(valocity, 0, 255);
        Serial.print("valocity : ");
        Serial.print(valocity);
        Serial.print("    backward");
        Serial.print("  deceleration");
      } else if ( y < 17) {
        valocity = constrain(valocity, 0, 255);
        Serial.print("valocity : ");
        Serial.print(valocity);
        Serial.print("    backward");
        Serial.print("  stay valocity");
      } else {
        valocity = valocity + 10;
        valocity = constrain(valocity, 0, 255);
        Serial.print("valocity : ");
        Serial.print(valocity);
        Serial.print("    backward");
        Serial.print("  acceleration");
      }
    }
  }
  analogWrite(PWM, valocity);
  delay(100);

  // 방향제어
  if (x < 7) {
    // 조향 모터가 '시계방향'으로 회전하도록 신호부여
    digitalWrite(dirPinLR,LOW); 
    
    // 500마이크로초 주기로 모터 축이 5회전하는 코드
    // 1:50 기어박스 내장되어 있으므로, 모터 1회전에 바퀴 7.2도 회전함
    // 따라서, 모터가 5회전하면 바퀴가 36도 회전함
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(50); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(50); 

    Serial.println("     right");
  } else if (x < 13) {
    // 스텝퍼모터 정지
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(50); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(50); 
    
    Serial.println("     stay direction");
    }else {
    // 조향 모터가 '시계방향'으로 회전하도록 신호부여
    digitalWrite(dirPinLR,HIGH); 
    
    // 500마이크로초 주기로 모터 축이 5회전하는 코드
    // 1:50 기어박스 내장되어 있으므로, 모터 1회전에 바퀴 7.2도 회전함
    // 따라서, 모터가 5회전하면 바퀴가 36도 회전함
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(50); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(50); 
    
    Serial.println("     left");
    }
}
