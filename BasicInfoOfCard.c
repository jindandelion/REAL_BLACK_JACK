#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50//ó������ 50���� �ʱ�ȭ�� �������� ������ ����Ǹ鼭 �ٲ�ϴ�! 


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30//�迭�� ũ�⸦ �����ڷ� ������� ��ȣ����� ���� 

void printCard(int cardnum) {
		
	if(cardnum/13==0)
		printf("��");
	else if(cardnum/13==1) 
		printf("��");
	else if(cardnum/13==2)
		printf("��"); 
	else if(cardnum/13==3)
		printf("��");
		
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
	}//�迭 ���� �� �� �迭�� 0~51���ڸ� �������־���. 
		
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
	
int puca;//pullCard�Լ����� ��ȯ ���� �ϳ� ���������� �迭�� ���� ���� ���� �� �ְ����ִ� ������ ���������� ������ �־���. 
//get one card from the tray
int pullCard(void) {	//ī�带 �ϳ��� �����ִ� �Լ� 
	
	int result;
	result=CardTray[puca];
	puca++;
	cardIndex++;
	return result;
	
}

















