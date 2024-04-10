#ifndef ESIZON_H
#define ESIZON_H

#include "estructuras.h"
#include "Gestion_Fichero.h"
#include "Categoria.h"
#include "Productos.h"
#include "Proveedor.h"
//#include "Menu.c"

void accederPrograma();
int iniciarSesion();

int comprobarAdminoProv(char *,char *,char *);
int comprobarTransportista(char *,char *);
int comprobarUsuario(char *,char *);

#endif // CABECERA_H
