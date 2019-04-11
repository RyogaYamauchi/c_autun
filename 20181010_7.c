#include<stdio.h>

int main(){
  int i=0;
  int data[5] = {};
  int data2[5] = {};
  int sum = 0;

  for (i=0; i<5; i++) {
   scanf("%d", &data[i]);
   if (sum<data[i]) sum = data[i];
  }

  printf("max : %d\n",sum);
  for (i=4; i>=0; i--) {
    data2[4-i] = data[i];
  }

  for (i=0; i<5; i++) {
    if (sum!=data2[i])  printf("data2[%d] : %d\n", i, data2[i]);
  }

}
