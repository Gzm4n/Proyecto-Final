#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "funciones.h"

#define startLine 2 // Linea donde empiezan los datos en los archivos

struct readData data;

char zonas[5][15] = {"Calderon", "Cumbaya", "Pifo", "Tababela", "Tumbaco"}; //Zonas de la ciudad

const char fileNames[5][30]= {"Data/data_calderon.csv", "Data/data_cumbaya.csv", "Data/data_pifo.csv", "Data/data_tababela.csv", "Data/data_tumbaco.csv"}; //Archivos de datos de las zonas

//Puntos limites para los indices de calidad del aire, en orden de menor a mayor
//{limite inferior, limite superior, indice inferior, indice superior}

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

void getString(char string[], int length){ //Funcion para leer strings de longitud length
    fgets(string, length, stdin);
    string[strcspn(string, "\n")]='\0';   
}

void validNumData(float *data, float min, float max){ //Funcion para validar numeros flotantes, con un rango minimo y maximo
    int flag=0;
    float temp=0;
    while(!flag){
        if (scanf("%f", &temp)!=1){
            while (getchar()!='\n');
            printf("Dato invalido, ingrese un numero entre %.2f y %.2f: ", min, max);
        } else if (temp<min || temp>max){
            while(getchar()!='\n')
            printf("Dato invalido, ingrese un numero entre %.2f y %.2f: ", min, max);
        } else flag=1;
    }
    while(getchar()!='\n');
    *data=temp;
}

void mayus(char *str) { //Funcion para convertir la primera letra de un string a mayuscula (ctype.h)
    *str = toupper(*str);
}

void openFileError(FILE *file){ //Funcion para manejar errores al abrir archivos
    if (file == NULL){
        printf("Error al abrir el archivo\n");
        printf("Saliendo del programa\n");
        exit(EXIT_FAILURE); //Terminar el programa si no puede abir el archivo (stdlib.h)
    }
}

bool checkZona(char zona[15]){ //Funcion para verificar si la zona ingresada es valida (stdbool.h)
    for (int i=0; i<5; i++){
        if (strcmp(zona, zonas[i])==0){ //(string.h)
            return true;
        }
    }
    return false;
}

void getDate(char date[10]){ //Funcion para obtener la fecha en formato YYYY-MM-DD
    char try[11];
    int year, month, day;
    printf("Ingrese la fecha en formato YYYY-MM-DD (Los guiones son importantes): ");
    getString(try, 11);
    while(1){
        if (strlen(try)!=10 || try[4]!='-' || try[7]!='-'){  
            printf("\nFecha invalida, ingrese la fecha en formato YYYY-MM-DD: ");
        } else {
            if (sscanf(try, "%d-%d-%d", &year, &month, &day)!=3 || year>2025 || year<2000 || month>12 || month<1 || day>31 || day<1){ //string scanf
                printf("\nFecha invalida, ingrese la fecha en formato YYYY-MM-DD: ");
            }else break;
        }
        getString(try, 11);
    }

    strcpy(date, try);
}

void updateData(const char *filename, struct Info *info){ //Funcion para actualizar los datos en el archivo
    FILE *file = fopen(filename, "a");
    openFileError(file);
    fprintf(file, "\n%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%s", info->co2, info->so2, info->no2, info->pm25, info->temp, info->wind, info->hum, info->date);
    fclose(file);
    printf("Datos guardados correctamente\n");
}

void getDiaActual(struct Info info, const char *filename){ //Funcion para obtener los datos del dia actual
    int op=0;
    while(1){
        printf("Ingrese la cantidad de CO2 en ppm: ");
        validNumData(&info.co2, 0, 2000);
        printf("Ingrese la cantidad de SO2 en ppb: ");
        validNumData(&info.so2, 0, 2100);
        printf("Ingrese la cantidad de NO2 en ppb: ");
        validNumData(&info.no2, 0, 500);
        printf("Ingrese la cantidad de PM2.5 en ug/m3: ");
        validNumData(&info.pm25, 0, 500);
        printf("Ingrese la temperatura en grados Celsius: ");
        validNumData(&info.temp, -10, 50);
        printf("Ingrese la velocidad del viento en km/h: ");
        validNumData(&info.wind, 0, 50);
        printf("Ingrese la humedad en porcentaje: ");
        validNumData(&info.hum, 0, 100);
        getDate(info.date);
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
                ">> ", info.co2, info.so2, info.no2, info.pm25, info.temp, info.wind, info.hum, info.date);
        scanf("%d", &op);
        if (op==1){
            break;
        }else if (op==2){
            continue;
        }else{ 
            printf("Opcion invalida, ingrese un numero entre 1 y 2\n");
        }
    }
    printf("\nGuardando datos...\n");
    while(getchar()!='\n');
    updateData(filename, &info);
}

void readLastLine(const char *filename, struct Info *info){ //Funcion para leer la ultima linea de un archivo
    FILE *file = fopen(filename, "r");
    openFileError(file);

    char line[100];
    fseek(file, 0, SEEK_END); // Ir al final del archivo
    long pos = ftell(file);
    if (pos==0){
        printf("No hay datos en el archivo\n");
        fclose(file);
        return;
    }
    while(pos>0){
        fseek(file, --pos, SEEK_SET);
        if (fgetc(file)=='\n') break; // Encontrar el final de la penultima linea
    }
    if (fgets(line, 100, file)!=NULL){
        if (sscanf(line, "%f,%f,%f,%f,%f,%f,%f,%s", &info->co2, &info->so2, &info->no2, &info->pm25, &info->temp, &info->wind, &info->hum, &info->date)!=8){
            printf("Ocurrio un error analizando la ultima linea\n");
            fclose(file);
            return;
        }
    } else{ 
        printf("Ocurrio un error leyendo la ultima linea.\n");
        fclose(file);
        return;
    }
    fclose(file);
}

float calcApiSubIndex(float cp, float clow, float chigh, float ilow, float ihigh){ //Funcion para calcular los subindices de calidad del aire
    return ((ihigh-ilow)/(chigh-clow))*(cp-clow)+ilow; //(indice superior - indice inferior)/(limite superior - limite inferior))*(valor actual - limite inferior)+indice inferior(breakpoints)
}

float getApiSubIndex(float val, const float breakpoints[6][4]){ //Funcion para obtener los subindices de calidad del aire
    for (int i=0; i<6; i++){
        if (val>=breakpoints[i][0] && val<=breakpoints[i][1]){ //Si el valor esta entre los limites de los breakpoints
            return calcApiSubIndex(val, breakpoints[i][0], breakpoints[i][1], breakpoints[i][2], breakpoints[i][3]);
        }
    }
    return 0.0;
}

float calcAPI(struct Info *info){ //Funcion para calcular el indice de calidad del aire
    float temp=0.0;
    printf("\nCalculando subindices...\n");
    float co2Index = getApiSubIndex(info->co2, co2Breakpoints);
    float so2Index = getApiSubIndex(info->so2, so2Breakpoints);
    float no2Index = getApiSubIndex(info->no2, no2Breakpoints);
    float pm25Index = getApiSubIndex(info->pm25, pm25Breakpoints);

    float api = co2Index;
    if (so2Index>api) api = so2Index;
    if (no2Index>api) api = no2Index;
    if (pm25Index>api) api = pm25Index; //Obtener el indice mas alto de los subindices

    //Ajustarse  a condiciones climaticas
    printf("\nAjustandose a las condiciones climaticas...\n");
    if (info->temp>40 || info->temp<0){
        temp = 1.2; //Si la temperatura es mayor a 40 o menor a 0, el indice de calidad del aire se incrementa en 20%
    } else temp= 1; 
    float wind= 1 - (info->wind/50);
    if (wind<0.5) wind=0.5; //Si la velocidad del viento es mayor a 50, el indice de calidad del aire se reduce en 50%
    float humidity= 0.5 + (info->hum/100); //Si la humedad es mayor a 50, el indice de calidad del aire se incrementa en 50%

    return api * temp * wind * humidity;
}

void printAPIEval(float api){ //Funcion para imprimir la evaluacion del indice de calidad del aire
    printf("\nEl indice de calidad del aire es: %.2f\n", api);
    if (api>=0 && api<=50){
        printf("\nCalidad del aire: Buena\n");
    } else if (api>=51 && api<=100){
        printf("\nCalidad del aire: Moderada\n");
    } else if (api>=101 && api<=150){
        printf("\nCalidad del aire: Danina para grupos sensibles\n");
    } else if (api>=151 && api<=200){
        printf("\nCalidad del aire: Danina para la salud\n");
    } else if (api>=201 && api<=300){
        printf("\nCalidad del aire: Muy danina para la salud\n");
    } else if (api>=301 && api<=500){
        printf("\nCalidad del aire: Peligrosa\n");
    } else{
        printf("\nError en los valores del API\n");
    }
}

int getIndex(char zona[15], char zonas[5][15]){ //Funcion para obtener el indice de la zona
    for (int i=0; i<5; i++){
        if (strcmp(zona, zonas[i])==0){
            return i;
        }
    }
    return -1;
}

int validZone(char zona[]){ //Funcion para validar la zona ingresada
    int index;
    while(1){
        printf("\nIngrese el nombre de la zona: ");
        getString(zona, 15);
        mayus(zona);
        if (checkZona(zona)){
            break;
        } else {
            printf("\nZona invalida, ingrese una de las siguientes zonas: ");
            for(int i=0; i<5; i++){
                printf("%s, ", zonas[i]);
            }
            printf("\n");
        }
    }
    index=getIndex(zona, zonas);
    if (index==-1){
        printf("\nError obteniendo el indice de la zona\n");
        return -1;
    }
    return index;
}

void getZoneAPI(const char *filename, struct Info *info, float api){ //Funcion para obtener el indice de calidad del aire de una zona en monitorActual
    FILE *file = fopen(filename, "r");
    openFileError(file);
    readLastLine(filename, info);
    api=calcAPI(info);
    if (api<=0){
        printf("\nError calculando el indice de calidad del aire\n");
        return;
    }
    printf("\nSegun los datos de hoy...\n");
    printAPIEval(api);
}

void monitorActual(struct Info *info){ //Funcion para monitorear la calidad del aire actual
    char zona[15];
    int index=0;
    float api=0.0;
    index=validZone(zona);
    getZoneAPI(fileNames[index], info, api);
}

int readFilesData(const char *filename, struct readData *data){ //Funcion para leer todos los datos de los archivos

    char buffer[256];
    int lineNum=0, n=0;

    FILE *file = fopen(filename, "r");
    
    openFileError(file);
    
    while(fgets(buffer, 256, file)!=NULL){ //Leer linea por linea para encontrar el numero de lineas
        lineNum++;
        if (lineNum>=startLine){ //Empezar a leer los datos despues de la linea 2 (cabeceros)
            char line[256];
            while (fgets(line, 256, file)!=NULL){
                if (sscanf(line, "%f,%f,%f,%f,%f,%f,%f", &data->co2Data[n], &data->so2Data[n], &data->no2Data[n], &data->pm25Data[n], &data->tempData[n], &data->windData[n], &data->humData[n])==7) (n)++; //Contador de lineas leidas (numero de datos)
                else{
                    printf("Error leyendo todos los datos del archivo\n");
                    break;
                }
            }
            break;
        }
    }
    fclose(file);
    return n;
}

float calcPromPond(float data[], int n){ //Funcion para calcular el promedio ponderado de los datos
    float Sum=0.0;
    int totalWeight=0;
    int weight=0;

    for(int i=0; i<n; i++){
        weight = i+1; //Peso de los datos que aumenta segun su cercania a la actualidad
        Sum += data[i]*weight;
        totalWeight += weight;
    }

    return Sum/totalWeight;
}

float predictZone(const char *filename, struct readData *data){ //Funcion para predecir el indice de calidad del aire de manana

    int n = readFilesData(filename, data);
    float co2Prom = calcPromPond(data->co2Data, n);
    float so2Prom = calcPromPond(data->so2Data, n);
    float no2Prom = calcPromPond(data->no2Data, n);
    float pm25Prom = calcPromPond(data->pm25Data, n);
    float tempProm = calcPromPond(data->tempData, n);
    float windProm = calcPromPond(data->windData, n);
    float humProm = calcPromPond(data->humData, n);

    struct Info proms = {co2Prom, so2Prom, no2Prom, pm25Prom, tempProm, windProm, humProm, "none"}; //Estructura con los promedios de los datos, none es la fecha que no se usa en calculos
    float api = calcAPI(&proms);
    return api;
}

void predictionAlerts(){ //Funcion para alertar si el indice de calidad del aire supera el limite de 200
    float api=0.0;
    for (int i=0; i<5; i++){
        api=predictZone(fileNames[i], &data);
        if (api>200){
            printf("\nALERTA DE PELIGRO, LOS INDICES PARA MANANA EN LA ZONA %s SUPERARAN EL LIMITE DE 200 API\n"
                    "LA CALIDAD DEL AIRE SERA PELIGROSA PARA LA SALUD\n", zonas[i]);
        }
    }
    printf("\nPara mas informacion, ingrese 3 en el progrrama\n");
}

void printPredict(int api, char zona[15], int index){ //Funcion para imprimir la prediccion del indice de calidad del aire de manana junto con sus recomendaciones divididas por zona
    printf("\nEl indice de calidad del aire para manana en la zona %s es: %d\n", zona, api);
    if (api>=0 && api<=50){
        printf("\nCalidad del aire: Buena\n");
    } else if (api>=51 && api<=100){
        printf("\nCalidad del aire: Moderada\n");
    } else if (api>=101 && api<=150){
        printf("\nCalidad del aire: Danina para grupos sensibles\n"
                "\nSe recomienda mantener a las personas vulnerables dentro de lugares cerrados y bien ventilados. O el uso de mascarrillas.\n");
    } else if (api>=151 && api<=200){
        printf ("\nALERTA DE PELIGRO:\n"
                "\nCalidad del aire: Danina para la salud\n");
        switch(index){
            case 0:
                printf("\nPara la zona %s se recomienda: \n"
                    "\nSuspender las actividades de mercados en el exterior y festivales.\n"
                    "\nProhibir el uso de madera o basura como combustible.\n", zonas[index]);
                break;
            case 1:
                printf("\nPara la zona %s se recomienda: \n"
                    "\nTransicion de las instituciones educativas a la educacion virtual.\n"
                    "\nInicitar a los negocios de comida a funcionar solamente a domicilio para limitar la exposicion.\n", zonas[index]);
                break;
            case 2:
                printf("\nPara la zona %s se recomienda: \n"
                    "\nSuspender las actividades industriales que emiten contaminantes temporalmente.\n"
                    "\nInicitar a los negocios a minimizar la contaminacion dentro de lugares cerrados usando ventilacion adecuada.\n", zonas[index]);
                break;
            case 3:
                printf("\nPara la zona %s se recomienda: \n"
                    "\nRestringir los viajes no esenciales hacia el aeropuerto Mariscal Sucre.\n"
                    "\nIncrementar los servicios de transporte electricos para reducir las emisiones de automoviles alrededor del aeropuerto.\n"
                    "\nProveer a viajeros con mascarillas.\n", zonas[index]);
                break;
            case 4:
                printf("\nPara la zona %s se recomienda: \n"
                    "\nCierre de calles no esenciales y restringir el uso de vehiculos a solo vehiculos electricos y de emergencia.\n"
                    "\nAdemas, se deberian distribuir mascarilas en centros comunitarios y estaciones de transporte publico.\n", zonas[index]);
                break;
        }

    }   
}

void predictTomorrow(){ //Funcion para predecir el indice de calidad del aire de manana por zona y mostrar sus recomendaciones
    char zona[15];
    float api;
    int index = validZone(zona);
    api = predictZone(fileNames[index], &data);
    printPredict(api, zona, index);
}

float calcReverseProm(float data[], int n, int days){ //Funcion para calcular el promedio de los ultimos n dias (30 a peticion de la consigna)
    float sum=0;
    int final=n-1-days;
    
    for (int i=n-1; i>final; i--){
        sum+=data[i];
    }
    return sum/days;
}

float historicalAverage(const char *filename, struct readData *data){ //Funcion para calcular el promedio historico de los ultimos 30 dias
    int n = readFilesData(filename, data);
    float co2Prom = calcReverseProm(data->co2Data, n, 30);
    float so2Prom = calcReverseProm(data->so2Data, n, 30);
    float no2Prom = calcReverseProm(data->no2Data, n, 30);
    float pm25Prom = calcReverseProm(data->pm25Data, n, 30);
    float tempProm = calcReverseProm(data->tempData, n, 30);
    float windProm = calcReverseProm(data->windData, n, 30);
    float humProm = calcReverseProm(data->humData, n, 30);
    struct Info proms = {co2Prom, so2Prom, no2Prom, pm25Prom, tempProm, windProm, humProm, "none"};
    float api = calcAPI(&proms);
    return api;
}

void historicalAvrgBySearch(){ //Funcion para calcular el promedio historico de los ultimos 30 dias por zona
    char zona[15];
    int index = validZone(zona);
    float api = historicalAverage(fileNames[index], &data);
    printf("\nSegun los datos de los ultimos 30 dias...\n");
    printAPIEval(api);
}

void printAPIEF(FILE *file, float api){ //Funcion para imprimir la evaluacion del indice de calidad del aire en el archivo
    fprintf(file, "\nEl indice de calidad del aire es: %.2f\n", api);
    if (api>=0 && api<=50){
        fprintf(file, "\nCalidad del aire: Buena\n");
    } else if (api>=51 && api<=100){
        fprintf(file, "\nCalidad del aire: Moderada\n");
    } else if (api>=101 && api<=150){
        fprintf(file, "\nCalidad del aire: Danina para grupos sensibles\n");
    } else if (api>=151 && api<=200){
        fprintf(file, "\nCalidad del aire: Danina para la salud\n");
    } else if (api>=201 && api<=300){
        fprintf(file, "\nCalidad del aire: Muy danina para la salud\n");
    } else if (api>=301 && api<=500){
        fprintf(file, "\nCalidad del aire: Peligrosa\n");
    } else{
       fprintf(file, "\nError en los valores del API\n");
    }
}

void printPredictF(int api, char zona[15], int index, FILE *file){ //Funcion para imprimir la prediccion del indice de calidad del aire de manana junto con sus recomendaciones divididas por zona en el archivo
    fprintf(file, "\nEl indice de calidad del aire para manana en la zona %s es: %d\n", zona, api);
    if (api>=0 && api<=50){
        fprintf(file, "\nCalidad del aire: Buena\n");
    } else if (api>=51 && api<=100){
        fprintf(file, "\nCalidad del aire: Moderada\n");
    } else if (api>=101 && api<=150){
        fprintf(file, "\nCalidad del aire: Danina para grupos sensibles\n"
                "Se recomienda mantener a las personas vulnerables dentro de lugares cerrados y bien ventilados. O el uso de mascarrillas.\n");
    } else if (api>=151 && api<=200){
        fprintf (file, "\nALERTA DE PELIGRO:\n"
                "\nCalidad del aire: Danina para la salud\n");
        switch(index){
            case 0:
                fprintf(file, "\nPara la zona %s se recomienda: \n"
                    "Suspender las actividades de mercados en el exterior y festivales.\n"
                    "Prohibir el uso de madera o basura como combustible.\n", zonas[index]);
                break;
            case 1:
                fprintf(file, "\nPara la zona %s se recomienda: \n"
                    "Transicion de las instituciones educativas a la educacion virtual.\n"
                    "Inicitar a los negocios de comida a funcionar solamente a domicilio para limitar la exposicion.\n", zonas[index]);
                break;
            case 2:
                fprintf(file, "\nPara la zona %s se recomienda: \n"
                    "Suspender las actividades industriales que emiten contaminantes temporalmente.\n"
                    "Inicitar a los negocios a minimizar la contaminacion dentro de lugares cerrados usando ventilacion adecuada.\n", zonas[index]);
                break;
            case 3:
                fprintf(file, "\nPara la zona %s se recomienda: \n"
                    "Restringir los viajes no esenciales hacia el aeropuerto Mariscal Sucre.\n"
                    "Incrementar los servicios de transporte electricos para reducir las emisiones de automoviles alrededor del aeropuerto.\n"
                    "Proveer a viajeros con mascarillas.\n", zonas[index]);
                break;
            case 4:
                fprintf(file, "\nPara la zona %s se recomienda: \n"
                    "Cierre de calles no esenciales y restringir el uso de vehiculos a solo vehiculos electricos y de emergencia.\n"
                    "Ademas, se deberian distribuir mascarilas en centros comunitarios y estaciones de transporte publico.\n", zonas[index]);
                break;
        }

    }   
}

void writeReport(bool f1, bool f2, bool f3, bool f4, struct Info *info){ //Funcion para escribir el reporte
    FILE *file = fopen("Data/reportes.txt", "a");
    openFileError(file);

    time_t t = time(NULL); //Obtener la fecha y hora actual (time.h)
    char *timestamp = ctime(&t);
    timestamp[strlen(timestamp)-1]='\0'; //Remover el salto de linea al final de la fecha

    fprintf(file, "Reporte generado el %s\n", timestamp);
    if (f1){
        fprintf(file, "\nSe han ingresado datos del dia actual\n");
        for (int i=0; i<5; i++){
            readLastLine(fileNames[i], info);
            float api = calcAPI(info);
            fprintf(file, "La informacion ingresada para la zona %s es: \n"
                    "CO2: %.1f ppm\n"
                    "SO2: %.1f ppb\n"
                    "NO2: %.1f ppb\n"
                    "PM2.5: %.1f ug/m3\n"
                    "Temperatura: %.1f C\n"
                    "Velocidad del viento: %.1f km/h\n"
                    "Humedad: %.1f %%\n"
                    "Fecha: %s\n", zonas[i], info->co2, info->so2, info->no2, info->pm25, info->temp, info->wind, info->hum, info->date);
            fprintf(file, "El indice de calidad del aire para la zona %s es: %.2f\n", zonas[i], api);
            printAPIEF(file, api);
            fprintf(file, "************************************\n");
        }

    } 
    if (!f1) {
        fprintf(file, "\nNo se han ingresado datos del dia actual\n");
    }
    if (f1 && f2){
        fprintf(file, "\nSe ha monitoreado la calidad del aire actual (apartado anterior).\n");
    } else if (!f1 && f2){
        fprintf(file, "\nSe ha monitoreado la calidad del aire segun los ultimos datos anadidos\n");
        for (int i=0; i<5; i++){
            readLastLine(fileNames[i], info);
            float api = calcAPI(info);
            fprintf(file, "\nEl indice de calidad del aire para la zona %s es: %.2f\n", zonas[i], api);
            printAPIEF(file, api);
            fprintf(file, "************************************\n");
        }
    }
    if (!f2){
        fprintf(file, "\nNo se ha monitoreado la calidad del aire actual\n");
    }
    if(f3 && !f1){
        fprintf(file,"\nSe predijo la calidad del aire con los datos existentes (sin valor actual)\n");
        for (int i=0; i<5; i++){
            predictZone(fileNames[i], &data);
            float api = predictZone(fileNames[i], &data);
            printPredictF(api, zonas[i], i, file);
            fprintf(file, "************************************\n");
        }
    }else if(f3 && f1){
        fprintf(file, "\nSe ha predicho la calidad del aire para manana con valores actuales\n");
        for (int i=0; i<5; i++){
            predictZone(fileNames[i], &data);
            float api = predictZone(fileNames[i], &data);
            printPredictF(api, zonas[i], i, file);
            fprintf(file, "************************************\n");
        }
    } else{
        fprintf(file, "\nNo se ha predicho la calidad del aire para manana\n");
    }
    if (f4){
        fprintf(file, "\nSe ha calculado el promedio historico de los ultimos 30 dias\n");
        for (int i=0; i<5; i++){
            float api=historicalAverage(fileNames[i], &data);
            fprintf(file, "\nPara la zona %s:\n", zonas[i]);
            printAPIEF(file, api);
            fprintf(file, "************************************\n");
        }
    } else{
        fprintf(file, "\nNo se ha calculado el promedio historico de los ultimos 30 dias\n");
    }
    fprintf(file, "\nFin del reporte\n"
                    "--------------------------------------------------------------------------------\n");
    fclose(file);

}

int mainValid(bool f1){ //Funcion para validar si se han ingresado datos del dia actual
    int op;
    if (!f1){
        printf("No se han ingresado datos del dia actual\n");
        while(1){        
            printf ("Deseas trabajar con los ultimos datos guardados?\n"
                    "1. Si\n"
                    "2. No\n"
                    ">> ");
            scanf("%d", &op);
            while(getchar()!='\n');
            if (op==1){
                return op;     
            }else if (op==2){
                printf("Regresando al menu principal\n");
                return op;
            }else{
                printf("Opcion invalida, ingrese un numero entre 1 y 2\n");
                continue;
            }
        }
    }
}