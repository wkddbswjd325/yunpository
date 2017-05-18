#include <stdio.h>
#include <stdlib.h>
//test�� �߰�dfsfwef

int swit[10][5] = { {0,1,2,INT_MAX,INT_MAX}, {3,7,9,11,INT_MAX}, {4,10,14,15,INT_MAX},
					{0,4,5,6,7}, {6,7,8,10,12}, {0,2,14,15,INT_MAX},
					{3,14,15,INT_MAX,INT_MAX}, {4,5,7,14,15}, {1,2,3,4,5}, {3,4,5,9,13} };

// ��� �ð谡 12�ø� ����Ű�� �ִ��� Ȯ���ϴ� �Լ�
int checkClock(int* pClock) {
	int i;

	for (i = 0; i < 16; i++) {
		if (*(pClock+i) != 0)
			return 0;
	}

	return 1;
}
// ����ġ�� pClock �Ű��� �޾Ƽ� Ƚ���� �ٲٴ� �Լ� --�ϰ� -1�Ǹ� 3���� ��ġ
void change(int s, int sSize, int* pClock) {
	int i;
	int c;

	for (i = 0; i < sSize; i++) {
		c = swit[s][i];
		(*(pClock + c))--;
		if (*(pClock + c) == -1)
			*(pClock + c) = 3;
	}
}

// ����ġ�� �ð�� �´°�
int f_overlap(int s, int* pClock) {
	int i;
	int result = 0;
	int c;

	for (i = 0; i < 5; i++) {
		c = 0;
		if (swit[s][i] < 16) {
			c = swit[s][i];
			if (*(pClock + c) > 0)
				result++;
		}
	}
	
	return result;
}


// ����ġ �����ؼ� �ð� ����ȭ �Լ�
void synchronized(int* pClock) {
	int s;
	int bestSwitch = 0; // 0-9���� ����ġ�� ������ ����ġ
	int overlap = 0;
	int result;

	int bestSwitchSize = 0;
	int sSize;

	while (bestSwitchSize < 5) {
		if (swit[bestSwitch][bestSwitchSize] >= 16)
			break;

		bestSwitchSize++;
	}

	for (s = 0; s < 10; s++) {
		sSize = 0;

		result = f_overlap(s, pClock);
		
		if (result > overlap) {
			overlap = result;
			bestSwitch = s;
		}
		else if (result == overlap) {
			while (sSize < 5) {
				if (swit[s][sSize] >= 16)
					break;

				sSize++;
			}

			if (sSize > bestSwitchSize) {
				bestSwitchSize = sSize;
				bestSwitch = s;
			}
			
		}
	} 

	change(bestSwitch, bestSwitchSize, pClock);

}


void main()
{
	int i;
	int clock[16];
	int count = 0;
	
	for (i = 0; i < 16; i++) {
		scanf("%d", &clock[i]);

		switch (clock[i]) {   // �ð�������� ������ �� Ƚ���� ����
		case 3:
			clock[i] = 3;
			break;
		case 6:
			clock[i] = 2;
			break;
		case 9:
			clock[i] = 1;
			break;
		case 12:
			clock[i] = 0;
			break;
		}
	}

	while (1) {
		if (checkClock(clock) == 1)
			break;

		synchronized(clock);
		count++;
	}

	printf("---------------------------------------------\n%d\n", count);
}
