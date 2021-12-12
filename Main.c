#include <stdio.h>
#include <math.h>   
#include <stdlib.h>
#include <time.h>

long long **asignar_matriz(int n, int m);                                                // Reservar la memoria y crear una matriz nula
void llenar_matriz(long long **matriz, int filas, int columnas);                         // Llenar la matriz nula con valores al azar utilizando la funcion rand()

int main()
{
    return 0;
}


long long **asignar_matriz(int n, int m)
{
    int i, j;
    long long **array;
    array = (long long **)malloc(n * sizeof(long long *)); // se reserva memoria  para la matriz de x filas que contiene direcciones de memoria a las segundas dimensiones.
    for (i = 0; i < n; i++)
    {
        array[i] = (long long *)malloc(m * sizeof(long long)); // se reserva memoria para las segundas dimensiones , x columnas
    }
    // en memoria ya tenemos reservado espacio para una matriz de x por x --> array[x][x]
    return &*array; // retorno de un puntero doble
}

void llenar_matriz(long long **matriz, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            matriz[i][j] = ((long long)(rand() % P)); // Se asignan valores aleatorios a cada coordenadas de la matriz
        }
    }
}
