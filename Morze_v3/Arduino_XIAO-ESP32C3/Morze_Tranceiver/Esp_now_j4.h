/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
#pragma once

#include "Esp_now.h"
#include "WiFi.h"

String EspNowReceivedString_;
uint8_t EspNowMac_[6];
 
 class Esp_now_j4{
  public:	 
    Esp_now_j4(uint8_t* mac_from_constructor);
	String s;
	void begin();
	void send(String s);
	String recvd();//""-not received	
	void clr();//clear received string	
  private:
static void OnDataRecv(const esp_now_recv_info* EspNowMac_, const uint8_t *incomingData, int len);// Обратная функция при получении по esp-now  
};

Esp_now_j4::Esp_now_j4(uint8_t* mac_from_constructor){
	memcpy(EspNowMac_, mac_from_constructor, 6);		
}  

void Esp_now_j4::begin(){ 
    // Выбираем режим WiFi
  //Serial.println("Запускаем протокол ESP-NOW");//debug
  WiFi.mode(WIFI_STA);
    // Запускаем протокол ESP-NOW
   if (esp_now_init() != ESP_OK) {
     //Serial.println("Error initializing ESP-NOW");//debug
     return;
   }
    // Регистрируем обратные функции  
  esp_now_register_recv_cb(OnDataRecv);
  
    // Указываем получателя
  esp_now_peer_info_t peerInfo={};
  memcpy(peerInfo.peer_addr, EspNowMac_, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
   if (esp_now_add_peer(&peerInfo) != ESP_OK){
     //Serial.println("Failed to add peer");//debug
     return;
   }  
}

void Esp_now_j4::send(String s){
  char c[s.length()+1];
  s.toCharArray(c,s.length()+1);  
  esp_err_t result = esp_now_send(EspNowMac_, (uint8_t *)c, sizeof(c));
}


void Esp_now_j4::OnDataRecv(const esp_now_recv_info* recv_info, const uint8_t *incomingData, int len) {  // Обратная функция при получении по esp-now
  if(strncmp((char*)EspNowMac_, (char*)recv_info->src_addr, 6)==0){
	  EspNowReceivedString_=String((char*)(incomingData));
	  //Serial.print("Received message: ");//debug
	  //Serial.println(EspNowReceivedString_);//debug
  }
  else{	  
	  //Serial.println("Wrong sender");//debug		
  }
}

String Esp_now_j4::recvd(){	
	return EspNowReceivedString_;
} 	

void Esp_now_j4::clr(){
	EspNowReceivedString_="";	
}