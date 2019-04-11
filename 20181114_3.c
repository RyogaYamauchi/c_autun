#include<stdio.h>

int judge(int,int);

int main(){
  int num1,num2,num3,result;
  scanf("%d",&num1);
  scanf("%d",&num2);
  scanf("%d",&num2);

  result = judge(num1,num2);
  result = judge(result,num3);
  printf("result = %d\n",result);
  return 0;
}

int judge(int num1,int num2){
  if(num1<num2)return num2;
  if(num1>num2)return num1;

  return 0;

}
