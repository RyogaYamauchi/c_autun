#include<stdio.h>
int (*mult(int [][2],int [][2]))[2];

int main(){
  int i,j;
  int data[2][2] = { {1,2},
                     {3,4}};
  int data2[2][2] = {{1,2},
                     {3,4}};
  int result[2][2] = {};

  **result = mult(data,data2);
  printf("%d,%d\n%d,%d",result[0][0],result[0][1],result[1][0],result[1][1]);


   for(i=0;i<2;i++){
    for(j=0;j<2;j++){
      printf("%d ",result[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int (*mult(int data[][2],int data2[][2]))[2]{
  int result[2][2];
  int i,j;

  for(i=0;i<2;i++){
    for(j=0;j<2;j++){
      result[i][j] = data[i][j] * data2[i][j];
    }
  }
  return **result;
}
