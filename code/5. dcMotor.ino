// 드라이브 모터 제어
const int PWM = 10; // 파워
const int in1 = 11; // 신호 1 
const int in2 = 12; // 신호 2
const int vcc = 13; // 5V 확인용

const int valocity = 100;

// 속도값 초기화
int i = 0;

void setup() {
  //통신 설정
  Serial.begin(9600); // 시리얼 통신
  
  // 드라이브모터 핀 모드 설정
  pinMode(PWM,OUTPUT);
  pinMode(in1,OUTPUT); 
  pinMode(in2, OUTPUT);
  pinMode(vcc, OUTPUT);
  digitalWrite(vcc, HIGH);
}

void loop() {
  //드라이브 모터가 앞으로 회전하도록 신호부여
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW); 
  analogWrite(PWM, i);

  if(i != valocity) {
    for (i = 0; i < valocity; i = i + 10) {
      analogWrite(PWM, i);
      delay(100);
    }
  }
  Serial.println("forward");  

  // 정지
  digitalWrite(in1,LOW); 
  digitalWrite(in2,LOW);
  
  analogWrite(PWM, 0);
  delay(100);
  Serial.println("motorStop");

  ////드라이브 모터가 뒤로 회전하도록 신호부여
  digitalWrite(in1,LOW); 
  digitalWrite(in2,HIGH); 
  analogWrite(PWM, i);
  
  if(i != valocity) {
    for (i = 0; i < valocity; i = i + 10) {
      analogWrite(PWM, i);
      delay(100);
    }
  }
  Serial.println("backward");
  
  // 정지
  digitalWrite(in1,LOW); 
  digitalWrite(in2,LOW);
  
  analogWrite(PWM, 0);
  delay(100);
  Serial.println("motorStop");
}
