#include <SoftwareSerial.h> //Biblioteca de comunicação do módulo
#include <EBYTE.h>          //Biblioteca do Kris

#define M0_LoRa 11
#define M1_LoRa 12
#define RX_LoRa 3 // Vai no TXD do módulo
#define TX_LoRa 2 // Vai no RXD do módulo
#define AUX_LoRa 4

void erro()
{
  if (lora.available() > 0)
  {
    String input = lora.readString();
    if (input == "0")
    {
      Serial.println("Sem erro");
    }
    else if (input == "1")
    {
      Serial.println("Erro no giroscopio e acelerometro");
    }
    else if (input == "2")
    {
      Serial.println("Erro no Stratologger");
      lora.print("100"); //desliga a viônica
    }
    else if (input == "3")
    {
      Serial.println("Erro no GPS");
      lora.print("100"); //desliga a viônica

    }
    else if (input == "4")
    {
      Serial.println("Erro no bmp388");
      Serial.println("Deseja continuar com o lançamento? (s/n)");
      char c = mySerial.read();
      if (c == 's')
      {
        lora.print("101"); //continua com o lançamento
      }
      else
      {
        lora.print("100"); //desliga a viônica
      }
    }
    else if (input == "5")
    {
      Serial.println("Erro no bmp390");
      Serial.println("Deseja continuar com o lançamento? (s/n)");
      char c = mySerial.read();
      if (c == 's')
      {
        lora.print("101"); //continua com o lançamento
      }
      else
      {
        lora.print("100"); //desliga a viônica
      }
    }
    else if (input == "6")
    {
      Serial.println("Erro no mpl");
      Serial.println("Deseja continuar com o lançamento? (s/n)");
      char c = mySerial.read();
      if (c == 's')
      {
        lora.print("101"); //continua com o lançamento
      }
      else
      {
        lora.print("100"); //desliga a viônica
      }
    }
    else
    {
      Serial.println("Erro desconhecido");
      Serial.println(input);
    }
  }
}

void setup()
{

  try
  {
    Serial.begin(9600); // Definir taxa de trabalho em 9600   //Colocar a mesma nos dois
    lora.begin(433E6);
    LoRa.init(); // Inicializa a comunicação e obtem todos os parâmetros do módulo
    // LoRa.Reset();                                       // Reseta parâmetros para os de fábrica

    // Os parametros de comunicação do módulo LoRa já foram setados previamente, então não é necessário setar novamente
    //  LoRa.SetAirDataRate(ADR_1K);                          // Estabelece a taxa de dados de transmissão
    //  LoRa.SetAddress(1);                                   // Estabelece o endereço da rede
    //  LoRa.SetChannel(23);                                  // Estabelece canal como 23
    //  LoRa.SaveParameters(PERMANENTE);                       // Salva todas as definições de forma temporária

    LoRa.PrintParameters();    // Imprime todos os parâmetros (configurações) obtidos do módulo
    LoRa.SetMode(MODE_NORMAL); // Define modo de operação como normal
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what("Módulo lora não funciona") << '\n';
    return 0;
  }

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
  erro()
  erro()
  erro()
  erro()
  erro()
  erro()
}

void loop()
{

  if (lora.available() > 0)
  {
    String input = lora.readString();
    Serial.print(" A Mensagem do Lora é: ");
    Serial.println(input);
  }
  delay(1500);
}