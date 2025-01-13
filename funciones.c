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
    printf("Ingrese la fecha en formato YYYY/MM/DD: ");
    getString(date);
    if (strlen(date)!=10){
        printf("Fecha invalida, ingrese la fecha en formato YYYY/MM/DD: ");
        getString(date);
    } else if (date[4]!='/'){
        printf("Fecha invalida, ingrese la fecha en formato YYYY/MM/DD: ");
        getString(date);
    } else if (date[7]!='/'){
        printf("Fecha invalida, ingrese la fecha en formato YYYY/MM/DD: ");
        getString(date);
    } else if (atoi(date)>2025){
        printf("Fecha invalida, ingrese la fecha en formato YYYY/MM/DD: ");
        getString(date);
    } else if (atoi(date+5)>12){
        printf("Fecha invalida, ingrese la fecha en formato YYYY/MM/DD: ");
        getString(date);
    } else if (atoi(date+8)>31){
        printf("Fecha invalida, ingrese la fecha en formato YYYY/MM/DD: ");
        getString(date);
    }
    return date;
}

void getDiaActual(struct info info){
    printf("Ingrese el nombre de la zona: ");
    getString(info.zona);
    while (!checkZona(info.zona)){
        printf("Zona no encontrada, ingrese una de las siguientes zonas\n");
        for (int i=0; i<5; i++){
            printf("%s\n", zonas[i]);
        }
        printf("\nIngrese: ");
        getString(info.zona);
    }
    
    mayus(info.zona);

    printf("Ingrese la temperatura: ");
    scanf("%f", &info.temp);
    printf("Ingrese la velocidad del viento: ");
    scanf("%f", &info.wind);
    printf("Ingrese la humedad: ");
    scanf("%f", &info.hum);
    printf("Ingrese la concentracion de PM2.5: ");
    scanf("%f", &info.pm25);
    printf("Ingrese la concentracion de NO2: ");
    scanf("%f", &info.no2);
    printf("Ingrese la concentracion de SO2: ");
    scanf("%f", &info.so2);
    printf("Ingrese la concentracion de CO2: ");
    scanf("%f", &info.co2);
    getDate(info.date);
}
