#include<stdio.h>

int main(){
  int i=0;
  int data[5] = {};
  int sum = 0;

  for (i=0; i<5; i++) {
   scanf("%d", &data[i]);
   if (sum<data[i]) sum = data[i];
  }
  printf("sum : %d\n",sum);
}
