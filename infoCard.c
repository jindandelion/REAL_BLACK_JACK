//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) { 
	
	switch(cardnum%13)
	{
		case 0:
			/******************************************************************************************************/
			cardnum=11;//또는 11 .여기 안에다 if문 써도 되는건가? 쓰면 if(CardSum+11>21) cardnum=1; else cardnum=11 
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
	//getcardnum에서 return을 11로하고  만약에 CardSum이 21이 넘으면 그때 10을 빼주는것. 
	return cardnum; 
}
//A function that calculates the sum of the cards.
int calcardsum(int user){
	
	int i;
	int sum;
	for(i=0;i<cardcnt[user];i++)
	{
		sum=sum+cardhold[user][i];//여기에 앞서 PullCard의 정수 반환값을 저장해주었으니까
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

