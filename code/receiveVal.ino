#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

String readString;

void setup() {
  //통신 설정
  Serial.begin(9600); // 시리얼 통신
  mySerial.begin(9600); // 블루투스 통신      
  Serial.println("serial-delimit-21"); // so I can keep track of what is loaded
}

void loop() {

  //expect a string like wer,qwe rty,123 456,hyre kjhg,
  //or like hello world,who are you?,bye!,
  while (mySerial.available()) {
    delay(10);  //small delay to allow input buffer to fill

    char c = mySerial.read();  //gets one byte from serial buffer
    if (c == '\n') {
      break;
    }  //breaks out of capture loop to print readstring
    readString += c;
  } //makes the string readString 

  if (readString.length() >0) {
    Serial.println(readString); //prints string to serial port out

    readString=""; //clears variable for new input
  }

  Serial.println(readString);
}
