#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"

//En las altas y bajas habra que añadir id cliente dependiendo sea proveedor o admin o cliente.
void alta_categoria(Categoria *categoria, int* tamanio_vector);
void baja_categoria(Categoria *categoria , int* tamanio, char *id_baja);
int indicar_categ(Categoria *categ, int* tamanio,char *categoria_productos);