#include <AFMotor.h>

AF_DCMotor motor_esq(1); //Seleciona o motor 1
AF_DCMotor motor_dir(2); //Seleciona o motor 4

int comando;

// 1 >> vira para a direita
// 2 >> vai reto
// 3 >> vira para a esquerda
// 0 >> para

void setup()
{
  Serial.begin(115200);
  
}

void loop()
{
  if(Serial.available()){ // Verifica se há caracteres disponíveis
    char caractere = Serial.read(); // Armazena caractere lido
    if(isDigit(caractere)){ // Verifica se o caractera ASCII é um digito entre 0 e 9
      comando = (caractere - '0');
    }
  }  

      if(comando == 1){
          //Serial.println("Virando para direita");
          motor_esq.setSpeed(148);
          motor_esq.run(FORWARD);
          motor_dir.setSpeed(148);
          motor_dir.run(BACKWARD);         
      }
      if(comando == 3){
          //Serial.println("Virando para esquerda");
          motor_esq.setSpeed(148);
          motor_esq.run(BACKWARD);
          motor_dir.setSpeed(148);
          motor_dir.run(FORWARD);
      }
      if(comando == 2){
          //Serial.println("Seguindo reto");
          motor_esq.setSpeed(148);
          motor_esq.run(FORWARD);
          motor_dir.setSpeed(148);
          motor_dir.run(FORWARD);         
      }
      if(comando == 0){
          //Serial.println("Fim das rotas, parando");
          motor_esq.setSpeed(0);
          motor_esq.run(FORWARD);
          motor_dir.setSpeed(0);
          motor_dir.run(FORWARD);         
        }
}
