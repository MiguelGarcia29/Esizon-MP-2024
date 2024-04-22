#include "Productos.h"

char *id_generator_prod(Producto *productos, int tamanio_vector);

// Depura el buffer.
void flushInputBufferr()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}


// Guarda el vector de Produtcos en el archivo siguiendo la estructura:
/*
    o Identificador del producto (Id_prod), 7 digitos.
    o Descripción del producto (Descrip), 50 caracteres maximo.
    o Id de la categoria a la que pertenece (Id_categ), 4 digitos.
    o Id del gestor del producto (Id_gestor), 4 digitos. Debera coincidir con el identificador de la
    empresa administradora o proveedora del producto.
    o Stock del producto (Stock).
    o Compromiso de Entrega (Entrega). Indicara el número de dias maximo que transcurrira desde
    la fecha de realización del pedido hasta la entrega al cliente.
    o Importe del producto en euros (Importe).
*/
void guardarProductosEnArchivo(Producto *productos, int numProductos)
{
    FILE *archivo = fopen(Productos_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Productos.txt.\n");
        return;
    }

    for (int i = 0; i < numProductos; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%s-%d-%d-%.2f\n",
                productos[i].id_prod,
                productos[i].nombre,
                productos[i].descrip,
                productos[i].id_categ,
                productos[i].id_gestor,
                productos[i].stock,
                productos[i].entrega,
                productos[i].importe);
    }

    fclose(archivo);
}

Producto *iniciarProductosDeArchivo(int *numProductos)
{
    FILE *archivo = fopen(Productos_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Productos_txt);
        return NULL;
    }

    // Contar la cantidad de lineas = productos en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA];
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear vector cliente
    Producto *productos = (Producto *)malloc(count * sizeof(Producto));
    if (productos == NULL)
    {
        fclose(archivo);
        printf("No se pudo asignar memoria para el vector de productos.\n");
        return NULL;
    }

    // Leer cada linea del archivo y rellenar el vector de productos
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(productos[i].id_prod, token, sizeof(productos[i].id_prod));
        token = strtok(NULL, "-");
        strncpy(productos[i].nombre, token, sizeof(productos[i].nombre));
        token = strtok(NULL, "-");
        strncpy(productos[i].descrip, token, sizeof(productos[i].descrip));
        token = strtok(NULL, "-");
        strncpy(productos[i].id_categ, token, sizeof(productos[i].id_categ));
        token = strtok(NULL, "-");
        strncpy(productos[i].id_gestor, token, sizeof(productos[i].id_gestor));
        token = strtok(NULL, "-");
        productos[i].stock = atoi(token);
        token = strtok(NULL, "-");
        productos[i].entrega = atoi(token); // atoi convierte la cadena en int
        token = strtok(NULL, "-");
        productos[i].importe = atof(token); // atof convierte la cadena en Float.
        i++;
    }

    fclose(archivo);
    *numProductos = count;
    return productos;
}


// El procedimiento se encarga de generar IDs en un vector de 7 digitos para designar a cada producto.
char *id_generator_prod(Producto *productos, int tamanio_vector)
{

    int id_generada = 1;

    if (tamanio_vector != 0)
    { // Si no hay nada en el vector, la primer id es 0000011.
        id_generada = atoi(productos[tamanio_vector - 1].id_prod);
        id_generada++;
    }
    char *id = malloc(8 * sizeof(char));
    if (id == NULL)
    {
        printf("Error al guardar memoria\n");
        exit(EXIT_FAILURE);
    }

    sprintf(id, "%07d", id_generada);
    return id;
}

// Procedimiento da de alta los productos.
//  En ella se necesita que se hayan dado de alta previamente las categorias.
void alta_producto(Producto **productos, int *tamanio_vector, char *idAlta, Categoria **categ, int * tamanio_categ)
{

    Producto nuevo_producto;

    strcpy(nuevo_producto.id_prod, id_generator_prod(*productos, *tamanio_vector));

    printf("\nNombre del producto: ");
    fgets(nuevo_producto.nombre, 15, stdin);
    nuevo_producto.nombre[strcspn(nuevo_producto.nombre, "\n")] = '\0';

    printf("\nPrecio del producto:");
    scanf("%f", &nuevo_producto.importe);
    flushInputBufferr();

    printf("\nIndique una breve descripcion del producto: ");
    fgets(nuevo_producto.descrip, 51, stdin);
    nuevo_producto.descrip[strcspn(nuevo_producto.descrip, "\n")] = '\0'; // strcspn() recorre el string en busca del salto de linea para depurarlo.

    printf("\nNumero de producto que se van a vender: ");
    scanf("%d", &nuevo_producto.stock);
    flushInputBufferr();

    printf("\nNumero de dias que tarda la entrega: ");
    scanf("%d", &nuevo_producto.entrega);
    flushInputBufferr();

    char categoria_productos[51];

    printf("\nIndique la categoria de su producto: ");
    fgets(categoria_productos, 51, stdin);                          // Dejo esto para hacer primero dar de alta de categs.
    categoria_productos[strcspn(categoria_productos, "\n")] = '\0'; // strcspn() recorre el string en busca del salto de linea para depurarlo.

    char* encontradoCategoria = indicar_categ(categ, tamanio_categ, categoria_productos);
    while (strcmp(encontradoCategoria,"") == 0)
    {
        printf("\nCategoria no encontrada.");
        printf("\nIndique la categoria de su producto: ");
        fgets(categoria_productos, 51, stdin);                          // Dejo esto para hacer primero dar de alta de categs.
        categoria_productos[strcspn(categoria_productos, "\n")] = '\0'; // strcspn() recorre el string en busca del salto de linea para depurarlo.
        encontradoCategoria = indicar_categ(categ, tamanio_categ, categoria_productos);
    }

    strcpy(nuevo_producto.id_categ, encontradoCategoria);

    strcpy(nuevo_producto.id_gestor, idAlta);

    *productos = (Producto *)realloc(*productos, (*tamanio_vector + 1) * sizeof(Producto));

    (*productos)[*tamanio_vector] = nuevo_producto;

    (*tamanio_vector)++;
}

// Procedimiento que da de baja los productos. (Usando la id, quizas haya que cambiarlo, o imprimir la lista de productos cada vez que se haga)
void baja_producto(Producto **productos, int *tamanio, char *id_baja)
{
    int encontrado = 0;

    for (int i = 0; i < *tamanio && encontrado == 0; i++) {
        if (strcmp((*productos)[i].id_prod, id_baja) == 0) {
            encontrado = 1;

            for (int j = i; j < (*tamanio - 1); j++) {
                (*productos)[j] = (*productos)[j + 1];
            }

            (*tamanio)--;
            *productos = realloc(*productos, (*tamanio) * sizeof(Producto));

            printf("Producto con ID %s ha sido dado de baja correctamente.\n", id_baja);
        }
    }

    if (!encontrado) {
        printf("No se encontró ningún producto con ID %s.\n", id_baja);
    }
}

// Muestra lista de los productos, dados de alta.
void listado_producto(Producto **productos, int *tamanio)
{

    for (int i = 0; i < *tamanio; i++)
    {
        printf("%s-%s-%s-%s-%s-%d-%d-%.2f\n", (*productos)[i].id_prod, (*productos)[i].nombre, (*productos)[i].descrip,
                   (*productos)[i].id_categ, (*productos)[i].id_gestor, (*productos)[i].stock, (*productos)[i].entrega, (*productos)[i].importe);
    }
}

// Muestra lista de los productos, dados de alta.
void listado_producto_prooved(Producto **productos, int tamanio, char *idProv)
{

    for (int i = 0; i < tamanio; i++)
    {
        if (strcmp((*productos)[i].id_gestor, idProv) == 0)
            printf("%s-%s-%s-%s-%s-%d-%d-%.2f\n", (*productos)[i].id_prod, (*productos)[i].nombre, (*productos)[i].descrip,
                   (*productos)[i].id_categ, (*productos)[i].id_gestor, (*productos)[i].stock, (*productos)[i].entrega, (*productos)[i].importe);
    }
}

// Muestra lista de los productos, dados de alta.
int productoEsDeProveedor(Producto **productos, int *tamanio, char *idProv, char *idProd)
{
    int encontrado = 0;

    for (int i = 0; i < *tamanio && encontrado == 0; i++)
    {

        if (strcmp((*productos)[i].id_gestor, idProv) == 0 && strcmp((*productos)[i].id_prod, idProd) == 0)
            encontrado = 1;
    }

    return encontrado;
}

// Búsqueda por descripción. Se toma como parametro "descripcion" aquella descripcion que introduce el usuario.
void busqueda_producto_descr(Producto *productos, int *tamanio, char *descripcion)
{

    int coincidencias = 0;

    printf("Productos encontrados con la descripción '%s':\n", descripcion);

    for (int i = 0; i < *tamanio; i++)
    {
        if (strstr(productos[i].descrip, descripcion) != NULL)
        { // El usuario introduce el nombre de el producto y lo busca imprimiendo todo sus datos.

            printf("%s-%s-%s-%s-%s-%d-%d-%.2f\n", productos[i].id_prod, productos[i].nombre, productos[i].descrip, productos[i].id_categ, productos[i].id_gestor, productos[i].stock, productos[i].entrega, productos[i].importe);
            printf("\n");
            coincidencias++;
        }
    }

    if (coincidencias == 0)
    {
        printf("No se encontraron productos con la descripción '%s'.\n", descripcion);
    }
}

// Búsqueda por categoría. Se toma como parametro "categ" aquella categoria que introduce el usuario.
void busqueda_producto_categ(Producto **productos, int *tamanio, char *categ, Categoria **categorias, int *tamanio_categ)
{
    int coincidencias = 0;

    printf("Productos encontrados de la categoria '%s':\n", categ);

    for (int i = 0; i < *tamanio; i++)
    {
        for (int j = 0; j < *tamanio_categ; j++)
        {
            if (strcmp((*productos)[i].id_categ, (*categorias)[j].id_categ) == 0)
            {

                printf("%s-%s-%s-%s-%s-%d-%d-%.2f\n", (*productos)[i].id_prod, (*productos)[i].nombre, (*productos)[i].descrip, (*productos)[i].id_categ,
                        (*productos)[i].id_gestor, (*productos)[i].stock, (*productos)[i].entrega, (*productos)[i].importe);
                printf("\n");
                coincidencias++;
            }
        }
    }
    if (coincidencias == 0)
    {
        printf("No se encontraron productos de la categoria '%s'.\n", categ);
    }
}
// Buscador de un producto. Se toma como parametro "producto_buscado" aquel producto que introduce el usuario.
void buscador_un_producto(Producto **productos, int *tamanio, char *producto_buscado)
{

    int coincidencias = 0;

    for (int i = 0; i < *tamanio; i++)
    {

        if (strcmp((*productos)[i].nombre, producto_buscado) == 0)
        {

            printf("%s-%s-%s-%s-%s-%d-%d-%.2f\n", (*productos)[i].id_prod, (*productos)[i].nombre, (*productos)[i].descrip,
                   (*productos)[i].id_categ, (*productos)[i].id_gestor, (*productos)[i].stock, (*productos)[i].entrega, (*productos)[i].importe);
            printf("\n");
            coincidencias++;
        }
    }
    if (coincidencias == 0)
    {
        printf("No se encontro el producto '%s'.\n", producto_buscado);
    }
}

void modificar_descripcion_prod(Producto **productos, int *tamanio, char *id_modificar);
void modificar_precio(Producto **productos, int *tamanio, char *id_modificar);
void modificar_stock(Producto **productos, int *tamanio, char *id_modificar);
void modificar_entrega(Producto **productos, int *tamanio, char *id_modificar);

// idProv == -1 para admins
void modificar_producto(Producto **productos, int *tamanio, char *idProv)
{
    int a;
    char producto_buscado[51];

    printf("\nIntroduce el nombre del producto que quieres modificar: ");
    fflush(stdin);
    fgets(producto_buscado, 51, stdin);
    producto_buscado[strcspn(producto_buscado, "\n")] = '\0';

    buscador_un_producto(productos, tamanio, producto_buscado);

    char id_modificar[8];
    printf("\nIntroduce el ID del producto que quieres modificar: ");
    fgets(id_modificar, 8, stdin);
    id_modificar[strcspn(id_modificar, "\n")] = '\0';

    // SI NO ES ADMIN HAY Q COMPROBAR QUE LA ID DEL PRODUCTO SEA LA MISMA QUE LA ID DEL QUE ESTA HACIENDO LA MODIFICACION -> ES UNA FUNCION NUEVA PERO IGUAL QUE ESTA
    if (productoEsDeProveedor(productos, tamanio, idProv, id_modificar) == 1 || strcmp(idProv, "-1") == 0)
    {

        printf("----------\n");
        printf("(1) Modificar descripcion\n");
        printf("(2) Modificar precio\n");
        printf("(3) Modificar stock\n");
        printf("(4) Modificar entrega\n");
        scanf("%d", &a);
        flushInputBufferr();
        printf("----------\n\n");

        switch (a)
        {
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
    else
    {
        printf("Ese producto no es suyo.\n");
    }
}

void modificar_descripcion_prod(Producto **productos, int *tamanio, char *id_modificar)
{

    int i = 0;

    while ((i + 1) < *tamanio && strcmp((*productos)[i].id_prod, id_modificar) != 0)
    {
        i++; // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    printf("Escribe la nueva descripcion: ");
    fgets((*productos)[i].descrip, 51, stdin);
    (*productos)[i].descrip[strcspn((*productos)[i].descrip, "\n")] = '\0';
}

void modificar_precio(Producto **productos, int *tamanio, char *id_modificar)
{

    int i = 0;

    while (i < *tamanio && strcmp((*productos)[i].id_prod, id_modificar) != 0)
    {
        i++; // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    printf("Introduce el nuevo importe: ");
    fflush(stdin);
    scanf("%f", &(*productos)[i].importe);
    flushInputBufferr();
}

void modificar_stock(Producto **productos, int *tamanio, char *id_modificar)
{

    int i = 0;

    while (i < *tamanio && strcmp((*productos)[i].id_prod, id_modificar) != 0)
    {
        i++; // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    printf("Cantidad de productos en stock: ");
    fflush(stdin);
    scanf("%d", &(*productos)[i].stock);
    flushInputBufferr();
}

void modificar_entrega(Producto **productos, int *tamanio, char *id_modificar)
{

    int i = 0;

    while (i < *tamanio && strcmp((*productos)[i].id_prod, id_modificar) != 0)
    {
        i++; // El objetivo del bucle es encontrar la posicion del id del producto que se quiere modificar.
    }

    printf("Nueva fecha maxima de entrega: ");
    fflush(stdin);
    scanf("%d", &(*productos)[i].entrega);
    flushInputBufferr();
}

void listarProductosPorCategoria(Producto **productos, int *numProductos, Categoria **categorias, int *numCategorias) {

    for (int i = 0; i < *numCategorias; i++) {
        printf("Categoria: %s - %s\n", (*categorias)[i].id_categ, (*categorias)[i].descrip);
        int encontrados = 0;
        for (int j = 0; j < *numProductos; j++) {
            if (strcmp((*productos)[j].id_categ, (*categorias)[i].id_categ) == 0) {
                encontrados = 1;
                printf("ID del producto: %s\n", (*productos)[j].id_prod);
                printf("Nombre: %s\n", (*productos)[j].nombre);
                printf("Descripcion: %s\n", (*productos)[j].descrip);
                printf("Stock: %d\n", (*productos)[j].stock);
                printf("Tiempo de entrega: %d\n", (*productos)[j].entrega);
                printf("Importe: %.2f\n", (*productos)[j].importe);
                printf("\n");
            }
        }
        if (!encontrados) {
            printf("No hay productos asociados a esta categoría.\n");
        }
    }
}

Producto* agregar_a_cesta(Producto **catalogo, int *num_productos, float *coste, int *tamLista) {
    int capacidad = 1;
    int num_seleccionados = 0;
    Producto *cesta = malloc(capacidad * sizeof(Producto));
    float precio = 0;

    char nombre_producto[16];
    while (1) {
        printf("Ingrese el nombre del producto que desea agregar a la cesta (o escriba 'fin' para salir): ");
        fgets(nombre_producto, 16, stdin);
        nombre_producto[strcspn(nombre_producto, "\n")] = '\0';
        if (strcmp(nombre_producto, "fin") == 0) {
            break;
        }

        // Buscar el producto en el catálogo
        int i;
        for (i = 0; i < *num_productos; i++) {
            if (strcmp((*catalogo)[i].nombre, nombre_producto) == 0) {
                // Agregar el producto a la cesta
                if (num_seleccionados == capacidad) {
                    // Aumentar la capacidad de la cesta si es necesario
                    capacidad += 1;
                    cesta = realloc(cesta, capacidad * sizeof(Producto));
                }
                cesta[num_seleccionados] = (*catalogo)[i];
                num_seleccionados++;
                precio += (*catalogo)[i].importe;
                break;
            }
        }
    }

    capacidad--;
    *tamLista = capacidad;
    cesta = realloc(cesta, capacidad * sizeof(Producto));
    *coste = precio;

    return cesta;
}
