/*
  854003 山内龍我
*/

#include<stdio.h>

int judge(int,int);
int main(){

  int num1,num2,num3;
  scanf("%d",&num1);
  scanf("%d",&num2);
  scanf("%d",&num3);

  if (num1>num2){
    if (num1>num3){
      printf("%d\n",num1);
    }
    else{
      printf("%d\n",num3);
    }
  }
  else{
    if (num2>num3){
      printf("%d\n",num2);
    }
    else{
      printf("%d\n",num3);
    }
  }



  return 0;
}
