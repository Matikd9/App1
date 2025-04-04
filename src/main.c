#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "orders.h"
#include "metrics.h"

int main(int argc,char *argv[]){
    int i;
    if (argc < 2){
        printf("Seleccione un csv e introduzca métricas.");
    }
    if (strcmp(argv[1], "ventas.csv") == 0){  
        char csv[] = "data/ventas.csv"; // Variable con nombre del .csv
        order *orders = NULL;
        int size = 10;
        structcsv(csv, &orders, &size);
        char *resultado0 = pms(&size, orders);
        char *resultadoo0 = pls(&size,orders);
        char *resultadoo1 =dms(&size,orders);
        char *resultadoo2 =dls(&size,orders);
        char *resultado3 = dmsp(&size,orders);
        char *resultado4 = dlsp(&size,orders);
        char *resultado2 = apo(&size, orders);
        char *resultado1 = apd(&size, orders);  
        char *resultado6 =ims(&size,orders);
        char *resultado5 = hp(&size,orders);

        for(i=1; i<argc ;i++){ // Ciclo for para recorrer cada argumento y hacer una comparación

            if (strcmp(argv[i], "pms") == 0){
                printf("%s", resultado0);
            }
            else if(strcmp(argv[i],"pls") == 0){
                printf("%s",resultadoo0);
            }
            else if(strcmp(argv[i],"dms") == 0){
                printf("%s", resultadoo1);
            } 
            else if(strcmp(argv[i],"dls") == 0){
                printf("%s", resultadoo2);
            }
            else if(strcmp(argv[i],"dmsp") == 0){
                printf("%s\n", resultado3);
            }
            else if(strcmp(argv[i],"dlsp") == 0){
                printf("%s\n", resultado4);
            }
            else if(strcmp(argv[i],"apo") == 0){
                printf("%s\n", resultado2);
            }   
            else if(strcmp(argv[i],"apd") == 0){
                printf("%s\n", resultado1);
            }
            else if(strcmp(argv[i],"ims") == 0){
                printf("%s", resultado6);
            }
            else if(strcmp(argv[i],"hp") == 0){
                printf("%s",resultado5);
            }
    }   }
        
}
