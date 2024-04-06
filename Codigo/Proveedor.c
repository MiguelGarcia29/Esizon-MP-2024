#include "Proveedor.h"


void cambiar_contrasenia(char nueva[16]); //cambia la contrasenia. Recibe la contrasenia del usuario

void cambiar_email(char nuevo[31]);  // cambia el email. Recibe el email del usuario

int encontrar_producto(Producto *prod,char id[8],AdminProv prov, int cantdad_prod); //recorre un bucle para relacionar un pedido con el producto que contiene el pedido




void mostrar_perfilprov(AdminProv perfil) //funcion que imprime los datos del usuario
{	
	printf("Rol: %s\n",perfil.perfil_usuario);	
	printf("Empresa: %s\n",perfil.nombre);
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
	
	return a; //si devuelve 0 el usuario ha introducido la contrasenia correcta
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


int mi_pedido(ProductoPedido *pedidos,char busc[8],Producto *prod,AdminProv prov,int cantdad_productospedidos, int cantdad_prod)//verifica que el producto pedido es provisto por el proveedor
{
	int i,res,mio;
	
	for(i = 0;i < cantdad_productospedidos && res != 0; i++)
	{
		res = strcmp(busc, pedidos[i].id_pedido); //busca en que estruct de productopedido esta la informacion sobre el pedido que se quiere
	}
	
	if(res == 0)
	{
		i--;
		
		mio = encontrar_producto(prod,pedidos[i].id_prod,prov,cantdad_prod); //si se encuentra el pedido pasara a buscar el producto
	}
	
	
	
	return mio; //si devuelve 0 el producto es provisto por el proveedor
}


int encontrar_producto(Producto *prod,char id[8],AdminProv prov,int cantdad_prod) //relaciona el pedido con el producto
{
	int i,res,mio;
	
	for(i = 0;i < cantdad_prod && res != 0; i++)
	{
		res = strcmp(id, prod[i].id_prod); //busca que producto es el que estamos buscando
	}
	
	if(res == 0)
	{
		i--;
		
		mio = mi_producto(prov.id_empresa,prod[i].id_gestor);//si se encuentra el producto pasara a verificar si dicho producto es provisto por mi
	}
	
	
	return mio; //si devuelve 0 el producto es provisto por el proveedor
}