#include <stdio.h>
#include <time.h>

// Función para limpiar el búfer de entrada
void flushInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Función para obtener la fecha actual y almacenarla en formato dd/mm/yyyy en una cadena dada
void obtener_fecha_actual(char *fecha_actual)
{
    time_t rawtime; // Variable para almacenar el tiempo en segundos desde 1970
    struct tm *info; // Estructura para almacenar la fecha y hora descompuesta
    time(&rawtime); // Obtiene el tiempo actual
    info = localtime(&rawtime); // Convierte el tiempo en la zona horaria local

    // Formatea la fecha y la guarda en la cadena proporcionada
    strftime(fecha_actual, 11, "%d/%m/%Y", info);
}
