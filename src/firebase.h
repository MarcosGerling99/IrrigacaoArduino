#include <Arduino.h>

void AtualizaIrrigou(byte irrigou)
{
  Firebase.setInt(firebaseData, "IrrigaAgora", IrrigaAgora);
  int AtualizaIrrigou = (int)Irrigou;
  Firebase.setInt(firebaseData, "Irrigou", AtualizaIrrigou);
}

void FalhaFirebase(byte Estado)
{
  if (Estado == 0)
  {
    Serial.println("Firebase Write Ok!");
  }
  else
  {
    Serial.println("Firebase Write Fail!");
  }
}

double LerChuva(int diaSemana)
{

  double ChuvaHoje = 0.0;

  // Leitura do minuto para Irrigar
  if (Firebase.getInt(firebaseData, "Chuva"))
  {
    if (firebaseData.dataType() == "int")
    {
      ChuvaHoje = (double)firebaseData.intData();
    }
  }

  return ChuvaHoje;
}

void AtualizaChuva()
{
  Firebase.setDouble(firebaseData, "Chuva", BaseDados.Chuva);
  if (BaseDados.Chuva != 0.0)
  {
    Firebase.setString(firebaseData, "HoraUltimaChuva", datas.horastring);
  }
}

void AtualizatemperaturaDia(int DiadaSemana, double Maxima, double Minima, double Chuva)
{
  switch (datas.dia - 1)
  {       // Converte o numero em dia da semana
  case 0: // Domingo
    Firebase.setDouble(firebaseData, "TemperaturaMaximaDomingo", Maxima);
    Firebase.setDouble(firebaseData, "TemperaturaMinimaDomingo", Minima);
    Firebase.setDouble(firebaseData, "ChuvaDomingo", Chuva);
    break;
  case 1: // Segunda
    Firebase.setDouble(firebaseData, "TemperaturaMaximaSegunda", Maxima);
    Firebase.setDouble(firebaseData, "TemperaturaMinimaSegunda", Minima);
    Firebase.setDouble(firebaseData, "ChuvaSegunda", Chuva);
    break;
  case 2: // terça
    Firebase.setDouble(firebaseData, "TemperaturaMaximaTerca", Maxima);
    Firebase.setDouble(firebaseData, "TemperaturaMinimaTerca", Minima);
    Firebase.setDouble(firebaseData, "ChuvaTerca", Chuva);
    break;
  case 3: // Quarta
    Firebase.setDouble(firebaseData, "TemperaturaMaximaQuarta", Maxima);
    Firebase.setDouble(firebaseData, "TemperaturaMinimaQuarta", Minima);
    Firebase.setDouble(firebaseData, "ChuvaQuarta", Chuva);
    break;
  case 4: // Quinta
    Firebase.setDouble(firebaseData, "TemperaturaMaximaQuinta", Maxima);
    Firebase.setDouble(firebaseData, "TemperaturaMinimaQuinta", Minima);
    Firebase.setDouble(firebaseData, "ChuvaQuinta", Chuva);
    break;
  case 5: // Sexta
    Firebase.setDouble(firebaseData, "TemperaturaMaximaSexta", Maxima);
    Firebase.setDouble(firebaseData, "TemperaturaMinimaSexta", Minima);
    Firebase.setDouble(firebaseData, "ChuvaSexta", Chuva);
    break;
  case 6: // Sábado
    Firebase.setDouble(firebaseData, "TemperaturaMaximaSabado", Maxima);
    Firebase.setDouble(firebaseData, "TemperaturaMinimaSabado", Minima);
    Firebase.setDouble(firebaseData, "ChuvaSexta", Chuva);
    break;
  default:
    datas.semana = "Nemhum";
    break;
  }
}

unsigned AtuaizaFirebase(unsigned ContadorScan)
{
  // Grava a temperatura DS18B20
  if (Firebase.setDouble(firebaseData, "Temperatura", BaseDados.Temperatura))
  {
    FalhaFirebase(0);
  }
  else
  {
    FalhaFirebase(1);
    ContadorScan = 1;
  }

  // Grava a temperatura maxima
  if (Firebase.setDouble(firebaseData, "TempMaximaHoje", BaseDados.TempMaximaHoje))
  {
    Firebase.setString(firebaseData, "HoraTemperaturaMaxima", BaseDados.HoraTemperaturaMaxima);
    FalhaFirebase(0);
  }
  else
  {
    FalhaFirebase(1);
    ContadorScan = 11;
  }

  // Grava a temperatura minima
  if (Firebase.setDouble(firebaseData, "TempMinimaHoje", BaseDados.TempMinimaHoje))
  {
    Firebase.setString(firebaseData, "HoraTemperaturaMinima", BaseDados.HoraTemperaturaMinima);
    FalhaFirebase(0);
  }
  else
  {
    FalhaFirebase(1);
    ContadorScan = 12;
  }

  // Grava a temperatura DHT
  if (Firebase.setFloat(firebaseData, "TemperaturaDHT", BaseDados.TemperaturaDht))
  {
    FalhaFirebase(0);
  }
  else
  {
    FalhaFirebase(1);
    ContadorScan = 2;
  }
  // Grava a umidade
  if (Firebase.setFloat(firebaseData, "Umidade", BaseDados.Umidade))
  {
    FalhaFirebase(0);
  }
  else
  {
    FalhaFirebase(1);
    ContadorScan = 3;
  }

  // Grava a umidade maxima
  if (Firebase.setFloat(firebaseData, "UmidadeMaximaHoje", BaseDados.UmidadeMaximaHoje))
  {
    Firebase.setString(firebaseData, "HoraUmidadeMaxima", BaseDados.HoraUmidadeMaxima);
    FalhaFirebase(0);
  }
  else
  {
    FalhaFirebase(1);
    ContadorScan = 31;
  }

  // Grava a umidade minima
  if (Firebase.setFloat(firebaseData, "UmidadeMinimaHoje", BaseDados.UmidadeMinimaHoje))
  {
    Firebase.setString(firebaseData, "HoraUmidadeMinima", BaseDados.HoraumidadeMinina);
    FalhaFirebase(0);
  }
  else
  {
    FalhaFirebase(1);
    ContadorScan = 32;
  }

  // Grava as horas do relógio RTC
  if (Firebase.setString(firebaseData, "Horas", datas.horastring))
  {
    FalhaFirebase(0);
  }
  else
  {
    FalhaFirebase(1);
    ContadorScan = 4;
  }

  // Leitura da hora para Irrigar
  if (Firebase.getInt(firebaseData, "HoraIrrigar"))
  {
    if (firebaseData.dataType() == "int")
    {
      int hora = firebaseData.intData();
      if (hora != 0)
      {
        irrigarDados.Hora = hora;
      }
    }
  }
  // Leitura do minuto para Irrigar
  if (Firebase.getInt(firebaseData, "MinutoIrrigar"))
  {
    if (firebaseData.dataType() == "int")
    {
      int minuto = firebaseData.intData();
      if (minuto != 0)
      {
        irrigarDados.Minuto = minuto;
      }
    }
  }

  // Leitura do set point floreira

  if (Firebase.getInt(firebaseData, "SetPointFloreira"))
  {
    if (firebaseData.dataType() == "int")
    {
      int floreira = firebaseData.intData();
      if (floreira != 0)
      {
        irrigarDados.SetPointFloreira = floreira;
      }
    }
  }

  // Leitura do set point tomates

  if (Firebase.getInt(firebaseData, "SetPointTomates"))
  {
    if (firebaseData.dataType() == "int")
    {
      int tomates = firebaseData.intData();
      if (tomates != 0)
      {
        irrigarDados.SetPointTomates = tomates;
      }
    }
  }

  // Leitura do set point Horta

  if (Firebase.getInt(firebaseData, "SetPointHorta"))
  {
    if (firebaseData.dataType() == "int")
    {
      int horta = firebaseData.intData();
      if (horta != 0)
      {
        irrigarDados.SetpointHorta = horta;
      }
    }
  }

  // Leitura se e para irrigar agora
  if (Firebase.getInt(firebaseData, "IrrigaAgora"))
  {
    if (firebaseData.dataType() == "int")
    {
      int agora = firebaseData.intData();
      if (agora != 0)
      {
        IrrigaAgora = agora;
      }
    }
  }

  ContadorScan = 1;
  return ContadorScan;
}