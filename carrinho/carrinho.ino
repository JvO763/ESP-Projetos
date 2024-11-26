#include <RH_ASK.h>
#include <SPI.h> // Inclua o SPI apenas se você estiver usando Arduino.

RH_ASK driver;

void setup() {
    Serial.begin(115200); // Para depuração.
    if (!driver.init()) {
        Serial.println("Erro na inicialização do driver RF!");
        while (1);
    }
}

void loop() {
    const char *msg = "Comando Carrinho";
    
    // Envie o comando RF.
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    
    delay(1000); // Aguarde 1 segundo entre os comandos.
}
