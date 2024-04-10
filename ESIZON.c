#include "ESIZON.h"

Cliente *clientes;
int numClientes;

AdminProv *adminProvs;
int numAdminProvs;

Categoria *categorias;
int numCategorias;

CompartimentoLocker *compartimentoLockers;
int numCompartimentoLockers;

DescuentoCliente *descuentoClientes;
int numDescuentoClientes;

Descuento *descuentos;
int numDescuentos;

Devolucion *devoluciones;
int numDevoluciones;

Locker *lockers;
int numLockers;

Pedido *pedidos;
int numPedido;

Producto *productos;
int numProductos;

ProductoPedido *productoPedidos;
int numProductoPedidos;

Transportista *transportistas;
int numTransportistas;

int rol;
int posVectorClienteActual;
// 1-Administrador
// 2-Usuario
// 3-Proveedor
// 4-Transportista


void inicializarDatos();
void almacenarDatos();

// CARGA TODO LOS DATOS EN LOS VECTORES
void inicializarDatos()
{
    clientes = iniciarClientesDeArchivo(&numClientes);
    adminProvs = iniciarAdminProvDeArchivo(&numAdminProvs);
    productos = iniciarProductosDeArchivo(&numProductos);
    categorias = iniciarCategoriasDeArchivo(&numCategorias);
    descuentos = iniciarDescuentosDeArchivo(&numDescuentos);
    descuentoClientes = iniciarDescuentosClientesDeArchivo(&numDescuentoClientes);
    lockers = iniciarLockersDeArchivo(&numLockers);
    compartimentoLockers = iniciarCompartimientoLockersDeArchivo(&numCompartimentoLockers);
    pedidos = iniciarPedidosDeArchivo(&numPedido);
    productoPedidos = iniciarProductoPedidosDeArchivo(&numProductoPedidos);
    transportistas = iniciarTransportistasDeArchivo(&numTransportistas);
    devoluciones = iniciarDevolucionDeArchivo(&numDevoluciones);
}

void almacenarDatos()
{
    guardarClientesEnArchivo(clientes, numClientes);
    guardarAdminProvEnArchivo(adminProvs, numAdminProvs);
    guardarProductosEnArchivo(productos, numProductos);
    guardarCategoriasEnArchivo(categorias, numCategorias);
    guardarDescuentosEnArchivo(descuentos, numDescuentos);
    guardarDescuentosClientesEnArchivo(descuentoClientes, numDescuentoClientes);
    guardarLockersEnArchivo(lockers, numLockers);
    guardarCompartimentoLockerEnArchivo(compartimentoLockers, numCompartimentoLockers);
    guardarPedidoEnArchivo(pedidos, numPedido);
    guardarProductoPedidoEnArchivo(productoPedidos, numProductoPedidos);
    guardarTransportistasEnArchivo(transportistas, numTransportistas);
    guardarDevolucionesEnArchivo(devoluciones, numDevoluciones);
}

int main()
{
    inicializarDatos();

    // ESTRUCTURA DEL PROGRAMA
    accederPrograma();
    // listado_producto(productos,&numProductos);

    almacenarDatos();
}

void accederPrograma()
{
    printf(" ########  #######   ######     ##########  ##########  ###      ##\n");
    printf(" ##       ##           ##              #    ##      ##  ## #     ##\n");
    printf(" ##       ##           ##             #     ##      ##  ##  #    ##\n");
    printf(" #####     ######      ##         #####     ##      ##  ##   #   ##\n");
    printf(" ##              ##    ##         #         ##      ##  ##    #  ##\n");
    printf(" ##              ##    ##        #          ##      ##  ##     # ##\n");
    printf(" #######    #####    ######     ########    ##########  ##      ###\n");
    printf("                                                      ##\n");
    printf("        ##                                          ##  ##\n");
    printf("         ##                                       ##     ##\n");
    printf("           ##                                   ##   ##    ##\n");
    printf("             ###                                   ###       ##\n");
    printf("                ###                             ###\n");
    printf("                   ####                     ####  \n");
    printf("                       #######       #######\n");
    printf("                              #######\n");

    // COMPROBAR QUE EL ROL ESTÉ REGISTRADO
    do
    {
        printf("¿Como vas a acceder?\n");
        printf("1- Administrador\n");
        printf("2- Usuario\n");
        printf("3- Proveedor\n");
        printf("4- Transportista\nIndique rol: ");
        scanf("%d", &rol);
        flushInputBuffer();
    } while (iniciarSesion() != 0);

    switch (rol)
    {
    case 1:
        menuadmin();
        break;
    case 2:
        menuusuario();
        break;
    case 3:
        menuproveedor();
        break;
    case 4:
        menutransportista();
        break;
    }
}

// Devuelve 0 si pudo iniciar sesion en el rol indicado y 1 si no,
int iniciarSesion()
{
    int encontrado = 1;
    if (rol < 1 || rol > 4)
    {
        printf("Ese rol no existe\n");
    }
    else
    {
        printf("Correo electronico: ");
        char correo[31];
        fgets(correo, 31, stdin);
        // Elimina el \n
        correo[strcspn(correo, "\n")] = 0;

        printf("Clave de acceso: ");
        char contrasenia[16];
        fgets(contrasenia, 16, stdin);
        contrasenia[strcspn(contrasenia, "\n")] = 0;
        // 1-Administrador
        // 2-Usuario
        // 3-Proveedor
        // 4-Transportista
        switch (rol)
        {
        case 1:
            encontrado = comprobarAdminoProv(correo, contrasenia, "administrador");
            break;
        case 2:
            encontrado = comprobarUsuario(correo, contrasenia);
            break;
        case 3:
            encontrado = comprobarAdminoProv(correo, contrasenia, "proveedor");
            break;
        case 4:
            encontrado = comprobarTransportista(correo, contrasenia);
            break;
        }

        // Mensaje de error si no accede
        if (encontrado == 1)
        {
            printf("Algún dato es incorrecto\n");
        }
    }

    return encontrado;
}

int comprobarAdminoProv(char *email, char *contrasenia, char *rol)
{
    int encontrado = 1;
    for (int i = 0; i < numAdminProvs && encontrado == 1; i++)
    {
        if (strcmp(adminProvs[i].email, email) == 0 && strcmp(adminProvs[i].contrasenia, contrasenia) == 0 && strcmp(adminProvs[i].perfil_usuario, rol) == 0)
        {
            encontrado = 0;
            posVectorClienteActual = i;
        }
    }

    return encontrado;
}

int comprobarUsuario(char *email, char *contrasenia)
{
    int encontrado = 1;
    for (int i = 0; i < numClientes && encontrado == 1; i++)
    {
        if (strcmp(clientes[i].email, email) == 0 && strcmp(clientes[i].contrasenia, contrasenia) == 0)
        {
            encontrado = 0;
            posVectorClienteActual = i;
        }
    }

    return encontrado;
}

int comprobarTransportista(char *email, char *contrasenia)
{
    int encontrado = 1;
    for (int i = 0; i < numTransportistas && encontrado == 1; i++)
    {
        if (strcmp(transportistas[i].email, email) == 0 && strcmp(transportistas[i].contrasenia, contrasenia) == 0)
        {
            encontrado = 0;
            posVectorClienteActual = i;
        }
    }

    return encontrado;
}

// Rol de administrador
// Solo puede acceder: Administrador
void menuadmin()
{
    int opcion;
    do
    {
        printf("--------------------------------------------------------\n");
        printf("             NOMBRE: %s                                 \n", adminProvs[posVectorClienteActual].nombre);
        printf("--------------------------------------------------------\n");
        printf("|1-Perfil                                              |\n");
        printf("|2-Clientes                                            |\n");
        printf("|3-Proveedores                                         |\n");
        printf("|4-Productos                                           |\n");
        printf("|5-Categorias                                          |\n");
        printf("|6-Pedidos                                             |\n");
        printf("|7-Transportista                                       |\n");
        printf("|8-Descuentos                                          |\n");
        printf("|9-Devoluciones                                        |\n");
        printf("|10-Salir del sistema                                  |\n");
        printf("--------------------------------------------------------\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            mostrarPerfil();
            break;
        case 2:
            mostrarClientes();
            break;
        case 3:
            mostrarProveedores();
            break;
        case 4:
            mostrarProductos();
            break;
        case 5:
            mostrarCategorias();
            break;
        case 6:
            mostrarPedidos();
            break;
        case 7:
            mostrarTransportista();
            break;
        case 8:
            mostrarDescuentos();
            break;
        case 9:
            mostrarDevoluciones();
            break;
        case 10:
            printf("Hasta pronto, ESIZON\n");
            salirprograma();
            break;
        default:
            printf("Opción no válida\n");
            break;
        }
    } while (opcion != 10);
}

// Rol de cliente
// Solo puede acceder: cliente
void menuusuario()
{
    int opcion;
    do
    {
        printf("--------------------------------------------------------\n");
        printf("             NOMBRE: %s \n", clientes[posVectorClienteActual].nomb_cliente);
        printf("--------------------------------------------------------\n");
        printf("|1-Perfil                                              |\n");
        printf("|2-Productos                                           |\n");
        printf("|3-Descuentos                                          |\n");
        printf("|4-Pedidos                                             |\n");
        printf("|5-Devoluciones                                        |\n");
        printf("|6-Salir del sistema                                   |\n");
        printf("--------------------------------------------------------\n");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            mostrarPerfil();
            break;
        case 2:
            mostrarProductos();
            break;
        case 3:
            mostrarDescuentos();
            break;
        case 4:
            mostrarPedidos();
            break;
        case 5:
            mostrarDevoluciones();
            break;
        case 6:
            printf("Hasta pronto, ESIZON\n");
            salirprograma();
            break;
        default:
            printf("Opción no válida\n");
            break;
        }
    } while (opcion != 6);
}

void menuproveedor()
{
    int opcion;
    do
    {
        printf("--------------------------------------------------------\n");
        printf("             NOMBRE: %s                                 \n", adminProvs[posVectorClienteActual].nombre);
        printf("--------------------------------------------------------\n");
        printf("|1-Perfil                                              |\n");
        printf("|2-Productos                                           |\n");
        printf("|3-Pedidos                                             |\n");
        printf("|4-Salir del sistema                                   |\n");
        printf("--------------------------------------------------------\n");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            mostrarPerfil();
            break;
        case 2:
            mostrarProductos();
            break;
        case 3:
            mostrarPedidos();
            break;
        case 4:
            printf("Hasta pronto, ESIZON\n");
            salirprograma();
            break;
        default:
            printf("Opción no válida\n");
            break;
        }
    } while (opcion != 4);
}

void menutransportista()
{
    int opcion;

    do
    {
        printf("--------------------------------------------------------\n");
        printf("             NOMBRE: %s                                 \n", transportistas[posVectorClienteActual].nombre);
        printf("--------------------------------------------------------\n");
        printf("|1-Perfil                                              |\n");
        printf("|2-Repartos                                            |\n");
        printf("|3-Retornos                                            |\n");
        printf("|4-Salir del sistema                                   |\n");
        printf("--------------------------------------------------------\n");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            mostrarPerfil();
            break;
        case 2:
            enReparto();
            break;
        case 3:
            retornoProducto();
            break;
        case 4:
            printf("Hasta pronto, ESIZON\n");
            salirprograma();
            break;
        default:
            printf("Opción no válida\n");
            break;
        }
    } while (opcion != 4);
}

// Esta opción permitirá a un usuario administrador consultar los datos de su perfil y modificarlos.
// Solo puede acceder: Administrador y clientes y transportista y proveedores
void mostrarPerfil()
{
    switch (rol)
    {
    case 1:

        break;
    case 2:

        break;
    case 3:
        mostrar_perfilprov(adminProvs[posVectorClienteActual]);
        flushInputBuffer();
        modificar_perfilprov(&adminProvs[posVectorClienteActual]);
        break;
    case 4:

        break;
    default:
        break;
    }
}

// Mediante esta opción el administrador podrá acceder a la información de los clientes dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de clientes.
// Solo puede acceder: Administrador
void mostrarClientes()
{
    // Implementación de la función clientes
}

// Mediante esta opción el administrador podrá acceder a la información de los proveedores, deproductos externos, dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de proveedores.
// Solo puede acceder: Administrador
void mostrarProveedores()
{
    // Implementación de la función proveedores
}

// Mediante esta opción el administrador podrá acceder a la información de los productos dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de productos.
// Solo puede acceder: Administrador y cliente y proveedor
void mostrarProductos()
{
    switch (rol)
    {
    case 1:

        break;
    case 2:

        break;
    case 3:
        seccionProductosProv();
        break;
    case 4:
        break;
    default:
        break;
    }
}

void seccionProductosProv()
{
    printf("Tus productos: \n");

    printf("¿Que deseas hacer?\n");
    printf("1- Listar mis productos\n");
    printf("2- Alta producto\n");
    printf("3- Baja producto\n");
    printf("4- Modificar producto\n");
    printf("5- Buscar producto\n");
    printf("6- Salir\n");

    int opcion;
    scanf("%d", &opcion);
    flushInputBuffer();

    switch (opcion)
    {
    case 1:
        listado_producto_prooved(productos, &numProductos, adminProvs[posVectorClienteActual].id_empresa);
        break;
    case 2:
        alta_producto(&productos, &numProductos, adminProvs[posVectorClienteActual].id_empresa, categorias, &numCategorias);
        break;
    case 3:
        printf("Introduzca la id del producto a dar de baja:\n");
        char *prodBaja;
        fgets(prodBaja, 8, stdin);
        if (productoEsDeProveedor(productos, &numProductos, adminProvs[posVectorClienteActual].id_empresa, prodBaja) == 1)
        {
            baja_producto(&productos, &numProductos, prodBaja);
        }
        else
        {
            printf("Ese producto no es suyo\n");
        }
        break;
    case 4:
        modificar_producto(productos,&numProductos,adminProvs[posVectorClienteActual].id_empresa);break;
    }
}

// Mediante esta opción el administrador podrá acceder a la información de las categorías dadas de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de categorías. Además podrá generar listados de productos por categoría.
// Solo puede acceder: Administrador
void mostrarCategorias()
{
    // Implementación de la función categorias
}

// Mediante esta opción el administrador podrá acceder a la información de los pedidos dados de alta en la plataforma.
// Solo puede acceder: Administrador y cliente y proveedores
void mostrarPedidos()
{
    printf("1- Listar pedidos pendientes\n");
    printf("2- Asignar transportista a pedido\n");

}

// Mediante esta opción el administrador podrá acceder a la información de todos los transportistas dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de transportistas.
// Solo puede acceder: Administrador
void mostrarTransportista()
{
    // Implementación de la función transportista
}

// Mediante esta opción el administrador podrá acceder a la información de todos los códigos promocionales y/o cheques regalo dados de alta en la plataforma.
// Solo puede acceder: Administrador y cliente
void mostrarDescuentos()
{
    // Implementación de la función descuentos
}

// Mediante esta opción el administrador podrá acceder a la información de todas las mostrarDevoluciones() de productos.
// Solo puede acceder: Administrador y cliente
void mostrarDevoluciones()
{
    // Implementación de la función mostrarDevoluciones()
}

// Esta opción permitirá al transportista consultar la lista de productos que tiene asignados para su entrega así como la fecha prevista para la misma, lo que le permite realizar su ruta de reparto.
// Solo puede acceder: transportista
void enReparto()
{
}

// El sistema facilitará al transportista la tarea de retornar a origen todos los productos que nohayan sido recogidos de los lockers en el plazo determinado, permitiéndole consultar todos los lockers por localidad y mostrando sus pedidos. En el momento de la recogida de los productos
// para su retorno, el sistema debe actualizar automáticamente el número de compartimentos
// ocupados y eliminar el código locker asociado al producto. Así como el estado de los productos
// y el stock de los mismos para que quede reflejada la operación
// Solo puede acceder: transportista
void retornoProducto()
{
}

// Esta opción permitirá al transportista consultar la lista de productos que tiene asignados para su entrega así como la fecha prevista para la misma, lo que le permite realizar su ruta de reparto.
// Solo puede acceder: Administrador y clientes y transportista y proveedor
void salirprograma()
{
}

