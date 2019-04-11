#include<stdio.h>

int main(){
  int i;
  int data[5];
  for (i=0; i<5; i++) {
   scanf("%d", &data[i]);
  }
  for (i=4; i>=0; i--) {
    printf("data%d : %d\n", i, data[i]);

  }

}
