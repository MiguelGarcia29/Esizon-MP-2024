#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#define MAX_DIG 7


typedef struct {
    char id_prod[8];
    char descrip[51];
    char id_categ[5];
    char id_gestor[5];
    int stock;
    int entrega;
    float importe;
}Producto;

// Funciones a hacer de los productos: 
void alta_producto();
void baja_producto();
void busqueda_producto();
void listado_producto();
void modificaciones_producto();





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

void alta_producto(Producto *productos, int* tamanio_vector){

    Producto nuevo_producto;

    printf("\nPrecio del producto:");
    scanf("%f", &nuevo_producto.importe);
    flushInputBuffer();


    printf("\nIndique una breve descripcion del producto:");
    fgets(nuevo_producto.descrip, 51, stdin);
    nuevo_producto.descrip[strcspn(nuevo_producto.descrip,"\n")] = '\0'; // strcspn() recorre el string en busca del salto de linea para depurarlo.

    printf("\nNumero de producto que se van a vender:");
    scanf("%d", &nuevo_producto.stock);
    flushInputBuffer();

    strcpy(nuevo_producto.id_prod, id_generator(productos ,*tamanio_vector));

    productos[*tamanio_vector] = nuevo_producto;

    (*tamanio_vector)++;
 
}

/*
baja_producto(Producto *productos , int* tamanio){


}
*/
  
