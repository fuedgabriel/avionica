#include <iostream>
#include <cstdlib>
#include <LoRa.h>
#include <SoftwareSerial.h> //Biblioteca de comunicação do módulo
#include <EBYTE.h>

#define gy_neo1 20
#define gy_neo2 21
#define MPL1 26
#define MPL2 27
#define BMP1 30
#define BMP2 31
#define lora1 32
#define lora2 33

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

