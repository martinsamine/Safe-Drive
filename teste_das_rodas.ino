#include <MotorDriver.h>

#define motorPinA 1
#define motorPinB 2

MotorDriver rodas;

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

void setup() {
  Serial.begin(38400);  // Velocidade de comunicação serial
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read();
      executarComando(comando);
  }
}
