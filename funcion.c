#include <stdio.h>
#include <string.h>
#include "funcion.h"

#define PRODUCTOS_FIJOS 5
#define TOTAL_PRODUCTOS 8

void leerCadena(char *cadena, int num)
{
    fflush(stdin);
    fgets(cadena, num, stdin);
    int len = strlen(cadena) - 1;
    if (len >= 0 && cadena[len] == '\n') {
        cadena[len] = '\0';
    }
}

int menu()
{
    int opc;
    printf("Seleccione una opcion\n");
    printf("1. Inicializar repuestos.\n");
    printf("2. Imprimir repuestos.\n");
    printf("3. Realizar Venta.\n");
    printf("4. Listar Ventas.\n");
    printf("5. Buscar Ventas.\n");
    printf("6. Agregar producto adicional.\n");
    printf("7. Salir.\n");
    printf(">> ");
    scanf("%d", &opc);
    return opc;
}

void inicializarProductos(struct Producto productos[8], int *numProductosActuales)
{
    strcpy(productos[0].nombre, "Filtro de Aceite");
    productos[0].precio = 50.0;
    productos[0].stock = 20;

    strcpy(productos[1].nombre, "Bujia");
    productos[1].precio = 30.0;
    productos[1].stock = 40;

    strcpy(productos[2].nombre, "Pastilla de Freno");
    productos[2].precio = 80.0;
    productos[2].stock = 15;

    strcpy(productos[3].nombre, "Correa de Distribucion");
    productos[3].precio = 120.0;
    productos[3].stock = 10;

    strcpy(productos[4].nombre, "Bateria");
    productos[4].precio = 250.0;
    productos[4].stock = 8;

    *numProductosActuales = PRODUCTOS_FIJOS; // Solo los 5 fijos al iniciar

    guardarProductos(productos, *numProductosActuales);
    printf("Productos inicializados correctamente (solo los 5 fijos).\n");
}

void imprimirProductos(struct Producto productos[8], int numProductosActuales)
{
    printf("REPUESTOS DISPONIBLES\n");
    printf("#\tNombre\t\t\tPrecio\tStock\n");
    for (int i = 0; i < numProductosActuales; i++)
    {
        printf("%d\t%-20s\t%.2f\t%d\n", i, productos[i].nombre, productos[i].precio, productos[i].stock);
    }
}

void guardarProductos(struct Producto *productos, int numProductosActuales)
{
    FILE *f;
    f = fopen("producto.dat", "wb+");
    if (f == NULL) {
        printf("Error al guardar productos.\n");
        return;
    }
    fwrite(&numProductosActuales, sizeof(int), 1, f); // Guardar cantidad
    fwrite(productos, sizeof(struct Producto), numProductosActuales, f);
    fclose(f);
}

int leerProductos(struct Producto productos[8], int *numProductosActuales)
{
    FILE *f;
    f = fopen("producto.dat", "rb+");
    if (f == NULL) {
        printf("No existe el archivo de productos.\n");
        *numProductosActuales = 0;
        return 0;
    }
    fread(numProductosActuales, sizeof(int), 1, f);
    fread(productos, sizeof(struct Producto), *numProductosActuales, f);
    fclose(f);
    return 1;
}

void agregarProductoAdicional(struct Producto productos[8], int *numProductosActuales)
{
    if (*numProductosActuales >= TOTAL_PRODUCTOS) {
        printf("Ya ha ingresado el máximo de productos adicionales permitidos (3).\n");
        return;
    }
    printf("Ingrese el nombre del producto #%d: ", *numProductosActuales + 1);
    fflush(stdin); // Limpiar buffer antes de leer cadena
    leerCadena(productos[*numProductosActuales].nombre, 30);
    printf("Ingrese el precio del producto #%d: ", *numProductosActuales + 1);
    scanf("%f", &productos[*numProductosActuales].precio);
    fflush(stdin); // Limpiar buffer antes de leer el siguiente dato
    printf("Ingrese el stock del producto #%d: ", *numProductosActuales + 1);
    scanf("%d", &productos[*numProductosActuales].stock);
    fflush(stdin); // Limpiar buffer por si acaso

    (*numProductosActuales)++;
    guardarProductos(productos, *numProductosActuales);
    printf("Producto adicional agregado correctamente.\n");
}

void realizarVenta(struct Venta ventas[5], struct Producto productos[8], int numProductosActuales, int *numVentas)
{
    // Leer productos actualizados desde archivo
    leerProductos(productos, &numProductosActuales);

    if (*numVentas >= 5) {
        printf("No se pueden registrar más ventas.\n");
        return;
    }
    struct Venta nuevaVenta;
    int numProductos, productoIndex, cantidad;
    printf("Ingrese el nombre del cliente: ");
    fflush(stdin); // Limpiar buffer antes de leer cadena
    leerCadena(nuevaVenta.clientes.nombre, 30);
    printf("Ingrese la cedula del cliente: ");
    scanf("%d", &nuevaVenta.clientes.cedula);
    fflush(stdin);

    printf("Ingrese el numero de productos diferentes a comprar (max 5): ");
    scanf("%d", &numProductos);
    fflush(stdin);
    if (numProductos > 5 || numProductos < 1) {
        printf("Numero de productos no valido, se limitará a 5.\n");
        return;
    }
    nuevaVenta.numProductos = numProductos;
    nuevaVenta.totalVenta = 0.0;

    for (int i = 0; i < numProductos; i++) {
        imprimirProductos(productos, numProductosActuales);
        printf("Seleccione el producto (0-%d): ", numProductosActuales-1);
        scanf("%d", &productoIndex);
        fflush(stdin);
        if (productoIndex < 0 || productoIndex >= numProductosActuales) {
            printf("Producto no valido, intente de nuevo.\n");
            i--;
            continue;
        }
        printf("Ingrese la cantidad a comprar (Stock disponible: %d): ", productos[productoIndex].stock);
        scanf("%d", &cantidad);
        fflush(stdin);

        if (cantidad < 1 || cantidad > productos[productoIndex].stock) {
            printf("Cantidad no valida o insuficiente stock. Intente de nuevo.\n");
            i--;
            continue;
        }
        // Registrar producto en venta
        nuevaVenta.productos[i] = productos[productoIndex];
        nuevaVenta.productos[i].stock = cantidad; // Aquí, 'stock' significa la cantidad comprada en la venta
        nuevaVenta.totalVenta += productos[productoIndex].precio * cantidad;
        productos[productoIndex].stock -= cantidad; // Descontar del stock original
    }

    ventas[*numVentas] = nuevaVenta;
    (*numVentas)++;
    guardarProductos(productos, numProductosActuales);
    guardarVentas(ventas, *numVentas);
    printf("Venta realizada exitosamente. Total: %.2f\n", nuevaVenta.totalVenta);
}

void listarVentas(struct Venta *ventas, int numVentas)
{
    if (numVentas == 0) {
        printf("No hay ventas registradas.\n");
        return;
    }
    printf("LISTA DE VENTAS\n");
    for (int i = 0; i < numVentas; i++) {
        printf("Venta #%d:\n", i + 1);
        printf("Cliente: %s, Cedula: %d\n", ventas[i].clientes.nombre, ventas[i].clientes.cedula);
        printf("Productos:\n");
        for (int j = 0; j < ventas[i].numProductos; j++) {
            printf("- %s (Cantidad: %d): %.2f\n", ventas[i].productos[j].nombre, ventas[i].productos[j].stock, ventas[i].productos[j].precio);
        }
        printf("Total de la venta: %.2f\n", ventas[i].totalVenta);
        printf("-------------------------\n");
    }
}

void guardarVentas(struct Venta *ventas, int numVentas)
{
    FILE *f;
    f = fopen("ventas.dat", "wb+");
    if (f == NULL) {
        printf("Error al abrir el archivo de ventas.\n");
        return;
    }
    fwrite(ventas, sizeof(struct Venta), numVentas, f);
    fclose(f);
}

int leerVentas(struct Venta *ventas, int *numVentas)
{
    FILE *f;
    f = fopen("ventas.dat", "rb+");
    if (f == NULL) {
        printf("No existe el archivo de ventas.\n");
        *numVentas = 0;
        return 0;
    }
    *numVentas = fread(ventas, sizeof(struct Venta), 5, f);
    fclose(f);
    return 1;
}

void buscarVenta()
{
    int cedulabuscar;
    struct Venta ventas[5];
    int numVentas = 0;
    leerVentas(ventas, &numVentas);
    printf("Ingrese la cedula del cliente a buscar: ");
    scanf("%d", &cedulabuscar);
    int encontrado = 0;
    for (int i = 0; i < numVentas; i++) {
        if (ventas[i].clientes.cedula == cedulabuscar) {
            printf("Venta encontrada:\n");
            printf("Cliente: %s, Cedula: %d\n", ventas[i].clientes.nombre, ventas[i].clientes.cedula);
            printf("Productos:\n");
            for (int j = 0; j < ventas[i].numProductos; j++) {
                printf("- %s (Cantidad: %d): %.2f\n", ventas[i].productos[j].nombre, ventas[i].productos[j].stock, ventas[i].productos[j].precio);
            }
            printf("Total de la venta: %.2f\n", ventas[i].totalVenta);
            encontrado = 1;
        }
    }
    if (!encontrado){
        printf("No se encontraron ventas para la cedula %d.\n", cedulabuscar);
    }
}