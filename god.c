#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main (){

char* test = malloc(sizeof(char));
for (int i = 0; i < 10; i++){
    test = (char*) realloc(test, (i+1)* sizeof(char));
    printf("size = %ld, i = %d\n",sizeof(*test), i);

}
test[0] = 'q';
test[2] = 'e';
printf(test);

return 0;
}