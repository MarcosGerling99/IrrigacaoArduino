#include <Arduino.h>

// Funções para gravar a Eeprom

void LerEprom()
{
  byte valor = 0;
  byte dia = 0;
  EEPROM.begin(4);        //Inicia a EEPROM com tamanho de 4 Bytes (minimo).
  valor = EEPROM.read(0); // le se irrigou
  Serial.print("Eprom:     ");
  Serial.println(valor); //Mostra no Monitor oque há antes de efetuar a gravação
  dia = EEPROM.read(1);  // le se irrigou
  Serial.print("Eprom DIA:     ");
  Serial.println(dia); //Mostra no Monitor oque há antes de efetuar a gravação

  if (valor == 0 || valor == 1)
  {
    Irrigou = valor;
  }
  if (dia >= 0 && dia <= 6)
  {
    DiaDeHoje = dia;
  }
  EEPROM.end(); //Fecha a EEPROM.
}

void GravarEprom(byte Grava)
{
  EEPROM.begin(4);        //Inicia a EEPROM com tamanho de 4 Bytes (minimo).
  EEPROM.write(0, Grava); //Escreve no endereço "0", o valor "18".
  EEPROM.commit();        //Salva o dado na EEPROM.
  EEPROM.end();           //Fecha a EEPROM.
  Serial.print("Gravou Eprom");
  Serial.println(Grava);
}

void GravarEpromDia(byte dia)
{
  EEPROM.begin(4);      //Inicia a EEPROM com tamanho de 4 Bytes (minimo).
  EEPROM.write(1, dia); //Escreve no endereço "0", o valor "18".
  EEPROM.commit();      //Salva o dado na EEPROM.
  EEPROM.end();         //Fecha a EEPROM.
  Serial.print("Gravou Dia!");
  Serial.println(dia);
}

void GravaChuvaEprom(double chuva)
{
  byte chuvaByte = 0;
  float chuvaFlutuante = (float)chuva;
  int ChuvaInteiro = round(chuvaFlutuante);
  if (ChuvaInteiro <= 200)
  {
    chuvaByte = ChuvaInteiro;
    EEPROM.begin(4); //Inicia a EEPROM com tamanho de 4 Bytes (minimo).
    EEPROM.write(2, chuvaByte);     //Escreve no endereço "dia mais 10", o valor da chuva.
    EEPROM.commit();                //Salva o dado na EEPROM.
    EEPROM.end();                   //Fecha a EEPROM.
    Serial.print("Gravou Chuva!");
    Serial.println(chuvaByte);
  }
}

void MoveChuvaEprom()
{
  byte chuvaAnterior = 0;
  EEPROM.begin(4); //Inicia a EEPROM com tamanho de 4 Bytes (minimo).
  chuvaAnterior = EEPROM.read(2);
  EEPROM.write(3, chuvaAnterior); //Escreve no endereço "dia mais 10", o valor da chuva.
  EEPROM.commit();                //Salva o dado na EEPROM.
  EEPROM.end();                   //Fecha a EEPROM.
  Serial.print("Moveu Chuva!");
  Serial.println(chuvaAnterior);
}

void LerChuvaEprom()
{
  EEPROM.begin(4); //Inicia a EEPROM com tamanho de 4 Bytes (minimo).

  chuvaHoje = EEPROM.read(2);  // le se irrigou.
  chuvaOntem = EEPROM.read(3); // le se irrigou.
  EEPROM.end();                //Fecha a EEPROM.
  Serial.print("ChuvaHoje");
  Serial.println(chuvaHoje);
  Serial.print("ChuvaOntem");
  Serial.println(chuvaOntem);
  if (chuvaHoje < 200)
  {
    BaseDados.Chuva = chuvaHoje;
  }
  if (chuvaOntem > 200)
  {
    chuvaOntem = 0;
  }
  Serial.print("BaseDados.Chuva:");
  Serial.println(BaseDados.Chuva);
}