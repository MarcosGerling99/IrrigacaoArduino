#include <Arduino.h>

// FUNÇÃO PARA LEITURA DA CHUVA
double SensorBascula(bool entradaSensor, double chuva) {
    double calcularChuva = chuva;
  if (!entradaSensor && pulsoSensor) {
    calcularChuva = calcularChuva  + 0.250;  // Leitura a cada 0,25 mm (4 pulso = 1 mm precipitação).
    pulsoSensor = entradaSensor;
    tempoChuva = 100 + millis(); // Atrasa a rotina para formar um delay do pulso do reed
    Choveu = true; // Sinaliza que precisa atualizar a chuva atual.
    Serial.print("Calculou!");
    Serial.println(calcularChuva);
  }
  else {
    pulsoSensor = entradaSensor;
    tempoChuva = 50 + millis(); // Atrasa a rotina para formar um delay do sinal lido
  }
  return calcularChuva;
}

// função para a leitura do sensor de temperatura e umidade.

