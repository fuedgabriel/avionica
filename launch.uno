#include <iostream>
#include <cstdlib>
#include <LoRa.h>
#include <SoftwareSerial.h> //Biblioteca de comunicação do módulo
#include <EBYTE.h>
#include <SoftwareSerial.h> //Biblioteca de comunicação do módulo
#include <EBYTE.h>          //Biblioteca do Kris
// pinos do ESP32

#define gy_neo1 20 // GPS
#define gy_neo2 21 // GPS
#define MPL1 26    // altímetro
#define MPL2 27    // altímetro
#define BMP1 30    // altímetro
#define BMP2 31    // altímetro
#define lora1 32   // módulo rf
#define lora2 33   // módulo rf
#define slogger 34 // altímetro (pino com valor fictício)


/*

BMP390 – altímetro, entradas 30 e 31
BMP388 – altímetro, entradas 28 e 29
MPL3115A2-I2C – altímetro, entradas 26 e 27
StratoLogger – altímetro
GY-NEO6MV2 – entradas 20 e 21 ------------
UBBL24-FL-TH -
SX1278 LoRA UART -
bq24074 - radiofrequencia LoRa, entradas 32 e 33

 */

// Tabela de erros
//  0 - Sem erro
//  1 - erro no giroscopio e acelerometro
//  2 - erro no Stratologger
//  3 - erro no GPS
//  4 - erro no bmp388
//  5 - erro no bmp390
//  6 - erro no mpl

// TABELAS DE ERROS - bips
//  1 - Sem erro
//  2 - erro no giroscopio e acelerometro
//  3 - erro no Stratologger
//  4 - erro no GPS
//  5 - erro no bmp388
//  6 - erro no bmp390
//  7 - erro no mpl
//  8 - erro no LoRa


// Função para emitir um bip
void beep(int quantidade, int tempo ) {

    for (int i = 0; i < quantidade; i++) {

        tone(32, 330, 1);
        pinmode(32, OUTPUT);
        delay(tempo);
        noTone(32);

    }

}


setup() {

    try {

        LoRa.init(); // Inicializa a comunicação e obtem todos os parâmetros do módulo

        // LoRa.Reset();                                       // Reseta parâmetros para os de fábrica
        LoRa.SetAirDataRate(ADR_1K);    // Estabelece a taxa de dados de transmissão
        LoRa.SetAddress(1);             // Estabelece o endereço da rede
        LoRa.SetChannel(23);            // Estabelece canal como 23
        LoRa.SaveParameters(TEMPORARY); // Salva todas as definições de forma temporária

        LoRa.PrintParameters(); // Imprime todos os parâmetros (configurações) obtidos do módulo
        LoRa.SetMode(MODE_NORMAL);

    }

    catch (const std::exception &e) {
        
        std::cerr << e.what("Modulo lora não funciona") << '\n';
        return 0;

    }
    
}

void loop()
{
}
