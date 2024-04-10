//Cliente

#include "cliente.h"


void cambiar_contrasenia_cliente(char nueva[16]); // funcion que cambia la contrasenia

void cambiar_email_cliente(char nuevo[31]); //funcion que cambia el email

void cambiar_direccion_cliente(char direccion[51], char provincia[21], char localidad[21]); //funcion que cambia direccion, provincia y localidad

void cartera(float *saldo);

void anadir_saldo(float *saldo);

void extraer_saldo(float *saldo);

int corroborar_contrasenia(char cad[16]);




void mostrar_cliente(Cliente client)
{

	printf("\nHola %s\n",client.nomb_cliente);
	printf("Direccion: %s, %s, %s\n",client.dir_cliente,client.localidad,client.provincia);
	printf("Email: %s\n",client.email);
	printf("Saldo: %.2f\n",client.cartera);
	printf("----------\n\n");

}


void cambiar_perfil_cliente(Cliente *client) //se presentara un menu para que el cliente pueda cambiar los datos que considere necesario
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
			cambiar_direccion_cliente(client->dir_cliente, client->provincia, client->localidad); //funcion cambiar direccion(provincia y localidad incluida)
		break;

		case (2):
			cambiar_email_cliente(client->email); //funcion cambiar email
		break;

		case (3):
			cambiar_contrasenia_cliente(client->contrasenia); //funcion cambiar contrasenia
		break;

		case (4):
			cartera(&client->cartera); //acceder a la cartera para retirar o aniadir dinero
		break;

		default:
			printf("Error\n\n");
		break;
	}

}


void cambiar_contrasenia_cliente(char nueva[16]) // funcion que cambia la contrasenia
{
	printf("Introduzca su nueva contrasenia: ");
	fflush(stdin);
	fgets(nueva,16,stdin);
}

void cambiar_email_cliente(char nuevo[31]) //funcion que cambia el email
{
	printf("Introduzca el nuevo email: ");
	fflush(stdin);
	fgets(nuevo,31,stdin);
}

void cambiar_direccion_cliente(char direccion[51], char provincia[21], char localidad[21]) //funcion que cambia direccion, provincia y localidad
{

	printf("Provincia: ");
	fflush(stdin);
	fgets(provincia,21,stdin);

	printf("Localidad: ");
	fflush(stdin);
	fgets(localidad,21,stdin);
	localidad[strcspn(localidad,"\n")] = '\0';

	printf("Direccion: ");
	fflush(stdin);
	fgets(direccion,51,stdin);
	direccion[strcspn(direccion,"\n")] = '\0';

}


int corroborar_contrasenia(char cad[16])// para modificar los datos del usuario se pedira la contrasenia
{
	char verificacion[16];
	int a;

	printf("Contrasenia: ");
	fflush(stdin);
	fgets(verificacion,16,stdin);// Se introduce la contrasenia

	a = strcmp(verificacion,cad);

	return a; //si devuelve 0 el usuario ha introducido la contrasenia correcta
}


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

void anadir_saldo(float *saldo)
{
	float a;

	printf("Cantidad de dinero a anadir: ");

	scanf("%f",&a);

	*saldo = *saldo + a;

}


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

// Guarda el vector de clientes en el archivo siguiendo la estructura:
/*  o Identificador del cliente (Id_cliente), 7 digitos.
    o Nombre completo del cliente (Nomb_cliente), 20 caracteres maximo.
    o Dirección del cliente (Dir_cliente), 50 caracteres maximo.
    o Población (Localidad), 20 caracteres maximo.
    o Provincia (Provincia), 20 caracteres maximo.
    o Email (email), 30 caracteres maximo, sera usado como nombre de usuario para el acceso a la
    plataforma.
    o Contrasenia para acceder al sistema (Contrasenia), con 15 caracteres maximo.
    o Cartera (Cartera), almacenara el dinero del que dispone el cliente para poder adquirir los
    productos.
    */

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

// LE PASO COMO PUNTERO EL NUM DE CLIENTES PARA LUEGO PODER ALMACENARLO EN EL PROGRAMA (MAIN) -> MISMA LOGICA PARA LAS DEMAS LECTURAS
Cliente *iniciarClientesDeArchivo(int *numClientes)
{
    FILE *archivo = fopen(Clientes_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", Clientes_txt);
        return NULL;
    }

    // Contar la cantidad de lineas = clientes en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA];
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear vector cliente
    Cliente *clientes = (Cliente *)malloc(count * sizeof(Cliente));
    if (clientes == NULL)
    {
        fclose(archivo);
        printf("No se pudo asignar memoria para el vector de clientes.\n");
        return NULL;
    }

    // Leer cada linea del archivo y rellenar el vector de clientes
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        // Strtok sirve para dividir la cadena en subcadenas por "-"
        // - OS ADJUNTO DOCUMENTACION CONSULTADA: https://www.ibm.com/docs/es/i/7.5?topic=functions-strtok-tokenize-string
        // - VIDEO QUE LO EXPLICA CON SUMA: https://www.youtube.com/watch?v=jHdbmHCVQ2c
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
        clientes[i].cartera = atof(token); // atof convierte la cadena en Float.
        i++;
    }

    fclose(archivo);
    *numClientes = count;
    return clientes;
}

























