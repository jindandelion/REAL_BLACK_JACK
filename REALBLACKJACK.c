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
//int cardnumcnt;//ī��Ʈ���̿��� 0���� N_CARDSET*N_CARD-1���� �� �迭 ��� �� ���° ���� ����� ī�������ִ� ����. 
//int cardcnt;//�� player�� �����ִ� ī���� ������ ����� ���ִ� ����. 
int cardcnt[N_MAX_USER]={2,2,2,2,2};//Variables that count the number of cards each player has.

//player info
int dollar[N_MAX_USER]={50,50,50,50,50};//dollars that each player has. At the beginning of the game, each player's money was initialized at $50.
int user;
int n_user;								//number of users

//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

//some utility functions
//
int roundIndex;
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

	switch(cardnum%13)
	{
		case 0:
			/******************************************************************************************************/
			cardnum=11;//�Ǵ� 11 .���� �ȿ��� if�� �ᵵ �Ǵ°ǰ�? ���� if(CardSum+11>21) cardnum=1; else cardnum=11 
			/*********************************************************************************************************/
			break;
		case 10:
		case 11:
		case 12:
			cardnum=10;
			break;
		default:
			cardnum=cardnum+1;
		
	}
	//getcardnum���� return�� 11���ϰ�  ���࿡ CardSum�� 21�� ������ �׶� 10�� ���ִ°�. 
	return cardnum; 
	/*do
	{
		sum=cardnum+sum;
	}while(/*********************���߿� �ض�!!!!!*****************************/
	
	/*cardSum[i]=sum;
	
	printf("sum=%d ",cardSum[i]);*///-->�̰� �ٸ� �Լ����� �ص� ������ ������? 
}
/***************************************
int Card_Sum(cardnum){
	
	int i;
	int j;
	int sumofcard;
	
	if(j=1)
		for(i=1;i</********\;i++)
			getCardNum(cardhold[1][i]);
			sumofcard=sumofcard+getCardNum(cardhold[1][i]);
			******************************************************************************/
//A function that calculates the sum of the cards.
void calcardsum(int cardnum){
	
	int i;
	int sum;
	for(i=0;i<cardcnt;i++)
	{
		sum=sum+cardhold[cardnum][i];//���⿡ �ռ� PullCard�� ���� ��ȯ���� �������־����ϱ�
	}
	
	cardSum[cardnum]=sum;
	
	return 0;
} 
		
//print the card information (e.g. DiaA)
void printCard(int cardnum) { //cardnum�̶�� ���� �� Cardtray[i]��� �迭�� ���� �� �� 
	
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
	cardIndex++;//�̰� �̷��� �ϸ� �ȵ� �� ���⵵ �ϰ�.. 
	
}



//card array controllers -------------------------------

//mix the card sets and put in the array
void swap(int*x,int*y)
{
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}

int mixCardTray(void) {
	
	int i=0;
	
	srand((unsigned)time(NULL));
	
	for(i=0;i<N_CARDSET*N_CARD;i++)
	{
		CardTray[i]=i;
	}//�迭 ���� �� �� �迭�� 0~51���ڸ� �������־���. 
	
	for(i=0;i<N_CARDSET*N_CARD;i++)
		swap(&CardTray[i],&CardTray[rand()%(N_CARDSET*N_CARD)]);
	
	/*for(i=0;i<N_CARDSET*N_CARD;i++)
	{
		temp=Cardtray[randnum1];
		Cardtray[randnum1]=Cardtray[randnum2];
		Cardtray[randnum2]=temp;
	}*/
	
}
int puca;//pullCard�Լ����� ��ȯ ���� �ϳ� ���������� �迭�� ���� ���� ���� �� �ְ����ִ� ������ ���������� ������ �־���. 
//get one card from the tray
int pullCard(void) {
	
	int result;
	result=CardTray[puca];
	puca++;
	cardIndex++;
	return result;
	
}


//playing game functions -----------------------------

//player settiing

//Input how many players play game.
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
		{
				putbet=N_MAX_BET;//Player�� �ں��� N_MAX_BET����  ���� ���������� Player�� ���þ��� �������� �����Ҷ� N_MAX_BET ������ �����Ѵٴ� ��
			bet[i]=rand()%putbet+1;  
		}
		else//Player�� �ں��� N_MAX_BET���� �۰� ���� ������ ���� ��� �ݾ��� �����ϰڴ�!
		{
			bet[i]=dollar[i]; 
		}
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
		cardhold[i][0] = pullCard();
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
	}
	
}

//Ask User's hope. Go or stop.
int getAction(void) {
	
	int gostop;
	
	printf("Action? (0-go, other-stay)");
	//scanf("%d",&gostop);
	gostop=getIntegerInput();
	//while���� ������ �� gostop�� ���� 0�̸� while�ȿ� for�� �־ ����.  
	if(gostop==0)
	{
		cardcnt[0]++;
		return 0;
	}
	else
		return 1;	
	
}
//Decide computer player's go or stop.
int getActionPlayer(int n_user){
	
	calcardsum(n_user);//The sum of the cards for the i-th user will be calculated.
	
	if(calcardsum(n_user)<=17)
	{
		cardcnt[n_user]++;
		return 1;
	}//������ go��. 
	else
	{
		printf("STAY!\n"); 
		return 2; 
	}
		

//Print Card Status
void printUserCardStatus(int user, int cardcnt) {
	//�׳� cardcnt��� ������ �� �ʿ��Ѱ��� �𸣰�
	//������ �ִ� ī�� ������ŭ ����Ʈ�� ���࿩ �Ǵϱ�
	
	int i;
	
	printf("   -> card : ");
	
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);

	printf("\t ::: ");
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack

//Before Use calcStepResult function have to call calcardSum function. 
//Each time players finish their turn, print each step's results.
int calcStepResult(int user) {
	
	if(cardcnt==2&&calcardsum[user]==21)
		printf("Black Jack! Congratulation, You Win!!\n");
		
	else if(calcardsum[user]>21)
		printf("DEAD[overflow!] (sum:%d)\n",cardSum[user]);
		
	else
		printf("\n");
	
	//int cardSum[N_MAX_USER]���� �� �迭���� ������ ����. 
}
//A function that tells the result of the round.
int checkResult(int n_user) {
	
	int i;
	
	if(cardSum[n_user]>21)//cardSum is array that means sum of each card that holded each player.
		printf("[[[[[Server Result is .....overflow!!]]]]]\n");
	else if(cardcnt[n_user]==2&&cardSum[n_user==21])//������ ī�� ������ �� 21�̿����� �����̴ϱ� �� x[n_user][0]+x[n_user][1]==21 �̷��� �ٲ���� 
		printf("[[[[[Server Result is .....Black Jack!!]]]]]\n");
	else
		printf("[[[[[Server Result is .....%d!!]]]]]\n",cardSum[n_user]);
		
		
	printf("------------ROUND%d's result is...------------",roundIndex);
	
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
	
	else if(cardSum[n_user]==21&&cardcnt[n_user]==2&&cardSum[0]!=21&&cardcnt[0]!=2)//If the dealer is blackjack, player loses the betting amount.
		{
			dollar[0]=dollar[0]-bet[0];//�ٵ� player�� ���� �����̸� break;�ٸ� ������ ����߉�. 
			printf("->Your Result: Lose! Server is BLACKJACK! (sum:%d)-->$%d\n",cardSum[0],dollar[0]);
		}

	else if(cardSum[0]>cardSum[n_user]&&cardSum[0]<=21)//if user is win
		{
			dollar[0]=dollar[0]+bet[0];
			printf("->Your Result: WIN! (sum:%d)-->$%d\n",cardSum[0],dollar[0]);
		}
	
	for(i=1;i<n_user;i++)
	{
		printf("->%d'th Player's Result:",i);
		if(cardSum[i]==21&&cardcnt[i]==2)
		{
			dollar[i]=dollar[i]+(bet[i]*2);
			printf("Black Jack! (sum:%d) --> $%d \n",cardSum[i],dollar[i]);
		}
			
		else if(cardSum[n_user]>21&&cardSum[i]<22)
		{
			dollar[i]=dollar[i]+(bet[i]*2);
			printf(" Win! Server is overflow! (sum:%d) --> $%d \n",cardSum[i],dollar[i]);
		}
			
		else if(cardSum[n_user]==21&&cardcnt[n_user]==2&&cardSum[i]!=21&&cardcnt[i]!=2)
		{
			dollar[i]=dollar[i]-bet[i];
			printf("lose! Server is BLACKJACK! (sum:%d) --> $%d \n",cardSum[i],dollar[i]);
		}	
		
		else if(cardSum[n_user]<cardSum[i]&&cardSum[i]<=21)
		{
			dollar[i]=dollar[i]+bet[i];
			printf("WIN! (sum:%d) --> $%d \n",cardSum[i],dollar[i]);
		}	
		
			
	}
}	

//Check The final WInner!
int checkWinner() {
	
	int i;
	int k;
	int windollar;
	
	printf("Game End!! Your money : $%d,",dollar[0]);
	printf("Player's money:'");
	for(i=1;i<n_user;i++)
	{
		printf("$%d",dollar[i]);
	}
	//maxdollar[i]==dollar[i];
	for(i=0;i<n_user;i++)
	{
		for(k=0;k<n_user;k++)
		{
			if(dollar[i]<dollar[k])
				windollar=dollar[k];
		}
	}
	// max_dollar = dollar[i] max<dollar[i] max=dollar[i] i==0 i>1 pal--layer[]i
	
	/*f(dollar[1]<dollar[0]&&dollar[2]<dollar[0]&&dollar[3]<dollar[0]&&dollar[4]<dollar[0])
		printf("You Win!! Congratulations~"\n);
	
	if else(dollar[0]<dollar[1]&&dollar[2]<dollar[1]&&dollar[3]<dollar[1]&&dollar[4]<dollar[1])
		printf("Player 1's Win.\n");
		
	if else(dollar[0]<dollar[2]&&dollar[1]<dollar[2]&&dollar[3]<dollar[2]&&dollar[4]<dollar[2])
		printf("Player 2's Win.\n");//�ٵ� ���࿡ ������? ���� �ں���?
	
	if else(dollar[0]<dollar[3]&&dollar[2]<dollar[3]&&dollar[0]<dollar[3]&&dollar[4]<dollar[3])
		printf("Player 3's Win.\n"); 
	
	if else(dollar[0]<dollar[4]&&dollar[2]<dollar[4]&&dollar[3]<dollar[4]&&dollar[1]<dollar[4])
		printf("Player 4's Win.\n");
	
	if else(dollar[0]=<dollar[1]&&dollar[2]<dollar[1]&&dollar[3]<dollar[1]&&dollar[4]<dollar[1])
		printf("Player 1's Win.\n");*/
	//int Winner��� ���������� �����ְ� Winner=0,1,
}// max_dollar = dollar[i] max<dollar[i] max=dollar[i] i==0 i>1 pal--layer[]i



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	int k;
	int j;
	
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
		//Each time Round starts anew, the variable cardcnt, which refers to the number of cards each player has, is reset to 2.
		for(k=0;k<n_user;k++)
		{
			cardcnt[k]={2,2,2,2,2};
		}	

			
		printf("--------------------------------------------\n");
		printf("----------Round %d (Card Index:%d)-----------\n",roundIndex,cardIndex);
		printf("--------------------------------------------\n");

		printf("-----------------BETTING STEP---------------\n");
		betDollar();
		printf("--------------------------------------------\n\n");
		printf("----------------CARD OFFERING---------------\n");
		offerCards(); //1. give cards to all the players
		printCardInitialStatus();
		
		printf("\n---------------- GAME start ----------------\n");
		//user turn
		printf(">>>My Turn!----------\n");
		printUserCardStatus(0,cardcnt[0]);//ó�� ���� ������ ī�带 ����ش�. 
		getAction(); //Ask go or stop.
		while(getAction==1)
		{
			cardhold[0][cardcnt[0]]=pullCard();//I called function pullCard so, it will be cardcnt++.
			
			printUserCardStatus(0,cardcnt[0]);
			getActioin();		
		}
		
		//each player's turn
		for (i=1;i<n_user;i++) //each player
		{
			printf("Player %d Turn!-------------------\n",i);
			printUserCardStatus(i,cardcnt[i]); 
			getActionPlayer(i);
			while(getActionPlayer()==1)
			{	
				printf("Go\n");
				cardhold[i][cardcnt[i]]=pullCard();
				printUserCardStatus(i,cardcnt[i]);
				getActionPlayer();
			}
			calcStepResult(i);
			/*while (getAction==0) //do until the player dies or player says stop
			{
				printUserCardStatus(i,cardcnt[i]);//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				while(getActionPlayer()==1)
				{	
					printf("Go\n");
					cardhold[i][cardcnt[i]]=pullCard();
					printUserCardStatus(i,cardcnt[i]);
					//GO? STOP? ::: getActionPlayer()
					//printCard(cardhold[0][0]);
					//printCard(cardhold[0][1]);
				}	//printUserCardStatus(i,cardcnt);
				//check if the turn ends or not
			}*/
			
		}//�� for���� ��ǻ�͵��� ������ ������. 
		//Server's turn.
		
		//result
		for(j=0;j<n_user;j++)
			checkResult(j);
		roundIndex++;
	} while (cardIndex==N_CARDSET*N_CARD);//�̰� �ѹ� �������� roundIndex++����ߵ�. 
	
	checkWinner();
	
	
	return 0;
}
