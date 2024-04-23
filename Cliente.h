
#ifndef PROVEEDOR_H_INCLUDED
#define PROVEEDOR_H_INCLUDED

//cliente
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void cambiar_contrasenia_cliente(char nueva[16]); // funcion que cambia la contrasenia
void cambiar_email_cliente(char nuevo[31]); //funcion que cambia el email
void cambiar_direccion_cliente(char direccion[51], char provincia[21], char localidad[21]); //funcion que cambia direccion, provincia y localidad
void cartera(float *saldo);
void anadir_saldo(float *saldo);
void extraer_saldo(float *saldo);
int corroborar_contrasenia(char cad[16]);

void altaCliente(Cliente **clientes, int *numClientes);
void bajaCliente(Cliente **clientes, int *numClientes);
void buscarCliente(Cliente **clientes, int *numClientes);
void listarClientes(Cliente **clientes, int *numClientes);
void modificarCliente(Cliente **clientes, int *numClientes);


#endif // DEVOLUCION_H_INCLUDED
