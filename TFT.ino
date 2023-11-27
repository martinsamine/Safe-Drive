//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                                                     BIBLIOTECAS
#include "TFT.h"
#include "SPI.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                           DEFINIÇÃO DE PINOS REFERENTE AOS TFT´S
#define dc1 8
#define cs1 10
#define rst1 9

TFT TFTscreen1 = TFT (cs1, dc1, rst1);

#define dc2 8
#define cs2 10
#define rst2 9

TFT TFTscreen2 = TFT (cs2, dc2, rst2);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                                    FUNÇÕES REFERENTES AO TFT
void tft1() {
  TFTscreen1.background(100, 0, 100); // Define a cor de fundo
  TFTscreen1.stroke(255, 0, 255); // Define a cor das letras para preto
  TFTscreen1.setTextSize(2); // Aumenta o tamanho da letra

  TFTscreen1.text("Humidade", 10, 10); // Exibe o texto "Humidade" em uma posição específica
  TFTscreen1.text("Temperatura Ambiente", 10, 30); 
  TFTscreen1.text("Velocidade do Carro", 10, 50);
  
}

void tft2() {
  TFTscreen2.background(0, 100, 100);
  TFTscreen2.stroke(0, 255, 255);
  TFTscreen2.setTextSize(2);

  TFTscreen2.text("Batimento Cardiaco", 10, 10);
  TFTscreen2.text("Oxigenação Sanguinea", 10, 30);
  TFTscreen2.text("Temperatura Corporal", 10, 50);
}

void setup() {
  Serial.begin(9600); //velocidade de saida de dados

  TFTscreen1.begin();
  TFTscreen1.background(0, 0, 0);

  TFTscreen2.begin();
  TFTscreen2.background(0, 0, 0);
}
                                                                                
void loop() {
  tft1();
  tft2();
  delay(1000);
}
