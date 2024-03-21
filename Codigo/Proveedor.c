#include "proveedor.h"


void cambiar_contrasenia(char nueva[16]);

void cambiar_email(char nuevo[31]);

void mostrar_perfilprov(AdminProv perfil)//funcion que imprime los datos del usuario
{
	printf("Nombre de usuario: %s",perfil.perfil_usuario);	
	printf("Empresa: %s",perfil.nombre);
	printf("Id empresa: %s\n",perfil.id_empresa);
	printf("Email: %s\n",perfil.email);
	printf("__________\n");
}
	

int verificar_contrasenia(char contrasena[16])// para modificar los datos del usuario se pedira la contrasenia
{
	char verificacion[16]; 
	int a;
	
	printf("Contrasena: ");
	fflush(stdin);
	fgets(verificacion,16,stdin);// Se introduce la contrasenia
	
	a = strcmp(verificacion,contrasena); // Compara si la contrasenia introducida y la del usuario son iguales
	
	return a; //si devuelve 0 el usuario podra modificar su perfil
}
	

void modificar_perfilprov(AdminProv *mod) //funcion con un menu segun que se quiera modificar
{
	int a;
	
	printf("(1) Cambiar contrasena\n");
	printf("(2) Cambiar email\n");
	fflush(stdin);
	scanf("%d",&a);
	
		switch(a)
		{
			case 1:
				cambiar_contrasenia(mod->contrasenia); //Si pulsa 1 se camabiara la contrasenia
			break;
			
			case 2:
				cambiar_email(mod->email); // Si pulsa 2 se cambia el email
			break;
			
			default:
			break;
		}
} 


void cambiar_contrasenia(char nueva[16]) // funcion que cambia la contrasenia
{
	printf("Introduzca su nueva contrasena: ");
	fflush(stdin);
	fgets(nueva,16,stdin);
}


void cambiar_email(char nuevo[31]) //funcion que cambia el email
{
	printf("Introduzca el nuevo email: ");
	fflush(stdin);
	fgets(nuevo,31,stdin);
}




int mi_producto(char empresa[5],char gestor[5]) // funcion que verifica que el producto lo provee este usuario
{
	int res;
	
	res = strcmp(empresa,gestor); //compara el id de la empresa del usuario con la id de la empresa gestora del usuario
	
	return res;
}


void modificar_producto(Producto *mod)
{
	int a;
	
	printf("(1) Modificar descripcion\n");
	printf("(2) Modificar precio\n");
	printf("(3) Modificar stock\n");
	printf("(4) Modificar entrega\n");
	fflush(stdin);
	scanf("%d",&a);
	printf("----------\n\n");
	
	switch(a)
	{
		case 1:
			modificar_descripcion_prod(mod->descrip);
		break;
		
		case 2:
			modificar_precio(&mod->importe);
		break;
		
		case 3:
			modificar_stock(&mod->stock);
		break;
		
		case 4:
			modificar_entrega(&mod->entrega);
		break;
		
		default:
			break;
	}
}


void modificar_descripcion_prod(char desc[51])
{
	printf("Escribe la nueva descripcion: ");
	fflush(stdin);
	fgets(desc,51,stdin);
}

void modificar_precio(float *precio)
{
	printf("Introduce el nuevo importe: ");
	fflush(stdin);
	scanf("%f",&precio);
}

void modificar_stock(int *stock)
{
	printf("Cantidad de productos en stock: ");
	fflush(stdin);
	scanf("%d",&stock);
}

void modificar_entrega(int *ent_maxima)
{
	printf("Nueva fecha maxima de entrega: ");
	fflush(stdin);
	scanf("%d",&ent_maxima);
}


int buscar_producto(char nombre[51])
{
	int i,busc;
	char cad[51];
	
	printf("Buscar producto: ");
	fflush(stdin);
	fgets(cad,51,stdin);
	
	busc = 1;
	
	for(i = 0;i < cantdad_prod + 1 && busc != 0; i++)
	{
		busc = strcmp(cad,nombre);
	}
	
	return i - 1;
}

//