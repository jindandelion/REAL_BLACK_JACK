//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) { 
	
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
}
//A function that calculates the sum of the cards.
int calcardsum(int user){
	
	int i;
	int sum;
	for(i=0;i<cardcnt[user];i++)
	{
		sum=sum+cardhold[user][i];//���⿡ �ռ� PullCard�� ���� ��ȯ���� �������־����ϱ�
	}
	
	cardSum[user]=sum;
	
	return cardSum[user];
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

