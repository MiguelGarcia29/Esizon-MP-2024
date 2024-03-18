//Proveedor
#include<stdio.h>
#include<string.h>


typedef struct {
    char id_prod[8];
    char descrip[51];
    char id_categ[5];
    char id_gestor[5];
    int stock;
    int entrega;
    float importe;
}Producto;


typedef struct{
    char id_empresa[5];
    char nombre[21];
    char email[31];
    char contrasenia[16];
    char perfil_usuario[13]; // "administrador" o "proveedor"
} AdminProv;


typedef struct {
    char id_locker[11];
    char localidad[21];
    char provincia[21];
    char ubicacion[21];
    int num_compt;
    int num_compocup;
}Locker;


typedef struct {
    char id_locker[11];
    int num_comp;
    char cod_locker[11];
    char estado[7]; // "ocupado" o "vacío"
    char fecha_ocupacion[11];
    char fecha_caducidad[11];
}ComportamientoLocker;


typedef struct {
    char id_pedido[8];
    char fecha_pedido[11];
    char id_cliente[8];
    char lugar_entrega[10]; // "domicilio" o "locker"
    char id_locker[11];
    char id_cod[11];
}Pedido;


void perfil_prov(AdminProv *info);

void mod(char cad[]);

void productos(Producto prod[], char empresa[5] );

void info_prod(Producto info);

void pedidos(Pedido ped, Locker lock, ComportamientoLocker comp);

void info_ped(Pedido info);







void perfil_prov(AdminProv *info) //Mostrar y modificar la informacion del perfil
{
    int j,k;

    printf("\nId_empresa: ");
    printf("%s", info->id_empresa); //Imprime el id

    printf("\nEmpresa: ");
    printf("%s", info->nombre); //Imprime la empresa

    printf("Email: ");
    printf("%s", info->email); //Imprime el email

    printf("Nombre de usuario: ");
    printf("%s", info->perfil_usuario); //imprime el perfil

    printf("\n__________");

    printf("\n\n(1) Modificar\n"); //Preguntar si se desea modificar los datos
    fflush(stdin);
    scanf("%d",&j);

    while(j == 1){
        printf("\n(1) Modificar nombre de usuario.\n "); //menu para saber que dato cambiar
        printf("(2) Modificar empresa.\n ");
        printf("(3) Modificar email.\n__________\n\n ");

        fflush(stdin);
        scanf("%d",&k);

    switch (k)  //segun lo que se quiera cambiar se enviara una cadena distinta a una funcion
    {
    case 1:
        mod(info->perfil_usuario);
        break;

    case 2:
        mod(info->nombre);
        break;

     case 3:
        mod(info->email);
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


void mod(char cad[51])
{
    printf("Introduzca el nuevo dato: ");
    fflush(stdin);
    fgets(cad,51,stdin); //Modifica la cadena
}










void productos(Producto prod[], char empresa[5] )  // permitira acceder a la informacion de los productos que provea.
{
    char cad[51];
    int nombre,id,a,k,i;

    printf("\n(1) Buscar producto\n");  //menu segun lo que quiera hacer el usuario
    printf("(2) Modificar producto\n");
    printf("(3) Dar producto de alta\n__________\n\n");
    scanf("%d",&a);

    switch (a)
    {
    case 1:

    printf("Buscar producto: ");
    fflush(stdin);
    fgets(cad,51,stdin); //actuara a modo de buscador


    for (i = 0;i < 5 && id != 0 || nombre != 0; i++)
    {

    id = strcmp(prod[i].id_gestor,empresa);
    nombre = strcmp(cad,prod[i].descrip );

    }

    i = i-1; //se suma una i de mas

    if(id == 0 && nombre == 0)
    {

        info_prod(prod[i]); //llamada a la funcion para mostrar la informacion del producto

    }
    else
    {
        printf("Producto no encontrado\n");
    }

         break;


    case 2:
    printf("Modificar producto: ");
    fflush(stdin);
    fgets(cad,51,stdin); //actuara a modo de buscador


    for(i = 0;i < 5 && id !=0 || nombre != 0; i++)
    {

    id = strcmp(prod[i].id_gestor,empresa);
    nombre = strcmp(cad,prod[i].descrip );

    }

    i = i-1; //se suma una i de mas

    if(id == 0 && nombre == 0)
    {

        info_prod(prod[i]); //llamada a la funcion para mostrar la informacion del producto
        while(a == 2)
    {
        printf("\n(1) Modificar descripcion.\n "); //menu para saber que dato cambiar
        printf("(2) Modificar categoria.\n ");
        printf("(3) Modificar precio.\n ");
        printf("(4) Modificar stock.\n__________\n\n ");

        fflush(stdin);
        scanf("%d",&k);

    switch (k)  //segun lo que se quiera cambiar se enviara una cadena distinta a la funcion para modificarlas funcion
    {
    case 1:
        mod(prod[i].descrip);
        break;

    case 2:
        mod(prod[i].id_categ);
        break;

     case 3:
    printf("Introduzca el nuevo dato: ");
    fflush(stdin);
    scanf("%f",&prod[i].importe);
        break;
     case 4:
    printf("Introduzca el nuevo dato: ");
    fflush(stdin);
    scanf("%d",&prod[i].stock);
        break;

    default:
    printf("Caracter equivocado\n\n");
        break;

    }

    printf("Presione 2 para seguir modificando\n\n");
    fflush(stdin);
    scanf("%d",&a);

    }

}
    else
    {
        printf("Producto no encontrado\n");
    }

        break;

    case 3:
            //dar de alta productos
        break;

    default:
        break;
    }


}



void info_prod(Producto info) //funcion para mostrar la informacon del producto escogido
{

        printf("\nId: %s\n",info.id_prod);
        printf("Nombre: %s",info.descrip);
        printf("Categoria: %s\n",info.id_categ);
        printf("%d en stock\n",info.stock);
        printf("Precio: %f\n",info.importe);
        printf("Llegara en %d dias\n",info.entrega);
        printf("_________\n\n");
}









void pedidos(Pedido ped[])
{

    char busc[8];
    int compara,a,i;

    printf("Introduzca el Id del pedido: ");
    fflush(stdin);
    fgets(busc,8,stdin);

    compara = 1;

    for(i = 0; i < 5 && compara != 0; i++)
    {
        compara = strcmp(busc, ped[i].id_pedido); //asegurarse de que sea el pedido buscado
    }

        i = i-1;

    if(compara == 0)
    {

    printf("\n(1) Buscar pedido\n");  //menu segun lo que quiera hacer el usuario
    printf("(2) Asignar locker\n");

    fflush(stdin);
    scanf("%d",&a);

    printf("_________\n\n");

    switch (a)
    {
    case 1:
        info_ped(ped[i]);
        break;

    default:
        break;
    }

    }
    else
    {
        printf("\nPedido no encontrado\n__________\n\n");
    }

}


void info_ped(Pedido info)
{
    printf("\nId: %s\n",info.id_pedido);
    printf("Cliente: %s\n",info.id_cliente);
    printf("Locker: %s\n",info.id_locker);
    printf("Llegara el %s\n",info.fecha_pedido);
    printf("Lugar: %s",info.lugar_entrega);
    printf("Codigo promocional: %s\n",info.id_cod);
}

