//Descuentos
#ifndef Descuentos_H
#define Descuentos_H


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Utilidades.h"

typedef struct {
    char id_cod[11];
    char descrip[51];
    char tipo[9]; // "codpro" o "cheqreg"
    char estado[9]; // "activo" o "inactivo"
    float importe;
    char aplicable[7]; // "todos" (si es aplicable a todos)
}Descuento;

void alta_descuentos(Descuento **desc, int *cantdad_desc);

void baja_descuentos(Descuento **desc, int *cantdad_desc, char *id_baja);

void modificar_descuento(Descuento *desc, int cantdad_desc, char *id);
void guardarDescuentosEnArchivo(Descuento *descuentos, int numDescuentos);

Descuento *iniciarDescuentosDeArchivo(int *numDesc);

#endif
