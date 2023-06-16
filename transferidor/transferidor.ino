#include <Servo.h>

#define POTENCIOMETRO_PINO A2
#define SERVO_PINO 9
#define BOTAO_30_PINO 3
#define BOTAO_45_PINO 4
#define BOTAO_60_PINO 5

#define DEBUG

int velhoAngulo;
Servo serv;

#ifdef DEBUG
void print_estado(const int angulo, const bool botao_30, const bool botao_45, const bool botao_60)
{
  Serial.print("{Angulo: ");
  Serial.print(angulo);
  Serial.print(", 30: ");
  Serial.print(botao_30);
  Serial.print(", 45: ");
  Serial.print(botao_45);
  Serial.print(", 60: ");
  Serial.print(botao_60);
  Serial.println("}");
}
#endif

void moverServo(const int angulo)
{
  serv.write(angulo);
  delay(20);
}

void setup()
{
  pinMode(POTENCIOMETRO_PINO, INPUT);
  pinMode(SERVO_PINO, OUTPUT);
  pinMode(BOTAO_30_PINO, INPUT);
  pinMode(BOTAO_45_PINO, INPUT);
  pinMode(BOTAO_60_PINO, INPUT);
  serv.attach(SERVO_PINO);

  int angulo = map(analogRead(POTENCIOMETRO_PINO), 0, 255, 0, 180);

  #ifdef DEBUG
  Serial.begin(9600);
  #endif
}

void loop()
{
  int angulo = map(analogRead(POTENCIOMETRO_PINO), 0, 255, 0, 180);
  bool botao_30 = digitalRead(BOTAO_30_PINO);
  bool botao_45 = digitalRead(BOTAO_45_PINO);
  bool botao_60 = digitalRead(BOTAO_60_PINO);

  #ifdef DEBUG
  print_estado(angulo, botao_30, botao_45, botao_60);
  #endif
}
