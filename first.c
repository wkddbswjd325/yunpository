#include <stdio.h>
#include <stdlib.h>
//test로 추가dfsfwef

int swit[10][5] = { {0,1,2,INT_MAX,INT_MAX}, {3,7,9,11,INT_MAX}, {4,10,14,15,INT_MAX},
					{0,4,5,6,7}, {6,7,8,10,12}, {0,2,14,15,INT_MAX},
					{3,14,15,INT_MAX,INT_MAX}, {4,5,7,14,15}, {1,2,3,4,5}, {3,4,5,9,13} };

// 모든 시계가 12시를 가리키고 있는지 확인하는 함수
int checkClock(int* pClock) {
	int i;

	for (i = 0; i < 16; i++) {
		if (*(pClock+i) != 0)
			return 0;
	}

	return 1;
}
// 스위치랑 pClock 매개로 받아서 횟수값 바꾸는 함수 --하고 -1되면 3으로 대치
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

// 스위치랑 시계랑 맞는거
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


// 스위치 선택해서 시계 동기화 함수
void synchronized(int* pClock) {
	int s;
	int bestSwitch = 0; // 0-9번의 스위치중 최적의 스위치
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

		switch (clock[i]) {   // 시계방향으로 돌려야 할 횟수를 저장
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
