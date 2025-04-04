#include <stdio.h>
#include "metrics.h"
#include <stdlib.h>
#include <string.h>
#include "orders.h"

// Calcula pizza más vendida
char *pms(int *size, order *orders) {
    float maximo = 0;
    char nombres_agregados[2000] = "";
    char pizzas_mas_vendidas[2000] = "";

    // Paso 1: Encontrar el máximo de ventas por tipo de pizza
    for (int i = 0; i < *size; i++) {
        float total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].pizza_name, orders[j].pizza_name) == 0) {
                total += orders[j].quantity;
            }
        }
        if (total > maximo) {
            maximo = total;
        }
    }

    // Paso 2: Agregar todas las pizzas con esa cantidad máxima (sin repetir)
    for (int i = 0; i < *size; i++) {
        float total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].pizza_name, orders[j].pizza_name) == 0) {
                total += orders[j].quantity;
            }
        }

        if (total == maximo && strstr(nombres_agregados, orders[i].pizza_name) == NULL) {
            strcat(pizzas_mas_vendidas, orders[i].pizza_name);
            strcat(pizzas_mas_vendidas, "\n");
            strcat(nombres_agregados, orders[i].pizza_name);
            strcat(nombres_agregados, "|");
        }
    }

    // Paso 3: Crear el mensaje final
    char *mensaje_final = malloc(strlen(pizzas_mas_vendidas) + 100);
    if (!mensaje_final) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    sprintf(mensaje_final, "Pizza(s) más vendida(s) (%.0f unidades):\n%s\n", maximo, pizzas_mas_vendidas);
    return mensaje_final;
}

// Calcula pizza menos vendida
char *pls(int *size, order *orders) {
    float minimo = -1; // Inicializar con -1 para indicar que no se ha encontrado un mínimo aún
    char nombres_agregados[2000] = "";
    char pizzas_menos_vendidas_str[2000] = "";

    // Paso 1: Encontrar el mínimo de ventas por tipo de pizza
    for (int i = 0; i < *size; i++) {
        float total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].pizza_name, orders[j].pizza_name) == 0) {
                total += orders[j].quantity;
            }
        }
        if (total > 0 && (minimo == -1 || total < minimo)) {
            minimo = total;
        }
    }

    // Paso 2: Agregar todas las pizzas con esa cantidad mínima (sin repetir)
    for (int i = 0; i < *size; i++) {
        float total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].pizza_name, orders[j].pizza_name) == 0) {
                total += orders[j].quantity;
            }
        }

        if (total == minimo && strstr(nombres_agregados, orders[i].pizza_name) == NULL) {
            strcat(pizzas_menos_vendidas_str, orders[i].pizza_name);
            strcat(pizzas_menos_vendidas_str, "\n");
            strcat(nombres_agregados, orders[i].pizza_name);
            strcat(nombres_agregados, "|");
        }
    }

    // Paso 3: Crear el mensaje final
    char *mensaje_final = malloc(strlen(pizzas_menos_vendidas_str) + 100);
    if (!mensaje_final) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    sprintf(mensaje_final, "Pizza(s) menos vendida(s) (%.0f unidades):\n%s\n", minimo, pizzas_menos_vendidas_str);
    return mensaje_final;
}

// Calcula el promedio de pizzas por día
char *apd(int *size, order *orders) {
    int contador = 0;
    int total_pizzas = 0;
    static char resultado[100];  // Usar un buffer estático para almacenar el resultado

    for (int i = 0; i < *size; i++) {
        total_pizzas += (int)orders[i].quantity;  // Convierte quantity a entero si es necesario

        // Si el día cambia, contar una nueva entrada
        if (i == 0 || strcmp(orders[i+1].order_date, orders[i].order_date) != 0) {
            contador++;
        }
    }

    if (contador > 0) {
        double promedio = (double) total_pizzas / contador;
        sprintf(resultado, "El promedio de pizzas por dia es %.2f\n", promedio);
    } else {
        strcpy(resultado, "No hay datos suficientes.");
    }
    return resultado;
}

// Calcula promedio de pizzas por orden
char *apo(int *size, order *orders) {
    int contador = 0;
    int total_pizzas = 0;
    static char resultado[100];  // Usar un buffer estático para almacenar el resultado

    for (int i = 0; i < *size; i++) {
        total_pizzas += (int)orders[i].quantity;  // Convierte quantity a entero si es necesario

        // Si el día cambia, contar una nueva entrada
        if (i == 0 ||orders[i+1].order_id !=  orders[i].order_id) {
            contador++;
        }
    }

    if (contador > 0) {
        double promedio = (double) total_pizzas / contador;
        sprintf(resultado, "El promedio de pizzas por orden es: %.2f\n", promedio);
    } else {
        strcpy(resultado, "No hay datos suficientes.");
    }
    return resultado;
}

//Calcula los días que venden más pizzas junto con la cantidad
char *dmsp(int *size, order *orders) {
    int num_fechas = 0;
    int ventas[200] = {0};
    char fechas[200][20]; 

    static char resultado[500];  
    resultado[0] = '\0';  

    // Cuenta las ventas por fecha
    for (int i = 0; i < *size; i++) {
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
char *dlsp(int *size, order *orders) {
    int num_fechas = 0;
    int ventas[200] = {0};
    char fechas[200][20];  

    static char resultado[500];  
    resultado[0] = '\0';  

    // Cuenta las ventas por fecha
    for (int i = 0; i < *size; i++) {
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
char *dms(int *size, order *orders) {
    int num_fechas = 0;
    double ventas[200] = {0};  // almacenar  cantidad de dinero recaudado por fecha
    char fechas[200][20]; 

    static char resultado[500];  
    resultado[0] = '\0';  

    // Contar ventas por fecha en términos de dinero
    for (int i = 0; i < *size; i++) {
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
    sprintf(resultado, "La(s) fecha(s) con más ventas en términos de dinero (%.2f) fueron: \n", ventas[max_index]);
    for (int i = 0; i < num_fechas; i++){
        if (ventas[i] == ventas[max_index]){
            strcat(resultado, "- ");
            strcat(resultado, fechas[i]);
            strcat(resultado, "\n\n");
        }
    }
    return resultado;
}





// Calcula la fecha con menos dinero generado junto con la cantidad recaudada
char *dls(int *size, order *orders) {
    int num_fechas = 0;
    double ventas[200] = {0};  // se  almacena la cantidad de dinero recaudado por fecha
    char fechas[200][20]; 

    static char resultado[500];  
    resultado[0] = '\0';  

    // Contar ventas por fecha en términos de dinero
    for (int i = 0; i < *size; i++) {
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
        sprintf(resultado, "La(s) fecha(s) con menos ventas en términos de dinero (%.2f) fueron: \n", ventas[min_index]);
        for (int i = 0; i < num_fechas; i++){
            if (ventas[i] == ventas[min_index]){
                strcat(resultado, "- ");
                strcat(resultado, fechas[i]);
                strcat(resultado, "\n\n");
            }
        }    
    }
    
    return resultado;
}

#define MAX_CATEGORIAS 10
#define MAX_INGREDIENTES 500
#define MAX_STR 200

// funcion para contar pizzas por categoría
char *hp(int *size, order *orders) {
    char categorias[*size][20]; // Array para categorías 
    float ventas[*size];        // Ventas acumuladas por cada categoria
    int categorias_unicas = 0; // Contador
    // Se cuentan ventas por categorio
    for (int i = 0; i < *size; i++) {
        int encontrado = 0;
        for (int j = 0; j < categorias_unicas; j++) {
            if (strcmp(categorias[j], orders[i].pizza_category) == 0) {
                ventas[j] += orders[i].quantity;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(categorias[categorias_unicas], orders[i].pizza_category);
            ventas[categorias_unicas] = orders[i].quantity;
            categorias_unicas++;
        }
    }

    char *resultado = malloc(5000);
    if (!resultado) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    strcpy(resultado, "Ventas por categoría:\n");

    char linea[100];
    for (int i = 0; i < categorias_unicas; i++) {
        sprintf(linea, "%s: %.0f unidades\n", categorias[i], ventas[i]);
        strcat(resultado, linea);
    }

    return resultado;
}

// funcion para encontrar ingrediente más vendido
char *ims(int *size, order *orders) {
    static char resultado[1024]; // static char para almacenar resultados
    resultado[0] = '\0'; // Aseguramos que el resultado esté vacío con un NULL
    
    // Limita la cantidad máxima de ingredientes por simplicidad
    char ingredientes[MAX_INGREDIENTES][MAX_STR]; // Nombres de los ingredientes
    int cantidad_ingredientes[MAX_INGREDIENTES] = {0}; 
    int num_ingredientes = 0;

    // Se procesa cada orden
    for (int i = 0; i < *size; i++) {
        int cantidad = (int)orders[i].quantity; // Obtiene cantidad de pizza
        char buffer[MAX_STR];
        strncpy(buffer, orders[i].pizza_ingredients, MAX_STR); // Copia los ingredientes

        // Separa ingredientes por coma
        char *token = strtok(buffer, ",");
        while (token != NULL) {
            // Elimina los espacios entre cada ingrediente
            while (*token == ' ') token++; 
            char *end = token + strlen(token) - 1;
            while (end > token && *end == ' ') *end-- = '\0';

            int encontrado = -1;
            // Se busca si el ingrediente ya está en el listado
            for (int j = 0; j < num_ingredientes; j++) {
                if (strcmp(ingredientes[j], token) == 0) {
                    encontrado = j;
                    break;
                }
            }

            if (encontrado == -1) {
                // Si no se encuentra el ingrediente se agrega
                if (num_ingredientes < MAX_INGREDIENTES) {
                    strcpy(ingredientes[num_ingredientes], token);
                    cantidad_ingredientes[num_ingredientes] = cantidad;
                    num_ingredientes++;
                }
            } else {
                // Si ya existe se suma
                cantidad_ingredientes[encontrado] += cantidad;
            }

            token = strtok(NULL, ",");
        }
    }

    // Busca el ingrediente con la mayor cantidad
    int max_cantidad = cantidad_ingredientes[0];
    int max_index = 0;
    for (int i = 1; i < num_ingredientes; i++) {
        if (cantidad_ingredientes[i] > max_cantidad) {
            max_cantidad = cantidad_ingredientes[i];
            max_index = i;
        }
    }

    // Se construye la estructura de como se va a printear
    sprintf(resultado, "El ingrediente más popular es: %s con una cantidad total de %d\n\n", ingredientes[max_index], max_cantidad);
    
    return resultado;
}

