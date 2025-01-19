#include <stdio.h>
#include <stdbool.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    const char zonas[5][15] = {"Calderon", "Cumbaya", "Pifo", "Tababela", "Tumbaco"};
    const char fileNames[5][30] = {"Data/calderon.csv", "Data/cumbaya.csv", "Data/pifo.csv", "Data/tababela.csv", "Data/tumbaco.csv"};
    struct Info info;
    int op1, op2;
    bool f1;

    while(1){
        printf("Ingrese una de las siguientes opciones: \n"
            "1. Ingresar datos del dia actual\n"
            "2. Monitoreo de contaminacion actual\n"
            "3. Prediccion de niveles del dia de manana\n"
            "4. Calculo de promedios historicos\n"
            "5. Recomendaciones\n"
            "6. Salir\n"
            ">> ");
        scanf("%d", &op1);
        if (op1<1 || op1>5){
            printf("Opcion invalida, ingrese un numero entre 1 y 6\n");
            continue;
        }
        switch(op1){
            case 1:
                for (int i = 0; i < 5; i++) {
                    printf("Ingrese los datos de la zona %s\n", zonas[i]);
                    getDiaActual(&info, fileNames[i]);
                    predictionAlerts();
                    f1 = true;
                }
                break;
            case 2:
                op2 = mainValid(f1);
                if (op2==2) break;
                monitorActual(&info);
                break;
            case 3:
                op2 = mainValid(f1);
                if (op2==2) break;
                predictTomorrow();
                break;
            case 4:
                historicalAverage();
                break;
            case 5:
                writeReport();
                return 0;
        }
    }
    return 0;
}