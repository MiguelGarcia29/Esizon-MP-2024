#include "ESIZON.h"

void almacenarDatos(Cliente *clientes, int numClientes, AdminProv *adminProvs, int numAdminProvs, Categoria *categorias, int numCategorias, CompartimentoLocker *compartimentoLockers, int numCompartimentoLockers, DescuentoCliente *descuentoClientes, int numDescuentoClientes, Descuento *descuentos, int numDescuentos, Devolucion *devoluciones, int numDevoluciones, Locker *lockers, int numLockers, Pedido *pedidos, int numPedido, Producto *productos, int numProductos, ProductoPedido *productoPedidos, int numProductoPedidos, Transportista *transportistas, int numTransportistas) ;

// CARGA TODO LOS DATOS EN LOS VECTORES
void inicializarDatos(Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                      Categoria **categorias, int *numCategorias, CompartimentoLocker **compartimentoLockers, int *numCompartimentoLockers,
                      DescuentoCliente **descuentoClientes, int *numDescuentoClientes, Descuento **descuentos, int *numDescuentos,
                      Devolucion **devoluciones, int *numDevoluciones, Locker **lockers, int *numLockers, Pedido **pedidos, int *numPedido,
                      Producto **productos, int *numProductos, ProductoPedido **productoPedidos, int *numProductoPedidos,
                      Transportista **transportistas, int *numTransportistas)
{
    iniciarClientesDeArchivo(numClientes,clientes);
    iniciarAdminProvDeArchivo(numAdminProvs,adminProvs);
    *productos = iniciarProductosDeArchivo(numProductos);
    *descuentos = iniciarDescuentosDeArchivo(numDescuentos);
    *descuentoClientes = iniciarDescuentosClientesDeArchivo(numDescuentoClientes);
    *lockers = iniciarLockersDeArchivo(numLockers);
    *compartimentoLockers = iniciarCompartimientoLockersDeArchivo(numCompartimentoLockers);
    *pedidos = iniciarPedidosDeArchivo(numPedido);
    *productoPedidos = iniciarProductoPedidosDeArchivo(numProductoPedidos);
    *transportistas = iniciarTransportistasDeArchivo(numTransportistas);
    *devoluciones = iniciarDevolucionDeArchivo(numDevoluciones);
    *categorias = iniciarCategoriasDeArchivo(numCategorias);
}

void almacenarDatos(Cliente *clientes, int numClientes, AdminProv *adminProvs, int numAdminProvs, Categoria *categorias, int numCategorias, CompartimentoLocker *compartimentoLockers, int numCompartimentoLockers, DescuentoCliente *descuentoClientes, int numDescuentoClientes, Descuento *descuentos, int numDescuentos, Devolucion *devoluciones, int numDevoluciones, Locker *lockers, int numLockers, Pedido *pedidos, int numPedido, Producto *productos, int numProductos, ProductoPedido *productoPedidos, int numProductoPedidos, Transportista *transportistas, int numTransportistas)
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

void accederPrograma(Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                      Categoria **categorias, int *numCategorias, CompartimentoLocker **compartimentoLockers, int *numCompartimentoLockers,
                      DescuentoCliente **descuentoClientes, int *numDescuentoClientes, Descuento **descuentos, int *numDescuentos,
                      Devolucion **devoluciones, int *numDevoluciones, Locker **lockers, int *numLockers, Pedido **pedidos, int *numPedido,
                      Producto **productos, int *numProductos, ProductoPedido **productoPedidos, int *numProductoPedidos,
                      Transportista **transportistas, int *numTransportistas)
{

    int rol;
    int posVectorClienteActual;
    // 1-Administrador
    // 2-Usuario
    // 3-Proveedor
    // 4-Transportista


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
        printf("¿Cómo vas a acceder?\n");
        printf("1- Administrador\n");
        printf("2- Usuario\n");
        printf("3- Proveedor\n");
        printf("4- Transportista\nIndique rol: ");
        scanf("%d", &rol);
        flushInputBuffer();
    } while (iniciarSesion(rol,&posVectorClienteActual,*clientes,*numClientes,*adminProvs,*numAdminProvs,*transportistas,*numTransportistas)!=0);

    switch (rol)
    {
    case 1:
        menuadmin();
        break;
    case 2:
        menuusuario();
        break;
    case 3:

        menuproveedor(rol,posVectorClienteActual,clientes,numClientes,adminProvs,numAdminProvs,transportistas,numTransportistas,productos,numProductos,categorias,numCategorias,productoPedidos,numProductoPedidos);
        break;
    case 4:
        menutransportista(rol,posVectorClienteActual,clientes,numClientes,adminProvs,numAdminProvs,transportistas,numTransportistas,productos,numProductos,categorias,numCategorias, numProductoPedidos);
        break;
    }


   // almacenarDatos(clientes, numClientes, adminProvs, numAdminProvs, categorias, numCategorias, compartimentoLockers, numCompartimentoLockers, descuentoClientes, numDescuentoClientes, descuentos, numDescuentos, devoluciones, numDevoluciones, lockers, numLockers, pedidos, numPedido, productos, numProductos, productoPedidos, numProductoPedidos, transportistas, numTransportistas);
}

// Devuelve 0 si pudo iniciar sesion en el rol indicado y 1 si no,
int iniciarSesion(int rol, int *posVectorActual, Cliente *clientes, int numClientes, AdminProv *adminProvs, int numAdminProvs, Transportista *transportistas, int numTransportistas)
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
            encontrado = comprobarAdminoProv(correo, contrasenia, "administrador",adminProvs,numAdminProvs,posVectorActual);
            break;
        case 2:
            encontrado = comprobarUsuario(correo, contrasenia,clientes,numClientes,posVectorActual);
            break;
        case 3:
            encontrado = comprobarAdminoProv(correo, contrasenia, "proveedor",adminProvs,numAdminProvs,posVectorActual);
            break;
        case 4:
            encontrado = comprobarTransportista(correo, contrasenia,transportistas,numTransportistas, posVectorActual);
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

int comprobarAdminoProv(char *email, char *contrasenia, char *rol, AdminProv *adminProvs, int numAdminProvs, int *posVectorClienteActual)
{
    int encontrado = 1;
    for (int i = 0; i < numAdminProvs && encontrado == 1; i++)
    {

        if (strcmp(adminProvs[i].email, email) == 0 && strcmp(adminProvs[i].contrasenia, contrasenia) == 0 && strcmp(adminProvs[i].perfil_usuario, rol) == 0)
        {
            encontrado = 0;
            *posVectorClienteActual = i;
        }
    }

    return encontrado;
}

int comprobarUsuario(char *email, char *contrasenia, Cliente * clientes, int numClientes, int *posVectorClienteActual)
{
    int encontrado = 1;
    for (int i = 0; i < numClientes && encontrado == 1; i++)
    {
        if (strcmp(clientes[i].email, email) == 0 && strcmp(clientes[i].contrasenia, contrasenia) == 0)
        {
            encontrado = 0;
            *posVectorClienteActual = 2;
        }
    }

    return encontrado;
}

int comprobarTransportista(char *email, char *contrasenia, Transportista *transportistas, int numTransportistas, int *posVectorClienteActual)
{
    int encontrado = 1;
    for (int i = 0; i < numTransportistas && encontrado == 1; i++)
    {
        if (strcmp(transportistas[i].email, email) == 0 && strcmp(transportistas[i].contrasenia, contrasenia) == 0)
        {
            encontrado = 0;
            *posVectorClienteActual = i;
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
        //printf("             NOMBRE: %s                                 \n", adminProvs[posVectorClienteActual].nombre);
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
            //mostrarPerfil();
            break;
        case 2:
            mostrarClientes();
            break;
        case 3:
            mostrarProveedores();
            break;
        case 4:
            //mostrarProductos();
            break;
        case 5:
            mostrarCategorias();
            break;
        case 6:
            //mostrarPedidos();
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
       // printf("             NOMBRE: %s \n", clientes[posVectorClienteActual].nomb_cliente);
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
            //mostrarPerfil();
            break;
        case 2:
            //mostrarProductos();
            break;
        case 3:
            mostrarDescuentos();
            break;
        case 4:
            //mostrarPedidos();
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

void menuproveedor(int rol,int posVectorClienteActual,Cliente **clientes, int  *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                   Transportista **transportistas, int* numTransportistas, Producto **productos, int *numProductos, Categoria ** categorias, int *numCategorias, ProductoPedido **pedidos, int *tamanioPed)
{
    int opcion;
    do
    {
        printf("--------------------------------------------------------\n");
        printf("             NOMBRE: %s                                 \n", (*adminProvs)[posVectorClienteActual].nombre);
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
            mostrar_perfilprov((*adminProvs)[posVectorClienteActual]);
            flushInputBuffer();
            printf("¿Quieres modificarlo?:\n");
            printf("1- Si\n");
            printf("2- No\n");
            int opcion;
            scanf("%d",&opcion);
            flushInputBuffer();
            if(opcion==1)
                modificar_perfilprov(&adminProvs[posVectorClienteActual]);
            break;
        case 2:
            seccionProductosProv(productos,numProductos, categorias, numCategorias,(*adminProvs)[posVectorClienteActual].id_empresa);
            break;
        case 3:
            seccionPedidosProv(pedidos,tamanioPed,(*adminProvs)[posVectorClienteActual].id_empresa,productos,numProductos,transportistas,numTransportistas);
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

void menutransportista(int rol, int posVectorClienteActual, Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                       Transportista **transportistas, int *numTransportistas, Producto **productos, int *numProductos, Categoria **categorias, int *numCategorias, int *numProductoPedidos)
{
    int opcion;

    do
    {
        printf("--------------------------------------------------------\n");
        printf("             NOMBRE: %s                                 \n", (*transportistas)[posVectorClienteActual].nombre);
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
            perfil_t(&(*transportistas)[posVectorClienteActual]);
            break;
        case 2:
            enReparto(transportistas, numProductoPedidos);//no encuentra los pedidos mirar
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
/* Solo puede acceder: Administrador y clientes y transportista y proveedores
void mostrarPerfil(int rol);
{
    switch (rol)
    {
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    default:
        break;
    }
}
*/
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
/*void mostrarProductos()
{
    switch (rol)
    {
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:
        break;
    default:
        break;
    }
}
*/
void seccionProductosProv(Producto **productos,int *numProductos, Categoria **categorias,int * numCategorias, char *id)
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
        listado_producto_prooved(productos, *numProductos, id);
        break;
    case 2:
        alta_producto(productos, numProductos, id, categorias, numCategorias);
        break;
    case 3:
        printf("Introduzca la id del producto a dar de baja:\n");
        char prodBaja[9];
        fgets(prodBaja, 9, stdin);
        prodBaja[strcspn(prodBaja, "\n")] = '\0';

        int recibidor = productoEsDeProveedor(productos, numProductos, id, prodBaja);
        printf("%d", recibidor);
        if (recibidor == 1)
        {
            baja_producto(productos, numProductos, prodBaja);
        }
        else
        {
            printf("Ese producto no es suyo\n");
        }

        break;
    case 4:
        modificar_producto(productos,numProductos,id);break;
    case 5:
        char producto_buscado[51];

        printf("\nIntroduce el nombre del producto que quieres buscar: ");
        fflush(stdin);
        fgets(producto_buscado, 51, stdin);
        producto_buscado[strcspn(producto_buscado, "\n")] = '\0';

        buscador_un_producto(productos, numProductos, producto_buscado);
        break;
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
void seccionPedidosProv(ProductoPedido **pedidos, int* tamanioPed, char *idProv,Producto** productos, int *nProductos,Transportista** trans, int * nTrans)
{
    printf("1- Listar pedidos pendientes\n");
    printf("2- Asignar transportista a pedido\n");
     int opcion;
    scanf("%d", &opcion);
    flushInputBuffer();

    switch (opcion)
    {
    case 1:
        listado_pedido_pendiente(pedidos,tamanioPed,idProv,productos,nProductos);
        break;

    case 2:
        asignarProductoPedidoProv(pedidos,tamanioPed,trans,nTrans,idProv,productos,nProductos);

        break;
    }

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
void enReparto(Transportista **transportistas, int *numProductoPedidos)
{
    printf("Dime la id del transportista que quiere saber los productos que tiene asignados:");
    char id_t[5];
    scanf("%4s", id_t);
    flushInputBuffer();
    reparto(transportistas, numProductoPedidos, id_t);
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
    printf("\n\n");
    printf("             XXXXXX\n");
    printf("             X\n");
    printf("             X\n");
    printf("             XXXX\n");
    printf("             X\n");
    printf("             X\n");
    printf("             XXXXXX");

    Sleep(100);
    system("cls");
//system("color 79");

    printf("\n\n");
    printf("             XXXXXX  XXXXXX\n");
    printf("             X       X\n");
    printf("             X       X\n");
    printf("             XXXX    XXXXXX\n");
    printf("             X            X\n");
    printf("             X            X\n");
    printf("             XXXXXX  XXXXXX");

    Sleep(100);
    system("cls");
//system("color 7d");

    printf("\n\n");
    printf("             XXXXXX  XXXXXX  XXXXXX\n");
    printf("             X       X         XX\n");
    printf("             X       X         XX\n");
    printf("             XXXX    XXXXXX    XX\n");
    printf("             X            X    XX\n");
    printf("             X            X    XX\n");
    printf("             XXXXXX  XXXXXX  XXXXXX");

    Sleep(100);
    system("cls");
//system("color 79");

    printf("\n\n");
    printf("             XXXXXX  XXXXXX  XXXXXX  XXXXXXXX\n");
    printf("             X       X         XX          X \n");
    printf("             X       X         XX        X   \n");
    printf("             XXXX    XXXXXX    XX     XXXXXX \n");
    printf("             X            X    XX      X     \n");
    printf("             X            X    XX     X      \n");
    printf("             XXXXXX  XXXXXX  XXXXXX  XXXXXXXX");

    Sleep(100);
    system("cls");
//system("color 7d");

    printf("\n\n");
    printf("             XXXXXX  XXXXXX  XXXXXX  XXXXXXXX   XXXXXX \n");
    printf("             X       X         XX          X   X      X\n");
    printf("             X       X         XX        X     X      X\n");
    printf("             XXXX    XXXXXX    XX     XXXXXX   X      X\n");
    printf("             X            X    XX      X       X      X\n");
    printf("             X            X    XX     X        X      X\n");
    printf("             XXXXXX  XXXXXX  XXXXXX  XXXXXXXX   XXXXXX ");

    Sleep(100);
    system("cls");
//system("color 79");

    printf("\n\n");
    printf("             XXXXXX  XXXXXX  XXXXXX  XXXXXXXX   XXXXXX    XX      X\n");
    printf("             X       X         XX          X   X      X   X X     X\n");
    printf("             X       X         XX        X     X      X   X  X    X\n");
    printf("             XXXX    XXXXXX    XX     XXXXXX   X      X   X   X   X\n");
    printf("             X            X    XX      X       X      X   X    X  X\n");
    printf("             X            X    XX     X        X      X   X     X X\n");
    printf("             XXXXXX  XXXXXX  XXXXXX  XXXXXXXX   XXXXXX    X      XX ");

    Sleep(600);
    system("cls");
    system("color 0f");
    printf("\n\n               REALIZADOR POR:\n");

    printf("                      +---------------------------------+\n");
    printf("                      |                                 |\n");
    printf("                      |    Jesus Miguel Garcia Bernal   |\n");
    printf("                      |     Manuel Gutierrez Recio      |\n");
    printf("                      | Carlos Manuel Pedraza Gonzalez  |\n");
    printf("                      |        Jacobo Caro Luna         |\n");
    printf("                      |                                 |\n");
    printf("                      +---------------------------------+\n");
    system("pause");
    system("cls");

    return;
}

