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
int CardTray[N_CARDSET*N_CARD]; 
int cardIndex = 0;	//얘는 그냥 변수						


//player info
int dollar[N_MAX_USER];					//dollars that each player has
{	
	int k;
	for(k=0;k<n_user;k++)
	{
		dollar[k]=50;	
	} 
	printf("%d$",dollar[i]);
	   
}

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
	
	int sum=0;

	switch(cardnum)
	{
		case 0;
			cardnum=1
		case 10,11,12;
			cardnum=10;
		default;
			cardnum=cardnum+1;
		
	}
	do
	{
		sum=cardnum+sum;
	}while(/*********************나중에 해라!!!!!*****************************/)
	
	printf("sum=%d ",cardnum);
}

//print the card information (e.g. DiaA)
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


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	
	int i;
	 
	int Cardtray[N_CARDSET*N_CARD];
	for(i=0;i<N_CARDSET*N_CARD;i++)
	{
		Cardtray[i]=i;
	}//배열 선언 후 각 배열에 0~51숫자를 저장해주었다. 
		
	int randnum1=rand()%52;
	int randnum2=rand()%52;
	
	srand(time(NULL));
	for(i=0;i<N_CARDSET*N_CARD;i++)
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
		//scanf("%d",&n_user);
		n_user=getIntegerInput();
		//-1이 들어가있으면 사용자가 숫자아닌걸 넣은거니까.. 내가 원하는 값이 아니면 다시 넣어라ㅏ! 다시 넣어라 출력..경고메세지 넣어. 
	}while(n_user>=6||n_user==0);
	
	
}


//betting
int betDollar(void)
{
	int i;
	int putbet;
	
	printf("Your betting (total:$%d)\n",dollar[0]); 
	/*scanf("%d",&bet[0]);*/
	bet[0]=getIntegerInput();
	/*변수의 논리*/
	/*player가 가진 값이 x보다 작으면 어떻게 해라*/ 
	for(i=1;i<n_user;i++)
		if(dollar[i]>5)
			putbet=5;
		else
			(0<putbet||putbet<dollar[i]);/**이거 약간 putbet이 0보다 크고 dollar[i]즉 가진 자본만큼 보단 작야아된다고 하고싶은데 이게 맞나*/
			 
		bet[i]=rand()%putbet+1;
	
	for(i=1;i<n_user,i++)//int n_user에 몇명이서 플레이할건지 입력 받았는데 그냥 이렇게 쓰면 되나? 
	{
		printf("Player%d bets $%d (out of:$%d)\n",i,bet[i],dollar[i]); 
	}	
	
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();//첫번째 카드.카드를 나눠주는 함수를 짜면 숫자가 하나가 저장되니까, 
	}
	for (i=0;i<n_user;i++)
	{
		cardhold[i][1] = pullCard();//i가 0이면 내카드고,,2면 player1의 카드고,, 처음에 두장씩 나눠주니깐 이렇게 한번 돌면  
	}

	//2. give two card for the dealer(operator)
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	
}

int getAction(void) {
	int gostop;
	printf("Action? (0-go, other-stay)");
	scanf("%d",&gostop);
	
	if(gosotop=0);
		pullCard();
	else
		/*다음 turn으로 넘어가*/ 
	
	
		
	
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
	printf("-->Card is mixed and put into the tray\n\n");
	
	printf("--------------------------------------------\n");
	printf("----------Round %d (CardIndex:%d)-----------\n",roundIndex,cardIndex);
	printf("--------------------------------------------\n");

	printf("-----------------BETTING STEP---------------\n");
	betDollar();
	

	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		printf() 
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
	} while (gameEnd == 0);//이거 한번 돌때마다 roundcnt++해줘야 되는데.. 하ㅏㅏㅏ 
	
	checkWinner();
	
	
	return 0;
}
