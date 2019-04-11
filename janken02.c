/*
  854003 山内龍我
  足し引きする
*/

#include<stdio.h>

int main(){
  int me,you;

  scanf("%d %d",&me,&you);

  if (me != you){
    if (me+1==you){
      printf("win\n");
    }
    else if (me-1==you){
      printf("lose\n");
    }
    else{
      printf("win\n");
    }
  }
  else{
    printf("even\n");
  }
  return 0;
}
