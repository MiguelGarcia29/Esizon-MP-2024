#include "estructuras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alta_pedidos(ProductoPedido **pedidos, int* tamanio_vector, Cliente actual_cliente,int* tamanio_cliente, Producto producto_seleccionado , int* tamanio_produc, Locker *lockers, int* tamanio_lockers, Transportista *transportista, int* tamanio_transportistas);
void baja_pedidos(ProductoPedido **pedidos , int* tamanio, char *id_baja);
void listado_pedido(ProductoPedido *pedidos, int* tamanio);
void buscador_un_pedidos(ProductoPedido *pedidos, int* tamanio , char* estad_pedido, int *coincidencia);
void modificar_pedidos(ProductoPedido *pedidos, int* tamanio, Transportista *transportistas, int tamanio_transportistas);
void consultar_estado(ProductoPedido *pedidos, int* tamanio, char *id_pedido_buscado);

void mostrar_menu();
void ejecutar_opcion(int opcion, Cliente *clientes, int *tamanio_clientes, Producto *productos, int *tamanio_productos, ProductoPedido *pedidos, int *tamanio_pedidos, Locker *lockers, int *tamanio_lockers, Transportista *transportista, int *tamanio_transportistas);

