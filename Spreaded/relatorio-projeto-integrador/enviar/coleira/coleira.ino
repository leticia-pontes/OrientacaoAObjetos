// Example code for the connection, including the writing of values into the firebase --Andrei--

#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <TinyGPSPlus.h>

TinyGPSPlus gps; //OBJ GPS
//#define FIREBASE_HOST "https://petcaredb-44767-default-rtdb.firebaseio.com/"
//#define FIREBASE_AUTH "AIzaSyBNdHdC72MdlMSpgjDGXRXy0lim1mIgq0g"

//Classes, ConnectionWifi, usada para definir os parametros da rede wifi na qual o esp se conectará
class ConnectionWifi {       // Classe
  public:             
    static const char* ssid;        // Atributo ssid, nome da rede na qual o esp se conectará
    static const char* password;  // Atributo password,  senha da rede na qual o esp se conectará
  ConnectionWifi() : ssid("esp32"), password("12345678") {} // metodo construtor
};

//Classes, ConnectionFirebase, usada para definir os parametros do banco de dados firebase na qual o esp se conectará
class ConnectionFirebase {
  public:
    static const char* FIREBASE_HOST; // Atributo HOST, indica o link e servidor em que o banco encontra-se, estatico, pois não pode ser mutavel
    static const char* FIREBASE_AUTH; // Atributo AUTH, indica o token de conexão com o firebase, estatico, pois não pode ser mutavel
  ConnectionFirebase() : FIREBASE_HOST("https://petcaredb-44767-default-rtdb.firebaseio.com/"), FIREBASE_AUTH("AIzaSyBNdHdC72MdlMSpgjDGXRXy0lim1mIgq0g") {} // metodo construtor
};

class PulseSensor{
  public:
    static const int PulseSensorPin;
    static const int LedPin;
  PulseSensor() : PulseSensorPin(36), LedPin(12){}
};

void writePulseValue(const String& path, int pulse) {
  if (Firebase.setInt(firebaseData, path, pulse)) {
    Serial.println("Pulse(BPM) written to Firebase: " + String(value));
  } else {
    Serial.println("Failed to write pulse(BPM) to Firebase");
  }
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(3000);
  
  ConnectionWifi conexaoWifi();
  ConnectionFirebase conexaoFirebase();

  WiFi.begin(conexaoWifi.ssid, conexaoWifi.password);
  
  FirebaseData firebaseData;
  Firebase.begin(conexaoFirebase.FIREBASE_HOST, conexaoFirebase.FIREBASE_AUTH);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the network");
}

void updateSerial(){
  delay(500);
  while (Serial.available())  {
    Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (Serial2.available())  {
    Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
  }
}

void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid()){
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
}

void loop() {
  //updateSerial(); //executar essa função se estiver rodando o gps pela primeira vez
  displayInfo();
  writePulseValue("/Coleira/Pulso", 42);
}
