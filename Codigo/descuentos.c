//Descuentos

#include"descuentos.h"

char *generar_id_descuentos(Descuento *desc, int cantdad_desc);

int encontrar_descuento(int cantdad_desc, Descuento *desc, char *id);

void flushInputBuffer();



char *generar_id_descuentos(Descuento *desc, int cantdad_desc) {
    int id_generada = 1;
    
    if (cantdad_desc != 0) {
        id_generada = atoi(desc[cantdad_desc - 1].id_cod);
        id_generada++;
    }
    
    char *id = malloc(11 * sizeof(char));
    
    if (id == NULL) {
        printf("Error al guardar en memoria\n");
        return NULL;
    }
    sprintf(id, "%010d", id_generada);
    
    return id;
}


void alta_descuentos(Descuento **desc, int *cantdad_desc) {
    int a;
    Descuento nuevo_descuento;

    printf("Descripcion: ");
    fgets(nuevo_descuento.descrip, 51, stdin);
    nuevo_descuento.descrip[strcspn(nuevo_descuento.descrip, "\n")] = '\0';

    printf("Tipo:\n");
    printf("(1) Codigo promocional\n");
    printf("(2) Cheque regalo\n");
    scanf("%d", &a);
                flushInputBuffer();

    switch (a) {
        case 1:
            strcpy(nuevo_descuento.tipo, "codpro");
        break;
        case 2:
            strcpy(nuevo_descuento.tipo, "cheqreg");
        break;
        default:
            printf("\nError\n\n");
            exit(EXIT_FAILURE);
        break;
    }

    printf("Aplicabilidad:\n");
    printf("(1) Todos\n");
    printf("(2) Solo ESIZON\n");
    scanf("%d", &a);
                flushInputBuffer();

    switch (a) {
        case 1:
            strcpy(nuevo_descuento.aplicable, "todos");
        break;
        case 2:
            strcpy(nuevo_descuento.aplicable, "esizon");
        break;
        default:
            printf("\nError\n\n");
            exit(EXIT_FAILURE);
        break;
    }

    printf("Importe: ");
    scanf("%f", &nuevo_descuento.importe);
                    flushInputBuffer();

    printf("Estado:\n");
    printf("(1) Activo\n");
    printf("(2) Inactivo\n");
    scanf("%d", &a);
                flushInputBuffer();

    switch (a) {
        case 1:
            strcpy(nuevo_descuento.estado, "activo");
        break;
        case 2:
            strcpy(nuevo_descuento.estado, "inactivo");
        break;
        default:
            printf("\nError\n\n");
            exit(EXIT_FAILURE);
        break;
    }

    strcpy(nuevo_descuento.id_cod, generar_id_descuentos(*desc, *cantdad_desc));
    
    printf("Su id es: %s\n", nuevo_descuento.id_cod);

    *desc = (Descuento *)realloc(*desc, (*cantdad_desc + 1) * sizeof(Descuento));
    (*desc)[*cantdad_desc] = nuevo_descuento;
    (*cantdad_desc)++;
}


void baja_descuentos(Descuento **desc, int *cantdad_desc, char *id_baja) {
    int encontrado = 0, i, j;
    
    for (i = 0; i < *cantdad_desc && encontrado == 0; i++) {
        if (strcmp((*desc)[i].id_cod, id_baja) == 0) {
            encontrado = 1;
            
            for (j = i; j < *cantdad_desc - 1; j++) {
                (*desc)[j] = (*desc)[j + 1];
            }
            
            (*cantdad_desc)--;
            *desc = realloc(*desc, (*cantdad_desc) * sizeof(Descuento));
            printf("\nBaja efectuada.\n\n");
        }
    }
    if (encontrado == 0) {
        printf("\nDescuento no encontrado\n\n");
    }
}


void modificar_descuento(Descuento *desc, int cantdad_desc, char *id) {
    int opcion, i;
    
    i = encontrar_descuento(cantdad_desc, desc, id);
    
    if (i != -1) {
        printf("\nSeleccione que desea modificar:\n");
        printf("(1) Estado\n");
        printf("(2) Importe\n");
        scanf("%d", &opcion);
                        flushInputBuffer();

        switch (opcion) {
            case 1:
                printf("\nNuevo estado\n\n");
                printf("(1) Activo\n");
                printf("(2) Inactivo\n");
                scanf("%d", &opcion);
                flushInputBuffer();
                if (opcion == 1)
                    strcpy(desc[i].estado, "activo");
                else if (opcion == 2)
                    strcpy(desc[i].estado, "inactivo");
                else
                    printf("\nOpcion invalida\n");
            break;
            case 2:
                printf("\nNuevo importe: ");
                scanf("%f", &desc[i].importe);
            break;
            default:
                printf("\nOpcion invalida\n");
            break;
        }
    } else {
        printf("Descuento no encontrado\n");
    }
}


int encontrar_descuento(int cantdad_desc, Descuento *desc, char *id) {
    int i, encontrado = 0;
    
    for (i = 0; i < cantdad_desc && encontrado == 0; i++) {
        if (strcmp(desc[i].id_cod, id) == 0) {
            encontrado = 1;
        }
    }
    if (encontrado == 0) {
        i = 0;
    }
    
    return i - 1;
}


void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}






























