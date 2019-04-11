#include <stdio.h>


typedef struct Person {
    char name[32];
    double height;
    double weight;
} Person;

double getBMI(Person p){
  double height;
  height = p.height/100.0;
  return p.weight / (height + height);
}

int main() {
    Person p[5]={
        {"Alice", 155.0, 45.0},
        {"Bob",   170.0, 65.0},
        {"Carol", 163.0, 55.0},
        {"Dave",  180.0, 85.0},
        {"Ellen", 160.0, 56.0}
    };

    int i;
    int BMI[5];
    double maxBMI = 0;
    int maxNumber = 0;

    for(i=0; i<5; i++) {
      BMI[i] = getBMI(p[i]);
      if(maxBMI<BMI[i]) {
        maxBMI = BMI[i];
        maxNumber = i;
      }
    }

    for(i=0; i<5; i++) {
      printf("No : %d, name:%s, height:%f ,weight:%f\n",i,p[i].name,p[i].height,p[i].weight);
    }

    printf("-----------maxBMI is ---------------\n");
    printf("maxBMI = %f , No.%d , name : %s , height : %f , weight : %f\n",maxBMI,maxNumber,p[maxNumber].name , p[maxNumber].height,p[maxNumber].weight);
    return 0;
}
