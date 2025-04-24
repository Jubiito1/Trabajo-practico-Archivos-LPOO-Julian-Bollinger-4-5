#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int main(){
 
    int opciones, DNI;
    bool continuar = true;
    char nombre[30], apellido[30], nombreObjetivo[30], apellidoObjetivo[30];
    FILE *usuarios;
    
    do
    {
        printf("1. Ingresar un nuevo usuario.\n");
        printf("2. Averiguar usuarios por DNI.\n");
        printf("3. Salir\n");
        scanf("%d", &opciones);

        switch(opciones)
        {
            case 1:
                printf("Ingrese nombre: ");
                scanf("%s", nombre);
                printf("Ingrese apellido: ");
                scanf("%s", apellido);
                printf("Ingrese DNI: ");   
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
                printf("Ingrese el apellido que desea buscar: ");
                scanf("%s", apellidoObjetivo);
                printf("Ingrese el nombre que desea buscar: ");
                scanf("%s", nombreObjetivo);
    
                usuarios = fopen("usuarios.txt", "r");
    
                if(usuarios == NULL)
                {
                    printf("ERROR, el archivo no se pudo abrir\n");
                    return 1;
                }          
    
                while(fscanf(usuarios, "%s %s %d", nombre, apellido, &DNI) != EOF)
                {
                    if(strcmp(apellido, apellidoObjetivo) == 0 && strcmp(nombre, nombreObjetivo) == 0)
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




