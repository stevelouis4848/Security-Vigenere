#include <stdio.h>
#include<stdlib.h>
#include<ctype.h>

int MAX_KEY_SIZE = 512;
int MAX_INPUT_SIZE = 512;
int ALPHA_SIZE = 25;


void fileReader(char *keyFileName, char *inputFileName);
void encoder(char *cleanKey, char *cleanInput, int keySize);

int main(int argc, char **argv){
	printf("main\n");
	fflush(stdout);
	int i;
	
	for(i = 2; i < argc; i += 2){
		
		fileReader(argv[i - 1], argv[i]);
	
	}
	
	return 0;
}

void fileReader(char *keyFileName, char *inputFileName){
	
	printf("filereader\n");
	fflush(stdout);
	int i = 0, keySize;
	FILE *keyFile, *inputFile;
	char buffer, *cleanKey, *cleanInput; 
	
	keyFile = fopen(keyFileName, "r");
	inputFile = fopen(inputFileName, "r");
	
	cleanKey = malloc((MAX_KEY_SIZE + 1) * sizeof(char));
	cleanInput = malloc((MAX_INPUT_SIZE + 1) * sizeof(char));
	
	while((buffer = fgetc(keyFile)) != EOF){
		
		if(isspace(buffer) == 0 && isalpha(buffer) != 0 ){
			i++;
		}		
	}
	
	keySize = i;
	
	fclose(keyFile);
	
	keyFile = fopen(keyFileName, "r");
	
	i = 0;
	
	while((buffer = fgetc(keyFile)) != EOF){
		
		if(isspace(buffer) == 0 && isalpha(buffer) != 0 ){
		
			cleanKey[i] = tolower(buffer);
	
			//printf("cleanKey[%d]:  %c\n", i, cleanKey[i]);
			i++;
		}		
	}
	
	cleanKey[i] = '\0';
	
	for(i = 0; i < MAX_INPUT_SIZE; i++){
		
		cleanInput[i] = 'x';
	}
	
	i = 0;
	while((buffer = fgetc(inputFile)) != EOF){
		
		if(isspace(buffer) == 0 && isalpha(buffer) != 0){
		
			cleanInput[i] = tolower(buffer);	
			
			//printf("cleanInput[%d]:  %c\n", i, cleanInput[i]);
			i++;
		}		
	}
	
	cleanInput[MAX_INPUT_SIZE + 1] = '\0';
	printf("cleanKEY:\n%s\ncleanINPUT:\n%s\n\n", cleanKey, cleanInput);

	encoder(cleanKey, cleanInput, keySize);
	
	fclose(keyFile);
	fclose(inputFile);
	return;
}

void encoder(char *cleanKey, char *cleanInput,int keySize){
	
	printf("encoder\n");
	fflush(stdout);
	int i;
	char *keyDecimal, *inputDecimal, *result;

	keyDecimal = malloc(MAX_KEY_SIZE * sizeof(char));
	inputDecimal = malloc(MAX_INPUT_SIZE * sizeof(char));
	result = malloc(MAX_INPUT_SIZE * sizeof(char));
	//resultChar = malloc(MAX_INPUT_SIZE * sizeof(char));
	
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
	
	printf("result:\n");
	
	for(i = 0; i < MAX_INPUT_SIZE; i++){
				
		printf("%c",result[i]);
	}
		
	
}

	