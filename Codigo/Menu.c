#include<stdio.h>

int rol=0;
//1-Administrador
//2-Usuario
//3-Proveedor
//4-Transportista


void menuadmin;
void menuusuario;
void menuproveedor;
void menutransportista;
void perfil;
void clientes;
void proveedores;
void productos;
void categorias;
void pedidos;
void transportista;
void descuentos;
void devoluciones;

int main()
{
	

	switch(rol)
	{
		case 1:
			menuadmin;
			break;
		case 2:
			meenuusuario;
			break;
		case 3:
			menuproveedor;
			break;
		case 4:
			menutransportista;
			break;
	}

//Rol de administrador
//Solo puede acceder: Administrador

void menuadmin
{
	int opcion;
	do
	{
		printf("Dime que quieres realizar como administrador: ");
		printf("1-Perfil");
		printf("2-Clientes");
		printf("3-Proveedores");
		printf("4-Productos");
		printf("5-Categorías");
		printf("6-Pedidos");
		printf("7-Transportista");
		printf("8-Descuentos");
		printf("9-Devoluciones");
		printf("10-Salir del sistema");
		scanf("%d",&opcion);
		switch(opcion)
		{
		
			case 1:
				perfil;
				break;
			case 2:
				clientes;
				break;
			case 3:
				proveedores;
				break;
			case 4:
				productos;
				break;
			case 5:
				categorias;
				break;
			case 6:
				pedidos;
				break;
			case 7:
				transportista;
				break;
			case 8:
				descuentos;
				break;
			case 9:
				devoluicones;
				break;
			case 10:
				printf("Hasta pronto, ESIZON");
				break;
	
		
		
		}
			
	}while(opcion!=10 || opcion >10);
	
}


//Rol de cliente
//Solo puede acceder: cliente y administrador

void menuusuario
{
	int opcion;
	do
	{
		printf("Dime que quieres realizar como administrador: ");
		printf("1-Perfil \n2-Productos \n3-Descuentos \n4-Pedidos \n5-Devoluciones\n6-Salir del sistema");
		scanf("%d",&opcion);
		switch(opcion)
		{
		
			case 1:
				perfil;
				break;
			case 2:
				productos;
				break;
			case 3:
				descuentos;
				break;
			case 4:
				pedidos;
				break;
			case 5:
				devoluciones;
				break;
			case 6:
				printf("Hasta pronto, ESIZON");
				break;
	
		
		
		}
			
	}while(opcion!=6 || opcion >6);
	
}



//Esta opción permitirá a un usuario administrador consultar los datos de su perfil y modificarlos.
//Solo puede acceder: Administrador
void perfil
{
	
}

//Mediante esta opción el administrador podrá acceder a la información de los clientes dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de clientes.
//Solo puede acceder: Administrador
void clientes
{
	
}

//Mediante esta opción el administrador podrá acceder a la información de los proveedores, deproductos externos, dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de proveedores.
//Solo puede acceder: Administrador
void proveedores
{
	

}


//Mediante esta opción el administrador podrá acceder a la información de los productos dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de productos.
//Solo puede acceder: Administrador
void productos
{
	
}

//Mediante esta opción el administrador podrá acceder a la información de las categorías dadas de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de categorías. Además podrá generar listados de productos por categoría.
//Solo puede acceder: Administrador
void categorias
{
	
	
}

//Mediante esta opción el administrador podrá acceder a la información de los pedidos dados de alta en la plataforma.
//Solo puede acceder: Administrador
void pedidos
{
	
	
}

//Mediante esta opción el administrador podrá acceder a la información de todos los transportistas dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de transportistas.
//Solo puede acceder: Administrador
void transportista
{
	
}

//Mediante esta opción el administrador podrá acceder a la información de todos los códigos promocionales y/o cheques regalo dados de alta en la plataforma.
//Solo puede acceder: Administrador
void descuentos
{
	
}


//Mediante esta opción el administrador podrá acceder a la información de todas las devoluciones de productos.
//Solo puede acceder: Administrador
void devoluciones
{
	
	
}
