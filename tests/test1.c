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

    free(orders);  
    return 0;
}