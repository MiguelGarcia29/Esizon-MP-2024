#ifndef DESCUENTOCLIENTE_H_INCLUDED
#define DESCUENTOCLIENTE_H_INCLUDED

#include "Utilidades.h"

typedef struct {
    char id_cliente[8];
    char id_cod[11];
    char fecha_asignacion[11];
    char fecha_caducidad[11];
    int estado; // 1 (Aplicado) o 0 (No aplicado)
}DescuentoCliente;

void guardarDescuentosClientesEnArchivo(DescuentoCliente *, int );
DescuentoCliente *iniciarDescuentosClientesDeArchivo(int *);

#endif // DESCUENTOCLIENTE_H_INCLUDED
