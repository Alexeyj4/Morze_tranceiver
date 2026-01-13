#include <Esp_now_j4.h>

//#define SPEAKER_FREQUENCY 3200 //maximum volume by datasheet on this speaker
#define SPEAKER_FREQUENCY 6000 
#define SPEAKER_REF_PIN 6 //D4
#define SPEAKER_PIN 4 //D6
#define BTN_REF_PIN 8 //D8
#define BTN_IN_PIN 10 //D10
#define TRANCEIVE_PAUSE 10

uint8_t MAC[] = {0x64, 0xE8, 0x33, 0xB5, 0x97, 0x48}; //transceiver 1
//uint8_t MAC[] = {0x64, 0xE8, 0x33, 0xB6, 0xBD, 0xDC}; //transceiver 2

Esp_now_j4 esp_now(MAC);

int buzzer_on_flag=0;

void setup() {    
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
      if(buzzer_on_flag==0){
        tone(SPEAKER_PIN, SPEAKER_FREQUENCY);
        buzzer_on_flag=1;
      }
    }
    if(s.startsWith("0")){
      noTone(SPEAKER_PIN);
      digitalWrite(SPEAKER_PIN, LOW);
      buzzer_on_flag=0;    
    }  
    esp_now.clr();
  }

  if(digitalRead(BTN_IN_PIN)==HIGH){    
    esp_now.send("1");
  }

  if(digitalRead(BTN_IN_PIN)==LOW){
    esp_now.send("0");
  }

  delay(TRANCEIVE_PAUSE);

}
