#include "Gestion_Fichero.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANIO_MAXIMO_LINEA 256
#define Clientes_txt "Datos/Clientes.txt"
#define AdminProv_txt "Datos/AdminProv.txt"
#define Productos_txt "Datos/Productos.txt"
#define Categorias_txt "Datos/Categorias.txt"
#define Descuento_txt "Datos/Descuentos.txt"
#define DescuentoCliente_txt "Datos/DescuentosClientes.txt"
#define Lockers_txt "Datos/Lockers.txt"
#define CompartimentoLocker_txt "Datos/CompartimentosLockers.txt"
#define Pedido_txt "Datos/Pedidos.txt"
#define ProductoPedido_txt "Datos/ProductosPedidos.txt"
#define Transportistas_txt "Datos/Transportistas.txt"
#define Devoluciones_txt "Datos/Devoluciones.txt"

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
    Cliente *clientes = (Cliente *)malloc(count * sizeof(Cliente));
    if (clientes == NULL)
    {
        fclose(archivo);
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
    AdminProv *adminProvs = (AdminProv *) malloc(count * sizeof(AdminProv));
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
        fprintf(archivo, "%s-%s-%s-%s-%s-%d-%d-%.2f\n",
                productos[i].id_prod,
                productos[i].nombre,
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
    Producto *productos = (Producto *)malloc(count * sizeof(Producto));
    if (productos == NULL)
    {
        fclose(archivo);
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
        strncpy(productos[i].nombre, token, sizeof(productos[i].nombre));
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
    Categoria *categorias = (Categoria *)malloc(count * sizeof(Categoria));
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
    Descuento *descuentos =(Descuento *) malloc(count * sizeof(Descuento));
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

DescuentoCliente *iniciarDescuentosClientesDeArchivo(int *numDescC)
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
    DescuentoCliente *descuentos =(DescuentoCliente *) malloc(count * sizeof(DescuentoCliente));
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

Locker *iniciarLockersDeArchivo(int *numLock)
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
    Locker *lockers = (Locker *)malloc(count * sizeof(Locker));
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
void guardarCompartimentoLockerEnArchivo(CompartimentoLocker *comportamientos, int numComportamientos)
{
    FILE *archivo = fopen(CompartimentoLocker_txt, "w");
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

CompartimentoLocker *iniciarCompartimientoLockersDeArchivo(int *numCompLock)
{
    FILE *archivo = fopen(CompartimentoLocker_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", CompartimentoLocker_txt);
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
    CompartimentoLocker *comportamientoL = (CompartimentoLocker *)malloc(count * sizeof(CompartimentoLocker));
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

// Guarda el vector de ComportamientoLocker en el archivo siguiendo la estructura:
/*
    o Identificador del pedido (Id_pedido), 7 dígitos.
    o Fecha del pedido (día, mes y año)
    o Identificador del cliente que realiza el pedido (Id_cliente), 7 dígitos.
    o Lugar de entrega (Lugar): «domicilio» o «locker»
    o Identificador de Locker (Id_locker), 10 caracteres máximo.
    o Identificador del código promocional o cheque regalo (Id_cod), 10 caracteres máximo.
*/
void guardarPedidoEnArchivo(Pedido *pedidos, int numPedidos)
{
    FILE *archivo = fopen(Pedido_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Pedidos.txt.\n");
        return;
    }

    for (int i = 0; i < numPedidos; i++)
    {

        // PARA QUE INTRODUZCA UN ESPACIO SI NO HAY LOCKER
        if (strcmp(pedidos[i].lugar_entrega, "locker") != 0)
        {
            strcpy(pedidos[i].id_locker, " ");
        }

        fprintf(archivo, "%s-%s-%s-%s-%s-%s-\n",
                pedidos[i].id_pedido,
                pedidos[i].fecha_pedido,
                pedidos[i].id_cliente,
                pedidos[i].lugar_entrega,
                pedidos[i].id_locker,
                pedidos[i].id_cod);
    }

    fclose(archivo);
    printf("Datos de pedidos guardados en el archivo Pedidos.txt.\n");
}

Pedido *iniciarPedidosDeArchivo(int *numPedidos)
{
    FILE *archivo = fopen(Pedido_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Pedido_txt);
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
    Pedido *pedidos = (Pedido *)malloc(count * sizeof(Pedido));
    if (pedidos == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de Pedido.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(pedidos[i].id_pedido, token, sizeof(pedidos[i].id_pedido));
        token = strtok(NULL, "-");
        strncpy(pedidos[i].fecha_pedido, token, sizeof(pedidos[i].fecha_pedido));
        token = strtok(NULL, "-");
        strncpy(pedidos[i].id_cliente, token, sizeof(pedidos[i].id_cliente));
        token = strtok(NULL, "-");
        strncpy(pedidos[i].lugar_entrega, token, sizeof(pedidos[i].lugar_entrega));
        token = strtok(NULL, "-");
        // SI NO ESTA EN LOCKER QUE DEJE ID LOCKER VACIA
        if (strcmp(pedidos[i].lugar_entrega, "locker") != 0)
            strncpy(pedidos[i].id_locker, "", sizeof(pedidos[i].id_locker));
        else
            strncpy(pedidos[i].id_locker, token, sizeof(pedidos[i].id_locker));
        token = strtok(NULL, "-");
        strncpy(pedidos[i].id_cod, token, sizeof(pedidos[i].id_cod));

        i++;
    }

    fclose(archivo);
    *numPedidos = count;
    return pedidos;
}

// Guarda el vector de ProductoPedidos en el archivo siguiendo la estructura:
/*
    o Identificador del pedido (Id_pedido), 7 dígitos.
    o Identificador del producto (Id_prod), 7 dígitos.
    o Número de unidades (Num_unid)
    o Fecha prevista de entrega (día, mes y año).
    o Importe del producto en euros (Importe). Importante que quede constancia del importe al que
    compra un cliente un producto si la empresa modifica posteriormente su importe.
    o Estado del pedido: «enPreparación», «enviado», «enReparto», «enLocker», «entregado», «devuelto» o «transportista».
    o Identificador del transportista (Id_transp), 4 dígitos.
    o Identificador del locker (Id_locker), 10 caracteres máximo.
    o Código del locker (Cod_locker).
    o Fecha de entrega/devolución por el transportista
*/
void guardarProductoPedidoEnArchivo(ProductoPedido *productosPedidos, int numProductosPedidos)
{
    FILE *archivo = fopen(ProductoPedido_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo ProductosPedidos.txt.\n");
        return;
    }

    for (int i = 0; i < numProductosPedidos; i++)
    {
        // SI EL PRODUCTO ES DISTINTO DE "ENLOCKER", ESTABLECE CON ESPACIO LA INFORMACION DEL LOCKER
        if (strcmp(productosPedidos[i].id_locker, "") == 0)
            strcpy(productosPedidos[i].id_locker, " ");
        if (strcmp(productosPedidos[i].cod_locker, "") == 0)
            strcpy(productosPedidos[i].cod_locker, " ");
        if (strcmp(productosPedidos[i].id_transp, "") == 0)
            strcpy(productosPedidos[i].id_transp, " ");
        if (strcmp(productosPedidos[i].fecha_entrega_devolucion_transp, "") == 0)
            strcpy(productosPedidos[i].fecha_entrega_devolucion_transp, " ");

        fprintf(archivo, "%s-%s-%d-%s-%.2f-%s-%s-%s-%s-%s-\n",
                productosPedidos[i].id_pedido,
                productosPedidos[i].id_prod,
                productosPedidos[i].num_unid,
                productosPedidos[i].fecha_entrega_prevista,
                productosPedidos[i].importe,
                productosPedidos[i].estado_pedido,
                productosPedidos[i].id_transp,
                productosPedidos[i].id_locker,
                productosPedidos[i].cod_locker,
                productosPedidos[i].fecha_entrega_devolucion_transp);
    }

    fclose(archivo);
    printf("Datos de productos pedidos guardados en el archivo ProductosPedidos.txt.\n");
}

ProductoPedido *iniciarProductoPedidosDeArchivo(int *numProductos)
{
    FILE *archivo = fopen(ProductoPedido_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", ProductoPedido_txt);
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
    ProductoPedido *prodPed = (ProductoPedido *)malloc(count * sizeof(ProductoPedido));
    if (prodPed == NULL)
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
        strncpy(prodPed[i].id_pedido, token, sizeof(prodPed[i].id_pedido));
        token = strtok(NULL, "-");
        strncpy(prodPed[i].id_prod, token, sizeof(prodPed[i].id_prod));
        token = strtok(NULL, "-");
        prodPed[i].num_unid = atoi(token);
        token = strtok(NULL, "-");
        strncpy(prodPed[i].fecha_entrega_prevista, token, sizeof(prodPed[i].fecha_entrega_prevista));
        token = strtok(NULL, "-");
        prodPed[i].importe = atof(token);
        token = strtok(NULL, "-");
        strncpy(prodPed[i].estado_pedido, token, sizeof(prodPed[i].estado_pedido));
        token = strtok(NULL, "-");
        strncpy(prodPed[i].id_transp, token, sizeof(prodPed[i].id_transp));
        token = strtok(NULL, "-");
        strncpy(prodPed[i].id_locker, token, sizeof(prodPed[i].id_locker));
        token = strtok(NULL, "-");
        strncpy(prodPed[i].cod_locker, token, sizeof(prodPed[i].cod_locker));
        token = strtok(NULL, "-");
        strncpy(prodPed[i].fecha_entrega_devolucion_transp, token, sizeof(prodPed[i].fecha_entrega_devolucion_transp));

        i++;
    }

    fclose(archivo);
    *numProductos = count;
    return prodPed;
}

// Guarda el vector de Transportitas en el archivo siguiendo la estructura:
/*
    o Identificador del transportista (Id_transp), 4 dígitos.
    o Nombre del transportista (Nombre), 20 caracteres máximo.
    o Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la
    plataforma.
    o Contraseña para acceder al sistema (Contraseña), con 15 caracteres máximo.
    o Nombre de la empresa (Nombre), 20 caracteres máximo.
    o Ciudad de reparto (Ciudad), 20 caracteres máximo.
*/
void guardarTransportistasEnArchivo(Transportista *transportistas, int numTransportistas)
{
    FILE *archivo = fopen(Transportistas_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Transportistas.txt.\n");
        return;
    }

    for (int i = 0; i < numTransportistas; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%s-%s-\n",
                transportistas[i].id_transp,
                transportistas[i].nombre,
                transportistas[i].email,
                transportistas[i].contrasenia,
                transportistas[i].nombre_empresa,
                transportistas[i].ciudad_reparto);
    }

    fclose(archivo);
    printf("Datos de transportistas guardados en el archivo Transportistas.txt.\n");
}

Transportista *iniciarTransportistasDeArchivo(int *numTransportista)
{
    FILE *archivo = fopen(Transportistas_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Transportistas_txt);
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
    Transportista *transportistas = (Transportista *)malloc(count * sizeof(Transportista));
    if (transportistas == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de Transportistas.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(transportistas[i].id_transp, token, sizeof(transportistas[i].id_transp));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].nombre, token, sizeof(transportistas[i].nombre));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].email, token, sizeof(transportistas[i].email));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].contrasenia, token, sizeof(transportistas[i].contrasenia));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].nombre_empresa, token, sizeof(transportistas[i].nombre_empresa));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].ciudad_reparto, token, sizeof(transportistas[i].ciudad_reparto));

        i++;
    }

    fclose(archivo);
    *numTransportista = count;
    return transportistas;
}

void guardarDevolucionesEnArchivo(Devolucion *devoluciones, int numDevoluciones)
{
    FILE *archivo = fopen(Devoluciones_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Devoluciones.txt.\n");
        return;
    }

    for (int i = 0; i < numDevoluciones; i++)
    {
        if (strcmp(devoluciones[i].fecha_aceptacion, "") == 0)
            strcpy(devoluciones[i].fecha_aceptacion, " ");
        if (strcmp(devoluciones[i].fecha_caducidad, "") == 0)
            strcpy(devoluciones[i].fecha_caducidad, " ");
        fprintf(archivo, "%s-%s-%s-%s-%s-%s-%s-\n",
                devoluciones[i].id_pedido,
                devoluciones[i].id_prod,
                devoluciones[i].fecha_devolucion,
                devoluciones[i].motivo,
                devoluciones[i].estado,
                devoluciones[i].fecha_aceptacion,
                devoluciones[i].fecha_caducidad);
    }

    fclose(archivo);
    printf("Datos de devoluciones guardados en el archivo Devoluciones.txt.\n");
}

Devolucion *iniciarDevolucionDeArchivo(int *numDevolucion)
{
    FILE *archivo = fopen(Devoluciones_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Devoluciones_txt);
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

    // Crear el vector de Devoluciones
    Devolucion *devoluciones =(Devolucion *) malloc(count * sizeof(Devolucion));
    if (devoluciones == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de Devoluciones.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(devoluciones[i].id_pedido, token, sizeof(devoluciones[i].id_pedido));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].id_prod, token, sizeof(devoluciones[i].id_prod));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].fecha_devolucion, token, sizeof(devoluciones[i].fecha_devolucion));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].motivo, token, sizeof(devoluciones[i].motivo));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].estado, token, sizeof(devoluciones[i].estado));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].fecha_aceptacion, token, sizeof(devoluciones[i].fecha_aceptacion));
        token = strtok(NULL, "-");
        strncpy(devoluciones[i].fecha_caducidad, token, sizeof(devoluciones[i].fecha_caducidad));

        i++;
    }

    fclose(archivo);
    *numDevolucion = count;
    return devoluciones;
}