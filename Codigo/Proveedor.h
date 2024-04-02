//proveedor
#include<stdio.h>
#include<string.h>
#include "estructuras.h"


void modificar_perfilprov(AdminProv *mod); //modifica el perfil del proveedor. Recibe el estruct del perfil del proveedor

void mostrar_perfilprov(AdminProv perfil); //muestran el perfil del proveedor. Recibe el estruct del perfil del proveedor

int verificar_contrasenia(char cad[16]); //pide al usuario que introduzca su contraseña y corrobora si la contraseña es o no correcta.
// Recibe la contraseña del proveedor

int mi_producto(char empresa[5],char gestor[5]); //Corrobora que el producto sobre el que se quiere hacer algo es provisto por el proveedor. Entra el id de la empresa 
// del proveedor y el id del gestor del producto

//int mi_pedido(ProductoPedido pedidos[cantdad_productospedidos],char busc[8],Producto prod[cantdad_prod],AdminProv prov) //Corrobora que el pedido sobre el que se quiere 
//hacer algo es provisto por el proveedor. Recibe todos los estructs de pedidos, el id del pedido que se quiere manipular, todos los estructs de productos y 
//el perfil del proveedor