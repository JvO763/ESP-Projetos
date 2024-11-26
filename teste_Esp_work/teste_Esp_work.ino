//#include <TB6612_ESP32.h>
//
//// *** Wiring connections from ESP32 to TB6612FNG Motor Controller ***
//
//#define AIN1 4  // ESP32 Pin D13 to TB6612FNG Pin AIN1
//#define BIN1 27 // ESP32 Pin D12 to TB6612FNG Pin BIN1
//#define AIN2 2  // ESP32 Pin D14 to TB6612FNG Pin AIN2
//#define BIN2 32 // ESP32 Pin D27 to TB6612FNG Pin BIN2
//#define PWMA 26 // ESP32 Pin D26 to TB6612FNG Pin PWMA
//#define PWMB 25 // ESP32 Pin D25 to TB6612FNG Pin PWMB
//#define STBY 33 // ESP32 Pin D33 to TB6612FNG Pin STBY
//
//// *** Encoder pin definitions ***
//#define ENCODER1_PIN_A 14 // Encoder 1 pin A
//#define ENCODER1_PIN_B 15 // Encoder 1 pin B
//#define ENCODER2_PIN_A 18 // Encoder 2 pin A
//#define ENCODER2_PIN_B 19 // Encoder 2 pin B
//
//// these constants are used to allow you to make your motor configuration
//// line up with function names like forward.  Value can be 1 or -1
//const int offsetA = 1;
//const int offsetB = 1;
//
//Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY, 5000, 8, 1);
//Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY, 5000, 8, 2);
//
//void setup() {
//    Serial.begin(115200); // Inicializa o monitor serial
//    pinMode(ENCODER1_PIN_A, INPUT);
//    pinMode(ENCODER1_PIN_B, INPUT);
//    pinMode(ENCODER2_PIN_A, INPUT);
//    pinMode(ENCODER2_PIN_B, INPUT);
//}
//
//void loop() {
//    // Leitura das entradas dos encoders
//    int encoder1_A_value = digitalRead(ENCODER1_PIN_A);
//    int encoder1_B_value = digitalRead(ENCODER1_PIN_B);
//    int encoder2_A_value = digitalRead(ENCODER2_PIN_A);
//    int encoder2_B_value = digitalRead(ENCODER2_PIN_B);
//
//    // Cálculo das diferenças
//    int diff_encoder1 = encoder1_A_value - encoder1_B_value;
//    int diff_encoder2 = encoder2_A_value - encoder2_B_value;
//
//    // Imprime as diferenças no monitor serial
//    Serial.print("Diferença Encoder 1: ");
//    Serial.println(diff_encoder1);
//    Serial.print("Diferença Encoder 2: ");
//    Serial.println(diff_encoder2);
//
//    delay(1000); // Delay de 1 segundo entre leituras para evitar overflow no monitor serial
//
//    // Seu código original para controle dos motores
//    delay(5000);
//
//    motor1.drive(255, 5000);  // Turn Motor 1 for 5 seconds at full speed
//    motor1.brake();
//    delay(5000);
//
//    motor2.drive(255, 5000);  // Turn Motor 2 for 5 seconds at full speed
//    motor2.brake();
//    delay(5000);
//
//    forward(motor1, motor2, 255); // Forward Motor 1 and Motor 2 for 1 second at full speed
//    delay(1000);
//
//    brake(motor1, motor2); // Stop Motor 1 and Motor 2 for 2 seconds
//    delay(5000);
//
//    back(motor1, motor2, -255); // Reverse Motor 1 and Motor 2 for 1 second at full speed
//    delay(1000);
//
//    brake(motor1, motor2); // Stop Motor 1 and Motor 2 for 2 seconds
//    delay(5000);
//
//    left(motor1, motor2, 255);
//    delay(5000);
//    brake(motor1, motor2);
//    delay(1000);
//    right(motor1, motor2, 255);
//    delay(5000);
//
//    brake(motor1, motor2); // Stop Motor 1 and Motor 2 for 2 seconds
//    delay(5000);
//}


#include <TB6612_ESP32.h>

// *** Wiring connections from ESP32 to TB6612FNG Motor Controller ***

#define AIN1 4  // ESP32 Pin D13 to TB6612FNG Pin AIN1
#define BIN1 27 // ESP32 Pin D12 to TB6612FNG Pin BIN1
#define AIN2 2  // ESP32 Pin D14 to TB6612FNG Pin AIN2
#define BIN2 32 // ESP32 Pin D27 to TB6612FNG Pin BIN2
#define PWMA 26 // ESP32 Pin D26 to TB6612FNG Pin PWMA
#define PWMB 25 // ESP32 Pin D25 to TB6612FNG Pin PWMB
#define STBY 33 // ESP32 Pin D33 to TB6612FNG Pin STBY

// *** Encoder pin definitions ***
#define ENCODER1_PIN_A 14 // Encoder 1 pin A
#define ENCODER1_PIN_B 15 // Encoder 1 pin B
#define ENCODER2_PIN_A 18 // Encoder 2 pin A
#define ENCODER2_PIN_B 19 // Encoder 2 pin B

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY, 5000, 8, 1);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY, 5000, 8, 2);

void setup() {
    Serial.begin(115200); // Inicializa o monitor serial
    pinMode(ENCODER1_PIN_A, INPUT);
    pinMode(ENCODER1_PIN_B, INPUT);
    pinMode(ENCODER2_PIN_A, INPUT);
    pinMode(ENCODER2_PIN_B, INPUT);
}

void loop() {
    // Controla os motores e lê os encoders ao mesmo tempo
    motor1.drive(255);  // Liga Motor 1 a 255 de velocidade
    motor2.drive(255);  // Liga Motor 2 a 255 de velocidade

    unsigned long startTime = millis(); // Guarda o tempo de início
    while (millis() - startTime < 5000) {  // Loop de 5 segundos para controlar motores
        // Leitura das entradas dos encoders
        int encoder1_A_value = digitalRead(ENCODER1_PIN_A);
        int encoder1_B_value = digitalRead(ENCODER1_PIN_B);
        int encoder2_A_value = digitalRead(ENCODER2_PIN_A);
        int encoder2_B_value = digitalRead(ENCODER2_PIN_B);

        // Cálculo das diferenças
        int diff_encoder1 = encoder1_A_value - encoder1_B_value;
        int diff_encoder2 = encoder2_A_value - encoder2_B_value;

        // Imprime as diferenças no monitor serial
        Serial.print("Diferença Encoder 1: ");
        Serial.println(diff_encoder1);
        Serial.print("Diferença Encoder 2: ");
        Serial.println(diff_encoder2);

        delay(100);  // Pequeno delay para suavizar a leitura do serial
    }

    // Para os motores
    motor1.brake();
    motor2.brake();
    delay(1000);  // Espera 1 segundo antes de repetir o loop

    // Outras operações de controle de motor podem ser adicionadas aqui da mesma maneira,
    // garantindo que as leituras do encoder sejam feitas enquanto os motores estão se movendo.
}
