/*
Algoritimo para Esp32 DOIT DEVKI V1
Dev por "Michael" Trillobit3sGames
trillobit3s@gmail.com - estuartyy@gmail.com 
primeira versão bluetooth arduino 05/02/2017
Ultima atualização bluetooth Esp32 14/12/2023

USE ESTES CARACTERES EM SEU CÓDIGO

F = PARA FRENTE => S = PARA  
B = PARA TRÁS => S = PARA
L = PARA ESQUERDA => S = PARA
R = PARA DIREITA => S = PARA

S = PARADO

V = BUZINA => v = buzina desligada
W = LED FRENTE => w = led frente desligado
U = LED TRÁS => u = led trás   desligado 
*/

#include "BluetoothSerial.h" //biblioteca bluetooth 

BluetoothSerial SerialBT;

#define LED_Verd_Esq 23 //LED verde 1
#define LED_Verd_Dir 22 //LED verde 2
#define LED_Verm_Esq 21 //LED vermelho 1 
#define LED_Verm_Dir 19 //LED vermelho 2

#define BUZZER 18 //Buzina

const int MR1 = 14; //in1
const int MR2 = 27; //in2
const int ML1 = 26; //in3
const int ML2 = 25; //in4

const int ENA = 13; //ENA
const int ENB = 12; //ENB 

int vSpeed = 255; //Define velocidade padrão 0 a 255.
char receivedChar;  //O valor recebido será armazenado como CHAR nesta variável

void setup() 
{
  //Serial.begin(9600); //monitor usado pelo HC05
  Serial.begin(115200); //Padrão
  SerialBT.begin("Esp32"); //Você pode alterar o nome do seu dispositivo Bluetooth aqui

  pinMode(LED_Verd_Esq, OUTPUT); //indica um sinal de saida led digital
  pinMode(LED_Verd_Dir, OUTPUT); //indica um sinal de saida led digital
  pinMode(LED_Verm_Esq, OUTPUT);
  pinMode(LED_Verm_Dir, OUTPUT);
  
  pinMode(MR1, OUTPUT); //indica um sinal de saida motor digital PWM
  pinMode(MR2, OUTPUT); //indica um sinal de saida motor digital PWM
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
  pinMode(ENA, OUTPUT); //indica um sinal de saida controle velocidade PWM
  pinMode(ENB, OUTPUT); //indica um sinal de saida controle velocidade PWM
    
  pinMode(BUZZER, OUTPUT); //indica um sinal de saida autofalante digital
  noTone(BUZZER);
}  

void loop() 
{
  analogWrite(ENA, 255); //velovidade do motor esquerdo
  analogWrite(ENB, 255); //velovidade do motor direito

  receivedChar =(char)SerialBT.read();

  if (Serial.available()) 
  {
    SerialBT.write(Serial.read());
  }

  if (SerialBT.available()) 
  { 
    Serial.print (" Recebido: "); //imprimir no monitor serial
    Serial.println(receivedChar); //imprimir no monitor serial
    
  if (receivedChar == 'F'){ //FRENTE. 
    andarParaFrente();
  }
  if (receivedChar == 'B'){ //TRÁS. 
    andarParaTras();
  }
  if (receivedChar == 'L'){ //ESQUERDA. 
    andarParaEsquerda();
  }  
  if (receivedChar == 'R'){ //DIREITA.       
    andarParaDireita();
  }
  if (receivedChar == 'F' && receivedChar == 'R'){ //FRENTE DIREITA. 
    frenteDireita();
  }
  if (receivedChar == 'F' && receivedChar == 'L'){ //FRENTE ESQUERDA.
    frenteEsquerda();
  }
  if (receivedChar == 'B' && receivedChar == 'R'){ //TRÁS DIREITA. 
    trasDireita();
  } 
  if (receivedChar == 'B' && receivedChar == 'L'){ //TRÁS ESQUERDA.
    trasEsquerda();
  }
  if (receivedChar == 'W'){ //Farol Frente Ligado
    farolFrenteLigado();
  }
  if (receivedChar == 'w'){ //Farol Frente Desligado
    farolFrenteDesligado();
  }
  if (receivedChar == 'U'){ //Farol Tras Ligado
    farolTrasLigado();
  }
  if (receivedChar == 'u'){ //Farol Tras Desligado
    farolTrasDesligado();
  }
  if (receivedChar == 'V'){ //ligar Buzina
    ligarBuzina();
  }
  if (receivedChar == 'v'){ //Desligar Buzina
    desligarBuzina();
  }

    if(receivedChar == 'S')
    {
      ficarParado();
    }
  }
  delay(20);
}

  void andarParaFrente()
  {
    digitalWrite(MR1, LOW);
    digitalWrite(MR2, HIGH);
    digitalWrite(ML1, HIGH);
    digitalWrite(ML2, LOW);
  }
  void andarParaTras()
  {
    digitalWrite(MR1, HIGH);
    digitalWrite(MR2, LOW);
    digitalWrite(ML1, LOW);
    digitalWrite(ML2, HIGH);
  }
  void andarParaDireita()
  {
    digitalWrite(MR1, HIGH);
    digitalWrite(MR2, LOW);
	  digitalWrite(ML1, HIGH);
    digitalWrite(ML2, LOW);
  }
  void andarParaEsquerda()
  {
    digitalWrite(MR1, LOW);
	  digitalWrite(MR2, HIGH);
    digitalWrite(ML1, LOW);
    digitalWrite(ML2, HIGH);
  }
  void ficarParado()
  {
    digitalWrite(MR1, LOW);
    digitalWrite(MR2, LOW);
    digitalWrite(ML1, LOW);
    digitalWrite(ML2, LOW);
  }
  void trasEsquerda()
  {
    digitalWrite(MR1, HIGH); 
    digitalWrite(MR2, LOW);
    digitalWrite(ML1, 150);    
    digitalWrite(ML2, LOW);  
  }
  void trasDireita()
  {
    digitalWrite(MR1, LOW);   
    digitalWrite(MR2, HIGH);
    digitalWrite(ML1, LOW);   
    digitalWrite(ML2, 150); 
  }
  void frenteEsquerda()
  {
    digitalWrite(MR1, LOW);   
    digitalWrite(MR2, HIGH);
    digitalWrite(ML1, LOW); 
    digitalWrite(ML2, 150); 
  }
  void frenteDireita()
  {
    digitalWrite(MR1, 150); 
    digitalWrite(MR2, LOW);
    digitalWrite(ML1, HIGH);      
    digitalWrite(ML2, LOW);   
  }
  void farolFrenteLigado()
  {
    digitalWrite(LED_Verd_Esq, HIGH);
    digitalWrite(LED_Verd_Dir, HIGH);
  }
  void farolFrenteDesligado()
  {
    digitalWrite(LED_Verd_Esq, LOW);
    digitalWrite(LED_Verd_Dir, LOW); 
  }
  void farolTrasLigado()
  {
    digitalWrite(LED_Verm_Esq, HIGH);
    digitalWrite(LED_Verm_Dir, HIGH);
  }
  void farolTrasDesligado()
  {
    digitalWrite(LED_Verm_Esq, LOW);
    digitalWrite(LED_Verm_Dir, LOW); 
  }
  void ligarBuzina()
  {
    tone(BUZZER, 1000);
  }
  void desligarBuzina()
  {
    noTone(BUZZER);
  }
