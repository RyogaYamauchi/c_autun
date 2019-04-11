/*
 image01.c
 Handy Graphic の HgImageLoad を試す
 */

#include <stdio.h>
#include <stdlib.h>
#include <handy.h>

int main()
{
    HgOpen(600.0, 400.0);
    
    // データを読み込んで gid にイメージ id （HandyGraphic が内部で利用する）を保持
    int gid;
    gid = HgImageLoad("image_tori.jpg");
    
    // gid を指定して描画する（位置・倍率・角度も指定）
    HgImagePut(100.0, 100.0, gid, 0.4, 0.0); // 座標位置 (100.0, 100.0) に倍率 0.4 傾き 0.0 で描画する
    HgImagePut(300.0, 200.0, gid, 1.0, 0.314); // 座標位置 (300.0, 200.0) に倍率 1.0 傾き 1/10π で描画する
    
    // 注意：
    // 一度読み込んだイメージデータは何度でも描画できる
    // イメージ id を gid[10] などのように配列変数で確保して複数の画像をプログラムで指定することも（もちろん）可能
    
    // キーが押されるのを待って終了
    HgGetChar();
    HgClose();
    
    return 0;
}
