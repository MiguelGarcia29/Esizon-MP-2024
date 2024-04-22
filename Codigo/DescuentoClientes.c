//DescuentoClientes

#include"DescuentoClientes.h"

void flushInputBuffer();

int todos_esizon(Descuento desc,Producto *prod,int numprodpe);

int activo_inactivo(Descuento desc);

int aplicado(Descuento desc);

int cheq_cod(Descuento desc,int numprodpe);

int descontar(Descuento desc,float *precio);


void flushInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void rellenar_descuentocliente(Descuento *desc, Cliente *clientes, DescuentoCliente **desccliente, int cantdad_desc, int cantdad_cli, int *cantdad_desccli) //anade la info de descuento cliente
{
    int indice; // Indice para recorrer los structs de DescuentoCliente
	
	indice = *cantdad_desccli;
	
	*cantdad_desccli = cantdad_desc * cantdad_cli; 
    
    if (*desccliente == NULL)	//Memoria dinamica
	{
        *desccliente = malloc((*cantdad_desccli) * sizeof(DescuentoCliente));
        if (*desccliente == NULL) 
		{
            printf("Error: No se pudo asignar memoria para DescuentoCliente\n");
            exit(EXIT_FAILURE);
        }
        
    } else 
	{
        // Si ya se ha asignado memoria, aumentar el tamano del bloque de memoria
        *desccliente = realloc(*desccliente, (*cantdad_desccli) * sizeof(DescuentoCliente));
        if (*desccliente == NULL) 
		{
            printf("Error: No se pudo reasignar memoria para DescuentoCliente\n");
            exit(EXIT_FAILURE);
        }
    }

    time_t rawtime;
    struct tm *info;

    // Obtener la fecha y hora actual
    time(&rawtime);
    info = localtime(&rawtime);

    // Recorrer cada descuento y asignarlo a cada cliente
    for (int i = 0; i < cantdad_cli; i++) {
            strcpy((*desccliente)[indice].id_cliente, clientes[i].id_cliente); // Asignar el ID del cliente
            
            strcpy((*desccliente)[indice].id_cod, desc[cantdad_desc - 1].id_cod);//Asignar el ID del codigo
            
            strftime((*desccliente)[indice].fecha_asignacion, 11, "%d-%m-%Y", info); // Asignar la fecha de asignacion

            (*desccliente)[indice].estado = 0; // Establecer el estado como no aplicado
            
            indice++;
        }
	}
	
	

void anadir_fecha_caducidad(char *caducidad, int cantdad_descli) //anade la fecha de caducidad al struct
{
	time_t rawtime;
    struct tm *current_time;
    time(&rawtime);
    current_time = localtime(&rawtime);

    // Sumar dos semanas a la fecha actual
    time_t caducidad_seconds = rawtime + (2 * 7 * 24 * 60 * 60); // Dos semanas en segundos
    struct tm *caducidad_info = localtime(&caducidad_seconds);

    // Introducir la fecha en la cadena proporcionada
    strftime(caducidad, 11, "%d-%m-%Y", caducidad_info);
}



void mostrar_descuentos_cliente(char id_cliente[8], Descuento *desc, DescuentoCliente *desc_cliente, int cant_desc, int cant_desc_cli) //Muestra los descuentos que posee el cliente
{
    printf("\nDescuentos del cliente con ID: %s\n", id_cliente);

    for (int i = 0; i < cant_desc_cli; i++) 
	{
        if (strcmp(desc_cliente[i].id_cliente, id_cliente) == 0) //si coincide el id del cliente de la sesion con el de descuento cliente lo muestra en pantalla
		{
            
                printf("\n\nDescripcion: %s\n", desc[i].descrip);
                printf("Tipo: %s\n", desc[i].tipo);
                printf("Aplicabilidad: %s\n", desc[i].aplicable);
                if(strcmp(desc[i].tipo,"codpro") == 0)
                {
                	printf("Importe: %.0f %% \n", desc[i].importe);
				}
                else
                {
                	printf("Importe: %.2f \n", desc[i].importe);
				}
                printf("Estado: %s\n", desc[i].estado);
                printf("Codigo del descuento: %s\n", desc_cliente[i].id_cod);
                printf("Uso: %s\n", desc_cliente[i].estado == 1 ? "Aplicado" : "No aplicado");
                printf("%d",desc_cliente[i].estado);
            	printf("Fecha de asignacion: %s\n", desc_cliente[i].fecha_asignacion);
            	printf("Fecha de caducidad: %s\n", desc_cliente[i].fecha_caducidad);

            printf("------------------------------------\n");
        }
    }
}


void baja_descuento_clientes(DescuentoCliente **desccli, int *cantdad_desccli,int cantdad_desc,int cantdad_cli, char *id_baja) //Cuando un descuento se da de baja tambien lo hace descuento cliente
{
    int encontrado = 0, i, j;

    for (i = 0; i < *cantdad_desccli && encontrado == 0; i++) {
        if (strcmp((*desccli)[i].id_cod, id_baja) == 0) {
            

            for (j = i; j < *cantdad_desccli - 1; j++) {
                (*desccli)[j] = (*desccli)[j + 1]; //Reposicionar las estructuras
            }

            *cantdad_desccli = cantdad_desc * cantdad_cli; //Memoria dinamica
            *desccli = realloc(*desccli, (*cantdad_desccli) * sizeof(DescuentoCliente));
            encontrado = 1;
        }
    }
    
}


void actualizar_estado_descuentos_caducados(Descuento *desc,DescuentoCliente *desccli, int cant_desc) //cuando pase la fecha de caducidad el desuento pasara a estar inactivo
{
    // Obtener la fecha actual
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Convertir la fecha actual a un formato comparable
    char fecha_actual[11];
    strftime(fecha_actual, sizeof(fecha_actual), "%d-%m-%Y", timeinfo);

    // Comparar la fecha actual con la fecha de caducidad de cada descuento
    for (int i = 0; i < cant_desc; i++) {
        // Convertir la fecha de caducidad del descuento a un formato comparable
        char fecha_caducidad[11];
        strcpy(fecha_caducidad, desccli[i].fecha_caducidad);

        // Comparar las fechas
        if (strcmp(fecha_actual, fecha_caducidad) > 0) {
            // La fecha actual es posterior a la fecha de caducidad, por lo que el descuento esta caducado
            strcpy(desc[i].estado, "inactivo"); // Establecer el estado como inactivo
        }
    }
}


void asignar_descuento(DescuentoCliente *desc_cliente, int cant_desc_cli)  //hace que un admin pueda hacer aplicable el descuento de un cliente en especifico
{
	char id_cliente[8],id_descuento[11];
	int encontrado = 0;
	
	printf("Introduce el ID del cliente: ");
   	scanf("%8s", id_cliente);
   	flushInputBuffer();

    printf("Introduce el ID del descuento: ");
    scanf("%11s", id_descuento);
    flushInputBuffer();
	
    for (int i = 0; i < cant_desc_cli && encontrado == 0; i++) {
        if (strcmp(desc_cliente[i].id_cliente, id_cliente) == 0 && strcmp(desc_cliente[i].id_cod, id_descuento) == 0) {
            desc_cliente[i].estado = 0; // Establecer el estado como no usado
            printf("El descuento %s para el cliente %s ha sido marcado como no usado.\n", id_descuento, id_cliente);
            encontrado = 1;
        }
    }
    // Si no se encuentra el descuento para el cliente especificado se mostrara el mensaje de error
    if(encontrado == 0)
    {
    	printf("No se encontro el descuento %s para el cliente %s.\n", id_descuento, id_cliente);

	}
}


int todos_esizon(Descuento desc,Producto *prod,int numprodpe)
{
	int res = 1,esizon = 0,i;
	
	for(i = 0; i < numprodpe && esizon == 0;i++)
	{
		if(strcmp(prod[i].id_gestor,"0000" == 0))
		{
			esizon = 1
		}
	}
	
	if(strcmp(desc.aplicable,"todos") == 0)
	{
		res = 0;
	}
	
	if(strcmp(desc.aplicable,"esizon") == 0 && esizon == 1)
	{
			res = 0;
	}
	
	return res;
}


int activo_inactivo(Descuento desc)
{
	int res;
	
	if(strcmp(desc.estado,"activo") == 0)
	{
		res = 0;
	}
	else
	{
		res = 1;
	}
	
	return res;
}


int aplicado(DescuentoCliente desc)
{
	int res;
	
	if(desc.estado == 0)
	{
		res = 0;
	}
	else
	{
		res = 1;
	}
	
	return res;
}


int cheq_cod(Descuento desc,int numprodpe)
{
	int res = 1;
	
	if(strcmp(desc.tipo,"cheqreg") == 0)
	{
		res = 0;
	}
	if(strcmp(desc.tipo,"codpro") == 0 && numprodpe == 1)
	{
		res = 0;
	}
}


void descontar(Descuento desc,float *precio)
{
	if(strcmp(desc.tipo,"cheqreg") == 0)
	{
		*precio = *precio - desc.importe;
	}
	else
	{
		*precio = *precio * desc.importe /(float)100;
	}
}


void aplicar_descuento(float *precio,Descuento *desc,DescuentoCliente *desccli,char id_cliente[8],Producto *prod,int cantdad_desc,int cantdad_desccli,int numprodpe)
{
	int a,i,j,encontrado = 0;
	
	char id_desc[11];
	
	Descuento elegido;
	DescuentoCliente elegidocliente;
	
	printf("\n\nUtilizar un codigo de descuento:\n\n");
	printf("(1) Si");
	printf("(2) En otra ocasion\n");
	
	scanf("%d",&a);
	
	if(a == 1)
	{
		mostrar_descuentos_cliente(id_cliente[8],*desc,*desccli,cantdad_desc,cantdad_desccli);
		
		printf("\n\n\nIntroduzca el codigo que desea utilizar: ");
		scanf("%11s",id_desc);
	}
	else
	{
		return;
	}
	
	for(i = 0; i < cantdad_desccli && encontrado == 0;i++)
	{
		if(strcmp(desccli[i].id_cod,id_desc) == 0 && strcmp(desccli[i].id_cliente,id_cliente) == 0)
		{
			elegidocliente = desccli[i];
			
			encontrado = 1;
		}
	}
	
	if(encontrado == 0)
	{
		printf("\nDescuento no encontrado\n");
		return;
	}
	
	encontrado = 0;
	
	for(i = 0; i < cantdad_desc && encontrado == 0; i++)
	{
		if(strcmp(id_desc,desc[i].id_cod) == 0)
		{
			elegido = desc[i];
			
			encontrado = 1;
		}
	}
	
	if(encontrado == 0)
	{
		printf("\nProducto no encontrado\n\n");
		return;
	}
	
	if(todos_esizon(elegido,*prod,numprodpe) == 0 && activo_inactivo(elegido) == 0 && aplicado(elegidocliente) == 0 && cheq_cod(elegido,numprodpe) == 0)
	{
		descontar(elegido,precio);
	}
	else
	{
		printf("Descuento no disponible.\n");
	}
	printf("%f",*precio);
}