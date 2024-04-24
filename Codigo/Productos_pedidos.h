#ifndef Producto_Pedido_H
#define Producto_Pedido_H

#include "Cliente.h"
#include "Utilidades.h"

#include "Productos.h"
#include "Pedidos.h"
#include "Lockers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id_pedido[8];
    char id_prod[8];
    int num_unid;
    char fecha_entrega_prevista[11];
    float importe;
    char estado_pedido[15]; // "enPreparacion", "enviado", "enReparto", "enLocker", "entregado", "devuelto", "transportista"
    char id_transp[5];
    char id_locker[11];
    char cod_locker[11];
    char fecha_entrega_devolucion_transp[11];
}ProductoPedido;

void baja_prodPed(ProductoPedido **pedidos , int* tamanioProP, char *id_baja);
void listado_pedido(ProductoPedido **pedidos, int* tamanio);
void buscarPedido (ProductoPedido **pedidos, int** tamanio , char* id);
void consultar_estado(ProductoPedido *pedidos, int* tamanio, char *id_pedido_buscado);
char *seleccionar_producto(Producto *productos, int* tamanio, char *productos_select);
int reducirStock(Producto *productos, int tamProd,char*idProd, int ctdadReducir);
void guardarProductoPedidoEnArchivo(ProductoPedido *, int );
ProductoPedido *iniciarProductoPedidosDeArchivo(int *);
void hacerPedido(Producto **listaCompra, int *tamLista,Producto **productos, int *numnProductos,
                 Pedido **pedidos, int *numPedidos, ProductoPedido **prodPeds,int *numProdPe, char *idCliente,
                  char *tipoEntrega, char *idLocker);
void listado_pedido_pendiente(ProductoPedido **pedidos, int* tamanio, char *idProd,Producto **productos, int * nProductos);


#endif
