#ifndef CATEGORIA_H
#define CATEGORIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estructuras.h"
#include "limpiarBuffer.c"


//En las altas y bajas habra que añadir id cliente dependiendo sea proveedor o admin o cliente.
char* id_generator_categ(Categoria *categorias, int tamanio_vector);
void alta_categoria(Categoria *categoria, int* tamanio_vector);
void baja_categoria(Categoria *categoria , int* tamanio, char *id_baja);
int check_categ(Categoria *categ, int* tamanio,char *categoria_productos);
char *indicar_categ(Categoria *categ, int* tamanio, char *categoria_productos);
void modificar_categoria(Categoria *categorias, int* tamanio);
void modificar_descripcion_categ(Categoria *categorias, int* tamanio,char *id_modificar);

#endif