#include<stdio.h>

int factrical(int , int);

int main(){
  int num1=0;
  int num2=0;

  scanf("%d",&num1);
  scanf("%d",&num2);

  printf("%d\n",factrical(num1,num2));
  return 0;
}

int factrical(int num1,int num2){
  return (num1*num1)+(num2*num2);
}
