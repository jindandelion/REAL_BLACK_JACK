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
int cardnum;
int cardnumcnt;//카드트레이에서 0부터 N_CARDSET*N_CARD-1까지 의 배열 요소 중 몇번째 까지 썼는지 카운터해주는 변수. 

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
	}while(/*********************나중에 해라!!!!!*****************************/)
	
	cardSum[i]=sum;
	
	printf("sum=%d ",cardSum[i]);
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
	}//배열 선언 후 각 배열에 0~51숫자를 저장해주었다. 
		
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
int puca;//pullCard함수에서 반환 값이 하나 나갈때마다 배열의 다음 값이 나갈 수 있게해주는 변수를 전역변수로 설정해 주엇다. 
//get one card from the tray
int pullCard(void) {	//카드를 하나씩 꺼내주는 함수 
	
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
		//-1이 들어가있으면 사용자가 숫자아닌걸 넣은거니까.. 내가 원하는 값이 아니면 다시 넣어라ㅏ! 다시 넣어라 출력..경고메세지 넣어. 
	}while(n_user>=6||n_user<=0);
	
	
}


//betting
int betDollar(void)/************************End*****************************/
{
	int i;
	int putbet;//putbet변수는 컴퓨터player의 배팅액이 랜덤으로 배팅될때, 컴퓨터가 알맞게 배팅할 수 있도록 도와주는 변수이다. 
	
	printf("Your betting (total:$%d)\n",dollar[0]); 
	/*scanf("%d",&bet[0]);*/
	do{
		bet[0]=getIntegerInput();
		if(bet[0]>dollar[0])
			printf("You only have %d$!!!Bet Again!!!\n",dollar[0]);
	}while(bet[0]<=dollar[0]);
		
	/*변수의 논리*/
	/*player가 가진 값이 x보다 작으면 어떻게 해라*/ 
	for(i=1;i<n_user;i++)
	{
		if(dollar[i]>N_MAX_BET)
			putbet=N_MAX_BET;//Player의 자본이 N_MAX_BET보다  많이 남아있으면 Player의 배팅액을 랜덤으로 설정할때 N_MAX_BET 밑으로 설정한다는 뜻
			bet[i]=rand()%putbet+1;  
		else//Player의 자본이 N_MAX_BET보다 작게 남아 있으면 남은 모든 금액을 올인하겠다!
			bet[i]=dollar[i]; 
			//(0<putbet||putbet<dollar[i]);/**이거 약간 putbet이 0보다 크고 dollar[i]즉 가진 자본만큼 보단 작야아된다고 하고싶은데 이게 맞나*/
			//bet[i]=rand()%putbet+1;
			printf("Player%d bets $%d (out of:$%d)\n",i,bet[i],dollar[i]); 
	}
	
	/*for(i=1;i<n_user,i++)//int n_user에 몇명이서 플레이할건지 입력 받았는데 그냥 이렇게 쓰면 되나? 
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
		cardhold[i][0] = pullCard();//첫번째 카드.카드를 나눠주는 함수를 짜면 숫자가 하나가 저장되니까,
		/*****************************************************************
		pullcard가 숫자 내보내면 cardhold에 숫자가 저장되겠지?
		그럼 printcard(cardhold[][])이런식으로 해서 카드 프린트 하는거 ㅇㅎ 
		********************************************************************/
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
		//카드를 한장 더 나눠줌 
		
	else
		
		/*다음 turn으로 넘어가*/ 
	
	
		
	
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
	
	if(sum==21)//x는 카드 숫자의  합 
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
	//int Winner라는 전역변수를 세워주고 Winner=0,1,
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
	} while (gameEnd == 0);//이거 한번 돌때마다 roundIndex++해줘야 되는데.. 하ㅏㅏㅏ 
	
	checkWinner();
	
	
	return 0;
}
