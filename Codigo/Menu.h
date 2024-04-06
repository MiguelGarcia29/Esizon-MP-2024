#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estructuras.h"

// Rol de administrador
// Solo puede acceder: Administrador
void mostrarPerfil();

// Rol de cliente
// Solo puede acceder: cliente y administrador
void menuusuario();

// Rol de administrador
// Solo puede acceder: Administrador
void menuadmin();

// Rol de proveedor
// Solo puede acceder: proveedor
void menuproveedor();

// Rol de transportista
// Solo puede acceder: transportista
void menutransportista();

// Esta opción permitirá a un usuario administrador consultar los datos de su perfil y modificarlos.
// Solo puede acceder: Administrador y clientes y transportista y proveedores
void muestraPerfil();

// Mediante esta opción el administrador podrá acceder a la información de los clientes dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de clientes.
// Solo puede acceder: Administrador
void mostrarClientes();

// Mediante esta opción el administrador podrá acceder a la información de los proveedores, de productos externos, dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de proveedores.
// Solo puede acceder: Administrador
void mostrarProveedores();

// Mediante esta opción el administrador podrá acceder a la información de los productos dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de productos.
// Solo puede acceder: Administrador y cliente y proveedor
void mostrarProductos();

// Mediante esta opción el administrador podrá acceder a la información de las categorías dadas de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de categorías. Además podrá generar listados de productos por categoría.
// Solo puede acceder: Administrador
void mostrarCategorias();

// Mediante esta opción el administrador podrá acceder a la información de los pedidos dados de alta en la plataforma.
// Solo puede acceder: Administrador y cliente y proveedores
void mostrarPedidos();

// Mediante esta opción el administrador podrá acceder a la información de todos los transportistas dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de transportistas.
// Solo puede acceder: Administrador
void mostrarTransportista();

// Mediante esta opción el administrador podrá acceder a la información de todos los códigos promocionales y/o cheques regalo dados de alta en la plataforma.
// Solo puede acceder: Administrador y cliente
void mostrarDescuentos();

// Mediante esta opción el administrador podrá acceder a la información de todas las devoluciones de productos.
// Solo puede acceder: Administrador y cliente
void mostrarDevoluciones();

// Esta opción permitirá al transportista consultar la lista de productos que tiene asignados para su entrega así como la fecha prevista para la misma, lo que le permite realizar su ruta de reparto.
// Solo puede acceder: transportista
void enReparto();

// El sistema facilitará al transportista la tarea de retornar a origen todos los productos que no hayan sido recogidos de los lockers en el plazo determinado, permitiéndole consultar todos los lockers por localidad y mostrando sus pedidos. En el momento de la recogida de los productos
// para su retorno, el sistema debe actualizar automáticamente el número de compartimentos
// ocupados y eliminar el código locker asociado al producto. Así como el estado de los productos
// y el stock de los mismos para que quede reflejada la operación
// Solo puede acceder: transportista
void retornoProducto();

// Esta opción permitirá al transportista consultar la lista de productos que tiene asignados para su entrega así como la fecha prevista para la misma, lo que le permite realizar su ruta de reparto.
// Solo puede acceder: Administrador y clientes y transportista y proveedor
void salirprograma();

#endif // MENU_H
