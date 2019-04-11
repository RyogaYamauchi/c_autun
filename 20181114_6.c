#include<stdio.h>

int janken(int ,int);

int main(){
  int me,you;
  printf("手は");
  scanf("%d %d",&me,&you);

  switch(janken(me,you))
  {
    case 1: printf("even\n");
            break;
    case 2: printf("win\n");
            break;
    case 3: printf("lose\n");
            break;
    default:printf("null pointer exception : 01");
  }
  return 0;
}

int janken(int me,int you)
{
  if(me==you)
  {
    return 1;
  }
  else if((me ==1 && you == 2)||(me==2 && you == 3) || (me==3 && you ==1))
  {
    return 2;
  }
  else
  {
    return 3;
  }
}
