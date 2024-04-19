#include "AdminProv.h"

char* id_generator(AdminProv *a, int tamanio_vector) {
    int id_generada = 1;

    // Si hay elementos en el vector, obtiene el último ID y genera uno nuevo incrementándolo
    if (tamanio_vector != 0) {
        id_generada = atoi(a[tamanio_vector - 1].id_empresa) + 1;
    }

    // Asigna memoria para el ID generado
    char* id = malloc(5 * sizeof(char));
    if (id == NULL) {
        printf("Error al asignar memoria. \n");
        exit(EXIT_FAILURE);
    }

    // Formatea la nueva ID y la guarda en el arreglo
    sprintf(id, "%03d", id_generada);

    return id;
}


void alta_AdminProv(AdminProv **l, int* tamanio_vector) {
    AdminProv nuevo_adminprov;
    // Genera un nuevo ID para el locker
    char *cadena = id_generator(*l, *tamanio_vector);
    strcpy(nuevo_adminprov.id_empresa, cadena);
    free(cadena); // Libera la memoria asignada para el ID generado

    // Solicita al usuario información sobre el nuevo locker
    int respuesta;
    printf("\nSeleccione nuevo rol:");
    printf("\n1-Administrador");
    printf("\n2-Proveedor\n");
    scanf("%d", &respuesta);
   switch(respuesta)
   {
   		case 1:
		   	strcpy(nuevo_adminprov.nombre, "ESIZON");
		   	strcpy(nuevo_adminprov.perfil_usuario, "administrador");
		   	break;

		case 2:
			printf("Dime el nombre de la empresa:\n");
			char empresa[20];
			scanf("%s", empresa);
			strcpy(nuevo_adminprov.nombre, empresa);
			strcpy(nuevo_adminprov.perfil_usuario, "proveedor");
			fflush(stdin);
			break;
		default:
			printf("Esa opcion es incorrecta\n");
   }

    printf("\nDime tu correo electronico:");
    scanf("%30s", nuevo_adminprov.email);
    fflush(stdin);

	printf("\nDime tu contrasenia:");
    scanf("%16s", nuevo_adminprov.contrasenia);
    fflush(stdin);

    // Realiza una realocación de memoria para agregar el nuevo locker al arreglo
    *l = (AdminProv *)realloc(*l, (*tamanio_vector + 1) * sizeof(AdminProv));
    if (*l == NULL) {
        printf("Error al asignar memoria para el nuevo locker. \n");
        exit(EXIT_FAILURE);
    }
    (*l)[*tamanio_vector] = nuevo_adminprov; // Guarda el nuevo locker en el arreglo
    (*tamanio_vector)++;
}

void baja_adminprov(AdminProv *l, int* tamanio, char *id_baja) {
    int encontrado = 0;

    // Busca el locker con el ID dado y lo elimina del arreglo
    for (int i = 0; i < *tamanio; i++) {
        if (strcmp(l[i].id_empresa, id_baja) == 0) {
            encontrado = 1;

            // Reorganiza el arreglo para eliminar el locker encontrado
            for (int j = i; j < *tamanio - 1; j++) {
                l[j] = l[j + 1];
            }

            (*tamanio)--; // Reduce el tamaño del arreglo
            printf("Ha sido dado de baja correctamente.\n", id_baja);
            break; // Sale del bucle una vez encontrado y eliminado el locker
        }
    }

    if (encontrado == 0) {
        printf("La ID registrada no ha sido encontrada.\n");
    }
}

void listado_adminprov(AdminProv *l, int tamanio) {
    // Recorre el arreglo de lockers y muestra la información de cada uno
    for (int i = 0; i < tamanio; i++) {
        printf("%s-%s-%s-%s-%s\n", l[i].id_empresa, l[i].nombre, l[i].email, l[i].contrasenia, l[i].perfil_usuario);
    }
}

// Guarda el vector de AdminYProvs en el archivo siguiendo la estructura:
/*
    o Identificador de la empresa administradora o proveedora (Id_empresa), 4 digitos.
    o Nombre de la empresa (Nombre), seria ESIZON si es administrador, 20 caracteres maximo.
    o Email (email), 30 caracteres maximo, sera usado como nombre de usuario para el acceso a la
    plataforma.
    o Contrasenia para acceder al sistema (Contrasenia), con 15 caracteres maximo.
    o Perfil del usuario (Perfil_usuario): «administrador» o «proveedor».
*/
void guardarAdminProvEnArchivo(AdminProv *admins, int numAdmins)
{
    FILE *archivo = fopen(AdminProv_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", AdminProv_txt);
        return;
    }

    for (int i = 0; i < numAdmins; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%s-\n",
                admins[i].id_empresa,
                admins[i].nombre,
                admins[i].email,
                admins[i].contrasenia,
                admins[i].perfil_usuario);
    }

    fclose(archivo);
}

void *iniciarAdminProvDeArchivo(int *numAdmins,AdminProv **pr)
{
    FILE *archivo = fopen(AdminProv_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", AdminProv_txt);
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

    // Crear el vector de adminProv
    AdminProv *adminProvs = (AdminProv *) malloc(count * sizeof(AdminProv));
    if (adminProvs == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de AdminProv.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(adminProvs[i].id_empresa, token, sizeof(adminProvs[i].id_empresa));
        token = strtok(NULL, "-");
        strncpy(adminProvs[i].nombre, token, sizeof(adminProvs[i].nombre));
        token = strtok(NULL, "-");
        strncpy(adminProvs[i].email, token, sizeof(adminProvs[i].email));
        token = strtok(NULL, "-");
        strncpy(adminProvs[i].contrasenia, token, sizeof(adminProvs[i].contrasenia));
        token = strtok(NULL, "-");
        strncpy(adminProvs[i].perfil_usuario, token, sizeof(adminProvs[i].perfil_usuario));
        i++;
    }

    fclose(archivo);
    *numAdmins = count;
    *pr = adminProvs;
}

/*
int main() {
    AdminProv *administradores_proveedores = NULL;
    int tamano_admin_prov = 0;
    int opcion;
    char id_baja[5];

    do {
        printf("\n1. Alta de administrador/proveedor");
        printf("\n2. Baja de administrador/proveedor");
        printf("\n3. Listado de administradores/proveedores");
        printf("\n4. Salir");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                alta_AdminProv(&administradores_proveedores, &tamano_admin_prov);
                break;
            case 2:
                printf("Ingrese el ID del administrador/proveedor a dar de baja: ");
                scanf("%s", id_baja);
                baja_adminprov(administradores_proveedores, &tamano_admin_prov, id_baja);
                break;
            case 3:
                listado_adminprov(administradores_proveedores, tamano_admin_prov);
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida. Por favor, seleccione una opción válida.\n");
        }
    } while(opcion != 4);

    // Liberar la memoria asignada para el arreglo de administradores/proveedores
    free(administradores_proveedores);

    return 0;
}*/
