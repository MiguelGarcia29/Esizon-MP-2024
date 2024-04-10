#include "Devolucion.h"

int pedido_existe(ProductoPedido *pedido, int tamanio_pedido, char *id_pedido) {
    for (int i = 0; i < tamanio_pedido; i++) {
        if (strcmp(pedido[i].id_pedido, id_pedido) == 0) {
            return 1; // El pedido existe
        }
    }
    return 0; // El pedido no existe
}

void alta_devolucion_admin(Devolucion **devoluciones, int *num_devoluciones, ProductoPedido *pedidos, int tamanio_pedidos) {
    char id_pedido[8];
    printf("\nIngrese el ID del pedido: ");
    scanf("%s", id_pedido);

    if (pedido_existe(pedidos, tamanio_pedidos, id_pedido)) {
        Devolucion nueva_devolucion;
        strcpy(nueva_devolucion.id_pedido, id_pedido);
        printf("Ingrese el ID del producto: ");
        scanf("%s", nueva_devolucion.id_prod);
        obtener_fecha_actual(nueva_devolucion.fecha_devolucion);
        printf("Ingrese el motivo de la devolución: ");
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
        printf("Ingrese el motivo de la devolución: ");
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

void baja_devolucion(Devolucion **devoluciones, int *num_devoluciones, char *id_devolucion) {
    int encontrado = 0;
    for (int i = 0; i < *num_devoluciones; i++) {
        if (strcmp((*devoluciones)[i].id_pedido, id_devolucion) == 0) {
            encontrado = 1;

            for (int j = i; j < *num_devoluciones - 1; j++) {
                (*devoluciones)[j] = (*devoluciones)[j + 1];
            }
            (*num_devoluciones)--;
            printf("Devolución con ID %s eliminada correctamente.\n", id_devolucion);
            break;
        }
    }
    if (!encontrado) {
        printf("Devolución con ID %s no encontrada.\n", id_devolucion);
    }
}

void buscar_devolucion(Devolucion *devoluciones, int num_devoluciones, char *id_devolucion) {
    int encontrado = 0;
    for (int i = 0; i < num_devoluciones; i++) {
        if (strcmp(devoluciones[i].id_pedido, id_devolucion) == 0) {
            printf("ID del pedido: %s\n", devoluciones[i].id_pedido);
            printf("ID del producto: %s\n", devoluciones[i].id_prod);
            printf("Fecha de devolución: %s\n", devoluciones[i].fecha_devolucion);
            printf("Motivo: %s\n", devoluciones[i].motivo);
            printf("Estado: %s\n", devoluciones[i].estado);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Devolución con ID %s no encontrada.\n", id_devolucion);
    }
}

void listar_devoluciones(Devolucion *devoluciones, int num_devoluciones) {
    printf("\nListado de Devoluciones:\n");
    for (int i = 0; i < num_devoluciones; i++) {
       printf("%s-%s-%s-%s-%s\n", devoluciones[i].id_pedido,devoluciones[i].id_prod,devoluciones[i].fecha_devolucion,devoluciones[i].motivo,devoluciones[i].estado);
    }
}

void devoluciones_pendientes(Devolucion *devoluciones, int num_devoluciones) {
    printf("\nDevoluciones Pendientes de Aceptación:\n");
    for (int i = 0; i < num_devoluciones; i++) {
        if (strcmp(devoluciones[i].estado, "pendiente") == 0) {
            printf("%s-%s-%s-%s\n",
                   devoluciones[i].id_pedido, devoluciones[i].id_prod, devoluciones[i].fecha_devolucion,
                   devoluciones[i].motivo);
        }
    }
}

void modificar_estado_enviado(Devolucion *devoluciones, int num_devoluciones, char *id_devolucion) {
    int encontrado = 0;
    for (int i = 0; i < num_devoluciones; i++) {
        if (strcmp(devoluciones[i].id_pedido, id_devolucion) == 0) {
            strcpy(devoluciones[i].estado, "enviado");
            printf("Estado de la devolución con ID %s cambiado a 'enviado'.\n", id_devolucion);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Devolución con ID %s no encontrada.\n", id_devolucion);
    }
}
/*
int main() {
    Devolucion *devoluciones = NULL;

    Cliente actual;
    strcpy(actual.id_cliente, "0000002");
    int num_devoluciones = 0;
    int opcion;
    int usu;
    char id[8];
    ProductoPedido pedidos[10]; // Definir un arreglo de pedidos como ejemplo

    do {
        printf("\nMenú de Opciones:\n");
        printf("1. Alta de Devolución\n");
        printf("2. Baja de Devolución\n");
        printf("3. Buscar Devolución\n");
        printf("4. Listar Devoluciones\n");
        printf("5. Devoluciones Pendientes de Aceptación\n");
        printf("6. Modificar Estado a 'Enviado'\n");
        printf("7. Salir\n");
        printf("Elige una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Dime si eres admin o usuario: 1-Admin 2-Cliente \n");
                scanf("%d", &usu);
                if(usu==1)
                {
                    alta_devolucion_admin(&devoluciones, &num_devoluciones, pedidos, sizeof(pedidos) / sizeof(pedidos[0]));
                }
                else
                {
                    printf("Dime el id de usuario: ");
                    scanf("%s", id);
                    alta_devolucion_cliente(&devoluciones, &num_devoluciones, actual, pedidos, sizeof(pedidos) / sizeof(pedidos[0]));
                }
                break;
            case 2:
                if (num_devoluciones > 0) {
                    char id_baja[8];
                    printf("\nIngrese el ID de la devolución a dar de baja: ");
                    scanf("%s", id_baja);
                    baja_devolucion(&devoluciones, &num_devoluciones, id_baja);
                } else {
                    printf("No hay devoluciones para dar de baja.\n");
                }
                break;
            case 3:
                if (num_devoluciones > 0) {
                    char id_busqueda[8];
                    printf("\nIngrese el ID de la devolución a buscar: ");
                    scanf("%s", id_busqueda);
                    buscar_devolucion(devoluciones, num_devoluciones, id_busqueda);
                } else {
                    printf("No hay devoluciones para buscar.\n");
                }
                break;
            case 4:
                if (num_devoluciones > 0) {
                    listar_devoluciones(devoluciones, num_devoluciones);
                } else {
                    printf("No hay devoluciones para listar.\n");
                }
                break;
            case 5:
                if (num_devoluciones > 0) {
                    devoluciones_pendientes(devoluciones, num_devoluciones);
                } else {
                    printf("No hay devoluciones pendientes de aceptación.\n");
                }
                break;
            case 6:
                if (num_devoluciones > 0) {
                    char id_enviado[8];
                    printf("\nIngrese el ID de la devolución a marcar como 'enviado': ");
                    scanf("%s", id_enviado);
                    modificar_estado_enviado(devoluciones, num_devoluciones, id_enviado);
                } else {
                    printf("No hay devoluciones para marcar como 'enviado'.\n");
                }
                break;
            case 7:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida. Por favor, seleccione una opción válida.\n");
                break;
        }
    } while (opcion != 7);

    // Liberar memoria dinámica
    free(devoluciones);

    return 0;
}
*/

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
    printf("Datos de devoluciones guardados en el archivo Devoluciones.txt.\n");
}

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

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
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

        i++;
    }

    fclose(archivo);
    *numDevolucion = count;
    return devoluciones;
}
