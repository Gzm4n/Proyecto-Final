#include <stdio.h>
#include <stdbool.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    //Todos los calculos incluyen las condiciones climaticas correspondientes.

    const char zonas[5][15] = {"Calderon", "Cumbaya", "Pifo", "Tababela", "Tumbaco"}; //Zonas evaluadas
    const char *fileNames[] = {"Data/data_calderon.csv", "Data/data_cumbaya.csv", "Data/data_pifo.csv", "Data/data_tababela.csv", "Data/data_tumbaco.csv"}; //Ubicacion y nombre de los archivos
    struct Info info; //Inicializacion de estructura
    int op1, op2; //Opciones para el menu
    bool f1, f2, f3, f4; //Flag para evaluar el uso de cada una de las funciones en el menu, para posterior analisis en reportes.txt

    while(1){ //Menu con validacion infinita
        printf("\nIngrese una de las siguientes opciones: \n"
            "1. Ingresar datos del dia actual\n"
            "2. Monitoreo de contaminacion actual\n"
            "3. Prediccion de niveles del dia de manana\n"
            "4. Calculo de promedios historicos\n"
            "5. Salir\n"
            ">> ");
        scanf("%d", &op1);
        while(getchar()!='\n'); //Limpieza de buffer
        if (op1<1 || op1>5){
            printf("Opcion invalida, ingrese un numero entre 1 y 5\n");
            continue; //Salta la iteracion
        }
        switch(op1){
            case 1: //Ingresar datos del dia actual
                for (int i = 0; i < 5; i++) {
                    printf("\nIngrese los datos de la zona %s\n", zonas[i]);
                    getDiaActual(info, fileNames[i]);
                }
                predictionAlerts(); //Se evalua con todos los datos en todas las zonas para, mediante un promedio ponderado, emitir alertas en caso de que se prevea peligro en alguna zona
                f1 = true; //El uso vuelve a la bandera verdadera (stdbool.h)

                break;
            case 2: //Monitorear la contaminacion del ultimo dato en la base
                op2 = mainValid(f1); //Evalua si se ingresaron datos del ultimo dia
                if (op2==2) break;
                monitorActual(&info);
                f2 = true;
                break;
            case 3: //Predecir los valores el dia de manana (promedio ponderado)
                op2 = mainValid(f1); //Evalua si se ingresaron datos del ultimo dia
                if (op2==2) break;
                predictTomorrow();
                f3 = true;
                break;
            case 4: //Realizar el promedido general de los ultimos 30 dias.
                historicalAvrgBySearch();
                f4 = true; 
                break;
            case 5: //Cierra el programa y obligatoriamente escribe un reporte de su uso.
                writeReport(f1, f2, f3, f4, &info);
                return 0;
        }
    }
    return 0;
}