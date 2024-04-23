#include "ESIZON.h"
#include <windows.h>

void almacenarDatos(Cliente *clientes, int numClientes, AdminProv *adminProvs, int numAdminProvs, Categoria *categorias, int numCategorias, CompartimentoLocker *compartimentoLockers, int numCompartimentoLockers, DescuentoCliente *descuentoClientes, int numDescuentoClientes, Descuento *descuentos, int numDescuentos, Devolucion *devoluciones, int numDevoluciones, Locker *lockers, int numLockers, Pedido *pedidos, int numPedido, Producto *productos, int numProductos, ProductoPedido *productoPedidos, int numProductoPedidos, Transportista *transportistas, int numTransportistas) ;

// CARGA TODO LOS DATOS EN LOS VECTORES
void inicializarDatos(Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                      Categoria **categorias, int *numCategorias, CompartimentoLocker **compartimentoLockers, int *numCompartimentoLockers,
                      DescuentoCliente **descuentoClientes, int *numDescuentoClientes, Descuento **descuentos, int *numDescuentos,
                      Devolucion **devoluciones, int *numDevoluciones, Locker **lockers, int *numLockers, Pedido **pedidos, int *numPedido,
                      Producto **productos, int *numProductos, ProductoPedido **productoPedidos, int *numProductoPedidos,
                      Transportista **transportistas, int *numTransportistas)
{
    *clientes = iniciarClientesDeArchivo(numClientes);
    *adminProvs=iniciarAdminProvDeArchivo(numAdminProvs);
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
// ALMACENA TODOS LOS DATOS REGISTRADOS
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
// FUNCION QUE DA INICIO AL SISTEMA
void accederPrograma(Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                      Categoria **categorias, int *numCategorias, CompartimentoLocker **compartimentoLockers, int *numCompartimentoLockers,
                      DescuentoCliente **descuentoClientes, int *numDescuentoClientes, Descuento **descuentos, int *numDescuentos,
                      Devolucion **devoluciones, int *numDevoluciones, Locker **lockers, int *numLockers, Pedido **pedidos, int *numPedido,
                      Producto **productos, int *numProductos, ProductoPedido **productoPedidos, int *numProductoPedidos,
                      Transportista **transportistas, int *numTransportistas)
{
    // Declaración de variables locales
    int rol = 6; // Inicializa el rol como 6 (ningún rol definido)
    int posVectorClienteActual; // Variable para almacenar la posición del cliente actual

    // Impresión del mensaje de bienvenida
    // Se imprime un diseño gráfico y se solicitan las credenciales de inicio de sesión

    printf("\n");
    printf("   ########  #######   ######     ##########  ##########  ###      ##\n");
    printf("   ##       ##           ##              #    ##      ##  ## #     ##\n");
    printf("   ##       ##           ##             #     ##      ##  ##  #    ##\n");
    printf("   #####     ######      ##         #####     ##      ##  ##   #   ##\n");
    printf("   ##              ##    ##         #         ##      ##  ##    #  ##\n");
    printf("   ##              ##    ##        #          ##      ##  ##     # ##\n");
    printf("   #######    #####    ######     ########    ##########  ##      ###\n");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// Se encarga de mostrar el color de los caracteres
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Se encarga de mostrar el color de los caracteres
    printf("                                                        ##\n");
    printf("          ##                                          ##  ##\n");
    printf("           ##                                       ##     ##\n");
    printf("            ##                                   ##   ##    ##\n");
    printf("              ###                                   ###       ##\n");
    printf("                 ###                             ###\n");
    printf("                    ####                     ####  \n");
    printf("                        #######       #######\n");
    printf("                               #######\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);// Se encarga de mostrar el color de los caracteres

    // COMPROBAR QUE EL ROL ESTÉ REGISTRADO
    // Ciclo para el inicio de sesión
    do
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

        // Llama a la función iniciarSesion para validar las credenciales y obtener el rol del usuario
        rol = iniciarSesion(&posVectorClienteActual, *clientes, *numClientes, *adminProvs, *numAdminProvs, *transportistas, *numTransportistas, correo, contrasenia);

    } while (rol == 6); // Repetir hasta que se inicie sesión con éxito

    // Una vez iniciada la sesión, se redirige al usuario según su rol
    switch (rol)
    {
    case 1: // Administrador
        menuadmin(rol, posVectorClienteActual, clientes, numClientes, adminProvs, numAdminProvs, transportistas, numTransportistas, productos, numProductos, categorias, numCategorias, numProductoPedidos);
        break;
    case 2: // Usuario (cliente)
        menuusuario(rol, posVectorClienteActual, clientes, numClientes, adminProvs, numAdminProvs, transportistas, numTransportistas, productos, numProductos, categorias, numCategorias, numProductoPedidos);
        break;
    case 3: // Proveedor
        menuproveedor(rol, posVectorClienteActual, clientes, numClientes, adminProvs, numAdminProvs, transportistas, numTransportistas, productos, numProductos, categorias, numCategorias, productoPedidos, numProductoPedidos);
        break;
    case 4: // Transportista
        menutransportista(rol, posVectorClienteActual, lockers, numLockers, clientes, numClientes, adminProvs, numAdminProvs, transportistas, numTransportistas, productos, numProductos, categorias, numCategorias, numProductoPedidos, productoPedidos, compartimentoLockers, numCompartimentoLockers);
        break;
    }
}

// Función para iniciar sesión
// Devuelve el rol del usuario que inició sesión
// Devuelve 0 si pudo iniciar sesión en el rol indicado y 1 si no
int iniciarSesion(int *posVectorActual, Cliente *clientes, int numClientes, AdminProv *adminProvs, int numAdminProvs, Transportista *transportistas, int numTransportistas, char *correo, char *contrasenia)
{
    // Variable para almacenar el rol del usuario
    int rol = 6;

    // Comprobar si el usuario es un administrador
    if (comprobarAdminoProv(correo, contrasenia, "administrador", adminProvs, numAdminProvs, posVectorActual) == 0)
        rol = 1; // Rol de administrador

    // Comprobar si el usuario es un cliente
    if (comprobarUsuario(correo, contrasenia, clientes, numClientes, posVectorActual) == 0)
        rol = 2; // Rol de cliente

    // Comprobar si el usuario es un proveedor
    if (comprobarAdminoProv(correo, contrasenia, "proveedor", adminProvs, numAdminProvs, posVectorActual) == 0)
        rol = 3; // Rol de proveedor

    // Comprobar si el usuario es un transportista
    if (comprobarTransportista(correo, contrasenia, transportistas, numTransportistas, posVectorActual) == 0)
        rol = 4; // Rol de transportista

    // Mensaje de error si no se pudo iniciar sesión
    if (rol == 6)
    {
        printf("Algún dato es incorrecto\n");
    }

    // Devolver el rol del usuario
    return rol;
}

// Función para comprobar las credenciales de un administrador o proveedor
int comprobarAdminoProv(char *email, char *contrasenia, char *rol, AdminProv *adminProvs, int numAdminProvs, int *posVectorClienteActual)
{
    // Variable para indicar si se ha encontrado una coincidencia de credenciales
    int encontrado = 1;

    // Recorre el arreglo de administradores y proveedores
    for (int i = 0; i < numAdminProvs && encontrado == 1; i++)
    {
        // Verifica si el correo electrónico, contraseña y rol coinciden
        if (strcmp(adminProvs[i].email, email) == 0 && strcmp(adminProvs[i].contrasenia, contrasenia) == 0 && strcmp(adminProvs[i].perfil_usuario, rol) == 0)
        {
            // Si hay coincidencia, actualiza las variables y sale del bucle
            encontrado = 0;
            *posVectorClienteActual = i; // Se actualiza la posición del vector del cliente
        }
    }

    // Devuelve 1 si no se encuentra coincidencia, 0 si se encuentra
    return encontrado;
}


// Función para comprobar las credenciales de un usuario
int comprobarUsuario(char *email, char *contrasenia, Cliente *clientes, int numClientes, int *posVectorClienteActual)
{
    // Variable para indicar si se ha encontrado una coincidencia de credenciales
    int encontrado = 1;

    // Recorre el arreglo de clientes
    for (int i = 0; i < numClientes && encontrado == 1; i++)
    {
        // Verifica si el correo electrónico y la contraseña coinciden
        if (strcmp(clientes[i].email, email) == 0 && strcmp(clientes[i].contrasenia, contrasenia) == 0)
        {
            // Si hay coincidencia, actualiza las variables y sale del bucle
            encontrado = 0;
            *posVectorClienteActual = 2; // Se asigna un valor fijo de 2, pero debería ser i para obtener la posición real del cliente
        }
    }

    // Devuelve 1 si no se encuentra coincidencia, 0 si se encuentra
    return encontrado;
}

// Función para comprobar las credenciales de un transportista
int comprobarTransportista(char *email, char *contrasenia, Transportista *transportistas, int numTransportistas, int *posVectorClienteActual)
{
    // Variable para indicar si se ha encontrado una coincidencia de credenciales
    int encontrado = 1;

    // Recorre el arreglo de transportistas
    for (int i = 0; i < numTransportistas && encontrado == 1; i++)
    {
        // Verifica si el correo electrónico y la contraseña coinciden
        if (strcmp(transportistas[i].email, email) == 0 && strcmp(transportistas[i].contrasenia, contrasenia) == 0)
        {
            // Si hay coincidencia, actualiza las variables y sale del bucle
            encontrado = 0;
            *posVectorClienteActual = i;
        }
    }

    // Devuelve 1 si no se encuentra coincidencia, 0 si se encuentra
    return encontrado;
}


// Función menuadmin:
// Permite a un administrador gestionar diversas operaciones del sistema.
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
        // Mostrar el nombre del administrador actual
        printf("--------------------------------------------------------\n");
        printf("             NOMBRE: %s                                 \n", (*adminProvs)[posVectorClienteActual].nombre);
        printf("--------------------------------------------------------\n");

        // Mostrar el menú de opciones disponibles para el administrador
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

        // Leer la opción seleccionada por el administrador
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        // Procesar la opción seleccionada
        switch (opcion)
        {
        case 1:
            // Mostrar y, opcionalmente, modificar el perfil del administrador
            mostrar_perfilprov((*adminProvs)[posVectorClienteActual]);
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
            // Acceder a la sección de gestión de clientes
            seccionClienteAdmin(clientes,numClientes);
            break;
        case 3:
            // Acceder a la sección de gestión de proveedores
            mostrarProveedoresAdmin(adminProvs,numAdminProvs);
            break;
        case 4:
            // Acceder a la sección de gestión de productos
            mostrarProductosAdmin(productos, numProductos,categorias,numCategorias,(*adminProvs)[posVectorClienteActual].id_empresa);
            break;
        case 5:
            // Acceder a la sección de gestión de categorías
            mostrarCategoriasAdmin(categorias,numCategorias,productos,numProductos);
            break;
        case 6:
            // Acceder a la sección de gestión de pedidos
            mostrarPedidosAdmin(productoPedidos,numProductoPedidos,transportistas,numTransportistas,(*adminProvs)[posVectorClienteActual].id_empresa,productos,numProductos,pedidos,numPedido);
            break;
        case 7:
            // Acceder a la sección de gestión de transportistas
            mostrarTransportista(transportistas,numTransportistas);
            break;
        case 8:
            // Acceder a la sección de gestión de descuentos
            mostrarDescuentosAdmin(descuentos,numDescuentos,descuentoClientes,numDescuentoClientes,clientes,numClientes);
            break;
        case 9:
            // Acceder a la sección de gestión de devoluciones
            mostrarDevolucionesAdmin(devoluciones,numDevoluciones,productoPedidos,numProductoPedidos);
            break;
        case 10:
            // Salir del sistema
            printf("Hasta pronto, ESIZON\n");
            salirprograma();
            break;
        default:
            printf("Opción no válida\n");
            break;
        }
    } while (opcion != 10); // Continuar mostrando el menú hasta que el administrador decida salir
}

// Función mostrarCategoriasAdmin:
// Permite a un administrador gestionar las categorías de productos del sistema.
void mostrarCategoriasAdmin(Categoria **categorias, int *numCategorias,Producto **productos, int *numProductos){
    int opcion;
    do {
        // Mostrar las opciones disponibles para el administrador
        printf("1- Alta categoria                                     \n");
        printf("2- Baja categoria                                     \n");
        printf("3- Buscar categoria                                   \n");
        printf("4- Listar categorias                                  \n");
        printf("5- Modificar categoria                                \n");
        printf("6- Listar productos por categoria                     \n");
        printf("7- Salir\n");

        // Leer la opción seleccionada por el administrador
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        // Procesar la opción seleccionada
        switch (opcion) {
            case 1:
                // Dar de alta una nueva categoría
                alta_categoria(categorias, numCategorias);
                break;
            case 2:
                // Dar de baja una categoría existente
                baja_categoria(categorias, numCategorias);
                break;
            case 3:
                // Buscar una categoría por su nombre
                buscarCategoria(categorias, numCategorias);
                break;
            case 4:
                // Listar todas las categorías registradas en el sistema
                listarCategorias(categorias, numCategorias);
                break;
            case 5:
                // Modificar una categoría existente
                modificarCategoria(categorias, numCategorias);
                break;
            case 6:
                // Listar todos los productos asociados a una categoría específica
                listarProductosPorCategoria(productos, numProductos, categorias, numCategorias);
                break;
        }
    } while (opcion != 7); // Continuar mostrando el menú hasta que el administrador seleccione la opción de salir
}

// Función mostrarProductosAdmin:
// Permite a un administrador gestionar los productos del sistema.
void mostrarProductosAdmin(Producto **productos, int *numProductos, Categoria ** categorias, int *numCategorias, char * id){

    int opcion;
    do {
        // Mostrar las opciones disponibles para el administrador
        printf("1- Alta producto\n");
        printf("2- Baja producto\n");
        printf("3- Buscar producto\n");
        printf("4- Listar productos\n");
        printf("5- Modificar producto\n");
        printf("6- Salir\n");
        printf("Ingrese una opcion: ");

        // Leer la opción seleccionada por el administrador
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        char producto_buscado[51]; // Variable para almacenar el nombre del producto buscado

        // Procesar la opción seleccionada
        switch (opcion) {
            case 1:
                // Dar de alta un nuevo producto
                alta_producto(productos, numProductos, id, categorias, numCategorias);
                break;
            case 2:
                // Dar de baja un producto existente
                printf("Introduzca la id del producto a dar de baja:\n");
                char prodBaja[9];
                fgets(prodBaja, 9, stdin);
                prodBaja[strcspn(prodBaja, "\n")] = '\0';
                baja_producto(productos, numProductos, prodBaja);
                break;
            case 3:
                // Buscar un producto por su nombre
                printf("\nIntroduce el nombre del producto que quieres buscar: ");
                fgets(producto_buscado, 51, stdin);
                producto_buscado[strcspn(producto_buscado, "\n")] = '\0';
                buscador_un_producto(productos, numProductos, producto_buscado);
                break;
            case 4:
                // Listar todos los productos registrados en el sistema
                listado_producto(productos, numProductos);
                break;
            case 5:
                // Modificar un producto existente
                modificar_producto(productos, numProductos, "-1"); // El tercer parámetro "-1" indica que se modificará un producto existente
                break;
        }
    } while (opcion != 6); // Continuar mostrando el menú hasta que el administrador seleccione la opción de salir
}


// Función mostrarPedidosAdmin:
// Permite a un administrador gestionar los pedidos del sistema.
void mostrarPedidosAdmin(ProductoPedido ** pedidos, int * tamPedidos, Transportista ** trans, int *nTrans,char *idProv, Producto **productos, int * nProductos, Pedido **ped, int * numPed){

    int opcion;
    do {
        // Mostrar las opciones disponibles para el administrador
        printf("1- Alta de pedido\n");
        printf("2- Baja de pedido\n");
        printf("3- Buscar pedido\n");
        printf("4- Listar pedidos\n");
        printf("5- Asignar transportista a pedido\n");
        printf("6- Asignar locker a pedido\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");

        // Leer la opción seleccionada por el administrador
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        float coste;
        int tamLista;
        Producto *cesta;
        char idPed[8]; // Variable para almacenar el ID del pedido

        // Procesar la opción seleccionada
        switch (opcion) {
            case 1:
                // Dar de alta un nuevo pedido
                cesta = agregar_a_cesta(productos, nProductos, &coste, &tamLista);

                printf("¿Donde desea que se entregue su pedido?\n");
                printf("1. Domicilio\n");
                printf("2. Locker\n");

                int opc;
                printf("Ingrese su opcion (1 o 2): ");
                scanf("%d", &opc);
                flushInputBuffer();
                char entrega[10];
                char idLocker[11];
                switch (opc) {
                    case 1:
                        strcpy(entrega, "domicilio");
                        strcpy(idLocker, " ");
                        break;
                    case 2:
                        strcpy(entrega, "locker");
                        printf("Ingrese la ID del locker donde desea enviar su pedido: ");
                        fgets(idLocker, 11, stdin);
                        idLocker[strcspn(idLocker, "\n")] = '\0';
                        break;
                }

                hacerPedido(&cesta, tamLista, productos, nProductos,
                            ped, numPed, pedidos, tamPedidos, idProv,
                            entrega, idLocker);
                break;
            case 2:
                // Dar de baja un pedido existente
                printf("Introduzca la id del pedido a dar de baja:\n");
                fgets(idPed, 8, stdin);
                idPed[strcspn(idPed, "\n")] = '\0';
                baja_prodPed(pedidos, tamPedidos, idPed);
                baja_pedido(ped, numPed, idPed);
                break;
            case 3:
                // Buscar un pedido por su ID
                printf("Introduzca la id del pedido a buscar:\n");
                fgets(idPed, 8, stdin);
                idPed[strcspn(idPed, "\n")] = '\0';
                buscarPedido(pedidos, tamPedidos, idPed);
                break;
            case 4:
                // Listar todos los pedidos registrados en el sistema
                listado_pedido(pedidos, tamPedidos);
                break;
            case 5:
                // Asignar un transportista a un pedido
                asignarProductoPedidoProv(pedidos, tamPedidos, trans, nTrans, idProv, productos, nProductos);
                break;
            case 6:
                // Asignar un locker a un pedido
                asignarLocker(pedidos, ped, numPed, tamPedidos);
                break;
        }
    } while (opcion != 7); // Continuar mostrando el menú hasta que el administrador seleccione la opción de salir
}


// Función mostrarProveedoresAdmin:
// Permite a un administrador gestionar los proveedores del sistema.
void mostrarProveedoresAdmin(AdminProv **proveedores, int* numProveedores) {
    int opcion;
    do {
        // Mostrar las opciones disponibles para el administrador
        printf("1- Alta proveedor\n");
        printf("2- Baja proveedor\n");
        printf("3- Buscar proveedor\n");
        printf("4- Listar proveedores\n");
        printf("5- Modificar proveedor\n");
        printf("6- Volver al menu anterior\n");
        printf("Seleccione una opcion: ");

        // Leer la opción seleccionada por el administrador
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        char idP[5]; // Variable para almacenar el ID del proveedor

        // Procesar la opción seleccionada
        switch (opcion) {
            case 1:
                // Dar de alta un nuevo proveedor
                altaProveedor(proveedores, numProveedores);
                break;
            case 2:
                // Dar de baja un proveedor existente
                printf("Ingrese la ID: ");
                fgets(idP, 5, stdin);
                idP[strcspn(idP, "\n")] = '\0';
                bajaProveedor(proveedores, numProveedores, idP);
                break;
            case 3:
                // Buscar un proveedor por su nombre
                buscarProveedor(proveedores, numProveedores);
                break;
            case 4:
                // Listar todos los proveedores registrados en el sistema
                listarProveedores(proveedores, numProveedores);
                break;
            case 5:
                // Modificar los detalles de un proveedor existente
                modificarProveedor(proveedores, numProveedores);
                break;
        }
    } while (opcion != 6); // Continuar mostrando el menú hasta que el administrador seleccione la opción de volver al menú anterior
}


// Función seccionClienteAdmin:
// Permite a un administrador gestionar los clientes del sistema.
void seccionClienteAdmin(Cliente **clientes, int *numClientes) {
    int opcionClientes;

    // Bucle para mostrar el menú y procesar la selección del administrador
    do {
        // Mostrar las opciones disponibles para el administrador
        printf("1- Alta de cliente\n");
        printf("2- Baja de cliente\n");
        printf("3- Busqueda de cliente\n");
        printf("4- Listado de clientes\n");
        printf("5- Modificacion de cliente\n");
        printf("6- Salir\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcionClientes);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        // Procesar la opción seleccionada
        switch (opcionClientes) {
            case 1:
                // Dar de alta un nuevo cliente
                altaCliente(clientes, numClientes);
                break;
            case 2:
                // Dar de baja un cliente existente
                bajaCliente(clientes, numClientes);
                break;
            case 3:
                // Buscar un cliente por su ID
                buscarCliente(clientes, numClientes);
                break;
            case 4:
                // Listar todos los clientes registrados en el sistema
                listarClientes(clientes, numClientes);
                break;
            case 5:
                // Modificar los detalles de un cliente existente
                modificarCliente(clientes, numClientes);
                break;
        }
    } while (opcionClientes != 6); // Continuar mostrando el menú hasta que el administrador seleccione la opción de salir
}

// Función mostrarDescuentosAdmin:
// Permite a un administrador gestionar los descuentos disponibles en el sistema.
void mostrarDescuentosAdmin(Descuento **descuentos, int *numDescuentos, DescuentoCliente **descuentoClientes, int *numDescuentoClientes, Cliente **clientes, int numClientes) {
    int opcion;
    do {
        // Mostrar las opciones disponibles para el administrador
        printf("1- Alta descuento\n");
        printf("2- Baja descuento\n");
        printf("3- Listado de descuentos\n"); // Se agregó un '\n' al final de la cadena para separar las opciones
        printf("4- Modificar descuentos\n"); // Se agregó un '\n' al final de la cadena para separar las opciones
        printf("5- Asignar descuento\n"); // Se agregó un '\n' al final de la cadena para separar las opciones
        printf("6- Salir\n");
        printf("Seleccione una opcion: ");

        // Leer la opción seleccionada por el administrador
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        char id[11]; // Variable para almacenar el ID del descuento

        // Procesar la opción seleccionada
        switch (opcion) {
            case 1:
                // Dar de alta un nuevo descuento y asignarlo automáticamente a los clientes
                alta_descuentos(descuentos, numDescuentos);
                rellenar_descuentocliente(descuentos, clientes, descuentoClientes, numDescuentos, numClientes, numDescuentoClientes);
                anadir_fecha_caducidad((*descuentoClientes)[(*numDescuentoClientes) - 1].fecha_caducidad, *numDescuentoClientes);
                break;
            case 2:
                // Dar de baja un descuento y eliminarlo de los clientes que lo tenían asignado
                printf("Introduce el ID del descuento a dar de baja: ");
                fgets(id, 11, stdin);
                id[strcspn(id, "\n")] = '\0';
                flushInputBuffer();
                baja_descuentos(descuentos, numDescuentos, id);
                baja_descuento_clientes(descuentoClientes, numDescuentoClientes, numDescuentos, numClientes, id);
                break;
            case 3:
                // Mostrar todos los descuentos disponibles en el sistema
                listar_descuentos(descuentos, numDescuentos);
                break;
            case 4:
                // Modificar los detalles de un descuento existente
                modificar_descuento(descuentos, numDescuentos);
                break;
            case 5:
                // Asignar un descuento específico a un cliente determinado
                asignar_descuento(descuentoClientes, numDescuentoClientes);
                break;
        }
    } while (opcion != 6); // Continuar mostrando el menú hasta que el administrador seleccione la opción de salir
}


// Función menuusuario:
// Permite a un usuario con rol de cliente interactuar con el sistema.
void menuusuario(int rol, int posVectorClienteActual, Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                      Categoria **categorias, int *numCategorias, CompartimentoLocker **compartimentoLockers, int *numCompartimentoLockers,
                      DescuentoCliente **descuentoClientes, int *numDescuentoClientes, Descuento **descuentos, int *numDescuentos,
                      Devolucion **devoluciones, int *numDevoluciones, Locker **lockers, int *numLockers, Pedido **pedidos, int *numPedido,
                      Producto **productos, int *numProductos, ProductoPedido **productoPedidos, int *numProductoPedidos,
                      Transportista **transportistas, int *numTransportistas)
{
    int opcion;
    // Bucle para mostrar el menú y procesar la selección del cliente
    do
    {
        // Mostrar el nombre del cliente y el menú de opciones disponibles
        printf("--------------------------------------------------------\n");
        printf("             NOMBRE: %s \n", (*clientes)[posVectorClienteActual].nomb_cliente);
        printf("--------------------------------------------------------\n");
        printf("|1-Perfil                                              |\n");
        printf("|2-Productos                                           |\n");
        printf("|3-Descuentos                                          |\n");
        printf("|4-Pedidos                                             |\n");
        printf("|5-Devoluciones                                        |\n");
        printf("|6-Salir del sistema                                   |\n");
        printf("--------------------------------------------------------\n");

        // Leer la opción seleccionada por el cliente
        scanf("%d", &opcion);
        flushInputBufferr(); // Limpiar el búfer de entrada para evitar problemas con scanf

        // Procesar la opción seleccionada
        switch (opcion)
        {
        case 1:
            // Mostrar el perfil del cliente y, opcionalmente, permitir su modificación
            mostrar_cliente((*clientes)[posVectorClienteActual]);
            printf("¿Quieres modificarlo?:\n");
            printf("1- Si\n");
            printf("2- No\n");
            int opcion;
            scanf("%d",&opcion);
            flushInputBuffer();
            if(opcion==1)
                cambiar_perfil_cliente(&clientes[posVectorClienteActual]);
            break;
        case 2:
            // Mostrar los productos disponibles para el cliente
            mostrarProductosCliente(productos, numProductos);
            break;
        case 3:
            // Mostrar los descuentos disponibles
            mostrar_descuentos_cliente((*clientes)[posVectorClienteActual].id_cliente,descuentos,descuentoClientes,numDescuentos,numDescuentoClientes);
            break;
        case 4:
            // Acceder a la sección de gestión de pedidos del cliente
            mostrarPedidosClientes(productoPedidos, numProductoPedidos, productos, numProductos, pedidos, numPedido, clientes, posVectorClienteActual,descuentos,descuentoClientes,numDescuentos,numDescuentoClientes);
            break;
        case 5:
            // Acceder a la sección de gestión de devoluciones del cliente
            mostrarDevoluciones(devoluciones, numDevoluciones, clientes, posVectorClienteActual, pedidos, numPedido);
            break;
        case 6:
            // Salir del sistema
            printf("Hasta pronto, ESIZON\n");
            salirprograma();
            break;
        default:
            // Opción no válida
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 6); // Continuar mostrando el menú hasta que el cliente seleccione la opción de salir
}


// Función mostrarDevoluciones:
// Permite a un cliente interactuar con el sistema para gestionar devoluciones.
void mostrarDevoluciones(Devolucion **devoluciones, int *numDevo, Cliente **clientes, int posVectorClienteActual, Pedido **pedidos, int *numPedidos){
    int opcion;
    // Bucle para mostrar el menú y procesar la selección del cliente
    do {
        // Mostrar las opciones disponibles para el cliente
        printf("1- Alta devolucion\n");
        printf("2- Consultar devolucion\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");

        // Leer la opción seleccionada por el cliente
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        // Procesar la opción seleccionada
        switch (opcion) {
            case 1:
                // Realizar una nueva solicitud de devolución
                alta_devolucion_cliente(devoluciones, numDevo, (*clientes)[posVectorClienteActual], pedidos, *numPedidos);
                break;
            case 2:
                // Consultar el estado de una devolución utilizando su ID
                printf("Introduzca la id de la devolucion:\n");
                char idD[8];
                fgets(idD, 8, stdin);
                idD[strcspn(idD, "\n")] = '\0'; // Eliminar el salto de línea del final
                buscar_devolucion(devoluciones, numDevo, idD);
                break;
        }
    } while (opcion != 3); // Continuar mostrando el menú hasta que el cliente seleccione la opción de salir
}


// Función mostrarPedidosClientes:
// Permite a un cliente interactuar con el sistema para gestionar sus pedidos.
void mostrarPedidosClientes(ProductoPedido ** pedidos, int * tamPedidos, Producto **productos, int * nProductos, Pedido **ped,
                             int * numPed, Cliente **clientes, int posVectorClienteActual,Descuento **descuentos, DescuentoCliente **descuentosClientes, int *cantdadDesc, int*cantidadDescCli){

    int opcion;
    // Bucle para mostrar el menú y procesar la selección del cliente
    do {
        // Mostrar las opciones disponibles para el cliente
        printf("1- Alta de pedido\n");
        printf("2- Buscar pedido\n");
        printf("3- Listar pedidos\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");

        // Leer la opción seleccionada por el cliente
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        float coste;
        int tamLista;
        Producto *cesta;
        char entrega[10];
        char idLocker[11];
        // Procesar la opción seleccionada
        switch(opcion)
        {
            case 1:
                // Agregar un nuevo pedido al sistema
                cesta = agregar_a_cesta(productos,nProductos,&coste,&tamLista);

                aplicar_descuento(&coste,*descuentos,*descuentosClientes,(*clientes)[posVectorClienteActual].id_cliente,cesta,*cantdadDesc,*cantidadDescCli,nProductos);

                // Verificar si el cliente tiene suficiente saldo en su cartera
                if(coste > (*clientes)[posVectorClienteActual].cartera){
                    printf("Saldo insuficiente");
                }else{
                    // Solicitar al cliente que elija la ubicación de entrega del pedido
                    printf("¿Donde desea que se entregue su pedido?\n");
                    printf("1. Domicilio\n");
                    printf("2. Locker\n");

                    int opc;
                    printf("Ingrese su opcion (1 o 2): ");
                    scanf("%d", &opc);
                    flushInputBuffer();

                    // Según la opción del cliente, establecer la ubicación de entrega y la ID del locker (si es necesario)
                    switch (opc) {
                        case 1:
                            strcpy(entrega,"domicilio");
                            strcpy(idLocker," ");
                            break;
                        case 2:
                            strcpy(entrega,"locker");
                            printf("Ingrese la ID del locker donde desea enviar su pedido: ");
                            fgets(idLocker, 11, stdin);
                            idLocker[strcspn(idLocker, "\n")] = '\0';
                            break;
                    }

                    // Realizar el pedido y actualizar el saldo de la cartera del cliente
                    hacerPedido(&cesta, tamLista, productos, nProductos,
                     ped, numPed, pedidos, tamPedidos, (*clientes)[posVectorClienteActual].id_cliente,
                      entrega, idLocker);
                    (*clientes)[posVectorClienteActual].cartera -=coste;
                }
                break;
            case 2:
                // Buscar un pedido por su ID
                printf("Introduzca la id del pedido a buscar:\n");
                char idPed[8];
                fgets(idPed, 8, stdin);
                idPed[strcspn(idPed, "\n")] = '\0';
                buscar_pedido_cliente(ped, numPed, (*clientes)[posVectorClienteActual].id_cliente, idPed);
                break;
            case 3:
                // Listar todos los pedidos del cliente
                listado_pedido_cliente(ped, numPed, (*clientes)[posVectorClienteActual].id_cliente);
                break;
        }
    } while (opcion != 4); // Continuar mostrando el menú hasta que el cliente seleccione la opción de salir
}


// Función mostrarProductosCliente:
// Permite a un cliente buscar y listar productos disponibles en el sistema.
void mostrarProductosCliente(Producto **productos, int *numProductos){

    int opcion;
    // Bucle para mostrar el menú y procesar la selección del cliente
    do {

        // Mostrar las opciones disponibles para el cliente
        printf("1- Buscar producto\n");
        printf("2- Listar productos\n");
        printf("3- Salir\n");
        printf("Ingrese una opcion: ");

        // Leer la opción seleccionada por el cliente
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        char producto_buscado[51];
        // Procesar la opción seleccionada
        switch (opcion) {

            case 1:
                // Buscar un producto por su nombre
                printf("\nIntroduce el nombre del producto que quieres buscar: ");
                fgets(producto_buscado, 51, stdin);
                producto_buscado[strcspn(producto_buscado, "\n")] = '\0'; // Eliminar el salto de línea del final
                buscador_un_producto(productos, numProductos, producto_buscado);
                break;
            case 2:
                // Listar todos los productos disponibles
                listado_producto(productos, numProductos);
                break;

        }
    } while (opcion != 3); // Continuar mostrando el menú hasta que el cliente seleccione la opción de salir
}


// Función menuproveedor:
// Permite a un proveedor interactuar con el sistema, accediendo a diferentes funcionalidades.
void menuproveedor(int rol, int posVectorClienteActual, Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                   Transportista **transportistas, int *numTransportistas, Producto **productos, int *numProductos, Categoria **categorias, int *numCategorias, ProductoPedido **pedidos, int *tamanioPed)
{
    int opcion;
    // Bucle para mostrar el menú y procesar la selección del proveedor
    do
    {
        // Mostrar el nombre del proveedor y el menú de opciones disponibles
        printf("--------------------------------------------------------\n");
        printf("             NOMBRE: %s                                 \n", (*adminProvs)[posVectorClienteActual].nombre);
        printf("--------------------------------------------------------\n");
        printf("|1-Perfil                                              |\n");
        printf("|2-Productos                                           |\n");
        printf("|3-Pedidos                                             |\n");
        printf("|4-Salir del sistema                                   |\n");
        printf("--------------------------------------------------------\n");
        // Leer la opción seleccionada por el proveedor
        scanf("%d", &opcion);

        // Procesar la opción seleccionada
        switch (opcion)
        {
        case 1:
            // Ver y, opcionalmente, modificar el perfil del proveedor
            mostrar_perfilprov((*adminProvs)[posVectorClienteActual]);
            flushInputBuffer(); // Limpiar el búfer de entrada antes de solicitar entrada adicional
            printf("¿Quieres modificarlo?:\n");
            printf("1- Si\n");
            printf("2- No\n");
            int opcion;
            scanf("%d", &opcion);
            flushInputBuffer(); // Limpiar el búfer de entrada antes de solicitar entrada adicional
            if (opcion == 1)
                modificar_perfilprov(&adminProvs[posVectorClienteActual]);
            break;
        case 2:
            // Acceder a la sección de gestión de productos del proveedor
            seccionProductosProv(productos, numProductos, categorias, numCategorias, (*adminProvs)[posVectorClienteActual].id_empresa);
            break;
        case 3:
            // Acceder a la sección de gestión de pedidos del proveedor
            seccionPedidosProv(pedidos, tamanioPed, (*adminProvs)[posVectorClienteActual].id_empresa, productos, numProductos, transportistas, numTransportistas);
            break;
        case 4:
            // Salir del sistema
            printf("Hasta pronto, ESIZON\n");
            salirprograma();
            break;
        default:
            // Opción no válida
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 4); // Continuar mostrando el menú hasta que el proveedor seleccione la opción de salir del sistema
}

// Función menutransportista:
// Permite a un transportista interactuar con el sistema, accediendo a diferentes funcionalidades.
void menutransportista(int rol, int posVectorClienteActual, Locker **lockers, int *numLockers, Cliente **clientes, int *numClientes, AdminProv **adminProvs, int *numAdminProvs,
                       Transportista **transportistas, int *numTransportistas, Producto **productos, int *numProductos, Categoria **categorias, int *numCategorias, int *numProductoPedidos, ProductoPedido **productoPedidos, CompartimentoLocker **compartimentoLockers, int *numCompartimentoLockers)
{
    int opcion;
    char id_t[8]; // Incrementamos el tamaño para incluir el carácter nulo

    do
    {
        // Mostrar el nombre del transportista y el menú de opciones disponibles
        printf("--------------------------------------------------------\n");
        printf("             NOMBRE: %s                                 \n", (*transportistas)[posVectorClienteActual].nombre);
        printf("--------------------------------------------------------\n");
        printf("|1-Perfil                                              |\n");
        printf("|2-Repartos                                            |\n");
        printf("|3-Retornos                                            |\n");
        printf("|4-Salir del sistema                                   |\n");
        printf("--------------------------------------------------------\n");

        // Leer la opción seleccionada por el transportista
        scanf("%d", &opcion);
        getchar(); // Consumir el carácter de nueva línea residual del búfer de entrada

        // Procesar la opción seleccionada por el transportista
        switch (opcion)
        {
        case 1:
            // Ver perfil del transportista
            perfil_t(&(*transportistas)[posVectorClienteActual]);
            break;
        case 2:
            // Realizar repartos
            reparto(productoPedidos, numProductoPedidos, (*transportistas)[posVectorClienteActual].id_transp);
            // Comprobar si hay pedidos en reparto para este transportista
            enReparto(productoPedidos, numProductoPedidos, compartimentoLockers, numCompartimentoLockers, id_t);
            break;
        case 3:
            // Procesar retornos de productos
            retornoProducto(lockers, productos, numProductos, numLockers, (*lockers)[posVectorClienteActual].localidad);
            break;
        case 4:
            // Salir del sistema
            printf("Hasta pronto, ESIZON\n");
            salirprograma();
            break;
        default:
            // Opción no válida
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 4); // Continuar mostrando el menú hasta que el transportista seleccione la opción de salir
}



// Función seccionProductosProv:
// Permite al proveedor gestionar sus productos.
void seccionProductosProv(Producto **productos, int *numProductos, Categoria **categorias, int *numCategorias, char *id)
{
    // Mostrar los productos del proveedor
    printf("Tus productos: \n");

    // Mostrar opciones disponibles para el proveedor
    printf("¿Que deseas hacer?\n");
    printf("1- Listar mis productos\n");
    printf("2- Alta producto\n");
    printf("3- Baja producto\n");
    printf("4- Modificar producto\n");
    printf("5- Buscar producto\n");
    printf("6- Salir\n");

    int opcion;
    // Leer la opción seleccionada por el proveedor
    scanf("%d", &opcion);
    flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

    // Procesar la opción seleccionada
    switch (opcion)
    {
    case 1:
        // Listar los productos del proveedor
        listado_producto_prooved(productos, *numProductos, id);
        break;
    case 2:
        // Agregar un nuevo producto
        alta_producto(productos, numProductos, id, categorias, numCategorias);
        break;
    case 3:
        // Dar de baja un producto
        printf("Introduzca la id del producto a dar de baja:\n");
        char prodBaja[9];
        fgets(prodBaja, 9, stdin);
        prodBaja[strcspn(prodBaja, "\n")] = '\0';

        // Verificar si el producto pertenece al proveedor
        int recibidor = productoEsDeProveedor(productos, numProductos, id, prodBaja);
        if (recibidor == 1)
        {
            baja_producto(productos, numProductos, prodBaja); // Si el producto es del proveedor, dar de baja
        }
        else
        {
            printf("Ese producto no es suyo\n"); // Si el producto no es del proveedor, mostrar un mensaje de error
        }
        break;
    case 4:
        // Modificar un producto
        modificar_producto(productos, numProductos, id);
        break;
    case 5:
        // Buscar un producto por su nombre
        printf("\nIntroduce el nombre del producto que quieres buscar: ");
        char producto_buscado[51];
        fgets(producto_buscado, 51, stdin);
        producto_buscado[strcspn(producto_buscado, "\n")] = '\0';

        buscador_un_producto(productos, numProductos, producto_buscado);
        break;
    }
}


// Mediante esta opción el administrador podrá acceder a la información de los pedidos dados de alta en la plataforma.
// Solo puede acceder: Administrador y cliente y proveedores
void seccionPedidosProv(ProductoPedido **pedidos, int* tamanioPed, char *idProv, Producto** productos, int *nProductos, Transportista** trans, int * nTrans)
{
    // Mostrar las opciones disponibles para el proveedor
    printf("1- Listar pedidos pendientes\n");
    printf("2- Asignar transportista a pedido\n");

    int opcion;
    // Leer la opción seleccionada por el proveedor
    scanf("%d", &opcion);
    flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

    // Procesar la opción seleccionada
    switch (opcion)
    {
    case 1:
        // Listar los pedidos pendientes relacionados con los productos del proveedor
        listado_pedido_pendiente(pedidos, tamanioPed, idProv, productos, nProductos);
        break;

    case 2:
        // Asignar un transportista a un pedido relacionado con los productos del proveedor
        asignarProductoPedidoProv(pedidos, tamanioPed, trans, nTrans, idProv, productos, nProductos);
        break;
    }
}

// Mediante esta opción el administrador podrá acceder a la información de todos los transportistas dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de transportistas.
// Solo puede acceder: Administrador
void mostrarTransportista(Transportista **transportista, int *nTrans)
{
    int opcion;

    // Bucle para mostrar el menú y procesar la selección del usuario
    do {
        printf("1- Listar transportistas\n");
        printf("2- Agregar transportista\n");
        printf("3- Buscar transportista por ID\n");
        printf("4- Modificar transportista por ID\n");
        printf("5- Dar de baja transportista por ID\n");
        printf("6- Salir\n");
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        // Procesar la opción seleccionada por el usuario
        switch (opcion) {
            case 1:
                // Listar todos los transportistas
                listar_transportistas(transportista, nTrans);
                break;
            case 2:
                // Agregar un nuevo transportista
                agregar_transportista(transportista, nTrans);
                break;
            case 3:
                // Buscar un transportista por su ID
                buscar_transportista(transportista, nTrans);
                break;
            case 4:
                // Modificar un transportista por su ID
                modificar_transportista(transportista, nTrans);
                break;
            case 5:
                // Dar de baja un transportista por su ID
                dar_de_baja_transportista(transportista, nTrans);
                break;
        }
    } while (opcion != 6); // Continuar mostrando el menú hasta que el usuario seleccione la opción "Salir"
}


// Función mostrarDevolucionesAdmin:
// Permite a un administrador gestionar las devoluciones realizadas.
void mostrarDevolucionesAdmin(Devolucion** devoluciones, int *num_devoluciones, ProductoPedido **productoPedidos, int *prodPeds) {
    int opcion;

    // Bucle para mostrar el menú y procesar la selección del usuario
    do {
        printf("1- Listar devoluciones\n");
        printf("2- Alta devolucion\n");
        printf("3- Buscar devolucion por ID\n");
        printf("4- Devoluciones pendiente de confirmacion\n");
        printf("5- Dar de baja devolucion por ID\n");
        printf("6- Salir\n");
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf

        // Procesar la opción seleccionada por el usuario
        switch (opcion) {
            case 1:
                // Listar todas las devoluciones
                listar_devoluciones(devoluciones, num_devoluciones);
                break;
            case 2:
                // Dar de alta una nueva devolución
                alta_devolucion_admin(devoluciones, num_devoluciones, productoPedidos, prodPeds);
                break;
            case 3:
                // Buscar una devolución por su ID
                printf("Introduzca la id de la devolucion buscada:\n");
                char idD[8];
                fgets(idD, 8, stdin);
                idD[strcspn(idD, "\n")] = '\0'; // Eliminar el salto de línea del final
                buscar_devolucion(devoluciones, num_devoluciones, idD);// Buscar una devolución por su ID
                break;
            case 4:
                // Modificar y consultar devoluciones pendientes de confirmación
                modifYConsultarDevPedAdmin(devoluciones, num_devoluciones);
                break;
            case 5:
                // Dar de baja una devolución por su ID
                printf("Introduzca la id de la devolucion a dar de baja:\n");
                fgets(idD, 8, stdin);
                idD[strcspn(idD, "\n")] = '\0'; // Eliminar el salto de línea del final
                baja_devolucion(devoluciones, num_devoluciones, idD);// La funcion da de baja esa id
                break;
        }
    } while (opcion != 6); // Continuar mostrando el menú hasta que el usuario seleccione la opción "Salir"
}


// Esta opción permitirá al transportista consultar la lista de productos que tiene asignados para su entrega así como la fecha prevista para la misma, lo que le permite realizar su ruta de reparto.
// Solo puede acceder: transportista
void enReparto(ProductoPedido **pedidos, int *num_pedidos, CompartimentoLocker **compartimiento, int *tamanio_compartimento, char *id_t) {
    // Verificar si se encontraron pedidos asignados al transportista
    int encontrado = 0;
    int i;
    for (i = 0; i < *num_pedidos; i++) {
        // Comprueba si el pedido actual está asignado al transportista y tiene estado "enReparto"
        if (strcmp((*pedidos)[i].id_transp, id_t) == 0 && strcmp((*pedidos)[i].estado_pedido, "enReparto") == 0) {
            encontrado = 1;
            break; // Se encontró al menos un pedido, así que se puede salir del bucle
        }
    }

    // Si se encontraron pedidos, preguntar si se desea realizar una entrega
    if (encontrado == 1) {
        printf("¿Quieres realizar alguna entrega?\n1-Si\n2-No\n");
        int respuesta_enreparto;
        scanf("%d", &respuesta_enreparto);
        flushInputBuffer(); // Limpiar el búfer de entrada para evitar problemas con scanf
        switch (respuesta_enreparto) {
            case 1:
                // Si el usuario elige realizar una entrega, llama a la función entrega, que se encarga de realizar la propia entrega
                entrega(pedidos, compartimiento, num_pedidos, tamanio_compartimento, id_t);
                break;
            case 2:
                // Si el usuario elige no realizar una entrega, simplemente sale del switch
                break;
            default:
                // Si el usuario ingresa una opción inválida, muestra un mensaje de error
                printf("Opcion no valida.\n");
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
    retornarProductosNoRecogidos(productos, numProductos, lockers, numLockers, loca); // esta funcion sireve para devolver los productos los cuales no hayan sido recogidos
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
