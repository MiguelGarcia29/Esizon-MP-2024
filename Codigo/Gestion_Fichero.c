#include <stdio.h>
#include <stdlib.h>

#include "estructuras.h"

#define TAMANIO_MAXIMO_LINEA 256
#define Clientes_txt "Datos/Clientes.txt"
#define AdminProv_txt "Datos/AdminProv.txt"
#define Productos_txt "Datos/Productos.txt"
#define Categorias_txt "Datos/Categorias.txt"

// Guarda el vector de clientes en el archivo siguiendo la estructura:
/*  o Identificador del cliente (Id_cliente), 7 digitos.
    o Nombre completo del cliente (Nomb_cliente), 20 caracteres maximo.
    o Dirección del cliente (Dir_cliente), 50 caracteres maximo.
    o Población (Localidad), 20 caracteres maximo.
    o Provincia (Provincia), 20 caracteres maximo.
    o Email (email), 30 caracteres maximo, sera usado como nombre de usuario para el acceso a la
    plataforma.
    o Contrasenia para acceder al sistema (Contrasenia), con 15 caracteres maximo.
    o Cartera (Cartera), almacenara el dinero del que dispone el cliente para poder adquirir los
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

// LE PASO COMO PUNTERO EL NUM DE CLIENTES PARA LUEGO PODER ALMACENARLO EN EL PROGRAMA (MAIN) -> MISMA LOGICA PARA LAS DEMAS LECTURAS
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
    o Identificador de la empresa administradora o proveedora (Id_empresa), 4 digitos.
    o Nombre de la empresa (Nombre), seria ESIZON si es administrador, 20 caracteres maximo.
    o Email (email), 30 caracteres maximo, sera usado como nombre de usuario para el acceso a la
    plataforma.
    o Contrasenia para acceder al sistema (Contrasenia), con 15 caracteres maximo.
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

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
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
    o Identificador del producto (Id_prod), 7 digitos.
    o Descripción del producto (Descrip), 50 caracteres maximo.
    o Id de la categoria a la que pertenece (Id_categ), 4 digitos.
    o Id del gestor del producto (Id_gestor), 4 digitos. Debera coincidir con el identificador de la
    empresa administradora o proveedora del producto.
    o Stock del producto (Stock).
    o Compromiso de Entrega (Entrega). Indicara el número de dias maximo que transcurrira desde
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

Producto *iniciarProductosDeArchivo(int *numProductos)
{
    FILE *archivo = fopen(Productos_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Productos_txt);
        return NULL;
    }

    // Contar la cantidad de lineas = productos en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA];
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear vector cliente
    Producto *productos = malloc(count * sizeof(Producto));
    if (productos == NULL)
    {
        fclose(Productos_txt);
        printf("No se pudo asignar memoria para el vector de productos.\n");
        return NULL;
    }

    // Leer cada linea del archivo y rellenar el vector de productos
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(productos[i].id_prod, token, sizeof(productos[i].id_prod));
        token = strtok(NULL, "-");
        strncpy(productos[i].descrip, token, sizeof(productos[i].descrip));
        token = strtok(NULL, "-");
        strncpy(productos[i].id_categ, token, sizeof(productos[i].id_categ));
        token = strtok(NULL, "-");
        strncpy(productos[i].id_gestor, token, sizeof(productos[i].id_gestor));
        token = strtok(NULL, "-");
        productos[i].stock=atoi(token);
        token = strtok(NULL, "-");
        productos[i].entrega=atoi(token); // atoi convierte la cadena en int
        token = strtok(NULL, "-");
        productos[i].importe = atof(token); // atof convierte la cadena en Float.
        i++;
    }

    fclose(archivo);
    *numProductos = count;
    return productos;
}

// Guarda el vector de Categoria en el archivo siguiendo la estructura:
/*
    o Identificador de la categoria (Id_categ), 4 digitos.
    o Descripción de la categoria (Descrip), 50 caracteres maximo.
*/
void guardarCategoriasEnArchivo(Categoria *categorias, int numCategorias) {
    FILE *archivo = fopen(Categorias_txt, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo Categorias.txt.\n");
        return;
    }

    for (int i = 0; i < numCategorias; i++) {
        fprintf(archivo, "%s-%s-\n", categorias[i].id_categ, categorias[i].descrip);
    }

    fclose(archivo);
    printf("Datos de categorias guardados en el archivo Categorias.txt.\n");
}

Categoria* iniciarCategoriasDeArchivo(int *numCat) {
    FILE *archivo = fopen(Categorias_txt, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s.\n", Categorias_txt);
        return NULL;
    }

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL) {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de adminProv
    Categoria *categorias = malloc(count * sizeof(Categoria));
    if (categorias == NULL) {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de AdminProv.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL) {
        char *token = strtok(buffer, "-");
        strncpy(categorias[i].id_categ, token, sizeof(categorias[i].id_categ));
        token = strtok(NULL, "-");
        strncpy(categorias[i].descrip, token, sizeof(categorias[i].descrip));
        i++;
    }

    fclose(archivo);
    *numCat = count;
    return categorias;
}


int main() {
    int numCategorias;
    Categoria *categorias = iniciarCategoriasDeArchivo(&numCategorias);
    if (categorias == NULL) {
        printf("No se pudieron leer los datos de categorías del archivo.\n");
        return 1;
    }

    printf("Categorías leídas del archivo:\n");
    for (int i = 0; i < numCategorias; i++) {
        printf("ID Categoría: %s\n", categorias[i].id_categ);
        printf("Descripción: %s\n", categorias[i].descrip);
        printf("\n");
    }

    free(categorias); // Liberar la memoria asignada para el vector de categorías

    return 0;
}