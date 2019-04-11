#include<stdio.h>

int sub(int *);

int main(){
  int i=0;
  int data[5] = {};
  for (i=0; i<5; i++) {
   scanf("%d", &data[i]);
  }
  printf("max : %d\n",sub(data));
}

int sub(int data[5]){  //data[5]を*dataと書いても同じ意味になる
  int max,i;
  int sum=0;
  for (i=0; i<5; i++) {
    if (sum<data[i]) sum = data[i];
  }
  return sum;
}
