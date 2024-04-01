#ifndef Gestion_Lockers_H
#define Gestion_Lockers_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"

// Función para limpiar el buffer de entrada
void flushInputBuffer();

// Función para generar un ID único para un nuevo locker
char* id_generator(Locker *l, int tamanio_vector);

// Función para dar de alta un nuevo locker
void alta_locker(Locker **l, int* tamanio_vector);

// Función para verificar la disponibilidad de un locker
int ocupados_lockers(Locker *l, int tamanio, char *id);

// Función para dar de baja un locker existente
void baja_locker(Locker *l , int* tamanio, char *id_baja);

// Función para mostrar un listado de todos los lockers dados de alta
void listado_locker(Locker *l, int tamanio);

#endif
