#include "Transportista.h"

char* id_generator_trans(Transportista *t, int tamanio_vector) {
    int id_generada = 1;

    if (tamanio_vector != 0) {
        id_generada = atoi(t[tamanio_vector - 1].id_transp) + 1;
    }

    char* id = malloc(5 * sizeof(char));
    if (id == NULL) {
        printf("Error al asignar memoria. \n");
        exit(EXIT_FAILURE);
    }

    sprintf(id, "%04d", id_generada);

    return id;
}

void alta_transportista(Transportista **t, int* tamanio_vector){

    Transportista nuevo_transportista;
    char *cadena = id_generator_trans(*t, *tamanio_vector);
    strcpy(nuevo_transportista.id_transp, cadena);
    free(cadena);

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

    *t = (Transportista *)realloc(*t, (*tamanio_vector + 1) * sizeof(Transportista));
    if (*t == NULL) {
        printf("Error al asignar memoria. \n");
        exit(EXIT_FAILURE);
    }
    (*t)[*tamanio_vector] = nuevo_transportista;
    (*tamanio_vector)++;
}

void baja_transportista(Transportista *t , int* tamanio, char *id_baja){

    int encontrado = 0;

    for(int i = 0 ; i < *tamanio ; i++) {
        if(strcmp(t[i].id_transp, id_baja) == 0){
            encontrado = 1;
            for(int j = i; j < *tamanio - 1; j++) {
                t[j] = t[j + 1];
            }
            (*tamanio)--;
            printf("Transportista con ID %s ha sido dado de baja correctamente.\n", id_baja);
            break;
        }
    }

    if(encontrado == 0){
        printf("La ID registrada no ha sido encontrada.\n");
    }
}

void listado_transportista(Transportista *t, int tamanio){

    printf("ID Transportista - Nombre - Email - Contraseña - Nombre de la empresa - Ciudad de reparto\n");
    for(int i = 0 ; i < tamanio ; i++){
        printf("%s - %s - %s - %s - %s - %s\n", t[i].id_transp, t[i].nombre, t[i].email, t[i].contrasenia, t[i].nombre_empresa, t[i].ciudad_reparto);
    }
}


void mostrar_perfiltrans(Transportista perfil) //funcion que imprime los datos del usuario
{
	printf("Rol: Transportista\n");
	printf("Empresa: %s\n",perfil.nombre_empresa);
	printf("Ciudad de reparto: %s\n",perfil.ciudad_reparto);
	printf("Email: %s\n",perfil.email);
	printf("__________\n");
}
void cambiar_contrasenia_trans(char nueva[16]) // funcion que cambia la contrasenia
{
	printf("Introduzca su nueva contrasena: ");
	fflush(stdin);
	fgets(nueva,16,stdin);
}


void cambiar_email_trans(char nuevo[31]) //funcion que cambia el email
{
	printf("Introduzca el nuevo email: ");
	fflush(stdin);
	fgets(nuevo,31,stdin);
}

void modificar_perfiltrnas(Transportista *mod) //funcion con un menu segun que se quiera modificar
{
	int a;

	printf("(1) Cambiar contrasena\n");
	printf("(2) Cambiar email\n");
	fflush(stdin);
	scanf("%d",&a);

		switch(a)
		{
			case 1:
				cambiar_contrasenia_trans(mod->contrasenia); //Si pulsa 1 se camabiara la contrasenia
			break;

			case 2:
				cambiar_email_trans(mod->email); // Si pulsa 2 se cambia el email
			break;

			default:
			break;
		}
}

void reparto(ProductoPedido *pedidos, int num_pedidos, char *id_transp) {
    int indice=0;
    for (int i = 0; i < num_pedidos; i++) {
        if (strcmp(pedidos[i].id_transp, id_transp) == 0 && strcmp(pedidos[i].estado_pedido, "enReparto") == 0) {
        	printf("Productos asignados para reparto:\n");
            printf("ID Pedido: %s\n", pedidos[i].id_pedido);
            printf("ID Producto: %s\n", pedidos[i].id_prod);
            printf("Cantidad: %d\n", pedidos[i].num_unid);
            printf("Fecha de entrega prevista: %s\n", pedidos[i].fecha_entrega_prevista);
            printf("Importe: %.2f\n", pedidos[i].importe);
            printf("-------------------------------------\n");
            indice=1;
        }
    }
    if(indice!=1)
    {
    	printf("No se han encontrado pedidos asignados a esa ID\n");
	}
}

void fecha_caducidad(char *fecha)
{
	time_t rawtime;
    struct tm *info;

    // Obtener la fecha y hora actual
    time(&rawtime);
    info = localtime(&rawtime);

    // Sumar 7 días
    rawtime += 7 * 24 * 60 * 60; // 7 días en segundos

    // Actualizar la estructura tm
    info = localtime(&rawtime);

    strftime(fecha, 11, "%d/%m/%Y", info);
}

void entrega(ProductoPedido *pedidos, CompartimentoLocker *comportamiento, int num_pedidos, int tamanio_compartimento , char *id_transp)
{
    printf("Dime la id del producto que quieres entregar: ");
    char id_producto[8];
    scanf("%s", id_producto);
    flushInputBuffer();
    int encontrado = 0;
    for(int i=0;i<num_pedidos && encontrado!=1 ;i++)
    {
        if(strcmp(pedidos[i].id_prod, id_producto) == 0 && strcmp(pedidos[i].id_transp, id_transp) == 0)
        {
            encontrado = 1;
            printf("Donde lo quieres entregar: \n");
            printf("1-Locker\n");
            printf("2-Domicilio\n");
            int entrega;
            scanf("%d", &entrega);
            flushInputBuffer();
            switch(entrega)
            {
                case 1:
                    for(int j=0;j<tamanio_compartimento;j++)
                    {
                        if(strcmp(pedidos[i].id_locker, comportamiento[j].id_locker)==0 && strcmp(comportamiento[j].estado, "vacío")==0)
                        {
                            printf("Dime el código numerico asignado al locker (10 digitos): ");
                            char contrasenia_locker[11];
                            scanf("%s", contrasenia_locker);
                            strcpy(pedidos[i].cod_locker, contrasenia_locker);
                            strcpy(comportamiento[j].cod_locker, contrasenia_locker);
                            strcpy(comportamiento[j].estado, "ocupado");
                            char fecha[11];
                            obtener_fecha_actual(fecha);
                            strcpy(comportamiento[j].fecha_ocupacion, fecha);
                            printf("Producto entregado exitosamente en el locker.\n");
                            char fecha_vencimiento[11];
                            fecha_caducidad(fecha_vencimiento);
                            strcpy(comportamiento[j].fecha_caducidad, fecha_vencimiento);
                            break;
                        }
                    }
                    break;
                case 2:
                    printf("Producto entregado exitosamente en el domicilio.\n");
                    strcpy(pedidos[i].estado_pedido, "entregado");
                    break;
                default:
                    printf("Esa opción no se contempla.\n");
                    break;
            }
            break;
        }
    }

    if(encontrado == 0)
    {
        printf("No se encuentra esa ID de producto asociada al transportista.\n");
    }
}
/*
int main() {
    Transportista *transportistas = NULL;
    int num_transportistas = 0;
    int opcion;
    char id[5];

    ProductoPedido productos_pedidos[100];
    ComportamientoLocker comportamiento_locker[100];
    int num_productos_pedidos = 0;

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
        flushInputBuffer();

        switch (opcion) {
            case 1:
                alta_transportista(&transportistas, &num_transportistas);
                break;
            case 2:
                printf("Ingrese el ID del transportista a dar de baja: ");
                scanf("%4s", id);
                flushInputBuffer();
                baja_transportista(transportistas, &num_transportistas, id);
                break;
            case 3:
                printf("\nListado de transportistas:\n");
                listado_transportista(transportistas, num_transportistas);
                break;
            case 4:
                printf("Ingrese el ID del transportista para ver/modificar su perfil: ");
                scanf("%4s", id);
                flushInputBuffer();
                perfil(transportistas, num_transportistas, id);
                break;
            case 5:
                printf("Ingrese el ID del transportista para realizar el reparto de productos: ");
                scanf("%4s", id);
                flushInputBuffer();
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

    free(transportistas);

    return 0;
}
*/

// Guarda el vector de Transportitas en el archivo siguiendo la estructura:
/*
    o Identificador del transportista (Id_transp), 4 dígitos.
    o Nombre del transportista (Nombre), 20 caracteres máximo.
    o Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la
    plataforma.
    o Contraseña para acceder al sistema (Contraseña), con 15 caracteres máximo.
    o Nombre de la empresa (Nombre), 20 caracteres máximo.
    o Ciudad de reparto (Ciudad), 20 caracteres máximo.
*/
void guardarTransportistasEnArchivo(Transportista *transportistas, int numTransportistas)
{
    FILE *archivo = fopen(Transportistas_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo Transportistas.txt.\n");
        return;
    }

    for (int i = 0; i < numTransportistas; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%s-%s-\n",
                transportistas[i].id_transp,
                transportistas[i].nombre,
                transportistas[i].email,
                transportistas[i].contrasenia,
                transportistas[i].nombre_empresa,
                transportistas[i].ciudad_reparto);
    }

    fclose(archivo);
    printf("Datos de transportistas guardados en el archivo Transportistas.txt.\n");
}

Transportista *iniciarTransportistasDeArchivo(int *numTransportista)
{
    FILE *archivo = fopen(Transportistas_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Transportistas_txt);
        return NULL;
    }

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de Locker
    Transportista *transportistas = (Transportista *)malloc(count * sizeof(Transportista));
    if (transportistas == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de Transportistas.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(transportistas[i].id_transp, token, sizeof(transportistas[i].id_transp));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].nombre, token, sizeof(transportistas[i].nombre));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].email, token, sizeof(transportistas[i].email));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].contrasenia, token, sizeof(transportistas[i].contrasenia));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].nombre_empresa, token, sizeof(transportistas[i].nombre_empresa));
        token = strtok(NULL, "-");
        strncpy(transportistas[i].ciudad_reparto, token, sizeof(transportistas[i].ciudad_reparto));

        i++;
    }

    fclose(archivo);
    *numTransportista = count;
    return transportistas;
}
