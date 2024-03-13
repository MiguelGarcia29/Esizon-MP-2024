#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id_categ[5];
    char descrip[51];
}Categoria;


//La función muestra la información de la categoria del producto requerido. 
void almacenar(Categoria* cat);

void mostrar_categ(Categoria* cat){
    
    for(int i = 0 ; strcmp(cat[i].id_categ,'-1') != 0 ; i++)//Comparamos nuestro vector de Id_categ con el -1,indica el final de este.
    { 

        printf("%c-%c \n",cat[i].id_categ , cat[i].descrip); // A medida que avanza el vector, muestra cada descripcion de el producto que corresponde.
    }
    printf("----------");
    return 0;
}
