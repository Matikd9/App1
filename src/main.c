#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.c"
#include "orders.c"
#include "metrics.c"

int main(int argc,char *argv[]){
    int i;
    if (strcmp(argv[1], "ventas.csv") == 0){  
        char csv[] = "data/ventas.csv"; // Variable con nombre del .csv
        char datos[200][200][200]; // Array en el que se van a almacenar 
        int filas, columnas;
        leercsv(csv, datos, &filas, &columnas); // Se llama a la función para que guarde los datos en el array "datos" y los separe en filas y columnas
        for(i=1; i<argc ;i++){ // Ciclo for para recorrer cada argumento y hacer una comparación

            if (strcmp(argv[i], "pms") == 0){
                printf("Pizza más vendida:  \n");
            }
            else if(strcmp(argv[i],"pls") == 0){
                printf("Pizza menos vendida:  \n");
            }
            else if(strcmp(argv[i],"dms") == 0){
                printf("Fecha con más ventas en términos de dinero:  \n");
            } 
            else if(strcmp(argv[i],"dls") == 0){
                printf("Fecha con menos ventas en términos de dinero: \n");
            }
            else if(strcmp(argv[i],"dmsp") == 0){
                printf("Fecha con más ventas en términos de cantidad de pizzas: \n");
            }
            else if(strcmp(argv[i],"dlsp") == 0){
                printf("Fecha con menos ventas en términos de cantidad de pizzas: \n");
            }
            else if(strcmp(argv[i],"apo") == 0){
                printf("Promedio de pizzas por orden: %f\n", apo(csv));
            }   
            else if(strcmp(argv[i],"apd") == 0){
                printf("Promedio de pizzas por día: %f\n", apd(csv));
            }
            else if(strcmp(argv[i],"ims") == 0){
                printf("Ingrediente más vendido: \n");   
            }
            else if(strcmp(argv[i],"hp") == 0){
                printf("Cantidad de pizzas por categoría vendidas: \n");
            }
    }   }
        
}
