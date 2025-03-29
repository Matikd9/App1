#include <stdio.h>
#include <string.h>

// Lo que hace la función es leer el .csv para luego almacenar sus filas y columnas en un array doble
void leercsv(const char *archivo, char datos[200][200][200], int *filas, int *columnas) {
    FILE *file;
    file = fopen(archivo, "r"); // Se abre el archivo
    char linea[1024];  // Se crea un array para guardar las líneas del .csv
    *filas = 0; // Se inicia el contador de filas

    if (file != NULL) {
        while (fgets(linea, sizeof(linea), file) != NULL) { // Se lee el archivo línea por línea
            int col = 0;
            char *token = strtok(linea, ","); // Se separa la línea por comas
            while (token != NULL) {
                strcpy(datos[*filas][col], token);
                token = strtok(NULL, ",");
                col++;
            }
            *columnas = col;
            (*filas)++;
        }
        fclose(file);
    } else {
        printf("No se pudo abrir el archivo\n");
    }
}