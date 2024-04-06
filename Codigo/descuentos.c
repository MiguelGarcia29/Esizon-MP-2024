//Descuentos

#include"descuentos.h"








//void activo_inactivo();

//aplicar_descuento();

//buscar_descuento();

//listar_descuentos();


char *generar_id_descuentos(Descuento *desc, int cantdad_desc)
{
	
	int id_generada = 1;
	
	if(cantdad_desc != 0)
	{
		id_generada = atoi(desc[cantdad_desc].id_cod);
		
		id_generada++;
	}
	
	char *id = malloc(11 * sizeof(char));
	
	if(id == NULL)
	{
		printf("Error al guardar en memoria\n");
		return NULL;
	}
	
	snprintf(id,10,"%010d",id_generada);
	
	return id;
}


void alta_descuentos(Descuento *desc,int *cantdad_desc,DescuentoCliente *desccli)
{
	int a;
	
	fflush(stdin);
	strcpy(desc->id_cod,generar_id_descuentos(&desc,*cantdad_desc));
	
	printf("Descripcion: ");
	fflush(stdin);
	fgets(desc->descrip,51,stdin);
	
	printf("Tipo: \n");
	printf("(1) Codigo promocional\n");
	printf("(2) Cheque regalo\n");
	fflush(stdin);
	scanf("%d",&a);
	
	switch(a)
	{
		case 1:
			strcpy(desc->tipo,"codpro\0");
		break;
		
		case 2:
			strcpy(desc->tipo,"cheqreg\0");
		break;
		
		default:
			printf("Error\n");
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
			strcpy(desc->aplicable,"todos\0");
		break;
		
		case 2:
			strcpy(desc->aplicable,"esizon\0");
		break;
		
		default:
			printf("Error\n");
		break;
	}
	
	printf("Importe: ");
	fflush(stdin);
	scanf("%f",&desc->importe);
	

	printf("Estado: \n");
	printf("(1) Activo\n");
	printf("(2) Inactivo\n");
	
	fflush(stdin);
	scanf("%d",&a);
	
	switch(a)
	{
		case 1:
			strcpy(desc->estado,"activo\0");
			
			
		break;
		
		case 2:
			strcpy(desc->estado,"inactivo\0");
			
			printf("Introduzca la fecha en que quiere que entre en vigor el descuento: ");
			fflush(stdin);
			fgets(desccli->fecha_asignacion,10,stdin);
			
		break;
		
		default:
		break;
	}
	
	printf("Indique la fecha hasta la que estara habilitado este descuento: ");
	fflush(stdin);
	fgets(desccli->fecha_caducidad,10,stdin);
	
	*cantdad_desc++;
	
}

void baja_descuentos(Descuento *desc,int *cantdad_desc,char *id_baja)
{
	int encontrado = 0,i,j;
	
	for(i = 0;i < *cantdad_desc;i++)
	{
		if(strcmp(desc[i].id_cod,id_baja) == 0)
		{
			encontrado = 1;
			
			for(j = i;j < *cantdad_desc - 1; j++)
			{
				desc[j] = desc[j+1];
			}
			
			*cantdad_desc--;
			
			printf("\nBaja efectuada.\n");
			
		}
			
	}
		
}


int main()
{
	Descuento des;
	
	DescuentoCliente descli;
	
	int cantdad_des = 1;
	
	alta_descuentos(&des,&cantdad_des,&descli);
	
	printf("%s ",des.descrip);
	
	printf("%s \n",des.tipo);
	
	printf("%s \n",des.aplicable);
	
	printf("%2.f \n",des.importe);
	
	printf("%s \n",des.estado);
	
	printf("%s",descli.fecha_asignacion);
	
	printf("%s",descli.fecha_caducidad);

	printf("%s",des.id_cod);
	
	printf("%d",cantdad_des);
	
	return 0;
}































