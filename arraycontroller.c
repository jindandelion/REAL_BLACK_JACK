#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

extern int CardTray[N_CARDSET*N_CARD]; 
extern int cardIndex;							
extern int cardnum;

extern int cardcnt[N_MAX_USER];//Variables that count the number of cards each player has.

//player info
extern int dollar[N_MAX_USER];//dollars that each player has. At the beginning of the game, each player's money was initialized at $50.
extern int user;
extern int n_user;								//number of users

//play yard information
extern int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
extern int cardSum[N_MAX_USER];					//sum of the cards
extern int bet[N_MAX_USER];						//current betting 
extern int gameEnd; 							//game end flag

//some utility functions
//
extern int roundIndex;

//card array controllers -------------------------------

//mix the card sets and put in the array
void swap(int* x,int* y)
{
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}

int mixCardTray(void) {
	
	int i=0;
	
	srand((unsigned)time(NULL));
	//After declare array, I stored 0~51number
	for(i=0;i<N_CARDSET*N_CARD;i++)
	{
		CardTray[i]=i;
	}
	
	for(i=0;i<N_CARDSET*N_CARD;i++)
		swap(&CardTray[i],&CardTray[rand()%(N_CARDSET*N_CARD)]);
}

//get one card from the tray
int pullCard(void) {
	
	int result;
	result=CardTray[cardIndex];
	cardIndex++;
	
	if(cardIndex>N_CARDSET*N_CARD)
		gameEnd==0;
		
	return result;
	
}


