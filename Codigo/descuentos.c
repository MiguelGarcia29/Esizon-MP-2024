//Descuentos

#include"descuentos.h"

//funcion para buscar y mostrar

char *generar_id_descuentos(Descuento *desc, int cantdad_desc);




char *generar_id_descuentos(Descuento *desc, int cantdad_desc) //funcion que genera las ids de los descuentos
{
	
	int id_generada = 1;
	
	if(cantdad_desc != 0)
	{
		id_generada = atoi(desc[cantdad_desc - 1].id_cod);
		
		id_generada++;
	}
	
	char *id = malloc(11 * sizeof(char));
	
	if(id == NULL)
	{
		printf("Error al guardar en memoria\n");
		return NULL;
	}
	
	sprintf(id,"%010d",id_generada);
	
	return id;
}


void alta_descuentos(Descuento **desc,int *cantdad_desc) //funcion para crear descuentos
{
	int a;
	
	Descuento nuevo_descuento; //en esta estructura se guardaran los datos
	
	fflush(stdin);
	printf("Descripcion: ");
	fflush(stdin);                                                      
	fgets(nuevo_descuento.descrip,51,stdin);
	
	printf("Tipo: \n");
	printf("(1) Codigo promocional\n");
	printf("(2) Cheque regalo\n");
	fflush(stdin);
	scanf("%d",&a);
	
	switch(a)
	{
		case 1:
			strcpy(nuevo_descuento.tipo,"codpro");
		break;
		
		case 2: 
			strcpy(nuevo_descuento.tipo,"cheqreg");
		break;
		        
		default:
			printf("\nError\n\n");
			
			exit(EXIT_FAILURE);
		break;	
	}
	
	
	printf("Aplicablidad: \n");
	printf("(1) Todos\n");
	printf("(2) Solo ESIZON\n");
	
	fflush(stdin);
	scanf("%d",&a);
	
	switch(a)
	{
		case 1:
			strcpy(nuevo_descuento.aplicable,"todos");
		break;
		        
		case 2: 
			strcpy(nuevo_descuento.aplicable,"esizon");
		break;
		        
		default:
			printf("\nError\n\n");
			
			exit(EXIT_FAILURE);
		break;
	}
	
	printf("Importe: ");
	fflush(stdin);
	scanf("%f",&nuevo_descuento.importe);
	
             
	printf("Estado: \n");
	printf("(1) Activo\n");
	printf("(2) Inactivo\n");
	
	fflush(stdin);
	scanf("%d",&a);
	
	switch(a)
	{
		case 1:
			strcpy(nuevo_descuento.estado,"activo");	       
		break;  
		
		case 2:
			strcpy(nuevo_descuento.estado,"inactivo");
		break;
		
		default:
			printf("\nError\n\n");
			
			exit(EXIT_FAILURE);
		break;
	}
	
	fflush(stdin);
	strcpy(nuevo_descuento.id_cod,generar_id_descuentos(*desc,*cantdad_desc)); //se pasa la informacion de la estructura de antes a la que usaremos a lo largo del programa
	fflush(stdin);
	
	*desc = (Descuento *)realloc(*desc, (*cantdad_desc + 1) * sizeof(Descuento)); //ajustar la memoria dinamica
	
	(*desc)[*cantdad_desc] = nuevo_descuento;
	
	(*cantdad_desc++); //problema aqui
	
}

void baja_descuentos(Descuento **desc,int *cantdad_desc,char *id_baja) //funcion para dar descuentos de baja
{
	int encontrado = 0,i,j;
	
	for(i = 0;i < *cantdad_desc && encontrado == 0;i++)
	{
		if(strcmp((*desc)[i].id_cod,id_baja) == 0) //si se encuentra el id que se quiere dar de baja se reposicionan los descuentos de forma que todos los que hay a partir del descuento a eliminar
		{                                          //ocuparan una posicion menos
			encontrado = 1;
			
			for(j = i;j < *cantdad_desc - 1; j++)
			{
				(*desc)[j] = (*desc)[j+1];
			}
			
			*(cantdad_desc)--; //reduccion de la cantidad de descuentos
			
			*desc = realloc(*desc, (*cantdad_desc) * sizeof(Descuento)); //reajuste de la memoria dinamica
			
			printf("\nBaja efectuada.\n\n");
			
		}
			
	}
	
	if(encontrado == 0)
	{
		printf("\nDescuento no encontrado\n\n");
	}	
}


void aplicar_descuento(Descuento *desc,Producto *prod) //funcion para aplicar los descuentos
{
	fflush(stdin);
		
	if(strcmp(desc->estado,"activo") == 0) //si el descuento esta activo el usuario podra aplicarlo
	{
		if(strcmp(desc->aplicable,"todos") == 0) //si es aplicable a todos no hay problema
		{
			prod->importe = prod->importe - desc->importe;
			
			if(prod->importe < 0)
			{
				
				prod->importe = 0;
				
			}
			
			strcpy(desc->estado,"inactivo");//una vez usado el descuento es inactivo
			
		}
		
		else
		{
			if(strcmp(prod->id_gestor,"0001") == 0) //si solo es aplicable a esizon habra que corroborar que dicho producto es gestionado por esizon
				{
					prod->importe = prod->importe - desc->importe;
			
			if(prod->importe < 0)
			{
				
				prod->importe = 0;
				
			}
			
				}
		}
	}
	
	else
	{
		printf("\nDescuento no disponible.\n\n");
	}
	
}


void modificar_descuento(Descuento *desc, int i) {
    int opcion;

        printf("\nSeleccione que desea modificar:\n");
        printf("(1) Estado\n");
        printf("(2). Importe\n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("\nNuevo estado\n\n");
                printf("(1) Activo\n");
				printf("(2) Inactivo\n");
			
                scanf("%d", &opcion);
                
                if (opcion == 1)
                    strcpy(desc[i].estado, "activo");
                else if (opcion == 2)
                    strcpy(desc[i].estado, "inactivo");
                else
                    printf("\nOpcion invalida\n");
                break;
            case 2:
                printf("\nNuevo importe: ");
                scanf("%f", &desc[i].importe);
                break;
            default:
                printf("\nOpcion invalida\n");
                break;
        }
    } else {
        printf("Descuento no encontrado\n");
    }
}



int main()
{
	int c,b,cantdad_des = 1;
	c = 0;
	
	Descuento *des;
	
	des = malloc(cantdad_des * sizeof(Descuento));
	
	char id[11];
	
	Producto producto;
	producto.importe = 25;
	strcpy(producto.id_gestor,"0001");
	
	while(c == 0)
	{
		printf("\n(1) Alta\n");
		printf("(2) Mostrar\n");
		printf("(3) Modificar\n");
		printf("(4) Baja\n");
		
		scanf("%d",&b);
		fflush(stdin);
		
		switch(b)
		{
			case 1:
				alta_descuentos(&des,&cantdad_des);
				
				c = 0;
			break;
			
			case 2:
				printf("Descripcion: %s ",des[cantdad_des].descrip);
	
				printf("Tipo: %s \n",des[cantdad_des].tipo);
			
				printf("Aplicabilidad: %s \n",des[cantdad_des].aplicable);
	
				printf("Importe:%2.f \n",des[cantdad_des].importe);
	
				printf("Estado: %s \n",des[cantdad_des].estado);

				printf("Id: %s \n",des[cantdad_des].id_cod);
	
				printf("Cantidad: %d\n",cantdad_des);
				
				c = 0;
			break;
			
			case 3:
				modificar_descuento(&des,cantdad_des);
				
				c = 0;
			break;
			
			case 4:
				printf("Id baja:");
				fflush(stdin);
				fgets(id,11,stdin);
				id[strcspn(id,"\n")] = '\0';
				fflush(stdin);
				
				baja_descuentos(&des,&cantdad_des,id);
				
				c = 0;
			break;
			
			default:
				c = 1;
			break;
		}	
		
	}
	
	
	/*printf("Precio antes:%2.f\n",producto.importe);
	
	aplicar_descuento(&des[cantdad_des],&producto);
	
	printf("Despues:%2.f\n",producto.importe);*/
	
	return 0;	
}































