void howLetters (char **text, int *numberOfStr){
    int i = 0;
    int j = 0;
    int p = 0;
    int howWord = 1;
    char t;
    
    int lenNewStr = 1;
    

    for (i = 0; i < *numberOfStr;i++){
       char *newStr = malloc(sizeof(char));
        
        for(j = 0; j < strlen(text[i]); j++){
            lenNewStr++;
            while (tolower(text[i][j]) == tolower(text[i][j+1])){
                howWord++;
                j++;
            }
           /* if(howWord > 1){
                char *doStr = malloc(sizeof(char));
                char2int(howWord, doStr);
                strcat(newStr,doStr);
                lenNewStr += strlen(doStr);
                free(doStr);
            }*/
            howWord = 1;
        }
        lenNewStr = 1;
       // for( j = 0; j < strlen(newStr); j++) printf("%c",newStr[j]);
       printf("%s\n",newStr);
        free(newStr);
    }
   

}
