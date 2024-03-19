#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
void flushInputBuffer();



//El procedimiento se encarga de generar IDs en un vector de 7 digitos.
char* id_generator(Producto *productos, int tamanio_vector){

    int id_generada = 1;

   if(tamanio_vector != 0){ // Si no hay nada en el vector, la primer id es 0000011.
        id_generada = atoi(productos[tamanio_vector - 1].id_prod);
        id_generada++;
    }
    char *id = malloc(8 * sizeof(char));
    
    if(id == NULL){
        printf("Error al asignar memoria. \n");
        exit(EXIT_FAILURE);
    }

    sprintf(id,"%07d",id_generada);

    return id;
}

//Procedimiento da de alta los productos.
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

    printf("\nNumero de dias que tarda la entrega:");
    scanf("%d", &nuevo_producto.entrega);
    flushInputBuffer();

    /*
    Categoria a que pertenece?
    */

    strcpy(nuevo_producto.id_prod, id_generator(productos ,*tamanio_vector));

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
