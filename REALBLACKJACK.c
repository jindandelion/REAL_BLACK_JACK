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
extern int CardTray[N_CARDSET*N_CARD]; 
extern int cardIndex = 0;							
extern int cardnum;

extern int cardcnt[N_MAX_USER]={1,1,1,1,1};//Variables that count the number of cards each player has.

//player info
extern int dollar[N_MAX_USER]={50,50,50,50,50};//dollars that each player has. At the beginning of the game, each player's money was initialized at $50.
extern int user;
extern int n_user;								//number of users

//play yard information
extern int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
extern int cardSum[N_MAX_USER]={0,0,0,0,0};					//sum of the cards
extern int bet[N_MAX_USER];						//current betting 
extern int gameEnd = 0; 							//game end flag

//some utility functions
//
extern int roundIndex=1;
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


//card processing functions ---------------

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
			
		else if(cardSum[user]>21&&cardSum[i]<22)
		{
			dollar[i]=dollar[i]+(bet[i]*2);
			printf("->%d'th Player's Result: Win! Server is overflow! (sum:%d) --> $%d \n",i,cardSum[i],dollar[i]);
		}
			
		else if(cardSum[user]==21&&cardcnt[user]==2&&cardSum[i]!=21&&cardcnt[i]!=2)
		{
			dollar[i]=dollar[i]-bet[i];
			printf("->%d'th Player's Result: lose! Server is BLACKJACK! (sum:%d) --> $%d \n",i,cardSum[i],dollar[i]);
		}	
		
		else if(cardSum[user]<cardSum[i]&&cardSum[i]<=21)
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
		printf("$%d",dollar[i]);
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
		if(k==0)
		{	
			printf("You Win!!\n");
		}
		else
		{
			printf("Player %d Win.\n",k);
		}
	
	}
	
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
		for(i=0;i<n_user;i++)
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
		
			gAresult=getAction();
			
			cardsumofU=calcardsum(0);
			
			
			if(cardsumofU>21)
			{
				printf("DEAD!! overflow!\n");
				printf("sum: %d",cardsumofU);
				break;
			}
			else if(cardcnt[0]==2&&cardsumofU==21)
			{
				printf("BLACKJACK!!\n");
				printf("sum: %d",cardsumofU);
				break;
			}
			
			else if(gAresult==0)
			{	
				printf("GO!\n");
				cardhold[0][cardcnt[0]]=pullCard();
				cardcnt[0]++; 
				printUserCardStatus(0,cardcnt[0]);	
				printf("sum: %d",cardsumofU);
			}
			else if(gAresult==1)
			{
				printf("STOP!\n");
				printf("sum: %d ",cardsumofU);
				break;
			}
			
		}
		
		//each player's turn
		
		for (i=1;i<n_user;i++) //each player turn start!
		{
			printf("\n\n>>> Player %d Turn!-------------------\n",i);
			printUserCardStatus(i,cardcnt[i]); 
			
			while(1)
			{
				gAPresult=getActionPlayer(i);
				
				cardsumofP=calcardsum(i);//Stored cardsum of Player's
				
				if(gAPresult==0)
				{
					printf("GO!\n");
					cardhold[i][cardcnt[i]]=pullCard();
					cardcnt[i]++;
					printUserCardStatus(i,cardcnt[i]);
					printf("sum: %d",cardsumofP);
				}
				else if(cardsumofP>=17)
				{
					printf("STOP!\n");
					printf("sum: %d",cardsumofP);
					break;
				}
				else if(/*cardSum[i]*/cardsumofP>21)
				{
					printf("DEAD(overflow)\n!");
					printf("sum: %d",cardsumofP);
					break;
				}
				
			}
			
			
		}
		//Server's turn.
		printf("\n\n>>> Server's Turn!-------------------\n");
		
		printUserCardStatus(n_user,cardcnt[n_user]); 
		
		gAPresult=getActionPlayer(n_user);
		
		while(gAPresult==1)
		{	
			if(gAPresult==0)
			{
				printf("GO!");
				cardhold[n_user][cardcnt[n_user]]=pullCard();
				cardcnt[n_user]++;
				printUserCardStatus(n_user,cardcnt[n_user]);
				
			}
			else if(cardSum[n_user]>=17)
			{
				printf("STOP!");
				break;
			}
			else if(cardSum[n_user]>21)
			{
				printf("DEAD(overflow)!");
				break;
			}
			
				
		}	
		if(dollar[i]==0)
			gameEnd=0;
			
		checkResult(n_user);
		
		roundIndex++;
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
