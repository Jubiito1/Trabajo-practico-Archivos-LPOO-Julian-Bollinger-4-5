#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define max_jugadores 10

struct Jugador{
    char nombre[30];
    int puntaje;
};

void ingresarJugadores();
void mejoresDiez();
void busqueda();

int main(){

    FILE *archivoJugadores;
    struct Jugador jugadores[max_jugadores];
    struct Jugador jugador;
    char nombreBuscado[30];

    ingresarJugadores(jugadores, jugador);
    mejoresDiez(jugadores);
    printf("Ingrese el nombre del jugador que desea buscar: ");
    scanf("%s", nombreBuscado);
    busqueda(jugadores, nombreBuscado);


}

void ingresarJugadores(struct Jugador jugadores[], struct Jugador jugador){

    for(int i = 0; i < max_jugadores; i++){ 
        printf("Ingrese el nombre del jugador %d: ", i+1);
        scanf("%s", jugador.nombre);
        printf("Ingrese el puntaje del jugador %d: ", i+1);
        scanf("%d", &jugador.puntaje);

        FILE *archivo = fopen("jugadores.txt", "a+");
        if (archivo == NULL) {
            printf("Error al abrir el archivo\n");
            return;
        }
        fprintf(archivo, "%s %d\n", jugador.nombre, jugador.puntaje);
        fclose(archivo);
        jugadores[i] = jugador;
    }
}

void mejoresDiez(struct Jugador jugadores[]){

    for(int i = 0; i < max_jugadores; i++){
        for(int j = i + 1; j < max_jugadores; j++){
            if(jugadores[i].puntaje < jugadores[j].puntaje){
                struct Jugador temp = jugadores[i];
                jugadores[i] = jugadores[j];
                jugadores[j] = temp;
            }
        }
    }
    printf("Los 10 mejores jugadores son:\n");
    for(int i = 0; i < max_jugadores; i++){
        printf("%s %d\n", jugadores[i].nombre, jugadores[i].puntaje);
    }
}

void busqueda(struct Jugador jugadores[], char nombreBuscado[]){

    printf("Ingrese el nombre del jugador que desea buscar: ");
    scanf("%s", nombreBuscado);

    bool encontrado = false;
    for(int i = 0; i < max_jugadores; i++){
        if(strcmp(jugadores[i].nombre, nombreBuscado) == 0){
            printf("Jugador encontrado: %s %d\n", jugadores[i].nombre, jugadores[i].puntaje);
            encontrado = true;
        }
    }
    if(!encontrado){
        printf("Jugador no encontrado.\n");
    }
}