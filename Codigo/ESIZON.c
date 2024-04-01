
#include "ESIZON.h"

Cliente *clientes;
int numClientes;

AdminProv *adminProvs;
int numAdminProvs;

Producto *productos;
int numProductos;

Categoria *categorias;
int numCategorias;

Descuento *descuentos;
int numDescuentos;

DescuentoCliente *descuentoClientes;
int numDescuentoClientes;

Locker *lockers;
int numLockers;

CompartimentoLocker *compartimentoLockers;
int numCompartimentoLockers;

Pedido *pedidos;
int numPedido;

ProductoPedido *productoPedidos;
int numProductoPedidos;

Transportista *transportistas;
int numTransportistas;

Devolucion *devoluciones;
int numDevoluciones;

int rol;
// 1-Administrador
// 2-Usuario
// 3-Proveedor
// 4-Transportista

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
    } while (iniciarSesion()!=0);

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
        case 1: encontrado = comprobarAdminoProv(correo,contrasenia,"administrador"); break;
        case 2: encontrado = comprobarUsuario(correo,contrasenia);break;
        case 3: encontrado = comprobarAdminoProv(correo,contrasenia,"proveedor");break;
        case 4: encontrado = comprobarTransportista(correo,contrasenia);break;
        }
        
        //Mensaje de error si no accede
        if(encontrado == 1){
            printf("Algún dato es incorrecto\n");
        }
    }

    
    return encontrado;
}

int comprobarAdminoProv(char *email, char *contrasenia,char *rol){
    int encontrado=1;
    for(int i=0;i<numAdminProvs&&encontrado==1;i++){
        if(strcmp(adminProvs[i].email,email)==0&&strcmp(adminProvs[i].contrasenia,contrasenia)==0
        &&strcmp(adminProvs[i].perfil_usuario,rol)==0){
            encontrado = 0;
        }
    }

    return encontrado;

}

int comprobarUsuario(char *email, char *contrasenia){
    int encontrado=1;
    for(int i=0;i<numClientes&&encontrado==1;i++){
        if(strcmp(clientes[i].email,email)==0&&strcmp(clientes[i].contrasenia,contrasenia)==0){
            encontrado = 0;
        }
    }

    return encontrado;

}

int comprobarTransportista(char *email, char *contrasenia){
    int encontrado=1;
    for(int i=0;i<numTransportistas&&encontrado==1;i++){
        if(strcmp(transportistas[i].email,email)==0&&strcmp(transportistas[i].contrasenia,contrasenia)==0){
            encontrado = 0;
        }
    }

    return encontrado;

}

