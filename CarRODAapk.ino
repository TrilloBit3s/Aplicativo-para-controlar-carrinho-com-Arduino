/*
só ródinhas
Dev por "Michael" Trillobit3sGames
trillobit3s@gmail.com - estuartyy@gmail.com 

Carrinho bluetooth Arduino sem slider
primeira atualização 05/02/2017
Ultima atualização 12/11/2024

USE ESTES CARACTERES EM SEU CÓDIGO

F = PARA FRENTE => S = PARADO  
B = PARA ATRÁS => S = PARADO
L = PARA ESQUERDA => S = PARADO
R = PARA DIREITA => S = PARADO

S = PARADO

V = BUZINA => v = buzina desligada
W = LED FRENTE => w = led frente desligado
U = LED TRÁS => u = led trás   desligado 
*/

#include <SoftwareSerial.h>

SoftwareSerial BT(0, 1); // RX, TX 

const int motorA1  = 5;//3
const int motorA2  = 6;//5
const int motorB1  = 9;//6
const int motorB2  = 10;//9

const int ENA = 11;//10
const int ENB = 12;//11

const int BTState = 4;

int vSpeed = 255;
char state = 'S';

void setup() {
  BT.begin(9600);
  Serial.begin(9600);

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(BTState, INPUT);
}

void loop() {
  while (BT.available()) {
    char c = BT.read();
  }

  if (digitalRead(BTState) == LOW) {
    state = 'S'; // Pare se a conexão Bluetooth for perdida
  }

  if (Serial.available() > 0) {
    state = Serial.read();
    updateSpeed(state);
    executeCommand(state);
  }
}

void updateSpeed(char s) {
  switch (s) {
    case '0': vSpeed = 100; break;
    case '4': vSpeed = 140; break;
    case '6': vSpeed = 180; break;
    case '7': vSpeed = 200; break;
    case '8': vSpeed = 240; break;
    case '9': vSpeed = 255; break;
    case 'q': vSpeed = 255; break;
    default: vSpeed = 255; break;
  }
}

void executeCommand(char cmd) {
  switch (cmd) {
    case 'F': andarParaFrente(); break;
    case 'B': andarParaTras(); break;
    case 'L': andarParaEsquerda(); break;
    case 'R': andarParaDireita(); break;
    default: ficarParado(); break;
  }
}

void andarParaFrente() {
  analogWrite(ENA, vSpeed);
  analogWrite(ENB, vSpeed);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void andarParaTras() {
  analogWrite(ENA, vSpeed);
  analogWrite(ENB, vSpeed);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void andarParaDireita() {
  analogWrite(ENA, vSpeed);
  analogWrite(ENB, vSpeed);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void andarParaEsquerda() {
  analogWrite(ENA, vSpeed);
  analogWrite(ENB, vSpeed);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void ficarParado() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}