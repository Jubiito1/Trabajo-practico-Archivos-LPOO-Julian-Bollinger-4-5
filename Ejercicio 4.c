#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>  

#define MAX_PERSONAS 100

typedef struct {
    char nombre[30];
    char apellido[30];
    int dni;
} Persona;

int compararPorNombreYApellido(const void *a, const void *b) {
    Persona *p1 = (Persona *)a;
    Persona *p2 = (Persona *)b;
    int cmp = strcmp(p1->apellido, p2->apellido);
    if (cmp == 0) {
        return strcmp(p1->nombre, p2->nombre);
    }
    return cmp;
}

int compararPorDNI(const void *a, const void *b) {
    Persona *p1 = (Persona *)a;
    Persona *p2 = (Persona *)b;
    return p1->dni - p2->dni;
}

int main() {
    
    FILE *datos;
    Persona personas[MAX_PERSONAS];
    char nombreIngresado[30], apellidoIngresado[30], nombreBuscado[30], apellidoBuscado[30];
    int op, DNIIngresado, cantidadPersonas = 0;
    bool continuar = true;

    do {
        printf("Ingrese una opcion: \n");
        printf("1. Ingresar datos\n");
        printf("2. Buscar por nombre y apellido o por DNI\n");
        printf("3. Salir\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                // Ingresar datos
                if (cantidadPersonas < MAX_PERSONAS) {
                    printf("Ingrese nombre: ");
                    scanf("%29s", nombreIngresado);  // Límite de caracteres para evitar desbordamiento
                    printf("Ingrese apellido: ");
                    scanf("%29s", apellidoIngresado);  // Límite de caracteres
                    printf("Ingrese DNI: ");
                    scanf("%d", &DNIIngresado);

                    // Guardar la persona en el arreglo
                    strcpy(personas[cantidadPersonas].nombre, nombreIngresado);
                    strcpy(personas[cantidadPersonas].apellido, apellidoIngresado);
                    personas[cantidadPersonas].dni = DNIIngresado;
                    cantidadPersonas++;

                    // Guardar los datos en el archivo
                    datos = fopen("datos.txt", "a");
                    if (datos == NULL) {
                        printf("No se pudo abrir el archivo\n");
                        return 1;
                    }
                    // Verificar si los datos se escriben correctamente
                    if (fprintf(datos, "%s %s %d\n", nombreIngresado, apellidoIngresado, DNIIngresado) < 0) {
                        printf("Error al escribir en el archivo.\n");
                        fclose(datos);
                        return 1;
                    }
                    fclose(datos);

                    printf("Datos guardados correctamente.\n");
                } else {
                    printf("No se pueden ingresar más personas, el arreglo está lleno.\n");
                }
                break;

            case 2:
                // Buscar por nombre y apellido o por DNI
                if (cantidadPersonas == 0) {
                    printf("No hay datos ingresados aún.\n");
                } else {
                    int opcionBusqueda;
                    printf("¿Desea buscar por nombre y apellido (1) o por DNI (2)? ");
                    scanf("%d", &opcionBusqueda);

                    // Preguntar si se desea ordenar los datos
                    int opcionOrdenar;
                    printf("¿Desea ordenar los datos antes de la búsqueda? (1: Sí / 2: No): ");
                    scanf("%d", &opcionOrdenar);

                    // Ordenar array
                    if (opcionOrdenar == 1) {
                        int opcionCriterioOrden;
                        printf("Desea ordenar por nombre y apellido (1) o por DNI (2)? ");
                        scanf("%d", &opcionCriterioOrden);

                        if (opcionCriterioOrden == 1) {
                            qsort(personas, cantidadPersonas, sizeof(Persona), compararPorNombreYApellido);
                        } else if (opcionCriterioOrden == 2) {
                            qsort(personas, cantidadPersonas, sizeof(Persona), compararPorDNI);
                        } else {
                            printf("Opción inválida. No se ordenarán los datos.\n");
                        }
                    }

                    if (opcionBusqueda == 1) {
                        printf("Ingrese el apellido que desea buscar: ");
                        scanf("%29s", apellidoBuscado);  // Límite de caracteres
                        printf("Ingrese el nombre que desea buscar: ");
                        scanf("%29s", nombreBuscado);  // Límite de caracteres

                        // Buscar la persona por nombre y apellido
                        bool encontrado = false;
                        for (int i = 0; i < cantidadPersonas; i++) {
                            if (strcmp(personas[i].apellido, apellidoBuscado) == 0 && strcmp(personas[i].nombre, nombreBuscado) == 0) {
                                printf("Persona encontrada:\n");
                                printf("%s %s %d\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
                                encontrado = true;
                                break;
                            }
                        }
                        if (!encontrado) {
                            printf("Persona no encontrada.\n");
                        }
                    } else if (opcionBusqueda == 2) {
                        printf("Ingrese el DNI que desea buscar: ");
                        scanf("%d", &DNIIngresado);

                        // Buscar por DNI
                        bool encontrado = false;
                        for (int i = 0; i < cantidadPersonas; i++) {
                            if (personas[i].dni == DNIIngresado) {
                                printf("Persona encontrada:\n");
                                printf("%s %s %d\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
                                encontrado = true;
                                break;
                            }
                        }
                        if (!encontrado) {
                            printf("Persona no encontrada.\n");
                        }
                    } else {
                        printf("Opción inválida.\n");
                    }
                    //Imprimir array ordenado
                    if (opcionOrdenar == 1) {
                        printf("Datos ordenados:\n");
                        for (int i = 0; i < cantidadPersonas; i++) {
                            printf("%s %s %d\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
                        }
                    }
                }
                break;

            case 3:
                continuar = false;
                break;

            default:
                printf("Opción inválida, intente nuevamente.\n");
                break;
        }
    } while (continuar);

    return 0;
}