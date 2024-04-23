#include "Categoria.h"

// Función para limpiar el búfer de entrada
void flushInputBufferC(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Función para generar un ID para una categoría
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

// Función para agregar una nueva categoría
void alta_categoria(Categoria **categorias, int* tamanio_vector){

    Categoria nueva_categoria;

    strcpy(nueva_categoria.id_categ, id_generator_categ(*categorias ,*tamanio_vector));

    printf("Ingrese la descripcion de la categoria: ");
    fgets(nueva_categoria.descrip, 51, stdin);
    nueva_categoria.descrip[strcspn(nueva_categoria.descrip, "\n")] = '\0';

    // Agregar la nueva categoría al array
    *categorias = (Categoria *)realloc(*categorias, ((*tamanio_vector) + 1) * sizeof(Categoria));
    if (*categorias == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    (*categorias)[*tamanio_vector] = nueva_categoria;
    (*tamanio_vector)++;
    printf("Categoria agregada exitosamente.\n");
}

// Procedimiento para dar de baja una categoría
void baja_categoria(Categoria **categorias, int *numCategorias) {
    char id[5];
    int encontrado = 0;
    printf("Ingrese el ID de la categoria a eliminar: ");
    fgets(id, 5, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *numCategorias; i++) {
        if (strcmp((*categorias)[i].id_categ, id) == 0) {
            encontrado = 1;
            // Eliminar la categoría moviendo los elementos hacia adelante
            for (int j = i; j < *numCategorias - 1; j++) {
                (*categorias)[j] = (*categorias)[j + 1];
            }
            // Reducir el tamaño del array
            *categorias = (Categoria *)realloc(*categorias, ((*numCategorias) - 1) * sizeof(Categoria));
            if (*categorias == NULL) {
                printf("Error al liberar memoria.\n");
                exit(1);
            }
            (*numCategorias)--;
            printf("Categoria eliminada.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Categoria no encontrada.\n");
    }
}

// Función para comparar categorías
int check_categ(Categoria **categ, int *tamanio,char *categoria_productos){

    int coincidencia = 0 ;

    for(int i = 0 ; i < *tamanio && coincidencia == 0 ; i++){
    if (strcmp((*categ)[i].descrip, categoria_productos) == 0) {
                coincidencia = 1;
            }
        }
    return coincidencia;
}

// Función para obtener el ID de una categoría
char *indicar_categ(Categoria **categ, int* tamanio, char *categoria_productos) {
    char *categoriaEncontrada = "";
    int coincidencia = 0;

    for(int i = 0 ; i < *tamanio && coincidencia == 0 ; i++) {
        if (strcmp((*categ)[i].descrip, categoria_productos) == 0) {
            categoriaEncontrada = (*categ)[i].id_categ;
            coincidencia = 1;
        }
    }
    return categoriaEncontrada;
}

// Función para guardar las categorías en un archivo
void guardarCategoriasEnArchivo(Categoria *categorias, int numCategorias)
{
    FILE *archivo = fopen("Categorias.txt", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Categorias.txt.\n");
        return;
    }

    for (int i = 0; i < numCategorias; i++)
    {
        fprintf(archivo, "%s-%s-\n", categorias[i].id_categ, categorias[i].descrip);
    }

    fclose(archivo);
}

// Función para iniciar las categorías desde un archivo
Categoria *iniciarCategoriasDeArchivo(int *numCat)
{
    FILE *archivo = fopen(Categorias_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Categorias.txt.\n");
        return NULL;
    }

    // Contar la cantidad de líneas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud máxima de línea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de categorías
    Categoria *categorias = (Categoria *)malloc(count * sizeof(Categoria));
    if (categorias == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de categorias.\n");
        return NULL;
    }

    // Leer cada línea y rellenar el vector
    for(int i=0; i < count; i++)
    {
        if(fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL){
        char *token = strtok(buffer, "-");
        strncpy(categorias[i].id_categ, token, sizeof(categorias[i].id_categ));
        token = strtok(NULL, "-");
        strncpy(categorias[i].descrip, token, sizeof(categorias[i].descrip));
        }
    }

    fclose(archivo);
    *numCat = count;
    return categorias;
}

// Procedimiento para modificar una categoría
void modificarCategoria(Categoria **categorias, int *numCategorias) {
    char id[5];
    int encontrado = 0;
    printf("Ingrese el ID de la categoria: ");
    fgets(id, 5, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *numCategorias; i++) {
        if (strcmp((*categorias)[i].id_categ, id) == 0) {
            encontrado = 1;
            printf("Ingrese la nueva descripcion de la categoria (maximo 50 caracteres): ");
            fgets((*categorias)[i].descrip, 51, stdin);
            (*categorias)[i].descrip[strcspn((*categorias)[i].descrip, "\n")] = '\0';
            printf("Categoria modificada exitosamente.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Categoria no encontrada.\n");
    }
}

// Procedimiento para listar todas las categorías
void listarCategorias(Categoria **categorias, int *numCategorias) {
    printf("Categorias:\n");
    for (int i = 0; i < *numCategorias; i++) {
        printf("ID: %s\n", (*categorias)[i].id_categ);
        printf("Descripcion: %s\n", (*categorias)[i].descrip);
        printf("\n");
    }
}

// Procedimiento para buscar una categoría por su ID
void buscarCategoria(Categoria **categorias, int *numCategorias) {
    char id[5];
    int encontrado = 0;

    printf("Ingrese el ID de la categoria: ");
    fgets(id, 5, stdin);
    id[strcspn(id, "\n")] = '\0';

    for (int i = 0; i < *numCategorias && encontrado == 0; i++) {
        if (strcmp((*categorias)[i].id_categ, id) == 0) {
            encontrado = 1;
            printf("ID de la categoria: %s\n", (*categorias)[i].id_categ);
            printf("Descripcion: %s\n", (*categorias)[i].descrip);
            printf("---------------------------------\n");
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontro ninguna categoria con el ID.\n");
    }
}
