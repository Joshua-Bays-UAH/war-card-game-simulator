#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define DeckSize 52
#define Values 13

const char values[][12] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};

typedef struct cardStruct{
	int value;
	struct cardStruct *next;
}card_s;

int hand_size(card_s *ptr);
void print_hand(card_s *ptr);


int main(){
	srand(time(0)*clock());
	
	card_s topCard;
	topCard.value = rand() % DeckSize;
	topCard.next = NULL;
	
	/* Create a shuffled deck */
	card_s *cardPtr;
	for(int i = 1; i < DeckSize; i++){ shuffleLoopStart:
		int r = rand() % DeckSize;
		cardPtr = &topCard;
		while(cardPtr->next != NULL){
			if(cardPtr->value == r){ goto shuffleLoopStart; }
			cardPtr = cardPtr->next;
		}
		cardPtr->next = (card_s*)malloc(sizeof(card_s));
		cardPtr->next->value = r;
		cardPtr->next->next = NULL;
	}
	//print_hand(&topCard); return 1;

	/* Deal hands */
	card_s *player1TopPtr = &topCard;
	card_s *player2TopPtr = NULL;
	
	cardPtr = &topCard;
	
	card_s cpy;
	cardPtr = &topCard;
	
	for(int i = 0; i < DeckSize/2 - 1; i++){
		cardPtr = cardPtr->next;
	}
	player2TopPtr = cardPtr->next;
	//cardPtr->next = (card_s *)malloc(sizeof(card_s));
	cardPtr->next = NULL;
	
	card_s *player1BottomPtr = NULL;
	card_s *player2BottomPtr = NULL;
	
	cardPtr = player1TopPtr;
	while(cardPtr->next != NULL){
		cardPtr = cardPtr->next;
	}
	player1BottomPtr = cardPtr;
	
	cardPtr = player2TopPtr;
	while(cardPtr->next != NULL){
		cardPtr = cardPtr->next;
	}
	player2BottomPtr = cardPtr;
	
	/* Game loop */
	int p1 = 0; int p2 = 0;
	while(player1TopPtr->next != NULL && player2TopPtr->next != NULL){compStart:
		p1 = player1TopPtr->value % 13;
		p2 = player2TopPtr->value % 13;
		
		printf("%s VS %s   (%i VS %i)  (%i %i)  ", values[p1], values[p2], player1TopPtr->value, player2TopPtr->value, hand_size(player1TopPtr), hand_size(player2TopPtr));
		if(p1 > p2){
			printf("Player 1 wins\n");
			if(0 && hand_size(player1TopPtr) == 1){
				cardPtr = player2TopPtr;
				player2TopPtr = player2TopPtr->next;
				player1TopPtr->next = cardPtr;
				player1BottomPtr = cardPtr;
				player1BottomPtr->next = NULL;
			}
			
			cardPtr = player1TopPtr;
			player1TopPtr = player1TopPtr->next;
			player1BottomPtr->next = cardPtr;
			player1BottomPtr = player1BottomPtr->next;
			
			cardPtr = player2TopPtr;
			player2TopPtr = player2TopPtr->next;
			player1BottomPtr->next = cardPtr;
			player1BottomPtr = player1BottomPtr->next;
			player1BottomPtr->next = NULL;
		}else if(p1 < p2){
			printf("Player 2 wins\n");
			if(hand_size(player1TopPtr) == 1){break;}
			
			cardPtr = player2TopPtr;
			player2TopPtr = player2TopPtr->next;
			player2BottomPtr->next = cardPtr;
			player2BottomPtr = player2BottomPtr->next;
			
			cardPtr = player1TopPtr;
			player1TopPtr = player1TopPtr->next;
			player2BottomPtr->next = cardPtr;
			player2BottomPtr = player2BottomPtr->next;
			player2BottomPtr->next = NULL;
		}else if(p1 == p2){
			printf("Tie\n");
			
			cardPtr = player1TopPtr;
			player1TopPtr = player1TopPtr->next;
			player1BottomPtr->next = cardPtr;
			player1BottomPtr = player1BottomPtr->next;
			player1BottomPtr->next = NULL;
			
			cardPtr = player2TopPtr;
			player2TopPtr = player2TopPtr->next;
			player2BottomPtr->next = cardPtr;
			player2BottomPtr = player2BottomPtr->next;
			player2BottomPtr->next = NULL;
		}
	}
	
	return 0;
}

int hand_size(card_s *ptr){
	int ret = 1;
	while(ptr->next != NULL){
		ret++;
		ptr = ptr->next;
	}
	return ret;
}

void print_hand(card_s *ptr){
	do{
		printf("%i\n", ptr->value);
		ptr = ptr->next;
	}while(ptr->next != NULL);
	printf("%i\n", ptr->value);
}
