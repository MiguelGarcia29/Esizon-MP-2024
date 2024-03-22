#include "estructuras.h"
#include "Gestion_Fichero.h"

Cliente *clientes;
int numClientes;

AdminProv *adminProvs;
int numAdminProvs;

Producto *productos;
int numProductos;

Categoria *categorias;
int numCategorias;

Descuento *descuentos;
int numDescuentos;

DescuentoCliente *descuentoClientes;
int numDescuentoClientes;

Locker *lockers;
int numLockers;

CompartimentoLocker *compartimentoLockers;
int numCompartimentoLockers;

Pedido *pedidos;
int numPedido;

ProductoPedido *productoPedidos;
int numProductoPedidos;

Transportista *transportistas;
int numTransportistas;

Devolucion *devoluciones;
int numDevoluciones;

// CARGA TODO LOS DATOS EN LOS VECTORES
void inicializarDatos(){
    clientes = iniciarClientesDeArchivo(&numClientes);
    adminProvs = iniciarAdminProvDeArchivo(&numAdminProvs);
    productos = iniciarProductosDeArchivo(&numProductos);
    categorias = iniciarCategoriasDeArchivo(&numCategorias);
    descuentos = iniciarDescuentosDeArchivo(&numDescuentos);
    descuentoClientes = iniciarDescuentosClientesDeArchivo(&numDescuentoClientes);
    lockers = iniciarLockersDeArchivo(&numLockers);
    compartimentoLockers = iniciarCompartimientoLockersDeArchivo(&numCompartimentoLockers);
    pedidos = iniciarPedidosDeArchivo(&numPedido);
    productoPedidos = iniciarProductoPedidosDeArchivo(&numProductoPedidos);
    transportistas = iniciarTransportistasDeArchivo(&numTransportistas);
    devoluciones= iniciarDevolucionDeArchivo(&numDevoluciones);
}

void almacenarDatos(){
    guardarClientesEnArchivo(clientes,numClientes);
    guardarAdminProvEnArchivo(adminProvs,numAdminProvs);
    guardarProductosEnArchivo(productos,numProductos);
    guardarCategoriasEnArchivo(categorias,numCategorias);
    guardarDescuentosEnArchivo(descuentos,numDescuentos);
    guardarDescuentosClientesEnArchivo(descuentoClientes,numDescuentoClientes);
    guardarLockersEnArchivo(lockers,numLockers);
    guardarCompartimentoLockerEnArchivo(compartimentoLockers,numCompartimentoLockers);
    guardarPedidoEnArchivo(pedidos,numPedido);
    guardarProductoPedidoEnArchivo(productoPedidos,numProductoPedidos);
    guardarTransportistasEnArchivo(transportistas,numTransportistas);
    guardarDevolucionesEnArchivo(devoluciones,numDevoluciones);
}

int main(){
    inicializarDatos();

    //ESTRUCTURA DEL PROGRAMA




    almacenarDatos();
}