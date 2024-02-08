#include <iostream>
#include <cstdlib>
#include <LoRa.h>
#include <SoftwareSerial.h> //Biblioteca de comunicação do módulo
#include <EBYTE.h>
#include <SoftwareSerial.h> //Biblioteca de comunicação do módulo
#include <EBYTE.h>          //Biblioteca do Kris
#include <TinyGPS++.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
// pinos do ESP32

#define gy_neo1 20  // GPS
#define gy_neo2 21  // GPS
#define MPL1 26     // altímetro
#define MPL2 27     // altímetro
#define BMP9_1 28   // altímetro BMP390
#define BMP9_2 29   // altímetro BMP390
#define BMP8_1 30   // altímetro BMP388
#define BMP8_2 31   // altímetro BMP388
#define lora1 32    // módulo rf
#define lora2 33    // módulo rf
#define stlogger 34 // altímetro (pino com valor fictício)
Adafruit_MPU6050 mpu;

int GPSBaud = 9600;

// CRIANDO UM O BJETO PARA COMUNICAR COM A BIBLIOTECA
TinyGPSPlus gps;

// CRIANDO UMA PORTA SERIAL gpsSerial PARA CONVERSAR COM MÓDULO
SoftwareSerial gpsSerial(RXPin, TXPin);

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
//  9 - sinal não encontrado no GPS

// Função para emitir um bip
void beep(int quantidade)
{

    for (int i = 0; i < quantidade; i++)
    {

        tone(15, 330, 1000); // Emite um bip
        delay(1);
        noTone(15);
    }
}

void operador(){
    while (true){
                    if (lora.available() > 0)
                    {
                        String input = lora.readString();
                        if(input == "101"){
                            break; //prossegue a execução se o operador apertar quiser continuar
                        }else if (input == "100")
                        {
                            close();
                        }
                    }
                    delay(1500);
                    beep(5);

            }
}

setup()
{

    pinmode(15, OUTPUT); // speaker

    // lora
    try
    { // tentativa, caso não funcione saberemos por aviso

        LoRa.init(); // Inicializa a comunicação e obtem todos os parâmetros do módulo

        // LoRa.Reset();                                       // Reseta parâmetros para os de fábrica
        // LoRa.SetAirDataRate(ADR_1K);    // Estabelece a taxa de dados de transmissão
        // LoRa.SetAddress(1);             // Estabelece o endereço da rede
        // LoRa.SetChannel(23);            // Estabelece canal como 23
        // LoRa.SaveParameters(PERMANENTE); // Salva todas as definições de forma temporária
        LoRa.PrintParameters(); // Imprime todos os parâmetros (configurações) obtidos do módulo
        LoRa.SetMode(MODE_NORMAL);
        if (Lora.begin(433E6))
        {
            lora.print("0") // conectado com sucesso
        }
        else
        {
            while (true)
            {
                // erro no lora
                beep(8);
                delay(10);
                Lora.begin(433E6)
            }
        }
    }
    catch (const std::exception &e)
    {
        beep(8); // err
        close(); // encerra o programa
    }

    // gps
    try
    {
        gpsSerial.begin(GPSBaud); // inicia gps
        if (gps.encode(gpsSerial.read()))
        {
            {
                Serial.println("Sinal GPS detectado");
                lora.print("0")
            }
            else
            {
                beep(9);        // sinal não detectado
                lora.print("3") // envia para o lora erro no gps

                while (true){
                    if (lora.available() > 0)
                    {
                        String input = lora.readString();
                        if(input == "100"){
                            break; //Desliga o loop
                        }
                    }
                    delay(1500);
                    Serial.println("Sinal GPS não detectado");
                    beep(9);

                }
            }
        }
        // Verifica se o GPS está funcionando
        if (millis() > 5000 && gps.charsProcessed() < 10) 
        {
            if (lora.available() > 0)
            {
                String input = lora.readString();
                Serial.print(" A Mensagem do Lora é: ");
                Serial.println(input);
            }
            delay(1500);
            Serial.println("Sinal GPS não detectado");
            beep(9);
        }
    }
    catch (const std::exception &e)
    {
        beep(4);        // erro no gps
        lora.print("3") // envia para o lora erro no gps
            close();    // encerra o programa
    }

    // bmp388
    try
    {
        if (!bmp.begin_I2C(0x77)) // diferencia o bmp388 do bmp390
        {
            Serial.println("Não foi possível encontrar o sensor BMP388");
            beep(5);        // erro no bmp388
            lora.print("4") // envia para o lora erro no bmp388
            operador
        }
    }
    catch (const std::exception &e)
    {
        beep(5);        // erro no bmp388
        lora.print("4") // envia para o lora erro no bmp388
        operador();
    }

    // bmp390
    try
    {
        if (!bmp.begin_I2C(0x76)) // diferencia o bmp388 do bmp390
        {
            Serial.println("Não foi possível encontrar o sensor BMP390");
            beep(6);        // erro no bmp390
            lora.print("5") // envia para o lora erro no bmp390
            operador();
        }
        lora.print("0") // conectado com sucesso
    }
    catch (const std::exception &e)
    {
        beep(6);        // erro no bmp390
        lora.print("5") // envia para o lora erro no bmp390
        operador();
    }

    // mpl
    try
    {
        if (!mpl.begin(0x60))
        {
            Serial.println("Não foi possível encontrar o sensor MPL");
            beep(7);        // erro no mpl
            lora.print("6") // envia para o lora erro no mpl
            operador();
        }
        lora.print("0") // conectado com sucesso
    }
    catch (const std::exception &e)
    {
        beep(7);        // erro no mpl
        lora.print("6") // envia para o lora erro no mpl
        operador();
    }

    // mpu 6050
    try
    {
        if (!mpu.begin())
        {
            Serial.println("Não foi possível encontrar o sensor MPU6050");
            beep(2);        // erro no giroscopio e acelerometro
            lora.print("1") // envia para o lora erro no giroscopio e acelerometro
            operador();
        }
    }
    catch (const std::exception &e)
    {
        operador();
        beep(2);        // erro no giroscopio e acelerometro
        lora.print("1") // envia para o lora erro no giroscopio e acelerometro
    }
}

loop()
{
    // gps
    if (gpsSerial.available())
    {
        gps.encode(gpsSerial.read());
    }

    // lora
    if (LoRa.available())
    {
        Serial.println(LoRa.readString());
    }
}

float apogeu = 0; // contador
float altitude = 0;

void loop() {

    apogeu = altitude;

    altitude = stlogger.readAltitude();

    lora.print(altitude); // envia para o lora a altitude
    

    if (altitude < apogeu) {

        while (true) {
            
            if (apogeu >= 409 && apogeu <= 230) { //A altura do apogeu ocorre no intervalo fechado de 409m e 230m?

                abrirDrogue();

                altitude = stlogger.readAltitude();
            
                if ((apogeu - altitude) <= 5) { // quando a distância entre o apogeu e a altitude atual for +- 5m
                
                    abrirMain();

                }
        
            } else if (apogeu < 230 && apogeu > 40) { // A altura do apogeu ocorre no intervalo aberto de 230m e 40m?

                abrirDrogue(); // abrir os dois paraquedas juntos
                abrirMain();

            } else if (apogeu <= 40) { // A altura do apogeu ocorre igual ou abaixo de 40m?

                altitude = stlogger.readAltitude(); // o apogeu não abre

            } else {

                abrirDrogue();

                if (altitude >= 410) {

                    abrirMain();

                }

            }
            
        }

    }
