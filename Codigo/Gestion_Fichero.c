#include <stdio.h>

#define TAMANIO_MAXIMO_LINEA 256
#define Clientes_txt "Datos/Clientes.txt"
#define AdminProv_txt "Datos/AdminProv.txt"

typedef struct{
    char id_cliente[8];
    char nomb_cliente[21];
    char dir_cliente[51];
    char localidad[21];
    char provincia[21];
    char email[31];
    char contrasenia[16];
    float cartera;
}Cliente;

typedef struct{
    char id_empresa[5];
    char nombre[21];
    char email[31];
    char contrasenia[16];
    char perfil_usuario[13]; // "administrador" o "proveedor"
} AdminProv;

//Guarda el vector de clientes en el archivo siguiendo la estructura:
/*  o Identificador del cliente (Id_cliente), 7 dígitos.
    o Nombre completo del cliente (Nomb_cliente), 20 caracteres máximo.
    o Dirección del cliente (Dir_cliente), 50 caracteres máximo.
    o Población (Localidad), 20 caracteres máximo.
    o Provincia (Provincia), 20 caracteres máximo.
    o Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la
    plataforma.
    o Contrasenia para acceder al sistema (Contrasenia), con 15 caracteres máximo.
    o Cartera (Cartera), almacenará el dinero del que dispone el cliente para poder adquirir los
    productos.
    */

void guardarClientesEnArchivo(Cliente *clientes, int numClientes) {
    FILE *archivo = fopen(Clientes_txt , "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s.\n", Clientes_txt);
        return;
    }

    for (int i = 0; i < numClientes; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%s-%s-%s-%.2f\n",
                clientes[i].id_cliente,
                clientes[i].nomb_cliente,
                clientes[i].dir_cliente,
                clientes[i].localidad,
                clientes[i].provincia,
                clientes[i].email,
                clientes[i].contrasenia,
                clientes[i].cartera);
    }

    fclose(archivo);
}

//LE PASO COMO PUNTERO EL NUM DE CLIENTES PARA LUEGO PODER ALMACENARLO EN EL PROGRAMA (MAIN)
Cliente* leerClientesDeArchivo(int *numClientes) {
    FILE *archivo = fopen(Clientes_txt, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s.\n", Clientes_txt);
        return NULL;
    }

    // Contar la cantidad de lineas = clientes en el archivo
    int count = 0;
    char buffer[TAMANIO_MAXIMO_LINEA];
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA,archivo) != NULL) {
        count++;
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Crear vector cliente
    Cliente *clientes = malloc(count * sizeof(Cliente));
    if (clientes == NULL) {
        fclose(Clientes_txt);
        printf("No se pudo asignar memoria para el vector de clientes.\n");
        return NULL;
    }

    // Leer cada linea del archivo y rellenar el vector de clientes
    int i = 0;
    while (fgets(buffer, TAMANIO_MAXIMO_LINEA, archivo) != NULL) {
        // Strtok sirve para dividir la cadena en subcadenas por "-" 
        // - OS ADJUNTO DOCUMENTACION CONSULTADA: https://www.ibm.com/docs/es/i/7.5?topic=functions-strtok-tokenize-string
        // - VIDEO QUE LO EXPLICA CON SUMA: https://www.youtube.com/watch?v=jHdbmHCVQ2c
        char *token = strtok(buffer, "-");
        strncpy(clientes[i].id_cliente, token, sizeof(clientes[i].id_cliente));
        token = strtok(NULL, "-");
        strncpy(clientes[i].nomb_cliente, token, sizeof(clientes[i].nomb_cliente));
        token = strtok(NULL, "-");
        strncpy(clientes[i].dir_cliente, token, sizeof(clientes[i].dir_cliente));
        token = strtok(NULL, "-");
        strncpy(clientes[i].localidad, token, sizeof(clientes[i].localidad));
        token = strtok(NULL, "-");
        strncpy(clientes[i].provincia, token, sizeof(clientes[i].provincia));
        token = strtok(NULL, "-");
        strncpy(clientes[i].email, token, sizeof(clientes[i].email));
        token = strtok(NULL, "-");
        strncpy(clientes[i].contrasenia, token, sizeof(clientes[i].contrasenia));
        token = strtok(NULL, "-");
        clientes[i].cartera = atof(token); // atof convierte la cadena en Float.
        i++;
    }

    fclose(archivo);
    *numClientes = count;
    return clientes;
}

//Guarda el vector de AdminYProvs en el archivo siguiendo la estructura:
/*
    o Identificador de la empresa administradora o proveedora (Id_empresa), 4 dígitos.
    o Nombre de la empresa (Nombre), sería ESIZON si es administrador, 20 caracteres máximo.
    o Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la
    plataforma.
    o Contrasenia para acceder al sistema (Contrasenia), con 15 caracteres máximo.
    o Perfil del usuario (Perfil_usuario): «administrador» o «proveedor».
*/
void guardarAdminProvEnArchivo(AdminProv *admins, int numAdmins) {
    FILE *archivo = fopen(AdminProv_txt, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s.\n",AdminProv_txt);
        return;
    }

    for (int i = 0; i < numAdmins; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%s\n",
                admins[i].id_empresa,
                admins[i].nombre,
                admins[i].email,
                admins[i].contrasenia,
                admins[i].perfil_usuario);
    }

    fclose(archivo);
}


int main() {
    
    AdminProv admins[2] = {
        {"0001", "ESIZON", "antonio.martin@esizon.com", "antonimar01", "administrador"},
        {"0002", "ROTAZON", "jorgelopeeez@ROTAZON.com", "rotazon05", "proveedor"}
    };

    guardarAdminProvEnArchivo(admins, 2);
    printf("Datos de AdminProv guardados en el archivo AdminProv.txt.\n");

    return 0;

}
