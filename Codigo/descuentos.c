//Descuentos

#include"descuentos.h"






//void baja_descuentos();

//void activo_inactivo();

//aplicar_descuento();

//buscar_descuento();

//listar_descuentos();

void alta_descuentos(Descuento *desc)
{
	int a;
	
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
			strcpy(desc->tipo,"esizon\0");
		break;
		
		default:
			printf("Error\n");
		break;
	}
	
	printf("Importe: ");
	fflush(stdin);
	scanf("%f",&desc->importe);
	

	
}


int main()
{
	Descuento des;
	
	alta_descuentos(&des);
	
	printf("%s ",des.descrip);
	
	printf("%s \n",des.tipo);
	
	printf("%s \n",des.aplicable);
	
	printf("%2.f \n",des.importe);
	
	return 0;
}































