//Descuentos

#include<stdio.h>
#include<string.h>
#include"estructuras.h"
#include<stdlib.h>


void listar_descuentos_admin(Descuento *desc,int cantdad_desc);

void alta_descuentos(Descuento **desc, int *cantdad_desc);

void baja_descuentos(Descuento **desc, int *cantdad_desc, char *id_baja);

void modificar_descuento(Descuento *desc, int cantdad_desc);