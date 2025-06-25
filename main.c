#include <stdio.h>
#include "funcion.h"

int main() {
    Equipo equipos[NUM_EQUIPOS];
    Partido partidos[MAX_PARTIDOS];
    int numPartidos = 0;
    int opcion;

    inicializarEquipos(equipos);

    do {
        printf("\n--- LIGAPRO SERIE A 2025 ---\n");
        printf("1. Ingresar resultado de partido y goleadores\n");
        printf("2. Ver tabla de posiciones\n");
        printf("3. Ver historial de partidos jugados\n");
        printf("4. Ver goleador del torneo\n");
        printf("5. Ver goleador de cada equipo\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                registrarPartido(equipos, partidos, &numPartidos);
                break;
            case 2:
                mostrarTablaPosiciones(equipos);
                break;
            case 3:
                mostrarHistorialPartidos(partidos, numPartidos, equipos);
                break;
            case 4:
                imprimirGoleadoresTorneo(equipos);
                break;
            case 5:
                imprimirGoleadoresPorEquipo(equipos);
                break;
            case 6:
                printf("Programa finalizado.\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 6);

    return 0;
}