#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "funciones.h"
 
void getString(char string[15]){
    int c;
    while (getchar()!='\n');
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")]='\0';

}

void validNumData(float *data, int min, int max){
    scanf("%f", &data);
    while (data<min || data>max || data!=1){
        if (data!=1){
            while (getchar()!='\n');
        }
        printf("Dato invalido, ingrese un numero entre %d y %d: ", min, max);
        scanf("%f", &data);
    }
}

void mayus(char string[15]){
    if (string[0] != '\0' && islower(string[0])) {
        string[0] = toupper(string[0]);
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

char getDate(char date[10]){
    printf("Ingrese la fecha en formato YYYY-MM-DD (Los guiones son importantes): ");
    getString(date);
    if (strlen(date)!=10 || date[4]!='-' || date[7]!='-' || atoi(date)>2025 || atoi(date+5)>12 || atoi(date+8)>31){  
        printf("Fecha invalida, ingrese la fecha en formato YYYY-MM-DD: ");
        getString(date);
    return date;
    }
}

void updateData(const char *filename, struct Info *info){
    FILE *file = fopen(filename, "a");
    if (file == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }
    fprintf(file, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%s\n", info->co2, info->so2, info->no2, info->pm25, info->temp, info->wind, info->hum, info->date);
    fclose(file);
    printf("Datos guardados correctamente\n");
}

void getDiaActual(struct Info *info, const char *filename){
    int op;
    while(1){
        printf("Ingrese la cantidad de CO2 en ppm: ");
        validNumData(&info->co2, 350, 450);
        printf("Ingrese la cantidad de SO2 en ppb: ");
        validNumData(&info->so2, 0, 20);
        printf("Ingrese la cantidad de NO2 en ppb: ");
        validNumData(&info->no2, 5, 60);
        printf("Ingrese la cantidad de PM2.5 en ug/m3: ");
        validNumData(&info->pm25, 5, 100);
        printf("Ingrese la temperatura en grados Celsius: ");
        validNumData(&info->temp, -10, 45);
        printf("Ingrese la velocidad del viento en km/h: ");
        validNumData(&info->wind, 0, 50);
        printf("Ingrese la humedad en porcentaje: ");
        validNumData(&info->hum, 20, 90);
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
    updateData(*filename, info);
}



