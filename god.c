#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define blue  "\033[0;34m"

int readAndProcess(int *numberOfStr, char ***text);

int comp ( const void *a, const void *b);

int main (){
    int numberOfStr = 0 ;
    char **text;
    int i = 0;
    
    int otv = 1000;
    readAndProcess(&numberOfStr, &text);
    qsort(text,numberOfStr,sizeof(*text),comp);
    //otv = comp(text[1], text[2]);
    //printf("%d\n", otv);
    for (i = 0; i < numberOfStr; i++)
        printf("%s\n",text[i]);
    
    /*for (i = 0; i < numberOfStr; i++)
        free(text[i]);
    free(text);*/

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

int comp (const void *a, const void *b){
    
    int c = 0;
    int d = 0;
    int j = 0;
    const char 
    *str_a = *(const char *const *) a, 
    *str_b = *(const char *const *) b;
   // printf("1.%s 2.%s\n",str_a,str_b);

    j = (str_a[0] == ' ') ? 1 : 0;
    for (j;str_a[j] != ' ' && str_a[j] != ','; j++)
        c++;
    for (j = strlen(str_a)-2;str_a[j] != ' '; j--)
        c++;
    if (c > strlen(str_a))
        c = strlen(str_a)-2;
    
    j = (str_b[0] == ' ') ? 1 : 0;
    for (j;str_b[j] != ' ' && str_b[j] != ','; j++)
        d++;
    for (j = strlen(str_b)-2;str_b[j] != ' '; j--)
        d++;
    if (d > strlen(str_b))
        d = strlen(str_b)-2;
   // printf("1.%d 2.%d\n",c,d);
    if(c > d)
        return 1;
    if (c < d)
        return -1;
    if (c == d)
        return 0;
}