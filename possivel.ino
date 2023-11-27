//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                                                     BIBLIOTECAS
//                                                           - MOTORES
#include <MotorDriver.h>
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                                  DEFINIÇÃO DE PINOS REFERENTE AOS ULTRASÓNICOS
#define trigPin1 53
#define trigPin2 51
#define trigPin3 49
#define trigPin4 47

#define echoPin1 52
#define echoPin2 50
#define echoPin3 48
#define echoPin4 46

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                                      DEFINIÇÃO DE PINOS REFERENTE AOS MOTORES
#define motorPinA 1
#define motorPinB 2
MotorDriver rodas;                  //variavel usada para chamar funcoes do MotorDrive.h

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                   DEFINIÇÃO DE PINOS REFERENTE AOS SENSORES DE VELOCIDADE
#define direitaRPM 42
#define esquerdaRPM 43

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                             DEFINIÇÃO DE FUNÇÕES REFERENTES AO MOVIMENTO DO CARRO
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

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                           FUNÇÕES REFERENTES AOS ULTRASÓNICOS
long measureDistance1 () {
  long duration1, distance1;

  digitalWrite(trigPin1, LOW); // estabiliza sensor
  delayMicroseconds(2);

  digitalWrite(trigPin1, HIGH); // envia um pulso para ativar, mede distancia e desliga
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH); // começa a ler quando é HIGH e quando for LOW pára de medir, isto acontece no pino echoPin e guarda tudo no duration
  distance1 = duration1 / 58; // conversão das casas decimais (tava-mos em metros e segundos mas recebo em centimetros e microsegundos e tenho de dividir por 2 pois o eco é 2 vezes a distancia)

  Serial.print("Distancia medida: ");
  Serial.print(distance1);
  Serial.println("cm: ");

  return distance1;
}

long measureDistance2 () {
  long duration2, distance2;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 / 58;

  Serial.print("Distancia medida: ");
  Serial.print(distance2);
  Serial.println("cm: ");

  return distance2;
}

long measureDistance3 () {
  long duration3, distance3;

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 / 58;

  Serial.print("Distancia medida: ");
  Serial.print(distance3);
  Serial.println("cm: ");

  return distance3;
}

long measureDistance4 () {
  long duration4, distance4;

  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);

  duration4 = pulseIn(echoPin4, HIGH);
  distance4 = duration4 / 58;

  Serial.print("Distancia medida: ");
  Serial.print(distance4);
  Serial.println("cm: ");
  return distance4;
}

void desviar() { // assume o comando caso haj obstaculo a distâncias inferiores a 30cm
  long distancia1 = measureDistance1(); // o da frente
  long distancia2 = measureDistance2(); // o da direita
  long distancia3 = measureDistance3(); // o da esquerda
  long distancia4 = measureDistance4(); // o de trás

  if (distancia4 <= 30)
    parar();
  if (distancia1 <= 30 && distancia2 <= 30 && distancia3 <= 30)
    moverTras();
  if (distancia1 <= 30 && distancia2 <= 30)
    moverEsquerda();
  if (distancia2 <= 30 && distancia3 <= 30)
    moverFrente();
  if (distancia1 <= 30 && distancia3 <= 30)
    moverDireita();
  /*if (distancia1 <= 30 && distancia3 <= 30 && distancia4 <= 30)
    buzzer();*/
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                     FUNÇÕES REFERENTES AOS SENSORES DE VELOCIDADE
void contador() {
  volatile byte pulsos = 0;
  pulsos++;
}

long velocidade1() {
  int rpm1 = 0;
  volatile byte pulsos1;
  unsigned long timeOld1 = 0;
  unsigned int pulsosPorVolta1 = 20; // tem 20 furos a roda
  float pi = 3.14159;
  //float v1 = 0;
  //int  r = 0,011; // raio da roda

  contador();

  if (millis() - timeOld1 >= 250) { // Atualiza contador a cada segundo
    detachInterrupt(0); // Desabilita interrupcao durante o calculo

    rpm1 = (pulsos1 / pulsosPorVolta1) * 60;
    //v1 =((2*pi*rpm1)/60) * r;

    pulsos1 = 0;
    attachInterrupt(0, contador, FALLING); // Habilita interrupcao
    Serial.print("RPM1 atual = ");
    Serial.print(rpm1);
  }
  return rpm1;
}

long velocidade2() {
  int rpm2 = 0;
  volatile byte pulsos2;
  unsigned long timeOld2 = 0;
  unsigned int pulsosPorVolta2 = 20; // tem 20 furos a roda
  float pi = 3.14159;
  //float v2 = 0;
  //int  r = 0,011; // raio da roda

  contador();

  if (millis() - timeOld2 >= 250) { // Atualiza contador a cada segundo
    detachInterrupt(0); // Desabilita interrupcao durante o calculo

    rpm2 = (pulsos2 / pulsosPorVolta2) * 60;
    //v2 =((2*pi*rpm2)/60) * r;

    pulsos2 = 0;
    attachInterrupt(0, contador, FALLING); // Habilita interrupcao
    Serial.print("RPM2 atual = ");
    Serial.print(rpm2);
  }
  return rpm2;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                                    FUNÇÕES REFERENTES AO BLUETHOOTH

char direcao;       // recebe caracter do Serial monitor(usada na funcao do bluetooth)
void moverBluethooth() {

  if (Serial.available()) {            // se houver para ler guarda os dados na variavel direcao
    direcao = Serial.read();
  }


  if (direcao == 'F') { // Caso seja recebido o caracter F, o carro anda para a frente
    moverFrente();
  }
  else if (direcao == 'D') {
    moverDireita();
  }
  else if (direcao == 'E') {
    moverEsquerda();
  }
  else if (direcao == 'T') {
    moverTras();
  }
  else if (direcao == 'P') {
    parar();
  }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                                     VOID SET UP
void setup() {
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //                                                            DEFINIÇÃO DE INPUTS E OUTPUTS REFERENTES AOS ULTRASÓNICOS
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //                                                                  DEFINIÇÃO DE INPUT REFERENTE AOS MOTORES
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //                                                                  DEFINIÇÃO DE INPUT REFERENTE AO SENSOR DE VELOCIDADE
  pinMode(direitaRPM, INPUT);
  pinMode(esquerdaRPM, INPUT);
  attachInterrupt(0, contador, FALLING);


}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                                           VOID LOOP
void loop() {
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //                                                                  CHAMADAS DAS FUNÇÕES REFERENTES AOS ULTRASÓNICOS
  measureDistance1();
  measureDistance2();
  measureDistance3();
  measureDistance4();
  desviar();

  Serial.println("\n ");
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //                                                                   CHAMADA DA FUNÇÃO REFERENTE AOS SENSORES DE VELOCIDADE
  velocidade1();
  velocidade2();

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //                                                                      CHAMADA DA FUNÇÃO REFERENTE AO BLUETHOOTH
  moverBluethooth();
  delay(1000);
}
