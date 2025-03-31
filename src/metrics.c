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

// Calcula la fecha con más dinero generado junto con la cantidad recaudada
char *dms(int size, order *orders) {
    int num_fechas = 0;
    double ventas[200] = {0};  // almacenar  cantidad de dinero recaudado por fecha
    char fechas[200][20]; 

    static char resultado[500];  
    resultado[0] = '\0';  

    // Contar ventas por fecha en términos de dinero
    for (int i = 0; i < size; i++) {
        char *fecha_actual = orders[i].order_date;  
        double cantidad = orders[i].total_price; 

        // Buscar si la fecha ya existe 
        int j;
        for (j = 0; j < num_fechas; j++) {
            if (strcmp(fechas[j], fecha_actual) == 0) {
                ventas[j] += cantidad; 
                break;
            }
        }

        // Si no existe, se agrega
        if (j == num_fechas && num_fechas < 200) {
            strcpy(fechas[num_fechas], fecha_actual);
            ventas[num_fechas] = cantidad;
            num_fechas++;
        }
    }

    // Encontrar la fecha con la mayor cantidad de dinero recaudado
    int max_index = 0;
    for (int i = 1; i < num_fechas; i++) {
        if (ventas[i] > ventas[max_index]) {
            max_index = i;  
        }
    }

    // mostrar los resultados
    sprintf(resultado, "La fecha con más ventas en términos de dinero fue %s con un total de $%.2f\n", 
            fechas[max_index], ventas[max_index]);
    
    return resultado;
}





// Calcula la fecha con menos dinero generado junto con la cantidad recaudada
char *dls(int size, order *orders) {
    int num_fechas = 0;
    double ventas[200] = {0};  // se  almacena la cantidad de dinero recaudado por fecha
    char fechas[200][20]; 

    static char resultado[500];  
    resultado[0] = '\0';  

    // Contar ventas por fecha en términos de dinero
    for (int i = 0; i < size; i++) {
        char *fecha_actual = orders[i].order_date;  
        double cantidad = orders[i].total_price; 

        // Buscar si la fecha ya existe 
        int j;
        for (j = 0; j < num_fechas; j++) {
            if (strcmp(fechas[j], fecha_actual) == 0) {
                ventas[j] += cantidad; 
                break;
            }
        }

        // Si no existe, agregarla
        if (j == num_fechas && num_fechas < 200) {
            strcpy(fechas[num_fechas], fecha_actual);
            ventas[num_fechas] = cantidad;
            num_fechas++;
        }
    }

    // Encontrar la fecha con la menor cantidad de dinero recaudado (sin contar el  0)
    int min_index = -1;
    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i] > 0) { 
            if (min_index == -1 || ventas[i] < ventas[min_index]) {
                min_index = i;
            }
        }
    }

    // si es que no hay ventas mayores a 0 
    if (min_index == -1) {
        sprintf(resultado, "No hay ventas registradas.");
    } else {
        sprintf(resultado, "La fecha con menos ventas en términos de dinero fue %s con un total de $%.2f\n", 
                fechas[min_index], ventas[min_index]);
    }
    
    return resultado;
}