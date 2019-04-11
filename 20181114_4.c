#include<stdio.h>
float calc(float,float);
int main(){
  float num1,num2;
  scanf("%f",&num1);
  scanf("%f",&num2);

  printf("%f\n",calc(num1,num2));
  return 0;
}

float calc(float num1,float num2){

  return num1*num2;
}
