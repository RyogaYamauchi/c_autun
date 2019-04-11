/*
  854003 山内龍我
  総当たり
*/

#include<stdio.h>

int main(){
  int me,you;

  scanf("%d %d",&me,&you);

  if (me != you){
    if (me == 1 && you ==2) printf("win\n");
    if (me == 1 && you ==3) printf("lose\n");
    if (me == 2 && you ==1) printf("lose\n");
    if (me == 2 && you ==3) printf("win\n");
    if (me == 3 && you ==1) printf("win\n");
    if (me == 3 && you ==2) printf("lose\n");
  }
  else{
    printf("even\n");
  }
  return 0;
}
