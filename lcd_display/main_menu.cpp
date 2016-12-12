#include "Arduino.h"
#include <LiquidCrystal.h>
#include "MPPT.hpp"
#include "main_menu.hpp"
#include "power_sensing.hpp"
#include "charger.hpp"

#define left_button A3
#define enter_button A2
#define right_button A1

extern LiquidCrystal lcd;
extern power MPPT;

void button_init(void){
	pinMode(left_button, INPUT);
	pinMode(right_button, INPUT);
	pinMode(enter_button, INPUT);
}

void main_menu(void){
  int eb,rb,lb;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Main Menu");
   while(1){
    eb = digitalRead(enter_button);
    rb = digitalRead(right_button);
    lb = digitalRead(left_button);
    if(eb | rb | lb){
      while((digitalRead(enter_button) | digitalRead(right_button) | digitalRead(left_button))); 
      break;
    }
    delay(10);
  }
  main_menu1();
}

void main_menu1(void){
  int rb,lb,eb;
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Find Power Point");
  while(1){
    eb = digitalRead(enter_button);
    rb = digitalRead(right_button);
    lb = digitalRead(left_button);
    if(eb | rb | lb){
      while((digitalRead(enter_button) | digitalRead(right_button) | digitalRead(left_button))); 
      break;
    }
    delay(10);
  }
	if(eb) find_pp();
	if(rb) main_menu2();
	if(lb) main_menu5();
}

void main_menu2(void){
  int eb,rb,lb;
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("MPPT");
	while(1){
    eb = digitalRead(enter_button);
    rb = digitalRead(right_button);
    lb = digitalRead(left_button);
    if(eb | rb | lb){
      while((digitalRead(enter_button) | digitalRead(right_button) | digitalRead(left_button))); 
      break;
    }
    delay(10);
  }
  if(eb) mppt();
	if(rb) main_menu3();
	if(lb) main_menu1();
}

void main_menu3(void){
  int eb,rb,lb;
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Power Sensing");
  while(1){
      eb = digitalRead(enter_button);
      rb = digitalRead(right_button);
      lb = digitalRead(left_button);
      if(eb | rb | lb){
        while((digitalRead(enter_button) | digitalRead(right_button) | digitalRead(left_button))); 
        break;
      }
      delay(10);
    }
  if(eb) output_sensing(MPPT);
	if(rb) main_menu4();
	if(lb) main_menu2();
}

void main_menu4(void){
  int eb,rb,lb;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SEPIC manual");
  while(1){
      eb = digitalRead(enter_button);
      rb = digitalRead(right_button);
      lb = digitalRead(left_button);
      if(eb | rb | lb){
        while((digitalRead(enter_button) | digitalRead(right_button) | digitalRead(left_button))); 
        break;
      }
      delay(10);
    }
  if(eb) sepic_adjust();
  if(rb) main_menu5();
  if(lb) main_menu3();


}

void main_menu5(void){
  int eb,rb,lb;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Charge Battery");
  while(1){
      eb = digitalRead(enter_button);
      rb = digitalRead(right_button);
      lb = digitalRead(left_button);
      if(eb | rb | lb){
        while((digitalRead(enter_button) | digitalRead(right_button) | digitalRead(left_button))); 
        break;
      }
      delay(10);
    }
  if(eb) charge();
  if(rb) main_menu1();
  if(lb) main_menu4();

}

