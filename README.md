# AICar

### 1. 페달 테스트  
* [코드 링크](https://github.com/mtinet/AICar/blob/master/code/1.%20pedal.ino)  
* 테스트 이미지  
![](https://github.com/mtinet/AICar/blob/master/image/Slide1.jpg?raw=true) 

### 2. 전진, 후진 스위치 테스트  
* [코드 링크](https://github.com/mtinet/AICar/blob/master/code/2.%20switch.ino)  
* 테스트 이미지  
![](https://github.com/mtinet/AICar/blob/master/image/Slide2.jpg?raw=true) 

### 3. 블루투스 테스트  
* [코드 링크](https://github.com/mtinet/AICar/blob/master/code/3.%20bluetooth.ino)  
* 테스트 이미지  
![](https://github.com/mtinet/AICar/blob/master/image/Slide3.jpg?raw=true)  

### 4. 스텝모터 테스트  
* [코드 링크](https://github.com/mtinet/AICar/blob/master/code/4.%20stepMotor.ino)  
* 테스트 이미지  
![](https://github.com/mtinet/autonomousCar/blob/master/image/stepMotorCircuit.jpg?raw=true)  
![](https://github.com/mtinet/AICar/blob/master/image/Slide4.jpg?raw=true) 

### 5. DC모터 테스트  
* [코드 링크]()  
* 테스트 이미지  
![](https://github.com/mtinet/AICar/blob/master/image/Slide5.jpg?raw=true)  
![](https://github.com/mtinet/AICar/blob/master/image/Slide6.jpg?raw=true) 

### 6. 배터리 연결 및 비상정지 스위치 
* [코드 링크]()  
* 테스트 이미지  
![](https://github.com/mtinet/AICar/blob/master/image/Slide7.jpg?raw=true) 

### 7. 전체 테스트  
* [코드 링크](https://github.com/mtinet/AICar/blob/master/code/1.%20buttonVoiceVisionCar_miniboard.ino)  
![](https://github.com/mtinet/AICar/blob/master/image/Slide8.jpg?raw=true)  

### 모터 드라이버 구입  
* [[SMG-A] 12V/24V 7A 160W 듀얼 DC 모터 드라이버 모듈 [SZH-CH076]](https://www.devicemart.co.kr/goods/view?no=1361692)  
* [[ITM] TB6600 스테핑 모터드라이버](https://www.devicemart.co.kr/goods/view?no=10894384)  
* [Electric Bike/Scooter Foot Pedal Throttle Ebike Electric Tricycle Accelerator Pedal Speed Control Bicycle kit](https://www.aliexpress.com/item/32916923695.html?spm=a2g0o.cart.0.0.6cd43c00q48Iys&mp=1)  

### 앱인벤터  
* [이미지 분류 학습](https://classifier.appinventor.mit.edu/)  
* [익스텐션 다운로드](https://mit-cml.github.io/extensions/) : PersonalImageClassifier, BLE 다운로드 받을 것  
* BLE 세팅 방법  
![](https://github.com/mtinet/AICar/blob/master/image/bleConnect.png?raw=true)  
```
serviceUUID : 0000FFE0-0000-1000-8000-00805F9B34FB
name : 아두이노의 AT커맨드로 자기가 지정해 준 이름 입력  
```
* 아두이노 AT 커맨드 사용할 때 업로드 해야하는 코드, 블루투스 모듈(HM-10)이 다른 장치에 연결되지 않은 상태에서만 AT 커맨드가 적용됨, 아두이노의 시리얼 모니터 하단에 있는 옵션에서는 'line ending 없음' 또는 'Both NL & ER'을 선택하고, 통신속도는 9600보드레이트로 선택함  
```
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }

  Serial.println("Goodnight moon!");

  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop() { 
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
```

### 참고자료  
* [앱인벤터 코드 작성 참고자료](http://blog.naver.com/PostView.nhn?blogId=kids_power&logNo=221368450791&parentCategoryNo=&categoryNo=42&viewDate=&isShowPopularPosts=true&from=search)  
* [앱인벤터, 아두이노 통신](http://sanguru.me/arduino009/) 
* [딕셔너리 결과물 보는 방법](http://ai2.appinventor.mit.edu/reference/blocks/dictionaries.html#get-value-at-key-path)  
* [BLE 세팅](http://www.martyncurrey.com/arduino-hm-10-and-app-inventor-2/#AI2)  

