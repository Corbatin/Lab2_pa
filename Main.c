#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define P (long long)3781996138433268199
#define Pa (long long)1761129190
#define Pb (long long)892783079
#define bAJO (long long)2147483647

long long **asignar_matriz(int n, int m);                        // Reservar la memoria y crear una matriz nula
void llenar_matriz(long long **matriz, int filas, int columnas); // Llenar la matriz nula con valores al azar utilizando la funcion rand()
void llenar_submatriz(long long **matriz, long long **matriz_original, int iFilas, int fFilas, int iCol, int fCol);
void imprimir_matriz(long long **array, int filas, int columnas); // Funcion que imprime la matriz
void menu();                                                      // Menu para desplazarse entre las funciones del programa
long long **sumaMatrices(long long **matriz1, long long **matriz2, int filas, int columnas);
long long **restaMatrices(long long **matriz1, long long **matriz2, int filas, int columnas);
long long **multiplicacion_clasica(long long **matriz_1, long long **matriz_2, int filas_1, int filas_2, int col_1, int col_2);
long long **Mult_Strassen(long long **matriz_1, long long **matriz_2, int dim, long long **matriz_resultado);
void llenar_con_0(long long **matriz, int filas, int columnas);

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
    int opcion, filas, columnas, el, filas_2, columnas_2;
    long long **Matriz_1, **Matriz_2, **Matriz_resultado;
    clock_t tiempo1, tiempo2;

    printf("\nEscoga la cantidad de filas de la matriz 1: ");
    scanf("%i", &filas);
    printf("\nEscoga la cantidad de columnas de la matriz 1: ");
    scanf("%i", &columnas);

    Matriz_1 = asignar_matriz(filas, columnas);
    llenar_matriz(Matriz_1, filas, columnas);
    Matriz_2 = asignar_matriz(filas, columnas);
    llenar_matriz(Matriz_2, filas, columnas);
    // llenar_submatriz(Matriz_2,Matriz_1,0,filas/2,0,columnas/2);

    Matriz_resultado = asignar_matriz(filas, columnas);

    /*
    printf("\nEscoga la cantidad de filas de la matriz 2: ");
    scanf("%i", &filas_2);
    printf("\nEscoga la cantidad de columnas de la matriz 2: ");
    scanf("%i", &columnas_2);

    Matriz_1 = asignar_matriz(filas, columnas);
    Matriz_2 = asignar_matriz(filas_2, columnas_2);

    llenar_matriz(Matriz_1, filas, columnas);
    llenar_matriz(Matriz_2, filas_2, columnas_2);

    Matriz_resultado = asignar_matriz(filas_2, columnas);
    llenar_con_0(Matriz_resultado, filas_2, columnas);

    do
    {
        printf("\nQue desea ver?");
        printf("\n 1) Generar Nueva matriz 1. ");
        printf("\n 2) Generar Nueva matriz 2. ");
        printf("\n 3) Multiplicacion Matrices clasica.");
        printf("\n 4) Multiplicacion Matrices por Strassen.");
        // printf("\n 69) Leer Nueva matriz por archivo. ");
        printf("\n 0) Salir del programa.");
        scanf("%i", &opcion);

        switch (opcion)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            if(filas != columnas_2)
            {
                printf("\nDimensiones incorrectas, no se puede realizar multiplicacion ");
                break;
            }
            else{
                printf("\nMatriz 1: \n");
                imprimir_matriz(Matriz_1, filas, columnas);
                printf("\nMatriz 2: \n");
                imprimir_matriz(Matriz_2, filas_2, columnas_2);
                multiplicacion_clasica(Matriz_1, Matriz_2, filas, filas_2, columnas, columnas_2, Matriz_resultado);
                printf("\nMatriz Resultado: \n");
                imprimir_matriz(Matriz_resultado, filas_2, columnas);
                // free(cosas);
            }
            break;
        case 4:
            printf("\nMatriz 1: \n");
            imprimir_matriz(Matriz_1, filas, columnas);
            printf("\nMatriz 2: \n");
            imprimir_matriz(Matriz_2, filas_2, columnas_2);
            multiplicacion_clasica(Matriz_1, Matriz_2, filas, filas_2, columnas, columnas_2, Matriz_resultado);
            printf("\nMatriz Resultado: \n");
            imprimir_matriz(Matriz_resultado, filas_2, columnas);
            break;
        case 0:
            break;
        default:
            break;
        }
    } while (opcion);
    */
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

void llenar_submatriz(long long **matriz, long long **matriz_original, int iFilas, int fFilas, int iCol, int fCol)
{
    for (int i = iFilas; i < fFilas; i++)
    {
        for (int j = iCol; j < fCol; j++)
        {
            matriz[i][j] = matriz_original[i][j]; // Se asignan valores aleatorios a cada coordenadas de la matriz
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

long long **multiplicacion_clasica(long long **matriz_1, long long **matriz_2, int filas_1, int filas_2, int col_1, int col_2)
{
    long long suma, **Matriz_resultado;
    Matriz_resultado = asignar_matriz(filas_2, col_1);

    for (int i = 0; i < filas_1; i++)
    {
        for (int j = 0; j < col_2; j++)
        {
            suma = 0;
            for (int k = 0; k < col_1; k++)
            {
                suma = SumaP(suma, MultP(matriz_1[i][k], matriz_2[k][j]));
                // Matriz_resultado[i][j] += matriz_1[i][k] * matriz_2[k][j];
            }
            Matriz_resultado[i][j] = SumaP(suma, Matriz_resultado[i][j]);
        }
    }
    return Matriz_resultado;
}

void llenar_con_0(long long **matriz, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            matriz[i][j] = 0;
        }
    }
}

long long **Mult_Strassen(long long **matriz_1, long long **matriz_2, int dim)
{
    long long **matriz_a11, **matriz_a12, **matriz_a21, **matriz_a22;
    long long **matriz_b11, **matriz_b12, **matriz_b21, **matriz_b22;
    long long **matrizResultado;
    long long S1, S2, S3, S4, S5, T1, T2, T3, T4, T5, M1, M2, M3, M4, M5, M6, M7, C11, C12, C21, C22, aux, aux2;

    if (dim <= 2)
    {
        matrizResultado = asignar_matriz(2, 2);
        matrizResultado = multiplicacion_clasica(matriz_1, matriz_2, 2, 2, 2, 2); // transfromarla de void a long long
        return matrizResultado;
    }
    matriz_a11 = asignar_matriz(dim / 2, dim / 2);
    llenar_submatriz(matriz_a11, matriz_1, 0, dim / 2, 0, dim / 2); 
    matriz_a12 = asignar_matriz(dim / 2, dim / 2);
    llenar_submatriz(matriz_a12, matriz_1, dim / 2, dim, 0, dim);
    matriz_a21 = asignar_matriz(dim / 2, dim / 2);
    llenar_submatriz(matriz_a21, matriz_1, 0, dim / 2, dim / 2, dim);
    matriz_a22 = asignar_matriz(dim / 2, dim / 2);
    llenar_submatriz(matriz_a22, matriz_1, dim / 2, dim, dim / 2, dim);

    matriz_b11 = asignar_matriz(dim / 2, dim / 2);
    llenar_submatriz(matriz_b11, matriz_2, 0, dim / 2, 0, dim / 2);
    matriz_b12 = asignar_matriz(dim / 2, dim / 2);
    llenar_submatriz(matriz_b12, matriz_2, dim / 2, dim, 0, dim);
    matriz_b21 = asignar_matriz(dim / 2, dim / 2);
    llenar_submatriz(matriz_b21, matriz_2, 0, dim / 2, dim / 2, dim);
    matriz_b22 = asignar_matriz(dim / 2, dim / 2);
    llenar_submatriz(matriz_b22, matriz_2, dim / 2, dim, dim / 2, dim);

    Mult_Strassen(matriz_a11, matriz_b11, dim / 2); 
    Mult_Strassen(matriz_a12, matriz_b12, dim / 2);
    Mult_Strassen(matriz_a21, matriz_b21, dim / 2);
    Mult_Strassen(matriz_a22, matriz_b22, dim / 2);
    

    // Sumas de la matriz A
    S1 = sumaMatrices(matriz_a11, matriz_a22, dim, dim );
    S2 = sumaMatrices(matriz_a21, matriz_a22, dim, dim );
    S3 = sumaMatrices(matriz_a11, matriz_a12,dim,dim);
    S4 = restaMatrices(matriz_a21, matriz_a11, dim, dim );
    S5 = restaMatrices(matriz_a12, matriz_a22,dim,dim);

    // Sumas de la matriz B
    T1 = sumaMatrices(matriz_b11, matriz_b22, dim, dim);
    T2 = sumaMatrices(matriz_b21, matriz_b22, dim ,dim);
    T3 = sumaMatrices(matriz_b11, matriz_b12, dim, dim);
    T4 = restaMatrices(matriz_b21, matriz_b11, dim, dim);
    T5 = restaMatrices(matriz_b12, matriz_b22, dim, dim);

    // Multiplicaciones de Strassen
    M1 = multiplicacion_clasica(S1, T1,dim,dim,dim,dim);
    M2 = multiplicacion_clasica(S2, matriz_b11,dim,dim,dim,dim);
    M3 = multiplicacion_clasica(matriz_a11, T5,dim,dim,dim,dim);
    M4 = multiplicacion_clasica(matriz_a22, T4,dim,dim,dim,dim);
    M5 = multiplicacion_clasica(S3, matriz_b22,dim,dim,dim,dim);
    M6 = multiplicacion_clasica(S4, T3,dim,dim,dim,dim);
    M7 = multiplicacion_clasica(S5, T2,dim,dim,dim,dim);

    // Recombinacion de Strassen
    
    //Hay que asignar los aux y aux como doble punteros
    aux = sumaMatrices(M1, M4,dim,dim);
    aux2 = restaMatrices(aux, M5,dim,dim);
    aux = sumaMatrices(aux2, M7,dim,dim);
    C11 = aux2;
    C12 = sumaMatrices(M3, M5,dim,dim);
    C21 = restaMatrices(M2, M4,dim,dim);
    aux = restaMatrices(M1, M4,dim,dim);
    aux2 = sumaMatrices(M3, M6,dim,dim);
    C22 = sumaMatrices(aux, aux2,dim,dim);

    return 0; // algo
}

long long **Strassen(long long **matriz, int dim)
{

    // if (dim){

    // }
    // matriz_a11 = asignar_matriz(dim / 2, dim / 2);
    // llenar_submatriz(matriz_a11, matriz_1, 0, dim / 2, 0, dim / 2);
}

long long **sumaMatrices(long long **matriz1, long long **matriz2, int filas, int columnas)
{
    long long **Mresultado;
    Mresultado = asignar_matriz(filas, columnas);
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            Mresultado[i][j] = matriz1[i][j] + matriz2[i][j];
        }
    }
    return Mresultado;
}

long long **restaMatrices(long long **matriz1, long long **matriz2, int filas, int columnas)
{
    long long resta = 0, **matrizResultado;
    matrizResultado = asignar_matriz(filas, columnas);
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            resta = RestaP(matriz1[i][j], matriz2[i][j]);
            matrizResultado[i][j] = matrizResultado[i][j];
            printf("\nMatriz : %lld ", matrizResultado[i][j]);
        }
    }
    return matrizResultado;
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

/* TEXTOS SAGRADOS 2

matriz 2x2
matriz = asignar_matriz(2,2)

matriz m x m
matriz_11 = asignar_matriz(m/2,m/2)
matriz_12 = asignar_matriz(m/2,m/2)
matriz_21 = asignar_matriz(m/2,m/2)
matriz_22 = asignar_matriz(m/2,m/2)


matriz_11 = copiar_valores (matriz,0,m/2,0,m/2 )
matriz_12 = copiar_valores (matriz,m/2,m,0,m/2 )
matriz_21 = copiar_valores (matriz,0,m/2,m/2,m)
matriz_22 = copiar_valores (matriz,m/2,m,m/2,m )

memcpy ->	copia n bytes entre dos áreas de memoria que no deben solaparse
strcpy ->	copia una cadena en otra
*/