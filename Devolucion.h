#ifndef DEVOLUCION_H_INCLUDED
#define DEVOLUCION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilidades.h"
#include "Productos_pedidos.h"
#include "Cliente.h"

typedef struct {
    char id_pedido[8];
    char id_prod[8];
    char fecha_devolucion[11];
    char motivo[51];
    char estado[10]; // "pendiente", "aceptado", "denegado", "enviado", "recibido"
    char fecha_aceptacion[11];
    char fecha_caducidad[11];
}Devolucion;

void guardarDevolucionesEnArchivo(Devolucion *, int );
Devolucion *iniciarDevolucionDeArchivo(int *);
void alta_devolucion_admin(Devolucion **devoluciones, int *num_devoluciones, ProductoPedido **pedidos, int *tamanio_pedidos);
void listar_devoluciones(Devolucion **devoluciones, int *num_devoluciones);
void buscar_devolucion(Devolucion **devoluciones, int *num_devoluciones, char *id_devolucion);
void baja_devolucion(Devolucion **devoluciones, int *num_devoluciones, char *id_devolucion);
void modifYConsultarDevPedAdmin(Devolucion **lista_devoluciones, int *num_devoluciones);
void alta_devolucion_cliente(Devolucion **devoluciones, int *num_devoluciones, Cliente actual, ProductoPedido *pedidos, int tamanio_pedidos) ;
#endif // DEVOLUCION_H_INCLUDED
