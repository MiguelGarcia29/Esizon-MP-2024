#ifndef Gestion_Fichero
#define Gestion_Fichero

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

void guardarClientesEnArchivo(Cliente *clientes, int numClientes);
Cliente *iniciarClientesDeArchivo(int *numClientes);
void guardarAdminProvEnArchivo(AdminProv *admins, int numAdmins);
AdminProv *iniciarAdminProvDeArchivo(int *numAdmins);
void guardarProductosEnArchivo(Producto *productos, int numProductos);
Producto *iniciarProductosDeArchivo(int *numProductos);
void guardarCategoriasEnArchivo(Categoria *categorias, int numCategorias);
Categoria *iniciarCategoriasDeArchivo(int *numCat);
void guardarDescuentosEnArchivo(Descuento *descuentos, int numDescuentos);
Descuento *iniciarDescuentosDeArchivo(int *numDesc);
void guardarDescuentosClientesEnArchivo(DescuentoCliente *descuentosClientes, int numDescuentosClientes);
DescuentoCliente *iniciarDescuentosClientesDeArchivo(int *numDescC);
void guardarLockersEnArchivo(Locker *lockers, int numLockers);
Locker *iniciarLockersDeArchivo(int *numLock);
void guardarCompartimentoLockerEnArchivo(CompartimentoLocker *comportamientos, int numComportamientos);
CompartimentoLocker *iniciarCompartimientoLockersDeArchivo(int *numCompLock);
void guardarPedidoEnArchivo(Pedido *pedidos, int numPedidos);
Pedido *iniciarPedidosDeArchivo(int *numPedidos);
void guardarProductoPedidoEnArchivo(ProductoPedido *productosPedidos, int numProductosPedidos);
ProductoPedido *iniciarProductoPedidosDeArchivo(int *numProductos);
void guardarTransportistasEnArchivo(Transportista *transportistas, int numTransportistas);
Transportista *iniciarTransportistasDeArchivo(int *numTransportista);
void guardarDevolucionesEnArchivo(Devolucion *devoluciones, int numDevoluciones);
Devolucion *iniciarDevolucionDeArchivo(int *numDevolucion);



#include  "Gestion_Fichero.c"
#endif