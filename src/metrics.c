#include <stdio.h>
#include "utils.h"
#include "metrics.h"
#include <stdlib.h>
#include <string.h>

char datos[200][200][200];
int filas,columnas;

// Calcula promedio de pizzas por día
double apd(const char *archivo){

    leercsv(archivo,datos,&filas,&columnas);
    int contador = 0;
    int total_pizzas = 0;
    
    for(int i = 1;i<filas;i++){
        total_pizzas += atoi(datos[i][3]);
        if(i == 0 || strcmp(datos[i][4], datos[i - 1][4]) != 0){
            contador++;
        }
    }
    if (contador > 0) {
        double promedio = (double) total_pizzas / contador;
        return promedio;
    } else {
        printf("No hay datos suficientes para calcular el promedio.\n");
    }
}


// Calcula promedio de pizzas por orden
double apo(const char *archivo){
    leercsv(archivo,datos,&filas,&columnas);
    
    int cantidad_ordenes = 0;
    int total_pizzas = 0;
    
    for(int i = 1;i<filas;i++){
        total_pizzas += atoi(datos[i][3]);
        if(i == 0 || strcmp(datos[i][2], datos[i - 1][2]) != 0){
            cantidad_ordenes++;
        }
    }
    if (cantidad_ordenes > 0) {
        double promedio = (double) total_pizzas / cantidad_ordenes;
        return promedio;
    } else {
        printf("No hay datos suficientes para calcular el promedio.\n");
    }
}
