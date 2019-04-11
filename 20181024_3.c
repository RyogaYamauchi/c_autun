#include<stdio.h>
int main(){
  int i,j;
  int data[3][5];
  int count = 0;
  int sum = 0;
  for(i = 0;i<3;i++){
    for(j=0;j<5;j++){
      count++;
      data[i][j] = count;
      sum = count+sum;
      printf("%2d ",data[i][j]);
    }
    printf(" : %d\n",sum);
    sum = 0;
  }

  printf("-- -- -- -- --\n");
  for(j=0;j<5;j++){
    for(i=0;i<3;i++){
      sum = sum+data[i][j];
    }
    printf("%2d ",sum);
    sum = 0;

  }
  printf("\n");
  return 0;
}
