
#include "DescuentoCliente.h"

// Guarda el vector de DescuentosClientes en el archivo siguiendo la estructura:
/*
    o Identificador del cliente (Id_cliente), 7 dígitos.
    o Identificador del código promocional o cheque regalo (Id_cod), 10 caracteres máximo.
    o Fecha de asignación (día, mes y año)
    o Fecha de caducidad (día, mes y año)
    o Estado (Estado): 1 (Aplicado) ó 0 (No aplicado)
*/
void guardarDescuentosClientesEnArchivo(DescuentoCliente *descuentosClientes, int numDescuentosClientes)
{
    FILE *archivo = fopen(DescuentoCliente_txt, "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo DescuentosClientes.txt.\n");
        return;
    }

    for (int i = 0; i < numDescuentosClientes; i++)
    {
        fprintf(archivo, "%s-%s-%s-%s-%d\n",
                descuentosClientes[i].id_cliente,
                descuentosClientes[i].id_cod,
                descuentosClientes[i].fecha_asignacion,
                descuentosClientes[i].fecha_caducidad,
                descuentosClientes[i].estado);
    }

    fclose(archivo);
}

DescuentoCliente *iniciarDescuentosClientesDeArchivo(int *numDescC)
{
    FILE *archivo = fopen(DescuentoCliente_txt, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s.\n", DescuentoCliente_txt);
        return NULL;
    }

    // Contar la cantidad de lineas en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA]; // Longitud maxima de linea
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear el vector de DescuentoCliente
    DescuentoCliente *descuentos =(DescuentoCliente *) malloc(count * sizeof(DescuentoCliente));
    if (descuentos == NULL)
    {
        fclose(archivo);
        printf("Error: No se pudo asignar memoria para el vector de DescuentoCliente.\n");
        return NULL;
    }

    // Leo cada linea y rellenar el vector de adminProv
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL)
    {
        char *token = strtok(buffer, "-");
        strncpy(descuentos[i].id_cliente, token, sizeof(descuentos[i].id_cliente));
        token = strtok(NULL, "-");
        strncpy(descuentos[i].id_cod, token, sizeof(descuentos[i].id_cod));
        token = strtok(NULL, "-");
        strncpy(descuentos[i].fecha_asignacion, token, sizeof(descuentos[i].fecha_asignacion));
        token = strtok(NULL, "-");
        strncpy(descuentos[i].fecha_caducidad, token, sizeof(descuentos[i].fecha_caducidad));
        token = strtok(NULL, "-");
        descuentos[i].estado = atoi(token);
        i++;
    }

    fclose(archivo);
    *numDescC = count;
    return descuentos;
}
