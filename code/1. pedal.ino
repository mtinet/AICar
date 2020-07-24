const int pedalSensor = A0;
int pedalVal = 0;

void setup() {
  //통신 설정
  Serial.begin(9600); // 시리얼 통신
}

void loop() {
  pedalVal = analogRead(pedalSensor);
  Serial.print(pedalVal);
  Serial.print("  ");
  pedalVal = map(pedalVal, 230, 850, 0, 255);
  Serial.print(pedalVal);
  Serial.print("  ");
  pedalVal = constrain(pedalVal, 0, 255);
  Serial.println(pedalVal);
}
