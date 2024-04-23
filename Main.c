#include "Cliente.h"
#include "Descuentos.h"
#include "DescuentoCliente.h"
#include "Lockers.h"
#include "CompartimentosLockers.h"
#include "Categoria.h"
#include "Productos.h"
#include "Pedidos.h"
#include "Productos_pedidos.h"
#include "Devolucion.h"
#include "Proveedor.h"
#include "Transportista.h"

#include "Esizon.h"

int main(){
    Cliente *c;
    int nC;

    AdminProv *ap;
    int nAP;

    Categoria *cat;
    int numCat;

    CompartimentoLocker *cL;
    int numCL;

    DescuentoCliente *descCl;
    int numDesCli;

    Descuento *des;
    int numDes;

    Devolucion *dev;
    int numDev;

    Locker *lockers;
    int numL;

    Pedido *p;
    int numP;

    Producto *prod;
    int numProds;

    ProductoPedido *prodP;
    int numProdP;

    Transportista *t;
    int numT;


    inicializarDatos(&c,&nC,&ap,&nAP,&cL,&numCat,&cL,&numCL,&descCl,&numDesCli,&des,&numDes,&dev,&numDev,&lockers,&numL,&p,&numP,&prod,&numProds,&prodP,&numProdP,&t,&numT);

    accederPrograma (&c,&nC,&ap,&nAP,&cL,&numCat,&cL,&numCL,&descCl,&numDesCli,&des,&numDes,&dev,&numDev,&lockers,&numL,&p,&numP,&prod,&numProds,&prodP,&numProdP,&t,&numT);

    almacenarDatos(c,nC,ap,nAP,cat,numCat,cL,numCL,descCl,numDesCli,des,numDes,dev,numDev,lockers,numL,p,numP,prod,numProds,prodP,numProdP,t,numT);
}
