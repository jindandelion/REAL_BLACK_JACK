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
		cardcnt[0]++;//0��° ����� ��, user�� ������ �ִ� ī���� ��. 
		return 0;
	}
	else
		return 1;	
	
}
int getActionPlayer(int n_user){
	
	calcardsum(n_user);//The sum of the cards for the i-th user will be calculated.
	if(calcardsum(n_user)<=17)//������ go��. 
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
		sum=sum+cardhold[cardnum][i];//���⿡ �ռ� PullCard�� ���� ��ȯ���� �������־����ϱ�
	}
	
	cardSum[cardnum]=sum;
	
	return 0;
} 
calcardSum















