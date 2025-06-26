#include <stdio.h>
#include <string.h>
#include "funcion.h"

int main(int argc, char const *argv[])
{
    struct Producto productos[8];
    struct Venta ventas[5];
    int opcion, numVentas = 0;
    int numProductosActuales = 5; // 5 productos iniciales

    do
    {
        printf("\n-----------------------------------\n");
        printf("SISTEMA DE GESTION DE REPUESTOS DE VEHICULOS\n");
        printf("\n");
        printf("MENU DE OPCIONES:\n");
        fflush(stdin);
        opcion = menu();
        printf("\n-----------------------------------\n");

        switch (opcion)
        {
        case 1:
            inicializarProductos(productos, &numProductosActuales);
            break;
        case 2:
            if(leerProductos(productos, &numProductosActuales) == 0){
                printf("No hay repuestos disponibles.\n");
            }else{
                imprimirProductos(productos, numProductosActuales);
            }
            break;
        case 3:
            realizarVenta(ventas, productos, numProductosActuales, &numVentas);
            break;
        case 4:
            leerVentas(ventas, &numVentas);
            if (numVentas == 0) {
                printf("No hay ventas registradas.\n");
            } else {
                listarVentas(ventas, numVentas);
            }
            break;
        case 5:
            buscarVenta();
            break;
        case 6:
            agregarProductoAdicional(productos, &numProductosActuales);
            break;
        default:
            break;
        }
    } while (opcion != 7);

    return 0;
}