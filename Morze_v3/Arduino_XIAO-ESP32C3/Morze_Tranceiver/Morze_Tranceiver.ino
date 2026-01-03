//#define SPEAKER_FREQUENCY 3200 //maximum volume by datasheet on this speaker
#define SPEAKER_FREQUENCY 6000 
#define SPEAKER_REF_PIN 6 //D4
#define SPEAKER_PIN 4 //D6
#define BTN_REF_PIN 8 //D8
#define BTN_IN_PIN 10 //D10

void setup() {  
  pinMode(SPEAKER_REF_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  digitalWrite(SPEAKER_REF_PIN, LOW);
  digitalWrite(SPEAKER_PIN, LOW);
  pinMode(BTN_REF_PIN, OUTPUT);//Btn ref+
  pinMode(BTN_IN_PIN, INPUT_PULLDOWN);//Btn input
  digitalWrite(BTN_REF_PIN, HIGH);    
}


void loop() {  
  if(digitalRead(BTN_IN_PIN)==HIGH){
    tone(SPEAKER_PIN, SPEAKER_FREQUENCY);
  }
  delay(10);
  if(digitalRead(BTN_IN_PIN)==LOW){
    noTone(SPEAKER_PIN);
  }

  

}
