#include<stdio.h>

typedef struct Car{
  int num;
  double gas;
}Car;

int main(void){
  Car car1 = {1234,25.5};
  Car car2 = {4567,52.2};


  car1.num = 1234;
  car1.gas = 25.5;

  printf("No.%d : Gas, %f\n",car1.num,car1.gas);
  printf("No.%d : Gas, %f\n",car2.num,car2.gas);

  car2 = car1;

  printf("No.%d : Gas, %f\n",car2.num,car2.gas);

  return 0;
}
