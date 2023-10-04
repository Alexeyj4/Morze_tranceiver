//user setup
const int button_pin=4;
const int tx_pin=2;
const int buzzer_pin=3;
const int beep_iter_max=100;
const int stadnby_iter_max=5000;
//end user setup

int stadnby_iter=stadnby_iter_max;
int beep_iter=beep_iter_max;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(button_pin, INPUT);
  pinMode(tx_pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(digitalRead(button_pin)==0){ //кнопка нажата
    tone(buzzer_pin,1000);
    beep_iter--;
    if(beep_iter<=0){
      beep_iter=beep_iter_max;
      if(digitalRead(tx_pin)==0){
        digitalWrite(tx_pin,1);
      }
      else{
        digitalWrite(tx_pin,0);        
      }
    }  
  }
  else{    //кнопка не нажата
    noTone(buzzer_pin);
    stadnby_iter--;
    if(stadnby_iter<=0){
      stadnby_iter=stadnby_iter_max;
      if(digitalRead(tx_pin)==0){
        digitalWrite(tx_pin,1);
      }
      else{
        digitalWrite(tx_pin,0);        
      }
    }
  }


}
