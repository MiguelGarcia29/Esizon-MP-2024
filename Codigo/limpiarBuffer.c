#include "limpiarBuffer.h"

//Depura el buffer.
void flushInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}