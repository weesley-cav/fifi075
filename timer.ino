#include "TimerOne.h"
#include "stdio.h"

int TIMER_FLAG = 0;
long int TIMER_ONE_SECOND = 1000000;

int TIMER_SECONDS = 30;
int TIMER_MINUTES = 59;
int TIMER_HOURS = 1;

int TIMER_SELECTED = 2; // em horas

void setup(){
  Serial.begin(9600);  
  pinMode(13, OUTPUT);
  Timer1.initialize(TIMER_ONE_SECOND); // Inicializa o Timer1 e configura para um período definido
  Timer1.attachInterrupt(callback); // Configura a função callback() como a função para ser chamada a cada interrupção do Timer1
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

void loop(){
  int i = 0;
  Serial.print("Timer Flag ");
  Serial.println(TIMER_FLAG);

  Serial.print("\n");
  char buffer [20];
  i=sprintf (buffer, "%d:%d:%d", TIMER_HOURS, TIMER_MINUTES, TIMER_SECONDS);
  for(int l= 0; l<=i; l++) 
  Serial.print(buffer[l]);

  Serial.print("\n");
}
