int pedalF = 7;
boolean pedalFVal = 0;

int pedalB = 8;
boolean pedalBVal = 0;

const int ground = 9;

void setup() {
  //통신 설정
  Serial.begin(9600); // 시리얼 통신

  // 페달모드 전진 후진 신호
  pinMode(pedalF, INPUT_PULLUP);
  pinMode(pedalB, INPUT_PULLUP);
  pinMode(ground, OUTPUT);
  digitalWrite(ground, LOW);
}

void loop() {
  // 전진, 후진 스위치 값 저장
  pedalFVal = digitalRead(pedalF);
  pedalBVal = digitalRead(pedalB);

  // 페달 값 변화 시리얼 모니터링
  Serial.print(pedalFVal);
  Serial.print("  ");
  Serial.println(pedalBVal);
}
