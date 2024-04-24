#include "Productos_pedidos.h"
#include <string.h>
#include <time.h>
void modificar_estado_pedido(ProductoPedido *pedidos, int* tamanio,char *id_modificar);
void modificar_entrega_productoPedido(ProductoPedido *pedidos, int* tamanio,char *id_modificar);

void fecha_entrega(char *fecha, int dia_entrega)
{

    time_t rawtime; // Defino la struct de tiempo.

    // Convertir la fecha actual a time_t
    time(&rawtime);

    // Sumar x días a la fecha actual.
    rawtime += dia_entrega * 24 * 60 * 60; // X días en segundos

    // Actualizar la estructura tm
    struct tm *nueva_fecha = localtime(&rawtime);

    strftime(fecha, 11, "%d/%m/%Y", nueva_fecha); // Convierte la struct tm en un formato legible tal que dia/mes/año
}

char *seleccionar_producto(Producto *productos, int* tamanio, char *productos_select){

    char *producto_Encontrado = NULL;  // Iniciamos una variable local como NULL al comienzo de la función
    int coincidencia;

    for(int i = 0 ; i < *tamanio && coincidencia == 0 ; i++){
        if(strcmp(productos[i].nombre,productos_select) == 0){
            producto_Encontrado = malloc(16 * sizeof(char));
            if(producto_Encontrado == NULL){
                printf("Error al asignar memoria.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(producto_Encontrado, productos[i].id_prod);
            coincidencia++;
        }
    }
    return producto_Encontrado;
}


void baja_prodPed(ProductoPedido **pedidos , int* tamanio, char *id_baja){

    int encontrado = 0;

    for(int i = 0 ; i < *tamanio && encontrado == 0 ; i++) //Comparamos la id que queremos dar de baja con las ids registradas.
    {
        if(strcmp((*pedidos)[i].id_prod,id_baja) == 0){
            encontrado = 1;

        for(int j = i; j < *tamanio - 1; j++) //Reposicionamos las ids posteriores a la dada de baja.
        {
           (*pedidos)[j] = (*pedidos)[j + 1];
        }

        (*tamanio)--; //Reduzco el tamaño del array.
        *pedidos = (ProductoPedido *)realloc(*pedidos, (*tamanio) * sizeof(ProductoPedido));

        printf("Producto con ID %s ha sido de baja correctamente.\n", id_baja);
        }
    }

    if(encontrado == 0){
        printf("La ID registrada no ha sido encontrada.\n");
    }
}

void listado_pedido(ProductoPedido **pedidos, int* tamanio){

    for(int i = 0 ; i < *tamanio ; i++){
        printf("%s-%s-%d-%s-%.2f-%s\n",(*pedidos)[i].id_pedido,(*pedidos)[i].id_prod,(*pedidos)[i].num_unid,(*pedidos)[i].fecha_entrega_prevista,
               (*pedidos)[i].importe,(*pedidos)[i].estado_pedido);
    }
}


void buscarPedido (ProductoPedido **pedidos, int** tamanio , char* id){

    int coincidencia = 0;
    for(int i = 0 ; i < *tamanio ; i++ ){

        if(strcmp((*pedidos)[i].id_pedido,id) == 0){

            printf("%s-%s-%d-%s-%.2f-%s\n",(*pedidos)[i].id_pedido,(*pedidos)[i].id_prod,(*pedidos)[i].num_unid,(*pedidos)[i].fecha_entrega_prevista,
                   (*pedidos)[i].importe,(*pedidos)[i].estado_pedido);
            printf("\n");
            coincidencia++;
            }
        }

}


void modificar_estado_pedido(ProductoPedido *pedidos, int* tamanio,char *ID_producto){

    int i = 0;

    while(i < *tamanio && strcmp(pedidos[i].id_prod,ID_producto) != 0){
        i++;    // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    printf("Escribe el estado del pedido: \n");
	fgets(pedidos[i].estado_pedido,15,stdin);
    flushInputBuffer();
}



void modificar_entrega_productoPedido(ProductoPedido *pedidos, int* tamanio,char *ID_producto){

    int i = 0;
    int dia_retraso;

    while(i < *tamanio && strcmp(pedidos[i].id_prod,ID_producto) != 0){
        i++;    // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    // COMPROBAR FUNC DE LA SUMA DE DIAS.
    printf("Escribe el retraso que puede tener el pedido: ");
	scanf("%d",&dia_retraso);
    fecha_entrega(pedidos[i].fecha_entrega_prevista,dia_retraso); // Comprobar que lo que hace es sumar los dias de retraso a la fecha anteriormente estimada.
    flushInputBuffer();
}

void consultar_estado(ProductoPedido *pedidos, int* tamanio, char *id_pedido_buscado){

    int coincidencias = 0;

    for(int i = 0 ; i < *tamanio && coincidencias == 0; i++ ){

        if(strcmp(pedidos[i].id_pedido,id_pedido_buscado) == 0){

            printf("%s\n",pedidos[i].estado_pedido);
            printf("\n");
            coincidencias++;

            }
        }
    if (coincidencias == 0) {
        printf("No se encontro el producto pedido con la id '%s'.\n", id_pedido_buscado);
    }
}

//DEVUELVE 0 si puede reducirlo y 1 si no
int reducirStock(Producto *productos, int tamProd,char*idProd, int ctdadReducir){
    int cambio = -1;
    for(int i=0;i<tamProd;i++){
        if(strcmp(productos[i].id_prod,idProd)==0){
            if(ctdadReducir<=productos[i].stock){
                productos[i].stock -= ctdadReducir;
                return 0;
            }else{
                printf("SOLO EXISTEN %d productos\n",productos[i].stock);
                return 1;
            }
        }
    }

    return cambio;
}

// DEVUELVE 1 si encuentra el ID ingresado
int encontrarID_prod(ProductoPedido *prodped, int tamanio_prodped, char *ID_producto){

    int encontrado = 0;

    for(int i = 0 ; i < tamanio_prodped && encontrado == 0; i++){

        if(strcmp(prodped[i].id_prod,ID_producto)==0){
            encontrado = 1;
        }
    }
    return encontrado;
}

// Guarda el vector de ProductoPedidos en el archivo siguiendo la estructura:
/*
    o Identificador del pedido (Id_pedido), 7 dígitos.
    o Identificador del producto (Id_prod), 7 dígitos.
    o Número de unidades (Num_unid)
    o Fecha prevista de entrega (día, mes y año).
    o Importe del producto en euros (Importe). Importante que quede constancia del importe al que
    compra un cliente un producto si la empresa modifica posteriormente su importe.
    o Estado del pedido: «enPreparación», «enviado», «enReparto», «enLocker», «entregado», «devuelto» o «transportista».
    o Identificador del transportista (Id_transp), 4 dígitos.
    o Identificador del locker (Id_locker), 10 caracteres máximo.
    o Código del locker (Cod_locker).
    o Fecha de entrega/devolución por el transportista
*/
void guardarProductoPedidoEnArchivo(ProductoPedido *productosPedidos, int numProductosPedidos)
{
    FILE *archivo = fopen(ProductoPedido_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo ProductosPedidos.txt.\n");
        return;
    }

    for (int i = 0; i < numProductosPedidos; i++)
    {
        // SI EL PRODUCTO ES DISTINTO DE "ENLOCKER", ESTABLECE CON ESPACIO LA INFORMACION DEL LOCKER
        if (strcmp(productosPedidos[i].id_locker, "") == 0)
            strcpy(productosPedidos[i].id_locker, " ");
        if (strcmp(productosPedidos[i].cod_locker, "") == 0)
            strcpy(productosPedidos[i].cod_locker, " ");
        if (strcmp(productosPedidos[i].id_transp, "") == 0)
            strcpy(productosPedidos[i].id_transp, " ");
        if (strcmp(productosPedidos[i].fecha_entrega_devolucion_transp, "") == 0)
            strcpy(productosPedidos[i].fecha_entrega_devolucion_transp, " ");

        fprintf(archivo, "%s-%s-%d-%s-%.2f-%s-%s-%s-%s-%s-\n",
                productosPedidos[i].id_pedido,
                productosPedidos[i].id_prod,
                productosPedidos[i].num_unid,
                productosPedidos[i].fecha_entrega_prevista,
                productosPedidos[i].importe,
                productosPedidos[i].estado_pedido,
                productosPedidos[i].id_transp,
                productosPedidos[i].id_locker,
                productosPedidos[i].cod_locker,
                productosPedidos[i].fecha_entrega_devolucion_transp);
    }

    fclose(archivo);
}

ProductoPedido *iniciarProductoPedidosDeArchivo(int *numProductos)
{
    FILE *archivo = fopen(ProductoPedido_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", ProductoPedido_txt);
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
    ProductoPedido *prodPed = (ProductoPedido *)malloc(count * sizeof(ProductoPedido));
    if (prodPed == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de ComportamientoLocker.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector
    for(int i=0;i<count;i++)
    {
        if(fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL){
        char *token = strtok(buffer, "-");
        strncpy(prodPed[i].id_pedido, token, sizeof(prodPed[i].id_pedido));
        token = strtok(NULL, "-");
        strncpy(prodPed[i].id_prod, token, sizeof(prodPed[i].id_prod));
        token = strtok(NULL, "-");
        prodPed[i].num_unid = atoi(token);
        token = strtok(NULL, "-");
        strncpy(prodPed[i].fecha_entrega_prevista, token, sizeof(prodPed[i].fecha_entrega_prevista));
        token = strtok(NULL, "-");
        prodPed[i].importe = atof(token);
        token = strtok(NULL, "-");
        strncpy(prodPed[i].estado_pedido, token, sizeof(prodPed[i].estado_pedido));
        token = strtok(NULL, "-");
        strncpy(prodPed[i].id_transp, token, sizeof(prodPed[i].id_transp));
        token = strtok(NULL, "-");
        strncpy(prodPed[i].id_locker, token, sizeof(prodPed[i].id_locker));
        token = strtok(NULL, "-");
        strncpy(prodPed[i].cod_locker, token, sizeof(prodPed[i].cod_locker));
        token = strtok(NULL, "-");
        strncpy(prodPed[i].fecha_entrega_devolucion_transp, token, sizeof(prodPed[i].fecha_entrega_devolucion_transp));

        }
    }

    fclose(archivo);
    *numProductos = count;
    return prodPed;
}

//Hace un pedido recibiendo previamente una lista de los productos que desea comprar el usuario, hay que buscar algo para que no de error
void hacerPedido(Producto **listaCompra, int *tamLista,Producto **productos, int *numnProductos,
                 Pedido **pedidos, int *numPedidos, ProductoPedido **prodPeds,int *numProdPe, char *idCliente,
                  char *tipoEntrega, char *idLocker)
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
        strcpy(prodPed.id_prod, (*listaCompra)[i].id_prod);

        do{
        printf("Cuantas unidades quieres de %s:", (*listaCompra)[i].nombre);
        scanf("%d", &prodPed.num_unid);
        flushInputBuffer();
        }while(prodPed.num_unid <= 0 || reducirStock(productos,&numPedidos,prodPed.id_prod,prodPed.num_unid)!=0); //

        prodPed.importe = prodPed.num_unid * (*listaCompra)[i].importe;
        coste += prodPed.importe;
        strcpy(prodPed.estado_pedido, "enPreparacion");
        strcpy(prodPed.id_locker, idLocker);

        *prodPeds = (ProductoPedido *)realloc(*prodPeds, (*numProdPe + 1) * sizeof(ProductoPedido));
        (*prodPeds)[*numProdPe] = prodPed;
        (*numProdPe)++;
    }

}

void listado_pedido_pendiente(ProductoPedido **pedidos, int* tamanio, char *idProd,Producto **productos, int * nProductos){

    for(int i = 0 ; i < *tamanio ; i++){
            if(strcmp((*pedidos)[i].estado_pedido,"enPreparacion")==0&&productoEsDeProveedor(productos,nProductos,idProd,(*pedidos)[i].id_prod)==1){
                printf("%s-%s-%d-%s-%.2f-%s\n",(*pedidos)[i].id_pedido,(*pedidos)[i].id_prod,(*pedidos)[i].num_unid,(*pedidos)[i].fecha_entrega_prevista,
               (*pedidos)[i].importe,(*pedidos)[i].estado_pedido);
            }
    }


}

void asignarLocker(Pedido **lista_pedidos, ProductoPedido **lista_productos_pedidos, int *num_pedidos, int *num_productos_pedidos) {
    char id_pedido[8], id_locker[11];

    printf("Ingrese el ID del pedido a asignarLocker: ");
    fgets(id_pedido, 8, stdin);
    id_pedido[strcspn(id_pedido, "\n")] = '\0';

    // Buscar el pedido
    int i;
    for (i = 0; i < *num_pedidos; i++) {
        if (strcmp((*lista_pedidos)[i].id_pedido, id_pedido) == 0) {

            // Buscar el producto pedido
            int j;
            printf("Ingrese el ID del locker al que desea asignar: ");
            fgets(id_locker, 11, stdin);
            id_locker[strcspn(id_locker, "\n")] = '\0';
            strcpy((*lista_pedidos)[i].id_locker, id_locker);
            for (j = 0; j < *num_productos_pedidos; j++) {
                if (strcmp((*lista_productos_pedidos)[j].id_pedido, id_pedido) == 0) {
                    strcpy((*lista_productos_pedidos)[j].id_locker, id_locker);
                }
            }
        }
    }
}
