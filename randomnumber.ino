#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "auth";
char ssid[] = "ssid";
char pass[] = "pass";
int radiation[] = {0,0,0,0};
int posicao = 0;
int inverter = 0;
int result = 0;
String missanga = "";
int virtualpin = 1;
String blynko;
int upload;

void boing() {
    int first;
    int second;
    radiation[posicao] = micros();
    posicao = posicao + 1;
    if (posicao == 4){
    posicao = 0;
    first = radiation[1] - radiation [0];
        second = radiation[3] - radiation[2];
        if (first != second) {
            if (inverter == 0) {
                inverter = 1;}
                if (first > second){
                    result = 1;}
                else{
                    result = 0;}}
            else{
                inverter = 0;}
                if (first > second){
                    result = 0;}
                else{
                    result = 1;}
        posicao = 0;
        missanga = String(result) + missanga;
        if (missanga.length() == 8){

    virtualpin= virtualpin +1;
    if (virtualpin == 251){
      virtualpin = 1;
    }
    blynko = missanga;
    missanga = "";
    upload = 1;
        } 

        }
}

void setup() {
    // Debug console
    pinMode(36, INPUT_PULLUP);
    attachInterrupt(36, boing, FALLING);
    Blynk.begin(auth, ssid, pass);
    M5.begin();
}


void loop() {

    Blynk.run();
    if (upload ==1){
      Blynk.virtualWrite(virtualpin, blynko);
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(10, 10);
      M5.Lcd.setTextColor(WHITE);
      M5.Lcd.setTextSize(3);
      M5.Lcd.drawString(String(virtualpin), 160, 120);
      upload = 0;}

}
