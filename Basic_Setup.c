void printUserCardStatus(int user, int cardcnt) {
	//그냥 cardcnt라는 변수가 왜 필요한건지 모르겠
	//가지고 있는 카드 개수만큼 프린트를 해줘여 되니까
	
	int i;
	
	printf("   -> card : ");
	
	for (i=0;i<cardcnt;i++)
	{
		printCard(cardhold[user][i]);
	}
	
	printf("\t ::: ");

}
int cardcnt[N_MAX_USER]={2,2,2,2,2};

int getAction(void) {
	
	int gostop;
	
	printf("Action? (0-go, other-stay)");
	//scanf("%d",&gostop);
	gostop=getIntegerInput();
	//while문을 돌려서 그 gostop의 값이 0이면 while안에 for문 넣어서 돌려.  
	if(gostop==0)
	{
		cardcnt[0]++;//0번째 사용자 즉, user가 가지고 있는 카드의 수. 
		return 0;
	}
	else
		return 1;	
	
}
int getActionPlayer(int n_user){
	
	calcardsum(n_user);//The sum of the cards for the i-th user will be calculated.
	if(calcardsum(n_user)<=17)//무조건 go함. 
		cardcnt[n_user]++;
		return 1;
		
	else
		printf("STAY!\n"); 
		return 2; 
		
	
	
}
void calcardsum(int cardnum){//A function that calculates the sum of the cards.
	
	int i;
	int sum;
	for(i=0;i<cardcnt;i++)
	{
		sum=sum+cardhold[cardnum][i];//여기에 앞서 PullCard의 정수 반환값을 저장해주었으니까
	}
	
	cardSum[cardnum]=sum;
	
	return 0;
} 
calcardSum















