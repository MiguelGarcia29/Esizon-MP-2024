#ifndef COMPARTIMENTOSLOCKERS_H_INCLUDED
#define COMPARTIMENTOSLOCKERS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Utilidades.h"

typedef struct {
    char id_locker[11];
    int num_comp;
    char cod_locker[11];
    char estado[8]; // "ocupado" o "vacio"
    char fecha_ocupacion[11];
    char fecha_caducidad[11];
}CompartimentoLocker;

void guardarCompartimentoLockerEnArchivo(CompartimentoLocker *, int );
CompartimentoLocker *iniciarCompartimientoLockersDeArchivo(int *);

#endif // COMPARTIMENTOSLOCKERS_H_INCLUDED
