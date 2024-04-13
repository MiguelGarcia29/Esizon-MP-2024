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

void baja_pedidos(ProductoPedido **pedidos , int* tamanio, char *id_baja);
void listado_pedido(ProductoPedido *pedidos, int* tamanio);
void buscador_un_pedidos(ProductoPedido *pedidos, int* tamanio , char* estad_pedido);
//void modificar_pedidos(ProductoPedido *pedidos, int* tamanio, Transportista *transportistas, int tamanio_transportistas);
void consultar_estado(ProductoPedido *pedidos, int* tamanio, char *id_pedido_buscado);
char *seleccionar_producto(Producto *productos, int* tamanio, char *productos_select);
void mostrar_menu();
//void ejecutar_opcion(int opcion, Cliente *clientes, int *tamanio_clientes, Producto *productos, int *tamanio_productos, ProductoPedido *pedidos, int *tamanio_pedidos, Locker *lockers, int *tamanio_lockers, Transportista *transportista, int *tamanio_transportistas);
int reducirStock(Producto *productos, int tamProd,char*idProd, int ctdadReducir);
void guardarProductoPedidoEnArchivo(ProductoPedido *, int );
ProductoPedido *iniciarProductoPedidosDeArchivo(int *);
void hacerPedido(Producto *listaCompra, int tamLista,Producto *productos, int numnProductos, Pedido **pedidos, int *numPedidos, ProductoPedido **prodPeds,int *numProdPe, char *idCliente, char *tipoEntrega, char *idLocker, float *costeTotal);


#endif
