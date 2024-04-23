#include "Pedidos.h"

char *id_generator_pedido (Pedido *pedidos, int tamanio_vector) {

    int id_generada = 1;

    if (tamanio_vector != 0)
    { // Si no hay nada en el vector, la primer id es 0000011.
        id_generada = atoi(pedidos[tamanio_vector - 1].id_pedido);
        id_generada++;
    }
    char *id = malloc(8 * sizeof(char));
    if (id == NULL)
    {
        printf("Error al guardar memoria\n");
        exit(EXIT_FAILURE);
    }

    sprintf(id, "%07d", id_generada);
    return id;
}


// Guarda el vector de ComportamientoLocker en el archivo siguiendo la estructura:
/*
    o Identificador del pedido (Id_pedido), 7 dígitos.
    o Fecha del pedido (día, mes y año)
    o Identificador del cliente que realiza el pedido (Id_cliente), 7 dígitos.
    o Lugar de entrega (Lugar): «domicilio» o «locker»
    o Identificador de Locker (Id_locker), 10 caracteres máximo.
    o Identificador del código promocional o cheque regalo (Id_cod), 10 caracteres máximo.
*/
void guardarPedidoEnArchivo(Pedido *pedidos, int numPedidos)
{
    FILE *archivo = fopen(Pedido_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Pedidos.txt.\n");
        return;
    }

    for (int i = 0; i < numPedidos; i++)
    {

        // PARA QUE INTRODUZCA UN ESPACIO SI NO HAY LOCKER
        if (strcmp(pedidos[i].lugar_entrega, "locker") != 0)
        {
            strcpy(pedidos[i].id_locker, " ");
        }

        fprintf(archivo, "%s-%s-%s-%s-%s-%s-\n",
                pedidos[i].id_pedido,
                pedidos[i].fecha_pedido,
                pedidos[i].id_cliente,
                pedidos[i].lugar_entrega,
                pedidos[i].id_locker,
                pedidos[i].id_cod);
    }

    fclose(archivo);
}

Pedido *iniciarPedidosDeArchivo(int *numPedidos)
{
    FILE *archivo = fopen(Pedido_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Pedido_txt);
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
    Pedido *pedidos = (Pedido *)malloc(count * sizeof(Pedido));
    if (pedidos == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de Pedido.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(pedidos[i].id_pedido, token, sizeof(pedidos[i].id_pedido));
        token = strtok(NULL, "-");
        strncpy(pedidos[i].fecha_pedido, token, sizeof(pedidos[i].fecha_pedido));
        token = strtok(NULL, "-");
        strncpy(pedidos[i].id_cliente, token, sizeof(pedidos[i].id_cliente));
        token = strtok(NULL, "-");
        strncpy(pedidos[i].lugar_entrega, token, sizeof(pedidos[i].lugar_entrega));
        token = strtok(NULL, "-");
        // SI NO ESTA EN LOCKER QUE DEJE ID LOCKER VACIA
        if (strcmp(pedidos[i].lugar_entrega, "locker") != 0)
            strncpy(pedidos[i].id_locker, "", sizeof(pedidos[i].id_locker));
        else
            strncpy(pedidos[i].id_locker, token, sizeof(pedidos[i].id_locker));
        token = strtok(NULL, "-");
        strncpy(pedidos[i].id_cod, token, sizeof(pedidos[i].id_cod));

        i++;
    }

    fclose(archivo);
    *numPedidos = count;
    return pedidos;
}

void baja_pedido(Pedido **pedidos, int *npedidos, char *id_pedido_baja) {
    int i, j;
    for (i = 0; i < *npedidos; i++) {
        if (strcmp((*pedidos)[i].id_pedido, id_pedido_baja) == 0) {
            // Si se encuentra el pedido, se eliminan los datos de esa posición
            for (j = i; j < *npedidos - 1; j++) {
                (*pedidos)[j] = (*pedidos)[j + 1];
            }
            (*npedidos)--; // Se reduce la cantidad de pedidos
            printf("Pedido dado de baja.\n" );
            return;
        }
    }
    printf("No se encontro ningun pedido con el ID.\n");
}

void listado_pedido_cliente(Pedido **pedidos, int* tamanio, char *idC) {
    for (int i = 0; i < *tamanio; i++) {
        if (strcmp((*pedidos)[i].id_cliente, idC) == 0) {
            printf("ID Pedido: %s\n", (*pedidos)[i].id_pedido);
            printf("Fecha Pedido: %s\n", (*pedidos)[i].fecha_pedido);
            printf("ID Cliente: %s\n", (*pedidos)[i].id_cliente);
            printf("Lugar de Entrega: %s\n", (*pedidos)[i].lugar_entrega);
            printf("ID Locker: %s\n", (*pedidos)[i].id_locker);
            printf("ID COD: %s\n", (*pedidos)[i].id_cod);
        }
    }
}

void buscar_pedido_cliente(Pedido **pedidos, int* tamanio, char *idC, char *idProducto) {
    for (int i = 0; i < *tamanio; i++) {

        if (strcmp((*pedidos)[i].id_cliente, idC) == 0 && strcmp((*pedidos)[i].id_cod, idProducto) == 0) {
            // Si coincide, imprimir los detalles del pedido
            printf("ID Pedido: %s\n", (*pedidos)[i].id_pedido);
            printf("Fecha Pedido: %s\n", (*pedidos)[i].fecha_pedido);
            printf("ID Cliente: %s\n", (*pedidos)[i].id_cliente);
            printf("Lugar de Entrega: %s\n", (*pedidos)[i].lugar_entrega);
            printf("ID Locker: %s\n", (*pedidos)[i].id_locker);
            printf("ID COD: %s\n", (*pedidos)[i].id_cod);
        }
    }
}

