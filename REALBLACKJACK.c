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


//card tray object
int CardTray[N_CARDSET*N_CARD]; 
int cardIndex = 0;	//��� �׳� ����						


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
	}while(/*********************���߿� �ض�!!!!!*****************************/)
	
	printf("sum=%d ",cardnum);
}

//print the card information (e.g. DiaA)
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


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	
	int i;
	 
	int Cardtray[N_CARDSET*N_CARD];
	for(i=0;i<N_CARDSET*N_CARD;i++)
	{
		Cardtray[i]=i;
	}//�迭 ���� �� �� �迭�� 0~51���ڸ� �������־���. 
		
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
	
	//ī�带 �ϳ��� �����ִ� �Լ� 
}


//playing game functions -----------------------------

//player settiing

int configUser(void) {
	
	do
	{
		printf("Input the number of players(MAX:5)\n");
		//scanf("%d",&n_user);
		n_user=getIntegerInput();
		//-1�� �������� ����ڰ� ���ھƴѰ� �����Ŵϱ�.. ���� ���ϴ� ���� �ƴϸ� �ٽ� �־��! �ٽ� �־�� ���..���޼��� �־�. 
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
	/*������ ��*/
	/*player�� ���� ���� x���� ������ ��� �ض�*/ 
	for(i=1;i<n_user;i++)
		if(dollar[i]>5)
			putbet=5;
		else
			(0<putbet||putbet<dollar[i]);/**�̰� �ణ putbet�� 0���� ũ�� dollar[i]�� ���� �ں���ŭ ���� �۾߾Ƶȴٰ� �ϰ������ �̰� �³�*/
			 
		bet[i]=rand()%putbet+1;
	
	for(i=1;i<n_user,i++)//int n_user�� ����̼� �÷����Ұ��� �Է� �޾Ҵµ� �׳� �̷��� ���� �ǳ�? 
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
		cardhold[i][0] = pullCard();//ù��° ī��.ī�带 �����ִ� �Լ��� ¥�� ���ڰ� �ϳ��� ����Ǵϱ�, 
	}
	for (i=0;i<n_user;i++)
	{
		cardhold[i][1] = pullCard();//i�� 0�̸� ��ī���,,2�� player1�� ī���,, ó���� ���徿 �����ִϱ� �̷��� �ѹ� ����  
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
		/*���� turn���� �Ѿ*/ 
	
	
		
	
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
	} while (gameEnd == 0);//�̰� �ѹ� �������� roundcnt++����� �Ǵµ�.. �Ϥ����� 
	
	checkWinner();
	
	
	return 0;
}
