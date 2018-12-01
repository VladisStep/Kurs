#include <stdio.h>
void howLetters (char **text, int *numberOfStr){
    int i = 0; 
    int j = 0;
    int t = 1;
    int how = 1;
    int schet = 1;
    int lenStr = 0;
    char *newStr = malloc(sizeof(char));
    char symb;

    char test [100] = "";


    for (i = 0; i < *numberOfStr; i++){
        for (j = 0; j < strlen(text[i])-1; j++){
            if ((tolower(text[i][j]) == tolower(text[i][j+1])) && isalpha(text[i][j])){
                while ((tolower(text[i][j]) == tolower(text[i][j+1])) && isalpha(text[i][j])){
                    schet++;
                    j++;
                }       
                while (schet > t){
                    t *= 10;
                    how++;
                }
                lenStr += how+1;
                printf("%d ", lenStr);
              /* newStr = (char*) realloc(newStr,lenStr*sizeof(char));
               //printf("%d.", lenStr -1);
               newStr[lenStr - 1] = 'a';
              // printf("%c ", newStr[lenStr - 1]);*/
                how = 1;
                t = 1;
                schet = 1;
            }
        }
    
    }

