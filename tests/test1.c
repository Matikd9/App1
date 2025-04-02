#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/orders.c"
#include "../src/metrics.c"

int main() {
    order *orders = NULL;
    int size = 10;  

    structcsv("data/ventas.csv", &orders, &size);  

    char *resultado1 = apd(size, orders);  
    printf("%s\n", resultado1);

    char *resultado2 = apo(size, orders);
    printf("%s\n", resultado2);

    char *resultado3 = dmsp(size,orders);
    printf("%s\n", resultado3);

    char *resultado4 = dlsp(size,orders);
    printf("%s\n", resultado4);
    
    Ingrediente resultado5 = ims(size,orders);
    printf("Ingrediente mas vendido: %s\n\n", resultado5.nombre);

    ResultadoCategorias resultado_categorias = hp(size,orders);
    printf("Nombre Categoría: Cantidad de Pizzas\n");

    for (int i = 0; i < resultado_categorias.num_categorias; i++) {
        printf("%s: %d\n", resultado_categorias.categorias[i].nombre, resultado_categorias.categorias[i].cantidad_de_pizzas);
    }

    free(orders);  
    return 0;
}