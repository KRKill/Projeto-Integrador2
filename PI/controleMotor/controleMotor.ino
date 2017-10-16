/* Defines */
#define CALIB_ESQ 2.50  // valor lido com joystick esquerdo em repouso
#define CALIB_DIR 2.50  // valor lido com joystick direito em repouso
#define JOY_ESQ   A0    // pino ADC do joystick esquerdo (somente eixo Y / vertical)
#define JOY_DIR   A1    // pino ADC do joystick direito (somente eixo Y / vertical)
#define MOTOR_ESQ_PWM 5 // pino do PWM do motor esquerdo
#define MOTOR_ESQ_DIR 4 // pino de direçao do motor esquerdoo
#define MOTOR_DIR_PWM 3 // pino do PWM do motor esquerdo
#define MOTOR_DIR_DIR 2 // pino de direçao do motor direito
/*---------------------------------------*/

/* Variaveis globais */
int pwmEsq, pwmDir;
/*---------------------------------------*/

/* Inicializa */
void setup() {
  Serial.begin(9600);
  /* Configura pinos de direcao */
  pinMode(MOTOR_ESQ_DIR, OUTPUT);
  pinMode(MOTOR_DIR_DIR, OUTPUT);
}
/*---------------------------------------*/

/* Loop */
void loop() {
  // Le valores nos ADC //
  unsigned int joyEsq = analogRead(JOY_ESQ);
  unsigned int joyDir = analogRead(JOY_DIR);
  
  // Converte valor lido pra um equivalente a tensão lida
  float tensaoEsq = joyEsq * (5.0 / 1023.0);
  float tensaoDir = joyDir * (5.0 / 1023.0);
  
  // Imprime leituras //
  Serial.print("Esquerdo: ");
  Serial.print(tensaoEsq);
  Serial.print("      ");
  Serial.print("Direito: ");
  Serial.print(tensaoDir);
  Serial.println();

  // Controle dos motores //
  if((tensaoEsq - CALIB_ESQ)>=0){
    digitalWrite(MOTOR_ESQ_DIR, LOW);
    //pwmEsq = (tensaoEsq - CALIB_ESQ)*102;
  }
  else{
    digitalWrite(MOTOR_ESQ_DIR, HIGH);
    //pwmEsq = (CALIB_ESQ - tensaoEsq)*102; 
  }
  
  if((tensaoDir - CALIB_DIR)>=0){
    digitalWrite(MOTOR_DIR_DIR, LOW);
    //pwmDir = (tensaoDir - CALIB_DIR)*102;
  }
  else{
    digitalWrite(MOTOR_DIR_DIR, HIGH);
    //pwmDir = (CALIB_DIR - tensaoDir)*102;
  }
  pwmEsq = (tensaoEsq - CALIB_ESQ)*102;
  pwmDir = (tensaoDir - CALIB_DIR)*102;
  analogWrite(MOTOR_ESQ_PWM, pwmEsq);
  analogWrite(MOTOR_DIR_PWM, pwmDir);
}
