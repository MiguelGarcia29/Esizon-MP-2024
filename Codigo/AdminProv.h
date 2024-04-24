#ifndef ADMINPROV_H_INCLUDED
#define ADMINPROV_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilidades.h"

typedef struct{
    char id_empresa[5];
    char nombre[21];
    char email[31];
    char contrasenia[16];
    char perfil_usuario[14]; // "administrador" o "proveedor"
} AdminProv;

void guardarAdminProvEnArchivo(AdminProv *admins, int numAdmins);
AdminProv *iniciarAdminProvDeArchivo(int *numAdmins);

#endif // ADMINPROV_H_INCLUDED
