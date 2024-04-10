#include "Productos_pedidos.h"
#include <time.h>
#include <string.h>
#include "Utilidades.c"


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


void baja_pedidos(ProductoPedido **pedidos , int* tamanio, char *id_baja){

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

void listado_Pedido(ProductoPedido *pedidos, int* tamanio){

    depurarBuffer();
    for(int i = 0 ; i < *tamanio ; i++){
        printf("%s-%s-%d-%s-%.2f-%s\n",pedidos[i].id_pedido,pedidos[i].id_prod,pedidos[i].num_unid,pedidos[i].fecha_entrega_prevista,pedidos[i].importe,pedidos[i].estado_pedido);
    }
}

//buscador de pedido segun su estado
void buscador_un_pedidos(ProductoPedido *pedidos, int* tamanio , char* estad_pedido){

    int coincidencia = 0;
    for(int i = 0 ; i < *tamanio ; i++ ){

        if(strcmp(pedidos[i].estado_pedido,estad_pedido) == 0){

            printf("%s-%s-%d-%s-%.2f-%s\n",pedidos[i].id_pedido,pedidos[i].id_prod,pedidos[i].num_unid,pedidos[i].fecha_entrega_prevista,pedidos[i].importe,pedidos[i].estado_pedido);
            printf("\n");
            coincidencia++;
            }
        }
        if(coincidencia == 0) {
        printf("No se encontraron pedidos (%s).\n", estad_pedido);
    }
}

void modificar_estado_pedido(ProductoPedido *pedidos, int* tamanio,char *id_modificar);
void modificar_transportistas(ProductoPedido *pedidos, int* tamanio,char *id_modificar);
void modificar_entrega(ProductoPedido *pedidos, int* tamanio,char *id_modificar);

// Permite modificar ciertas características del producto pedido.
void modificar_pedidos(ProductoPedido *pedidos, int* tamanio, Transportista *transportistas, int tamanio_transportistas){

    int a;
    char ID_producto[8];
    printf("Ingrese el ID de su producto\n"); 
    fgets(ID_producto,8,stdin);
    depurarBuffer();
    listado_Pedido(pedidos,tamanio);

    if(encontrarID_prod(pedidos, tamanio, ID_producto) != 1){
        printf("El ID ingresado no se ha encontrado.\n");
    }else{


        //SI NO ES ADMIN HAY Q COMPROBAR QUE LA ID DEL PRODUCTO SEA LA MISMA QUE LA ID DEL QUE ESTA HACIENDO LA MODIFICACION -> ES UNA FUNCION NUEVA PERO IGUAL QUE ESTA

        printf("----------\n");
        printf("(1) Modificar estado\n");
        printf("(2) Modificar transportista\n");
        printf("(3) Modificar entrega\n");
        fflush(stdin);
        scanf("%d", &a);
        printf("----------\n\n");

        switch (a) {
            case 1:
                modificar_estado_pedido(pedidos, tamanio, ID_producto);
                break;

            case 2:
                listado_transportista(transportistas,tamanio_transportistas);
                modificar_transportistas(pedidos, tamanio, ID_producto);
                break;

            case 3:
                modificar_entrega(pedidos, tamanio, ID_producto);
                break;

            default:
                break;
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
    depurarBuffer();
}

void modificar_transportistas(ProductoPedido *pedidos, int* tamanio,char *ID_producto){

    int i = 0;

    while(i < *tamanio && strcmp(pedidos[i].id_prod,ID_producto) != 0){
        i++;    // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    printf("Escribe el nuevo id del transportista: ");
	fflush(stdin);
	fgets(pedidos[i].id_transp,5,stdin);
    depurarBuffer();
}

void modificar_entrega(ProductoPedido *pedidos, int* tamanio,char *ID_producto){

    int i = 0;
    int dia_retraso;

    while(i < *tamanio && strcmp(pedidos[i].id_prod,ID_producto) != 0){
        i++;    // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    // COMPROBAR FUNC DE LA SUMA DE DIAS.
    printf("Escribe el retraso que puede tener el pedido: ");
	scanf("%d",&dia_retraso);
    fecha_entrega(pedidos[i].fecha_entrega_prevista,dia_retraso); // Comprobar que lo que hace es sumar los dias de retraso a la fecha anteriormente estimada.
    depurarBuffer();
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