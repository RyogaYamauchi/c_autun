/*
  854003 山内龍我
*/

#include<stdio.h>

int main(){

  int num1,num2,num3,answer;

  scanf("%d",&num1);
  answer = num1;

  scanf("%d",&num2);
  if (num2>answer){
    answer = num2;
  }

  scanf("%d",&num3);
  if (num3>answer){
    answer = num3;
  }

  printf("%d\n",answer);

  return 0;
}
