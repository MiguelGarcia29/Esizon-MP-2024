#ifndef ESIZON_H
#define ESIZON_H

#include "estructuras.h"
#include "Gestion_Fichero.c"
#include "Categoria.h"
#include "Productos.c"
#include "Proveedor.c"
//#include "Menu.c"

void accederPrograma();
int iniciarSesion();

int comprobarAdminoProv(char *,char *,char *);
int comprobarTransportista(char *,char *);
int comprobarUsuario(char *,char *);

void inicializarDatos();
void almacenarDatos();

#endif // CABECERA_H
