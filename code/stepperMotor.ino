/* 
아두이노 UNO - 모터 드라이버(DM322E)
         p3 - PUL
         p2 - DIR
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
*/

const int dirPin = 2;  // 회전 방향
const int stepPin = 3; // 스텝 펄스
 
// Motor steps per rotation
const int STEPS_PER_REV = 400; // 모터 1회전 
 
void setup() {
  
  // Setup the pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}
void loop() {
  // 모터가 '시계방향'으로 회전하도록 신호부여
  digitalWrite(dirPin,HIGH); 
  
  // 500마이크로초 주기로 모터 축이 5회전하는 코드
  // 1:50 기어박스 내장되어 있으므로, 모터 1회전에 바퀴 7.2도 회전함
  // 따라서, 모터가 5회전하면 바퀴가 36도 회전함
  for(int x = 0; x < STEPS_PER_REV*5; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  
  // 1초 쉼
  delay(1000); 
  
  //모터가 '반시계방향'으로 회전하도록 신호부여
  digitalWrite(dirPin,LOW); 
  
  // 500마이크로초 주기로 모터 축이 5회전하는 코드
  // 1:50 기어박스 내장되어 있으므로, 모터 1회전에 바퀴 7.2도 회전함
  // 따라서, 모터가 5회전하면 바퀴가 36도 회전함
  for(int x = 0; x < STEPS_PER_REV*5; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  
  // 1초 쉼
  delay(1000); 
    
    // 모터가 '반시계방향'으로 회전하도록 신호부여
  digitalWrite(dirPin,LOW); 
  
  // 500마이크로초 주기로 모터 축이 5회전하는 코드
  // 1:50 기어박스 내장되어 있으므로, 모터 1회전에 바퀴 7.2도 회전함
  // 따라서, 모터가 5회전하면 바퀴가 36도 회전함
  for(int x = 0; x < STEPS_PER_REV*5; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  
  // 1초 쉼
  delay(1000); 
  
  //모터가 '시계방향'으로 회전하도록 신호부여
  digitalWrite(dirPin,HIGH); 
  
  // 500마이크로초 주기로 모터 축이 5회전하는 코드
  // 1:50 기어박스 내장되어 있으므로, 모터 1회전에 바퀴 7.2도 회전함
  // 따라서, 모터가 5회전하면 바퀴가 36도 회전함
  for(int x = 0; x < STEPS_PER_REV*5; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  
  // 1초 쉼
  delay(1000); 
}
