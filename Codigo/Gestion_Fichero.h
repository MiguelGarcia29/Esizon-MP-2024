#ifndef Gestion_Fichero_H
#define Gestion_Fichero_H

#include "estructuras.h"

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