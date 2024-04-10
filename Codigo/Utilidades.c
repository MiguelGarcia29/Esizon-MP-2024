#include <stdio.h>
#include <time.h>


void flushInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void obtener_fecha_actual(char *fecha_actual)
{
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(fecha_actual, 11, "%d/%m/%Y", info);
}
