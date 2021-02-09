# AICar

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
void setup() {
  //통신 설정
  Serial.begin(9600); // 시리얼 통신(컴퓨터-USB케이블-아두이노 메가)
  Serial3.begin(9600); // 블루투스 통신(스마트폰 앱-블루투스-아두이노 메가)
  Serial.println("start");
}

void loop() {
  if (Serial3.available())        // 블루투스에서 데이터가 들어올 경우
    Serial.write(Serial3.read()); // 컴퓨터로 보냄
  if (Serial.available())         // 컴퓨터에서 데이터가 들어올 경우
    Serial3.write(Serial.read()); // 블루투스로 보냄
}
```

### 참고자료  
* [앱인벤터 코드 작성 참고자료](http://blog.naver.com/PostView.nhn?blogId=kids_power&logNo=221368450791&parentCategoryNo=&categoryNo=42&viewDate=&isShowPopularPosts=true&from=search)  
* [앱인벤터, 아두이노 통신](http://sanguru.me/arduino009/) 
* [딕셔너리 결과물 보는 방법](http://ai2.appinventor.mit.edu/reference/blocks/dictionaries.html#get-value-at-key-path)  
* [BLE 세팅](http://www.martyncurrey.com/arduino-hm-10-and-app-inventor-2/#AI2)  

