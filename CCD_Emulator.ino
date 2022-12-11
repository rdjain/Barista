/*
 * CCD_Emulator.ino
 *
 * Author: Rishabh Jain
 */ 
 
#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal.h>
#define buzzerPin 33
/*Specifying the SSID and Password of the WiFi*/

const char *ssid = "CCD_INDUS_69";
const char *password = "";
 
//Specifying the Webserver instance to connect with HTTP Port: 80
WebServer server(80);
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal My_LCD(13, 12, 14, 27, 26, 25);

void buzzer(int times, int del){
  int i = 0;
  for (i = 0; i<= times; i++){
    digitalWrite(buzzerPin, HIGH);
    delay(del);
    digitalWrite(buzzerPin, LOW);
    delay(del); 
  }
}

void setup() {
  pinMode(buzzerPin,OUTPUT);
  digitalWrite(buzzerPin,LOW);
  analogWrite(2,85);
  My_LCD.begin(16, 2);
  My_LCD.clear();
  My_LCD.print("Setting AP...");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  //Specifying the functions which will be executed upon corresponding GET request from the client
  server.on("/",handle_OnConnect);
  server.on("/led1on",handle_led1on);
  server.on("/led2on",handle_led2on);
  server.on("/led3on",handle_led3on);
  server.on("/led5on",handle_led5on);
  server.on("/led6on",handle_led6on);
  server.onNotFound(handle_NotFound);
  //Starting the Server
  server.begin();
  My_LCD.clear();
  My_LCD.print("Barista Ready!");
  buzzer(1, 2000);
  
}
 
void loop() {
  server.handleClient();

}
 
void handle_OnConnect()
{
  server.send(200, "text/plain", "Welcome to Barista!"); 
  My_LCD.clear();
  My_LCD.print("What Drink?");
  buzzer(4, 300);
}
 
void handle_led1on()
{
  server.send(200, "text/plain", "Cappucino");
  My_LCD.clear();
  My_LCD.print("Cappucino");
  buzzer(4, 300);
  
}
 
void handle_led2on()
{
  server.send(200, "text/plain", "Espresso");
  My_LCD.clear();
  My_LCD.print("Espresso");
  buzzer(4, 300);
}
 
void handle_led3on()
{
  server.send(200, "text/plain", "Latte");
  My_LCD.clear();
  My_LCD.print("Latte");
  buzzer(4, 300);
}

void handle_led5on()
{
  server.send(200, "text/plain", "Milk");
  My_LCD.clear();
  My_LCD.print("Milk");
  buzzer(4, 300);
}


void handle_led6on()
{
  server.send(200, "text/plain", "Water");
  My_LCD.clear();
  My_LCD.print("Water");
  buzzer(4, 300);
}

void handle_NotFound()
{
  server.send(404, "text/plain", "No Such drink");
  My_LCD.clear();
  My_LCD.print("No such drink");
  buzzer(4, 300);
}
 
