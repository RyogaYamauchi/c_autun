/* fish01.c
   課題１　魚の描写を関数として独立させる
　　2018.11.14 g1853914 Minakata Minami
*/

#include <stdio.h>
#include <math.h>
#include <handy.h>
#include<time.h>
#include<stdlib.h>

int fishLeft(int);
int fishRight(int);
double fish[5][10];


int main() {
  double x, y, size, dx, dy;
  int num = 1;
  int i,j,temp;

  HgOpen(400.0, 400.0);
  srand(time(NULL));

  for(i=0;i<10;i++){
    for(j=0;j<5;j++){
      if(j==0) temp=200;
      fish[i][j] = rand()%100+temp+200;
      if(j==2) temp=10;
      fish[i][j] = rand()%10+temp+size;
      if(j==3) fish[i][j] = rand()%10;
    }
  }

  for(;;) {

    for(i=0;i<10;i++){
      if(fish[i][3]<0){
        fishLeft(i);
      }
      if(fish[i][3]>0){
        fishRight(i);
      }
    }
    HgSleep(0.1);
    HgClear();
	}
  return 0;
}

int fishLeft(int number) {
  int i;

  HgSetColor(HG_RED);
  HgSetFillColor(HG_RED);
  HgFanFill(fish[number][0], fish[number][1], fish[number][2], 1.25 * M_PI, 0.75 * M_PI, 0); //頭
  HgMoveTo(fish[number][0] + fish[number][2], fish[number][1]); //胴体
  HgLineTo(fish[number][0] + fish[number][2] * 3.0, fish[number][1]); //胴骨
  HgLineTo(fish[number][0] + fish[number][2] * 4.0, fish[number][1] - fish[number][2]); //尾びれ
  HgMoveTo(fish[number][0] + fish[number][2] * 3.0, fish[number][1]);
  HgLineTo(fish[number][0] + fish[number][2] * 4.0, fish[number][1] + fish[number][2]); //尾びれ
  HgSetFillColor(HG_WHITE); //白色
  HgCircleFill(fish[number][0] + fish[number][2] / 3.0, fish[number][1] + fish[number][2] / 2.0, fish[number][2] / 4.0, 0); //目を入れる
  HgSetColor(HG_RED);
  for(i = 0; i < 5; i++){
    HgLine(fish[number][0] + fish[number][2] * 1.2 + i * fish[number][2] / 3.0, fish[number][1] - fish[number][2] / 2.0,
             fish[number][0] + fish[number][2] * 1.2 + i * fish[number][2] / 3.0, fish[number][1] + fish[number][2] / 2.0);
  }
  if( fish[number][1] < fish[number][2] || fish[number][1] > (400.0 - fish[number][2]) ) fish[number][4] *= (-1.0);
  fish[number][1] += fish[number][4];
  if( fish[number][0] < fish[number][2] || fish[number][0] > (400.0 - fish[number][2]) ) fish[number][3] *= (-1.0);
  fish[number][0] += fish[number][3];
  return 0;
}

int fishRight(int number) {
	int j;

	HgSetColor(HG_RED);
	HgSetFillColor(HG_RED);
	HgFanFill(fish[number][0], fish[number][1], fish[number][2], 0.25 * M_PI, -2.25 * M_PI, 0); //頭
	HgMoveTo(fish[number][0] - fish[number][2], fish[number][1]); //胴体
	HgLineTo(fish[number][0] - fish[number][2] * 3.0, fish[number][1]); // 胴骨
	HgLineTo(fish[number][0] - fish[number][2] * 4.0, fish[number][1] + fish[number][2]); //尾びれ
	HgMoveTo(fish[number][0] - fish[number][2] * 3.0, fish[number][1]);
	HgLineTo(fish[number][0] - fish[number][2] * 4.0, fish[number][1] - fish[number][2]); //尾びれ
	HgSetFillColor(HG_WHITE); //白色
	HgCircleFill(fish[number][0] - fish[number][2] / 3.0, fish[number][1] + fish[number][2] / 2.0, fish[number][2] / 4.0, 0); // 目を入れる
	HgSetColor(HG_RED);
	for(j = 0; j < 5; j++) {
		HgLine(fish[number][0] - fish[number][2] * 1.2 - j * fish[number][2] / 3.0, fish[number][1] + fish[number][2] / 2.0,
             fish[number][0] - fish[number][2] * 1.2 - j * fish[number][2] / 3.0, fish[number][1] - fish[number][2] / 2.0);
	}
  if( fish[number][1] < fish[number][2] || fish[number][1] > (400.0 - fish[number][2]) ) fish[number][4] *= (-1.0);
  fish[number][1] += fish[number][4];
  if( fish[number][0] < fish[number][2] || fish[number][0] > (400.0 - fish[number][2]) ) fish[number][3] *= (-1.0);
  fish[number][0] += fish[number][3];
	return 0;
}
