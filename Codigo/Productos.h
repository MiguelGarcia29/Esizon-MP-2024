#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <estructuras.h>
#include "Categoria.h"

// Funciones a hacer de los productos: 

void alta_producto();
void baja_producto();
void busqueda_producto();
void listado_producto();
void modificaciones_producto();
void buscador_un_producto();
void flushInputBuffer();


//Depura el buffer.
void flushInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//El procedimiento se encarga de generar IDs en un vector de 7 digitos.
char* id_generator(Producto *productos, int tamanio_vector){

    int id_generada = 1;

   if(tamanio_vector != 0){ // Si no hay nada en el vector, la primer id es 0000011.
        id_generada = atoi(productos[tamanio_vector - 1].id_prod);
        id_generada++;
    }
    char id[8];

    sprintf(id,"%07d",id_generada);

    return id;
}

//Procedimiento da de alta los productos.
void alta_producto(Producto *productos, int* tamanio_vector, Cliente actual, Categoria *categ , int* tamanio_categ){

    Producto nuevo_producto;

    strcpy(nuevo_producto.id_prod, id_generator(productos ,*tamanio_vector));

    printf("\nNombre del producto:");
    fgets(nuevo_producto.nombre, 15, stdin);
    nuevo_producto.nombre[strcspn(nuevo_producto.nombre,"\n")] = '\0'; 

    printf("\nPrecio del producto:");
    scanf("%f", &nuevo_producto.importe);
    flushInputBuffer();

    printf("\nIndique una breve descripcion del producto:");
    fgets(nuevo_producto.descrip, 51, stdin);
    nuevo_producto.descrip[strcspn(nuevo_producto.descrip,"\n")] = '\0'; // strcspn() recorre el string en busca del salto de linea para depurarlo.

    printf("\nNumero de producto que se van a vender:");
    scanf("%d", &nuevo_producto.stock);
    flushInputBuffer();

    printf("\nNumero de dias que tarda la entrega:");
    scanf("%d", &nuevo_producto.entrega);
    flushInputBuffer();


    char categoria_productos[51];

    printf("\nIndique la categoria de su producto:");
    fgets(categoria_productos,51,stdin); // Dejo esto para hacer primero dar de alta de categs.
    categoria_productos[strcspn(categoria_productos,"\n")] = '\0'; // strcspn() recorre el string en busca del salto de linea para depurarlo.
    
    int encontradoCategoria = indicar_categ(categ,tamanio_categ,categoria_productos);
    
    while(encontradoCategoria == 0){
        printf("\nCategoria no encontrada.");
        printf("\nIndique la categoria de su producto:");
        fgets(categoria_productos,51,stdin); // Dejo esto para hacer primero dar de alta de categs.
        categoria_productos[strcspn(categoria_productos,"\n")] = '\0'; // strcspn() recorre el string en busca del salto de linea para depurarlo.
        encontradoCategoria = indicar_categ(categ,tamanio_categ,categoria_productos);
    }

    strcpy(nuevo_producto.id_categ, categoria_productos);

    strcpy(nuevo_producto.id_gestor, actual.id_cliente);
   

    productos[*tamanio_vector] = nuevo_producto;

    (*tamanio_vector)++;
 
}



//Procedimiento da de baja los productos. (Usando la id, quizas alla que cambiarlo, o imprimir la lista de productos cada vez que se haga)
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

    for(int i = 0 ; i < *tamanio ; i++){

        printf("%s-%s-%s-%s-%d-%d-%f\n",productos[i].id_prod,productos[i].descrip,productos[i].id_categ,productos[i].id_gestor,productos[i].stock,productos[i].entrega,productos[i].importe);

    }

}

//Búsqueda por descripción.
void busqueda_producto_descr(Producto *productos, int* tamanio, char *descripcion) {
    
    int coincidencias = 0;

    printf("Productos encontrados con la descripción '%s':\n", descripcion);

    for (int i = 0; i < *tamanio; i++) {
        if (strstr(productos[i].descrip, descripcion) != NULL) { //El usuario introduce el nombre de el producto y lo busca imprimiendo todo sus datos.
            printf("ID: %s\n", productos[i].id_prod);
            printf("Descripción: %s\n", productos[i].descrip);
            printf("Categoría: %s\n", productos[i].id_categ);
            printf("Gestor: %s\n", productos[i].id_gestor);
            printf("Stock: %d\n", productos[i].stock);
            printf("Entrega: %d\n", productos[i].entrega);
            printf("Importe: %.2f\n", productos[i].importe);
            printf("\n");
            coincidencias++;
        }
    }

    if (coincidencias == 0) {
        printf("No se encontraron productos con la descripción '%s'.\n", descripcion);
    }
}

//Búsqueda por categoría.
void busqueda_producto_categ(Producto *productos, int* tamanio, char *categ, Categoria *categorias, int* tamanio_categ) {
    int coincidencias = 0;

    printf("Productos encontrados de la categoria '%s':\n", categ);

    for (int i = 0; i < *tamanio; i++) {
        for(int j = 0 ; j < *tamanio_categ; j++){
        if (strcmp(productos[i].id_categ, categorias[j].id_categ) == 0) {
            printf("ID: %s\n", productos[i].id_prod);
            printf("Descripción: %s\n", productos[i].descrip);
            printf("Categoría: %s\n", productos[i].id_categ);
            printf("Gestor: %s\n", productos[i].id_gestor);
            printf("Stock: %d\n", productos[i].stock);
            printf("Entrega: %d\n", productos[i].entrega);
            printf("Importe: %.2f\n", productos[i].importe);
            printf("\n");
            coincidencias++;
            }
        }
    }

    if (coincidencias == 0) {
        printf("No se encontraron productos de la categoria '%s'.\n", categ);
    }
}

void buscador_un_producto(Producto *p, int* tamanio , char *producto_buscado){

    int coincidencias = 0;

    for(int i = 0 ; i < *tamanio ; i++ ){

        if(strcmp(p[i].nombre,producto_buscado) == 0){
            printf("ID: %s\n", p[i].id_prod);
            printf("Descripción: %s\n", p[i].descrip);
            printf("Categoría: %s\n", p[i].id_categ);
            printf("Gestor: %s\n", p[i].id_gestor);
            printf("Stock: %d\n", p[i].stock);
            printf("Entrega: %d\n", p[i].entrega);
            printf("Importe: %.2f\n", p[i].importe);
            printf("\n");
            coincidencias++;
            }
        }
    
    if (coincidencias == 0) {
        printf("No se encontro el producto '%s'.\n", producto_buscado);
    }
}
