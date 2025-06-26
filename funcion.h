#ifndef FUNCION_H
#define FUNCION_H

#include <stdio.h>
#include <string.h>

struct Cliente
{
    char nombre[30];
    int cedula;
};

struct Producto
{
    char nombre[30];
    float precio;
    int stock; // cantidad disponible en inventario
};

struct Venta
{
    struct Cliente clientes;
    int numProductos;
    struct Producto productos[5];
    float totalVenta;
};

void leerCadena(char *cadena, int num);
int menu();
void inicializarProductos(struct Producto productos[8], int *numProductosActuales);
void imprimirProductos(struct Producto productos[8], int numProductosActuales);
void guardarProductos(struct Producto *productos, int numProductosActuales);
int leerProductos(struct Producto productos[8], int *numProductosActuales);
void realizarVenta(struct Venta ventas[5], struct Producto productos[8], int numProductosActuales, int *numVentas);
void listarVentas(struct Venta *ventas, int numVentas);
void guardarVentas(struct Venta *ventas, int numVentas);
int leerVentas(struct Venta *ventas, int *numVentas);
void buscarVenta();
void agregarProductoAdicional(struct Producto productos[8], int *numProductosActuales);

#endif // FUNCION_H