#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    struct Info info[5];
    int op;

    while(1){
        printf("Ingrese una de las siguientes opciones: \n"
            "1. Ingresar datos del dia actual\n"
            "2. Monitoreo de contaminacion actual\n"
            "3. Prediccion de niveles futuros\n"
            "4. Calculo de promedios historicos\n"
            "5. Recomendaciones\n"
            "6. Salir\n"
            ">> ");
        scanf("%d", &op);
        if (op<1 || op>6){
            printf("Opcion invalida, ingrese un numero entre 1 y 6\n");
            continue;
        }
        switch(op){
            case 1:
                for (int i = 0; i < 5; i++) {
                    printf("Ingrese los datos de la zona %s\n", zonas[i]);
                    switch(i){
                        case 0:
                        getDiaActual(&info[i], "Data/calderon.csv");
                        break;
                        case 1:
                        getDiaActual(&info[i], "Data/cumbaya.csv");
                        break;
                        case 2:
                        getDiaActual(&info[i], "Data/pifo.csv");
                        break;
                        case 3:
                        getDiaActual(&info[i], "Data/tababela.csv");
                        break;
                        case 4:
                        getDiaActual(&info[i], "Data/tumbaco.csv");
                        break;
                }
                break;
            case 2:
                monitoreoActual("datos.csv");
                break;
            case 3:
                prediccionFuturo("datos.csv");
                break;
            case 4:
                promediosHistoricos("datos.csv");
                break;
            case 5:
                recomendaciones("datos.csv");
                break;
            case 6:
                writeReport();
                return 0;
        }
    }
    return 0;
}