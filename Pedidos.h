#ifndef PEDIDOS_H
#define PEDIDOS_H

#include "Utilidades.h"
#include "Productos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id_pedido[8];
    char fecha_pedido[11];
    char id_cliente[8];
    char lugar_entrega[10]; // "domicilio" o "locker"
    char id_locker[11];
    char id_cod[11];
}Pedido;


void guardarPedidoEnArchivo(Pedido *, int );
Pedido *iniciarPedidosDeArchivo(int *);
void baja_pedido(Pedido **pedidos, int *npedidos, char *id_pedido_baja);
void listado_pedido_cliente(Pedido **pedidos, int* tamanio, char *idC);
void buscar_pedido_cliente(Pedido **pedidos, int* tamanio, char *idC, char *idProducto);
#endif
