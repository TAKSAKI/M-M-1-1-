#include<iostream>
using namespace std;
#include<cmath>
#include<stdlib.h>
#include<fstream>

#define END_TIME 10000　//終了時間を10000とする
#define try 200 //客の単位平均時間に訪れる回数の最大値を設定
double rnd_exp(double ramda) { //指数分布の乱数作成
	double a = (rand() + 0.5) / (RAND_MAX + 1);
	return -log(1 - a) / ramda;
}
int main() {
	ofstream ofs("第三回.csv");　//データを保存するためにエクセルファイルを作る
	double customramda = 1;　//客が単位平均時間に訪れる回数の最小値を設定
	double serverramda = 10;　//サーバが単位時間に処理する平均回数回数を10とする
	for (int i = 0; i < try; i++) {//客の単位時間平均に訪れる回数を1から200に設定しロス率を計算
		double customtime = 0;　//お客が訪ねてくる時刻初期値
		double servertime = 0;　//サーバーが利用終了時刻初期値
		double cusnum = 0;　// お客の訪問数
		double lossnum = 0; //ロスする人数
		double ave = 0;
		while (true) {
			double x = rnd_exp(customramda);
			customtime += x;
			if (customtime > END_TIME) {　//終了時刻における処理
				customtime -= x;
				break;
			}
			cusnum += 1;
			if (customtime < servertime) lossnum += 1;//サーバーの時刻がお客の時間よりもかかる場合ロスする
			else {
				double y = rnd_exp(serverramda);
				servertime = customtime + y;　//サーバの利用時間更新
			}
		}
		ofs <<customramda<<","<< lossnum / cusnum << endl;
		customramda += 1;
	}
}
