#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define blue  "\033[0;34m"

int readAndProcess(int *numberOfStr, char ***text);

int menu(char **text, int numberOfStr);

void findBlue (char **text, int *numberOfStr);

void howLetters (char **text, int *numberOfStr);

void deletthree (char **text, int *numberOfStr);

void bubbleSort (char **text, int *numberOfStr);

void int2char (int howWord, char *doStr);

int comp (const void *a, const void *b);

int main (){
    int numberOfStr = 0 ;
    char **text;
    int i = 0;
    
    readAndProcess(&numberOfStr, &text);
    numberOfStr = menu(text,numberOfStr);
    
    for (i = 0; i < numberOfStr; i++)
        free(text[i]);
    free(text);

return 0;
}

int readAndProcess(int *numberOfStr, char ***text){

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
    *numberOfStr = numOfStr;

    return 0;
}

int menu(char **text, int numberOfStr){
    char func;
    int i = 0;
    
    printf("1 - Вывести каждое предложение, и если в нем есть словосочетание “define BLUE”, то все слова после этого словосочетания вывести голубым цветом.\n");
    printf("2 - Во всем тексте заменить последовательность подряд идущих букв без учета регистра подстрокой вида “<кол-во подряд идущих букв><буква в верхнем регистре>”.\n");
    printf("3 - Удалить все предложения в которых количество слов кратно трем.\n");
    printf("4 - Отсортировать предложения по уменьшению суммарной длины первого и последнего слова. Если в предложении одно слово, то необходимо брать длину этого слова.\n");
    printf("P - Вывести массив строк\n");
    printf("0 - Завершить программу\n");
    start:
    printf("Введите номер функции: ");
    scanf("%s", &func);
    printf("    выбранная функция -> %c\n",func);

    switch(func){

        case '1':
            findBlue(text, &numberOfStr);
            goto start;
        break;

        case '2':
            howLetters(text, &numberOfStr);
            goto start;
        break;

        case '3':
            deletthree (text, &numberOfStr);
            goto start;
        break;

        case '4':
            qsort(text,numberOfStr,sizeof(*text),comp);
            goto start;
        break;

        case 'P':
            for (i = 0; i < numberOfStr; i++)
                printf("%s\n",text[i]); 
            goto start;
        break;

        case '0':
        break;

        default:
            printf("\033[0;31mФункции %c не существует\n\033[0m", func);
            goto start;
        break;
    }
    return numberOfStr;
}

void findBlue (char **text, int *numberOfStr){
    char find[] = "define BLUE";
    char *haveDef;
    int i = 0;
    int j = 0;
    int ind = 0;
    
    for(i = 0; i < *numberOfStr; i++){
        haveDef = strstr(text[i],find);
        if ( haveDef == NULL)
            printf ("%s\n",text[i]);
        else{
            ind = (int)(haveDef - text[i]+11);
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
            while(tolower(text[i][j]) == tolower(text[i][j+1]) && isalpha(text[i][j])){
                howWord++;
                j++;
            }
            if(howWord > 1){
                char *doStr = (char*) malloc(sizeof(char));
                int2char(howWord, doStr);   
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


void int2char(int howWord, char *doStr){
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

int comp (const void *a, const void *b){
    int howA = 0;
    int howB = 0;
    int j = 0;
    const char *str_a = *(const char *const *) a; 
    const char *str_b = *(const char *const *) b;

    j = (str_a[0] == ' ') ? 1 : 0;
    for (j;str_a[j] != ' ' && str_a[j] != ','; j++)
        howA++;
    for (j = strlen(str_a)-2;str_a[j] != ' '; j--)
        howA++;
    if (howA > strlen(str_a))
        howA = strlen(str_a)-2;
    
    j = (str_b[0] == ' ') ? 1 : 0;
    for (j;str_b[j] != ' ' && str_b[j] != ','; j++)
        howB++;
    for (j = strlen(str_b)-2;str_b[j] != ' '; j--)
        howB++;
    if (howB > strlen(str_b))
        howB = strlen(str_b)-2;
    if(howA > howB)
        return 1;
    if (howA < howB)
        return -1;
    if (howA == howB)
        return 0;
}