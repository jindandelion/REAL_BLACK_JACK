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


//card tray object
int CardTray[N_CARDSET*N_CARD]; 
int cardIndex = 0;							
int cardnum;

int cardcnt[N_MAX_USER]={1,1,1,1,1};//Variables that count the number of cards each player has.

//player info
int dollar[N_MAX_USER]={50,50,50,50,50};//dollars that each player has. At the beginning of the game, each player's money was initialized at $50.
int user;
int n_user;								//number of users

//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER]={0,0,0,0,0};					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

//some utility functions
//
int roundIndex=1;
//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)
int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}

int main(int argc, char *argv[]) {
	int roundIndex = 1;
	int max_user;
	int i;
	int j;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();//Input how many players play game.
	printf("-->Card is mixed and put into the tray\n\n");

	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		//Each time Round starts anew, the variable cardcnt, which refers to the number of cards each player has, is reset to 2.
		for(i=0;i<=n_user;i++)
		{
			cardcnt[i]=2;
		}	
		
		for(i=0;i<=n_user;i++)
		{
			cardSum[i]=0;
		}

			
		printf("--------------------------------------------\n");
		printf("----------Round %d (Card Index:%d)-----------\n",roundIndex,cardIndex);
		printf("--------------------------------------------\n");

		printf("-----------------BETTING STEP---------------\n");
		betDollar();
		
		printf("--------------------------------------------\n\n");
		printf("----------------CARD OFFERING---------------\n");
		offerCards(); //1. give cards to all the players,//offering initial 2 cards
		
		if(cardIndex>N_CARDSET*N_CARD)
		{
			gameEnd=1;
			break;
		}
		printCardInitialStatus();//print card initial status();
		
		printf("\n---------------- GAME start ----------------\n");
		//user turn
		printf(">>> My Turn!-------------------\n");
		printUserCardStatus(0,cardcnt[0]);//first, print initial card.
		
	
		
		int gAresult;//Variable that stored getAction Result.
		int gAPresult;//Variable that stored getActionPlayer's Result.
		int cardsumofP;//Stored cardsum of Players
		int cardsumofU;//Stored cardsum of User
		
		while(1)
		{	
		
			cardSum[0]=0;
			//gAresult=getAction();
			
			calcardsum(0);
			printf("sum: %d ",cardSum[0]);
			
			if(cardSum[0]>21)
			{
				printf("DEAD!! overflow!\n");
				break;
			}
			else if(cardcnt[0]==2&&cardSum[0]==21)
			{
				printf("BLACKJACK!!\n");
				printf("sum: %d",cardsumofU);
				break;
			}
			gAresult=getAction();
			
			if(gAresult==0)
			{	
				printf("GO!\n");
				cardhold[0][cardcnt[0]]=pullCard();
				cardcnt[0]++; 
				printUserCardStatus(0,cardcnt[0]);
				if(cardIndex>N_CARDSET*N_CARD)
				{
					gameEnd=1;
					break;
				}
			}
			else if(gAresult==1)
			{
				printf("STOP!\n");
				printf("sum: %d ",cardSum[0]);
				break;
			}
			
		}
		
		//each player's turn
		
		for (i=1;i<n_user;i++) //each player turn start!
		{
			printf("\n\n>>> Player %d Turn!-------------------\n",i);
			
			while(1)
			{
				//gAPresult=getActionPlayer(i);
				printUserCardStatus(i,cardcnt[i]);
				cardSum[i]=0;
				calcardsum(i);//Stored cardsum of Player's
				printf("sum : %d  ",cardSum[i]);
				
				if(cardSum[i]>21)
				{
					printf("DEAD(overflow)\n!");
					break;
				}
				else if(cardSum[i]<17)
				{
					printf("GO!\n");
					cardhold[i][cardcnt[i]]=pullCard();
					if(cardIndex>N_CARDSET*N_CARD)
					{
						gameEnd=1;
						break;
					}
					cardcnt[i]++;
				}
				else if(cardSum[i]==21&&cardcnt[i]==2)
				{
					printf("BLACKJACK!\n");
					break;
				}
				else if(cardSum[i]>=17)
				{
					printf("STOP!\n");
					break;
				}
				
			}
			
			
		}
		//Server's turn.
		printf("\n\n>>> Server's Turn!-------------------\n");
		
		while(1)
			{
				printUserCardStatus(n_user,cardcnt[n_user]);
				cardSum[n_user]=0;
				calcardsum(n_user);//Stored cardsum of Player's
				printf("sum : %d  ",cardSum[n_user]);
				
				if(cardSum[n_user]>21)
				{
					printf("DEAD(overflow)\n!");
					break;
				}
				else if(cardSum[n_user]<17)
				{
					printf("GO!\n");
					cardhold[n_user][cardcnt[n_user]]=pullCard();
					if(cardIndex>N_CARDSET*N_CARD)
					{
						gameEnd=1;
						break;
					}
					cardcnt[n_user]++;
				}
				else if(cardSum[n_user]==21&&cardcnt[n_user]==2)
				{
					printf("BLACKJACK!\n");
					break;
				}
				else if(cardSum[n_user]>=17)
				{
					printf("STOP!\n");
					break;
				}
				
			}	
		
		for(i=0;i<n_user;i++)
		{
			if(dollar[i]==0)
			{
				gameEnd=1;
				printf("Player %d bankrupt(Player 0 is Y0u)\n",i);
				
			}
			
		}
			
		checkResult(n_user);
		
		roundIndex++;
		
		if(gameEnd==1)
			break;
	} while (1);
	
	checkWinner();
	
	
	return 0;
}
