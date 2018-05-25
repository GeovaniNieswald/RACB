#include <SoftwareSerial.h>                  //Inlcui a biblioteca SoftwareSerial.h

#define RxD  10                              //Define RxD como 10
#define TxD  11                              //Define TxD como 11

SoftwareSerial blueToothSerial(RxD, TxD);    //Instância a biblioteca SoftwareSerial.h

int velocidade = 0;
int velocidadeb = 0;

void setup()
{
  //Configuração dos pinos - Motor 1
  pinMode(2, OUTPUT);         //Pino ENA da PonteH - Pino 2 do arduino
  pinMode(3, OUTPUT);         //Pino IN1 da PonteH - Pino 3(PWM) do arduino
  pinMode(5, OUTPUT);         //Pino IN2 da PonteH - Pino 5(PWM) do arduino

  //Configuração dos pinos - Motor 2
  pinMode(4, OUTPUT);         //Pino ENB da PonteH - Pino 4 do arduino
  pinMode(6, OUTPUT);         //Pino IN3 da PonteH - Pino 6(PWM) do arduino
  pinMode(9, OUTPUT);         //Pino IN4 da PonteH - Pino 9(PWM) do arduino

  parear_dispositivo();       //Executa a função para parear o dispositivo
}

void loop()
{
  char letra;                          //Variável char para armazenar o caractere recebido

  if (blueToothSerial.available())     //Se algo for recebido pela serial do módulo bluetooth
  {
    
    letra = blueToothSerial.read();    //Armazena o caractere recebido na variável letra

    if (letra == '0')
    {
      velocidade = 0;
      velocidadeb = 0;
    }
    if (letra == '1')
    {
      velocidade = 100;
      velocidadeb = 100*0.29;
    }
    if (letra == '2')
    {
      velocidade = 120;
      velocidadeb = 120*0.29;
    }
    if (letra == '3')
    {
      velocidade = 130;
      velocidadeb = 130*0.29;
    }
    if (letra == '4')
    {
      velocidade = 140;
      velocidadeb = 140*0.29;
    }
    if (letra == '5')
    {
      velocidade = 150;
      velocidadeb = 150*0.29;
    }
    if (letra == '6')
    {
      velocidade = 160;
      velocidadeb = 160*0.29;
    }
    if (letra == '7')
    {
      velocidade = 170;
      velocidadeb = 170*0.29;
    }
    if (letra == '8')
    {
      velocidade = 180;
      velocidadeb = 180*0.29;
    }
    if (letra == '9')
    {
      velocidade = 190;
      velocidadeb = 190*0.29;
    }
    if (letra == 'q')
    {
      velocidade = 200;
      velocidadeb = 200*0.29;
    }

    if (letra == 'F')                 //Se o caractere recebido for a letra 'F', move o carrinho para frente
    {
      direcao(2, 5, 3, velocidade);
      direcao(4, 9, 6, velocidade);
    }
    else if (letra == 'B')            //Se o caractere recebido for a letra 'B', move o carrinho para trás
    {
      direcao(2, 3, 5, velocidade);
      direcao(4, 6, 9, velocidade);
    }
    else if (letra == 'R')            //Se o caractere recebido for a letra 'R', move o carrinho para direita
    {
      direcao(4, 9, 6, velocidade);
    }
    else if (letra == 'L')            //Se o caractere recebido for a letra 'L', move o carrinho para esquerda
    {
      direcao(2, 5, 3, velocidade);
    }
    else if (letra == 'S')           //Se o caractere recebido for a letra 'S', para o carrinho
    {
      digitalWrite(2, LOW);          //Desabilita o motor 1
      digitalWrite(4, LOW);          //Desabilita o motor 2
    }
    else if (letra == 'G')            //Se o caractere recebido for a letra 'G', move o carrinho para frente e para esquerda
    {
      direcao(2, 5, 3, velocidade);
      direcao(4, 9, 6, velocidadeb);
    }
    else if (letra == 'I')            //Se o caractere recebido for a letra 'I', move o carrinho para frente e para direita
    {
      direcao(2, 5, 3, velocidadeb);
      direcao(4, 9, 6, velocidade);
    }
    else if (letra == 'H')            //Se o caractere recebido for a letra 'H', move o carrinho para trás e para esquerda
    {
      direcao(2, 3, 5, velocidade);
      direcao(4, 6, 9, velocidadeb);
    }
    else if (letra == 'J')            //Se o caractere recebido for a letra 'J', move o carrinho para trás e para esquerda
    {
      direcao(2, 3, 5, velocidadeb);
      direcao(4, 6, 9, velocidade);
    }
  }
}

void parear_dispositivo()
{
  blueToothSerial.begin(9600);                    //Configura o baud rate do bluetooth como 9600
  blueToothSerial.print("AT");
  delay(400);
  blueToothSerial.print("AT+DEFAULT");            // Restaura configuração de fabrica do Bluetooth
  delay(2000);
  blueToothSerial.print("AT+NAMERobo-Arduino");   // Configura o nome do disopsitivo bluetoothpara "Robo-Arduino", a legenda do bluetooth não pode passar de 12 caracteres
  delay(400);
  blueToothSerial.print("AT+PIN1234");            // Muda o codigo de acesso para "1234"
  delay(400);
  blueToothSerial.print("AT+AUTH1");
  delay(400);
  blueToothSerial.flush();                       // Dá um flush na serial do módulo bluetooth
}

void direcao(int p1, int p2, int p3, int velo)
{
  digitalWrite(p1, HIGH);
  analogWrite(p2, LOW);
  analogWrite(p3, velo);
}
