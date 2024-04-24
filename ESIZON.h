#ifndef ESIZON_H
#define ESIZON_H

#include "Cliente.h"
#include "Descuentos.h"
#include "DescuentoCliente.h"
#include "Lockers.h"
#include "CompartimentosLockers.h"
#include "Categoria.h"
#include "Productos.h"
#include "Pedidos.h"
#include "Productos_pedidos.h"
#include "Devolucion.h"
#include "Proveedor.h"
#include "Transportista.h"

//#include "Menu.c"

void accederPrograma(Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                      Categoria **categorias, int *numCategorias, CompartimentoLocker **compartimentoLockers, int *numCompartimentoLockers,
                      DescuentoCliente **descuentoClientes, int *numDescuentoClientes, Descuento **descuentos, int *numDescuentos,
                      Devolucion **devoluciones, int *numDevoluciones, Locker **lockers, int *numLockers, Pedido **pedidos, int *numPedido,
                      Producto **productos, int *numProductos, ProductoPedido **productoPedidos, int *numProductoPedidos,
                      Transportista **transportistas, int *numTransportistas);
int iniciarSesion();

void inicializarDatos(Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                      Categoria **categorias, int *numCategorias, CompartimentoLocker **compartimentoLockers, int *numCompartimentoLockers,
                      DescuentoCliente **descuentoClientes, int *numDescuentoClientes, Descuento **descuentos, int *numDescuentos,
                      Devolucion **devoluciones, int *numDevoluciones, Locker **lockers, int *numLockers, Pedido **pedidos, int *numPedido,
                      Producto **productos, int *numProductos, ProductoPedido **productoPedidos, int *numProductoPedidos,
                      Transportista **transportistas, int *numTransportistas);
                      void almacenarDatos(Cliente *clientes, int numClientes, AdminProv *adminProvs, int numAdminProvs, Categoria *categorias, int numCategorias, CompartimentoLocker *compartimentoLockers, int numCompartimentoLockers, DescuentoCliente *descuentoClientes, int numDescuentoClientes, Descuento *descuentos, int numDescuentos, Devolucion *devoluciones, int numDevoluciones, Locker *lockers, int numLockers, Pedido *pedidos, int numPedido, Producto *productos, int numProductos, ProductoPedido *productoPedidos, int numProductoPedidos, Transportista *transportistas, int numTransportistas);
int comprobarAdminoProv(char *email, char *contrasenia, char *rol, AdminProv *adminProvs, int numAdminProvs, int *posVectorClienteActual);
int comprobarTransportista(char *email, char *contrasenia, Transportista *transportistas, int numTransportistas, int *posVectorClienteActual);
int comprobarUsuario(char *email, char *contrasenia, Cliente * clientes, int numClientes, int *posVectorClienteActual);

#endif // CABECERA_H
