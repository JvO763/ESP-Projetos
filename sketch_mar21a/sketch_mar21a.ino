#include "SoftwareSerial.h"

SoftwareSerial ESP_Serial(10, 11); // TX, RX

String rede = "pao";
String senha = "zubuzulu";
String resposta = "";

const int rele = 2;
int estadoRele = 0;
String botao = "";

void setup() {
  pinMode(rele, OUTPUT);

  Serial.begin(9600);
  ESP_Serial.begin(9600);
  
  delay(1000); //espera de seguranca

  Serial.println("Conectando a rede...");
  String CWJAP = "\"AT+CWJAP=\"";
  CWJAP += rede;
  CWJAP += "\",\"";
  CWJAP += senha;
  CWJAP += "\"";
  sendCommand(CWJAP);
  readResponse(10000);

  delay(2000); //espera de seguranca

  if (resposta.indexOf("OK") == -1) { //procura na resposta se houve OK
    Serial.println("Atencao: Nao foi possivel conectar a rede WiFi.");
    Serial.println("Verifique se o nome da rede e senha foram preenchidos corretamente no codigo e tente novamente.");
  } else {

    Serial.println("Obtendo endereco de IP na rede...");
    sendCommand("AT+CIFSR");
    readResponse(1000);

    Serial.println("Configurando para multiplas conexoes...");
    sendCommand("AT+CIPMUX=1");
    readResponse(1000);

    Serial.println("Ligando servidor...");
    sendCommand("AT+CIPSERVER=1,80");
    readResponse(1000);

    Serial.print("Pronto, acesse o IP atraves de um dispositivo ligado na mesma rede do ESP8266.");
  }
}

void loop() {
  if (ESP_Serial.available()) {
    //.find le os dados vindos da serial ate o alvo, neste caso +IPD,
    if (ESP_Serial.find("+IPD,")) {

      delay(500);
      char id = ESP_Serial.peek();//pega ID da conexao

      //verifica se cliente esta requisitando a pagina /go:
      if (ESP_Serial.find("increment")) {
    estadoRele++;
} else if (ESP_Serial.find("decrement")) {
    estadoRele--;
}
  
 //    if (estadoRele == 0) {
 //       botao = "ON";
 //     } else {
 //       botao = "OFF";
 //     } 

      //nossa pagina web em HTML
      String webpage = String("HTTP/1.1 200 OK\r\n") +
                 "Content-Type: text/html\r\n" +
                 "Connection: close\r\n" +
                 "\r\n" +
                 "<a href=\"increment\" style=\"font-size: 20em\">+</a>" +
                 "<a href=\"decrement\" style=\"font-size: 20em\">-</a>" +
                 "<br><br>" +
                 //"<h1>Carga Atual: " +
                 //String(estadoRele) +
                 "</h1>" +
                 "\r\n";


      String cipSend = "AT+CIPSEND=";
      cipSend += (int(id) - 48);
      cipSend += ",";
      cipSend += webpage.length();
      Serial.println(webpage.length());
      sendCommand(cipSend);
      readResponse(750);

      sendCommand(webpage);
      readResponse(1000);

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += (int(id) - 48);
      sendCommand(closeCommand);
      readResponse(750);
      Serial.println(estadoRele);
    }
  }
}

void sendCommand(String cmd) {
  ESP_Serial.println(cmd);
}

void readResponse(unsigned int timeout) {
  unsigned long timeIn = millis(); //momento que entramos nessa funcao é salvo
  resposta = "";
  while (timeIn + timeout > millis()) {
    if (ESP_Serial.available()) {
      char c = ESP_Serial.read();
      resposta += c;
    }
  }
  //Serial.println(resposta);
}
