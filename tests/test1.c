#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orders.h"
#include "metrics.h"

int main() {
    order *orders = NULL;
    int size = 10;  

    structcsv("data/ventas.csv", &orders, &size);  

    char *resultado0 = pms(&size, orders);
    printf("%s", resultado0);

    char *resultadoo0 = pls(&size,orders);
    printf("%s",resultadoo0);

    char *resultadoo1 =dms(&size,orders);
    printf("%s", resultadoo1);

    char *resultadoo2 =dls(&size,orders);
    printf("%s", resultadoo2);

    char *resultado3 = dmsp(&size,orders);
    printf("%s\n", resultado3);

    char *resultado4 = dlsp(&size,orders);
    printf("%s\n", resultado4);

    char *resultado2 = apo(&size, orders);
    printf("%s\n", resultado2);

    char *resultado1 = apd(&size, orders);  
    printf("%s\n", resultado1);

    char *resultado6 =ims(&size,orders);
    printf("%s", resultado6);
    
    char *resultado5 = hp(&size,orders);
    printf("%s",resultado5);


    free(orders);  
    return 0;
}