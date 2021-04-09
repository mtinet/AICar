#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // TXD, RXD

char cmd = "";
boolean modeState = 1;

void setup() {
  //통신 설정
  Serial.begin(9600); // 시리얼 통신
  mySerial.begin(9600); // 블루투스 통신   
}

void loop() {
  if (mySerial.available() ){        // 블루투스 통신에 데이터가 있을 경우
    cmd = mySerial.read();     // 블루투스의 데이터(문자 한 글자)를 'cmd' 변수에 저장
  
    // cmd 변수의 데이터가 m이면 modeState의 상태를 바꿈
    if (cmd == 'm') {
      modeState = !modeState;
      Serial.println("input 'm'");
      Serial.print("mode is : ");
      Serial.println(modeState);
    }
  }
}
