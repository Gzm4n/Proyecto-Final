#include <stdio.h>
#include <stdbool.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    const char zonas[5][15] = {"Calderon", "Cumbaya", "Pifo", "Tababela", "Tumbaco"};
    const char *fileNames[] = {"Data/data_calderon.csv", "Data/data_cumbaya.csv", "Data/data_pifo.csv", "Data/data_tababela.csv", "Data/data_tumbaco.csv"};
    struct Info info;
    int op1, op2;
    bool f1, f2, f3, f4;

    while(1){
        printf("Ingrese una de las siguientes opciones: \n"
            "1. Ingresar datos del dia actual\n"
            "2. Monitoreo de contaminacion actual\n"
            "3. Prediccion de niveles del dia de manana\n"
            "4. Calculo de promedios historicos\n"
            "5. Salir\n"
            ">> ");
        scanf("%d", &op1);
        while(getchar()!='\n');
        if (op1<1 || op1>5){
            printf("Opcion invalida, ingrese un numero entre 1 y 5\n");
            continue;
        }
        switch(op1){
            case 1:
                for (int i = 0; i < 5; i++) {
                    printf("Ingrese los datos de la zona %s\n", zonas[i]);
                    getDiaActual(info, fileNames[i]);
                }
                predictionAlerts();
                f1 = true;

                break;
            case 2:
                op2 = mainValid(f1);
                if (op2==2) break;
                monitorActual(&info);
                f2 = true;
                break;
            case 3:
                op2 = mainValid(f1);
                if (op2==2) break;
                predictTomorrow();
                f3 = true;
                break;
            case 4:
                historicalAvrgBySearch();
                f4 = true; 
                break;
            case 5:
                writeReport(f1, f2, f3, f4, &info);
                return 0;
        }
    }
    return 0;
}