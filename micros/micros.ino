#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ESP32Servo.h> // biblioteca específica para o controle de servos no ESP32
#include <Wire.h> // Biblioteca para comunicação I2C
#include <Adafruit_GFX.h> // Biblioteca para gráficos
#include <Adafruit_SSD1306.h> // Biblioteca para controle do display OLED


//!-------  Servo Motor Configurações ------!
#define TASK_IDENTIFICADOR_SERVO "ServoTask"
#define DELAY_UP_SERVO 100 //ms
#define DELAY_ENTRE_SERVO 1000 //ms
#define DELAY_DOWN_SERVO 200 //ms
#define FREQUENCIA_SERVO 50 //Hz
#define REF_POSICIONAMENTO_INICIAL 500 //microsegundos
#define REF_POSICIONAMENTO_FINAL 2500 //microsegundos
#define DIRECAO_POSITIVA 1
#define DIRECAO_NEGATIVA -1
#define ANGULO_INICIAL 0 //graus
#define INCREMENTO 2 //magnitude
#define PIN_SERVO 15
#define PIN_BOTAO 12 // Pino do botão
#define PIN_BOTAO_PARADA 13 // Pino do botão de parada


//!-------  Display OLed Configurações ------!
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void displayServo_update(float angulo, float incremento) {
  display.clearDisplay();                 // Limpa o display
  display.setTextSize(1);                 // Define o tamanho do texto como 1 (pequeno)
  display.setTextColor(SSD1306_WHITE);    // Define a cor do texto como branco
  display.setCursor(0, 0);                // Define a posição do cursor para (0, 0)
  display.println("!-- ServoMotor --!");
  display.println("");        
  display.print("Angulo: ");      
  display.print(angulo);                  
  display.println(" graus");
  display.println("");  
  display.print("Incremento: ");
  display.println(incremento);
  display.println("");  
  if(incremento < 0) display.println("Direcao: Negativa");
  else display.println("Direcao: Positiva");
  display.display();
}


Servo servoMotor;
void taskServoMotor(void * params) {
  Serial.println("Iniciando Task do ServoMotor!");
  servoMotor.setPeriodHertz(FREQUENCIA_SERVO);
  servoMotor.attach(PIN_SERVO, REF_POSICIONAMENTO_INICIAL, REF_POSICIONAMENTO_FINAL);
 
  int angulo = ANGULO_INICIAL;
  int direcao = DIRECAO_POSITIVA;
  servoMotor.write(angulo);


  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();


  // Aguarda o botão ser pressionado
  while(digitalRead(PIN_BOTAO) == HIGH) {
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }


  while (true) {
    angulo += INCREMENTO * direcao;
    servoMotor.write(angulo);
    Serial.print("Angulo: ");
    Serial.println(angulo);


// Verifica se o botão de parada foi pressionado
    if (digitalRead(PIN_BOTAO_PARADA) == HIGH) {
      // Parar o servo
      servoMotor.detach();
      // Desligar o sistema
      vTaskDelete(NULL);
    }


   
    if (angulo >= 180 || angulo <= 0) {
      direcao *= -1;
      Serial.println("Mudando direcao");
      vTaskDelay(DELAY_ENTRE_SERVO / portTICK_PERIOD_MS);
    } else if(direcao == DIRECAO_POSITIVA) {
      vTaskDelay(DELAY_UP_SERVO / portTICK_PERIOD_MS);
    } else if(direcao == DIRECAO_NEGATIVA) {
      vTaskDelay(DELAY_DOWN_SERVO / portTICK_PERIOD_MS);
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Iniciando ESP32");
 
  pinMode(PIN_BOTAO, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up


  // Inicializa a task do servo motor, mas sem executar ainda
  xTaskCreatePinnedToCore(taskServoMotor, TASK_IDENTIFICADOR_SERVO, 2048, NULL, 5, NULL, 0);
}


void loop() {
  // O loop pode ficar vazio ou pode ter outras lógicas
  delay(10);
}
