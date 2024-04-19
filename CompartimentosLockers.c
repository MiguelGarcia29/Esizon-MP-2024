#include "CompartimentosLockers.h"

void fecha_caducidad_compartimento(char *fecha) {
    time_t rawtime;
    struct tm *info;

    // Obtener la fecha y hora actual
    time(&rawtime);
    rawtime += 7 * 24 * 60 * 60; // 7 días en segundos

    info = localtime(&rawtime);
    strftime(fecha, 11, "%d/%m/%Y", info);
}

void alta_comportimiento(CompartimentoLocker **l, int* tamanio_vector) {
    CompartimentoLocker nuevo_compartimento;
    char fecha[11];
    obtener_fecha_actual(fecha);
    strcpy(nuevo_compartimento.fecha_ocupacion, fecha);

    char fechacaducidad[11];
    fecha_caducidad_compartimento(fechacaducidad);
    strcpy(nuevo_compartimento.fecha_caducidad, fechacaducidad);

    strcpy(nuevo_compartimento.estado, "ocupado");

    // Realiza una realocación de memoria para agregar el nuevo locker al arreglo
    *l = (CompartimentoLocker *)realloc(*l, (*tamanio_vector + 1) * sizeof(CompartimentoLocker));
    if (*l == NULL) {
        printf("Error al asignar memoria para el nuevo locker. \n");
        exit(EXIT_FAILURE);
    }
    (*l)[*tamanio_vector] = nuevo_compartimento; // Guarda el nuevo locker en el arreglo
    (*tamanio_vector)++;
}

void baja_comportamiento(CompartimentoLocker *l, int* tamanio, char *id_baja, char *codigo_de_baja) {
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

void listado_comportamiento(CompartimentoLocker *l, int tamanio) {
    // Recorre el arreglo de lockers y muestra la información de cada uno
    for (int i = 0; i < tamanio; i++) {
        printf("%s-%d-%s-%s-%s-%s\n", l[i].id_locker, l[i].num_comp, l[i].cod_locker, l[i].estado, l[i].fecha_ocupacion,l[i].fecha_caducidad );
    }
}


// Guarda el vector de ComportamientoLocker en el archivo siguiendo la estructura:
/*
    o Identificador del locker (Id_locker), 10 caracteres máximo.
    o Número de compartimento (Num_comp).
    o Código del locker (Cod_locker).
    o Estado: «ocupado» o «vacío»
    o Fecha ocupación (día, mes y año).
    o Fecha caducidad (día, mes y año).
*/
void guardarCompartimentoLockerEnArchivo(CompartimentoLocker *comportamientos, int numComportamientos)
{
    FILE *archivo = fopen(CompartimentoLocker_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo CompartimentosLockers.txt.\n");
        return;
    }

    for (int i = 0; i < numComportamientos; i++)
    {
        fprintf(archivo, "%s-%d-%s-%s-%s-%s-\n",
                comportamientos[i].id_locker,
                comportamientos[i].num_comp,
                comportamientos[i].cod_locker,
                comportamientos[i].estado,
                comportamientos[i].fecha_ocupacion,
                comportamientos[i].fecha_caducidad);
    }

    fclose(archivo);
}

CompartimentoLocker *iniciarCompartimientoLockersDeArchivo(int *numCompLock)
{
    FILE *archivo = fopen(CompartimentoLocker_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", CompartimentoLocker_txt);
        return NULL;
    }

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de Locker
    CompartimentoLocker *comportamientoL = (CompartimentoLocker *)malloc(count * sizeof(CompartimentoLocker));

    if (comportamientoL == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de ComportamientoLocker.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(comportamientoL[i].id_locker, token, sizeof(comportamientoL[i].id_locker));
        token = strtok(NULL, "-");
        comportamientoL[i].num_comp = atoi(token);
        token = strtok(NULL, "-");
        strncpy(comportamientoL[i].cod_locker, token, sizeof(comportamientoL[i].cod_locker));
        token = strtok(NULL, "-");
        strncpy(comportamientoL[i].estado, token, sizeof(comportamientoL[i].estado));
        token = strtok(NULL, "-");
        strncpy(comportamientoL[i].fecha_ocupacion, token, sizeof(comportamientoL[i].fecha_ocupacion));
        token = strtok(NULL, "-");
        strncpy(comportamientoL[i].fecha_caducidad, token, sizeof(comportamientoL[i].fecha_caducidad));

        i++;
    }

    fclose(archivo);
    *numCompLock = count;
    return comportamientoL;
}


/*
int main() {
    CompartimentoLocker *lockers = NULL; // Arreglo dinámico de lockers
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
}*/
