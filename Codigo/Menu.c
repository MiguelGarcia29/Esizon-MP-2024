#include <stdio.h>

// Prototipos de las funciones
void menuadmin();
void menuusuario();
void menuproveedor();
void menutransportista();
void perfil();
void clientes();
void proveedores();
void productos();
void categorias();
void pedidos();
void transportista();
void descuentos();
void devoluciones();
void reparto();
void retorno();
void salir();

int rol = 0;

//1-Administrador
//2-Usuario
//3-Proveedor
//4-Transportista

int main() {
    printf(" ########  #######   ######     ##########  ##########  ###      ##\n");
    printf(" ##       ##           ##              #    ##      ##  ## #     ##\n");
    printf(" ##       ##           ##             #     ##      ##  ##  #    ##\n");
    printf(" #####     ######      ##         #####     ##      ##  ##   #   ##\n");
    printf(" ##              ##    ##         #         ##      ##  ##    #  ##\n");
    printf(" ##              ##    ##        #          ##      ##  ##     # ##\n");
    printf(" #######    #####    ######     ########    ##########  ##      ###\n");
    printf("\n");
    
    
    switch (rol) {
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

    return 0;
}

//Rol de administrador
//Solo puede acceder: Administrador
void menuadmin() {
    int opcion;
    do {
        printf("Dime que quieres realizar como administrador: \n");
        printf("1-Perfil\n2-Clientes\n3-Proveedores\n4-Productos\n5-Categorías\n");
        printf("6-Pedidos\n7-Transportista\n8-Descuentos\n9-Devoluciones\n10-Salir del sistema\n");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                perfil();
                break;
            case 2:
                clientes();
                break;
            case 3:
                proveedores();
                break;
            case 4:
                productos();
                break;
            case 5:
                categorias();
                break;
            case 6:
                pedidos();
                break;
            case 7:
                transportista();
                break;
            case 8:
                descuentos();
                break;
            case 9:
                devoluciones();
                break;
            case 10:
                printf("Hasta pronto, ESIZON\n");
                salir();
                break;
            default:
                printf("Opción no válida\n");
                break;
        }
    } while (opcion != 10);
}

//Rol de cliente
//Solo puede acceder: cliente y administrador
void menuusuario() {
    int opcion;
    do {
        printf("Dime que quieres realizar como usuario: \n");
        printf("1-Perfil\n2-Productos\n3-Descuentos\n4-Pedidos\n5-Devoluciones\n6-Salir del sistema\n");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                perfil();
                break;
            case 2:
                productos();
                break;
            case 3:
                descuentos();
                break;
            case 4:
                pedidos();
                break;
            case 5:
                devoluciones();
                break;
            case 6:
                printf("Hasta pronto, ESIZON\n");
                salir();
                break;
            default:
                printf("Opción no válida\n");
                break;
        }
    } while (opcion != 6);
}

void menuproveedor() {
    int opcion;
    do {
        printf("Dime que quieres realizar como proveedor: \n");
        printf("1-Perfil\n2-Productos\n3-Pedidos\n4-Salir del sistema\n");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                perfil();
                break;
            case 2:
                productos();
                break;
            case 3:
                pedidos();
                break;
            case 4:
                printf("Hasta pronto, ESIZON\n");
                salir();
                break;
            default:
                printf("Opción no válida\n");
                break;
        }
    } while (opcion != 4);
}

void menutransportista() {
   int opcion;
    do {
        printf("Dime que quieres realizar como transportista: \n");
        printf("1-Perfil\n2-Repartos\n3-Retornos\n4-Salir del sistema\n");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                perfil();
                break;
            case 2:
                reparto();
                break;
            case 3:
                retorno();
                break;
            case 4:
                printf("Hasta pronto, ESIZON\n");
                salir();
                break;
            default:
                printf("Opción no válida\n");
                break;
        }
    } while (opcion != 4);
}


//Esta opción permitirá a un usuario administrador consultar los datos de su perfil y modificarlos.
//Solo puede acceder: Administrador y clientes y transportista y proveedores
void perfil() {
    // Implementación de la función perfil
}

//Mediante esta opción el administrador podrá acceder a la información de los clientes dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de clientes.
//Solo puede acceder: Administrador
void clientes() {
    // Implementación de la función clientes
}

//Mediante esta opción el administrador podrá acceder a la información de los proveedores, deproductos externos, dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de proveedores.
//Solo puede acceder: Administrador
void proveedores() {
    // Implementación de la función proveedores
}

//Mediante esta opción el administrador podrá acceder a la información de los productos dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de productos.
//Solo puede acceder: Administrador y cliente y proveedor
void productos() {
    // Implementación de la función productos
}

//Mediante esta opción el administrador podrá acceder a la información de las categorías dadas de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de categorías. Además podrá generar listados de productos por categoría.
//Solo puede acceder: Administrador
void categorias() {
    // Implementación de la función categorias
}

//Mediante esta opción el administrador podrá acceder a la información de los pedidos dados de alta en la plataforma.
//Solo puede acceder: Administrador y cliente y proveedores
void pedidos() {
    // Implementación de la función pedidos
}

//Mediante esta opción el administrador podrá acceder a la información de todos los transportistas dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de transportistas.
//Solo puede acceder: Administrador
void transportista() {
    // Implementación de la función transportista
}

//Mediante esta opción el administrador podrá acceder a la información de todos los códigos promocionales y/o cheques regalo dados de alta en la plataforma.
//Solo puede acceder: Administrador y cliente
void descuentos() {
    // Implementación de la función descuentos
}

//Mediante esta opción el administrador podrá acceder a la información de todas las devoluciones de productos.
//Solo puede acceder: Administrador y cliente
void devoluciones() {
    // Implementación de la función devoluciones
}

//Esta opción permitirá al transportista consultar la lista de productos que tiene asignados para su entrega así como la fecha prevista para la misma, lo que le permite realizar su ruta de reparto.
//Solo puede acceder: transportista
void reparto(){
    
}

//El sistema facilitará al transportista la tarea de retornar a origen todos los productos que nohayan sido recogidos de los lockers en el plazo determinado, permitiéndole consultar todos los lockers por localidad y mostrando sus pedidos. En el momento de la recogida de los productos
//para su retorno, el sistema debe actualizar automáticamente el número de compartimentos
//ocupados y eliminar el código locker asociado al producto. Así como el estado de los productos
//y el stock de los mismos para que quede reflejada la operación
//Solo puede acceder: transportista
void retorno()
{
    
}

//Esta opción permitirá al transportista consultar la lista de productos que tiene asignados para su entrega así como la fecha prevista para la misma, lo que le permite realizar su ruta de reparto.
//Solo puede acceder: Administrador y clientes y transportista y proveedor
void salir()
{
    
}

