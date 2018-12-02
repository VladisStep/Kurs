#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define blue  "\033[0;34m"

int reedAndSort(int *numberOfStr, char ***text);

int menu(char **text, int numberOfStr);

void findBlue (char **text, int *numberOfStr);

void howLetters (char **text, int *numberOfStr);

void deletthree (char **text, int *numberOfStr);

void bubbleSort (char **text, int *numberOfStr);

void char2int (int howWord, char *doStr);


int main (){
    int numberOfStr = 0 ;
    char **text;
    int i = 0;
    reedAndSort(&numberOfStr, &text);
    menu(text,numberOfStr);
    for (i = 0; i < numberOfStr; i++)
        free(text[i]);
    free(text);
return 0;
}

int reedAndSort(int *numberOfStr, char ***text){

    *text = 0;
   
    char c;
    char* str = 0;

    int i = 0;
    int j = 0;
    int numOfStr = 0;
    int lenStr = 0;
    int freeStr = 0;
    
    do{
        c = getchar();
        
        if (c != EOF){
            str = realloc(str,++lenStr*sizeof(char)+1);
            str[lenStr - 1] = c;
        }

        if (c == '.' || c =='\n' || c == EOF){
            freeStr = 1;
            if (lenStr > 1){
                str[lenStr] = '\0';
                i = 0;
                while (i < numOfStr) 
                    if (strcasecmp(str, (*text)[i++]) == 0)
                        break;
            
                if(i == numOfStr){
                *text = realloc(*text,++numOfStr*sizeof(char*));
                (*text)[numOfStr - 1] = str;
                str = 0;
                freeStr = 0;
                }
                
            }
            lenStr = 0;
        }
    }while(c != '\n' && c!= EOF); 

    if (freeStr)
        free(str);
    //for (i = numOfStr-1; i > 0; i--) printf("%s\n", (*text)[i]);
    *numberOfStr = numOfStr;

    return 0;
}

int menu(char **text, int numberOfStr){
    char func;
    int i = 0;

    start:
    printf("Введите номер функции: ");
    scanf("%s", &func);
    printf("    выбранная функция -> %c\n",func);

    switch(func){

        case '1':
        printf("ok1\n");
        findBlue(text, &numberOfStr);
        goto start;
        break;

        case '2':
        printf("ok2\n");
        howLetters(text, &numberOfStr);
        for (i = 0; i < numberOfStr; i++)
            printf("%s\n",text[i]);
        goto start;
        break;

        case '3':
        printf("ok3\n");
        deletthree (text, &numberOfStr);
        for (i = 0; i < numberOfStr; i++)
            printf("%s\n",text[i]);
        goto start;
        break;

        case '4':
        printf("ok4\n");
        bubbleSort (text, &numberOfStr);
        for (i = 0; i < numberOfStr; i++)
            printf("%s\n",text[i]);
        goto start;
        break;

         case '0':
        printf("ok0\n");
        return 0;
        break;
    }
    
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


void howLetters (char **text, int *numberOfStr){
    int i = 0;
    int j = 0;
    int k = 0;
    int howWord = 1;
    int lenNewStr = 0;

    for (i = 0; i < *numberOfStr; i++){
        char *newStr = (char*) malloc(sizeof(char));
        for ( j = 0; j < strlen(text[i]); j++){
            lenNewStr++;
            while(tolower(text[i][j]) == tolower(text[i][j+1])){
                howWord++;
                j++;
            }
            if(howWord > 1){
                char *doStr = (char*) malloc(sizeof(char));
                char2int(howWord, doStr);   
                newStr = (char*)realloc(newStr,(lenNewStr + strlen(doStr))*sizeof(char)+1);
                for(k = 0; k < strlen(doStr); k++){
                    newStr[lenNewStr - 1 + k] = doStr[k];
                }
                lenNewStr += strlen(doStr);
                newStr[lenNewStr -1] = toupper(text[i][j]);
                free(doStr);
            }
            else{
                newStr = (char*)realloc(newStr,lenNewStr*sizeof(char)+1);
                newStr[lenNewStr -1] = text[i][j];
            }
          howWord = 1;
        }
        newStr[lenNewStr] = '\0';
        free(text[i]);
        text[i] = newStr;
        newStr = NULL;
        lenNewStr = 0; 
    } 
}


void deletthree (char **text, int *numberOfStr){
    int i = 0;
    int j = 0;
    int howWord = 1;

    for (i = 0; i < *numberOfStr; i++){  
        j = (text[i][0] == ' ') ? 1 : 0;
        for(j; j < strlen(text[i]);j++){
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



void bubbleSort (char **text, int *numberOfStr){
    int i = 0;
    int j = 0;
    int save = 0;
    char *keepStr;
    int *size = calloc(*numberOfStr,sizeof(int));
    char space[] = " ";
    char *haveSpace;

    for (i = 0; i < *numberOfStr; i++){
        text[i][0] = (text[i][0] != ' ') ? :'*';
        haveSpace = strstr(text[i], space);
        if(haveSpace == NULL){
            size[i] = strlen(text[i])-1;
            text[i][0] = (text[i][0] != '*') ? :' ';
        }
        else
            {
                j = (text[i][0] == '*') ? 1 : 0;
                text[i][0] = (text[i][0] != '*') ? :' ';
                for (j;((text[i][j] != ' ') && (text[i][j] != ',')); j++)
                    size[i]++;
                for (j = strlen(text[i])-2;(text[i][j] != ' '); j--)
                    size[i]++;
                }
        }
    for (i = 0; i < *numberOfStr-1; i++){

        for (j = 0; j < *numberOfStr-1; j++){
            if (size[j] > size[j+1]){
                save = size[j];
                size[j] = size[j+1];
                size[j+1] = save;

                keepStr = text[j];
                text[j] = text[j+1];
                text[j+1] = keepStr;
            }
        }
    }
    free(size);
}

void char2int(int howWord,char *doStr){
    int i = 0;
    int j = 0;
    char c;
    while(howWord > 0){
        i++;
        doStr =(char*)realloc(doStr, i*sizeof(char)+1);
        doStr[i-1] = '0' + howWord % 10;
        howWord = howWord / 10;
        doStr[i] ='\0';  
    } 
    while( j < i){
        i--;
        c = doStr[j];
        doStr [j] = doStr[i];
        doStr[i] = c;
        j++;
    }
}