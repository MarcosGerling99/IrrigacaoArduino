
// Autor Marcos Gerling.
#include <Arduino.h> 
#include <NTPClient.h>   //Biblioteca do NTP.
#include <ESP8266WiFi.h> //Biblioteca do WiFi.
#include <WiFiUDP.h>     //Biblioteca do UDP.
#include "DHTesp.h"      //Biblioteca do sensor de temperatura e umidade
DHTesp dht;

WiFiUDP udp;                                          //Cria um objeto "UDP".
NTPClient ntp(udp, "a.st1.ntp.br", -3 * 3600, 60000); //Cria um objeto "NTP" com as configurações.

//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"

#define FIREBASE_HOST "irrigacao.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "Jus3ZdHmdK5lX5b8JIZuft9v2KUw7XejNtKZv9BU"
#define WIFI_SSID "TP-LINK"
#define WIFI_PASSWORD "infantarialeve"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseJson json;

#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>

OneWire barramento(D5);

DallasTemperature sensor(&barramento);

// Definição dos I/Os

#define led D4 //Define o LED ao pino D4.
// D1 e D2 I2C
#define Floreira D1           // saida do rele da floreira.
#define Tomates D7            // saida do rele dos tomates.
#define Horta D8              // saida do rele da horta.
#define entradaSensorChuva D2 // Definie a entrada difital do sensor do pluviometro de bascula.
#define SensorUmidade 12      // Entrada do sensor de umidade.

// Definição de variaveis globais.

String horastring, semana; //Váriavel que armazenara o horario do NTP.
int dia = 0, horas = 0, minutos = 0, segundos = 0;
byte Irrigou = 0, DiaDeHoje = 64;
unsigned long tempoanterior = 0;
unsigned long tempoanterior2 = 0;
unsigned long tempoChuva;
unsigned scan = 0, tempoAtualizacaoChuva = 0;
bool pulsoSensor = false, Choveu = false, IrrigacaoStart = false, SensorChuva = false;
int IrrigaAgora = 0;
int ContaDebug = 0;
byte chuvaHoje = 0, chuvaOntem = 0;

#include <estruturas.h>

// Definição dos objetos das estruturas
dadosFirebase BaseDados;
Timer Temp5000ms;
Timer Temp2000ms;
Timer Temp1000ms;
Timer tempo500ms;
Timer Temp250ms;
dataHora datas;
Pivos irrigarDados;

// Chama arquivos de funçoes externas
#include <eprom.h>       // Chama as funcoes que gravam na Eeprom.
#include <firebase.h>    // Chama as funções que atualizam no firebase.
#include <ntpRtc.h>      // Chama as funções que atualizam a data e a hora do servidor NTP.
#include <clock.h>       // Chama a função de tempo.
#include <sensores.h>    // Chama a rotina para leitura dos sensores.
#include <estatistica.h> // Chama a estatistica.
#include <irrigacao.h>   // chama a rotina que irriga.
#include <testes.h>      // Chama uma rotina de teste.

ICACHE_RAM_ATTR void InterrupcaoChoveu()
{

  if (!digitalRead(entradaSensorChuva) == HIGH)
  {
    SensorChuva = true;
  }
  else
  {
    SensorChuva = false;
  }

  if (tempoChuva < millis())
  {
    BaseDados.Chuva = SensorBascula(SensorChuva, BaseDados.Chuva);
  }
}

void setup()
{
  // put your setup code here, to run once:

  Serial.begin(115200);                 //Inicia a comunicação serial.
  pinMode(led, OUTPUT);               //Define o pino como saida.
  pinMode(entradaSensorChuva, INPUT); // Define como entrada a leitura do sensor INPUT_PULLUP.
  digitalWrite(led, 1);
  pinMode(Floreira, OUTPUT); // Define a saida da floreira.
  pinMode(Tomates, OUTPUT);  // Define a saida dos tomates.
  pinMode(Horta, OUTPUT);    // Define a saida da horta.

  attachInterrupt(digitalPinToInterrupt(entradaSensorChuva), InterrupcaoChoveu, CHANGE);

  irrigarDados.SetPointFloreira = 20;
  irrigarDados.SetPointTomates = 40;
  irrigarDados.SetpointHorta = 60;

  // Seta as saida em HIGH.

  digitalWrite(Floreira, LOW);
  digitalWrite(Tomates, LOW);
  digitalWrite(Horta, LOW);

  // Le a Eprom quando inicia.
  //GravarEprom(0);
  LerEprom();
  LerChuvaEprom();

  dht.setup(SensorUmidade, DHTesp::DHT22); // Connect DHT sensor to GPIO 17                      //Apaga o LED.

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData.setResponseSize(1024);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */
}

void loop()
{

  //FuncaoDeTeste(); // função de teste.

  Temp5000ms = Clock(Temp5000ms, 600000); // Atualiza o firebase
  Temp1000ms = Clock(Temp1000ms, 1000);   // Atualiza hora e temperaturas.
  Temp250ms = Clock(Temp250ms, 250);

  Irriga(); // Chama a função que verifica a irrigação.

  if (Temp5000ms.T)
  {
    // Atualiza todos os dados
    scan = AtuaizaFirebase(scan);
    // Atualiza novamente a chuva
    if (BaseDados.Chuva != 0.0)
    {
      AtualizaChuva();
    }
  }

  if (Temp1000ms.T)
  {
    // Chama o Servidor NTP
    datas = HoraNTP(datas);
    // Chama a leitura da temperatura
    sensor.requestTemperatures();
    //Serial.print("Temperatura ds18b20: ");
    //Serial.println(sensor.getTempCByIndex(0));
    BaseDados.Temperatura = sensor.getTempCByIndex(0);

    // Chama a atualização da chuva a cada um minuto depois
    if (Choveu)
    {
      if (tempoAtualizacaoChuva < 30)
      {
        tempoAtualizacaoChuva++;
      }
      else
      {
        GravaChuvaEprom(BaseDados.Chuva); // Grava na Eprom quanto choveu
        AtualizaChuva();
        Choveu = false;
        tempoAtualizacaoChuva = 0;
      }
    }

    // Chama a leitura da temperatura DHT
    //Serial.println(dht.getStatusString());
    BaseDados.TemperaturaDht = dht.getTemperature();
    BaseDados.Umidade = dht.getHumidity();
    //Serial.print("TempDHTBASE: ");
    //Serial.println(BaseDados.TemperaturaDht);
    //Serial.print("UmidadeBASE: ");
   //Serial.println(BaseDados.Umidade);
    //Serial.print("Chuva!!: ");
    //Serial.println(BaseDados.Chuva);
    //Serial.print("HoraIrrigar: ");
    //Serial.println(irrigarDados.Hora);
    //Serial.print("MinutoIrrigar:");
    //Serial.println(irrigarDados.Minuto);
    Serial.print("Irrigou:  ");
    Serial.println(Irrigou);
    //Serial.print("IrrigaAgora:  ");
    //Serial.println(IrrigaAgora);
  }

  if (Temp250ms.T)
  {
    MaximosEminimos(); // Chama a função de maximos e minimos

    if (digitalRead(led) == LOW)
    {
      digitalWrite(led, HIGH);
    }
    else
    {
      digitalWrite(led, LOW);
    }
    if (!digitalRead(entradaSensorChuva) == HIGH)
    {
      Serial.println("CHOVEU:@@@@@@");
    }
  }
}