#include <Arduino.h>

Timer Clock(Timer Data, unsigned Intervalo)
{

  unsigned long TempoAtual = millis();

  Timer Temp;

  if (TempoAtual - Data.TempoAnterior >= Intervalo)
  {
    Temp.TempoAnterior = TempoAtual;
    Temp.T = 1;
  }
  else{
    Temp.TempoAnterior = Data.TempoAnterior;
    Temp.T = 0;
  }
  return Temp;
}