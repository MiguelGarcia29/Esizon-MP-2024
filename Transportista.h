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


void perfil_t(Transportista t);
void guardarTransportistasEnArchivo(Transportista *, int );
Transportista *iniciarTransportistasDeArchivo(int *);

#endif // TRANSPORTISTA_H_INCLUDED
