#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANIO_MAXIMO_LINEA 256
#define Clientes_txt "Datos/Clientes.txt"
#define AdminProv_txt "Datos/AdminProv.txt"
#define Productos_txt "Datos/Productos.txt"
#define Categorias_txt "Datos/Categorias.txt"
#define Descuento_txt "Datos/Descuentos.txt"
#define DescuentoCliente_txt "Datos/DescuentosClientes.txt"
#define Lockers_txt "Datos/Lockers.txt"
#define CompartimentoLocker_txt "Datos/CompartimentosLockers.txt"
#define Pedido_txt "Datos/Pedidos.txt"
#define ProductoPedido_txt "Datos/ProductosPedidos.txt"
#define Transportistas_txt "Datos/Transportistas.txt"
#define Devoluciones_txt "Datos/Devoluciones.txt"

void flushInputBuffer();
void obtener_fecha_actual(char *fecha_actual);

#endif // UTILIDADES_H_INCLUDED
