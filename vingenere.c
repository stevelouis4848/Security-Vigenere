#include <stdio.h>
#include<stdlib.h>

int MAX_KEY_SIZE = 512;
int MAX_INPUT_SIZE = 512;
int ALPHA_SIZE = 25;


int main(int argc,char **argv){
	
	int i;
	
	for(i = 1; i < argc; i++ ){
		
		fileReader(argv[i], argv[i + 1]);
			
	}

void fileReader(char *keyFileName, char *inputFileName){
	
	FILE *keyFile, *inputFile;
	char *buffer, *cleanKey, *cleanInput; 
	
	keyFile = fopen(*keyFileName, "r");
	inputFile = fopen(*inputFileName, "r");
	
	buffer = malloc(sizeof(char));
	cleanKey = malloc(MAX_KEY_SIZE * sizeof(char));
	cleanInput = malloc(MAX_INPUT_SIZE * sizeof(char));
	
	for(i = 0; i < MAX_KEY_SIZE; i++){
		
		cleanKey[i] = NULL;
	}
	
	for(i = 0; i < MAX_INPUT_SIZE; i++){
		
		cleanInput[i] = NULL;
	}
	
	for(i = 0; fscanf(keyFile, %c, &buffer) != EOF; i++){
		
		if(isalpha(*buffer) != 0){
		
			tolower(*buffer, cleanKey[i]);
			
			printf("cleanKey[%d]:  %c\n", i, cleanKey[i]);
		}		
	}

	for(i = 0; fscanf(inputFile, %c, &buffer) != EOF; i++){
		
		if(isalpha(*buffer) != 0){
		
			tolower(*buffer, cleanInput[i]);	
			
		printf("cleanInput[%d]:  %c\n", i, cleanInput[i]);
		}		
	}
	
	printf("KEY:\n%s\n\nINPUT:\n%s\n", *cleanKey, cleanInput);
	
}

void Encoder(char *cleanKey, char *cleanInput){
	
	int i *keyDecimal, *keyDecimal, *resultDecimal;
	char *resultChar;
	
	keyDecimal = malloc(MAX_KEY_SIZE * sizeof(int));
	inputDecimal = malloc(MAX_INPUT_SIZE * sizeof(int));
	resultDecimal = malloc(MAX_INPUT_SIZE * sizeof(int));
	resultchar = malloc(MAX_INPUT_SIZE * sizeof(char));
	
	
	for(i = 0; cleanKey[i] != NULL; i++){
		
		keyDecimal[i] = cleanKey[i] - 'a';
		
		printf("keyDecimal[%d]: %d\n", i, keyDecimal[i]);
		
	}
	
	for(i = 0; cleanInput[i] != NULL; i++){
		
		inputDecimal[i] = cleanInput[i] - 'a';
		
		printf("inputDecimal[%d]:  %d\n", i, inputDecimal[i]); 
		
	}
	
	for(i = 0;cleanInput[i] != NULL; i++){
		
		resultDecimal[i] = (keyDecimal[i % MAX_KEY_SIZE] + inputDecimal[i]) % ALPHA_SIZE;
		resultChar[i] = (char)resultDecimal;		
		
		printf("resultDecimal[%d}:  %d\n", i, resultDecimal[i]);
		printf("resultChar[%d]:  %c\n", i, resultChar[i]);
		
	}
	
	printf("resultChar:  %s\n",*resultChar);	
}

	