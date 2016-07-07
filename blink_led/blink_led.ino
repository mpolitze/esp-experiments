#include <avr/sleep.h>

int led1 = 13;
int led2 = 12;
int input = 2;

int blink_delay = 250;

void setup() {    
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(input, INPUT);
  
  digitalWrite(led1, HIGH);
  delay(blink_delay);
  digitalWrite(led1, LOW);
  delay(blink_delay);
    
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void blink(){
  int d = digitalRead(input);
  digitalWrite(led1, d);
}

void loop() {    
  attachInterrupt(0, blink, CHANGE);

  digitalWrite(led2, HIGH);
  delay(blink_delay);
  digitalWrite(led2, LOW);
  delay(blink_delay);
  
  sleep_enable();
  sleep_cpu();
}
