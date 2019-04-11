#include<stdio.h>

int judge(int,int);

int main(){
  int num1,num2;
  scanf("%d",&num1);
  scanf("%d",&num2);

  printf("Big : %d\n",judge(num1,num2));

  return 0;
}

int judge(int num1,int num2){
  if(num1<num2)return num2;
  if(num1>num2)return num1;

  return 0;

}
