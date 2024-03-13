//Proveedor
#include<stdio.h>

void perfil_prov(AdminProv info) //Mostrar y modificar la informacion del perfil
{
    int j,k;

    printf("\nId_empresa: ");
    printf("%s", info.id_empresa); //Imprime el id

    printf("\nEmpresa: ");
    printf("%s", info.nombre); //Imprime la empresa

    printf("\nEmail: ");
    printf("%s", info.email); //Imprime el email

    printf("\nNombre de usuario: ");
    printf("%s", info.perfil_usuario); //imprime el perfil

    printf("\n__________");

    printf("\n\n(1) Modificar\n"); //Preguntar si se desea modificar los datos
    fflush(stdin);
    scanf("%d",&j);

    while(j == 1){
        printf("\n(1) Modificar nombre de usuario.\n "); //menu para saber que dato cambiar
        printf("(2) Modificar empresa.\n ");
        printf("(3) Modificar email.\n\n ");

        fflush(stdin);
        scanf("%d",&k);

    switch (k)  //segun lo que se quiera cambiar se enviara una cadena distinta a una funcion
    {
    case 1:
        mod(info.perfil_usuario);
        break;

    case 2:
        mod(info.nombre);
        break;

     case 3:
        mod(info.email);
        break;

    default:
    printf("Caracter equivocado\n\n");
        break;

    }

    printf("(1) Seguir modificando\n\n");
    fflush(stdin);
    scanf("%d",&j);

    } 
    
}

int mod(char cad[])
{
    printf("Introduzca el nuevo dato: ");
    fflush(stdin);
    fgets(cad,31,stdin); //Modifica la cadena
}
