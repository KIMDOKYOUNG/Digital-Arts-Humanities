byte data[]={
0B01000000, //0
0B01111001, //1
0B00100100, //2
0B00110000, //3
0B00011001, //4,
0B00010010, //5
0B00000010, //6
0B01111000, //7
0B00000000, //8
0B00010000  //9
};

const byte latchPin = 10; //ST_CP Pin
const byte clockPin = 11; //SH_CP Pin
const byte dataPin = 9; //DS Pin
const byte SegPower = 8;
const byte TransversboardLight[2] = {12,13};
int cnt = 3;
boolean state = false;

const byte trafficLight[3] = {5,6,7};
const byte lightTime[3] = {5,2,7};
unsigned long timeVal = 0;
unsigned long timeSeg = 0;
int indexVal = 0;


void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(SegPower, OUTPUT);
  
  pinMode(TransversboardLight[0], OUTPUT);
  pinMode(TransversboardLight[1], OUTPUT);
  
  for(int i=0;i<3;i++){
    pinMode(trafficLight[i], OUTPUT);
  }  
  digitalWrite(trafficLight[indexVal], HIGH);
  digitalWrite(TransversboardLight[1], HIGH);
}

void loop()
{  
  if(millis()-timeVal>=lightTime[indexVal]*1000){
    digitalWrite(trafficLight[indexVal], LOW);  
    indexVal++;
    if(indexVal==3)indexVal=0;
    digitalWrite(trafficLight[indexVal], HIGH);
    timeVal=millis();    
    
    if(indexVal==2){
      state=true;
      timeSeg=millis();
      digitalWrite(TransversboardLight[1], LOW);
      digitalWrite(TransversboardLight[0], HIGH);
      
      digitalWrite(SegPower, HIGH);      
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, data[cnt]);
      digitalWrite(latchPin, HIGH);   
    }
  }
  if(state==true){
    if(cnt>0 && millis()-timeSeg>=1000){
      cnt--; 
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, data[cnt]);
      digitalWrite(latchPin, HIGH);                       
      timeSeg=millis();      
    }
    if(cnt==0 && millis()-timeSeg>=1000){
      cnt=3;
      state = false;      
      digitalWrite(SegPower, LOW);
      digitalWrite(TransversboardLight[0], LOW);
      digitalWrite(TransversboardLight[1], HIGH);
    }
  }  
}
