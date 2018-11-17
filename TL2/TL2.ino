#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
 
int blueTx=12;   //Tx (보내는핀 설정)
int blueRx=13;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString=""; //받는 문자열

int TrafficLights1 []={2,3,4 };
int TrafficLights2 []={8,9,10 };

void  TrafficLight()
{

   digitalWrite(TrafficLights1[0],HIGH);    // 신호등 1 red On
   digitalWrite(TrafficLights2[2],HIGH);    //  신호등 2 green On
   delay(3000);
    
   digitalWrite(TrafficLights1[0],LOW); // 신호등1 red  off
   digitalWrite(TrafficLights2[2],LOW); // 신호등2 gren off
   delay(500);

   
   digitalWrite(TrafficLights1[2],HIGH); // 신호등1 green   on
   digitalWrite(TrafficLights2[0],HIGH); // 신호등2 red on                               
    delay(3000);
  
    digitalWrite(TrafficLights1[2],LOW); // 신호등1 red  off
   digitalWrite(TrafficLights2[0],LOW); // 신호등2 gren off
   delay(500);


  
}
 
void setup() {
  for(int i;i<6;i++)
  {
    pinMode(TrafficLights1[i],OUTPUT);
    pinMode(TrafficLights2[i],OUTPUT);
  }
  Serial.begin(9600);   //시리얼모니터 
  mySerial.begin(9600); //블루투스 시리얼 개방
  pinMode(13, OUTPUT);  //Pin 13을 OUTPUT으로 설정 (LED ON/OFF)
}
 
void loop()
{
        TrafficLight();
  
  while(mySerial.available())  //mySerial 값이 있으면
  {
    char myChar = (char)mySerial.read();  //mySerial int형식의 값을 char형식으로 변환
    myString+=myChar;   //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
  
  if(!myString.equals(""))  //myString 값이 있다면
  {
       Serial.println("input value: "+myString); //시리얼모니터에 myString값 출력
 
      if(myString=="o")  //myString 값이 'on' 이라면
      {
        digitalWrite(TrafficLights1[0], HIGH); //LED t1_red on
        digitalWrite(TrafficLights2[2], HIGH); //LED t2_green on     
        delay(7000);
      
      } 
      else if(myString=="L")
      {
        digitalWrite(TrafficLights1[2], HIGH); //LED T1_green on
        digitalWrite(TrafficLights2[0], HIGH); //LED T2_red  on 
        delay(7000);    
      }
      else
      {
        //digitalWrite(13, LOW);  //LED OF
      }
         
       myString="";  //myString 변수값 초기화
  }
   
    
}
