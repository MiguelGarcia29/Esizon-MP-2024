//Cliente

#include "cliente.h"


void cambiar_contrasenia_cliente(char nueva[16]); // funcion que cambia la contrasenia

void cambiar_email_cliente(char nuevo[31]); //funcion que cambia el email

void cambiar_direccion_cliente(char direccion[51], char provincia[21], char localidad[21]); //funcion que cambia direccion, provincia y localidad

int corroborar_contrasenia(char contrasena[16]); // para modificar los datos del usuario se pedira la contrasenia




void mostrar_cliente(Cliente client)
{
	
	printf("Hola: %s\n",client.nomb_cliente);
	printf("%s, %s\n",client.localidad,client.provincia);
	printf("Email: %s\n",client.email);
	printf("Saldo: %f\n",client.cartera);
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
			//acceder a la cartera para retirar o aniadir dinero
		break;
		
		default:
			printf("Error");
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
	
	printf("Direccion: ");
	fflush(stdin);
	fgets(direccion,51,stdin);
	
}


int corroborar_contrasenia(char contrasena[16])// para modificar los datos del usuario se pedira la contrasenia
{
	char verificacion[16]; 
	int a;
	
	printf("Contrasena: ");
	fflush(stdin);
	fgets(verificacion,16,stdin);// Se introduce la contrasenia
	
	a = strcmp(verificacion,contrasena); // Compara si la contrasenia introducida y la del usuario son iguales
	
	return a; //si devuelve 0 el usuario ha introducido la contrasenia correcta
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
	
	printf("Direccion: ");
	fflush(stdin);
	fgets(cli.dir_cliente,51,stdin);
	
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

























