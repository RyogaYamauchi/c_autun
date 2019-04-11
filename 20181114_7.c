#include<stdio.h>
#include<stdbool.h>

bool judge(int);

int main(){
  int year;

  printf("年 :");
  scanf("%d",&year);

  if(judge(year)==true)printf("うるう年です\n");
  if(judge(year)==false)printf("うるう年ちゃうで\n");

  return 0;
}

bool judge(int year){
  if(year % 4 ==0){
    if(year%100==0 && year%400!=0){
      return false;
    }
    else{
      return true;
    }
  }
}
