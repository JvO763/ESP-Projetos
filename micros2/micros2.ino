// Porta de cada LED
uint8_t ledR = 13;
uint8_t ledG = 12;
uint8_t ledB = 14;


const boolean invert = false;  // true para anodo comum, false para catodo comum


uint8_t color = 0;        
uint32_t R, G, B;          
uint8_t brightness = 255;  // 255 é o máximo de brilho


// setup
void setup() {
  Serial.begin(115200);     //Iniciando monitor serial na frequência correta para a ESP32
  delay(10);


  // Inicializa os pinos
  ledcAttach(ledR, 5000, 8);  // 5 kHz PWM, 8-bit de resolução
  ledcAttach(ledG, 5000, 8);  // 5 kHz PWM, 8-bit de resolução
  ledcAttach(ledB, 5000, 8);  // 5 kHz PWM, 8-bit de resolução
}


// loop
void loop() {
  int incremento;           //declarando a variável incremento
 
  Serial.println("Desligando..."); //Indicação para o usuário de que os LED's serão desligados
  ledcWrite(ledR, 0);              //Desligando o LED vermelho
  ledcWrite(ledG, 0);              //Desligando o LED verde
  ledcWrite(ledB, 0);              //Desligando o LED azul
  delay(2000);                     //Aguarda 2 segundos antes de prosseguir
 
Serial.println("digite um valor: "); //Pede o incremento para o usuário
  incremento=0;                      //Zera o incremento
  while(incremento==0){              //Fica nesse loop até que o novo incremento seja digitado


  incremento = Serial.parseInt();    //Recebe de fato o novo valor do incremento do usuário
  R=0;                               //Variáveis criadas para a lógica pedida no projeto
  G=0;
  B=0;
  }
 
  Serial.println("Ligando LEDS");    //Avisando o usuário de que os LED's ligarão
  for(int i=0;i<=255;i=i+incremento){//laço for, até i alcançar o valor de 255, com o incremento sendo somado a cada iteração
     //Lógica do PWM para cada cor
    R = R + 2*incremento;          
    G = G + incremento;
    B = B + 3*incremento;


    //Ligando os LED's com os valores de PWM calculados acima
    ledcWrite(ledR, R);
    ledcWrite(ledG, G);
    ledcWrite(ledB, B);


    delay(500);  // aguarda meio segundo até o próximo incremento
    //Serial.println(i);
  }


  Serial.println("Finalizado"); //Identificando o fim do laço for
 
 
}
