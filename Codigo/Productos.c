#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char id_prod[8];
    char descrip[51];
    char id_categ[5];
    char id_gestor[5];
    int stock;
    int entrega;
    float importe;
}Producto;

void alta_producto();
void baja_producto();
void busqueda_producto();
void listado_producto();
void modificaciones_producto();


void alta_producto(Producto* productos , int* tamanio_vector, char nuevo_id){
int ultimo_numero = 0;

    // Buscar el último número en los IDs existentes
    for (int i = 0; i < tamanio_vector; i++) {
        int numero_actual = atoi(productos[i].id_prod); // Convertir el ID actual a un número entero
        if (numero_actual > ultimo_numero) {
            ultimo_numero = numero_actual;
        }
    }

    // Generar el próximo ID incrementando en uno al último número encontrado
    sprintf(nuevo_id, "%04d", ultimo_numero + 1); // Formato del ID: 0001, 0002, etc.
}



