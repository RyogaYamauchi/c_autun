#include<stdio.h>

int main(){
  int i=0;
  int data[5] = {};
  int data2[5] = {};
  int sum = 0;
  int cnt = 0;

  for (i=0; i<5; i++) {
   scanf("%d", &data[i]);
   if (sum<data[i]) sum = data[i];
  }
  for (i=4; i>=0; i--) {
    data2[4-i] = data[i];
    printf("data2[%d] : %d\n", cnt, data[i]);
    cnt++;
  }
}
