#include "Lockers.h"


// Función para limpiar el buffer de entrada
void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Función para generar un ID único para un nuevo locker
char* id_generator(Locker *l, int tamanio_vector) {
    int id_generada = 1;

    // Si hay lockers en el vector, obtiene el último ID y genera uno nuevo incrementándolo
    if (tamanio_vector != 0) {
        id_generada = atoi(l[tamanio_vector - 1].id_locker + 4) + 1;
    }

    // Asigna memoria para el ID generado
    char* id = malloc(11 * sizeof(char));
    if (id == NULL) {
        printf("Error al asignar memoria. \n");
        exit(EXIT_FAILURE);
    }

    // Formatea la nueva ID y la guarda en el arreglo
    char id2[5];
    sprintf(id2, "%03d", id_generada); 
    strcpy(id, "Lock");
    strcat(id, id2);

    return id;
}

// Función para dar de alta un nuevo locker
void alta_locker(Locker **l, int* tamanio_vector){

    Locker nuevo_locker;
    // Genera un nuevo ID para el locker
    char *cadena = id_generator(*l, *tamanio_vector); 
    strcpy(nuevo_locker.id_locker, cadena);
    free(cadena); // Libera la memoria asignada para el ID generado
    
    // Solicita al usuario información sobre el nuevo locker
    printf("\nDime la localidad:");
    scanf("%20s", nuevo_locker.localidad);
    flushInputBuffer();

    printf("\nDime la provincia:");
    scanf("%20s", nuevo_locker.provincia);
    flushInputBuffer();

    printf("\nDime la direccion:");
    scanf("%20s", nuevo_locker.ubicacion);
    flushInputBuffer();

    printf("\nDime cuantos lockers hay en total:");
    scanf("%d", &nuevo_locker.num_compt); 
    // Realiza una realocación de memoria para agregar el nuevo locker al arreglo
    *l = (Locker *)realloc(*l, (*tamanio_vector + 1) * sizeof(Locker));
    (*l)[*tamanio_vector] = nuevo_locker; // Guarda el nuevo locker en el arreglo
    (*tamanio_vector)++;
    nuevo_locker.num_compocup=0;
}

int ocupados_lockers(Locker *l, int tamanio, char *id) {
    
	for (int i = 0; i < tamanio; i++) {
        if (strcmp(id, l[i].id_locker) == 0) { // Compara el ID dado con el ID del locker en la posición i
            if (l[i].num_compt > l[i].num_compocup) { // Verifica si hay compartimentos disponibles
                l[i].num_compocup++; // Incrementa el contador de compartimentos ocupados
                printf("Se ha añadido correctamente\n");
                return 0; // Devuelve 0 si no está lleno
            } else {
                printf("El locker está lleno\n");
                return 1; // Devuelve 1 si está lleno
            }
        }
    }
    printf("El ID del locker no se encontró en el sistema\n");
    return -1; // Devuelve -1 si no se encontró el ID del locker
}

// Función para dar de baja un locker existente
void baja_locker(Locker *l , int* tamanio, char *id_baja){

    int encontrado = 0;

    // Busca el locker con el ID dado y lo elimina del arreglo
    for(int i = 0 ; i < *tamanio ; i++) {
        if(strcmp(l[i].id_locker, id_baja) == 0){
            encontrado = 1;

            // Reorganiza el arreglo para eliminar el locker encontrado
            for(int j = i; j < *tamanio - 1; j++) {
                l[j] = l[j + 1];
            }

            (*tamanio)--; // Reduce el tamaño del arreglo
            printf("Locker con ID %s ha sido dado de baja correctamente.\n", id_baja);
            break; // Sale del bucle una vez encontrado y eliminado el locker
        }
    }

    if(encontrado == 0){
        printf("La ID registrada no ha sido encontrada.\n");
    }
}

// Función para mostrar un listado de todos los lockers dados de alta
void listado_locker(Locker *l, int tamanio){

    // Recorre el arreglo de lockers y muestra la información de cada uno
    for(int i = 0 ; i < tamanio ; i++){
        printf("%s-%s-%s-%s-%d-%d\n", l[i].id_locker, l[i].localidad, l[i].provincia, l[i].ubicacion, l[i].num_compt, (l[i].num_compocup-1));
    }
}

void busqueda_locker_localidad(Locker *lockers, int* tamanio, char *localidad){ // Se busca un locker en la localidad solicitada por el usuario.
    int coincidencias = 0;

    printf("Productos encontrados de la localidad '%s':\n", localidad);

    for (int i = 0; i < *tamanio; i++) {
        if (strcmp(lockers[i].localidad, localidad) == 0) {
            printf("%s-%s-%s-%s-%d-%d\n", lockers[i].id_locker, lockers[i].localidad, lockers[i].provincia, lockers[i].ubicacion, lockers[i].num_compt, (lockers[i].num_compocup-1));
            printf("\n");
            coincidencias++;
            }
    }
    if (coincidencias == 0) {
        printf("No se encontraron Lockers en la localidad '%s'.\n", localidad);
    }
}



int main()
{
    Locker *lockers = malloc(100 * sizeof(Locker)); 
    int tamanio_lockers = 0; 

    int opcion;
    char id_baja[11];
    char id_locker[11]; // Variable para almacenar el ID del locker a verificar

    do {
        printf("\nMenú de Opciones:\n");
        printf("1. Alta de Locker\n");
        printf("2. Baja de Locker\n");
        printf("3. Verificar disponibilidad de Locker\n"); // Nueva opción
        printf("4. Listado de Lockers\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        flushInputBuffer(); 

        switch (opcion) {
            case 1:
                alta_locker(&lockers, &tamanio_lockers);
                break;
            case 2:
                printf("\nIngrese el ID del Locker a dar de baja: ");
                scanf("%10s", id_baja); 
                flushInputBuffer();
                baja_locker(lockers, &tamanio_lockers, id_baja);
                break;
            case 3:
                printf("\nIngrese el ID del Locker a verificar: ");
                scanf("%10s", id_locker);
                flushInputBuffer();
                ocupados_lockers(lockers, tamanio_lockers, id_locker); // Llama a la función para verificar disponibilidad
                break;
            case 4:
                printf("\nListado de Lockers:\n");
                listado_locker(lockers, tamanio_lockers); 
                break;
            case 5:
                printf("\nSaliendo del programa.\n");
                break;
            default:
                printf("\nOpción no válida. Por favor, seleccione una opción válida.\n");
                break;
        }
    } while (opcion != 5);

    free(lockers); 

    return 0;
}
