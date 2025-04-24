#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int main(){

    int opciones, DNI, Objetivo;
    bool continuar = true;
    char nombre[30], apellido[30]; 
    FILE *usuarios;

    do
    {
        printf("1. Ingresar un nuevo usuario.\n");
        printf("2. Averiguar datos por DNI.\n");
        printf("3. Salir del programa.\n");
        scanf("%d", &opciones);

        switch(opciones)
        {
            case 1:
                printf("Ingrese su nombre: ");
                scanf("%s", nombre);
                printf("Ingrese su apellido: ");
                scanf("%s", apellido);
                printf("Ingrese su DNI: ");   
                scanf("%d", &DNI);
    
                usuarios = fopen("usuarios.txt", "a+");
                
                if(usuarios == NULL)
                {
                    printf("ERROR, el archivo no se pudo abrir\n");
                    return 1;
                }
    
                fprintf(usuarios, "%s %s %d\n", nombre, apellido, DNI);
                fclose(usuarios);
            break;
            
            case 2:
                printf("Ingrese el DNI de la persona buscada: ");
                scanf("%d", &Objetivo);
    
                usuarios = fopen("usuarios.txt", "r");
    
                if(usuarios == NULL)
                {
                    printf("ERROR, el archivo no se pudo abrir\n");
                    return 1;
                }          
    
                while(fscanf(usuarios, "%s %s %d", nombre, apellido, &DNI) != EOF)
                {
                    if(DNI == Objetivo)
                    {
                        printf("Nombre: %s\n", nombre);
                        printf("Apellido: %s\n", apellido);
                        printf("DNI: %d\n", DNI);
                    }
                }
                
                fclose(usuarios);
            break;

            case 3:
                continuar = false;
            break;

        }
    }while(continuar);

    return 0;
}
