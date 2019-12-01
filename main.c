#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int doesExist(char arr[][100],char arr2[],int count){
	int i = 0;
	for(i = 0 ; i < count ; i++){
		
		if(strncmp(arr[i], arr2,100) == 0){
			return 1;
		}
	}
	return 0;
}

void populateArray(char name[], char array[][100]){
	FILE *fptr = fopen(name, "r");
	if (fptr == NULL)
    {
        printf("Cannot open file \n");
        return;
    }
    char ch = fgetc(fptr);
    int i = 0,j=0;
    while (ch != EOF)
    {
    	if(ch == '\n'){
			j=0;
			i++;			
		} else {
			array[i][j] = ch;
	        j++;
		}
		ch = fgetc(fptr);
    }
    fclose(fptr);
}

int countLinesInFile(char name[]){
	int count = 0;
	
	FILE *fptr = fopen(name, "r");
	if (fptr == NULL)
    {
        printf("Cannot open file \n");
        
    }
    
    char ch = fgetc(fptr);
    while (ch != EOF)
    {
    	if(ch == '\n') count++;
    	ch = fgetc(fptr);
    }
    fclose(fptr);
    return count;
}

int main(){
	//Counting Number of lines in each file
	int positiveWordsCount = countLinesInFile("positive-words.txt");
	int negativeWordsCount = countLinesInFile("negative-words.txt");
	//Populating arrays with positive and negative words
	char positiveWords[positiveWordsCount][100];
	char negativeWords[negativeWordsCount][100];
	populateArray("negative-words.txt",negativeWords);
	populateArray("positive-words.txt",positiveWords);
	//Taking Response
	char input[1000],word[100][100];
	int i=0,j=0,k=0;
	printf("Enter response (1000 characters): ");
	gets(input);
	//Dividing response into words and lowering the caps
	while(i < strlen(input)){
		if(input[i] == ' ' || input[i] == '\n'){
			k=0;
			j++;
		} else {
			word[j][k] = tolower(input[i]);
			k++;
		}
		i++;
	}
	//Declaring Variables to count response
	int posResponse = 0 , negResponse = 0;
	//Counting good and bad words
	i=0;
	for( i = 0 ; i <= j ;i++ ){
		if(doesExist(positiveWords,word[i],positiveWordsCount))
			posResponse++;
		else if(doesExist(negativeWords,word[i],negativeWordsCount))
			negResponse++;
	}
	if(posResponse > negResponse)
		printf("Positive Sentiment\n");
	else if(posResponse < negResponse)
		printf("Negative Sentiment\n");
	else
		printf("Neutral Sentiment\n");
	printf("Press any key to exit...");
	scanf("%d",i);
	
	return 0;
}
