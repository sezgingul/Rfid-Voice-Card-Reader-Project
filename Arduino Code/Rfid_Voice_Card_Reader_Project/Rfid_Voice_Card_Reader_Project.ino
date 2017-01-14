// Rfid Sesli Kart Okuyucu
// Coder: Sezgin GÜL
// www.sezgingul.com
// www.robimek.com
#include <SPI.h>
#include <RFID.h>
#include <Wtv020sd16p.h>
int resetPin = 2;
int clockPin = 3;
int dataPin = 4;
int busyPin = 5;
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);
RFID rfid(10,9); // rfid sda ve reset pinleri
  
byte emaomos[5] = {19,168,166,2,31}; // kartın kimlik numarası
byte serNum[5];
byte data[5];
int yesil_led = 6; // yeşil led
int kirmizi_led = 7; // kırmızı led
  
void setup(){
wtv020sd16p.reset();
Serial.begin(9600);
rfid.init();
  
pinMode(yesil_led,OUTPUT);
pinMode(kirmizi_led,OUTPUT);
  
}
  
void loop(){
  
boolean emaomos_card = true;
  
if (rfid.isCard()){ // karttan verilerin okunması
if (rfid.readCardSerial()){
delay(1000);
data[0] = rfid.serNum[0];
data[1] = rfid.serNum[1];
data[2] = rfid.serNum[2];
data[3] = rfid.serNum[3];
data[4] = rfid.serNum[4];
}
  
for(int i=0; i<5; i++){
if(data[i]!= emaomos[i]) emaomos_card = false;
}
if (emaomos_card){ // kartın verileri eşleşiyor ise
  
wtv020sd16p.playVoice(2);
delay(4000);
  
digitalWrite(yesil_led,HIGH);
delay(2000);
digitalWrite(yesil_led,LOW);
}
else{ // kimlik bilgileri eşleşmiyor ise
wtv020sd16p.playVoice(1);
delay(4000);
digitalWrite(kirmizi_led, HIGH);
  
delay(2000);
digitalWrite(kirmizi_led, LOW);
}
  
delay(500);
rfid.halt();
  
}
}
