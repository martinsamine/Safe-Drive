#include <MotorDriver.h>

#define motorPinA 1
#define motorPinB 2

#define direitaRPM 42
#define esquerdaRPM 43

MotorDriver rodas;

  int rpm1 = 0;
  volatile byte pulsos1;
  unsigned long timeOld1 = 0;
  int rpm2 = 0;
  volatile byte pulsos2;
  unsigned long timeOld2 = 0;
  unsigned int pulsosPorVolta = 20; // tem 20 furos a rodafloat pi = 3.14159;
  float v1 = 0;
  float  r = 0.011; // raio da roda

void moverFrente() { //colocar int velocidade
  rodas.motor(motorPinA, FORWARD, 190);       //mete o motor da direita a andar para a frente a uma velocidade de 190
  rodas.motor(motorPinB, FORWARD, 190);      //mete o motor da esquerda a andar para a frente a uma velocidade de 190
}

void moverTras() {
  rodas.motor(motorPinA, BACKWARD, 190);
  rodas.motor(motorPinB, BACKWARD, 190);
}

void moverDireita() {
  rodas.motor(motorPinA, FORWARD, 190);
  rodas.motor(motorPinB, BRAKE, 0);
}

void moverEsquerda() {
  rodas.motor(motorPinB, FORWARD, 190);
  rodas.motor(motorPinA, BRAKE, 0);
}

void parar() {
  rodas.motor(motorPinA, BRAKE, 0);
  rodas.motor(motorPinB, BRAKE, 0);
}

void executarComando(char comando) {
  switch (comando) {
    case 'F':
      moverFrente();
      break;
    case 'T':
      moverTras();
      break;
    case 'D':
      moverDireita();
      break;
    case 'E':
      moverEsquerda();
      break;
    case 'P':
      parar();
      break;
    default:
      // Comando inválido
      break;
  }
}
void contador1() {
  pulsos1++;
}

void contador2() {
  pulsos2++;
}

long velocidade1() {
  contador1();

  if (millis() - timeOld1 >= 250) { // Atualiza contador a cada segundo
    detachInterrupt(0); // Desabilita interrupcao durante o calculo

    rpm1 = (pulsos1 / pulsosPorVolta) * 60;
    //v1 =((2*pi*rpm1)/60) * r;

    pulsos1 = 0;
//    timeold1 += 1000;
//    attachInterrupt(0, contador, FALLING); // Habilita interrupcao
      attachInterrupt(digitalPinToInterrupt(direitaRPM), contador1, FALLING);

    Serial.print("RPM1 atual = ");
    Serial.print(rpm1);
  }
  return rpm1;
}

long velocidade2() {
   contador2();

  if (millis() - timeOld2 >= 1000) { // Atualiza contador a cada segundo
    detachInterrupt(0); // Desabilita interrupcao durante o calculo

    rpm2 = (pulsos2 / pulsosPorVolta) * 60;
    //v2 =((2*pi*rpm2)/60) * r;

    pulsos2 = 0;
//timeold2 += 1000;
  //  attachInterrupt(0, contador, FALLING); // Habilita interrupcaO
      attachInterrupt(digitalPinToInterrupt(esquerdaRPM), contador2, FALLING);

   
    Serial.print("RPM2 atual = ");
    Serial.print(rpm2);
  }
  return rpm2;
}



void setup() {
  Serial.begin(38400);  // Velocidade de comunicação serial
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);

  /*attachInterrupt(0, contador, FALLING);
  pulsos = 0;
  rpm = 0;
  timeold = 0;*/
  
  /*pinMode(direitaRPM, INPUT);
  pinMode(esquerdaRPM, INPUT);*/
 // attachInterrupt(digitalPinToInterrupt(direitaRPM), contador1, FALLING);
 // attachInterrupt(digitalPinToInterrupt(esquerdaRPM), contador2, FALLING);
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read();
      executarComando(comando);
  }
  int V1=velocidade1();
  Serial.print("\n");
  delay(250);
  
  int V2 = velocidade2();
  Serial.print("\n");
  delay(250);

  }
