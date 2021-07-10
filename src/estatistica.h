#include <Arduino.h>

void MaximosEminimos()
{   // Verifica se a temperatura é maior que a maxima
    if (BaseDados.Temperatura > BaseDados.TempMaximaHoje)
    {
        BaseDados.TempMaximaHoje = BaseDados.Temperatura;
        BaseDados.HoraTemperaturaMaxima = datas.horastring;
    }
    // Verifica a umidade maxima
    if (BaseDados.Umidade > BaseDados.UmidadeMaximaHoje){
        BaseDados.UmidadeMaximaHoje =  BaseDados.Umidade;
        BaseDados.HoraUmidadeMaxima = datas.horastring;
    }

    // Verifica se a temperatura for zero.
    if (BaseDados.TempMinimaHoje == 0.0){
        BaseDados.TempMinimaHoje = 100.0;
    }
    //  Verifica se a temperatura é menor que a minima.
    if (BaseDados.Temperatura < BaseDados.TempMinimaHoje && BaseDados.Temperatura > -25.0)
    {
        BaseDados.TempMinimaHoje = BaseDados.Temperatura;
        BaseDados.HoraTemperaturaMinima = datas.horastring;
    }

     // Verifica se a umidade for zero.
    if (BaseDados.UmidadeMinimaHoje == 0.0){
        BaseDados.UmidadeMinimaHoje = 100.0;
    }

     // Verifica a umidade mimima.
    if (BaseDados.Umidade < BaseDados.UmidadeMinimaHoje && BaseDados.Umidade > 0.0){
        BaseDados.UmidadeMinimaHoje = BaseDados.Umidade;
        BaseDados.HoraumidadeMinina = datas.horastring;
    }

    // Verifica o momento de zerar os acumuladores.
    if ((datas.horas != 3) && (datas.minutos != 28) && (datas.dia != DiaDeHoje)){
        AtualizatemperaturaDia(datas.dia,BaseDados.TempMaximaHoje,BaseDados.TempMinimaHoje,BaseDados.Chuva);
        Irrigou = 0;                                // Registra que irrigou hoje
        GravarEprom(Irrigou);                       // Grava na Eprom que irrigou 
        GravarEpromDia(datas.dia);
        AtualizaIrrigou(Irrigou);                   // Atualiza no firebase que irrigou
        DiaDeHoje = datas.dia ; 
        BaseDados.TempMaximaHoje = 0.0;
         BaseDados.UmidadeMaximaHoje = 0.0;
         BaseDados.TempMinimaHoje = 100.0;
         BaseDados.UmidadeMinimaHoje = 100.0;
         MoveChuvaEprom(); // Movimenta a chuva do dia para a chuva do dia anterior
         BaseDados.Chuva = 0.0;
         GravaChuvaEprom(BaseDados.Chuva); // Grava na Eprom quanto choveu
         AtualizaChuva(); // Atualiza a variavel, ou seja zera a variavel chuva do dia.
    }

}