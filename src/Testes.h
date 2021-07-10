#include <Arduino.h>

void FuncaoDeTeste()
{
    if (Temp1000ms.T)
    {
        if (ContaDebug < 60)
        {
            ContaDebug++;
            Serial.print("TempoContador: ");
            Serial.println(ContaDebug);
        }
        else
        {
             double chuva = LerChuva(datas.dia);
             Serial.print("Leitura da Chuva: ");
             Serial.println(chuva);
            //GravaChuvaEprom(0.0); // Verifica no firebase quanto choveu
            ContaDebug = 0;
        }
    }
}