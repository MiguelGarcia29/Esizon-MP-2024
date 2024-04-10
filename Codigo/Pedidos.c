#include "Pedidos.h"

char *id_generator_pedido(Pedido *pedidos, int tamanio_vector)
{

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
void hacerPedido(Producto *listaCompra, int tamLista,Producto *productos, int numnProductos, Pedido **pedidos, int *numPedidos, ProductoPedido **prodPeds,
                 int *numProdPe, char *idCliente, char *tipoEntrega, char *idLocker, float *costeTotal)
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
        scanf("%d", prodPed.num_unid);
        depurarBuffer();
        }while(reducirStock(productos,numPedidos,prodPed.id_prod,prodPed.num_unid)!=0);
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

void alta_ticket_pedidos(Pedido **pedidos, int *tamanio_pedidos, Cliente actual_cliente, int *tamanio_cliente, Producto *productos, int *tamanio_productos)
{

    Pedido nuevo_pedido;
    char producto_seleccionado[16]; // Nombre del producto seleccionado
    char lugar_entreg[10];
    char fecha_actual[11];
    int cont = 0;
    int respuesta = 0;
    strcpy(nuevo_pedido.id_pedido, id_generator_pedido(*pedidos, *tamanio_pedidos));
    obtener_fecha_actual(&fecha_actual);

    printf("Que producto va a comprar: \n");
    fgets(producto_seleccionado, 8, stdin);
    flushInputBuffer();

    strcpy(nuevo_pedido.id_cliente, actual_cliente.id_cliente);

    printf("Seleccione el metodo de entrega de su pedido:\n");
    printf("1) En un locker.\n");
    printf("2) En su domicilio.\n");
    scanf("%d", &respuesta);
    switch (respuesta)
    {
    case 1:
        strcpy(nuevo_pedido.lugar_entrega, "locker");
        break;
    case 2:
        strcpy(nuevo_pedido.lugar_entrega, "domicilio");
    default:
        printf("ERROR PEDIDO CANCELADO.\n");
        break;
    }

    // Seleccionar productos.
    seleccionar_producto(productos, tamanio_productos, producto_seleccionado);
    // busqueda_producto_descr(productos, &tamanio_productos, producto_select);
}
