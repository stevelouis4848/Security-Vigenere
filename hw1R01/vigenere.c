#include <stdio.h>
#include<stdlib.h>
#include<ctype.h>

int MAX_INPUT_SIZE = 512;
int ALPHA_SIZE = 26;
int MAX_LINE_COUNT = 80;

void fileReader(char *keyFileName, char *inputFileName);
void encoder(char *cleanKey, char *cleanInput, int keySize);

int main(int argc, char **argv){

	int i;
	
	for(i = 2; i < argc; i += 2){
		
		fileReader(argv[i - 1], argv[i]);
	
	}
	
	return 0;
}

void fileReader(char *keyFileName, char *inputFileName){
	
	int i, j = 0, keySize;
	FILE *keyFile, *inputFile;
	char buffer, *cleanKey, *cleanInput; 
	
	keyFile = fopen(keyFileName, "r");
	inputFile = fopen(inputFileName, "r");
		
	cleanInput = malloc((MAX_INPUT_SIZE + 1) * sizeof(char));
	cleanInput[MAX_INPUT_SIZE] = '\0';
	
	for(i = 0; (i < MAX_INPUT_SIZE) && ((buffer = fgetc(keyFile)) != EOF); i++){
		
		if((isspace(buffer) == 0) && (isalpha(buffer) != 0)){
			j++;
		}		
	}
	
	keySize = j;
	
	cleanKey = malloc((keySize + 1) * sizeof(char));
	cleanKey[keySize] = '\0';
	
	fclose(keyFile);
	
	keyFile = fopen(keyFileName, "r");
	
	j=0;
	for(i = 0; (i < MAX_INPUT_SIZE) && ((buffer = fgetc(keyFile)) != EOF); i++){
		
		if((isspace(buffer) == 0) && (isalpha(buffer) != 0) ){
		
			cleanKey[j] = tolower(buffer);
			j++;
		}		
	}
	
	for(i = 0; i < MAX_INPUT_SIZE; i++){
		
		cleanInput[i] = 'x';
	}
		
	j = 0;
	for(i = 0; (i < MAX_INPUT_SIZE) && ((buffer = fgetc(inputFile)) != EOF); i++){
		
		if(isspace(buffer) == 0 && isalpha(buffer) != 0){
		
			cleanInput[j] = tolower(buffer);
			j++;
		}		
	}
	
	printf("\n\nVigenere Key:\n\n");
	
	i = 0;
	while(i < keySize){
		for(j = 0; (j < MAX_LINE_COUNT)  && (i < keySize); j++){
			
			printf("%c", cleanKey[i]);	
			i++;
		}
		printf("\n");
	}
	
	printf("\n\nPlaintext:\n\n");
	
	i = 0;
	while(i < MAX_INPUT_SIZE){
		for(j = 0; (j < MAX_LINE_COUNT)  && (i < MAX_INPUT_SIZE); j++){			
			
			printf("%c", cleanInput[i]);	
			i++;
		}
		printf("\n");
	}
	printf("\n\n");
	
	//printf("\n\nVigenere Key:\n\n%s\n\n\nPlainText:\n\n%s\n\n\n", cleanKey, cleanInput);

	encoder(cleanKey, cleanInput, keySize);
	
	fclose(keyFile);
	fclose(inputFile);
	return;
}

void encoder(char *cleanKey, char *cleanInput,int keySize){
	
	int i, j;
	char *keyDecimal, *inputDecimal, *result;

	keyDecimal = malloc(keySize * sizeof(char));
	inputDecimal = malloc(MAX_INPUT_SIZE * sizeof(char));
	result = malloc(MAX_INPUT_SIZE * sizeof(char));
	
	for(i = 0; i < keySize; i++){
		
		keyDecimal[i] = (char)(cleanKey[i] - 'a');
		
		//printf("keyDecimal[%d]: %d\n", i, keyDecimal[i]);		
	}
		
	for(i = 0; i < MAX_INPUT_SIZE; i++){
		
		inputDecimal[i] = (char)(cleanInput[i] - 'a');
		
		//printf("inputDecimal[%d]:  %d\n", i, inputDecimal[i]); 		
	}
	
	for(i = 0; i < MAX_INPUT_SIZE; i++){
		
		result[i] = ((keyDecimal[i % keySize] + inputDecimal[i]) % ALPHA_SIZE) + 'a';
		//resultChar[i] = (char)result + 'a';		
		
		//printf("result[%d}:  %d\n", i, result[i]);
		//printf("resultChar[%d]:  %c\n", i, resultChar[i]);		
	}	
	
	printf("Ciphertext:\n\n");
	
	i = 0;
	
	while(i < MAX_INPUT_SIZE){
		for(j = 0; (j < MAX_LINE_COUNT) && (i < MAX_INPUT_SIZE); j++){
					
			printf("%c",result[i]);
			i++;
		}		
		printf("\n");
	}
}