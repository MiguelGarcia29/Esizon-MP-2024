//DescuentoClientes

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"estructuras.h"
#include"descuentos.h"

void rellenar_descuentocliente(Descuento desc[], Cliente clientes[], DescuentoCliente **desccliente, int cantdad_desc, int cantdad_cli, int *cantdad_desccli);

void mostrar_descuentos_cliente(char id_cliente[8], Descuento *desc, DescuentoCliente *desc_cliente, int cant_desc, int cant_desc_cli);

void anadir_fecha_caducidad(char *caducidad, int cantdad_descli);

void baja_descuento_clientes(DescuentoCliente **desccli, int *cantdad_desccli,int candtdad_desc,int cantdad_cli, char *id_baja);

void actualizar_estado_descuentos_caducados(Descuento *desc,DescuentoCliente *desccli, int cant_desc);

void asignar_descuento(DescuentoCliente *desc_cliente, int cant_desc_cli);

void aplicar_descuento();