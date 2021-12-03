#include <AFMotor.h>
#include <Ultrasonic.h>

#define pino_trigger 18
#define pino_echo 2
#define feedback 19

AF_DCMotor motoresq(1);
AF_DCMotor motordir(2);


int quantidade = 8;
int valval = 0;
int valvaz2 = 0;
int distancia = 35.;

Ultrasonic ultrasonic(pino_trigger, pino_echo);
void pisca(int velocidade)
{
  digitalWrite(feedback, HIGH);
  delay(velocidade);
  digitalWrite(feedback, LOW);
  delay(velocidade);
}

void frente(int velocidade)
  {
    motoresq.setSpeed(velocidade);
    motoresq.run(FORWARD);
    motordir.setSpeed(velocidade);
    motordir.run(FORWARD);
  }
void tras(int velocidade, int tempo) 
  {
    motoresq.setSpeed(velocidade);
    motoresq.run(BACKWARD);
    motordir.setSpeed(velocidade);
    motordir.run(BACKWARD);
    delay(tempo);
  }
void direita() 
  {
    motoresq.setSpeed(255);
    motoresq.run(FORWARD);
  }
void esquerda() 
  {
    motordir.setSpeed(255);
    motordir.run(FORWARD);
  }

void parar()
   {
    motordir.run(RELEASE);
    motoresq.run(RELEASE);
   }
void eixoesq(int velocidade, int tempo)
{
    motordir.setSpeed(velocidade);
    motordir.run(FORWARD);
   
    motoresq.setSpeed(velocidade);
    motoresq.run(BACKWARD);
    delay(tempo);
}
void eixodir(int velocidade, int tempo)
{
    motoresq.setSpeed(velocidade);
    motoresq.run(FORWARD);
    
    motordir.setSpeed(velocidade);
    motordir.run(BACKWARD);
    delay(tempo);
}
  //ato de personalidade

void negacao(int tempo)
{
    
    
     eixodir(200,tempo);
     parar();
     delay(tempo);
     eixoesq(200, 120);
      
    
}

void setup() {
  Serial.begin(9600);
  pinMode(feedback, OUTPUT);
  // put your setup code here, to run once:
  frente(180);
  delay(500);
  
  

}

void loop() {
  
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  for(int i=1; i<= quantidade; i++){
      valval = valval + cmMsec;
  }
  Serial.println("A distancia calculada é: ");
  Serial.println(valval / 3);
  Serial.print("A distancia é: ");
  Serial.println(cmMsec);
 
  if ((valval / quantidade) > distancia) // mais longe que a distancia
 {
    pisca(120);
    //frente(255);
    //delay(10);
    frente(125);
 }

  if ((valval / quantidade) <= distancia) { //mais proximo que a distancia
    digitalWrite(feedback, HIGH);
    parar();
    delay(200);
    int aleatorio = random(1, 16);
    //condição aleatória para virar direita ou esquerda
    if (aleatorio <= 7)
    {
      eixodir(120, 100);
      delay(150);
    }
    else if (aleatorio > 7 && aleatorio < 15)
    {
      eixoesq(120, 100);
      delay(150);
    }
    else{
      tras(150, 180);
    }
    
    
 }
 if ((valval / quantidade) == 0)
 {
  digitalWrite(feedback, LOW);
 }
 
 valvaz2 = valval;
 valval = 0;

 
}
