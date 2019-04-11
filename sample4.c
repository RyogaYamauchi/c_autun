#include<stdio.h>
int draw(int **);

int main(){
  int data[3][3] = { {1,2,3},
                     {4,5,6},
                     {7,8,9}};
  draw(data);
  return 0;
}

int draw(int **data){
  int i,j;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      printf("%d ",data[i][j]);
    }
    printf("\n");
  }
}
