#include<stdio.h>

#define N 4
#define MAX_WAIT 12
typedef struct state {
	int used[N];//0入れない、1入れる
	int value;
}state;

int main() {
	int i, j, k;
	int tmp_value;
	state DP_TABLE[N][MAX_WAIT + 1];
	//荷物の順序は1kg当たりの価値が高い順にソート済でないと動作しないので注意せよ
	int Weight[N] = { 1, 2, 5, 4 };//0,1,...,(N-1)番目の荷物の重量
	int Value[N] = { 3000, 2000, 4000, 3000 };//0,1,...,(N-1)番目の荷物の価値
	//DPテーブル初期化
	for (i = 0; i < N; i++) {
		for (j = 0; j <= MAX_WAIT; j++) {
			DP_TABLE[i][j].value = 0;
			for (k = 0; k < N; k++) {
				DP_TABLE[i][j].used[k] = 0;
			}
		}
	}
	//初期化ここまで
	
	//荷物 i から順にナップサック容量 j で荷物を詰めてみる
	for (i = 0; i < N; i++) {
		for (j = 1; j <= MAX_WAIT; j++) {
			//0番目の豆を考えている、もしくは、今考えている荷物がナップサックに入らないときは例外処理が発生する
			if (i == 0 || j < Weight[i]) {
				if (i == 0) {//0番目の豆だけで構成しなくてはならないとき
					if (j < Weight[i]) {
						DP_TABLE[i][j].value = 0;
						DP_TABLE[i][j].used[0] = 0;
					}
					else {
						DP_TABLE[i][j].value = Value[0];
						DP_TABLE[i][j].used[0] = 1;
					}

				}
				else {//i-1番目の荷物までで構成される重量jのものを引き継がざるをえないとき
					DP_TABLE[i][j].value = DP_TABLE[i - 1][j].value;
					for (k = 0; k < N; k++) {
						DP_TABLE[i][j].used[k] = DP_TABLE[i - 1][j].used[k];
					}
				}
			}
			else {//例外処理でなく、一般処理のとき
				
				//このif文で価値比較
				if (DP_TABLE[i - 1][j].value > DP_TABLE[i - 1][j-Weight[i]].value+Value[i]) 
				{//i番目の荷物を加えずに重量jの時が優秀なケース
					DP_TABLE[i][j].value = DP_TABLE[i - 1][j].value;
					for (k = 0; k < N; k++) {
						DP_TABLE[i][j].used[k] = DP_TABLE[i - 1][j].used[k];
					}
				}
				else 
				{//i番目の荷物を加えて重量jの時が優秀なケース
					DP_TABLE[i][j].value = DP_TABLE[i - 1][j - Weight[i]].value + Value[i];
					for (k = 0; k < N; k++) {
						DP_TABLE[i][j].used[k] = DP_TABLE[i-1][j - Weight[i]].used[k];
					}
					DP_TABLE[i][j].used[i] = 1;
				}

			}
		}
	}

	//結果の表示
	for (j = 0; j <= MAX_WAIT; j++) {
		printf("ナップサック容量:%d\n", j);
		printf("価値:%d\n", DP_TABLE[N - 1][j].value);
		for (k = 0; k < N; k++) {
			if (DP_TABLE[N - 1][j].used[k] == 1) {
				printf("%d:ON  ", k);
			}
			else {
				printf("%d:OFF ", k);
			}
		}
		printf("\n\n");
	}
	
}