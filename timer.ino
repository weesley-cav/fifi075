#include "TimerOne.h"
#include "stdio.h"

const int PIN_MOTION_SENSOR = 2;
const int PIN_LED = 6;
const long int TIMER_ONE_SECOND = 1000000;
int TIMER_FLAG = 0;

int TIMER_SECONDS = 30;
int TIMER_MINUTES = 59;
int TIMER_HOURS = 1;

int TIMER_SELECTED = 2; // tempo em horas

void setup(){
  Serial.begin(9600);  

  Timer1.initialize(TIMER_ONE_SECOND); // Inicializa o Timer1 e configura para um período definido
  Timer1.attachInterrupt(callback); // Configura a função callback() como a função para ser chamada a cada interrupção do Timer1

 // attachInterrupt(digitalPinToInterrupt(PIN_MOTION_SENSOR), toggle, RISING); //Configura o sensor de movimento para interrupção e chamada da função toggle()
}


void toggle() {
  static bool led_state = false;
  Serial.println("DETECTED!");
  led_state = !led_state;
  digitalWrite(PIN_LED, led_state);
}

void callback(){
  TIMER_SECONDS++;
  
  if(TIMER_SECONDS == 60){
    TIMER_SECONDS = 0;
    TIMER_MINUTES++;
  }
  if(TIMER_MINUTES == 60){
    TIMER_SECONDS = 0;
    TIMER_MINUTES = 0;
    TIMER_HOURS++; 
  }
  if(TIMER_HOURS == TIMER_SELECTED){
    digitalWrite(13, digitalRead(13) ^ 1);
    TIMER_FLAG = 1;  
  }
}

  /*
    Escopo a seguir exibe na porta serial o horário do timer utilizando um buffer auxiliar
  */
void timer_print(){
  int i = 0;
  Serial.print("Timer Flag ");
  Serial.println(TIMER_FLAG);

  char buffer [20];
  i=sprintf (buffer, "%d:%d:%d", TIMER_HOURS, TIMER_MINUTES, TIMER_SECONDS);
  for(int l= 0; l<=i; l++) 
  Serial.print(buffer[l]);
  Serial.print("\n");
}


void loop(){
  timer_print();
}
