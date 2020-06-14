const int PWM = 11;
const int dir = 10;

int pedal = A0;
int val = 0;

void setup() {
  pinMode(PWM, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(pedal, INPUT);
  Serial.begin(9600);
  analogWrite(PWM, 0);
}

void loop() {
  digitalWrite(dir, HIGH);

  val = analogRead(pedal);
  val = map(val, 200, 900, 0, 255);
  val = constrain(val, 0, 255);

  analogWrite(PWM, val);
  Serial.println(val);
}
