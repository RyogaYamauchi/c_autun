/* fish01.c
   課題１　魚の描写を関数として独立させる
　　2018.11.14 g1853914 Minakata Minami
*/

#include <stdio.h>
#include <math.h>
#include <handy.h>

int l_fish(double x, double y, double size) { //左向きのfish
  int i;

  HgSetColor(HG_RED);
  HgSetFillColor(HG_RED);
  HgFanFill(x, y, size, 1.25 * M_PI, 0.75 * M_PI, 0); //頭
  HgMoveTo(x + size, y); //胴体
  HgLineTo(x + size * 3.0, y); //胴骨
  HgLineTo(x + size * 4.0, y - size); //尾びれ
  HgMoveTo(x + size * 3.0, y);
  HgLineTo(x + size * 4.0, y + size); //尾びれ
  HgSetFillColor(HG_WHITE); //白色
  HgCircleFill(x + size / 3.0, y + size / 2.0, size / 4.0, 0); //目を入れる
  HgSetColor(HG_RED);
  for(i = 0; i < 5; i++){
    HgLine(x + size * 1.2 + i * size / 3.0, y - size / 2.0,
             x + size * 1.2 + i * size / 3.0, y + size / 2.0);
  }
  return 0;
}

int r_fish(double x, double y, double size) { // 右向きのfish
	int j;

	HgSetColor(HG_RED);
	HgSetFillColor(HG_RED);
	HgFanFill(x, y, size, 0.25 * M_PI, -2.25 * M_PI, 0); //頭
	HgMoveTo(x - size, y); //胴体
	HgLineTo(x - size * 3.0, y); // 胴骨
	HgLineTo(x - size * 4.0, y + size); //尾びれ
	HgMoveTo(x - size * 3.0, y);
	HgLineTo(x - size * 4.0, y - size); //尾びれ
	HgSetFillColor(HG_WHITE); //白色
	HgCircleFill(x - size / 3.0, y + size / 2.0, size / 4.0, 0); // 目を入れる
	HgSetColor(HG_RED);
	for(j = 0; j < 5; j++) {
		HgLine(x - size * 1.2 - j * size / 3.0, y + size / 2.0,
             x - size * 1.2 - j * size / 3.0, y - size / 2.0);
	}
	return 0;
}



int main() {
  double x, y, size, dx, dy;
  int num = 1;

  HgOpen(400.0, 400.0);

  x = 200.0; //x座標の初期設定
  y = 200.0; //y座標の初期設定
  size = 10.0; //頭の半径を決める
  dx = -0.8 * size; //x方向の移動速度
  dy = 0.4 * size; //y速度の移動方法

  for(;;) {

		if(num == 1) { // 左向きのfish
			HgClear();
			l_fish(x, y, size);
			if( y < size || y > (400.0 - size) ) dy *= (-1.0);
			y += dy;
			if( x < size || x > (400.0 - size) ) dx *= (-1.0);
			x += dx;
			HgSleep(0.1);
		}else if (num == 2) { // 右向きのfish
		    HgClear();
			r_fish(x, y, size);
			if( y < size || y > (400.0 - size) ) dy *= (-1.0);
			y += dy;
			if( x < size || x > (400.0 - size) ) dx *= (-1.0);
			x += dx;
			HgSleep(0.1);
		}

		if(x == 8) { // 左→右
			num = 2;
		}else if(x == 392) { // 右→左
			num = 1;
		}

	}

  return 0;
}
