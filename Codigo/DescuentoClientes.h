//DescuentoClientes

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"descuentos.h"
#include"Cliente.h"
#include"Productos.h"

typedef struct {
    char id_cliente[8];
    char id_cod[11];
    char fecha_asignacion[11];
    char fecha_caducidad[11];
    int estado; // 1 (Aplicado) o 0 (No aplicado)
}DescuentoCliente;

void rellenar_descuentocliente(Descuento desc[], Cliente clientes[], DescuentoCliente **desccliente, int cantdad_desc, int cantdad_cli, int *cantdad_desccli);

void mostrar_descuentos_cliente(char id_cliente[8], Descuento *desc, DescuentoCliente *desc_cliente, int cant_desc, int cant_desc_cli);

void anadir_fecha_caducidad(char *caducidad, int cantdad_descli);

void baja_descuento_clientes(DescuentoCliente **desccli, int *cantdad_desccli,int candtdad_desc,int cantdad_cli, char *id_baja);

void actualizar_estado_descuentos_vencidos(Descuento *desc,DescuentoCliente *desccli, int cant_desc);

void asignar_descuento(DescuentoCliente *desc_cliente, int cant_desc_cli);

void aplicar_descuento(float *precio,Descuento *desc,DescuentoCliente *desccli,char id_cliente[8],Producto *prod,int cantdad_desc,int cantdad_desccli,int numprodpe);









