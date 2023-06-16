#include <Servo.h>

#define POTENCIOMETRO_PINO A2
#define SERVO_PINO 9
#define BOTAO_30_PINO 3
#define BOTAO_45_PINO 4
#define BOTAO_60_PINO 5

#define DEBUG

struct estado {
  int angulo;
  int botao_30;
  bool botao_45;
  bool botao_60;
} estadoPassado;

int memoriaAngulos[3];
int memoriaAngulosQnt = 0;
Servo serv;

static void anexar_angulo_memoria(const int angulo)
{
  memoriaAngulos[memoriaAngulosQnt] = angulo;
  memoriaAngulosQnt++;
}

static void retirar_angulo_memoria(const int angulo)
{
  int anguloIndice = 0;
  while (memoriaAngulos[anguloIndice] != angulo)
    anguloIndice++;
  
  while (anguloIndice < 2) {
    memoriaAngulos[anguloIndice] = memoriaAngulos[anguloIndice + 1];
    anguloIndice++;
  }

  memoriaAngulosQnt--;
}

int registrar_estado_atual(const int anguloMedido, const bool botao_30, const bool botao_45, const bool botao_60)
{
  if (!estadoPassado.botao_30 && botao_30){
    anexar_angulo_memoria(30);
    estadoPassado.botao_30 = true;
  }
  if (!estadoPassado.botao_45 && botao_45) {
    anexar_angulo_memoria(45);
    estadoPassado.botao_45 = true;
  }
  if (!estadoPassado.botao_60 && botao_60) {
    anexar_angulo_memoria(60);
    estadoPassado.botao_60 = true;
  }

  if (estadoPassado.botao_30 && !botao_30) {
    retirar_angulo_memoria(30);
    estadoPassado.botao_30 = false;
  }
  if (estadoPassado.botao_45 && !botao_45) {
    retirar_angulo_memoria(45);
    estadoPassado.botao_45 = false;
  }
  if (estadoPassado.botao_60 && !botao_60) {
    retirar_angulo_memoria(60);
    estadoPassado.botao_60 = false;
  }

  if (memoriaAngulosQnt)
    return memoriaAngulos[memoriaAngulosQnt - 1];

  int anguloPassado = estadoPassado.angulo;
  estadoPassado.angulo = anguloMedido;
  return anguloPassado;
}

#ifdef DEBUG
void print_estado(const int anguloMedido, const int anguloServo, const bool botao_30, const bool botao_45, const bool botao_60)
{
  Serial.print("{AnguloM: ");
  Serial.print(anguloMedido);

  Serial.print(", ");
  Serial.print("{AnguloS: ");
  Serial.print(anguloServo);

  Serial.print(", ");
  Serial.print(", 30: ");
  Serial.print(botao_30);

  Serial.print(", ");
  Serial.print(", 45: ");
  Serial.print(botao_45);

  Serial.print(", ");
  Serial.print(", 60: ");
  Serial.print(botao_60);

  Serial.println("}");
}
#endif

void mover_servo(const int angulo)
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

  estadoPassado = {0, LOW, LOW, LOW};
  mover_servo(estadoPassado.angulo);

  #ifdef DEBUG
  Serial.begin(9600);
  #endif
}

void loop()
{
  int anguloMedido = map(analogRead(POTENCIOMETRO_PINO), 0, 255, 0, 180);
  bool botao_30 = digitalRead(BOTAO_30_PINO);
  bool botao_45 = digitalRead(BOTAO_45_PINO);
  bool botao_60 = digitalRead(BOTAO_60_PINO);

  int anguloServo = registrar_estado_atual(anguloMedido, botao_30, botao_45, botao_60);
  mover_servo(anguloServo);

  #ifdef DEBUG
  print_estado(anguloMedido, anguloServo, botao_30, botao_45, botao_60);
  #endif
}
