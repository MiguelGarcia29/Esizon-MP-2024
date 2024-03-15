#include <stdio.h>
#include <stdlib.h>

#include "estructuras.h"

#define TAMANIO_MAXIMO_LINEA 256
#define Clientes_txt "Datos/Clientes.txt"
#define AdminProv_txt "Datos/AdminProv.txt"
#define Productos_txt "Datos/Productos.txt"

// Guarda el vector de clientes en el archivo siguiendo la estructura:
/*  o Identificador del cliente (Id_cliente), 7 dígitos.
    o Nombre completo del cliente (Nomb_cliente), 20 caracteres máximo.
    o Dirección del cliente (Dir_cliente), 50 caracteres máximo.
    o Población (Localidad), 20 caracteres máximo.
    o Provincia (Provincia), 20 caracteres máximo.
    o Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la
    plataforma.
    o Contrasenia para acceder al sistema (Contrasenia), con 15 caracteres máximo.
    o Cartera (Cartera), almacenará el dinero del que dispone el cliente para poder adquirir los
    productos.
    */

void guardarClientesEnArchivo(Cliente *clientes, int numClientes)
{
    FILE *archivo = fopen(Clientes_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Clientes_txt);
        return;
    }

    for (int i = 0; i < numClientes; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%s-%s-%s-%.2f\n",
                clientes[i].id_cliente,
                clientes[i].nomb_cliente,
                clientes[i].dir_cliente,
                clientes[i].localidad,
                clientes[i].provincia,
                clientes[i].email,
                clientes[i].contrasenia,
                clientes[i].cartera);
    }

    fclose(archivo);
}

// LE PASO COMO PUNTERO EL NUM DE CLIENTES PARA LUEGO PODER ALMACENARLO EN EL PROGRAMA (MAIN)
Cliente *iniciarClientesDeArchivo(int *numClientes)
{
    FILE *archivo = fopen(Clientes_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Clientes_txt);
        return NULL;
    }

    // Contar la cantidad de lineas = clientes en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA];
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear vector cliente
    Cliente *clientes = malloc(count * sizeof(Cliente));
    if (clientes == NULL)
    {
        fclose(Clientes_txt);
        printf("No se pudo asignar memoria para el vector de clientes.\n");
        return NULL;
    }

    // Leer cada linea del archivo y rellenar el vector de clientes
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        // Strtok sirve para dividir la cadena en subcadenas por "-"
        // - OS ADJUNTO DOCUMENTACION CONSULTADA: https://www.ibm.com/docs/es/i/7.5?topic=functions-strtok-tokenize-string
        // - VIDEO QUE LO EXPLICA CON SUMA: https://www.youtube.com/watch?v=jHdbmHCVQ2c
        char *token = strtok(buffer, "-");
        strncpy(clientes[i].id_cliente, token, sizeof(clientes[i].id_cliente));
        token = strtok(NULL, "-");
        strncpy(clientes[i].nomb_cliente, token, sizeof(clientes[i].nomb_cliente));
        token = strtok(NULL, "-");
        strncpy(clientes[i].dir_cliente, token, sizeof(clientes[i].dir_cliente));
        token = strtok(NULL, "-");
        strncpy(clientes[i].localidad, token, sizeof(clientes[i].localidad));
        token = strtok(NULL, "-");
        strncpy(clientes[i].provincia, token, sizeof(clientes[i].provincia));
        token = strtok(NULL, "-");
        strncpy(clientes[i].email, token, sizeof(clientes[i].email));
        token = strtok(NULL, "-");
        strncpy(clientes[i].contrasenia, token, sizeof(clientes[i].contrasenia));
        token = strtok(NULL, "-");
        clientes[i].cartera = atof(token); // atof convierte la cadena en Float.
        i++;
    }

    fclose(archivo);
    *numClientes = count;
    return clientes;
}

// Guarda el vector de AdminYProvs en el archivo siguiendo la estructura:
/*
    o Identificador de la empresa administradora o proveedora (Id_empresa), 4 dígitos.
    o Nombre de la empresa (Nombre), sería ESIZON si es administrador, 20 caracteres máximo.
    o Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la
    plataforma.
    o Contrasenia para acceder al sistema (Contrasenia), con 15 caracteres máximo.
    o Perfil del usuario (Perfil_usuario): «administrador» o «proveedor».
*/
void guardarAdminProvEnArchivo(AdminProv *admins, int numAdmins)
{
    FILE *archivo = fopen(AdminProv_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", AdminProv_txt);
        return;
    }

    for (int i = 0; i < numAdmins; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%s-\n",
                admins[i].id_empresa,
                admins[i].nombre,
                admins[i].email,
                admins[i].contrasenia,
                admins[i].perfil_usuario);
    }

    fclose(archivo);
}

AdminProv* iniciarAdminProvDeArchivo(int *numAdmins) {
    FILE *archivo = fopen(AdminProv_txt, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s.\n", AdminProv_txt);
        return NULL;
    }

    // Contar la cantidad de líneas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud máxima de línea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL) {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de adminProv
    AdminProv *adminProvs = malloc(count * sizeof(AdminProv));
    if (adminProvs == NULL) {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de AdminProv.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL) {
        char *token = strtok(buffer, "-");
        strncpy(adminProvs[i].id_empresa, token, sizeof(adminProvs[i].id_empresa));
        token = strtok(NULL, "-");
        strncpy(adminProvs[i].nombre, token, sizeof(adminProvs[i].nombre));
        token = strtok(NULL, "-");
        strncpy(adminProvs[i].email, token, sizeof(adminProvs[i].email));
        token = strtok(NULL, "-");
        strncpy(adminProvs[i].contrasenia, token, sizeof(adminProvs[i].contrasenia));
        token = strtok(NULL, "-");
        strncpy(adminProvs[i].perfil_usuario, token, sizeof(adminProvs[i].perfil_usuario));
        i++;
    }

    fclose(archivo);
    *numAdmins = count;
    return adminProvs;
}

// Guarda el vector de Produtcos en el archivo siguiendo la estructura:
/*
    o Identificador del producto (Id_prod), 7 dígitos.
    o Descripción del producto (Descrip), 50 caracteres máximo.
    o Id de la categoría a la que pertenece (Id_categ), 4 dígitos.
    o Id del gestor del producto (Id_gestor), 4 digítos. Deberá coincidir con el identificador de la
    empresa administradora o proveedora del producto.
    o Stock del producto (Stock).
    o Compromiso de Entrega (Entrega). Indicará el número de días máximo que transcurrirá desde
    la fecha de realización del pedido hasta la entrega al cliente.
    o Importe del producto en euros (Importe).
*/
void guardarProductosEnArchivo(Producto *productos, int numProductos) {
    FILE *archivo = fopen(Productos_txt, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo Productos.txt.\n");
        return;
    }

    for (int i = 0; i < numProductos; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%d-%d-%.2f\n",
                productos[i].id_prod,
                productos[i].descrip,
                productos[i].id_categ,
                productos[i].id_gestor,
                productos[i].stock,
                productos[i].entrega,
                productos[i].importe);
    }

    fclose(archivo);
}

int main() {
    Producto productos[2] = {
        {"0000001", "televisor 32” 3D", "0001", "0001", 50, 5, 340.0},
        {"0000002", "Auriculares inalámbricos", "0002", "0001", 125, 1, 45.0}
    };

    guardarProductosEnArchivo(productos, 2);

    return 0;
}