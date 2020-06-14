// 이 프로그램을 업로드 할 때는 반드시 블루투스 모듈의 tx, rx핀을 제거하고 진행하세요.
// 업로드가 완료되면,
// 블루투스 모듈의 tx는 아두이노 0번 핀에 꽂으세요.
// 블루투스 모듈의 rx는 아두이노 1번 핀에 꽂으세요.

int x = 0;
int y = 0;

void setup() {
  Serial.begin(9600); // 시리얼 통신   
  Serial.println("Now Start Receive Data by parseInt..."); 
}

void loop() {
}

void serialEvent(){
  int x = Serial.parseInt();
  int y = Serial.parseInt();
    
  if(Serial.read() == '\n'){
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
  }
}

    
