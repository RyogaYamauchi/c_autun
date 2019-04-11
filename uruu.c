/**
うるう年判定
854003 山内龍我
**/

#include<stdio.h>

int main(void){
  int year;
  int uruuflag=0;

  scanf("%d", &year);
  printf("%d", year);

  if(year % 4 == 0)
  {
    if(year % 100 != 0)
    {
      uruuflag = 1; //4で割り切れて100で割り切れないとき、フラッグを立てる
    } else
    {
      if(year % 400 == 0)
      {
        uruuflag = 1; //４で割り切れて４００でも割り切れるとき、フラッグを立てる
    }
  }
  }

  if(uruuflag == 1) printf(" leap\n");
  return 0;
}
