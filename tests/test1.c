#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orders.h"
#include "metrics.h"

int main() {
    order *orders = NULL;
    int size = 10;  

    structcsv("data/ventas.csv", &orders, &size);  

    char *resultado = apd(size, orders);  
    printf("%s\n", resultado);

    char *resultadoo = apo(size, orders);
    printf("%s\n", resultadoo);

    char *resultado2 = dmsp(size,orders);
    printf("%s\n", resultado2);

    char *resultado3 = dlsp(size,orders);
    printf("%s", resultado3);

    free(orders);  
    return 0;
}