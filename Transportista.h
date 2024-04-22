#ifndef TRANSPORTISTA_H_INCLUDED
#define TRANSPORTISTA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Utilidades.h"
#include "Productos_pedidos.h"
#include "CompartimentosLockers.h"

typedef struct {
    char id_transp[5];
    char nombre[21];
    char email[31];
    char contrasenia[16];
    char nombre_empresa[21];
    char ciudad_reparto[21];
}Transportista;


void perfil_t(Transportista *t);
void guardarTransportistasEnArchivo(Transportista *, int );
Transportista *iniciarTransportistasDeArchivo(int *);
void reparto(ProductoPedido **pedidos, int *num_pedidos, char *id_transp);
void asignarProductoPedidoProv(ProductoPedido **pedidos, int *num_pedidos, Transportista ** trans, int *nTrans,char *idProv, Producto **productos, int * nProductos);
int existeTransportista( Transportista ** trans, int *nTrans, char *idT);
void asignarProductoPedidoProv(ProductoPedido **pedidos, int *num_pedidos, Transportista ** trans, int *nTrans, char *idProv, Producto **productos, int * nProductos);
void dar_de_baja_transportista(Transportista **lista_transportistas, int *num_transportistas);
void modificar_transportista(Transportista **lista_transportistas, int *num_transportistas);
void buscar_transportista(Transportista **lista_transportistas, int *num_transportistas);
void listar_transportistas(Transportista **lista_transportistas, int *num_transportistas);
void agregar_transportista(Transportista **lista_transportistas, int *num_transportistas);

#endif // TRANSPORTISTA_H_INCLUDED
