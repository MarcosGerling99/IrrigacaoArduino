#include <Arduino.h>

void Irriga()
{

    if (Temp1000ms.T)
    {
        if ((datas.horas >= irrigarDados.Hora) && (datas.minutos >= irrigarDados.Minuto) && (datas.horas != 0) && (irrigarDados.Hora != 0) && (Irrigou == 0) && !IrrigacaoStart)
        {
            if (BaseDados.Chuva == 0.0) // LerChuva(datas.dia)
            {
                    LerChuvaEprom(); // Verifica na eprom se não choveu no dia e no dia anterior.
                if ((BaseDados.Chuva < 1.0) && (chuvaOntem < 4))
                {
                    IrrigacaoStart = true; // Inicia o processo de irrigação
                }
            }
            else if (BaseDados.Chuva < 1.0)
            {
               IrrigacaoStart = true; // Inicia o processo de irrigação
            }
            else{
                Irrigou = 1; // Registra que irrigou
                GravarEprom(Irrigou);      // Grava na Eprom que irrigou
            }
        }

        if (IrrigaAgora == 1 && !IrrigacaoStart)
        {
            IrrigacaoStart = true; // Inicia o processo de irrigação
        }

        // Irriga a floreira.
        if ((irrigarDados.floreita < irrigarDados.SetPointFloreira) && (irrigarDados.SetPointFloreira != 0) && IrrigacaoStart)
        {
            digitalWrite(Floreira, HIGH); // Liga floreira
            irrigarDados.floreita++;
            Serial.print("IrrigaFloreira:::");
            Serial.println(irrigarDados.floreita);
        }
        else
        {
            digitalWrite(Floreira, LOW); // Desliga floreira
        }

        if ((irrigarDados.tomates < irrigarDados.SetPointTomates) && (irrigarDados.SetPointTomates != 0) && IrrigacaoStart)
        {
            digitalWrite(Tomates, HIGH); // Liga Tomates
            irrigarDados.tomates++;
            Serial.print("IrrigaTomates:::");
            Serial.println(irrigarDados.tomates);
        }
        else
        {
            digitalWrite(Tomates, LOW); // Desliga Tomates
            if ((irrigarDados.horta < irrigarDados.SetpointHorta) && (irrigarDados.SetpointHorta != 0) && IrrigacaoStart)
            {
                digitalWrite(Horta, HIGH); // Liga Horta
                irrigarDados.horta++;
                Serial.print("IrrigaHorta:::");
                Serial.println(irrigarDados.horta);
            }
            else
            {
                if (IrrigacaoStart)
                {
                    digitalWrite(Horta, LOW);                   // Desliga Horta
                    irrigarDados.DiaSemanaIrrigado = datas.dia; // trava a irrigação o dia
                    IrrigaAgora = 0;
                    irrigarDados.floreita = 0; // zera a contagem.
                    irrigarDados.tomates = 0;  // zera a contagem.
                    irrigarDados.horta = 0;    // zera a contagem.
                    Irrigou = 1;               // Registra que irrigou hoje
                    IrrigacaoStart = false;    // Libera o processo.
                    GravarEprom(Irrigou);      // Grava na Eprom que irrigou
                    AtualizaIrrigou(Irrigou);  // Atualzia na nuvem que irrigou.
                }
            }
        }
    }
}