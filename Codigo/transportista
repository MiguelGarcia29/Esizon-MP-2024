#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char id_transp[5];
    char nombre[21];
    char email[31];
    char contrasenia[16];
    char nombre_empresa[21];
    char ciudad_reparto[21];
} Transportista;

typedef struct {
    char id_pedido[8];
    char id_prod[8];
    int num_unid;
    char fecha_entrega_prevista[11];
    float importe;
    char estado_pedido[15]; // "enPreparacion", "enviado", "enReparto", "enLocker", "entregado", "devuelto", "transportista"
    char id_transp[5];
    char id_locker[11];
    char cod_locker[11];
    char fecha_entrega_devolucion_transp[11];
} ProductoPedido;

void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Función para generar un ID único
char* id_generator(Transportista *t, int tamanio_vector) {
    int id_generada = 1;

    // Si hay transportistas en el vector, obtiene el último ID y genera uno nuevo incrementándolo
    if (tamanio_vector != 0) {
        id_generada = atoi(t[tamanio_vector - 1].id_transp) + 1;
    }

    // Asigna memoria para el ID generado
    char* id = malloc(5 * sizeof(char));
    if (id == NULL) {
        printf("Error al asignar memoria. \n");
        exit(EXIT_FAILURE);
    }

    // Formatea la nueva ID y la guarda en el arreglo
    sprintf(id, "%04d", id_generada); 

    return id;
}

// Función para dar de alta un nuevo transportista
void alta_transportista(Transportista **t, int* tamanio_vector){

    Transportista nuevo_transportista;
    // Genera un nuevo ID para el transportista
    char *cadena = id_generator(*t, *tamanio_vector); 
    strcpy(nuevo_transportista.id_transp, cadena);
    free(cadena); // Libera la memoria asignada para el ID generado
    
    // Solicita al usuario información sobre el nuevo transportista
    printf("\nDime el nombre:");
    scanf("%20s", nuevo_transportista.nombre);
    flushInputBuffer();

    printf("\nDime el correo:");
    scanf("%30s", nuevo_transportista.email);
    flushInputBuffer();

    printf("\nDime la contraseña para acceder al sistema:");
    scanf("%15s", nuevo_transportista.contrasenia);
    flushInputBuffer();
    
    printf("\nDime el nombre de la empresa:");
    scanf("%20s", nuevo_transportista.nombre_empresa);
    flushInputBuffer();
    
    printf("\nDime la ciudad de reparto:");
    scanf("%20s", nuevo_transportista.ciudad_reparto);
    flushInputBuffer();
    
    // Realiza una realocación de memoria para agregar el nuevo transportista al arreglo
    *t = (Transportista *)realloc(*t, (*tamanio_vector + 1) * sizeof(Transportista));
    if (*t == NULL) {
        printf("Error al asignar memoria. \n");
        exit(EXIT_FAILURE);
    }
    (*t)[*tamanio_vector] = nuevo_transportista; // Guarda el nuevo transportista en el arreglo
    (*tamanio_vector)++;
}

void baja_transportista(Transportista *t , int* tamanio, char *id_baja){

    int encontrado = 0;

    // Busca el transportista con el ID dado y lo elimina del arreglo
    for(int i = 0 ; i < *tamanio ; i++) {
        if(strcmp(t[i].id_transp, id_baja) == 0){
            encontrado = 1;

            // Reorganiza el arreglo para eliminar el transportista encontrado
            for(int j = i; j < *tamanio - 1; j++) {
                t[j] = t[j + 1];
            }

            (*tamanio)--; // Reduce el tamaño del arreglo
            printf("Transportista con ID %s ha sido dado de baja correctamente.\n", id_baja);
            break; // Sale del bucle una vez encontrado y eliminado el transportista
        }
    }

    if(encontrado == 0){
        printf("La ID registrada no ha sido encontrada.\n");
    }
}

// Función para mostrar un listado de todos los transportistas dados de alta
void listado_transportista(Transportista *t, int tamanio){

    // Recorre el arreglo de transportistas y muestra la información de cada uno
    for(int i = 0 ; i < tamanio ; i++){
        printf("%s-%s-%s-%s-%s-%s\n", t[i].id_transp, t[i].nombre, t[i].email, t[i].contrasenia, t[i].nombre_empresa, t[i].ciudad_reparto);
    }
}

// Función para mostrar el perfil de un transportista y permitir su modificación
void perfil(Transportista *t, int tamanio, char *id)
{
    int indice = -1;
    for(int i=0;i<tamanio;i++)
    {
        if(strcmp(id, t[i].id_transp) == 0)
        {
            printf("%s-%s-%s-%s-%s-%s\n", t[i].id_transp, t[i].nombre, t[i].email, t[i].contrasenia, t[i].nombre_empresa, t[i].ciudad_reparto);
            indice = i;
            break;
        }
    }

    if(indice != -1)
    {
        printf("¿Quieres modificar este perfil? \n");
        printf("1-Si\n");
        printf("2-No\n");
        int respuesta;
        scanf("%d", &respuesta);
        flushInputBuffer();

        if(respuesta == 1)
        {
            printf("\nDime el nombre:");
            scanf("%20s", t[indice].nombre);
            flushInputBuffer();

            printf("\nDime el correo:");
            scanf("%30s", t[indice].email);
            flushInputBuffer();

            printf("\nDime la contraseña para acceder al sistema:");
            scanf("%15s", t[indice].contrasenia);
            flushInputBuffer();
    
            printf("\nDime el nombre de la empresa:");
            scanf("%20s", t[indice].nombre_empresa);
            flushInputBuffer();
    
            printf("\nDime la ciudad de reparto:");
            scanf("%20s", t[indice].ciudad_reparto);
            flushInputBuffer();
        }
    }
    else
    {
        printf("Transportista con ID %s no encontrado.\n", id);
    }
}

// Función para realizar el reparto de productos por parte del transportista
void reparto(ProductoPedido *pedidos, int num_pedidos, char *id_transp) {
    // Mostrar los productos asignados para el reparto del transportista dado
    printf("Productos asignados para reparto:\n");
    for (int i = 0; i < num_pedidos; i++) {
        if (strcmp(pedidos[i].id_transp, id_transp) == 0 && strcmp(pedidos[i].estado_pedido, "enReparto") == 0) {
            printf("ID Pedido: %s\n", pedidos[i].id_pedido);
            printf("ID Producto: %s\n", pedidos[i].id_prod);
            printf("Cantidad: %d\n", pedidos[i].num_unid);
            printf("Fecha de entrega prevista: %s\n", pedidos[i].fecha_entrega_prevista);
            printf("Importe: %.2f\n", pedidos[i].importe);
            printf("-------------------------------------\n");
        }
    }

    // Lógica de reparto (marcar como entregado, actualizar estado, etc.)
    // Aquí puedes implementar la lógica para el reparto de productos
    // Por ejemplo, podrías pedir al transportista que ingrese el ID del pedido
    // que está entregando y luego actualizar el estado del pedido a "entregado".
    // También podrías considerar actualizar el stock de los productos entregados, etc.
}


int main() {
    Transportista *transportistas = NULL;
    int num_transportistas = 0;
    int opcion;
    char id[5];

    do {
        printf("\nMenú de opciones:\n");
        printf("1. Alta de transportista\n");
        printf("2. Baja de transportista\n");
        printf("3. Listado de transportistas\n");
        printf("4. Perfil de transportista\n");
        printf("5. Reparto de productos\n");
        printf("6. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);
        flushInputBuffer(); // Limpia el buffer de entrada

        switch (opcion) {
            case 1:
                alta_transportista(&transportistas, &num_transportistas);
                break;
            case 2:
                printf("Ingrese el ID del transportista a dar de baja: ");
                scanf("%4s", id);
                flushInputBuffer(); // Limpia el buffer de entrada
                baja_transportista(transportistas, &num_transportistas, id);
                break;
            case 3:
                printf("\nListado de transportistas:\n");
                listado_transportista(transportistas, num_transportistas);
                break;
            case 4:
                printf("Ingrese el ID del transportista para ver/modificar su perfil: ");
                scanf("%4s", id);
                flushInputBuffer(); // Limpia el buffer de entrada
                perfil(transportistas, num_transportistas, id);
                break;
            case 5:
                printf("Ingrese el ID del transportista para realizar el reparto de productos: ");
                scanf("%4s", id);
                flushInputBuffer(); // Limpia el buffer de entrada
                reparto(productos_pedidos, num_productos_pedidos, id);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Por favor, elija una opción válida del menú.\n");
                break;
        }
    } while (opcion != 6);

    // Liberar memoria asignada para el arreglo de transportistas
    free(transportistas);

    return 0;
}
