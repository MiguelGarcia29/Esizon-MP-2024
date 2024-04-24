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
	fgets(verificacion,16,stdin);// Se introduce la contrasenia
    verificacion[strcspn(verificacion, "\n")] = '\0';

	a = strcmp(verificacion,contrasena); // Compara si la contrasenia introducida y la del usuario son iguales

	return a; //si devuelve 0 el usuario ha introducido la contrasenia correcta
}


void modificar_perfilprov(AdminProv *mod) //funcion con un menu segun que se quiera modificar
{
	int a;

	printf("1- Cambiar contrasena\n");
	printf("2- Cambiar email\n");
	scanf("%d",&a);
	flushInputBuffer();

		switch(a)
		{
			case 1:
			    printf("Introduzca su nueva contraseña: ");
                fgets(mod->contrasenia, 16, stdin);
                mod->contrasenia[strcspn(mod->contrasenia, "\n")] = '\0';
			break;

			case 2:
				printf("Introduzca su nuevo email: ");
                fgets(mod->email, 31, stdin);
                mod->email[strcspn(mod->email, "\n")] = '\0';
			break;

		}
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

void altaProveedor(AdminProv **proveedores, int *numProveedores) {
    AdminProv nuevoProveedor;
    printf("Ingrese el ID de la empresa: ");
    fgets(nuevoProveedor.id_empresa, 5, stdin);
    nuevoProveedor.id_empresa[strcspn(nuevoProveedor.id_empresa, "\n")] = '\0';

    printf("Ingrese el nombre de la empresa : ");
    fgets(nuevoProveedor.nombre, 21, stdin);
    nuevoProveedor.nombre[strcspn(nuevoProveedor.nombre, "\n")] = '\0';

    printf("Ingrese el email de la empresa: ");
    fgets(nuevoProveedor.email, 31, stdin);
    nuevoProveedor.email[strcspn(nuevoProveedor.email, "\n")] = '\0';

    printf("Ingrese la contraseña de la empresa: ");
    fgets(nuevoProveedor.contrasenia, 16, stdin);
    nuevoProveedor.contrasenia[strcspn(nuevoProveedor.contrasenia, "\n")] = '\0';

    strcpy(nuevoProveedor.perfil_usuario, "proveedor");

    *proveedores = (AdminProv *)realloc(*proveedores, ((*numProveedores) + 1) * sizeof(AdminProv));
    if (*proveedores == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    (*proveedores)[*numProveedores] = nuevoProveedor;
    (*numProveedores)++;
}

void bajaProveedor(AdminProv **proveedores, int *numProveedores,char *id) {

    int encontrado = 0;

    for (int i = 0; i < *numProveedores && encontrado == 0; i++) {
        if (strcmp((*proveedores)[i].id_empresa, id) == 0) {
            encontrado = 1;
            // Eliminar el proveedor moviendo los elementos hacia adelante
            for (int j = i; j < *numProveedores - 1; j++) {
                (*proveedores)[j] = (*proveedores)[j + 1];
            }
            // Reducir el tamaño del array
            *proveedores = (AdminProv *)realloc(*proveedores, ((*numProveedores) - 1) * sizeof(AdminProv));
            if (*proveedores == NULL) {
                printf("Error al liberar memoria.\n");
            }else{
                (*numProveedores)--;
                printf("Proveedor eliminado exitosamente.\n");
            }
        }
    }
    if (!encontrado) {
        printf("Proveedor no encontrado.\n");
    }
}

void buscarProveedor(AdminProv **proveedores, int *numProveedores) {
    char id[5];
    int encontrado = 0;
    printf("Ingrese el ID: ");
    fgets(id, 5, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *numProveedores; i++) {
        if (strcmp((*proveedores)[i].id_empresa, id) == 0) {
            encontrado = 1;
            printf("Proveedor encontrado:\n");
            printf("ID: %s\nNombre: \nEmail: %s\n",
                   (*proveedores)[i].id_empresa, (*proveedores)[i].nombre, (*proveedores)[i].email);
            break;
        }
    }
    if (!encontrado) {
        printf("Proveedor no encontrado.\n");
    }
}

void listarProveedores(AdminProv **proveedores, int *numProveedores) {
    printf("Listado de proveedores:\n");
    for (int i = 0; i < *numProveedores; i++) {
        printf("ID: %s, Nombre: %s, Email: %s\n",
               (*proveedores)[i].id_empresa, (*proveedores)[i].nombre, (*proveedores)[i].email);
    }
}

void modificarProveedor(AdminProv **proveedores, int *numProveedores) {
    char id[5];
    int encontrado = 0;
    printf("Ingrese el ID: ");
    fgets(id, 5, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *numProveedores; i++) {
        if (strcmp((*proveedores)[i].id_empresa, id) == 0) {
            encontrado = 1;
            modificar_perfilprov(&(*proveedores)[i]);
            break;
        }
    }
    if (!encontrado) {
        printf("Proveedor no encontrado.\n");
    }
}
