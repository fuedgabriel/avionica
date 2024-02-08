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
void beep(int quantidade) {

    for (int i = 0; i < quantidade; i++) {

        tone(15, 330, 1000); // Emite um bip 
        delay(1);
        noTone(15); 
    }
    

}


setup() {
    
    pinmode(15, OUTPUT);
    
    try { // tentativa, caso não funcione saberemos por aviso

        LoRa.init(); // Inicializa a comunicação e obtem todos os parâmetros do módulo

        // LoRa.Reset();                                       // Reseta parâmetros para os de fábrica
        // LoRa.SetAirDataRate(ADR_1K);    // Estabelece a taxa de dados de transmissão
        // LoRa.SetAddress(1);             // Estabelece o endereço da rede
        // LoRa.SetChannel(23);            // Estabelece canal como 23
        // LoRa.SaveParameters(PERMANENTE); // Salva todas as definições de forma temporária
        LoRa.PrintParameters(); // Imprime todos os parâmetros (configurações) obtidos do módulo
        LoRa.SetMode(MODE_NORMAL);
        
    }

    catch (const std::exception &e) {
        beep(8); // avisa o erro
    }
    
}

void tom(char pino, int freq, int per); // pino frequência e período

void setup() {

    pinMode(20, OUTPUT);

}

void loop() {

    delay(1000);
    int tempo = 400;
    tone();
    
}
 

    
