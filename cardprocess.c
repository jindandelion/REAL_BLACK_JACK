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
//card processing functions ---------------
//card tray object
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
//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) { 
	
	switch(cardnum%13)
	{
		case 0:
			cardnum=11;
			break;
			
		case 10:
		case 11:
		case 12:
			cardnum=10;
			break;
			
		default:
			cardnum=(cardnum%13)+1;
			break;
		
	}

}
//A function that calculates the sum of the cards.
int calcardsum(int user){
	//getCardNum(int cardnum)
	
	int i;
	
	for(i=0;i<cardcnt[user];i++)
	{	
		cardSum[user]=cardSum[user]+getCardNum(cardhold[user][i]);
	}
	
	
	return cardSum[user];
} 
	
//print the card information (e.g. DiaA)
void printCard(int cardnum) { 
	
	if(cardnum/13==0)
		printf("¢À");
	else if(cardnum/13==1) 
		printf("¡ß");
	else if(cardnum/13==2)
		printf("¢¾"); 
	else if(cardnum/13==3)
		printf("¢¼"); 
		
	switch(cardnum%13)
	{
		case 0:
			printf("A ");
			break; 
			
		case 10:
			printf("J ");
			break;
			
		case 11:
			printf("Q ");
			break;
		
		case 12:
			printf("K ");
			break;
			
		default:
			printf("%d ",(cardnum%13)+1);
			break;
	}
	
}



