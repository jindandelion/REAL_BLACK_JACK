void printUserCardStatus(int user, int cardcnt) {
	//�׳� cardcnt��� ������ �� �ʿ��Ѱ��� �𸣰�
	//������ �ִ� ī�� ������ŭ ����Ʈ�� ���࿩ �Ǵϱ�
	
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
	//while���� ������ �� gostop�� ���� 0�̸� while�ȿ� for�� �־ ����.  
	if(gostop==0)
	{
		cardcnt++;
		return 0;
	}
	else
		return 1;	
	
}
void calcardsum(int cardnum){//A function that calculates the sum of the cards.
	
	int i;
	int sum;
	for(i=0;i<cardcnt;i++)
	{
		sum=sum+cardhold[cardnum][i];//���⿡ �ռ� PullCard�� ���� ��ȯ���� �������־����ϱ�
	}
	
	cardSum[cardnum]=sum;
	
	return 0;
} 
















