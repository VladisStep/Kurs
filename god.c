#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int reedAndSort (int *numberOfStr, char ***text);

int main(){
    int i = 0;
    char **text;
    int numberOfStr = 0;
    reedAndSort (&numberOfStr, &text) ;
    
}

int reedAndSort (int *numberOfStr, char ***text){
    text = malloc(sizeof(char**));
    char *string = malloc(sizeof(char*));
    char symbol;
    int schet = 0; // счетчик для поиска одинаковых строк
    int j = 0;
    int i = 0;
    int lenStr = 1;
    
    
    while (symbol != '\n'){
        
        while ((symbol != '.') && (symbol != '\n')){
            symbol = getchar();
            lenStr++;
            string = (char *)realloc(string, lenStr*sizeof(string));
            string[lenStr - 2] = symbol;  
        }
        symbol = getchar();
        string[lenStr - 1] = '\0';

        for (i = 0; i < *numberOfStr; i++){
            if (strlen(string) == strlen(text[i])){
                for(j = 0; j < strlen(string); j++){
                    if (tolower(string[j]) == tolower(text[i][j]))
                        schet++;
                }
                if (schet == strlen(string))
                    break;
                else 
                    schet = 0;            
            }
        }
        if (schet != strlen(string)){      
            *numberOfStr++;
            text = (char**)realloc(text, *numberOfStr*sizeof(char*));
            text[*numberOfStr - 1] = (char*)realloc(text[*numberOfStr - 1], strlen(string)*sizeof(char)+1);
            strcpy(text[*numberOfStr - 1], string);
        }
        schet = 0;
        free(string);
        string = NULL;
        lenStr = 1;
        //for(i = 0; i < *numberOfStr; i++) printf("%s\n", *text[i]);   
    }

}
