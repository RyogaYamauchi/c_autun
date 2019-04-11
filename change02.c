/*
 change02.c
 金種計算：配列とループで実現する
*/

#include <stdio.h>
#include <stdlib.h>

#define TYPES 6

int main()
{
	int total; // おつり総額
	int value[TYPES] = {500, 100, 50, 10, 5, 1}; // 各金種の額
	int num[TYPES]; // その金種での支払い数
	int i; // ループカウンタ
	
	// おつり総額を入力
	scanf("%d", &total);

	// ここに金種計算のロジックを書く
	for(i=0; i<TYPES; i++) {
		num[i] = total / value[i]; 
		total = total % value[i];
	} 
	
	// 結果を出力
	for(i=0; i<TYPES; i++) {
		printf("%d:%d ", value[i], num[i]);
	}
	printf("\n");
	
	return 0;
}
