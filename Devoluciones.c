#include "Devolucion.h"

// Función para verificar si un pedido existe en la lista de pedidos
int pedido_existe(ProductoPedido **pedido, int *tamanio_pedido, char *id_pedido) {
    for (int i = 0; i < *tamanio_pedido; i++) {
        if (strcmp((*pedido)[i].id_pedido, id_pedido) == 0) {
            return 1; // El pedido existe
        }
    }
    return 0; // El pedido no existe
}

// Función para dar de alta una devolución por parte de un administrador
void alta_devolucion_admin(Devolucion **devoluciones, int *num_devoluciones, ProductoPedido **pedidos, int *tamanio_pedidos) {
    char id_pedido[8];
    printf("\nIngrese el ID del pedido: ");
    scanf("%s", id_pedido);

    if (pedido_existe((*pedidos), *tamanio_pedidos, id_pedido)) {
        Devolucion nueva_devolucion;
        strcpy(nueva_devolucion.id_pedido, id_pedido);
        printf("Ingrese el ID del producto: ");
        scanf("%s", nueva_devolucion.id_prod);
        obtener_fecha_actual(nueva_devolucion.fecha_devolucion);
        printf("Ingrese el motivo de la devolucion: ");
        scanf(" %[^\n]", nueva_devolucion.motivo);
        strcpy(nueva_devolucion.estado, "pendiente");

        *devoluciones = (Devolucion*)realloc(*devoluciones, (*num_devoluciones + 1) * sizeof(Devolucion));
        if (*devoluciones == NULL) {
            printf("Error al asignar memoria.\n");
            exit(EXIT_FAILURE);
        }

        (*devoluciones)[*num_devoluciones] = nueva_devolucion;
        (*num_devoluciones)++;
    } else {
        printf("El pedido no ha sido encontrado o no existe.\n");
    }
}

// Función para dar de alta una devolución por parte de un cliente
void alta_devolucion_cliente(Devolucion **devoluciones, int *num_devoluciones, Cliente actual, ProductoPedido *pedidos, int tamanio_pedidos) {
    char id_pedido[8];
    printf("\nIngrese el ID del pedido: ");
    scanf("%s", id_pedido);

    if (pedido_existe(pedidos, tamanio_pedidos, id_pedido)) {
        Devolucion nueva_devolucion;
        strcpy(nueva_devolucion.id_pedido, id_pedido);
        printf("Ingrese el ID del producto: ");
        scanf("%s", nueva_devolucion.id_prod);
        obtener_fecha_actual(nueva_devolucion.fecha_devolucion);
        printf("Ingrese el motivo de la devolucion: ");
        scanf(" %[^\n]", nueva_devolucion.motivo);
        strcpy(nueva_devolucion.estado, "pendiente");

        *devoluciones = (Devolucion*)realloc(*devoluciones, (*num_devoluciones + 1) * sizeof(Devolucion));
        if (*devoluciones == NULL) {
            printf("Error al asignar memoria.\n");
            exit(EXIT_FAILURE);
        }

        (*devoluciones)[*num_devoluciones] = nueva_devolucion;
        (*num_devoluciones)++;
    } else {
        printf("El pedido no ha sido encontrado o no existe.\n");
    }
}

// Función para dar de baja una devolución
void baja_devolucion(Devolucion **devoluciones, int *num_devoluciones, char *id_devolucion) {
    int encontrado = 0;
    for (int i = 0; i < *num_devoluciones; i++) {
        if (strcmp((*devoluciones)[i].id_pedido, id_devolucion) == 0) {
            encontrado = 1;

            for (int j = i; j < *num_devoluciones - 1; j++) {
                (*devoluciones)[j] = (*devoluciones)[j + 1];
            }
            (*num_devoluciones)--;
            printf("Devolucion con ID %s eliminada correctamente.\n", id_devolucion);
            break;
        }
    }
    if (!encontrado) {
        printf("Devolucion con ID %s no encontrada.\n", id_devolucion);
    }
}

// Función para buscar una devolución por su ID
void buscar_devolucion(Devolucion **devoluciones, int *num_devoluciones, char *id_devolucion) {
    int encontrado = 0;
    for (int i = 0; i < *num_devoluciones; i++) {
        if (strcmp((*devoluciones)[i].id_pedido, id_devolucion) == 0) {
            printf("ID del pedido: %s\n", (*devoluciones)[i].id_pedido);
            printf("ID del producto: %s\n", (*devoluciones)[i].id_prod);
            printf("Fecha de devolucion: %s\n", (*devoluciones)[i].fecha_devolucion);
            printf("Motivo: %s\n", (*devoluciones)[i].motivo);
            printf("Estado: %s\n", (*devoluciones)[i].estado);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Devolucion con ID %s no encontrada.\n", id_devolucion);
    }
}

// Función para listar todas las devoluciones
void listar_devoluciones(Devolucion **devoluciones, int *num_devoluciones) {
    printf("\nListado de Devoluciones:\n");
    for (int i = 0; i < *num_devoluciones; i++) {
       printf("%s-%s-%s-%s-%s\n", (*devoluciones)[i].id_pedido,(*devoluciones)[i].id_prod,(*devoluciones)[i].fecha_devolucion,(*devoluciones)[i].motivo,(*devoluciones)[i].estado);
    }
}

// Función para mostrar las devoluciones pendientes de aceptación
void devoluciones_pendientes(Devolucion *devoluciones, int num_devoluciones) {
    printf("\nDevoluciones Pendientes de Aceptacion:\n");
    for (int i = 0; i < num_devoluciones; i++) {
        if (strcmp(devoluciones[i].estado, "pendiente") == 0) {
            printf("%s-%s-%s-%s\n",
                   devoluciones[i].id_pedido, devoluciones[i].id_prod, devoluciones[i].fecha_devolucion,
                   devoluciones[i].motivo);
        }
    }
}

// Función para modificar el estado de una devolución a "enviado"
void modificar_estado_enviado(Devolucion *devoluciones, int num_devoluciones, char *id_devolucion) {
    int encontrado = 0;
    for (int i = 0; i < num_devoluciones; i++) {
        if (strcmp(devoluciones[i].id_pedido, id_devolucion) == 0) {
            strcpy(devoluciones[i].estado, "enviado");
            printf("Estado de la devolucion con ID %s cambiado a 'enviado'.\n", id_devolucion);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Devolucion con ID %s no encontrada.\n", id_devolucion);
    }
}

// Función para modificar y consultar el estado de las devoluciones pendientes de aceptación por parte de un administrador
void modifYConsultarDevPedAdmin(Devolucion **lista_devoluciones, int *num_devoluciones) {
    printf("Devoluciones pendientes de aceptacion:\n");
    int contador = 0;

    for (int i = 0; i < *num_devoluciones; i++) {
        if (strcmp((*lista_devoluciones)[i].estado, "pendiente") == 0) {
            printf("ID Pedido: %s, ID Producto: %s, Estado: %s\n",
                   (*lista_devoluciones)[i].id_pedido,
                   (*lista_devoluciones)[i].id_prod,
                   (*lista_devoluciones)[i].estado);
            contador++;
        }
    }

    if (contador == 0) {
        printf("No hay devoluciones pendientes de aceptacion.\n");
        return;
    }

    char opcion;
    printf("¿Desea modificar el estado de alguna devolucion? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S') {
        char id[8];
        printf("Ingrese el ID de la devolucion que desea modificar: ");
        scanf("%s", id);

        for (int i = 0; i < *num_devoluciones; i++) {
            if (strcmp((*lista_devoluciones)[i].id_pedido, id) == 0) {
                if (strcmp((*lista_devoluciones)[i].estado, "pendiente") == 0) {
                    printf("¿Aceptar la devolucion? (s/n): ");
                    scanf(" %c", &opcion);
                    if (opcion == 's' || opcion == 'S') {
                        strcpy((*lista_devoluciones)[i].estado, "aceptada");
                        printf("Devolucion aceptada correctamente.\n");
                        printf("Ingrese la fecha de aceptacion (DD/MM/AAAA): ");
                        scanf("%s", (*lista_devoluciones)[i].fecha_aceptacion);
                        printf("Ingrese la nueva fecha de caducidad (DD/MM/AAAA): ");
                        scanf("%s", (*lista_devoluciones)[i].fecha_caducidad);
                    } else {
                        printf("Devolucion rechazada.\n");
                    }
                } else {
                    printf("Esta devolucion ya ha sido aceptada o rechazada.\n");
                }
                return;
            }
        }
        printf("No se encontro ninguna devolucion con el ID especificado.\n");
    }
}

// Función para guardar las devoluciones en un archivo de texto
void guardarDevolucionesEnArchivo(Devolucion *devoluciones, int numDevoluciones)
{
    FILE *archivo = fopen(Devoluciones_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Devoluciones.txt.\n");
        return;
    }

    for (int i = 0; i < numDevoluciones; i++)
    {
        if (strcmp(devoluciones[i].fecha_aceptacion, "") == 0)
            strcpy(devoluciones[i].fecha_aceptacion, " ");
        if (strcmp(devoluciones[i].fecha_caducidad, "") == 0)
            strcpy(devoluciones[i].fecha_caducidad, " ");
        fprintf(archivo, "%s-%s-%s-%s-%s-%s-%s-\n",
                devoluciones[i].id_pedido,
                devoluciones[i].id_prod,
                devoluciones[i].fecha_devolucion,
                devoluciones[i].motivo,
                devoluciones[i].estado,
                devoluciones[i].fecha_aceptacion,
                devoluciones[i].fecha_caducidad);
    }

    fclose(archivo);
}

// Función para iniciar las devoluciones desde un archivo de texto
Devolucion *iniciarDevolucionDeArchivo(int *numDevolucion)
{
    FILE *archivo = fopen(Devoluciones_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Devoluciones_txt);
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

    // Crear el vector de Devoluciones
    Devolucion *devoluciones =(Devolucion *) malloc(count * sizeof(Devolucion));
    if (devoluciones == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de Devoluciones.\n");
        return NULL;
    }

    // Leer cada linea y rellenar el vector
    for(int i=0;i<count;i++)
    {
        if(fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL){
        char *token = strtok(buffer, "-");
        strncpy(devoluciones[i].id_pedido, token, sizeof(devoluciones[i].id_pedido));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].id_prod, token, sizeof(devoluciones[i].id_prod));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].fecha_devolucion, token, sizeof(devoluciones[i].fecha_devolucion));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].motivo, token, sizeof(devoluciones[i].motivo));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].estado, token, sizeof(devoluciones[i].estado));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].fecha_aceptacion, token, sizeof(devoluciones[i].fecha_aceptacion));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].fecha_caducidad, token, sizeof(devoluciones[i].fecha_caducidad));

        }
    }

    fclose(archivo);
    *numDevolucion = count;
    return devoluciones;
}
