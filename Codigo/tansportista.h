#ifndef TRANSPORTISTA_H
#define TRANSPORTISTA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    char id_transp[5];
    char nombre[21];
    char email[31];
    char contrasenia[16];
    char nombre_empresa[21];
    char ciudad_reparto[21];
} Transportista;

typedef struct {
    char id_pedido[8];
    char id_prod[8];
    int num_unid;
    char fecha_entrega_prevista[11];
    float importe;
    char estado_pedido[15];
    char id_transp[5];
    char id_locker[11];
    char cod_locker[11];
    char fecha_entrega_devolucion_transp[11];
} ProductoPedido;

typedef struct {
    char id_locker[11];
    int num_comp;
    char cod_locker[11];
    char estado[7];
    char fecha_ocupacion[11];
    char fecha_caducidad[11];
} ComportamientoLocker;

void obtener_fecha_actual(char *fecha_actual);
char* id_generator(Transportista *t, int tamanio_vector);
void alta_transportista(Transportista **t, int* tamanio_vector);
void baja_transportista(Transportista *t , int* tamanio, char *id_baja);
void listado_transportista(Transportista *t, int tamanio);
void perfil(Transportista *t, int tamanio, char *id);
void reparto(ProductoPedido *pedidos, int num_pedidos, char *id_transp);
void fecha_caducidad(char *fecha);
void entrega(ProductoPedido *pedidos, ComportamientoLocker *comportamiento, int num_pedidos, int tamanio_compartimento, char *id_transp);

#endif /* TRANSPORTISTA_H */
