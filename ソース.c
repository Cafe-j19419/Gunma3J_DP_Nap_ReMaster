#include<stdio.h>

#define N 4
#define MAX_WAIT 12
typedef struct state {
	int used[N];//0����Ȃ��A1�����
	int value;
}state;

int main() {
	int i, j, k;
	int tmp_value;
	state DP_TABLE[N][MAX_WAIT + 1];
	//�ו��̏�����1kg������̉��l���������Ƀ\�[�g�ςłȂ��Ɠ��삵�Ȃ��̂Œ��ӂ���
	int Weight[N] = { 1, 2, 5, 4 };//0,1,...,(N-1)�Ԗڂ̉ו��̏d��
	int Value[N] = { 3000, 2000, 4000, 3000 };//0,1,...,(N-1)�Ԗڂ̉ו��̉��l
	//DP�e�[�u��������
	for (i = 0; i < N; i++) {
		for (j = 0; j <= MAX_WAIT; j++) {
			DP_TABLE[i][j].value = 0;
			for (k = 0; k < N; k++) {
				DP_TABLE[i][j].used[k] = 0;
			}
		}
	}
	//�����������܂�
	
	//�ו� i ���珇�Ƀi�b�v�T�b�N�e�� j �ŉו����l�߂Ă݂�
	for (i = 0; i < N; i++) {
		for (j = 1; j <= MAX_WAIT; j++) {
			//0�Ԗڂ̓����l���Ă���A�������́A���l���Ă���ו����i�b�v�T�b�N�ɓ���Ȃ��Ƃ��͗�O��������������
			if (i == 0 || j < Weight[i]) {
				if (i == 0) {//0�Ԗڂ̓������ō\�����Ȃ��Ă͂Ȃ�Ȃ��Ƃ�
					if (j < Weight[i]) {
						DP_TABLE[i][j].value = 0;
						DP_TABLE[i][j].used[0] = 0;
					}
					else {
						DP_TABLE[i][j].value = Value[0];
						DP_TABLE[i][j].used[0] = 1;
					}

				}
				else {//i-1�Ԗڂ̉ו��܂łō\�������d��j�̂��̂������p����������Ȃ��Ƃ�
					DP_TABLE[i][j].value = DP_TABLE[i - 1][j].value;
					for (k = 0; k < N; k++) {
						DP_TABLE[i][j].used[k] = DP_TABLE[i - 1][j].used[k];
					}
				}
			}
			else {//��O�����łȂ��A��ʏ����̂Ƃ�
				
				//����if���ŉ��l��r
				if (DP_TABLE[i - 1][j].value > DP_TABLE[i - 1][j-Weight[i]].value+Value[i]) 
				{//i�Ԗڂ̉ו����������ɏd��j�̎����D�G�ȃP�[�X
					DP_TABLE[i][j].value = DP_TABLE[i - 1][j].value;
					for (k = 0; k < N; k++) {
						DP_TABLE[i][j].used[k] = DP_TABLE[i - 1][j].used[k];
					}
				}
				else 
				{//i�Ԗڂ̉ו��������ďd��j�̎����D�G�ȃP�[�X
					DP_TABLE[i][j].value = DP_TABLE[i - 1][j - Weight[i]].value + Value[i];
					for (k = 0; k < N; k++) {
						DP_TABLE[i][j].used[k] = DP_TABLE[i-1][j - Weight[i]].used[k];
					}
					DP_TABLE[i][j].used[i] = 1;
				}

			}
		}
	}

	//���ʂ̕\��
	for (j = 0; j <= MAX_WAIT; j++) {
		printf("�i�b�v�T�b�N�e��:%d\n", j);
		printf("���l:%d\n", DP_TABLE[N - 1][j].value);
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