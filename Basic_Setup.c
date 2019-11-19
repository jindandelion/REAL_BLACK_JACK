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
	cardcnt[user]++;
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
		cardcnt++;
		return 0;
	}
	else
		return 1;	
	
}
