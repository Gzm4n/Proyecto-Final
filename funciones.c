#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "funciones.h"

const char zonas[5][15] = {"Calderon", "Cumbaya", "Pifo", "Tababela", "Tumbaco"};

const char fileNames[5][15] = {"Data/calderon.csv", "Data/cumbaya.csv", "Data/pifo.csv", "Data/tababela.csv", "Data/tumbaco.csv"};

const float co2Breakpoints[6][4] = {
    {0.0, 350.0, 0, 50},
    {351.0, 450.0, 51, 100},
    {451.0, 700.0, 101, 150},
    {701.0, 1000.0, 151, 200},
    {1001.0, 1500.0, 201, 300},
    {1501.0, 2000.0, 301, 500}
};
const float so2Breakpoints[6][4] = {
    {0.0, 20.0, 0, 50},
    {20.1, 80.0, 51, 100},
    {80.1, 365.0, 101, 150},
    {365.1, 800.0, 151, 200},
    {800.1, 1600.0, 201, 300},
    {1600.1, 2100.0, 301, 500}
};
const float no2Breakpoints[6][4] = {
    {0.0, 40.0, 0, 50},
    {40.1, 80.0, 51, 100},
    {80.1, 180.0, 101, 150},
    {180.1, 280.0, 151, 200},
    {280.1, 400.0, 201, 300},
    {400.1, 500.0, 301, 500}
};
const float pm25Breakpoints[6][4] = {
    {0.0, 12.0, 0, 50},
    {12.1, 35.4, 51, 100},
    {35.5, 55.4, 101, 150},
    {55.5, 150.4, 151, 200},
    {150.5, 250.4, 201, 300},
    {250.5, 500.4, 301, 500}
};

void getString(char string[], int length){
    while (getchar()!='\n');
    fgets(string, length, stdin);
    string[strcspn(string, "\n")]='\0';

}

void validNumData(float *data, float min, float max){
    scanf("%f", &data);
    float aux = *data;
    while (aux<min || aux>max || !aux){
        if (!aux){
            while (getchar()!='\n');
        }
        printf("Dato invalido, ingrese un numero entre %d y %d: ", min, max);
        scanf("%f", &aux);
    }
    *data = aux;
}

void mayus(char string[15]){
    if (string[0] != '\0' && islower(string[0])) {
        string[0] = toupper(string[0]);
    }
}

void openFileError(FILE *file){
    if (file == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }
}

bool checkZona(char zona[15]){
    for (int i=0; i<10; i++){
        if (strcmp(zona, zonas[i])==0){
            return true;
        }
    }
    return false;
}

void getDate(char *date){
    char try[11];
    printf("Ingrese la fecha en formato YYYY-MM-DD (Los guiones son importantes): ");
    getString(try, 10);
    while(1){
        if (strlen(try)!=10 || try[4]!='-' || try[7]!='-' || atoi(try)>2025 || atoi(try+5)>12 || atoi(try+8)>31){  
            printf("Fecha invalida, ingrese la fecha en formato YYYY-MM-DD: ");
            getString(try, 10);
        } else break;
    }
    strcpy(date, try);
}

void updateData(const char *filename, struct Info *info){
    FILE *file = fopen(filename, "a");
    openFileError(file);
    fprintf(file, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%s\n", info->co2, info->so2, info->no2, info->pm25, info->temp, info->wind, info->hum, info->date);
    fclose(file);
    printf("Datos guardados correctamente\n");
}

void getDiaActual(struct Info *info, const char *filename){
    int op;
    while(1){
        printf("Ingrese la cantidad de CO2 en ppm: ");
        validNumData(&info->co2, 350, 6000);
        printf("Ingrese la cantidad de SO2 en ppb: ");
        validNumData(&info->so2, 0, 500);
        printf("Ingrese la cantidad de NO2 en ppb: ");
        validNumData(&info->no2, 0, 300);
        printf("Ingrese la cantidad de PM2.5 en ug/m3: ");
        validNumData(&info->pm25, 0, 500);
        printf("Ingrese la temperatura en grados Celsius: ");
        validNumData(&info->temp, -10, 50);
        printf("Ingrese la velocidad del viento en km/h: ");
        validNumData(&info->wind, 0, 50);
        printf("Ingrese la humedad en porcentaje: ");
        validNumData(&info->hum, 0, 100);
        printf("Ingrese la fecha en formato YYYY-MM-DD: ");
        getDate(info->date);
        printf("\nLos siguientes datos son correctos?\n"
                "CO2: %.1f ppm\n"
                "SO2: %.1f ppb\n"
                "NO2: %.1f ppb\n"
                "PM2.5: %.1f ug/m3\n"
                "Temperatura: %.1f C\n"
                "Velocidad del viento: %.1f km/h\n"
                "Humedad: %.1f %%\n"
                "Fecha: %s\n"

                "\n1. Si\n"
                "2. No (volver a ingresar)\n"
                ">> ");
        scanf("%d", &op);
        if (op==1){
            break;
        }else if (op==2){
            continue;
        }else{ 
            printf("Opcion invalida, ingrese un numero entre 1 y 2\n");
        }
    }
    updateData(filename, info);
}

void readLastLine(const char *filename, struct Info *info, char *line){
    FILE *file = fopen(filename, "r");
    openFileError(file);

    fseek(file, 0, SEEK_END); // Ir al final del archivo
    long pos = ftell(file);
    while(pos>0){
        fseek(file, --pos, SEEK_SET);
        if (fgetc(file)=='\n') break;
    }
    if (fgets(line, 100, file)!=NULL){
        if (sscanf(line, "%f,%f,%f,%f,%f,%f,%f,%s", &info->co2, &info->so2, &info->no2, &info->pm25, &info->temp, &info->wind, &info->hum, info->date)!=8){
            printf("Ocurrio un error\n");
            fclose(file);
            return;
        }
    } else{ 
        printf("Ocurrio un error en el archivo.\n");
        fclose(file);
        return;
    }
    fclose(file);
}

float calcApiSubIndex(float cp, float clow, float chigh, float ilow, float ihigh){
    return ((ihigh-ilow)/(chigh-clow))*(cp-clow)+ilow;
}

float getApiSubIndex(float val, const float breakpoints[6][4]){
    for (int i=0; i<6; i++){
        if (val>=breakpoints[i][0] && val<=breakpoints[i][1]){
            return calcApiSubIndex(val, breakpoints[i][0], breakpoints[i][1], breakpoints[i][2], breakpoints[i][3]);
        }
    }
    return 0.0;
}

float calcAPI(struct Info *info){
    float temp;
    
    float co2Index = getApiSubIndex(info->co2, co2Breakpoints);
    float so2Index = getApiSubIndex(info->so2, so2Breakpoints);
    float no2Index = getApiSubIndex(info->no2, no2Breakpoints);
    float pm25Index = getApiSubIndex(info->pm25, pm25Breakpoints);

    float api = co2Index;
    if (so2Index>api) api = so2Index;
    if (no2Index>api) api = no2Index;
    if (pm25Index>api) api = pm25Index;

    //Ajustarse  a condiciones climaticas

    if (info->temp>40 || info->temp<0){
        temp = 10;
    } else temp= 0; 
    float wind= 1 - (info->wind/50);
    if (wind<0.5) wind=0.5;
    float humidity= 1 + (info->hum/100);

    return api * temp * wind * humidity;
}

void printMA(float api){
    printf("El indice de calidad del aire es: %.2f\n", api);
    if (api>=0 && api<=50){
        printf("Calidad del aire: Buena\n");
    } else if (api>=51 && api<=100){
        printf("Calidad del aire: Moderada\n");
    } else if (api>=101 && api<=150){
        printf("Calidad del aire: Danina para grupos sensibles\n");
    } else if (api>=151 && api<=200){
        printf("Calidad del aire: Danina para la salud\n");
    } else if (api>=201 && api<=300){
        printf("Calidad del aire: Muy danina para la salud\n");
    } else if (api>=301 && api<=500){
        printf("Calidad del aire: Peligrosa\n");
    } else{
        printf("Error\n");
    }
}

int getSwitchIndex(char zona[15], const char zonas[5][15]){
    for (int i=0; i<5; i++){
        if (strcmp(zona, zonas[i])==0){
            return i;
        }
    }
}

void maSwitchCase(const char *filename, struct Info *info, char *line, float api){ //Funcion para el menu de monitorActual
    FILE *file = fopen(filename, "r");
    openFileError(file);
    readLastLine(filename, info, line);
    api=calcAPI(info);
    printMA(api);
}

void monitorActual(struct Info *info){
    char zona[15], line[100];
    int index;
    float api;
    while(1){
        printf("Ingrese la zona que desea monitorear: ");
        getString(zona, 15);
        mayus(zona);
        if (!checkZona(zona)){
            printf("Zona invalida, ingrese una de las siguientes zonas: Calderon, Cumbaya, Pifo, Tababela, Tumbaco\n");
            continue;
        }
        break;
    }
    index=getSwitchIndex(zona, zonas);
    switch(index){
        case 0:
            maSwitchCase(fileNames[index], info, line, api);
            break;
        case 1:
            maSwitchCase(fileNames[index], info, line, api);
            break;
        case 2:
            maSwitchCase(fileNames[index], info, line, api);
            break;
        case 3:
            maSwitchCase(fileNames[index], info, line, api);
            break;
        case 4:
            maSwitchCase(fileNames[index], info, line, api);
            break;
    }
}

int readFilesData(const char *filename, float co2Data[], float so2Data[], float no2Data[], float pm25Data[], float tempData[], float windData[], float humData[]){

    char buffer[256];
    int lineNum, n;

    FILE *file = fopen(filename, "r");
    openFileError(file);
    
    while(fgets(buffer, 256, file)!=NULL){
        lineNum++;

        if (lineNum>=3){
            char line[100];
            while (fgets(line, 100, file)!=NULL){
                if (sscanf(line, "%f,%f,%f,%f,%f,%f,%f", &co2Data[n], &so2Data[n], &no2Data[n], &pm25Data[n], &tempData[n], &windData[n], &humData[n])==7) (n)++;
            }
        }

    }
    
    fclose(file);
    return n;
}

float calcPromPond(float data[], int n){
    float Sum;
    int totalWeight;

    for(int i=0; i<n; i++){
        int weight = n+i;
        Sum += data[i]*weight;
        totalWeight += weight;
    }

    return Sum/totalWeight;
}

float predictZone(const char *filename, float co2Data[], float so2Data[], float no2Data[], float pm25Data[], float tempData[], float windData[], float humData[],int *n){
    
    int n = readFilesData(filename, co2Data, so2Data, no2Data, pm25Data, tempData, windData, humData);
    float co2Prom = calcPromPond(co2Data, n);
    float so2Prom = calcPromPond(so2Data, n);
    float no2Prom = calcPromPond(no2Data, n);
    float pm25Prom = calcPromPond(pm25Data, n);
    float tempProm = calcPromPond(tempData, n);
    float windProm = calcPromPond(windData, n);
    float humProm = calcPromPond(humData, n);

    struct nonDated proms = {co2Prom, so2Prom, no2Prom, pm25Prom, tempProm, windProm, humProm};
    float api = calcAPI(&proms);
    return api;
}

void predictionAlerts(){

    float co2Data[100], so2Data[100], no2Data[100], pm25Data[100], tempData[100], windData[100], humData[100];
    int n;
    float api;

    for (int i=0; i<5; i++){
        api=predictZone(fileNames[i], co2Data, so2Data, no2Data, pm25Data, tempData, windData, humData, &n);
        if (api>200){
            printf("ALERTA DE PELIGRO, LOS INDICES PARA MANANA EN LA ZONA %s SUPERARAN EL LIMITE DE 200 API\n"
                    "LA CALIDAD DEL AIRE SERA PELIGROSA PARA LA SALUD\n"
                    "Para mayor informacion ingrese 3 en el programa.\n", zonas[i]);
        }
    }
}

void printPredict(int api, char zona[15], int index){
    printf("El indice de calidad del aire para manana en la zona %s es: %d\n", zona, api);
    if (api>=0 && api<=50){
        printf("Calidad del aire: Buena\n");
    } else if (api>=51 && api<=100){
        printf("Calidad del aire: Moderada\n");
    } else if (api>=101 && api<=150){
        printf("Calidad del aire: Danina para grupos sensibles\n");
    } else if (api>=151 && api<=200){
        printf ("ALERTA DE PELIGRO:\n"
                "Calidad del aire: Danina para la salud\n");
        switch(index){
            case 0:
                printf("Para la zona %s se recomienda: \n"
                    "Suspender las actividades de mercados en el exterior y festivales.\n"
                    "Prohibir el uso de madera o basura como combustible.\n", zonas[index]);
                break;
            case 1:
                printf("Para la zona %s se recomienda: \n"
                    "Transicion de las instituciones educativas a la educacion virtual.\n"
                    "Inicitar a los negocios de comida a funcionar solamente a domicilio para limitar la exposicion.\n", zonas[index]);
                break;
            case 2:
                printf("Para la zona %s se recomienda: \n"
                    "Suspender las actividades industriales que emiten contaminantes temporalmente.\n"
                    "Inicitar a los negocios a minimizar la contaminacion dentro de lugares cerrados usando ventilacion adecuada.\n", zonas[index]);
                break;
            case 3:
                printf("Para la zona %s se recomienda: \n"
                    "Restringir los viajes no esenciales hacia el aeropuerto Mariscal Sucre.\n"
                    "Incrementar los servicios de transporte electricos para reducir las emisiones de automoviles alrededor del aeropuerto.\n"
                    "Proveer a viajeros con mascarillas.\n", zonas[index]);
                break;
            case 4:
                printf("Para la zona %s se recomienda: \n"
                    "Cierre de calles no esenciales y restringir el uso de vehiculos a solo vehiculos electricos y de emergencia.\n"
                    "Ademas, se deberian distribuir mascarilas en centros comunitarios y estaciones de transporte publico.\n", zonas[index]);
                break;
        }

    }   
}

void predictTomorrow(){

    float co2Data[100], so2Data[100], no2Data[100], pm25Data[100], tempData[100], windData[100], humData[100];
    char zona[15];
    float co2Prom, so2Prom, no2Prom, pm25Prom, tempProm, windProm, humProm;
    float api;
    int n;

    while(1){
        printf("Ingrese el nombre de la zona que desea predecir a detalle: ");
        getString(zona, 15);
        mayus(zona);
        if (!checkZona(zona)){
            printf("Zona invalida, ingrese una de las siguientes zonas: Calderon, Cumbaya, Pifo, Tababela, Tumbaco\n");
            continue;
        }
        break;
    }

    int index = getSwitchIndex(zona, zonas);
    predictZone(fileNames[index], co2Data, so2Data, no2Data, pm25Data, tempData, windData, humData, &n);
    printPredict(api, zona, index);
}


int mainValid(bool f1){
    int op;
    if (!f1){
        printf("No se han ingresado datos del dia actual\n");
        while(1){        
            printf ("Deseas monitorear los ultimos datos guardados?\n"
                    "1. Si\n"
                    "2. No\n"
                    ">> ");
            scanf("%d", &op);
            if (op==1){
                return op;     
            }else if (op==2){
                printf("Regresando al menu principal\n");
                return op==2;
            }else{
                printf("Opcion invalida, ingrese un numero entre 1 y 2\n");
                continue;
            }
        }
    }
}