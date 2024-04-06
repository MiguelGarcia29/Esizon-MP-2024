#include "estructuras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alta_pedidos(ProductoPedido *pedidos, int* tamanio_vector, Cliente actual_cliente,int tamanio_cliente, Producto producto_seleccionado , int tamanio_produc, Locker lockers, int tamanio_lockers, Transportista transportista, int tamanio_transportistas);
void baja_pedidos(ProductoPedido *pedidos , int* tamanio, char *id_baja);
void listado_pedido(ProductoPedido *pedidos, int* tamanio);
void buscador_un_pedidos(ProductoPedido *pedidos, int* tamanio , char estado_pedido);
void modificar_pedidos(ProductoPedido *pedidos, int* tamanio);
void checkear_descuento(Descuento *descuentos, int* tamanio, char *descuento_buscado);
void check_estado(ProductoPedido *pedidos, int* tamanio , char *pedido_buscado);
