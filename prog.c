#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define blue  "\033[0;34m"

void findBlue (char **text, int *numberOfStr);

void howLetters (char **text, int *numberOfStr);

void deletthree (char **text, int *numberOfStr);

int main (){
    char *string = malloc(sizeof(char*));
    char **text = malloc(sizeof(char**));

    char func;
    char symbol;

    int schet = 0; // счетчик для поиска одинаковых строк
    int j = 0;
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

        for (i = 0; i < numberOfStr; i++){
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
            numberOfStr++;
            text = (char**)realloc(text, numberOfStr*sizeof(char*));
            text[numberOfStr - 1] = (char*)realloc(text[numberOfStr - 1], strlen(string)*sizeof(char)+1);
            strcpy(text[numberOfStr - 1], string);
        }
        schet = 0;
        free(string);
        string = NULL;
        lenStr = 1;

        
    }

   // for (i = 0; i< numberOfStr; i++) printf("%s\n",text[i]);

    printf("Введите номер функции: ");
    scanf("%c", &func);
    printf("    выбранная функция -> %c\n",func);

    switch(func){

        case '1':
        printf("ok1\n");
        findBlue(text, &numberOfStr);
        break;

        case '2':
        printf("ok2\n");
        //howLetters(text, &numberOfStr);
        break;

        case '3':
        printf("ok3\n");
        deletthree (text, &numberOfStr);
        for (i = 0; i < numberOfStr; i++)
            printf("%s\n",text[i]);
        break;

        case '4':
        printf("ok4\n");
        break;
    }
    
    for (i = 0; i < numberOfStr; i++)
        free(text[i]);
    free(text);

return 0;
}


void findBlue (char **text, int *numberOfStr){
    char find[] = "define BLUE";
    char *istr;
    int i = 0;
    int j = 0;
    int ind = 0;
    
    for(i=0; i < *numberOfStr; i++){
        istr = strstr(text[i],find);
        if ( istr == NULL)
            printf ("%s\n",text[i]);
        else{
            ind = (int)(istr - text[i]+11);
            for(j = 0; j < strlen(text[i]); j++){
                if (ind == j)
                    printf(blue);
                printf("%c", text[i][j]);
            }
            printf("\033[0m\n");
        }
    }
}




/*void howLetters (char **text, int *numberOfStr){
    int i = 0; 
    int j = 0;
    int t = 1;
    int how = 1;
    int schet = 1;
    int lenStr = 0;
    char *newStr = malloc(sizeof(char*));
    char symb;

    char test [100] = "";


    for (i = 0; i < *numberOfStr; i++){
        for (j = 0; j < strlen(text[i])-1; j++){
            if ((tolower(text[i][j]) == tolower(text[i][j+1])) && isalpha(text[i][j])){
                while ((tolower(text[i][j]) == tolower(text[i][j+1])) && isalpha(text[i][j])){
                    schet++;
                    //printf("%d ",j);
                    j++;
                }       
                //printf("%d%c ", schet,toupper(text[i][j]));
                //printf("%d ",schet);
                while (schet > t)
                    t *= 10;
                    how++;
                lenStr += how+1;
               printf(" lenStr = %d, t = %d how = %d\n", lenStr,t, how);
               newStr = (char*) realloc(*newStr,lenStr*sizeof(char));
               newStr[lenStr - 1] = 'a';
               printf("[%ld] %s\n", sizeof(newStr), newStr);
                how = 1;
                t = 1;
                schet = 1;
            }
        }
    
    }
}
*/

void deletthree (char **text, int *numberOfStr){
    int i = 0;
    int j = 0;
    int howWord = 1;

    for (i = 0; i < *numberOfStr; i++){  
        for(j = 0; j < strlen(text[i]);j++){
            if (text[i][j] == ' ')
                howWord++;
        }
        if (howWord % 3 == 0){
            free(text[i]);
            for (j = i; j < *numberOfStr; j++){
                text[j] = text[j+1];
            }
            i--;
            (*numberOfStr)--;
        }
        howWord = 1;
    }
}