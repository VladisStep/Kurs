#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main (){
    char *string = malloc(sizeof(char*));
    char **text = malloc(sizeof(char**));
    

    char symbol;

    int i = 0;
    int lenStr = 1;
    int numberOfStr = 0;

    while (symbol != '\n'){
        
        while ((symbol != '.') && (symbol != '\n')){
            symbol = getchar();
            lenStr++;
            string = (char *)realloc(string, lenStr*sizeof(string));
            string[lenStr - 2] = symbol;  
        }
        symbol = getchar();
        string[lenStr - 1] = '\0';

        numberOfStr++;
        text = (char**)realloc(text, numberOfStr*sizeof(char*));
        text[numberOfStr - 1] = (char*)realloc(text[numberOfStr - 1], strlen(string)*sizeof(char)+1);
        
        strcpy(text[numberOfStr - 1], string);
        free(string);
        string = NULL;
        lenStr = 1;


        
    }
printf("%s\n",text[0]);

return 0;
}