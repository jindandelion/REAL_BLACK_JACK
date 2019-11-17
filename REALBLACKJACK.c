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
int cardnum;
int cardnumcnt;//ī��Ʈ���̿��� 0���� N_CARDSET*N_CARD-1���� �� �迭 ��� �� ���° ���� ����� ī�������ִ� ����. 

//player info
int dollar[N_MAX_USER]=50;//dollars that each player has. At the beginning of the game, each player's money was initialized at $50.

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
	
	int i;
	int sum;

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
	
	cardSum[i]=sum;
	
	printf("sum=%d ",cardSum[i]);
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
			break; 
			
		case 10:
			printf("J");
			break;
			
		case 11:
			printf("Q");
			break;
		
		case 12:
			printf("K");
			break;
			
		default:
			printf("%d",(cardnum%13)+1);
			break;
	}
	cardIndex++;
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
		
	int randnum1=rand()%N_CARDSET*N_CARD;
	int randnum2=rand()%N_CARDSET*N_CARD;
	
	srand(time(NULL));
	
	for(i=0;i<N_CARDSET*N_CARD;i++)
	{
		int temp;
		temp=Cardtray[randnum1];
		Cardtray[randnum1]=Cardtray[randnum2];
		Cardtray[randnum2]=temp;
	}
	
}
int puca;//pullCard�Լ����� ��ȯ ���� �ϳ� ���������� �迭�� ���� ���� ���� �� �ְ����ִ� ������ ���������� ������ �־���. 
//get one card from the tray
int pullCard(void) {	//ī�带 �ϳ��� �����ִ� �Լ� 
	
	return=Cardtray[puca];
	puca++;
	
}


//playing game functions -----------------------------

//player settiing

int configUser(void) {
	
	do
	{
		printf("Input the number of players(MAX:5)\n");
		//scanf("%d",&n_user);
		n_user=getIntegerInput();
		if(n_user>=6||n_user<=0)
			printf("***Set the number of players at least 1 to 5 or less.***\n"); 
		//-1�� �������� ����ڰ� ���ھƴѰ� �����Ŵϱ�.. ���� ���ϴ� ���� �ƴϸ� �ٽ� �־��! �ٽ� �־�� ���..���޼��� �־�. 
	}while(n_user>=6||n_user<=0);
	
	
}


//betting
int betDollar(void)/************************End*****************************/
{
	int i;
	int putbet;//putbet������ ��ǻ��player�� ���þ��� �������� ���õɶ�, ��ǻ�Ͱ� �˸°� ������ �� �ֵ��� �����ִ� �����̴�. 
	
	printf("Your betting (total:$%d)\n",dollar[0]); 
	/*scanf("%d",&bet[0]);*/
	do{
		bet[0]=getIntegerInput();
		if(bet[0]>dollar[0])
			printf("You only have %d$!!!Bet Again!!!\n",dollar[0]);
	}while(bet[0]<=dollar[0]);
		
	/*������ ��*/
	/*player�� ���� ���� x���� ������ ��� �ض�*/ 
	for(i=1;i<n_user;i++)
	{
		if(dollar[i]>N_MAX_BET)
			putbet=N_MAX_BET;//Player�� �ں��� N_MAX_BET����  ���� ���������� Player�� ���þ��� �������� �����Ҷ� N_MAX_BET ������ �����Ѵٴ� ��
			bet[i]=rand()%putbet+1;  
		else//Player�� �ں��� N_MAX_BET���� �۰� ���� ������ ���� ��� �ݾ��� �����ϰڴ�!
			bet[i]=dollar[i]; 
			//(0<putbet||putbet<dollar[i]);/**�̰� �ణ putbet�� 0���� ũ�� dollar[i]�� ���� �ں���ŭ ���� �۾߾Ƶȴٰ� �ϰ������ �̰� �³�*/
			//bet[i]=rand()%putbet+1;
			printf("Player%d bets $%d (out of:$%d)\n",i,bet[i],dollar[i]); 
	}
	
	/*for(i=1;i<n_user,i++)//int n_user�� ����̼� �÷����Ұ��� �Է� �޾Ҵµ� �׳� �̷��� ���� �ǳ�? 
	{
		printf("Player%d bets $%d (out of:$%d)\n",i,bet[i],dollar[i]); 
	}	*/
	
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();//ù��° ī��.ī�带 �����ִ� �Լ��� ¥�� ���ڰ� �ϳ��� ����Ǵϱ�,
		/*****************************************************************
		pullcard�� ���� �������� cardhold�� ���ڰ� ����ǰ���?
		�׷� printcard(cardhold[][])�̷������� �ؼ� ī�� ����Ʈ �ϴ°� ���� 
		********************************************************************/
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
	int i;
	
	printf("---------------CARD OFFERING---------------");
	printf("-->Server       :");
	printf("X ");
	printCard(cardhold[n_user][1]);
	printf("\n");
	printf("-->You          :");
	printCard(cardhold[0][0]);
	printCard(cardhold[0][1]);
	printf("\n");
	for(i=1;i<n_user;i++)
	{
		printf("-->Player %d     :",i);
		printCard(cardhold[i][0]);
		printCard(cardhold[i][1]);
	}
	
}

int getAction(void) {
	
	int gostop;
	printf("Action? (0-go, other-stay)");
	//scanf("%d",&gostop);
	gostop=getIntegerInput();
	
	if(gosotop=0);
		//ī�带 ���� �� ������ 
		
	else
		
		/*���� turn���� �Ѿ*/ 
	
	
		
	
}


void printUserCardStatus(int user, int cardcnt) {
	
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	
	int sum;
	sum=getCardNum();
	
	if(sum==21)//x�� ī�� ������  �� 
		printf("Black Jack! Congratulation, You Win!!\n");
	else if(sum>21)
		printf("DEAD[overflow!] (sum:%d)\n",sum);
	else
		printf("\n");
	
}

int checkResult() {
	int i;
	
	printf("------------ROUND%d's result is...------------",roundIndex);
	printf("->Your Result: %d (sum:%d)-->$%d\n",/*getCardNum()*/,dollar[0]);
	for(i=1;i<n_user;i++)
	{
		printf("->Your Result: %d (sum:%d)-->$%d\n",/*getCardNum()*/,dollar[i]);
	}
}	


int checkWinner() {
	
	int i;
	
	printf("Game End!! Your money : %d,",dollar[0]);
	printf("Player's money:'");
	for(i=1;i<n_user;i++)
	{
		printf("%d",dollar[i]);
	}
	//int Winner��� ���������� �����ְ� Winner=0,1,
}



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;

	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();
	printf("-->Card is mixed and put into the tray\n\n");
	
/*  printf("--------------------------------------------\n");
	printf("----------Round %d (CardIndex:%d)-----------\n",roundIndex,cardIndex);
	printf("--------------------------------------------\n");*/

	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
			
		printf("--------------------------------------------\n");
		printf("----------Round %d (Card Index:%d)-----------\n",roundIndex,cardIndex);
		printf("--------------------------------------------\n");

		printf("-----------------BETTING STEP---------------\n");
		betDollar();
		printf("--------------------------------------------\n"); 
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
		roundIndex++;
	} while (gameEnd == 0);//�̰� �ѹ� �������� roundIndex++����� �Ǵµ�.. �Ϥ����� 
	
	checkWinner();
	
	
	return 0;
}
