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
//int cardnumcnt;//카드트레이에서 0부터 N_CARDSET*N_CARD-1까지 의 배열 요소 중 몇번째 까지 썼는지 카운터해주는 변수. 
//int cardcnt;//각 player가 갖고있는 카드의 갯수가 몇개인지 세주는 변수. 
int cardcnt[N_MAX_USER]={1,1,1,1,1};//Variables that count the number of cards each player has.

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
int puca;//pullCardEach time a function has a return value, a variable that allows the next value in the array to be set as a global variable.

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
int getCardNum(int cardnum) { //cardnum가 즉 pullCard에 저장된 수,아그러면 아... 
	
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
			cardnum=cardnum+1;
		
	}
	//getcardnum에서 return을 11로하고  만약에 CardSum이 21이 넘으면 그때 10을 빼주는것. 
}
//A function that calculates the sum of the cards.
int calcardsum(int user){
	
	int i;
	int result; 
	int sum;
	
	for(i=0;i<cardcnt[user];i++)
	{	
		result=getCardNum(cardhold[user][i]);
		sum=sum+result;
	}
	
	cardSum[user]=sum;
	
	return cardSum[user];
} 
	
//print the card information (e.g. DiaA)
void printCard(int cardnum) { //cardnum이라는 값이 곧 Cardtray[i]라는 배열에 저장 된 값 
	
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
	cardIndex++;//이걸 이렇게 하면 안될 것 같기도 하고.. 
	
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
	
	for(i=0;i<N_CARDSET*N_CARD;i++)
	{
		CardTray[i]=i;
	}//배열 선언 후 각 배열에 0~51숫자를 저장해주었다. 
	
	for(i=0;i<N_CARDSET*N_CARD;i++)
		swap(&CardTray[i],&CardTray[rand()%(N_CARDSET*N_CARD)]);
	
	/*for(i=0;i<N_CARDSET*N_CARD;i++)
	{
		temp=Cardtray[randnum1];
		Cardtray[randnum1]=Cardtray[randnum2];
		Cardtray[randnum2]=temp;
	}*/
	
}

//get one card from the tray
int pullCard(void) {
	
	int result;
	result=CardTray[puca];
	puca++;
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
		//scanf("%d",&n_user);
		n_user=getIntegerInput();
		if(n_user>=6||n_user<=0)
			printf("***Set the number of players at least 1 to %d or less.***",N_MAX_USER); 
		//-1이 들어가있으면 사용자가 숫자아닌걸 넣은거니까.. 내가 원하는 값이 아니면 다시 넣어라ㅏ! 다시 넣어라 출력..경고메세지 넣어. 
	}while(n_user>=6||n_user<=0);
		
}
	
//betting
int betDollar(void)
{
	int i;
	int putbet;//putbet변수는 컴퓨터player의 배팅액이 랜덤으로 배팅될때, 컴퓨터가 알맞게 배팅할 수 있도록 도와주는 변수이다. 
	
	printf("Your betting (total:$%d): ",dollar[0]); 
	
	/*scanf("%d",&bet[0]);*/
	do{
		bet[0]=getIntegerInput();
		
		if(bet[0]>dollar[0])
			printf("You only have %d$!!!Bet Again!!!\t:::",dollar[0]);
			
	}while(bet[0]>dollar[0]);
		
	/*변수의 논리*/
	/*player가 가진 값이 x보다 작으면 어떻게 해라*/ 
	for(i=1;i<n_user;i++)
	{
		if(dollar[i]>N_MAX_BET)
		{
			putbet=N_MAX_BET;//Player의 자본이 N_MAX_BET보다  많이 남아있으면 Player의 배팅액을 랜덤으로 설정할때 N_MAX_BET 밑으로 설정한다는 뜻
			bet[i]=rand()%putbet+1;  
		}
		else//Player의 자본이 N_MAX_BET보다 작게 남아 있으면 남은 모든 금액을 올인하겠다!
		{
			bet[i]=(rand()%dollar[i])+1;
		}
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
		cardhold[i][0] = pullCard();
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
	//scanf("%d",&gostop);
	gostop=getIntegerInput();
	//while문을 돌려서 그 gostop의 값이 0이면 while안에 for문 넣어서 돌려.  
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
	
	//calcardsum(n_user);//The sum of the cards for the i-th user will be calculated.
	
	if(calcardsum(n_user)<=17)
	{
		cardcnt[n_user]++;
		//printf("GO!\n");
		return 0;
	}//무조건 go함. 
	else
	{
	//	printf("STAY!\n"); 
		return 1; 
	}
}

//Print Card Status
void printUserCardStatus(int user, int number) {
	//그냥 cardcnt라는 변수가 왜 필요한건지 모르겠
	//가지고 있는 카드 개수만큼 프린트를 해줘여 되니까
	//printUserCardStatus(i,cardcnt[i]); 
	int i;
	
	printf("   -> card : ");
	
	//for (i=0;i<cardcnt[number];i++)
	for (i=0;i<number;i++)
	{
		printCard(cardhold[user][i]);
	}
	

	printf("\t ::: ");
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack

//Before Use calcStepResult function have to call calcardSum function. 
//Each time players finish their turn, print each step's results.
int calcStepResult(/*int user*/) {
	
	
	if(cardcnt[user]==2&&calcardsum(user)==21)
		printf("Black Jack! Congratulation, You Win!!\n");
		
	else if(calcardsum(user)>21)
		printf("DEAD[overflow!] (sum:%d)\n",cardSum[user]);
		
	else
		printf("STOP\n");
	
	//int cardSum[N_MAX_USER]합은 이 배열에다 저장을 해줌. 
}


//A function that tells the result of the round.
int checkResult(int user) {
	
	int i;
	
	if(cardSum[user]>21)//cardSum is array that means sum of each card that holded each player.
		printf("[[[[[Server Result is .....overflow!!]]]]]\n");
		
	else if(cardcnt[user]==2&&cardSum[user==21])//두장의 카드 더했을 때 21이여야지 블랙잭이니깐 어 x[n_user][0]+x[n_user][1]==21 이렇게 바꿔줘야 
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
			dollar[0]=dollar[0]-bet[0];//근데 player가 먼저 블랙잭이면 break;다른 곳에서 해줘야됌. 
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
	int winner;
	int maxdollar;
	
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
	
}// max_dollar = dollar[i] max<dollar[i] max=dollar[i] i==0 i>1 pal--layer[]i



int main(int argc, char *argv[]) {
	int roundIndex = 1;
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
			cardcnt[k]=2;
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
		printf(">>> My Turn!-------------------\n");
		printUserCardStatus(0,cardcnt[0]);//처음 받은 두장의 카드를 찍어준다. 
		
		//getAction(); //Ask go or stop.
		int gAresult;//Variable that stored getAction Result.
		int gAPresult;//Variable that stored getActionPlayer's Result.
		gAresult=getAction();
		while(1)
		{
			if(gAresult==0)
			{	
				calcardsum(0);
				if(cardSum[0]<17)
				{
					printf("GO!");
					cardhold[0][cardcnt[0]]=pullCard();
					printUserCardStatus(0,cardcnt[0]);
					cardcnt[0]++;	
				}
				/*else if(cardSum[0]>=17)
				{
					printf("STOP!");
					break;
				}*/
				else if(cardSum[0]>21)
				{
					printf("DEAD(overflow)!");
					break;
					
				}
				
				
			}
			else if(gAresult==1)
			{
				printf("STOP!");
				break;
			}
			
		}
		//each player's turn
		for (i=1;i<n_user;i++) //each player
		{
			gAPresult=getActionPlayer(i);
			
			int result;
			
			printf("\n\n>>> Player %d Turn!-------------------\n",i);
			printUserCardStatus(i,cardcnt[i]); 
			
			while(gAPresult==1)
			{
				if(gAPresult==0)
				{
					printf("GO!");
					cardhold[i][cardcnt[i]]=pullCard();
					cardcnt[i]++;
					printUserCardStatus(i,cardcnt[i]);
					
				}
				else if(cardSum[i]>=17)
				{
					printf("STOP!");
					break;
				}
				else if(cardSum[i]>21)
				{
					printf("DEAD(overflow)!");
					break;
				}
			}
			/*do
			{
				result=getActionPlayer(i);
				
			} while(result==1);*/
			calcStepResult(i);
			
		}//이 for문은 컴퓨터들이 돌릴때 쓸거임. 
		//Server's turn.
		//Endgame 다 곱해서 endgame 0 cardcnt[]<51 
		//result
		for(j=0;j<n_user;j++)
		{
			checkResult(j);
		}
			
		roundIndex++;
	} while (gameEnd == 0/*cardIndex==N_CARDSET*N_CARD||dollor[0]==0*//*Endgame==0*/);//이거 한번 돌때마다 roundIndex++해줘야돼. 
	
	checkWinner();
	
	
	return 0;
}
//진짜 못하겠어 아아아 난 졸려 나도 나오늘 저거배웠다 논리회로.거지같아 아니 나 궁금한거있어 ㅋ 
