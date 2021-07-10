#include <Arduino.h>

void IniciaNtp() {
  delay(2000);
  ntp.begin();//Inicia o NTP.
  ntp.forceUpdate();//Força o Update.
  delay(1000);
}

dataHora HoraNTP(dataHora datas) {

  datas.horastring = ntp.getFormattedTime();//Armazena na váriavel HORA, o horario atual.

  datas.dia = ntp. getDay();  //Dia da semana de 0 a 6, sendo 0 o domingo
  datas.horas = ntp.getHours(); // Pega a hora
  datas.minutos = ntp.getMinutes(); // Pega o minuto
  datas.segundos = ntp.getSeconds(); // Pega o segundo

  switch (datas.dia) { // Converte o numero em dia da semana
    case 0:
      datas.semana = "Domingo";
      break;
    case 1:
      datas.semana = "Segunda";
      break;
    case 2:
      datas.semana = "Terça";
      break;
    case 3:
      datas.semana = "Quarta";
      break;
    case 4:
      datas.semana = "Quinta";
      break;
    case 5:
      datas.semana = "Sexta";
      break;
    case 6:
      datas.semana = "Sábado";
      break;
    default:
      datas.semana = "Nemhum";
      break;
  }

  if (datas.horas == 3 && datas.minutos == 28) {
    IniciaNtp();
  }

  Serial.println(datas.horastring);//Printa a hora já formatada no monitor.
  //Serial.println(datas.semana);//Printa a data já formatada no monitor.

  if (datas.horastring == "10:24:30") //Se a hora atual for igual à que definimos, irá acender o led.
  {
    digitalWrite(led, 0);//Acende
  }
  return datas;
}

