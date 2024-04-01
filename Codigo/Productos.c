#include "Productos.h"


//Depura el buffer.
void flushInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//El procedimiento se encarga de generar IDs en un vector de 7 digitos para designar a cada producto.
char* id_generator_prod(Producto *productos, int tamanio_vector){

    int id_generada = 1;

   if(tamanio_vector != 0){ // Si no hay nada en el vector, la primer id es 0000011.
        id_generada = atoi(productos[tamanio_vector - 1].id_prod);
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

//Procedimiento da de alta los productos.
// En ella se necesita que se hayan dado de alta previamente las categorias.
void alta_producto(Producto *productos, int* tamanio_vector, Cliente actual, Categoria *categ , int* tamanio_categ){

    Producto nuevo_producto;

    strcpy(nuevo_producto.id_prod, id_generator_prod(productos ,*tamanio_vector));
    flushInputBuffer();

    printf("\nNombre del producto: ");
    fgets(nuevo_producto.nombre, 15, stdin);
    flushInputBuffer();
    nuevo_producto.nombre[strcspn(nuevo_producto.nombre,"\n")] = '\0'; 

    printf("\nPrecio del producto:");
    scanf("%f", &nuevo_producto.importe);
    flushInputBuffer();

    printf("\nIndique una breve descripcion del producto: ");
    fgets(nuevo_producto.descrip, 51, stdin);
    flushInputBuffer();
    nuevo_producto.descrip[strcspn(nuevo_producto.descrip,"\n")] = '\0'; // strcspn() recorre el string en busca del salto de linea para depurarlo.

    printf("\nNumero de producto que se van a vender: ");
    scanf("%d", &nuevo_producto.stock);
    flushInputBuffer();

    printf("\nNumero de dias que tarda la entrega: ");
    scanf("%d", &nuevo_producto.entrega);
    flushInputBuffer();


    char categoria_productos[51];

    printf("\nIndique la categoria de su producto: ");
    fgets(categoria_productos,51,stdin); // Dejo esto para hacer primero dar de alta de categs.
    categoria_productos[strcspn(categoria_productos,"\n")] = '\0'; // strcspn() recorre el string en busca del salto de linea para depurarlo.


    int encontradoCategoria = check_categ(categ,tamanio_categ,categoria_productos);
    while(encontradoCategoria == 0){
        printf("\nCategoria no encontrada.");
        printf("\nIndique la categoria de su producto: ");
        fgets(categoria_productos,51,stdin); // Dejo esto para hacer primero dar de alta de categs.
        categoria_productos[strcspn(categoria_productos,"\n")] = '\0'; // strcspn() recorre el string en busca del salto de linea para depurarlo.
        encontradoCategoria = check_categ(categ,tamanio_categ,categoria_productos);
    }
    if(encontradoCategoria != 0){
        strcpy(nuevo_producto.id_categ,indicar_categ(categ,tamanio_categ,categoria_productos));
    }

    strcpy(nuevo_producto.id_gestor, actual.id_cliente);
   
    productos[*tamanio_vector] = nuevo_producto;

    (*tamanio_vector)++;
 
}

//Procedimiento que da de baja los productos. (Usando la id, quizas haya que cambiarlo, o imprimir la lista de productos cada vez que se haga)
void baja_producto(Producto *productos , int* tamanio, char *id_baja){

    int encontrado = 0;

    for(int i = 0 ; i < *tamanio ; i++) //Comparamos la id que queremos dar de baja con las ids registradas.
    {
        if(strcmp(productos[i].id_prod,id_baja) == 0){
            encontrado = 1;

        for(int j = i; j < *tamanio - 1; j++) //Reposicionamos las ids posteriores a la dada de baja.
        {
           productos[j] = productos[j + 1];
        }

        (*tamanio)--; //Reduzco el tamaño del array.

        printf("Producto con ID %s ha sido de baja correctamente.\n", id_baja);

        }
    }

    if(encontrado != 0){
        printf("La ID registrada no ha sido encontrada.");
    }
}
// Muestra lista de los productos, dados de alta.
void listado_producto(Producto *productos, int* tamanio){
    
    flushInputBuffer();
    for(int i = 0 ; i < *tamanio ; i++){
        printf("%s-%s-%s-%s-%s-%d-%d-%.2f\n",productos[i].id_prod,productos[i].nombre,productos[i].descrip,productos[i].id_categ,productos[i].id_gestor,productos[i].stock,productos[i].entrega,productos[i].importe);
    }

}
//Búsqueda por descripción. Se toma como parametro "descripcion" aquella descripcion que introduce el usuario.
void busqueda_producto_descr(Producto *productos, int* tamanio, char *descripcion) {
    
    int coincidencias = 0;

    printf("Productos encontrados con la descripción '%s':\n", descripcion);

    for (int i = 0; i < *tamanio; i++) {
        if (strstr(productos[i].descrip, descripcion) != NULL) { //El usuario introduce el nombre de el producto y lo busca imprimiendo todo sus datos.
            
            printf("%s-%s-%s-%s-%s-%d-%d-%.2f\n",productos[i].id_prod,productos[i].nombre,productos[i].descrip,productos[i].id_categ,productos[i].id_gestor,productos[i].stock,productos[i].entrega,productos[i].importe);
            printf("\n");
            coincidencias++;

        }
    }

    if (coincidencias == 0) {
        printf("No se encontraron productos con la descripción '%s'.\n", descripcion);
    }
}

//Búsqueda por categoría. Se toma como parametro "categ" aquella categoria que introduce el usuario.
void busqueda_producto_categ(Producto *productos, int* tamanio, char *categ, Categoria *categorias, int* tamanio_categ) {
    int coincidencias = 0;

    printf("Productos encontrados de la categoria '%s':\n", categ);

    for (int i = 0; i < *tamanio; i++) {
        for(int j = 0 ; j < *tamanio_categ; j++){
        if (strcmp(productos[i].id_categ, categorias[j].id_categ) == 0) {
           
            printf("%s-%s-%s-%s-%s-%d-%d-%.2f\n",productos[i].id_prod,productos[i].nombre,productos[i].descrip,productos[i].id_categ,productos[i].id_gestor,productos[i].stock,productos[i].entrega,productos[i].importe);
            printf("\n");
            coincidencias++;

            }
        }
    }
    if (coincidencias == 0) {
        printf("No se encontraron productos de la categoria '%s'.\n", categ);
    }
}
//Buscador de un producto. Se toma como parametro "producto_buscado" aquel producto que introduce el usuario.
void buscador_un_producto(Producto *productos, int* tamanio , char *producto_buscado){

    int coincidencias = 0;

    for(int i = 0 ; i < *tamanio ; i++ ){

        if(strcmp(productos[i].nombre,producto_buscado) == 0){

            printf("%s-%s-%s-%s-%s-%d-%d-%.2f\n",productos[i].id_prod,productos[i].nombre,productos[i].descrip,productos[i].id_categ,      productos[i].id_gestor,productos[i].stock,productos[i].entrega,productos[i].importe);
            printf("\n");
            coincidencias++;

            }
        }
    if (coincidencias == 0) {
        printf("No se encontro el producto '%s'.\n", producto_buscado);
    }
}

void modificar_descripcion_prod(Producto *productos, int* tamanio,char *id_modificar);
void modificar_precio(Producto *productos, int* tamanio,char *id_modificar);
void modificar_stock(Producto *productos, int* tamanio,char *id_modificar);
void modificar_entrega(Producto *productos, int* tamanio,char *id_modificar);

void modificar_producto(Producto *productos, int* tamanio) {
    int a;
    char producto_buscado[51];

    printf("\nIntroduce el nombre del producto que quieres modificar: ");
    fflush(stdin);
    fgets(producto_buscado, 51, stdin);
    producto_buscado[strcspn(producto_buscado, "\n")] = '\0';

    buscador_un_producto(productos,tamanio,producto_buscado);

    char id_modificar[8];
    printf("\nIntroduce el ID del producto que quieres modificar: ");
    fgets(id_modificar,8,stdin);
    id_modificar[strcspn(id_modificar,"\n")] = '\0';
    flushInputBuffer();


     //SI NO ES ADMIN HAY Q COMPROBAR QUE LA ID DEL PRODUCTO SEA LA MISMA QUE LA ID DEL QUE ESTA HACIENDO LA MODIFICACION -> ES UNA FUNCION NUEVA PERO IGUAL QUE ESTA

    printf("----------\n");
    printf("(1) Modificar descripcion\n");
    printf("(2) Modificar precio\n");
    printf("(3) Modificar stock\n");
    printf("(4) Modificar entrega\n");
    fflush(stdin);
    scanf("%d", &a);
    printf("----------\n\n");

    switch (a) {
        case 1:
            modificar_descripcion_prod(productos, tamanio, id_modificar);
            break;

        case 2:
            modificar_precio(productos, tamanio, id_modificar);
            break;

        case 3:
            modificar_stock(productos, tamanio, id_modificar);
            break;

        case 4:
            modificar_entrega(productos, tamanio, id_modificar);
            break;

        default:
            break;
    }
}

void modificar_descripcion_prod(Producto *productos, int* tamanio,char *id_modificar){

    int i = 0;
    
    while(i < *tamanio && strcmp(productos[i].id_prod,id_modificar) != 0){
        i++;    // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    printf("Escribe la nueva descripcion: ");
	fflush(stdin);
	fgets(productos[i].id_prod,51,stdin);
    flushInputBuffer();
}

void modificar_precio(Producto *productos, int* tamanio,char *id_modificar){

    int i = 0;
    
    while(i < *tamanio && strcmp(productos[i].id_prod,id_modificar) != 0){
        i++;    // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

	printf("Introduce el nuevo importe: ");
	fflush(stdin);
	scanf("%f",&productos[i].importe);
    flushInputBuffer();
}

void modificar_stock(Producto *productos, int* tamanio,char *id_modificar){

    int i = 0;
    
    while(i < *tamanio && strcmp(productos[i].id_prod,id_modificar) != 0){
        i++;    // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

	printf("Cantidad de productos en stock: ");
	fflush(stdin);
	scanf("%d",&productos[i].stock);
    flushInputBuffer();
}

void modificar_entrega(Producto *productos, int* tamanio,char *id_modificar){
    
     int i = 0;
    
    while(i < *tamanio && strcmp(productos[i].id_prod,id_modificar) != 0){
        i++;    // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

	printf("Nueva fecha maxima de entrega: ");
	fflush(stdin);
	scanf("%d",&productos[i].entrega);
    flushInputBuffer();
}


