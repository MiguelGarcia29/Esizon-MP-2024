//proveedor
#include<stdio.h>
#include<string.h>
#include "estructuras.h"


void perfil_proveedor(AdminProv *prov);

void modificar_perfilprov(AdminProv *mod);

void mostrar_perfilprov(AdminProv perfil);

int verificar_contrasenia(AdminProv.contrasenia contrasena);

void cambiar_contrasenia(AdminProv.contrasenia nueva);

void cambiar_email(AdminProv.email nuevo);




void perfil_proveedor(AdminProv *prov)
{
	int a,b;
	
	printf("(1) Mostrar perfil\n");
	printf("(2) Modificar perfil\n");
	
	scanf("%d",&a);
	
	switch(a)
	{
		case 1:
			mostrar_perfilprov(prov);
		break;
		
		case 2:
			
			b = verificar_contrasenia(prov->contrasenia);
			
			if(b == 0)
			{
				modificar_perfilprov(&prov);	
			}
			else
			{
				printf("Contrasena incorrecta.\n");
			}
		break;
		
		default:
		break;	
	}
	
}



void mostrar_perfilprov(AdminProv perfil)//funcion que imprime los datos del usuario
{
	printf("Nombre de usuario: %s\n",perfil.usuario);	
	printf("Empresa: %s\n",perfil.nombre);
	printf("Id empresa: %s\n",perfil.id_empresa);
	printf("Email: %s\n",perfil.email);
	printf("__________n\n");
}
	


int verificar_contrasenia(AdminProv.contrasenia contrasena)
{
	char verificacion[16];
	int a;
	
	printf("Contrasena: ");
	fflush(stdin);
	fgets(verificacion,16,stdin);
	
	a = strcmp(verificacion,contrasena);
	
	return a;
}
	

void modificar_perfilprov(AdminProv *mod)
{
	int a;
	
	printf("(1) Cambiar contrasena\n");
	printf("(2) Cambiar email\n");
	scanf("%d",&a);
	
		switch(a)
		{
			case 1:
				cambiar_contrasenia(&mod->contrasenia);
			break;
			
			case 2:
				cambiar_email(&mod->email);
			break;
			
			default:
			break;
		}
} 


void cambiar_contrasenia(AdminProv.contrasenia nueva)
{
	printf("Introduzca su nueva contrasena: ");
	fflush(stdin);
	fgets(nueva,16,stdin);
}

void cambiar_email(AdminProv.email nuevo)
{
	printf("Introduzca el nuevo email: ");
	fflush(stdin);
	fgets(nuevo,31,stdin);
}


int main()
{
	    AdminProv proveedor;
    int a = 0;

    fflush(stdin);
    printf("Email: ");
    fgets(prov.email,31,stdin);

    fflush(stdin);
    printf("Id empresa: ");
    fgets(prov.id_empresa,5,stdin);

    fflush(stdin);
    printf("Empresa: ");
    fgets(prov.nombre,21,stdin);

    fflush(stdin);
    printf("Usuario: ");
    fgets(prov.perfil_usuario,13,stdin);
    
    fflush(stdin);
    printf("Contrasena: ");
    fgets(prov.perfil_usuario,16,stdin);

    while(a == 0)
    {
        perfil_proveedor(&proveedor);


        printf("Seguir pruebas: ");
        fflush(stdin);
        scanf("%d",&a);
    }

    return 0;
}