#include <Arduino.h>

// Definição das estruturas

// Data e hora do servidor NTC
struct dataHora
{
  String horastring;
  String semana;
  int dia;
  int horas;
  int minutos;
  int segundos;
};
// Estrutura dos dados dos temporizadores
struct Timer
{
  byte T = 0;
  unsigned long TempoAnterior = 0;
};

// Estruruas da base de dados do firebase

struct dadosFirebase
{
  double Chuva;
  double ChuvaDomingo;
  double ChuvaQuarta;
  double ChuvaQuinta;
  double ChuvaSabado;
  double ChuvaSegunda;
  double ChuvaSemana;
  double ChuvaSexta;
  double ChuvaTerca;
  String Horas;
  double Temperatura;
  double TempMaximaHoje;
  double TempMinimaHoje;
  double TemperaturaMaximaDomingo;
  double TemperaturaMaximaQuarta;
  double TemperaturaMaximaQuinta;
  double TemperaturaMaximaSabado;
  double TemperaturaMaximaSegunda;
  double TemperaturaMaximaSexta;
  double TemperaturaMaximaTerca;
  double TemperaturaMaxumaSemana;
  double TemperaturaMinimaDomingo;
  double TemperaturaMinimaQuarta;
  double TemperaturaMinimaQuinta;
  double TemperaturaMinimaSabado;
  double TemperaturaMinimaSegunda;
  double TemperaturaMinimaSemana;
  double TemperaturaMinimaSexta;
  double TemperaturaMinimaTerca;
  float Umidade;
  float UmidadeMaximaHoje;
  float UmidadeMinimaHoje;
  float TemperaturaDht;
  String HoraTemperaturaMaxima;
  String HoraTemperaturaMinima;
  String HoraUmidadeMaxima;
  String HoraumidadeMinina;
};

// Irrigacao Pivos

struct Pivos {
  unsigned floreita;
  unsigned tomates;
  unsigned horta;
  unsigned SetPointFloreira;
  unsigned SetPointTomates;
  unsigned SetpointHorta;
  int Hora;
  int Minuto;
  int DiaSemanaIrrigado;
};
