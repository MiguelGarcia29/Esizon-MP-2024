#ifndef Gestion_Fichero_H
#define Gestion_Fichero_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estructuras.h"

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

void guardarClientesEnArchivo(Cliente *, int );
Cliente *iniciarClientesDeArchivo(int *);
void guardarAdminProvEnArchivo(AdminProv *, int );
AdminProv *iniciarAdminProvDeArchivo(int *);
void guardarProductosEnArchivo(Producto *, int );
Producto *iniciarProductosDeArchivo(int *);
void guardarCategoriasEnArchivo(Categoria *, int );
Categoria *iniciarCategoriasDeArchivo(int *);
void guardarDescuentosEnArchivo(Descuento *, int );
Descuento *iniciarDescuentosDeArchivo(int *);
void guardarDescuentosClientesEnArchivo(DescuentoCliente *, int );
DescuentoCliente *iniciarDescuentosClientesDeArchivo(int *);
void guardarLockersEnArchivo(Locker *, int );
Locker *iniciarLockersDeArchivo(int *);
void guardarCompartimentoLockerEnArchivo(CompartimentoLocker *, int );
CompartimentoLocker *iniciarCompartimientoLockersDeArchivo(int *);
void guardarPedidoEnArchivo(Pedido *, int );
Pedido *iniciarPedidosDeArchivo(int *);
void guardarProductoPedidoEnArchivo(ProductoPedido *, int );
ProductoPedido *iniciarProductoPedidosDeArchivo(int *);
void guardarTransportistasEnArchivo(Transportista *, int );
Transportista *iniciarTransportistasDeArchivo(int *);
void guardarDevolucionesEnArchivo(Devolucion *, int );
Devolucion *iniciarDevolucionDeArchivo(int *);



#endif