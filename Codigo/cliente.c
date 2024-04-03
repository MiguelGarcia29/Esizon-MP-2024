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


int corroborar_contrasenia(char contrasena[16])// para modificar los datos del usuario se pedira la contrasenia
{
	char verificacion[16]; 
	int a;
	
	printf("Contrasena: ");
	fflush(stdin);
	fgets(verificacion,16,stdin);// Se introduce la contrasenia
	
	a = strcmp(verificacion,contrasena);
	
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





int main()
{
	Cliente cli;
	int c,b,a = 0;
	
	printf("Nombre: ");
	fflush(stdin);
	fgets(cli.nomb_cliente,21,stdin);
	
	printf("Provincia: ");
	fflush(stdin);
	fgets(cli.provincia,21,stdin);
	
	printf("Localidad: ");
	fflush(stdin);
	fgets(cli.localidad,21,stdin);
	cli.localidad[strcspn(cli.localidad,"\n")] = '\0';
	
	printf("Direccion: ");
	fflush(stdin);
	fgets(cli.dir_cliente,51,stdin);
	cli.dir_cliente[strcspn(cli.dir_cliente,"\n")] = '\0';
	
	printf("Email: ");
	fflush(stdin);
	fgets(cli.email,31,stdin);
	
	printf("Contrasenia: ");
	fflush(stdin);
	fgets(cli.contrasenia,16,stdin);
	
	printf("Saldo: ");
	fflush(stdin);
	scanf("%f",&cli.cartera);
	printf("----------\n\n");
	
	while(a == 0)
	{
		printf("(1) Mostrar perfil\n");
		printf("(2) Modificar perfil\n");
		
		scanf("%d",&b);
		
		switch(b)
		{
			case(1):
				mostrar_cliente(cli);
			break;
			
			case(2):
				c = corroborar_contrasenia(cli.contrasenia);
				
				if(c == 0)
				{
					cambiar_perfil_cliente(&cli);	
				}
		}
		
		printf("Continuar pruebas:");
		fflush(stdin);
		scanf("%d",&a);
		
		printf("----------\n\n");
	}
	
	return 0;
	
}


























