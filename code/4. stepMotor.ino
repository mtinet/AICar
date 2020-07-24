// 스텝 모터 제어
const int enA = 4;  // 구동 여부 결정
const int stepPin = 5; // 스텝 펄스
const int dirPinLR = 6;  // 좌우 회전

const int STEPS_PER_REV = 200; // 모터 1회전 

void setup() {
  //통신 설정
  Serial.begin(9600); // 시리얼 통신
  
  // 스텝모터 핀 모드 설정
  pinMode(dirPinLR,OUTPUT);
  pinMode(stepPin,OUTPUT); 
  pinMode(enA, OUTPUT);
  digitalWrite(enA, HIGH);
}

void loop() {
  // 조향 모터가 '반시계방향'으로 회전하도록 신호부여
  digitalWrite(dirPinLR,HIGH); 

  // 1000마이크로초 주기로 모터 축이 1.5회전하는 코드
  // 1:50 기어박스 내장되어 있으므로, 모터 1회전에 바퀴 7.2도 회전함
  // 따라서, 모터가 1.5회전하면 바퀴가 10.8도 회전함
  for(int x = 0; x < STEPS_PER_REV*1.5; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1000); 
  }

  // 조향 모터가 '시계방향'으로 회전하도록 신호부여
  digitalWrite(dirPinLR,LOW); 

  for(int x = 0; x < STEPS_PER_REV*1.5; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1000); 
  }
}
