#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


struct Persona {
	char nombre[30];
	char apellido[30];
};

int main() {

	FILE *datos, *datos2;
	struct Persona persona;
	char linea[100];

	datos = fopen("datos.txt", "r+");
	if (datos == NULL) {
		printf("No se pudo abrir el archivo original\n");
		return 1;
	}

	fprintf(datos, "Nombre: Juan\nApellido: Perez\n");

	printf("Ingrese el nombre: ");
	scanf("%29s", persona.nombre);

	printf("Ingrese el apellido: ");
	scanf("%29s", persona.apellido);

	datos2 = fopen("datos2.txt", "w+");
	if (datos2 == NULL) {
		printf("Error al crear el archivo");
		fclose(datos);
		return 1;
	}

	while(fgets(linea, sizeof(linea), datos) != NULL) {
		fputs(linea, datos2);
	}

	fprintf(datos2, "Nombre: %s\nApellido: %s\n", persona.nombre, persona.apellido);

	fclose(datos);
	fclose(datos2);

	printf("\nArchivo 1:\n");

	datos = fopen("datos.txt", "r");
	while (fgets(linea, sizeof(linea), datos) != NULL) {
		printf("%s", linea);
	}
	fclose(datos);

	printf("\nArchivo 2:\n");
	datos2 = fopen("datos2.txt", "r");
	while (fgets(linea, sizeof(linea), datos2) != NULL) {
		printf("%s", linea);
	}
	fclose(datos2);

	return 0;
}