//Descuentos

#include<stdio.h>
#include<string.h>
#include"estructuras.h"
#include<stdlib.h>
#include<time.h>




void alta_descuentos(Descuento **desc, int *cantdad_desc);

void baja_descuentos(Descuento **desc,int *cantdad_desc,char *id_baja);

void aplicar_descuento(Descuento *desc, Producto *prod);

void modificar_descuento(Descuento *desc);