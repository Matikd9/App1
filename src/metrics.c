#include <stdio.h>
#include "utils.h"
#include "metrics.h"
#include <stdlib.h>
#include <string.h>
#include "orders.h"

// Calcula el promedio de pizzas por día
char *apd(int size, order *orders) {
    int contador = 0;
    int total_pizzas = 0;
    static char resultado[100];  // Usar un buffer estático para almacenar el resultado

    for (int i = 0; i < size; i++) {
        total_pizzas += (int)orders[i].quantity;  // Convierte quantity a entero si es necesario

        // Si el día cambia, contar una nueva entrada
        if (i == 0 || strcmp(orders[i+1].order_date, orders[i].order_date) != 0) {
            contador++;
        }
    }

    if (contador > 0) {
        double promedio = (double) total_pizzas / contador;
        sprintf(resultado, "resultado es %.9f, total pizzas: %d, contador: %i", promedio, total_pizzas, contador);
    } else {
        strcpy(resultado, "No hay datos suficientes.");
    }
    return resultado;
}


// Calcula promedio de pizzas por orden
char *apo(int size, order *orders) {
    int contador = 0;
    int total_pizzas = 0;
    static char resultado[100];  // Usar un buffer estático para almacenar el resultado

    for (int i = 0; i < size; i++) {
        total_pizzas += (int)orders[i].quantity;  // Convierte quantity a entero si es necesario

        // Si el día cambia, contar una nueva entrada
        if (i == 0 ||orders[i+1].order_id !=  orders[i].order_id) {
            contador++;
        }
    }

    if (contador > 0) {
        double promedio = (double) total_pizzas / contador;
        sprintf(resultado, "El promedio de pizzas por orden es: %.9f", promedio);
    } else {
        strcpy(resultado, "No hay datos suficientes.");
    }
    return resultado;
}
