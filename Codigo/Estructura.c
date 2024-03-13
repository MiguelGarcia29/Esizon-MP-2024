@ -0,0 +1,111 @@
//Estructura Cliente:

typedef struct Cliente{
    char id_cliente[8];
    char nomb_cliente[21];
    char dir_cliente[51];
    char localidad[21];
    char provincia[21];
    char email[31];
    char contraseña[16];
    float cartera;
};

typedef struct AdminProv{
    char id_empresa[5];
    char nombre[21];
    char email[31];
    char contraseña[16];
    char perfil_usuario[13]; // "administrador" o "proveedor"
};

typedef struct Producto{
    char id_prod[8];
    char descrip[51];
    char id_categ[5];
    char id_gestor[5];
    int stock;
    int entrega;
    float importe;
};

typedef struct Categoria{
    char id_categ[5];
    char descrip[51];
};

typedef struct Descuento{
    char id_cod[11];
    char descrip[51];
    char tipo[9]; // "codpro" o "cheqreg"
    char estado[9]; // "activo" o "inactivo"
    float importe;
    char aplicable[6]; // "todos" (si es aplicable a todos)
};

typedef struct DescuentoCliente{
    char id_cliente[8];
    char id_cod[11];
    char fecha_asignacion[11];
    char fecha_caducidad[11];
    int estado; // 1 (Aplicado) ó 0 (No aplicado)
};

typedef struct Locker{
    char id_locker[11];
    char localidad[21];
    char provincia[21];
    char ubicacion[21];
    int num_compt;
    int num_compocup;
};

typedef struct ComportamientoLocker{
    char id_locker[11];
    int num_comp;
    char cod_locker[11];
    char estado[7]; // "ocupado" o "vacío"
    char fecha_ocupacion[11];
    char fecha_caducidad[11];
};

typedef struct Pedido{
    char id_pedido[8];
    char fecha_pedido[11];
    char id_cliente[8];
    char lugar_entrega[10]; // "domicilio" o "locker"
    char id_locker[11];
    char id_cod[11];
};

typedef struct ProductoPedido{
    char id_pedido[8];
    char id_prod[8];
    int num_unid;
    char fecha_entrega_prevista[11];
    float importe;
    char estado_pedido[15]; // "enPreparación", "enviado", "enReparto", "enLocker", "entregado", "devuelto", "transportista"
    char id_transp[5];
    char id_locker[11];
    char cod_locker[11];
    char fecha_entrega_devolucion_transp[11];
};

typedef struct Transportista{
    char id_transp[5];
    char nombre[21];
    char email[31];
    char contraseña[16];
    char nombre_empresa[21];
    char ciudad_reparto[21];
};

typedef struct Devolucion{
    char id_pedido[8];
    char id_prod[8];
    char fecha_devolucion[11];
    char motivo[51];
    char estado[10]; // "pendiente", "aceptado", "denegado", "enviado", "recibido"
    char fecha_aceptacion[11];
    char fecha_caducidad[11];
};