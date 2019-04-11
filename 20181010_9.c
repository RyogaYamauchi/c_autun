#include<stdio.h>
int main(){
  int i,j;
  int data[5];
  int data2[100] = {};
  
  for (i=0; i<5; i++) {
   scanf("%d", &data[i]);
   data2[data[i]] += 1;
  }
  for (i=0; i<100; i++) {
    for(j=0; j<data2[i];j++){
      if (data2[i]>0) printf("%d\n",i);
    }
  }
}
