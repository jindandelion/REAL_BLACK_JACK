#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50//처음에는 50으로 초기화를 해줬지만 게임이 진행되면서 바뀝니다! 


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30//배열의 크기를 지시자로 만들어진 기호상수로 지정 

void printCard(int cardnum) {
		
	if(cardnum/13==0)
		printf("♣");
	else if(cardnum/13==1) 
		printf("◆");
	else if(cardnum/13==2)
		printf("♥"); 
	else if(cardnum/13==3)
		printf("♠");
		
	switch(cardnum%13)
	{
		case 0:
			printf("A");
		case 10:
			printf("J");
		case 11:
			printf("Q");
		case 12:
			printf("K");
		default:
			printf("%d",(cardnum%13)+1);
	}
	
	return 0;
	}
}

int mixCardTray(void) {
	
	int i;
	 
	int Cardtray[N_CARD];
	for(i=0;i<N_CARD;i++)
	{
		Cardtray[i]=i;
	}//배열 선언 후 각 배열에 0~51숫자를 저장해주었다. 
		
	int randnum1=rand()%52;
	int randnum2=rand()%52;
	
	srand(time(NULL));
	for(i=0;i<N_CARD;i++)
	{
		int temp;
		temp=Cardtray[randnum1];
		Cardtray[randnum1]=Cardtray[randnum2];
		Cardtray[randnum2]=temp;
	}
	
int puca;//pullCard함수에서 반환 값이 하나 나갈때마다 배열의 다음 값이 나갈 수 있게해주는 변수를 전역변수로 설정해 주엇다. 
//get one card from the tray
int pullCard(void) {	//카드를 하나씩 꺼내주는 함수 
	
	int result;
	result=CardTray[puca];
	puca++;
	cardIndex++;
	return result;
	
}

















