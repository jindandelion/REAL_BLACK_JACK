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
//playing game functions -----------------------------

//player settiing

//Input how many players play game.
int configUser(void) {
	
	do
	{
		printf("Input the number of players(MAX:%d): ",N_MAX_USER);
		n_user=getIntegerInput();
		if(n_user>=6||n_user<=0)
			printf("***Set the number of players at least 1 to %d or less.***",N_MAX_USER); 
	
	}while(n_user>=6||n_user<=0);
		
}
	
//betting
int betDollar(void)
{
	int i;
	 
	
	printf("Your betting (total:$%d): ",dollar[0]); 
	
	do{
		bet[0]=getIntegerInput();
		
		if(bet[0]>dollar[0])
			printf("You only have %d$!!!Bet Again!!!\t:::",dollar[0]);
			
	}while(bet[0]>dollar[0]);
		
	for(i=1;i<n_user;i++)
	{
		if(dollar[i]>N_MAX_BET)
		{
			bet[i]=rand()%N_MAX_BET+1;  
		}
		else//if players money left less Max_bet_dollar
		{
			bet[i]=(rand()%dollar[i])+1;
		}
			printf("Player%d bets $%d (out of:$%d)\n",i,bet[i],dollar[i]); 
	}
	
	
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
	}
	for (i=0;i<n_user;i++)
	{
		cardhold[i][1] = pullCard();  
	}

	//2. give two card for the dealer(operator)
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	int i;
	//Print dealer's card
	printf("-->Server       :");
	printf("X ");
	printCard(cardhold[n_user][1]); 
	printf("\n");
	//Print user's card
	printf("-->You          :");
	printCard(cardhold[0][0]);
	printCard(cardhold[0][1]);
	printf("\n");
	//Print computer player's card
	for(i=1;i<n_user;i++)
	{
		printf("-->Player %d     :",i);
		printCard(cardhold[i][0]);
		printCard(cardhold[i][1]);
		printf("\n");
	}
	
}

//Ask User's hope. Go or stop.
int getAction(void) {
	
	int gostop;
	
	printf("Action? (0-go, other-stay)\t");

	gostop=getIntegerInput();
	
	if(gostop==0)
	{
		return 0;
	}
	else
		return 1;	
	
}


//Decide computer player's go or stop.
int getActionPlayer(int n_user){

	//calcardsum(n_user);is The sum of the cards for the i-th user will be calculated.
	
	if(calcardsum(n_user)<=17)
	{
		cardcnt[n_user]++;
		return 0;
	} 
	else
	{
		return 1; 
	}
}

//Print Card Status
void printUserCardStatus(int user, int number) {
	 
	int i;
	
	printf("   -> card : ");
	
	for (i=0;i<number;i++)
	{
		printCard(cardhold[user][i]);
	}
	

	printf("\t ::: ");
}
