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


//card tray object
int CardTray[N_CARDSET*N_CARD]; //int cardtray라는 배열 
int cardIndex = 0;	//얘는 그냥 변수						


//player info
int dollar[N_MAX_USER];					//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

//some utility functions

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
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	
		
	if(i/13==0)
		printf("♣");
	else if(i/13==1) 
		printf("◆");
	else if(i/13==2)
		printf("♥"); 
	else if(i/13==3)
		printf("♠");
		
	if(i%13==0)
		printf("A");
	else if(i%13==1)
		printf("2");
	else if(i%13==2)
		printf("3");
	else if(i%13==3)
		printf("4");
	else if(i%13==4)
		printf("5");
	else if(i%13==5)
		printf("6");
	else if(i%13==6)
		printf("7");
	else if(i%13==7)
		printf("8");
	else if(i%13==8)
		printf("9");
	else if(i%13==9) 
		printf("10");
	else if(i%13==10)
		printf("J");
	else if(i%13==11)
		printf("Q");
	else if(i%13==12)
		printf("K");

	
	return 0;
	}
}


//card array controllers -------------------------------

//mix the card sets and put in the array
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
	
}

//get one card from the tray
int pullCard(void) {
	//카드를 하나씩 꺼내주는 함수 
}


//playing game functions -----------------------------

//player settiing

int configUser(void) {
	
	do
	{
		printf("Input the number of players(MAX:5)\n");
		scanf("%d",&n_user);
	}while(n_user>=6||n_user==0);
	
	
}


//betting
int betDollar(void)
{
	int i;
	for(i=0;i<N_MAX_USER;i++)
	{
	do{	
	printf("How much do you want to bet?\n");//라고 물었을 때  그 플레이어가 갖고있는 돈보다 적거나같은금액을 입력해야만 한다. 
	scanf("%d",&dollar[N_MAX_USER]);
	}while(dollar[N_MAX_USER]<입력받은값) 
	}
	
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();//카드를 나눠주는 함수를 짜면 숫자가 하나가 저장되니까, 
		cardhold[i][1] = pullCard();//i가 0이면 내카드고,,2면 player1의 카드고,, 처음에 두장씩 나눠주니깐 이렇게 한번 돌면  
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	
}

int getAction(void) {
	
}


void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);//
	printf("\t ::: ");
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	
}

int checkResult() {
	int i;
	printf("---------------------ROUND i result is...",roundcounter)
}

int checkWinner() {
	
}



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		for () //each player
		{
			while () //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
