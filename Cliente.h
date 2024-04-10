
#ifndef PROVEEDOR_H_INCLUDED
#define PROVEEDOR_H_INCLUDED

//cliente
#include <stdio.h>
#include "Utilidades.h"

typedef struct{
    char id_cliente[8];
    char nomb_cliente[21];
    char dir_cliente[51];
    char localidad[21];
    char provincia[21];
    char email[31];
    char contrasenia[16];
    float cartera;
} Cliente;

void mostrar_cliente(Cliente cliente);

void cambiar_perfil_cliente(Cliente *cliente); //se presentara un menu para que el cliente pueda cambiar los datos que considere necesario

void guardarClientesEnArchivo(Cliente *clientes, int numClientes);
Cliente *iniciarClientesDeArchivo(int *numClientes);

#endif // DEVOLUCION_H_INCLUDED
