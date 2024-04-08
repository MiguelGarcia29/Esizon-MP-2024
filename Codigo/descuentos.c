//Descuentos

#include"descuentos.h"



char *generar_id_descuentos(Descuento *desc, int cantdad_desc);




//void activar_descuento

//void activo_inactivo();

//aplicar_descuento();

//buscar_descuento();

//listar_descuentos();


char *generar_id_descuentos(Descuento *desc, int cantdad_desc)
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


void alta_descuentos(Descuento **desc,int *cantdad_desc)
{
	int a;
	
	Descuento nuevo_descuento;
	
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
			strcpy(nuevo_descuento.tipo,"codpro\0");
		break;
		
		case 2: 
			strcpy(nuevo_descuento.tipo,"cheqreg\0");
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
			strcpy(nuevo_descuento.aplicable,"todos\0");
		break;
		        
		case 2: 
			strcpy(nuevo_descuento.aplicable,"esizon\0");
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
			strcpy(nuevo_descuento.estado,"activo\0");
			
			       
		break;  
		
		case 2:
			strcpy(nuevo_descuento.estado,"inactivo\0");
		break;
		
		default:
			printf("\nError\n\n");
			
			exit(EXIT_FAILURE);
		break;
	}
	
	fflush(stdin);
	strcpy(nuevo_descuento.id_cod,generar_id_descuentos(*desc,*cantdad_desc));
	fflush(stdin);
	
	*desc = (Descuento *)realloc(*desc, (*cantdad_desc + 1) * sizeof(Descuento));
	
	(*desc)[*cantdad_desc] = nuevo_descuento;
	
	(*cantdad_desc++);
	
}

void baja_descuentos(Descuento **desc,int *cantdad_desc,char *id_baja)
{
	int encontrado = 0,i,j;
	
	for(i = 0;i < *cantdad_desc && encontrado == 0;i++)
	{
		if(strcmp((*desc)[i].id_cod,id_baja) == 0)
		{
			encontrado = 1;
			
			for(j = i;j < *cantdad_desc - 1; j++)
			{
				(*desc)[j] = (*desc)[j+1];
			}
			
			*(cantdad_desc)--;
			
			*desc = realloc(*desc, (*cantdad_desc) * sizeof(Descuento));
			
			printf("\nBaja efectuada.\n\n");
			
		}
			
	}
	
	if(encontrado == 0)
	{
		printf("\nDescuento no encontrado\n\n");
	}
		
}


int main()
{
	int cantdad_des = 0;
	
	Descuento *des;
	

	
	alta_descuentos(&des,&cantdad_des);
	
	printf("Descripcion: %s ",des[cantdad_des].descrip);
	
	printf("%s \n",des[cantdad_des].tipo);
	
	printf("%s \n",des[cantdad_des].aplicable);
	
	printf("Importe: %2.f \n",des[cantdad_des].importe);
	
	printf("%s \n",des[cantdad_des].estado);

	printf("%s \n",des[cantdad_des].id_cod);
	
	printf("Cantdidad: %d",cantdad_des);
	
	return 0;
	
}































