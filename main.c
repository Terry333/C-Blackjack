#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PLAYERS 4
#define DECK_SIZE 52
#define BUST_SIZE 21

void Configure_Deck();

typedef struct Players {
	int Hand_Value;
} Player;

typedef struct Cards {
	char *Name;
	int PrimaryValue;
	int SecondaryValue;	
	Player Owner;
} Card;

Player Players_Set[MAX_PLAYERS];
Card Card_Deck[DECK_SIZE];

int main(int argc, char **argv) {
	printf("Game started!\n");
	//memset(&Card_Deck, '0', sizeof(Card) * DECK_SIZE);
	Configure_Deck();
	printf("Game over...\n");
	return 0;
}

void Configure_Deck(){
	FILE *file;
	if((file = fopen("CardData.data", "r")) == NULL){
		printf("Invalid card data!\n");
		exit(1);
	}
	else{
		printf("Found file!\n");
	}
	
	char lines[DECK_SIZE / 4][100];
	
	for(int i = 0; i < DECK_SIZE / 4; i++){
		rewind(file);
		fseek(file, 0, (i * 100) * sizeof(char));
		fscanf(file, "%[^\n]", lines[i]);
		printf("%s\n", lines[i]);
	}
	
	for(int c = 0; c < 4; c++){
		char *type;
		switch(c){
			case 0:
				type = " Hearts";
				break;
			case 1:
				type = " Spades";
				break;
			case 2:
				type = " Diamonds";
				break;
			case 3:
				type = " Clubs";
				break;
		}
		for(int i = 0; i < DECK_SIZE / 4; i++){
			int first_int = 0;
			int	second_int = 0;
			char *token = strtok(lines[i], ";");
			char *name = token;
			char *number_token = strtok(NULL, ";");
			char *first_value = number_token;
			char *second_value = NULL;
			if(strcmp(first_value, "x") == 0){
				first_value = "11";
				second_value = "1";
				sscanf(second_value, "%d", &second_int);
			}
			strcat(name, type);
			sscanf(first_value, "%d", &first_int);
			printf("%s\n", name);
			Card_Deck[i] = (Card){ .Name = name, .PrimaryValue = first_int, .SecondaryValue = second_int, .Owner = NULL };
		}
	}
	
	fclose(file);
	printf("Finished setting deck!\n");
}
