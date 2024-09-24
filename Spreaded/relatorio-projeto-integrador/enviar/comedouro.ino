// Bibliotecas usadas

#include <WiFi.h>
#include "time.h"
#include <FirebaseESP32.h>
#include <ESP32Servo.h>
#include <string.h>


// Credenciais de Wifi
const char* WIFI_SSID = "LETICIA";
const char* WIFI_PASSWORD = "fepr8693";


// Configuração do servidor NTP
const char* NTP_SERVER = "pool.ntp.org";
const long  GMT_OFFSET_SEC = -10800;
const int   DAYLIGHT_OFFSET_SEC = 0;

struct tm timeinfo;


// Configuração do Firebase
#define API_KEY "AIzaSyAB3bUSrHm-h-GzToxUFtZVMZXQJSoJXpc"
#define DATABASE_URL "https://projeto-integrador-46e02-default-rtdb.firebaseio.com/"

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

bool signedUp = false;

unsigned long tempoChecagemAnteriorMillis = 0;
const unsigned long intervaloChecagemMillis = 8000;


const int trigger = 19;
const int echo = 18;

const int pin_servo = 15;
Servo servo;


int distanciaCapacidadeContainer;

int horaAlmoco;
int minutoAlmoco;
int horaJanta;
int minutoJanta;
int horaAtualInt;
int minutoAtualInt;


// Classes
class Comedouro {

  public:
    bool containerVazio;

    Comedouro(bool containerVazio, bool tampaAberta) {
      this->containerVazio = containerVazio;
    }
};

class Horario {

  private:

    int hora;
    int minuto;
  
  public: 

    Horario(int hora, int minuto) : hora(hora), minuto(minuto) {}

    int getHora() const {
      return hora;
    }

    int getMinuto() const {
      return minuto;
    }

    void mostrarHorario() {
      Serial.print(hora);
      Serial.print(":");
      Serial.print(minuto);
      Serial.println();
    }

    bool operator==(const Horario& other) const {
      if ( this == &other ) return true;
      if ( this->hora != other.hora ) return false;
      if ( this->minuto != other.minuto ) return false;
      return true;
    }

    bool ehMeiaNoite() const {
      return hora == 0 && minuto == 0;
    }
};

class Refeicao {

  private:

    Horario horarioDefinido;
    bool refeicaoFeita;
  
  public:

    Refeicao(const Horario& horarioDefinido, bool refeicaoFeita) :
    horarioDefinido(horarioDefinido), refeicaoFeita(refeicaoFeita) {}

    Horario getHorario() const {
      return horarioDefinido;
    }

    void setHorario(const Horario& novoHorario) {
      horarioDefinido = novoHorario;
    }

    bool getRefeicaoFeita() const {
      return refeicaoFeita;
    }

    bool ehHorarioRefeicao(const Horario& agora) const {
        return agora == horarioDefinido;
    }

    void completarRefeicao() {
      refeicaoFeita = true;
    }

    void resetarRefeicao() {
      refeicaoFeita = false;
    }
};


// Funções do sistema

// Wifi
void conectarWifi() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("\nConectando");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println("Conectado!");
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Horário Atual
void configurarHorarioAtualNTP() {

  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
}

Horario getHorarioAtualNTP() {

  char horaAtual[3];
  strftime(horaAtual, 3, "%H", &timeinfo);
  sscanf(horaAtual, "%d", &horaAtualInt);

  char minutoAtual[3];
  strftime(minutoAtual, 3, "%M", &timeinfo);
  sscanf(minutoAtual, "%d", &minutoAtualInt);

  Horario agora(horaAtualInt, minutoAtualInt);

  return agora;
}

// Firebase
void conectarFirebase() {

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    signedUp = true;
    Serial.println("Firebase Connection Successful\n");
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

Horario getHorarioRefeicaoFirebase(FirebaseData& fbdo, char* tipoRefeicao) {

  int hora, minuto;

  char pathHora[30], pathMinuto[30];

  snprintf(pathHora, sizeof(pathHora), "hora-refeicao/%s/hora", tipoRefeicao);
  snprintf(pathMinuto, sizeof(pathMinuto), "hora-refeicao/%s/minuto", tipoRefeicao);

  hora = Firebase.getInt(fbdo, pathHora) ? fbdo.intData() : 0;
  minuto = Firebase.getInt(fbdo, pathMinuto) ? fbdo.intData() : 0;

  Horario horario(hora, minuto);

  return horario;
}

int verificarCapacidade() {

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  int retorno = pulseIn(echo, HIGH);
  
  int distanciaCM = retorno / 58.2;

  return distanciaCM;
}

void liberarRacao() {
  servo.write(0);
  delay(1300);
  servo.write(90);
}


// Execução do código
void setup() {

  Serial.begin(115200);
  Serial.println("\nHello, ESP32!");

  conectarWifi();

  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
  configurarHorarioAtualNTP();

  conectarFirebase();

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  servo.attach(pin_servo);
  servo.write(90);
}

Comedouro comedouro(false, false);
Refeicao almoco(Horario(0, 0), false);
Refeicao janta(Horario(0, 0), false);

void loop() {

  unsigned long tempoChecagemAtualMillis = millis();

  if (tempoChecagemAtualMillis - tempoChecagemAnteriorMillis >= intervaloChecagemMillis) {
    tempoChecagemAnteriorMillis = tempoChecagemAtualMillis;

    if (Firebase.ready() && signedUp) {

      distanciaCapacidadeContainer = verificarCapacidade();

      comedouro.containerVazio = (distanciaCapacidadeContainer >= 20);
      Firebase.setBool(fbdo, "container/vazio", comedouro.containerVazio);

      Serial.print("\n\nConteiner ");
      Serial.print(comedouro.containerVazio ? "vazio" : "cheio");
      Serial.print("!");
      Serial.print("\nDistância: ");
      Serial.print(distanciaCapacidadeContainer);
      Serial.print(" cm\n");

      configurarHorarioAtualNTP();
      Horario agora = getHorarioAtualNTP();
      Serial.print("\nHorario atual: ");
      agora.mostrarHorario();

      if (agora.ehMeiaNoite()) {
        almoco.resetarRefeicao();
        janta.resetarRefeicao();
      }

      Horario horarioAlmoco = getHorarioRefeicaoFirebase(fbdo, "almoco");
      Horario horarioJanta = getHorarioRefeicaoFirebase(fbdo, "janta");

      almoco.setHorario(horarioAlmoco);
      janta.setHorario(horarioJanta);


      Serial.print("Horario do almoco: ");
      almoco.getHorario().mostrarHorario();

      Serial.print("Horario da janta: ");
      horarioJanta.mostrarHorario();

      if (almoco.ehHorarioRefeicao(agora) && !almoco.getRefeicaoFeita() && !comedouro.containerVazio) {
        liberarRacao();
        almoco.completarRefeicao();
        Firebase.setBool(fbdo, "hora-refeicao/almoco/feito", almoco.getRefeicaoFeita());
      }
      
      else if (janta.ehHorarioRefeicao(agora) && !janta.getRefeicaoFeita() && !comedouro.containerVazio) {
        liberarRacao();
        janta.completarRefeicao();
        Firebase.setBool(fbdo, "hora-refeicao/janta/feito", janta.getRefeicaoFeita());
      }
    
    }
  }
}