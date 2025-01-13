#include <stdio.h>
#include <math.h>
#include <string.h>
#include "funciones.h"

void getString(string, length){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(string, length, stdin);
    string[strcspn(string, "\n")] = '\0';

}

void getDiaActual(struct info info){
    printf("Ingrese la zona cuya informacion desea ingresar: ");
    fgets(info.zona, 15, stdin);
}
