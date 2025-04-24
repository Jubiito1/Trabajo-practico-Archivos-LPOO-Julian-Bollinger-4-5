#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int main()
{
    int op, DNI, DNIIngresado;
    bool DNIRepetido = false,continuar = true;
    char nombre[30], apellido[30], nombreBuscado[30], apellidoBuscado[30], nombreIngresado[30], apellidoIngresado[30];
    FILE *datos;
    
    do
    {
        printf("1. Ingresar un nuevo usuario.\n");
        printf("2. Averiguar datos por DNI.\n");
        printf("3. Salir del programa.\n");
        scanf("%d", &op);

        switch(op){

            case 1:
                DNIRepetido = false;
    
                printf("Ingrese nombre: ");
                scanf("%s", nombreIngresado);
                printf("Ingrese apellido: ");
                scanf("%s", apellidoIngresado);            
                printf("Ingrese DNI: ");   
                scanf("%d", &DNIIngresado);
    
                datos = fopen("datos.txt", "r");
    
                if (datos != NULL)
                {
                    char nomTemp[30], apeTemp[30];
                    int dniTemp;
    
                    while(fscanf(datos, "%s %s %d", nomTemp, apeTemp, &dniTemp) != EOF)
                    {
                        if(dniTemp == DNIIngresado)
                        {
                            printf("El DNI ya existe. No se puede ingresar el dato.\n");
                            DNIRepetido = true;
                            break;
                        }
                    }
                    fclose(datos);
                }
    
                if (!DNIRepetido)
                {
                    datos = fopen("datos.txt", "a");
                    if(datos == NULL)
                    {
                        printf("No se pudo abrir el archivo\n");
                        return 1;
                    }
                    
                    strcpy(nombre, nombreIngresado);
                    strcpy(apellido, apellidoIngresado);
                    DNI = DNIIngresado;
                    
                    fprintf(datos, "%s %s %d\n", nombre, apellido, DNI);
                    printf("Datos guardados correctamente.\n");
                    fclose(datos);
                }
                
                
                if(datos == NULL)
                {
                    printf("ERROR, el archivo no se pudo abrir\n");
                    return 1;
                }
                
                fclose(datos);
            break;
            
            case 2:
                printf("Ingrese el apellido que desea buscar: ");
                scanf("%s", apellidoBuscado);
                printf("Ingrese el nombre que desea buscar: ");
                scanf("%s", nombreBuscado);
                
                datos = fopen("datos.txt", "r");
                
                if(datos == NULL){
                    printf("ERROR, el archivo no se pudo abrir\n");
                    return 1;
                }          
                
                while(fscanf(datos, "%s %s %d", nombre, apellido, &DNI) != EOF){
                    if(strcmp(apellido, apellidoBuscado) == 0 && strcmp(nombre, nombreBuscado) == 0){
                        printf("Nombre: %s\n", nombre);
                        printf("Apellido: %s\n", apellido);
                        printf("DNI: %d\n", DNI);
                    }
                }
                
                fclose(datos);
            break;
            
            case 3:
                continuar = false;
            break;
        }
    }while(continuar);

    return 0;
}