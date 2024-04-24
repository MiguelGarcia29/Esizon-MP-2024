#include "cliente.h"

// Función para mostrar los detalles de un cliente
void mostrar_cliente(Cliente client)
{
    printf("\nHola %s\n",client.nomb_cliente);
    printf("Direccion: %s, %s, %s\n",client.dir_cliente,client.localidad,client.provincia);
    printf("Email: %s\n",client.email);
    printf("Saldo: %.2f\n",client.cartera);
    printf("----------\n\n");
}

// Función para que un cliente cambie su perfil
void cambiar_perfil_cliente(Cliente *client)
{
    int a;
    printf("(1) Cambiar direccion\n");
    printf("(2) Cambiar email\n");
    printf("(3) Cambiar contrasenia\n");
    printf("(4) Acceder a mi cartera\n");
    scanf("%d",&a);
    printf("----------\n\n");
    switch(a)
    {
        case(1):
            cambiar_direccion_cliente(client->dir_cliente, client->provincia, client->localidad);
        break;
        case (2):
            cambiar_email_cliente(client->email);
        break;
        case (3):
            cambiar_contrasenia_cliente(client->contrasenia);
        break;
        case (4):
            cartera(&client->cartera);
        break;
        default:
            printf("Error\n\n");
        break;
    }
}

// Función para cambiar la contraseña de un cliente
void cambiar_contrasenia_cliente(char nueva[16])
{
    printf("Introduzca su nueva contrasenia: ");
    fgets(nueva,16,stdin);
    nueva[strcspn(nueva, "\n")] = '\0';
}

// Función para cambiar el email de un cliente
void cambiar_email_cliente(char nuevo[31])
{
    printf("Introduzca el nuevo email: ");
    fgets(nuevo,31,stdin);
    nuevo[strcspn(nuevo, "\n")] = '\0';
}

// Función para cambiar la dirección de un cliente
void cambiar_direccion_cliente(char direccion[51], char provincia[21], char localidad[21])
{
    printf("Provincia: ");
    fgets(provincia,21,stdin);
    provincia[strcspn(provincia, "\n")] = '\0';
    printf("Localidad: ");
    fgets(localidad,21,stdin);
    localidad[strcspn(localidad,"\n")] = '\0';
    printf("Direccion: ");
    fgets(direccion,51,stdin);
    direccion[strcspn(direccion,"\n")] = '\0';
}

// Función para verificar la contraseña de un cliente
int corroborar_contrasenia(char cad[16])
{
    char verificacion[16];
    int a;
    printf("Contrasenia: ");
    fgets(verificacion,16,stdin);
    verificacion[strcspn(verificacion, "\n")] = '\0';
    a = strcmp(verificacion,cad);
    return a;
}

// Función para manejar la cartera de un cliente
void cartera(float *saldo)
{
    int a;
    printf("(1) Anadir saldo\n");
    printf("(2) Extraer saldo\n");
    scanf("%d",&a);
    switch(a)
    {
        case 1:
            anadir_saldo(saldo);
        break;
        case 2:
            extraer_saldo(saldo);
        break;
        default:
            printf("Error");
        break;
    }
}

// Función para añadir saldo a la cartera de un cliente
void anadir_saldo(float *saldo)
{
    float a;
    printf("Cantidad de dinero a anadir: ");
    scanf("%f",&a);
    *saldo = *saldo + a;
}

// Función para extraer saldo de la cartera de un cliente
void extraer_saldo(float *saldo)
{
    float a;
    printf("Cantidad de dinero a extraer: ");
    scanf("%f",&a);
    if (*saldo - a <= 0)
    {
        printf("No hay saldo suficiente\n");
    }
    else
    {
        *saldo = *saldo - a;
    }
}

// Función para guardar los clientes en un archivo
void guardarClientesEnArchivo(Cliente *clientes, int numClientes)
{
    FILE *archivo = fopen(Clientes_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Clientes_txt);
        return;
    }

    for (int i = 0; i < numClientes; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%s-%s-%s-%.2f\n",
                clientes[i].id_cliente,
                clientes[i].nomb_cliente,
                clientes[i].dir_cliente,
                clientes[i].localidad,
                clientes[i].provincia,
                clientes[i].email,
                clientes[i].contrasenia,
                clientes[i].cartera);
    }

    fclose(archivo);
}

// Función para iniciar los clientes desde un archivo
Cliente *iniciarClientesDeArchivo(int *numClientes)
{
    FILE *archivo = fopen(Clientes_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Clientes_txt);
        return NULL;
    }

    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA];
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    rewind(archivo);

    Cliente *clientes = (Cliente *)malloc(count * sizeof(Cliente));
    if (clientes == NULL)
    {
        fclose(archivo);
        printf("No se pudo asignar memoria para el vector de clientes.\n");
        return NULL;
    }

    int i = 0;
    for(i=0;i<count;i++)
    {
        if(fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL){
        char *token = strtok(buffer, "-");
        strncpy(clientes[i].id_cliente, token, sizeof(clientes[i].id_cliente));
        token = strtok(NULL, "-");
        strncpy(clientes[i].nomb_cliente, token, sizeof(clientes[i].nomb_cliente));
        token = strtok(NULL, "-");
        strncpy(clientes[i].dir_cliente, token, sizeof(clientes[i].dir_cliente));
        token = strtok(NULL, "-");
        strncpy(clientes[i].localidad, token, sizeof(clientes[i].localidad));
        token = strtok(NULL, "-");
        strncpy(clientes[i].provincia, token, sizeof(clientes[i].provincia));
        token = strtok(NULL, "-");
        strncpy(clientes[i].email, token, sizeof(clientes[i].email));
        token = strtok(NULL, "-");
        strncpy(clientes[i].contrasenia, token, sizeof(clientes[i].contrasenia));
        token = strtok(NULL, "-");
        clientes[i].cartera = atof(token);
        }
    }

    fclose(archivo);
    *numClientes = count;
    return clientes;
}

// Función para generar un ID para un cliente
char *id_generator_cl(Cliente **clientes, int *tamanio_vector)
{
    int id_generada = 1;
    if (*tamanio_vector != 0)
    {
        id_generada = atoi((*clientes)[*tamanio_vector - 1].id_cliente);
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

// Función para dar de alta un nuevo cliente
void altaCliente(Cliente **clientes, int *numClientes) {
    Cliente nuevoCliente;
    strcpy(nuevoCliente.id_cliente, id_generator_cl(clientes, numClientes));

    printf("Ingrese el nombre del cliente: ");
    fgets(nuevoCliente.nomb_cliente, 21, stdin);
    nuevoCliente.nomb_cliente[strcspn(nuevoCliente.nomb_cliente, "\n")] = '\0';

    printf("Ingrese la dirección del cliente: ");
    fgets(nuevoCliente.dir_cliente, 51, stdin);
    nuevoCliente.dir_cliente[strcspn(nuevoCliente.dir_cliente, "\n")] = '\0';

    printf("Ingrese la localidad del cliente: ");
    fgets(nuevoCliente.localidad, 21, stdin);
    nuevoCliente.localidad[strcspn(nuevoCliente.localidad, "\n")] = '\0';

    printf("Ingrese la provincia del cliente: ");
    fgets(nuevoCliente.provincia, 21, stdin);
    nuevoCliente.provincia[strcspn(nuevoCliente.provincia, "\n")] = '\0';

    printf("Ingrese el email del cliente: ");
    fgets(nuevoCliente.email, 31, stdin);
    nuevoCliente.email[strcspn(nuevoCliente.email, "\n")] = '\0';

    printf("Ingrese la contraseña del cliente: ");
    fgets(nuevoCliente.contrasenia, 16, stdin);
    nuevoCliente.contrasenia[strcspn(nuevoCliente.contrasenia, "\n")] = '\0';

    printf("Ingrese el saldo de la cartera del cliente: ");
    scanf("%f", &nuevoCliente.cartera);
    flushInputBuffer();

    *clientes = (Cliente *)realloc(*clientes, ((*numClientes) + 1) * sizeof(Cliente));
    if (*clientes == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    (*clientes)[*numClientes] = nuevoCliente;
    (*numClientes)++;
}

// Función para dar de baja un cliente
void bajaCliente(Cliente **clientes, int *numClientes) {
    char id[8];
    int encontrado = 0;
    printf("Ingrese el ID del cliente a buscar: ");
    fgets(id, 8, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *numClientes; i++) {
        if (strcmp((*clientes)[i].id_cliente, id) == 0) {
            encontrado = 1;
            for (int j = i; j < *numClientes - 1; j++) {
                (*clientes)[j] = (*clientes)[j + 1];
            }
            *clientes = (Cliente *)realloc(*clientes, ((*numClientes) - 1) * sizeof(Cliente));
            if (*clientes == NULL) {
                printf("Error al liberar memoria.\n");
                exit(1);
            }
            (*numClientes)--;
            printf("Cliente eliminado exitosamente.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Cliente no encontrado.\n");
    }
}

// Función para buscar un cliente por ID
void buscarCliente(Cliente **clientes, int *numClientes) {
    char id[8];
    int encontrado = 0;
    printf("Ingrese el ID del cliente a buscar: ");
    fgets(id, 8, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *numClientes; i++) {
        if (strcmp((*clientes)[i].id_cliente, id) == 0) {
            encontrado = 1;
            printf("Cliente encontrado:\n");
            printf("ID: %s, Nombre: %s, Dirección: %s, Localidad: %s, Provincia: %s, Email: %s, Cartera: %.2f\n",
                   (*clientes)[i].id_cliente, (*clientes)[i].nomb_cliente, (*clientes)[i].dir_cliente,
                   (*clientes)[i].localidad, (*clientes)[i].provincia, (*clientes)[i].email, (*clientes)[i].cartera);
            break;
        }
    }
    if (!encontrado) {
        printf("Cliente no encontrado.\n");
    }
}

// Función para listar todos los clientes
void listarClientes(Cliente **clientes, int *numClientes) {
    printf("Listado de clientes:\n");
    for (int i = 0; i < *numClientes; i++) {
        printf("ID: %s, Nombre: %s, Dirección: %s, Localidad: %s, Provincia: %s, Email: %s, Cartera: %.2f\n",
               (*clientes)[i].id_cliente, (*clientes)[i].nomb_cliente, (*clientes)[i].dir_cliente,
               (*clientes)[i].localidad, (*clientes)[i].provincia, (*clientes)[i].email, (*clientes)[i].cartera);
    }
}

// Función para modificar los datos de un cliente
void modificarCliente(Cliente **clientes, int *numClientes) {
    char id[8];
    int encontrado = 0;
    printf("Ingrese el ID del cliente a buscar: ");
    fgets(id, 8, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *numClientes; i++) {
        if (strcmp((*clientes)[i].id_cliente, id) == 0) {
            encontrado = 1;
            cambiar_perfil_cliente(&(*clientes)[i]);
            break;
        }
    }
    if (!encontrado) {
        printf("Cliente no encontrado.\n");
    }
}
