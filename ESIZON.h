#ifndef ESIZON_H
#define ESIZON_H

#include "Cliente.h"
#include "Descuentos.h"
#include "DescuentoCliente.h"
#include "Lockers.h"
#include "CompartimentosLockers.h"
#include "Categoria.h"
#include "Productos.h"
#include "Pedidos.h"
#include "Productos_pedidos.h"
#include "Devolucion.h"
#include "Proveedor.h"
#include "Transportista.h"

//#include "Menu.c"

void accederPrograma();
int iniciarSesion();

int comprobarAdminoProv(char *,char *,char *);
int comprobarTransportista(char *,char *);
int comprobarUsuario(char *,char *);

#endif // CABECERA_H
