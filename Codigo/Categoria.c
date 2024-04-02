#include "Categoria.h"

//Depura el buffer.
void flushInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char* id_generator_categ(Categoria *categorias, int tamanio_vector){

    int id_generada = 1;

   if(tamanio_vector != 0){ // Si no hay nada en el vector, la primer id es 0000011.
        id_generada = atoi(categorias[tamanio_vector - 1].id_categ);
        id_generada++;
    }

    char *id = malloc(5 * sizeof(char));
    if (id == NULL) {
        printf("Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    sprintf(id,"%04d",id_generada);

    return id;
}

//Dar de altas las categorias. Habria que identificar quien lo hace pq solo podrian los admins.
void alta_categoria(Categoria *categoria, int* tamanio_vector /*Cliente actual*/){

    Categoria nueva_categoria;

    strcpy(nueva_categoria.id_categ, id_generator_categ(categoria ,*tamanio_vector));

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
int check_categ(Categoria *categ, int* tamanio,char *categoria_productos){

    int coincidencia = 0 ;

    for(int i = 0 ; i < *tamanio && coincidencia == 0 ; i++){
    if (strcmp(categ[i].descrip, categoria_productos) == 0) {
                coincidencia = 1;
            }
        }
    return coincidencia;
}

char *indicar_categ(Categoria *categ, int* tamanio, char *categoria_productos) {
    char *categoriaEncontrada = NULL;
    int coincidencia = 0;

    for(int i = 0 ; i < *tamanio && coincidencia == 0 ; i++) {
        if (strcmp(categ[i].descrip, categoria_productos) == 0) {
            categoriaEncontrada = malloc(5 * sizeof(char));
            if (categoriaEncontrada == NULL) {
                printf("Error al asignar memoria.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(categoriaEncontrada, categ[i].id_categ);
            coincidencia = 1;
        }
    }
    return categoriaEncontrada;
}

void modificar_categoria(Categoria *categorias, int* tamanio){
    char id_modificar[8];

    printf("\nIntroduce el ID de la categoria que quieres modificar: ");
    fgets(id_modificar,8,stdin);
    id_modificar[strcspn(id_modificar,"\n")] = '\0';
    flushInputBuffer();

    modificar_descripcion_categ(categorias, tamanio, id_modificar);
}

void modificar_descripcion_categ(Categoria *categorias, int* tamanio,char *id_modificar) {
    int i = 0;

    while(i < *tamanio && strcmp(categorias[i].id_categ,id_modificar) != 0){
        i++;
    }

    printf("Escribe la nueva descripcion: ");
    fflush(stdin);
    fgets(categorias[i].descrip, 51, stdin);
    categorias[i].descrip[strcspn(categorias[i].descrip, "\n")] = '\0';
    flushInputBuffer();
}
int main(){
    return 0;
}