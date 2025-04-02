#include <stdio.h>
#include "../include/utils.h"
#include "../include/metrics.h"
#include <stdlib.h>
#include <string.h>
#include "../include/orders.h"

// Calcula pizza más vendida
char *pms(int size, order *orders) {
    float maximo = 0;
    char nombres_agregados[2000] = "";
    char pizzas_mas_vendidas[2000] = "";

    // Paso 1: Encontrar el máximo de ventas por tipo de pizza
    for (int i = 0; i < size; i++) {
        float total = 0;
        for (int j = 0; j < size; j++) {
            if (strcmp(orders[i].pizza_name, orders[j].pizza_name) == 0) {
                total += orders[j].quantity;
            }
        }
        if (total > maximo) {
            maximo = total;
        }
    }

    // Paso 2: Agregar todas las pizzas con esa cantidad máxima (sin repetir)
    for (int i = 0; i < size; i++) {
        float total = 0;
        for (int j = 0; j < size; j++) {
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

    sprintf(mensaje_final, "Pizza(s) más vendida(s) (%.0f unidades):\n%s", maximo, pizzas_mas_vendidas);
    return mensaje_final;
}

// Calcula pizza menos vendida
char *pls(int size, order *orders) {
    float minimo = -1; // Inicializar con -1 para indicar que no se ha encontrado un mínimo aún
    char nombres_agregados[2000] = "";
    char pizzas_menos_vendidas_str[2000] = "";

    // Paso 1: Encontrar el mínimo de ventas por tipo de pizza
    for (int i = 0; i < size; i++) {
        float total = 0;
        for (int j = 0; j < size; j++) {
            if (strcmp(orders[i].pizza_name, orders[j].pizza_name) == 0) {
                total += orders[j].quantity;
            }
        }
        if (total > 0 && (minimo == -1 || total < minimo)) {
            minimo = total;
        }
    }

    // Paso 2: Agregar todas las pizzas con esa cantidad mínima (sin repetir)
    for (int i = 0; i < size; i++) {
        float total = 0;
        for (int j = 0; j < size; j++) {
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

    sprintf(mensaje_final, "Pizza(s) menos vendida(s) (%.0f unidades):\n%s", minimo, pizzas_menos_vendidas_str);
    return mensaje_final;
}

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

#define MAX_CATEGORIAS 10
#define MAX_INGREDIENTES 500
#define MAX_STR 200

// Estructura auxiliar para categorías
typedef struct {
    char nombre[MAX_STR];
    int cantidad_de_pizzas;
} Categoria;

// Estructura para el resultado de categorías
typedef struct {
    Categoria categorias[MAX_CATEGORIAS];
    int num_categorias;
} ResultadoCategorias;

// Estructura auxiliar para ingredientes
typedef struct {
    char nombre[MAX_STR];
    int total;
} Ingrediente;


// funcion para contar pizzas por categoría

ResultadoCategorias hp(int size, order *orders) {
    ResultadoCategorias resultado;
    resultado.num_categorias = 0;

    for (int i = 0; i < size; i++) {
        char *categoria = orders[i].pizza_category;
        int cantidad = (int)orders[i].quantity;

        if (strlen(categoria) == 0) continue;

        // Buscar si ya existe
        int encontrada = -1;
        for (int j = 0; j < resultado.num_categorias; j++) {
            if (strcmp(resultado.categorias[j].nombre, categoria) == 0) {
                encontrada = j;
                break;
            }
        }

        if (encontrada == -1) {
            // Agregar nueva categoría
            strcpy(resultado.categorias[resultado.num_categorias].nombre, categoria);
            resultado.categorias[resultado.num_categorias].cantidad_de_pizzas = cantidad;
            resultado.num_categorias++;
        } else {
            // Acumular cantidad
            resultado.categorias[encontrada].cantidad_de_pizzas += cantidad;
        }
    }

    return resultado;
}


// funcion para encontrar ingrediente más vendido


Ingrediente ims(int size, order *orders) {
    Ingrediente ingredientes[MAX_INGREDIENTES];
    int num_ingredientes = 0;

    for (int i = 0; i < size; i++) {
        int cantidad = (int)orders[i].quantity;
        char buffer[MAX_STR];
        strncpy(buffer, orders[i].pizza_ingredients, MAX_STR);

        // Separar ingredientes por coma
        char *token = strtok(buffer, ",");
        while (token != NULL) {
            while (*token == ' ') token++; // limpiar espacios

            int encontrado = -1;
            for (int j = 0; j < num_ingredientes; j++) {
                if (strcmp(ingredientes[j].nombre, token) == 0) {
                    encontrado = j;
                    break;
                }
            }

            if (encontrado == -1) {
                // Nuevo ingrediente
                strcpy(ingredientes[num_ingredientes].nombre, token);
                ingredientes[num_ingredientes].total = cantidad;
                num_ingredientes++;
            } else {
                // Ya existe, sumar cantidad
                ingredientes[encontrado].total += cantidad;
            }

            token = strtok(NULL, ",");
        }
    }

    // Buscar el ingrediente con mayor cantidad
    Ingrediente top = ingredientes[0];
    for (int i = 1; i < num_ingredientes; i++) {
        if (ingredientes[i].total > top.total) {
            top = ingredientes[i];
        }
    }

    return top;
}
