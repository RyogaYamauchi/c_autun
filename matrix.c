#include<stdio.h>

int mat_add(int*,int*);
int *result;

int main()
{
  int num1[3] = {1,2,3};
  int num2[3] = {4,5,6};

  *result = mat_add(num1,num2);
  printf("%d,\n",result);

  return 0;
}

int mat_add(int *num1, int *num2)
{
  int i=0;

  for(i=0;i<3;i++){
    result[i] = num1[i] * num2[i];
    printf("result[%d] = %d\n",i,result[i]);
  }
  return 0;
}
