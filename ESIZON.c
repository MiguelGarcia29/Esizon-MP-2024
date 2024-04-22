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
        menuadmin(rol,posVectorClienteActual,clientes,numClientes,adminProvs,numAdminProvs,transportistas,numTransportistas,productos,numProductos,categorias,numCategorias, numProductoPedidos);
        break;
    case 2:
        menuusuario();
        break;
    case 3:

        menuproveedor(rol,posVectorClienteActual,clientes,numClientes,adminProvs,numAdminProvs,transportistas,numTransportistas,productos,numProductos,categorias,numCategorias,productoPedidos,numProductoPedidos);
        break;
    case 4:
        menutransportista(rol,posVectorClienteActual,lockers,numLockers, clientes,numClientes,adminProvs,numAdminProvs,transportistas,numTransportistas,productos,numProductos,categorias,numCategorias, numProductoPedidos, productoPedidos, compartimentoLockers,numCompartimentoLockers);
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
void menuadmin(int rol,int posVectorClienteActual,Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                      Categoria **categorias, int *numCategorias, CompartimentoLocker **compartimentoLockers, int *numCompartimentoLockers,
                      DescuentoCliente **descuentoClientes, int *numDescuentoClientes, Descuento **descuentos, int *numDescuentos,
                      Devolucion **devoluciones, int *numDevoluciones, Locker **lockers, int *numLockers, Pedido **pedidos, int *numPedido,
                      Producto **productos, int *numProductos, ProductoPedido **productoPedidos, int *numProductoPedidos,
                      Transportista **transportistas, int *numTransportistas)
{
    int opcion;
    do
    {
        printf("--------------------------------------------------------\n");
        printf("             NOMBRE: %s                                 \n", (*adminProvs)[posVectorClienteActual].nombre);
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
            seccionClienteAdmin(clientes,numClientes);
        case 3:
            mostrarProveedoresAdmin(adminProvs,numAdminProvs);
            break;
        case 4:
            mostrarProductosAdmin(productos, numProductos,categorias,numCategorias,(*adminProvs)[posVectorClienteActual].id_empresa);
            break;
        case 5:
            mostrarCategoriasAdmin(categorias,numCategorias,productos,numProductos);
            break;
        case 6:
            mostrarPedidosAdmin(productoPedidos,numProductoPedidos,transportistas,numTransportistas,(*adminProvs)[posVectorClienteActual].id_empresa,productos,numProductos,pedidos,numPedido);
            break;
        case 7:
            mostrarTransportista(transportistas,numTransportistas);
            break;
        case 8:
            mostrarDescuentos();
            break;
        case 9:
            mostrarDevolucionesAdmin(devoluciones,numDevoluciones,productoPedidos,numProductoPedidos);
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

void mostrarCategoriasAdmin(Categoria **categorias, int *numCategorias,Producto **productos, int *numProductos){
    int opcion;
    do {
        printf("1- Alta categoría                                     \n");
        printf("2- Baja categoría                                     \n");
        printf("3- Buscar categoría                                   \n");
        printf("4- Listar categorías                                  \n");
        printf("5- Modificar categoría                                \n");
        printf("6- Listar productos por categoría                     \n");
        printf("7- Salir\n");

        scanf("%d", &opcion);
        flushInputBuffer();

        switch (opcion) {
            case 1:
                alta_categoria(categorias, numCategorias);
                break;
            case 2:
                baja_categoria(categorias, numCategorias);
                break;
            case 3:
                buscarCategoria(categorias, numCategorias);
                break;
            case 4:
                listarCategorias(categorias, numCategorias);
                break;
            case 5:
                modificarCategoria(categorias, numCategorias);
                break;
            case 6:
                listarProductosPorCategoria(productos,numProductos,categorias,numCategorias);
                break;
        }
    } while (opcion != 7);
}

void mostrarProductosAdmin(Producto **productos, int *numProductos, Categoria ** categorias, int *numCategorias, char * id){

    int opcion;
    do {

        printf("1- Alta producto\n");
        printf("2- Baja producto\n");
        printf("3- Buscar producto\n");
        printf("4- Listar productos\n");
        printf("5- Modificar producto\n");
        printf("6- Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);
        flushInputBuffer();

        switch (opcion) {
            case 1:
                alta_producto(productos, numProductos, id, categorias, numCategorias);
        break;
                break;
            case 2:
                printf("Introduzca la id del producto a dar de baja:\n");
                char prodBaja[9];
                fgets(prodBaja, 9, stdin);
                prodBaja[strcspn(prodBaja, "\n")] = '\0';
                baja_producto(productos, numProductos, prodBaja);
                break;
            case 3:
              char producto_buscado[51];

                printf("\nIntroduce el nombre del producto que quieres buscar: ");
                fflush(stdin);
                fgets(producto_buscado, 51, stdin);
                producto_buscado[strcspn(producto_buscado, "\n")] = '\0';

                buscador_un_producto(productos, numProductos, producto_buscado);
                break;
            case 4:
                listado_producto(productos, numProductos);
                break;
            case 5:
                modificar_producto(productos,numProductos,"-1");
                break;
        }
    } while (opcion != 6);


}

void mostrarPedidosAdmin(ProductoPedido ** pedidos, int * tamPedidos, Transportista ** trans, int *nTrans,char *idProv, Producto **productos, int * nProductos, Pedido **ped, int * numPed){

    int opcion;
    do {
        printf("1- Alta de pedido\n");
        printf("2- Baja de pedido\n");
        printf("3- Buscar pedido\n");
        printf("4- Listar pedidos\n");
        printf("5- Asignar transportista a pedido\n");
        printf("6- Asignar locker a pedido\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        flushInputBuffer();

        switch (opcion) {
            case 1:
                float coste;
                int tamLista;
                Producto *cesta = agregar_a_cesta(productos,nProductos,&coste,&tamLista);

                printf("¿Dónde desea que se entregue su pedido?\n");
                printf("1. Domicilio\n");
                printf("2. Locker\n");

                int opc;
                printf("Ingrese su opción (1 o 2): ");
                scanf("%d", &opc);
                flushInputBuffer();
                char opcion[10];
                char idLocker[11];
                switch (opc) {
                    case 1:
                        strcpy(opcion,"domicilio");
                        strcpy(idLocker," ");
                        break;
                    case 2:
                        strcpy(opcion,"locker");
                        printf("Ingrese la ID del locker donde desea enviar su pedido: ");
                        fgets(idLocker, 11, stdin);
                        idLocker[strcspn(idLocker, "\n")] = '\0';
                        break;

                }

                hacerPedido(&cesta, tamLista,productos, nProductos,
                 ped, numPed, pedidos,tamPedidos, idProv,
                  opcion, idLocker);

                break;
            case 2:
                printf("Introduzca la id del pedido a dar de baja:\n");
                char idPed[8];
                fgets(idPed, 8, stdin);
                idPed[strcspn(idPed, "\n")] = '\0';
                baja_prodPed(pedidos,tamPedidos,idPed);
                baja_pedido(ped,numPed,idPed);
                break;
            case 3:
                printf("Introduzca la id del pedido a buscar:\n");
                fgets(idPed, 8, stdin);
                idPed[strcspn(idPed, "\n")] = '\0';
                buscarPedido(pedidos,tamPedidos,idPed);
                break;
            case 4:
                listado_pedido(pedidos,tamPedidos);
                break;
            case 5:
                asignarProductoPedidoProv(pedidos, tamPedidos,  trans, nTrans,idProv, productos, nProductos);
                break;
            case 6:
                asignarLocker(pedidos,ped,numPed,tamPedidos);
                break;

        }
    } while (opcion != 7);

}

void mostrarProveedoresAdmin(AdminProv **proveedores, int* numProveedores){
int opcion;
    do {

        printf("1- Alta proveedor\n");
        printf("2- Baja proveedor\n");
        printf("3- Buscar proveedor\n");
        printf("4- Listar proveedores\n");
        printf("5- Modificar proveedor\n");
        printf("6- Volver al menú anterior\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
    flushInputBuffer();

        switch (opcion) {
            case 1:
                altaProveedor(proveedores, numProveedores);
                break;
            case 2:
                bajaProveedor(proveedores, numProveedores);
                break;
            case 3:
                buscarProveedor(proveedores, numProveedores);
                break;
            case 4:
                listarProveedores(proveedores, numProveedores);
                break;
            case 5:
                modificarProveedor(proveedores, numProveedores);
                break;

        }
    } while (opcion != 6);}

void seccionClienteAdmin(Cliente **clientes, int *numClientes){
    printf("1- Alta de cliente\n");
    printf("2- Baja de cliente\n");
    printf("3- Busqueda de cliente\n");
    printf("4- Listado de clientes\n");
    printf("5- Modificación de cliente\n");
    printf("Seleccione una opción: ");
    int opcionClientes;
    scanf("%d", &opcionClientes);
    flushInputBuffer();
    switch (opcionClientes) {
        case 1:
            // Dar de alta un cliente
            altaCliente(clientes, numClientes);
            break;
        case 2:
            // Dar de baja un cliente
            bajaCliente(clientes, numClientes);
            break;
        case 3:
            // Buscar un cliente
            buscarCliente(clientes, numClientes);
            break;
        case 4:
            // Listar todos los clientes
            listarClientes(clientes, numClientes);
            break;
        case 5:
            // Modificar un cliente
            modificarCliente(clientes, numClientes);
            break;

    }

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

void menutransportista(int rol, int posVectorClienteActual, Locker **lockers,int *numLockers ,Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                       Transportista **transportistas, int *numTransportistas, Producto **productos, int *numProductos, Categoria **categorias, int *numCategorias, int *numProductoPedidos, ProductoPedido **productoPedidos, CompartimentoLocker **compartimentoLockers, int *numCompartimentoLockers)
{
    int opcion;
    char id_t[7]; // Incrementamos el tamaño para incluir el carácter nulo

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
        getchar(); // Consumir el carácter de nueva línea residual del búfer de entrada

        switch (opcion)
        {
        case 1:
            perfil_t(&(*transportistas)[posVectorClienteActual]);
            break;
        case 2:
            reparto(productoPedidos, numProductoPedidos, (*transportistas)[posVectorClienteActual].id_transp);
            enReparto(productoPedidos, numProductoPedidos, compartimentoLockers, numCompartimentoLockers, id_t);
            break;
        case 3:
            retornoProducto(lockers,productos,numProductos, numLockers, (*lockers)[posVectorClienteActual].localidad);
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
void mostrarTransportista(Transportista **transportista, int *nTrans)
{

     int opcion;

    do {
        printf("1- Listar transportistas\n");
        printf("2- Agregar transportista\n");
        printf("3- Buscar transportista por ID\n");
        printf("4- Modificar transportista por ID\n");
        printf("5- Dar de baja transportista por ID\n");
        printf("6- Salir\n");
        scanf("%d", &opcion);
        flushInputBuffer();

        switch (opcion) {
            case 1:
                listar_transportistas(transportista, nTrans);
                break;
            case 2:
                agregar_transportista(transportista, nTrans);
                break;
            case 3:
                buscar_transportista(transportista, nTrans);
                break;
            case 4:
                modificar_transportista(transportista, nTrans);
                break;
            case 5:
                dar_de_baja_transportista(transportista, nTrans);
                break;


        }
    } while (opcion != 6);


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

void mostrarDevolucionesAdmin(Devolucion** devoluciones, int *num_devoluciones, ProductoPedido ** productoPedidos, int *prodPeds){
 int opcion;

    do {
        printf("1- Listar devoluciones\n");
        printf("2- Alta devolución\n");
        printf("3- Buscar devolución por ID\n");
        printf("4- Devoluciones pendiente de confirmacion\n");
        printf("5- Dar de baja devolución por ID\n");
        printf("6- Salir\n");
        scanf("%d", &opcion);
        flushInputBuffer();

        switch (opcion) {
            case 1:
                listar_devoluciones(devoluciones, num_devoluciones);
                break;
            case 2:
                alta_devolucion_admin(devoluciones, num_devoluciones, productoPedidos, prodPeds);
                break;
            case 3:
                printf("Introduzca la id de la devolucion buscada:\n");
                char idD[8];
                fgets(idD, 8, stdin);
                idD[strcspn(idD, "\n")] = '\0';
                buscar_devolucion(devoluciones,num_devoluciones,idD);
                break;
            case 4:
                modifYConsultarDevPedAdmin(devoluciones, num_devoluciones);
                break;
            case 5:
                printf("Introduzca la id de la devolucion a dar de baja:\n");
                fgets(idD, 8, stdin);
                idD[strcspn(idD, "\n")] = '\0';
                buscar_devolucion(devoluciones,num_devoluciones,idD);
                break;

        }
    } while (opcion != 6);

}

// Esta opción permitirá al transportista consultar la lista de productos que tiene asignados para su entrega así como la fecha prevista para la misma, lo que le permite realizar su ruta de reparto.
// Solo puede acceder: transportista
void enReparto(ProductoPedido **pedidos, int *num_pedidos, CompartimentoLocker **compartimiento, int *tamanio_compartimento, char *id_t) {
    // Verificar si se encontraron pedidos asignados al transportista
    int encontrado = 0;
    int i;
    for (i = 0; i < *num_pedidos; i++) {
        if (strcmp((*pedidos)[i].id_transp, id_t) == 0 && strcmp((*pedidos)[i].estado_pedido, "enReparto") == 0) {
            encontrado = 1;
            break;
        }
    }

    // Si se encontraron pedidos, preguntar si se desea realizar una entrega
    if (encontrado == 1) {
        printf("¿Quieres realizar alguna entrega?\n1-Sí\n2-No\n");
        int respuesta_enreparto;
        scanf("%d", &respuesta_enreparto);
        flushInputBuffer();
        switch (respuesta_enreparto) {
            case 1:
                entrega(pedidos, compartimiento, num_pedidos, tamanio_compartimento, id_t);

                break;
            case 2:
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    }
}


// El sistema facilitará al transportista la tarea de retornar a origen todos los productos que nohayan sido recogidos de los lockers en el plazo determinado, permitiéndole consultar todos los lockers por localidad y mostrando sus pedidos. En el momento de la recogida de los productos
// para su retorno, el sistema debe actualizar automáticamente el número de compartimentos
// ocupados y eliminar el código locker asociado al producto. Así como el estado de los productos
// y el stock de los mismos para que quede reflejada la operación
// Solo puede acceder: transportista
void retornoProducto(Locker **lockers, Producto **productos, int *numProductos, int *numLockers, char *loca) {
    retornarProductosNoRecogidos(productos, numProductos, lockers, numLockers, loca); // No necesitas desreferenciar los punteros aquí
}

// Esta opción permitirá al transportista consultar la lista de productos que tiene asignados para su entrega así como la fecha prevista para la misma, lo que le permite realizar su ruta de reparto.
// Solo puede acceder: Administrador y clientes y transportista y proveedor
void salirprograma()
{

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

