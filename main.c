#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DeckSize 52
#define Values 13

typedef struct cardStruct{
	int value;
	struct cardStruct *next;
}card_s;


int main(){
	srand(time(0));
	
	card_s topCard;
	topCard.value = rand() % DeckSize;
	topCard.next = NULL;
	
	card_s *cardPtr;
	for(int i = 0; i < DeckSize; i++){ shuffleLoopStart:
		int r = rand() % DeckSize;
		cardPtr = &topCard;
		while(cardPtr->next != NULL){
			if(cardPtr->value == r){ goto shuffleLoopStart; }
			cardPtr = cardPtr->next;
		}
		cardPtr->value = r;
		cardPtr->next = (card_s *)malloc(sizeof(card_s));
	}
	
	card_s *player1Ptr = &topCard;
	
	cardPtr = &topCard;
	for(int i = 0; i < DeckSize / 2; i++){
		
	}
	
	
	return 0;
}
