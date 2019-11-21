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

//A function that tells the result of the round.
int checkResult(int user) {
	
	int i;
	int blackjack;//if server is blackjack, return 1; so not blackjack player change lose.
	
	if(cardSum[user]>21)//cardSum is array that means sum of each card that holded each player.
		printf("[[[[[Server Result is .....overflow!!]]]]]\n");
		
	else if(cardcnt[user]==2&&cardSum[user]==21) 
	{
		printf("[[[[[Server Result is .....Black Jack!!]]]]]\n");
		blackjack=1;
	}
				
	else
		printf("[[[[[Server Result is .....Sum: %d!!]]]]]\n",cardSum[n_user]);
		
		
	printf("\n\n------------ROUND%d's result is...------------\n\n",roundIndex);

	/*--------------This is Check the User's REsult------------------*/
	if(cardSum[0]==21&&cardcnt[0]==2)//if player is blackjack,
		{
			dollar[0]=dollar[0]+(bet[0]*2);
			printf("->Your Result: BLACKJACK! Congratulations!(sum:%d)-->$%d\n",cardSum[0],dollar[0]);
		}
		
	else if(cardSum[n_user]>21&&cardSum[0]<22)//if dealer is overflow.
		{
			dollar[0]=dollar[0];
			printf("->Your Result: WIN!! Server is overflow. (sum:%d)-->$%d\n",cardSum[0],dollar[0]);
		}
	
	else if(cardSum[user]==21&&cardcnt[user]==2&&cardSum[0]!=21&&cardcnt[0]!=2||blackjack==1)//If the dealer is blackjack, player loses the betting amount.
		{
			dollar[0]=dollar[0]-bet[0];
			printf("->Your Result: Lose! Server is BLACKJACK! (sum:%d)-->$%d\n",cardSum[0],dollar[0]);
		}

	else if(cardSum[0]>cardSum[user]&&cardSum[0]<=21)//if user is win
		{
			dollar[0]=dollar[0]+bet[0];
			printf("->Your Result: WIN! (sum:%d)-->$%d\n",cardSum[0],dollar[0]);
		}
	/*------------This sentence check player's result----------------*/
	for(i=1;i<user;i++)
	{
		printf("\n");
		
		if(cardSum[i]==21&&cardcnt[i]==2)
		{
			dollar[i]=dollar[i]+(bet[i]*2);
			printf("->%d'th Player's Result: Black Jack! (sum:%d) --> $%d \n",i,cardSum[i],dollar[i]);
		}
		//server is overflow but, player not overflow.
		else if(cardSum[i]>21)
		{
			dollar[i]=dollar[i]-bet[i];
			printf("->%d'th Player's Result:Lose!! overflow (sum:%d) --> $%d \n",i,cardSum[i],dollar[i]);
			}	
		else if(cardSum[user]>21)
		{
			dollar[i]=dollar[i]+bet[i];
			printf("->%d'th Player's Result: Win! Server is overflow! (sum:%d) --> $%d \n",i,cardSum[i],dollar[i]);
		}
			
		else if(cardSum[user]==21&&cardcnt[user]==2)
		{
			dollar[i]=dollar[i]-bet[i];
			printf("->%d'th Player's Result: lose! Server is BLACKJACK! (sum:%d) --> $%d \n",i,cardSum[i],dollar[i]);
		}	
		
		else if(cardSum[user]<=cardSum[i]&&cardSum[i]<=21)
		{
			dollar[i]=dollar[i]+bet[i];
			printf("->%d'th Player's Result: WIN! (sum:%d) --> $%d \n",i,cardSum[i],dollar[i]);
		}	
		printf("\n");
			
	}
}	

//Check The final WInner!
int checkWinner() {
	
	int i;
	int k;
	int winner;
	int maxdollar;
	
	printf("Game End!! Your money : $%d,",dollar[0]);
	
	printf("Player's money:'");
	for(i=1;i<n_user;i++)
	{
		printf("$%d  ",dollar[i]);
	}
	//Check who is winner.
	for(i=0;i<n_user;i++)
	{
		for(k=0;k<n_user;k++)
		{
			if(dollar[i]<dollar[k])
			{
				maxdollar=dollar[k];
				winner=k;
			}
				
		}
		if(winner==0)
		{	
			printf("You Win!!\n");
		}
		else
		{
			printf("Player %d Win.\n",winner);
		}
	
	}
	
}


