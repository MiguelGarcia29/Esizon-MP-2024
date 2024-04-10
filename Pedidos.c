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

//Hace un pedido recibiendo previamente una lista de los productos que desea comprar el usuario, hay que buscar algo para que no de error
void hacerPedido(Producto *listaCompra, int tamLista,Producto *productos, int numnProductos, Pedido **pedidos, int *numPedidos, ProductoPedido **prodPeds,int *numProdPe, char *idCliente, char *tipoEntrega, char *idLocker, float *costeTotal)
{

    // CREO EL NUEVO PEDIDO
    Pedido nuevo;

    strcpy(nuevo.id_pedido, id_generator_pedido(*pedidos, *numPedidos));
    obtener_fecha_actual(&nuevo.fecha_pedido);
    strcpy(nuevo.lugar_entrega, tipoEntrega);
    strcpy(nuevo.id_locker, idLocker);
    strcpy(nuevo.id_cliente, idCliente);

    *pedidos = (Pedido *)realloc(*pedidos, (*numPedidos + 1) * sizeof(Pedido));
    (*pedidos)[*numPedidos] = nuevo;
    (*numPedidos)++;

    float coste = 0;
    // CREO LOS PRODUCTOSPEDIDOS
    for (int i = 0; i < *numProdPe; i++)
    {
        ProductoPedido prodPed;
        strcpy(prodPed.id_pedido, nuevo.id_pedido);
        strcpy(prodPed.id_prod, listaCompra[i].id_prod);

        do{
        printf("Cuantas unidades quieres de %s:", listaCompra[i].nombre);
        scanf("%d", &prodPed.num_unid);
        flushInputBuffer();
        }while(prodPed.num_unid <= 0 || reducirStock(productos,&numPedidos,prodPed.id_prod,prodPed.num_unid)!=0); //

        prodPed.importe = prodPed.num_unid * listaCompra[i].importe;
        coste += prodPed.importe;
        strcpy(prodPed.estado_pedido, "enPreparacion");
        strcpy(prodPed.id_locker, idLocker);

        *prodPeds = (ProductoPedido *)realloc(*prodPeds, (*numProdPe + 1) * sizeof(ProductoPedido));
        (*prodPeds)[*numProdPe] = prodPed;
        (*numProdPe)++;
    }

    (*costeTotal) = coste;
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
    printf("Datos de pedidos guardados en el archivo Pedidos.txt.\n");
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
