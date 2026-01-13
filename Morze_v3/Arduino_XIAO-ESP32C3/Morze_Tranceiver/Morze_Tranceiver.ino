#include <Esp_now_j4.h>

//#define SPEAKER_FREQUENCY 3200 //maximum volume by datasheet on this speaker
#define SPEAKER_FREQUENCY 6000 
#define SPEAKER_REF_PIN 6 //D4
#define SPEAKER_PIN 4 //D6
#define BTN_REF_PIN 8 //D8
#define BTN_IN_PIN 10 //D10
#define TRANCEIVE_PAUSE 50

//uint8_t MAC[] = {0x64, 0xE8, 0x33, 0xB5, 0x97, 0x48}; //transceiver 1
uint8_t MAC[] = {0x64, 0xE8, 0x33, 0xB6, 0xBD, 0xDC}; //transceiver 2

Esp_now_j4 esp_now(MAC);

void setup() {  
  Serial.begin(115200);
  esp_now.begin();
  pinMode(SPEAKER_REF_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  digitalWrite(SPEAKER_REF_PIN, LOW);
  digitalWrite(SPEAKER_PIN, LOW);
  pinMode(BTN_REF_PIN, OUTPUT);//Btn ref+
  pinMode(BTN_IN_PIN, INPUT_PULLDOWN);//Btn input
  digitalWrite(BTN_REF_PIN, HIGH);    
}


void loop() {  

  String s=esp_now.recvd();
  if(s!=""){
    if(s.startsWith("1")){
      tone(SPEAKER_PIN, SPEAKER_FREQUENCY);
    }
    if(s.startsWith("0")){
      noTone(SPEAKER_PIN);
      digitalWrite(SPEAKER_PIN, LOW);    
    }  
    esp_now.clr();
  }

  if(digitalRead(BTN_IN_PIN)==HIGH){    
    //tone(SPEAKER_PIN, SPEAKER_FREQUENCY);
    esp_now.send("1");
  }

  delay(TRANCEIVE_PAUSE);

  if(digitalRead(BTN_IN_PIN)==LOW){
    noTone(SPEAKER_PIN);
    digitalWrite(SPEAKER_PIN, LOW);
    esp_now.send("0");
  }



}
