#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    char id_locker[11];
    int num_comp;
    char cod_locker[11];
    char estado[7]; // "ocupado" o "vacío"
    char fecha_ocupacion[11];
    char fecha_caducidad[11];
} ComportamientoLocker;

void obtener_fecha_actual(char *fecha_actual) {
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(fecha_actual, 11, "%d/%m/%Y", info);
   
}

void fecha_caducidad(char *fecha) {
    time_t rawtime;
    struct tm *info;
    
    // Obtener la fecha y hora actual
    time(&rawtime);
    rawtime += 7 * 24 * 60 * 60; // 7 días en segundos
    
    info = localtime(&rawtime);
    strftime(fecha, 11, "%d/%m/%Y", info);
}

int id_generator(int tamanio_vector) {
    return tamanio_vector + 1;
}

void alta_comportimiento(ComportamientoLocker **l, int* tamanio_vector) {
    ComportamientoLocker nuevo_compartimento;
    char fecha[11];
    obtener_fecha_actual(fecha);
    strcpy(nuevo_compartimento.fecha_ocupacion, fecha);

    char fechacaducidad[11];
    fecha_caducidad(fechacaducidad);
    strcpy(nuevo_compartimento.fecha_caducidad, fechacaducidad);
    
    strcpy(nuevo_compartimento.estado, "ocupado");
    
    // Realiza una realocación de memoria para agregar el nuevo locker al arreglo
    *l = (ComportamientoLocker *)realloc(*l, (*tamanio_vector + 1) * sizeof(ComportamientoLocker));
    if (*l == NULL) {
        printf("Error al asignar memoria para el nuevo locker. \n");
        exit(EXIT_FAILURE);
    }
    (*l)[*tamanio_vector] = nuevo_compartimento; // Guarda el nuevo locker en el arreglo
    (*tamanio_vector)++;
}

void baja_comportamiento(ComportamientoLocker *l, int* tamanio, char *id_baja, char *codigo_de_baja) {
    int encontrado = 0;

    // Busca el locker con el ID dado y lo elimina del arreglo
    for (int i = 0; i < *tamanio; i++) {
        if (strcmp(l[i].id_locker, id_baja) == 0 && strcmp(l[i].cod_locker, codigo_de_baja) == 0) {
            encontrado = 1;

            // Reorganiza el arreglo para eliminar el locker encontrado
            for (int j = i; j < *tamanio - 1; j++) {
                l[j] = l[j + 1];
            }

            (*tamanio)--; // Reduce el tamaño del arreglo
            printf("Compartimento ha sido dado de baja correctamente.\n", id_baja);
            break; // Sale del bucle una vez encontrado y eliminado el locker
        }
    }

    if (encontrado == 0) {
        printf("La ID registrada no ha sido encontrada.\n");
    }
}

void listado_comportamiento(ComportamientoLocker *l, int tamanio) {
    // Recorre el arreglo de lockers y muestra la información de cada uno
    for (int i = 0; i < tamanio; i++) {
        printf("%s-%d-%s-%s-%s-%s\n", l[i].id_locker, l[i].num_comp, l[i].cod_locker, l[i].estado, l[i].fecha_ocupacion,l[i].fecha_caducidad );
    }
}

// Función para limpiar el buffer de entrada
void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    ComportamientoLocker *lockers = NULL; // Arreglo dinámico de lockers
    int tamanio_vector = 0; // Tamaño inicial del vector

    int opcion;
    char id[11];
    char codigo[11];

    do {
        printf("\nMenú:\n");
        printf("1. Alta de comportamiento\n");
        printf("2. Baja de comportamiento\n");
        printf("3. Listado de comportamiento\n");
        printf("4. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                alta_comportimiento(&lockers, &tamanio_vector);
                break;
            case 2:
                printf("Ingrese el ID del comportamiento a dar de baja: ");
                scanf("%s", id);
                flushInputBuffer(); // Limpiar el buffer de entrada después de leer una cadena de caracteres
                printf("Ingrese el código del comportamiento a dar de baja: ");
                scanf("%s", codigo);
                flushInputBuffer(); // Limpiar el buffer de entrada después de leer una cadena de caracteres
                baja_comportamiento(lockers, &tamanio_vector, id, codigo);
                break;
            case 3:
                listado_comportamiento(lockers, tamanio_vector);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Por favor, ingrese una opción válida.\n");
        }
    } while (opcion != 4);

    // Liberar memoria asignada para los lockers
    if (lockers != NULL) {
        free(lockers);
        lockers = NULL;
    }

    return 0;
}
