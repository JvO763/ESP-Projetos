const int pin32 = 32;  // Porta de controle para direção 1
const int pin33 = 33;  // Porta de controle para direção 2

void setup() {
    Serial.begin(115200);  // Inicializa a comunicação serial

    pinMode(pin32, OUTPUT);  // Define o pino 32 como saída
    pinMode(pin33, OUTPUT);  // Define o pino 33 como saída
}

void loop() {
    // Verifica se há dados disponíveis no terminal
    if (Serial.available() > 0) {
        char command = Serial.read();  // Lê o comando recebido

        if (command == '1') {
            // Gira os motores no sentido horário por 2 segundos
            rotateClockwise();
            Serial.println("Motores girando no sentido horário por 2 segundos.");
        } else if (command == '2') {
            // Gira os motores no sentido anti-horário por 2 segundos
            rotateCounterClockwise();
            Serial.println("Motores girando no sentido anti-horário por 2 segundos.");
        }
    }
}

// Função para girar os motores no sentido horário por 2 segundos
void rotateClockwise() {
    digitalWrite(pin32, HIGH);  // Define o pino 32 como HIGH
    digitalWrite(pin33, LOW);   // Define o pino 33 como LOW
    delay(2000);  // Aguarda 2 segundos
    stopMotors(); // Para os motores após 2 segundos
}

// Função para girar os motores no sentido anti-horário por 2 segundos
void rotateCounterClockwise() {
    digitalWrite(pin32, LOW);   // Define o pino 32 como LOW
    digitalWrite(pin33, HIGH);  // Define o pi  no 33 como HIGH
    delay(2000);  // Aguarda 2 segundos
    stopMotors(); // Para os motores após 2 segundos
}

// Função para parar os motores
void stopMotors() {
    digitalWrite(pin32, LOW);   // Define o pino 32 como LOW
    digitalWrite(pin33, LOW);   // Define o pino 33 como LOW
}
