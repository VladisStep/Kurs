#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int reedAndSort (int *numberOfStr, char ***text);

int main(){
    int i = 0;
    char **text;
    int numberOfStr = 0;
    reedAndSort (&numberOfStr, &text);
    for (i = 0; i< numberOfStr; i++) printf("%d. %s\n",i, text[i]);
    
    
}

int reedAndSort (int *numberOfStr, char ***text){
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
