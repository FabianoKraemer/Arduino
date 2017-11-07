//Programa : Motor shield com sensor TCRT5000
//Adaptacoes : FILIPEFLOP
//
//Baseado no programa original de Michael McRoberts

#include <AFMotor.h>

AF_DCMotor motor_esq(1); //Seleciona o motor 1
AF_DCMotor motor_dir(2); //Seleciona o motor 4

int SENSOR1, SENSOR2, SENSOR3;

//deslocamentos de calibracao
int leftOffset = 0, rightOffset = 0, centre = 0;
//pinos para a velocidade e direcao do motor
int speed1 = 3, speed2 = 11, direction1 = 12, direction2 = 13;
//velocidade inicial e deslocamento de rotacao
int startSpeed = 120, rotate = 30;
//limiar do sensor
int threshold = 50;
//velocidades iniciais dos motores esquerdo e direito
int left = startSpeed, right = startSpeed;

int somasensores = 0;

//Rotina de calibracao do sensor
void calibrate()
{
 for (int x=0; x<10; x++) //Executa 10 vezes para obter uma media
 {
   delay(100);
   SENSOR1 = analogRead(8); // sensor da esquerda
   SENSOR2 = analogRead(9); // sensor do meio
   SENSOR3 = analogRead(10); // sensor da direita
   leftOffset = leftOffset + SENSOR1;
   centre = centre + SENSOR2;
   rightOffset = rightOffset + SENSOR3;
   delay(100);
 }
 //obtem a media para cada sensor
 leftOffset = leftOffset /10;
 rightOffset = rightOffset /10;
 centre = centre / 10;
 //calcula os deslocamentos para os sensores esquerdo e direito
 leftOffset = 150;
 rightOffset = 150;
 centre = 150;
}

void setup()
{
  calibrate();
  delay(3000);
  Serial.begin(115200);
}

void loop()
{
  //utiliza a mesma velocidade em ambos os motores
    left = startSpeed;
    right = startSpeed;
    Serial.println("Segue reto.");
    Serial.print("sensor 1: ");
    Serial.println(SENSOR1);
    Serial.print("sensor 2: ");
    Serial.println(SENSOR2);
    Serial.print("sensor 3: ");
    Serial.print(SENSOR3);
    Serial.println("\n ");

  //le os sensores e adiciona os deslocamentos
  SENSOR1 = analogRead(8) + leftOffset;
  SENSOR2 = analogRead(9) + centre;
  SENSOR3 = analogRead(10) + rightOffset;
  //////////////////////////////////////////////

  
  // teste para parar em caso de cruzamento
  somasensores = SENSOR1 + SENSOR2 + SENSOR3;
  somasensores = somasensores / 3;

  if (somasensores > 850){
      left = 98;
      right = 98;
      motor_esq.setSpeed(left);
      motor_esq.run(FORWARD);
      motor_dir.setSpeed(right);
      motor_dir.run(BACKWARD);    
  }
  //////////////////////////////////////////////

  
  //Serial.print("leftOffset: ");
  //Serial.println(leftOffset);
  //Serial.print("rightOffset: ");
  //Serial.println(rightOffset);
  
  // pra seguir reto /////////////////////////////
  if ((SENSOR2 > SENSOR1) and (SENSOR2 > SENSOR3)){
      Serial.println("Seguindo reto");
      motor_esq.setSpeed(98);
      motor_esq.run(FORWARD);
      motor_dir.setSpeed(98);
      motor_dir.run(FORWARD);
  }
  /////////////////////////////////////////////////
  
  //Se SENSOR3 for maior do que o sensor do centro + limiar,
  // vire para a direita
  if ((SENSOR3) > (SENSOR1+leftOffset)) //  and (SENSOR3) > (SENSOR2+centre)
  {
    
    //left = startSpeed - rotate;
    //right = startSpeed + rotate;
    left = 98;
    right = 0;
    Serial.println("Vira para a direita.");
    Serial.print("sensor 1: ");
    Serial.println(SENSOR1);
    Serial.print("sensor 2: ");
    Serial.println(SENSOR2);
    Serial.print("sensor 3: ");
    Serial.print(SENSOR3);
    Serial.println(" \n");
    motor_esq.setSpeed(left);
    motor_esq.run(FORWARD);
    motor_dir.setSpeed(right);
    motor_dir.run(FORWARD);
  }
  //////////////////////////////////////////////////////////////
  
  //Se SENSOR1 for maior do que o sensor do centro + limiar,
// vire para a esquerda
  if ((SENSOR1) > (SENSOR3+rightOffset)) // and (SENSOR1) > (SENSOR2+centre)
  {
    
    //left = startSpeed - rotate;
    //right = startSpeed + rotate;
    left = 0;
    right = 98;
    
    Serial.println("Vira para a esquerda.");
    Serial.print("sensor 1: ");
    Serial.println(SENSOR1);
    Serial.print("sensor 2: ");
    Serial.println(SENSOR2);
    Serial.print("sensor 3: ");
    Serial.println(SENSOR3);
    Serial.println(" \n");
    motor_esq.setSpeed(left);
    motor_esq.run(FORWARD);
    motor_dir.setSpeed(right);
    motor_dir.run(FORWARD);
  }
  ///////////////////////////////////////////////////////////////////
  

  //Envia os valores de velocidade para os motores
  //motor_esq.setSpeed(left);
  //motor_esq.run(FORWARD);
  //motor_dir.setSpeed(right);
  //motor_dir.run(FORWARD);
  
  
}

// testar saida dos sensores 


