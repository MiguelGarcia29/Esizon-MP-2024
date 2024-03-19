#include <stdio.h>
#include <stdlib.h>

#include "estructuras.h"

#define TAMANIO_MAXIMO_LINEA 256
#define Clientes_txt "Datos/Clientes.txt"
#define AdminProv_txt "Datos/AdminProv.txt"
#define Productos_txt "Datos/Productos.txt"
#define Categorias_txt "Datos/Categorias.txt"
#define Descuento_txt "Datos/Descuentos.txt"
#define DescuentoCliente_txt "Datos/DescuentosClientes.txt"
#define Lockers_txt "Datos/Lockers.txt"
#define ComportamientoLocker_txt "Datos/CompartimentosLockers.txt"

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

AdminProv *iniciarAdminProvDeArchivo(int *numAdmins)
{
    FILE *archivo = fopen(AdminProv_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", AdminProv_txt);
        return NULL;
    }

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de adminProv
    AdminProv *adminProvs = malloc(count * sizeof(AdminProv));
    if (adminProvs == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de AdminProv.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
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
void guardarProductosEnArchivo(Producto *productos, int numProductos)
{
    FILE *archivo = fopen(Productos_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Productos.txt.\n");
        return;
    }

    for (int i = 0; i < numProductos; i++)
    {
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
        productos[i].stock = atoi(token);
        token = strtok(NULL, "-");
        productos[i].entrega = atoi(token); // atoi convierte la cadena en int
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
void guardarCategoriasEnArchivo(Categoria *categorias, int numCategorias)
{
    FILE *archivo = fopen(Categorias_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Categorias.txt.\n");
        return;
    }

    for (int i = 0; i < numCategorias; i++)
    {
        fprintf(archivo, "%s-%s-\n", categorias[i].id_categ, categorias[i].descrip);
    }

    fclose(archivo);
}

Categoria *iniciarCategoriasDeArchivo(int *numCat)
{
    FILE *archivo = fopen(Categorias_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Categorias_txt);
        return NULL;
    }

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de categorias
    Categoria *categorias = malloc(count * sizeof(Categoria));
    if (categorias == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de categorias.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
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

// Guarda el vector de Descuentos en el archivo siguiendo la estructura:
/*
    o Identificador del código promocional o cheque regalo (Id_cod), 10 caracteres máximo.
    o Descripción del descuento (Descrip), 50 caracteres máximo.
    o Tipo de descuento (Tipo): «codpro» (código promocional) o «cheqreg» (cheque regalo)
    o Estado (Estado): «activo» o «inactivo»
    o Importe del descuento en euros (Importe)
    o Aplicabilidad (Aplicable): «todos» (si es aplicable a todos los productos) o «esizon» (si sólo es
    aplicable a los gestionados por ESIZON.
*/

void guardarDescuentosEnArchivo(Descuento *descuentos, int numDescuentos)
{
    FILE *archivo = fopen(Descuento_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Descuentos.txt.\n");
        return;
    }

    for (int i = 0; i < numDescuentos; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%.2f-%s-\n",
                descuentos[i].id_cod,
                descuentos[i].descrip,
                descuentos[i].tipo,
                descuentos[i].estado,
                descuentos[i].importe,
                descuentos[i].aplicable);
    }

    fclose(archivo);
}

Descuento *iniciarDescuentosDeArchivo(int *numDesc)
{
    FILE *archivo = fopen(Descuento_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Descuento_txt);
        return NULL;
    }

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de descuentos
    Descuento *descuentos = malloc(count * sizeof(Descuento));
    if (descuentos == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de descuentos.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(descuentos[i].id_cod, token, sizeof(descuentos[i].id_cod));
        token = strtok(NULL, "-");
        strncpy(descuentos[i].descrip, token, sizeof(descuentos[i].descrip));
        token = strtok(NULL, "-");
        strncpy(descuentos[i].tipo, token, sizeof(descuentos[i].tipo));
        token = strtok(NULL, "-");
        strncpy(descuentos[i].estado, token, sizeof(descuentos[i].estado));
        token = strtok(NULL, "-");
        descuentos[i].importe = atof(token);
        token = strtok(NULL, "-");
        strncpy(descuentos[i].aplicable, token, sizeof(descuentos[i].aplicable));
        i++;
    }

    fclose(archivo);
    *numDesc = count;
    return descuentos;
}

// Guarda el vector de DescuentosClientes en el archivo siguiendo la estructura:
/*
    o Identificador del cliente (Id_cliente), 7 dígitos.
    o Identificador del código promocional o cheque regalo (Id_cod), 10 caracteres máximo.
    o Fecha de asignación (día, mes y año)
    o Fecha de caducidad (día, mes y año)
    o Estado (Estado): 1 (Aplicado) ó 0 (No aplicado)
*/
void guardarDescuentosClientesEnArchivo(DescuentoCliente *descuentosClientes, int numDescuentosClientes)
{
    FILE *archivo = fopen(DescuentoCliente_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo DescuentosClientes.txt.\n");
        return;
    }

    for (int i = 0; i < numDescuentosClientes; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%d\n",
                descuentosClientes[i].id_cliente,
                descuentosClientes[i].id_cod,
                descuentosClientes[i].fecha_asignacion,
                descuentosClientes[i].fecha_caducidad,
                descuentosClientes[i].estado);
    }

    fclose(archivo);
}

Descuento *iniciarDescuentosClientesDeArchivo(int *numDescC)
{
    FILE *archivo = fopen(DescuentoCliente_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", DescuentoCliente_txt);
        return NULL;
    }

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de DescuentoCliente
    DescuentoCliente *descuentos = malloc(count * sizeof(DescuentoCliente));
    if (descuentos == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de DescuentoCliente.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(descuentos[i].id_cliente, token, sizeof(descuentos[i].id_cliente));
        token = strtok(NULL, "-");
        strncpy(descuentos[i].id_cod, token, sizeof(descuentos[i].id_cod));
        token = strtok(NULL, "-");
        strncpy(descuentos[i].fecha_asignacion, token, sizeof(descuentos[i].fecha_asignacion));
        token = strtok(NULL, "-");
        strncpy(descuentos[i].fecha_caducidad, token, sizeof(descuentos[i].fecha_caducidad));
        token = strtok(NULL, "-");
        descuentos[i].estado = atoi(token);
        i++;
    }

    fclose(archivo);
    *numDescC = count;
    return descuentos;
}

// Guarda el vector de DescuentosClientes en el archivo siguiendo la estructura:
/*
    o Identificador del Locker (Id_locker), 10 caracteres máximo.
    o Población (Localidad), 20 caracteres máximo.
    o Provincia (Provincia), 20 caracteres máximo.
    o Ubicación (Ubica), 20 caracteres máximo.
    o Número de compartimentos total (Num_compT).
    o Número de compartimentos ocupados actualmente (Num_compOcup).
*/
void guardarLockersEnArchivo(Locker *lockers, int numLockers)
{
    FILE *archivo = fopen(Lockers_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Lockers.txt.\n");
        return;
    }

    for (int i = 0; i < numLockers; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%d-%d\n",
                lockers[i].id_locker,
                lockers[i].localidad,
                lockers[i].provincia,
                lockers[i].ubicacion,
                lockers[i].num_compt,
                lockers[i].num_compocup);
    }

    fclose(archivo);
}

Locker * iniciarLockersDeArchivo(int *numLock)
{
    FILE *archivo = fopen(Lockers_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Lockers_txt);
        return NULL;
    }

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de Locker
    Locker *lockers = malloc(count * sizeof(Locker));
    if (lockers == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de Locker.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(lockers[i].id_locker, token, sizeof(lockers[i].id_locker));
        token = strtok(NULL, "-");
        strncpy(lockers[i].localidad, token, sizeof(lockers[i].localidad));
        token = strtok(NULL, "-");
        strncpy(lockers[i].provincia, token, sizeof(lockers[i].provincia));
        token = strtok(NULL, "-");
        strncpy(lockers[i].ubicacion, token, sizeof(lockers[i].ubicacion));
        token = strtok(NULL, "-");
        lockers[i].num_compt = atoi(token);
        token = strtok(NULL, "-");
        lockers[i].num_compocup = atoi(token);
        i++;
    }

    fclose(archivo);
    *numLock = count;
    return lockers;
}

// Guarda el vector de ComportamientoLocker en el archivo siguiendo la estructura:
/*
    o Identificador del locker (Id_locker), 10 caracteres máximo.
    o Número de compartimento (Num_comp).
    o Código del locker (Cod_locker).
    o Estado: «ocupado» o «vacío»
    o Fecha ocupación (día, mes y año).
    o Fecha caducidad (día, mes y año).
*/
void guardarComportamientoLockerEnArchivo(ComportamientoLocker *comportamientos, int numComportamientos)
{
    FILE *archivo = fopen(ComportamientoLocker_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo CompartimentosLockers.txt.\n");
        return;
    }

    for (int i = 0; i < numComportamientos; i++)
    {
        fprintf(archivo, "%s-%d-%s-%s-%s-%s-\n",
                comportamientos[i].id_locker,
                comportamientos[i].num_comp,
                comportamientos[i].cod_locker,
                comportamientos[i].estado,
                comportamientos[i].fecha_ocupacion,
                comportamientos[i].fecha_caducidad);
    }

    fclose(archivo);
}

ComportamientoLocker * iniciarComportamientoLockersDeArchivo(int *numCompLock)
{
    FILE *archivo = fopen(ComportamientoLocker_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", ComportamientoLocker_txt);
        return NULL;
    }

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de Locker
    ComportamientoLocker *comportamientoL = malloc(count * sizeof(ComportamientoLocker));
    if (comportamientoL == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de ComportamientoLocker.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(comportamientoL[i].id_locker, token, sizeof(comportamientoL[i].id_locker));
        token = strtok(NULL, "-");
        comportamientoL[i].num_comp = atoi(token);
        token = strtok(NULL, "-");
        strncpy(comportamientoL[i].cod_locker, token, sizeof(comportamientoL[i].cod_locker));
        token = strtok(NULL, "-");
        strncpy(comportamientoL[i].estado, token, sizeof(comportamientoL[i].estado));
        token = strtok(NULL, "-");
        strncpy(comportamientoL[i].fecha_ocupacion, token, sizeof(comportamientoL[i].fecha_ocupacion));
        token = strtok(NULL, "-");
        strncpy(comportamientoL[i].fecha_caducidad, token, sizeof(comportamientoL[i].fecha_caducidad));
        
        i++;
    }

    fclose(archivo);
    *numCompLock = count;
    return comportamientoL;
}


int main() {
    int numComportamientos;
    ComportamientoLocker *comportamientos = iniciarComportamientoLockersDeArchivo(&numComportamientos);
    if (comportamientos == NULL) {
        printf("No se pudieron cargar los datos de comportamientos de lockers del archivo.\n");
        return 1;
    }

    printf("Comportamientos de lockers cargados del archivo:\n");
    for (int i = 0; i < numComportamientos; i++) {
        printf("ID Locker: %s\n", comportamientos[i].id_locker);
        printf("Número de compartimento: %d\n", comportamientos[i].num_comp);
        printf("Código del locker: %s\n", comportamientos[i].cod_locker);
        printf("Estado: %s\n", comportamientos[i].estado);
        printf("Fecha de ocupación: %s\n", comportamientos[i].fecha_ocupacion);
        printf("Fecha de caducidad: %s\n", comportamientos[i].fecha_caducidad);
        printf("\n");
    }

    free(comportamientos); // Liberar la memoria asignada para el vector de comportamientos de lockers

    return 0;
}
