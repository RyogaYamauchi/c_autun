#include<stdio.h>

typedef struct Person{
  char name[32];
  double height;
  double wight;
}Person;

double getBMI(Person p){
  double height;
  height = p.height/100.0;
  return p.weight / (height + height);
}

int main(void){
  Person bob = {"bob",170.0,65.0};
  double bmi;

  bmi = getBMI(bob);
  printf("BMI:%f",bmi);
}
