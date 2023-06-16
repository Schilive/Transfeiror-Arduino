#include <Servo.h>

#define POTENCIOMETRO_PINO A2
#define SERVO_PINO 9

#define DEBUG

Servo serv;

#ifdef DEBUG
void print_estado(const int potenciometro, const int angulo)
{
  Serial.print("{Potenciometro: ");
  Serial.print(potenciometro);

  Serial.print(", ");
  Serial.print("{Angulo: ");
  Serial.print(angulo);

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
  serv.attach(SERVO_PINO);

  #ifdef DEBUG
  Serial.begin(9600);
  #endif
}

void loop()
{
  int potenciometro = analogRead(POTENCIOMETRO_PINO);
  int angulo = map(potenciometro, 0, 255, 0, 180);

  #ifdef DEBUG
  print_estado(potenciometro, angulo);
  #endif
}
