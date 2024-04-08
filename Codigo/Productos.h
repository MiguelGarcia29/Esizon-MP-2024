#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "Categoria.c"


void alta_producto(Producto **productos, int* tamanio_vector, char* idAlta, Categoria *categ , int* tamanio_categ);
void baja_producto(Producto **productos , int* tamanio, char *id_baja);
void listado_producto(Producto *productos, int* tamanio);
void busqueda_producto_descr(Producto *productos, int* tamanio, char *descripcion);
void busqueda_producto_categ(Producto *productos, int* tamanio, char *categ, Categoria *categorias, int* tamanio_categ);
void buscador_un_producto(Producto *productos, int* tamanio , char *producto_buscado);
void modificar_producto(Producto *productos, int* tamanio, char *adminProv);
char *indicar_categ(Categoria *categ, int* tamanio, char *categoria_productos);
int productoEsDeProveedor(Producto *productos, int *tamanio, char *idProv, char *idProd);
void listado_producto_prooved(Producto *productos, int *tamanio, char *idProv);


#endif