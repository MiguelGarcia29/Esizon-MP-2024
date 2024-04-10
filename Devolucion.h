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

#endif // DEVOLUCION_H_INCLUDED
