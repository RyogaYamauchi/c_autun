#include<stdio.h>

int main(){
  int i=0;
  int data[5] = {};
  int sum = 0;
  int cnt = 0;

  for (i=0; i<5; i++) {
   scanf("%d", &data[i]);
   if (sum<data[i]) sum = data[i];
  }
  for (i=0; i<5; i++) {
    if (sum==data[i]) cnt++;
  }
  printf("sum : %d  %d個\n ",sum,cnt);
}
