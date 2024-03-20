#include <stdio.h>
#include <stdlib.h>
#include <estructuras.h>
#include <string.h>

typedef struct {
    char id_categ[5];
    char descrip[51];
}Categoria;



void almacenar(Categoria* cat);

char* id_generator(Categoria *categorias, int tamanio_vector){

    int id_generada = 1;

   if(tamanio_vector != 0){ // Si no hay nada en el vector, la primer id es 0000011.
        id_generada = atoi(categorias[tamanio_vector - 1].id_categ);
        id_generada++;
    }
    char id[5];

    sprintf(id,"%04d",id_generada);

    return id;
}

//Dar de altas las categorias. Habria que identificar quien lo hace pq solo podrian los admins.
void alta_categoria(Categoria *categoria, int* tamanio_vector, Cliente actual){

    Categoria nueva_categoria;

    strcpy(nueva_categoria.id_categ, id_generator(categoria ,*tamanio_vector));

    printf("\nIndique una breve descripcion de la categoria:");
    fgets(nueva_categoria.descrip, 51, stdin);
    nueva_categoria.descrip[strcspn(nueva_categoria.descrip,"\n")] = '\0'; // strcspn() recorre el string en busca del salto de linea para depurarlo.

    categoria[*tamanio_vector] = nueva_categoria;

    (*tamanio_vector)++;
 
}

//Procedimiento da de baja los productos. (Usando la id introducida por user, quizas alla que cambiarlo, o imprimir la lista de productos cada vez que se haga)
void baja_categoria(Categoria *categoria , int* tamanio, char *id_baja){

    int encontrado = 0;

    for(int i = 0 ; i < *tamanio ; i++) //Comparamos la id que queremos dar de baja con las ids registradas.
    {
        if(strcmp(categoria[i].id_categ,id_baja) == 0){
            encontrado = 1;

        for(int j = i; j < *tamanio - 1; j++) //Reposicionamos las ids posteriores a la dada de baja.
        {
           categoria[j] = categoria[j + 1];
        }

        (*tamanio)--; //Reduzco el tamaño del array.

        printf("Categoria con ID %s ha sido de baja correctamente.\n", id_baja);

        }
    }

    if(encontrado != 0){
        printf("La ID registrada no ha sido encontrada.");
    }
}
//Funcion usada para compara categorias con la que ingresara el usuario al dar de alta un producto. Se pasa como parametro el registro de categorias y categoria_productos como aquella categoria que introduce el usuario.
int indicar_categ(Categoria *categ, int* tamanio,char *categoria_productos){

    int coincidencia = 0 ;

    for(int i = 0 ; i < *tamanio && coincidencia == 0 ; i++){
    if (strcmp(categ[i].descrip, categoria_productos) == 0) {
                coincidencia = 1;
            }
        }
    return coincidencia;
}