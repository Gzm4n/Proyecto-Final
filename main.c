#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    const char zonas[5][15] = {"Calderon", "Cumbaya", "Pifo", "Tababela", "Tumbaco"};
    struct Info info;
    int op1, op2, f1;

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
                    switch(i){
                        case 0:
                        getDiaActual(&info, "Data/calderon.csv");
                        break;
                        case 1:
                        getDiaActual(&info, "Data/cumbaya.csv");
                        break;
                        case 2:
                        getDiaActual(&info, "Data/pifo.csv");
                        break;
                        case 3:
                        getDiaActual(&info, "Data/tababela.csv");
                        break;
                        case 4:
                        getDiaActual(&info, "Data/tumbaco.csv");
                        break;
                    }
                }
                f1 = 1;
                break;
            case 2:
                if (!f1){
                    printf("No se han ingresado datos del dia actual\n");
                    while(1){        
                        printf ("Deseas monitorear los ultimos datos guardados?\n"
                                "1. Si\n"
                                "2. No\n"
                                ">> ");
                        scanf("%d", &op2);
                        if (op2==1){
                            monitorActual(&info);
                            break;
                        }else if (op2==2){
                            printf("Regresando al menu principal\n");
                            break;
                        }else{
                        printf("Opcion invalida, ingrese un numero entre 1 y 2\n");
                        continue;
                        }
                    }
                }else monitorActual(&info);
                break;
            case 3:
                predictTomorrow(); //adds comparation and recommendation
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