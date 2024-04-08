#include "Productos_pedidos.h"
#include <time.h>
#include <string.h>
#include "Productos.h"
#include "Categoria.h"
/*Permitir al cliente realizar pedidos controlando los códigos promocionales y/o
cheques regalo que pueda utilizar en función de si están activos o no y de la aplicabilidad
que tengan sobre el producto.*/
/*Consultar el estado de cada uno de los productos de su
pedido. */
/* A recogida de un pedido que haya sido depositado en
un ESILocker antes de la fecha de caducidad, para ello se le debe mostrar la opción
solicitándole el código locker asociado. Una vez introducido, el sistema mostrará un
mensaje en pantalla indicando el número de compartimento que se ha abierto. El estado
de los productos recogidos, en consecuencia, se debe actualizar. */
/* Realizar altas, bajas, búsquedas, listados y
modificaciones de pedidos. */
/* Listados habrá que contemplar la posibilidad de listarlos según su estado. Esto es
necesario para poder localizar rápidamente los pedidos cuya fecha de entrega sea próxima
y que, por tanto, deben ser procesados con mayor prioridad.*/
/*Asignación de transportistas a los productos pedidos en
función de la dirección del cliente y ciudad de reparto*/
/*Asignación de lockers a los pedidos en base a la localidad de
entrega y ubicación del locker.*/
/*Un usuario proveedor podrá acceder únicamente a la información de los pedidos de productos
que él mismo suministra*/


char* id_generator_pedido(ProductoPedido *pedidos, int tamanio_vector){

    int id_generada = 1;


   if(tamanio_vector != 0){ // Si no hay nada en el vector, la primer id es 0000011.
        id_generada = atoi(pedidos[tamanio_vector - 1].id_pedido);
        id_generada++;
    }
    char *id = malloc(8 * sizeof(char));
    if(id == NULL){
        printf("Error al guardar memoria\n");
        exit(EXIT_FAILURE);
    }

    sprintf(id, "%07d" ,id_generada);
    return id;
}


void fecha_entrega(char *fecha, int dia_entrega)
{ 
    
    time_t rawtime; // Defino la struct de tiempo.

    // Convertir la fecha actual a time_t 
    time(&rawtime);
    
    // Sumar x días a la fecha actual.
    rawtime += dia_entrega * 24 * 60 * 60; // X días en segundos
    
    // Actualizar la estructura tm
    struct tm *nueva_fecha = localtime(&rawtime);
    
    strftime(fecha, 11, "%d/%m/%Y", nueva_fecha); // Convierte la struct tm en un formato legible tal que dia/mes/año
}



void busqueda_locker_localidad(Locker *lockers, int* tamanio, char *localidad){ // Se busca un locker en la localidad solicitada por el usuario.
    int coincidencias = 0;

    printf("Productos encontrados de la localidad '%s':\n", localidad);

    for (int i = 0; i < *tamanio; i++) {
        if (strcmp(lockers[i].localidad, localidad) == 0) {
            printf("%s-%s-%s-%s-%d-%d\n", lockers[i].id_locker, lockers[i].localidad, lockers[i].provincia, lockers[i].ubicacion, lockers[i].num_compt, (lockers[i].num_compocup-1));
            printf("\n");
            coincidencias++;
            }
    }
    if (coincidencias == 0) {
        printf("No se encontraron Lockers en la localidad '%s'.\n", localidad);
    }
}


int ocupados_lockers(Locker *l, int tamanio, char *id) {
    
	for (int i = 0; i < tamanio; i++) {
        if (strcmp(id, l[i].id_locker) == 0) { // Compara el ID dado con el ID del locker en la posición i
            if (l[i].num_compt > l[i].num_compocup) { // Verifica si hay compartimentos disponibles
                l[i].num_compocup++; // Incrementa el contador de compartimentos ocupados
                printf("Se ha añadido correctamente\n");
                return 0; // Devuelve 0 si no está lleno
            } else {
                printf("El locker está lleno\n");
                return 1; // Devuelve 1 si está lleno
            }
        }
    }
    printf("El ID del locker no se encontró en el sistema\n");
    return -1; // Devuelve -1 si no se encontró el ID del locker
}

void listado_transportista(Transportista *t, int tamanio){

    printf("ID Transportista - Nombre - Email - Contraseña - Nombre de la empresa - Ciudad de reparto\n");
    for(int i = 0 ; i < tamanio ; i++){
        printf("%s - %s - %s - %s - %s - %s\n", t[i].id_transp, t[i].nombre, t[i].email, t[i].contrasenia, t[i].nombre_empresa, t[i].ciudad_reparto);
    }
}






// Sirve para seleccionar el producto que se va a pedir.
Producto *pedir_producto(Producto *productos , int* tamanio_productos, ProductoPedido *pedidos, int* tamanio){

    char producto_pedido[16];
    int respuesta;
    int coincidencia = 0;

    while(coincidencia == 0){
    printf("Que producto desea comprar?\n");
    fgets(producto_pedido,16,stdin);
    producto_pedido[strcspn(producto_pedido,"\n")] = '\0'; 

    buscador_un_pedidos(pedidos, tamanio , producto_pedido, &coincidencia);

    }
    printf("Esta seguro que desea comprar ese producto?\n1) SI \n 2) NO \n");
    scanf("%d",&respuesta);
    if(respuesta == 1){
        for(int i = 0 ; i < *tamanio_productos ; i++ ){
            if(strcmp(productos[i].nombre,producto_pedido) == 0){
                
                return &productos[i]; // Devolvemos el puntero al producto encontrado.
             }
        }
    }
    return NULL;
}


// Una vez seleccionado el producto que se quiere comprar, se da de alta el pedido correspondiente. Struct de Productos debe pasar como puntero??
void alta_pedidos(ProductoPedido **pedidos, int* tamanio_vector, Cliente actual_cliente,int* tamanio_cliente, Producto producto_seleccionado , int* tamanio_produc, Locker *lockers, int* tamanio_lockers, Transportista *transportista, int* tamanio_transportistas){
    
    ProductoPedido nuevo_producto_pedido;
    char fecha_estimada[11];


    strcpy(nuevo_producto_pedido.id_pedido, id_generator_pedido(*pedidos ,*tamanio_vector)); //Damos el id, al pedido mediante la funcion generadora de IDs.
    flushInputBuffer();

    strcpy(nuevo_producto_pedido.id_prod,producto_seleccionado.id_prod); // Copia la id del producto en la id de producto pedido.

    fecha_entrega(fecha_estimada,producto_seleccionado.entrega); // Hacemos llamada a la funcion que se encarga de: Fecha entrega = Fecha_Actual + Nº dias entrega.

    strcpy(nuevo_producto_pedido.fecha_entrega_prevista,fecha_estimada); // Copia Fecha entrega en el pedido requerido.

    int num_encargos; // Numero que se le quita al stock

    printf("---------------------\n\n");
    printf("Cuantos productos desea? ");

    scanf("%d",&num_encargos);

    if(num_encargos <= producto_seleccionado.stock){
    nuevo_producto_pedido.num_unid = num_encargos;
    producto_seleccionado.stock = producto_seleccionado.stock - num_encargos;
    }else{
        printf("NO HAY STOCK SUFICIENTE \n");
    }

    // El importe del pedido sera igual al precio del producto.
    nuevo_producto_pedido.importe = producto_seleccionado.importe;

    strcpy(nuevo_producto_pedido.estado_pedido,"enPreparacion"); // Le doy como estado de alta al pedido para su comienzo enPreparacion. dsp se ira modificando.

    // Se debe comprobar que el Locker no esta ocupado. Ademas quizas necesite una funcion que busque Lockers, a partir de la localidad del cliente.
    char id_locker_seleccionada[11];
    printf("Seleccione el ID del Locker que mejor le convenga: \n");

    busqueda_locker_localidad(lockers, tamanio_lockers, actual_cliente.localidad);
    fgets(id_locker_seleccionada,11,stdin);
    flushInputBuffer();

    ocupados_lockers(lockers,*tamanio_lockers,id_locker_seleccionada); // No se si hace falta agragar el pedido al locker o ya lo hace la funcion.

    // Seleccionar transportista, ADMIN SOLO
    char id_transportista_seleccionado[5];
    listado_transportista(transportista,*tamanio_transportistas);
    // Comprobar que es ADMIN
    printf("Selecione el ID del tranportista que quiere que entregue el producto:\n");
    fgets(id_transportista_seleccionado,11,stdin);
    flushInputBuffer();

    strcpy(nuevo_producto_pedido.id_transp, id_transportista_seleccionado);


    *pedidos = (ProductoPedido *)realloc(*pedidos, (*tamanio_vector + 1) * sizeof(ProductoPedido));
    if (*pedidos == NULL) {
        printf("Error al aumentar el tamaño del vector.\n");
        return;
    }

    (*pedidos)[*tamanio_vector] = nuevo_producto_pedido;

    (*tamanio_vector)++;
 
}
void baja_pedidos(ProductoPedido **pedidos , int* tamanio, char *id_baja){

    int encontrado = 0;

    for(int i = 0 ; i < *tamanio && encontrado == 0 ; i++) //Comparamos la id que queremos dar de baja con las ids registradas.
    {
        if(strcmp((*pedidos)[i].id_prod,id_baja) == 0){
            encontrado = 1;

        for(int j = i; j < *tamanio - 1; j++) //Reposicionamos las ids posteriores a la dada de baja.
        {
           (*pedidos)[j] = (*pedidos)[j + 1];
        }

        (*tamanio)--; //Reduzco el tamaño del array.
        *pedidos = (ProductoPedido *)realloc(*pedidos, (*tamanio) * sizeof(ProductoPedido));

        printf("Producto con ID %s ha sido de baja correctamente.\n", id_baja);

        }
    }

    if(encontrado != 0){
        printf("La ID registrada no ha sido encontrada.");
    }
}

void listado_Pedido(ProductoPedido *pedidos, int* tamanio){
    
    flushInputBuffer();
    for(int i = 0 ; i < *tamanio ; i++){
        printf("%s-%s-%d-%s-%.2f-%s\n",pedidos[i].id_pedido,pedidos[i].id_prod,pedidos[i].num_unid,pedidos[i].fecha_entrega_prevista,pedidos[i].importe,pedidos[i].estado_pedido);
    }
}

//buscador de pedido segun su estado
void buscador_un_pedidos(ProductoPedido *pedidos, int* tamanio , char* estad_pedido, int *coincidencia){

    for(int i = 0 ; i < *tamanio ; i++ ){

        if(strcmp(pedidos[i].estado_pedido,estad_pedido) == 0){

            printf("%s-%s-%d-%s-%.2f-%s\n",pedidos[i].id_pedido,pedidos[i].id_prod,pedidos[i].num_unid,pedidos[i].fecha_entrega_prevista,pedidos[i].importe,pedidos[i].estado_pedido);
            printf("\n");
            coincidencia++;
            }
        }
        if(coincidencia == 0) {
        printf("No se encontraron pedidos (%s).\n", estad_pedido);
    }
}

void modificar_estado_pedido(ProductoPedido *pedidos, int* tamanio,char *id_modificar);
void modificar_transportistas(ProductoPedido *pedidos, int* tamanio,char *id_modificar);
void modificar_entrega(ProductoPedido *pedidos, int* tamanio,char *id_modificar);

// Permite modificar ciertas características del producto pedido.
void modificar_pedidos(ProductoPedido *pedidos, int* tamanio, Transportista *transportistas, int tamanio_transportistas){

    int a;

    listado_Pedido(pedidos,tamanio);

    char id_modificar[8];
    printf("\nIntroduce el ID del producto que quieres modificar: ");
    fgets(id_modificar,8,stdin);    
    id_modificar[strcspn(id_modificar,"\n")] = '\0';
    flushInputBuffer();


     //SI NO ES ADMIN HAY Q COMPROBAR QUE LA ID DEL PRODUCTO SEA LA MISMA QUE LA ID DEL QUE ESTA HACIENDO LA MODIFICACION -> ES UNA FUNCION NUEVA PERO IGUAL QUE ESTA

    printf("----------\n");
    printf("(1) Modificar estado\n");
    printf("(2) Modificar transportista\n");
    printf("(3) Modificar entrega\n");
    fflush(stdin);
    scanf("%d", &a);
    printf("----------\n\n");

    switch (a) {
        case 1:
            modificar_estado_pedido(pedidos, tamanio, id_modificar);
            break;

        case 2:
            listado_transportista(transportistas,tamanio_transportistas);
            modificar_transportistas(pedidos, tamanio, id_modificar);
            break;

        case 3:
            modificar_entrega(pedidos, tamanio, id_modificar);
            break;

        default:
            break;
    }
}

void modificar_estado_pedido(ProductoPedido *pedidos, int* tamanio,char *id_modificar){

    int i = 0;
    
    while(i < *tamanio && strcmp(pedidos[i].id_prod,id_modificar) != 0){
        i++;    // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    printf("Escribe el estado del pedido: ");
	fflush(stdin);
	fgets(pedidos[i].estado_pedido,15,stdin);
    flushInputBuffer();
}

void modificar_transportistas(ProductoPedido *pedidos, int* tamanio,char *id_modificar){

    int i = 0;
    
    while(i < *tamanio && strcmp(pedidos[i].id_prod,id_modificar) != 0){
        i++;    // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    printf("Escribe el nuevo id del transportista: ");
	fflush(stdin);
	fgets(pedidos[i].id_transp,5,stdin);
    flushInputBuffer();
}

void modificar_entrega(ProductoPedido *pedidos, int* tamanio,char *id_modificar){

    int i = 0;
    int dia_retraso;
    
    while(i < *tamanio && strcmp(pedidos[i].id_prod,id_modificar) != 0){
        i++;    // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    // COMPROBAR FUNC DE LA SUMA DE DIAS.
    printf("Escribe el retraso que puede tener el pedido: ");
	scanf("%d",&dia_retraso);
    fecha_entrega(pedidos[i].fecha_entrega_prevista,dia_retraso); // Comprobar que lo que hace es sumar los dias de retraso a la fecha anteriormente estimada.
    flushInputBuffer();
}

/* void checkear_descuento(Descuento *descuentos, int* tamanio, char *descuento_buscado); */
void consultar_estado(ProductoPedido *pedidos, int* tamanio, char *id_pedido_buscado){

    int coincidencias = 0;

    for(int i = 0 ; i < *tamanio ; i++ ){

        if(strcmp(pedidos[i].id_pedido,id_pedido_buscado) == 0){

            printf("%s\n",pedidos[i].estado_pedido);
            printf("\n");
            coincidencias++;

            }
        }
    if (coincidencias == 0) {
        printf("No se encontro el producto pedido con la id '%s'.\n", id_pedido_buscado);
    }
}




void mostrar_menu(){
    printf("\n----- MENU -----\n");
    printf("1. Alta de pedido\n");
    printf("2. Baja de pedido\n");
    printf("3. Modificar pedido\n");
    printf("4. Consultar estado de pedido\n");
    printf("0. Salir\n");
    printf("Ingrese su opcion: ");
}

// Función para ejecutar la opción seleccionada
void ejecutar_opcion(int opcion, Cliente *clientes, int *tamanio_clientes, Producto *productos, int *tamanio_productos, ProductoPedido *pedidos, int *tamanio_pedidos, Locker *lockers, int *tamanio_lockers, Transportista *transportista, int *tamanio_transportistas){
    
    char ID_Cliente[] = "00000001"; // Corrección en la declaración de la variable ID_Cliente
    char id_baja[8];
    char id_pedido_buscado[8];
    switch (opcion) {
        case 1:
            Producto *producto_seleccionado = pedir_producto(productos, tamanio_productos, pedidos, tamanio_pedidos); // Corrección en la llamada a pedir_producto
            alta_pedidos(&pedidos, tamanio_pedidos, *clientes, tamanio_clientes, *producto_seleccionado , tamanio_productos, lockers, tamanio_lockers,  transportista, tamanio_transportistas); // Corrección en la llamada a alta_pedidos
            printf("Opción de alta de pedido seleccionada.\n");
            break;
        case 2:
            printf("A que ID desea dar de baja: \n");
            listado_Pedido(pedidos, tamanio_pedidos); // Corrección en la llamada a listado_Pedido
            fgets(id_baja,8,stdin);
            flushInputBuffer();
            baja_pedidos(&pedidos, tamanio_pedidos, id_baja); // Corrección en la llamada a baja_pedidos
            printf("Opción de baja de pedido seleccionada.\n");
            break;
        case 3:
            modificar_pedidos(pedidos, tamanio_pedidos, transportista, *tamanio_transportistas); // Corrección en la llamada a modificar_pedidos
            printf("Opción de modificar pedido seleccionada.\n");
            break;
        case 4:
            printf("Cual es el ID de su pedido: \n");
            listado_Pedido(pedidos, tamanio_pedidos); // Corrección en la llamada a listado_Pedido
            fgets(id_pedido_buscado,8,stdin);
            flushInputBuffer();
            consultar_estado(pedidos, tamanio_pedidos, id_pedido_buscado); // Corrección en la llamada a consultar_estado
            printf("Opción de consultar estado de pedido seleccionada.\n");
            break;
        case 0:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opción no válida. Por favor, seleccione una opción válida.\n");
    }
}



// Resto del código...
//Main ProductosPedidos
int main(){
    // Declaración e inicialización de las variables
    Cliente clientes[100];
    int tamanio_clientes = 0;
    Producto productos[100]; // Se asume un máximo de 100 productos
    int tamanio_productos = 0;
    ProductoPedido *pedidos = malloc(100 * sizeof(ProductoPedido)); // Se asume un máximo de 100 pedidos
    int tamanio_pedidos = 0;
    Locker lockers[100]; // Se asume un máximo de 100 productos
    int tamanio_lockers = 0;
    Transportista transportista[100]; // Se asume un máximo de 100 pedidos
    int tamanio_transportistas = 0;
    int opcion;
    Categoria categorias[100]; // Suponiendo que se tienen 100 categorías
    int tamanio_categorias = 0;
    Cliente cliente_actual;
    strcpy(cliente_actual.id_cliente,"0000001");
    
     // Registro de categorías
    printf("Registro de categorias:\n");
    for (int i = 0; i < 3; i++) {
        alta_categoria(categorias, &tamanio_categorias);
    }

    // Registro de productos
    printf("Registro de productos:\n");
    for(int i = 0; i < 3; i++) {
        alta_producto(productos, &tamanio_productos,cliente_actual.id_cliente, categorias, &tamanio_categorias);
    }

    // Mostrar listado de productos
    printf("\nListado de productos registrados:\n");
    listado_producto(productos, &tamanio_productos);

    // Mostrar listado de categorías
    printf("\nListado de categorías registradas:\n");
    for (int i = 0; i < tamanio_categorias; i++) {
        printf("%s - %s\n", categorias[i].id_categ, categorias[i].descrip);
    }

    // Dar de baja un producto
    char id_baja[8];
    printf("\n¿Qué producto desea dar de baja? (Ingrese el ID): ");
    scanf("%s", id_baja);
    baja_producto(productos, &tamanio_productos, id_baja);

    // Dar de baja una categoria
    printf("\n¿Que categoria desea dar de baja? (Ingrese el ID): ");
    scanf("%s", id_baja);
    baja_categoria(categorias, &tamanio_categorias, id_baja);

    // Buscar productos por descripción
    char descripcion_buscada[51];
    printf("\nIngrese la descripción del producto que desea buscar: ");
    fflush(stdin);
    fgets(descripcion_buscada, 51, stdin);
    descripcion_buscada[strcspn(descripcion_buscada, "\n")] = '\0';
    busqueda_producto_descr(productos, &tamanio_productos, descripcion_buscada);

    // Buscar productos por categoría
    char categoria_buscada[51];
    printf("\nIngrese la categoría del producto que desea buscar: ");
    fflush(stdin);
    fgets(categoria_buscada, 51, stdin);
    categoria_buscada[strcspn(categoria_buscada, "\n")] = '\0';
    busqueda_producto_categ(productos, &tamanio_productos, categoria_buscada, categorias, &tamanio_categorias);

     // Modificar producto o categoria
    int select = 0;
    printf("Pulse:\n 1) Para modificar un producto\n 2) Para modificar una categoria\n");
    scanf("%d",&select);
    if (select == 1){
        char id_prov[4];
        strcpy(id_prov,"-1");
        modificar_producto(productos, &tamanio_productos, id_prov);
    }else{
        if(select == 2){
            modificar_categoria(categorias, &tamanio_categorias);
        }
    }

    // Bucle principal del programa
    do {
        mostrar_menu();
        scanf("%d", &opcion);
        ejecutar_opcion(opcion, clientes, &tamanio_clientes, productos, &tamanio_productos, pedidos, &tamanio_pedidos, lockers, &tamanio_lockers, transportista, &tamanio_transportistas);
    } while (opcion != 0);

    free(pedidos); // Liberar memoria asignada a pedidos

    return 0;
}