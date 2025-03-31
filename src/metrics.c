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
        sprintf(resultado, "El promedio de pizzas por dia es %.2f", promedio);
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
        sprintf(resultado, "El promedio de pizzas por orden es: %.2f", promedio);
    } else {
        strcpy(resultado, "No hay datos suficientes.");
    }
    return resultado;
}

//Calcula los días que venden más pizzas junto con la cantidad
char *dmsp(int size, order *orders) {
    int num_fechas = 0;
    int ventas[200] = {0};
    char fechas[200][20]; 

    static char resultado[500];  
    resultado[0] = '\0';  

    // Cuenta las ventas por fecha
    for (int i = 0; i < size; i++) {
        char *fecha_actual = orders[i].order_date;  
        int cantidad = (int) orders[i].quantity;

        // Revisa si la fecha esta repetida
        int j;
        for (j = 0; j < num_fechas; j++) {
            if (strcmp(fechas[j], fecha_actual) == 0) {
                ventas[j] += cantidad; 
                break;
            }
        }

        // Si la fecha no estaba agregada, la agrega
        if (j == num_fechas && num_fechas < 200) {
            strcpy(fechas[num_fechas], fecha_actual);
            ventas[num_fechas] = cantidad;
            num_fechas++;
        }
    }

    // Encuentra la cantidad maxima de ventas 
    int max_ventas = 0;
    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i] > max_ventas) {
            max_ventas = ventas[i];  // Guardar la cantidad máxima
        }
    }

    // Muestra los resultados
    sprintf(resultado, "Las fechas con más ventas (%d pizzas) son:\n", max_ventas);
    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i] == max_ventas) {
            strcat(resultado, "- ");
            strcat(resultado, fechas[i]);
            strcat(resultado, "\n");
        }
    }

    return resultado;
}


//Fecha con menos ventas en términos de cantidad de pizzas (junto a la cantidad de pizzas)
char *dlsp(int size, order *orders) {
    int num_fechas = 0;
    int ventas[200] = {0};
    char fechas[200][20];  

    static char resultado[500];  
    resultado[0] = '\0';  

    // Cuenta las ventas por fecha
    for (int i = 0; i < size; i++) {
        char *fecha_actual = orders[i].order_date;  
        int cantidad = (int) orders[i].quantity;

        // Revisa si la fecha esta repetida
        int j;
        for (j = 0; j < num_fechas; j++) {
            if (strcmp(fechas[j], fecha_actual) == 0) {
                ventas[j] += cantidad; 
                break;
            }
        }

        // Si la fecha no estaba agregada, la agrega
        if (j == num_fechas && num_fechas < 200) {
            strcpy(fechas[num_fechas], fecha_actual);
            ventas[num_fechas] = cantidad;
            num_fechas++;
        }
    }

   // Encuentra la cantidad minima de ventas 
    int min_ventas = -1;  //Se parte con un valor para encontrar si hubo ventas

    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i] > 0) {  
            if (min_ventas == -1 || ventas[i] < min_ventas) {
                min_ventas = ventas[i];
            }
        }
    }

// Si no encuentra valores mayores que 0, significa que no hubo ventas
if (min_ventas == -1) {
    min_ventas = 0;  
}

    // Muestra los resultados
    sprintf(resultado, "Las fechas con menos ventas (%d pizzas) son:\n", min_ventas);
    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i] == min_ventas) {
            strcat(resultado, "- ");
            strcat(resultado, fechas[i]);
            strcat(resultado, "\n");
        }
    }

    return resultado;
}