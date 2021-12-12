#include <stdio.h>
#include <math.h>   
#include <stdlib.h>
#include <time.h>

#define P (long long)3781996138433268199
#define Pa (long long)1761129190
#define Pb (long long)892783079
#define bAJO (long long)2147483647

long long **asignar_matriz(int n, int m);                                              // Reservar la memoria y crear una matriz nula
void llenar_matriz(long long **matriz, int filas, int columnas);                       // Llenar la matriz nula con valores al azar utilizando la funcion rand()
void imprimir_matriz(long long **array, int filas, int columnas);                      // Funcion que imprime la matriz
void menu();                                                                           // Menu para desplazarse entre las funciones del programa
void multiplicacion_original(long long **matriz_1,long long **matriz_2,int filas_1,int filas_2,int col_1,int col_2);

// ########### Funciones Profesor #######//
long long MultP(long long a, long long b);
long long RestaP(long long a, long long b);
long long SumaP(long long a, long long b);
long long InvP(long long A);


int main()
{
    srand(time(0)); // metodo para generar numeros aleatorios
    menu();
    return 0;
}

void menu()
{
    int opcion, filas, columnas, el;
    long long** Matriz_1, Matriz_2, Matriz_resultado;
    clock_t tiempo1, tiempo2;
    
    printf("\nEscoga la cantidad de filas de la matriz 1: ");
    scanf("%i", &filas);
    printf("\nEscoga la cantidad de columnas de la matriz 1: ");
    scanf("%i", &columnas);
    
    Matriz_resultado = asignar_matriz(filas, columnas);

    do{
        printf("Que desea ver?");
        printf("\n 1) Generar Nueva matriz 1. ");
        printf("\n 2) Generar Nueva matriz 2. ");
        printf("\n 3) Multiplicacion Matrices clasica.");
        printf("\n 4) Multiplicacion Matrices por Strassen.");
        //printf("\n 69) Leer Nueva matriz por archivo. ");
        printf("\n 0) Salir del programa.");    
        scanf("%i",&opcion);
        
        switch (el)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;    
        case 0:
            break;    
        default:
            break;
        }
        
    }while(opcion);
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
void imprimir_matriz(long long **array, int filas, int columnas)
{
    int i, j;
    printf("\nIMPRIMIENDO MATRIZ\n");
    printf("\n==================\n");

    for (i = 0; i < filas; i++)
    {
        printf("\n");
        for (j = 0; j < columnas; j++)
        {
            printf("%lld ", array[i][j]);
        }
    }
}
















// Funciones entregadas para los calculos en mod p.
long long InvP(long long A)
{
    long long a, b, s1, s2, r, u;
    a = A;
    b = P;
    s1 = 1;
    s2 = 0;
    if (A == 0)
    {
        printf("Error, division entre 0\n");
        return (0);
    }
    while ((a % 2) == 0)
    {
        a >>= 1;
        if ((s1 % 2) == 0)
        {
            s1 >>= 1;
        }
        else
        {
            s1 = (s1 + P) >> 1;
        }
    }
    if (b > a)
    {
        r = b;
        b = a;
        a = r;
        u = s2;
        s2 = s1;
        s1 = u;
    }
    while ((b != 0) && (b != a))
    {
        r = a - b;
        u = RestaP(s1, s2);
        while ((r % 2) == 0)
        {
            r >>= 1;
            if ((u % 2) == 0)
            {
                u >>= 1;
            }
            else
            {
                u = (u + P) >> 1;
            }
        }
        if (r < b)
        {
            a = b;
            b = r;
            s1 = s2;
            s2 = u;
        }
        else
        {
            a = r;
            s1 = u;
        }
    }
    return (s1);
}

long long SumaP(long long a, long long b)
{
    long long c;
    c = a + b;
    if (c < P)
    {
        return (c);
    }
    else
    {
        return (c - P);
    }
}

long long MultP(long long a, long long b)
{
    long long a0, a1, b0, b1, d0, d1, d2, d3;
    long long c;

    a0 = a & bAJO;
    a1 = a >> 31;
    b0 = b & bAJO;
    b1 = b >> 31;
    d0 = a0 * b0;
    d3 = a1 * b1;
    a1 += a0;
    b1 += b0;
    d2 = d0 + d3;
    d1 = a1 * b1;
    d1 -= d2;
    d3 += (d1 >> 31);
    d2 = d1 & bAJO;
    d2 += d0 >> 31;
    d1 = d0 & bAJO;
    a1 = d3 / Pa;
    b1 = ((d3 % Pa) << 31) + d2 - (a1 * Pb);
    while (b1 < 0)
    {
        b1 += P;
    }
    while (b1 >= P)
    {
        b1 -= P;
    }
    a0 = b1 / Pa;
    b0 = ((b1 % Pa) << 31) + d1 - (a0 * Pb);
    while (b0 < 0)
    {
        b0 += P;
    }
    while (b0 >= P)
    {
        b0 -= P;
    }
    return (b0);
}

long long RestaP(long long a, long long b)
{
    if (a < b)
    {
        return ((P + a) - b);
    }
    else
    {
        return (a - b);
    }
}
