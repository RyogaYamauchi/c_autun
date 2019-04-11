/*
 じゃんけん判定をする
 グー:1 チョキ:2 パー:3 とする。
 入力は二つの数字を入れる（最初に自分の手、次に相手の手）
 1 2 は自分がグー、相手がチョキなので、自分の「勝ち」と出せばよい
 
 条件分岐を自分の出した手で場合分けした場合
 
 */

#include <stdio.h>

int main() {
    
     //変数の宣言（変数は必ず冒頭にまとめて記載すること）
    int me;     //自分の出した手の値を格納する変数
    int you;    //相手の出した手の値を格納する変数
	
    // データを入力
	scanf("%d %d", &me, &you);
	
    //条件分岐を自分の出した手で場合分けした場合
	if( me == 1 ) { // 自分がグーだった場合、
        
		if( you == 1 ) printf("even\n");        //相手がグー
		else if( you == 2 ) printf("win\n");    //相手がチョキ
		else printf("lose\n");                  //相手がパー
	
    } else if( me == 2 ) { // 自分がチョキだった場合、
        
		if( you == 2 ) printf("even\n");        //相手がチョキ
		else if( you == 3 ) printf("win\n");    //相手がパー
		else printf("lose\n");                  //相手がグー
	
    } else { // 自分がパーだった場合、
        
		if( you == 3 ) printf("even\n");        //相手がパー
		else if( you == 1 ) printf("win\n");    //相手がグー
		else printf("lose\n");                  //相手がチョキ
        
	}
	
	return 0;
}

