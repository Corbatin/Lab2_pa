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
long long **Mult_Strassen(long long **matriz_1, long long **matriz_2, int dim);
void llenar_con_0(long long **matriz, int filas, int columnas);
long long **recombinarMatriz(long long **C11, long long **C12, long long **C21, long long **C22, int dim); // Funcion que recombina las 4 sub matrices en la matriz mas grande
void dividir_matriz(long long **matrizO, long long **matriz_11, long long **matriz_12, long long **matriz_21, long long **matriz_22, int dim);
long long** matriz_par(long long **matriz, int filas, int columnas;
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

    Matriz_resultado = asignar_matriz(filas, columnas);
    Matriz_resultado = multiplicacion_clasica(Matriz_1, Matriz_2, filas, filas, columnas, columnas);
    printf("\nMatriz 1: \n");
    imprimir_matriz(Matriz_1, filas, columnas);
    printf("\nMatriz 2: \n");
    imprimir_matriz(Matriz_2, filas, columnas);
    Matriz_resultado = multiplicacion_clasica(Matriz_1, Matriz_2, filas, filas, columnas, columnas);
    printf("\n\nMultiplicacion Clasica: \n");
    imprimir_matriz(Matriz_resultado, filas, columnas);
    llenar_con_0(Matriz_resultado, filas, columnas);
    Matriz_resultado = Mult_Strassen(Matriz_1, Matriz_2, filas);
    printf("\n\nMultiplicacion de Strassen : \n");
    imprimir_matriz(Matriz_resultado, filas, columnas);

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
            matriz[i][j] = i + j + 1; //((long long)(rand() % P)); // Se asignan valores aleatorios a cada coordenadas de la matriz
        }
    }
}

void llenar_submatriz(long long **matriz, long long **matriz_original, int iFilas, int iCol, int filas, int col)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matriz[i][j] = matriz_original[iFilas + i][iCol + j]; // Se asignan valores aleatorios a cada coordenadas de la matriz
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

// long long **multiplicacion_clasica(long long **matriz_1, long long **matriz_2, int filas_1, int filas_2, int col_1, int col_2)
// {
//     long long suma, **Matriz_resultado;
//     Matriz_resultado = asignar_matriz(filas_2, col_1);

//     for (int i = 0; i < filas_1; i++)
//     {
//         for (int j = 0; j < col_2; j++)
//         {
//             suma = 0;
//             for (int k = 0; k < col_1; k++)
//             {
//                 suma = SumaP(suma, MultP(matriz_1[i][k], matriz_2[k][j]));
//                 // Matriz_resultado[i][j] += matriz_1[i][k] * matriz_2[k][j];
//             }
//             Matriz_resultado[i][j] = SumaP(suma, Matriz_resultado[i][j]);
//         }
//     }
//     return Matriz_resultado;
// }

long long **multiplicacion_clasica(long long **matriz_1, long long **matriz_2, int filas_1, int filas_2, int col_1, int col_2)
{
    long long **Matriz_resultado;
    Matriz_resultado = asignar_matriz(filas_2, col_1);
    llenar_con_0(Matriz_resultado, filas_2, col_1);
    for (int i = 0; i < filas_1; i++)
    {
        for (int j = 0; j < col_2; j++)
        {
            for (int k = 0; k < col_1; k++)
            {
                Matriz_resultado[i][j] += matriz_1[i][k] * matriz_2[k][j];
            }
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
    long long **S1, **S2, **S3, **S4, **S5, **T1, **T2, **T3, **T4, **T5, **M1, **M2, **M3, **M4, **M5, **M6, **M7, **C11, **C12, **C21, **C22, **aux, **aux2;

    if (dim <= 2)
    {
        matrizResultado = asignar_matriz(2, 2);
        matrizResultado = multiplicacion_clasica(matriz_1, matriz_2, 2, 2, 2, 2); // transfromarla de void a long long
        return matrizResultado;
    }
    matriz_a11 = asignar_matriz(dim / 2, dim / 2);
    matriz_a12 = asignar_matriz(dim / 2, dim / 2);
    matriz_a21 = asignar_matriz(dim / 2, dim / 2);
    matriz_a22 = asignar_matriz(dim / 2, dim / 2);
    dividir_matriz(matriz_1, matriz_a11, matriz_a12, matriz_a21, matriz_a22, dim);

    matriz_b11 = asignar_matriz(dim / 2, dim / 2);
    matriz_b12 = asignar_matriz(dim / 2, dim / 2);
    matriz_b21 = asignar_matriz(dim / 2, dim / 2);
    matriz_b22 = asignar_matriz(dim / 2, dim / 2);
    dividir_matriz(matriz_2, matriz_b11, matriz_b12, matriz_b21, matriz_b22, dim);

    Mult_Strassen(matriz_a11, matriz_b11, dim / 2);
    Mult_Strassen(matriz_a12, matriz_b12, dim / 2);
    Mult_Strassen(matriz_a21, matriz_b21, dim / 2);
    Mult_Strassen(matriz_a22, matriz_b22, dim / 2);

    S1 = asignar_matriz(dim / 2, dim / 2);
    S2 = asignar_matriz(dim / 2, dim / 2);
    S3 = asignar_matriz(dim / 2, dim / 2);
    S4 = asignar_matriz(dim / 2, dim / 2);
    S5 = asignar_matriz(dim / 2, dim / 2);
    T1 = asignar_matriz(dim / 2, dim / 2);
    T2 = asignar_matriz(dim / 2, dim / 2);
    T3 = asignar_matriz(dim / 2, dim / 2);
    T4 = asignar_matriz(dim / 2, dim / 2);
    T5 = asignar_matriz(dim / 2, dim / 2);
    M1 = asignar_matriz(dim / 2, dim / 2);
    M2 = asignar_matriz(dim / 2, dim / 2);
    M3 = asignar_matriz(dim / 2, dim / 2);
    M4 = asignar_matriz(dim / 2, dim / 2);
    M5 = asignar_matriz(dim / 2, dim / 2);
    M6 = asignar_matriz(dim / 2, dim / 2);
    M7 = asignar_matriz(dim / 2, dim / 2);
    C11 = asignar_matriz(dim / 2, dim / 2);
    C12 = asignar_matriz(dim / 2, dim / 2);
    C21 = asignar_matriz(dim / 2, dim / 2);
    C22 = asignar_matriz(dim / 2, dim / 2);
    aux = asignar_matriz(dim / 2, dim / 2);
    aux2 = asignar_matriz(dim / 2, dim / 2);

    // Sumas de la matriz 1
    S1 = sumaMatrices(matriz_a11, matriz_a22, dim / 2, dim / 2);
    S2 = sumaMatrices(matriz_a21, matriz_a22, dim / 2, dim / 2);
    S3 = sumaMatrices(matriz_a11, matriz_a12, dim / 2, dim / 2);
    S4 = restaMatrices(matriz_a21, matriz_a11, dim / 2, dim / 2);
    S5 = restaMatrices(matriz_a12, matriz_a22, dim / 2, dim / 2);

    // Sumas de la matriz 2
    T1 = sumaMatrices(matriz_b11, matriz_b22, dim / 2, dim / 2);
    T2 = sumaMatrices(matriz_b21, matriz_b22, dim / 2, dim / 2);
    T3 = sumaMatrices(matriz_b11, matriz_b12, dim / 2, dim / 2);
    T4 = restaMatrices(matriz_b21, matriz_b11, dim / 2, dim / 2);
    T5 = restaMatrices(matriz_b12, matriz_b22, dim / 2, dim / 2);

    // Multiplicaciones de Strassen
    M1 = multiplicacion_clasica(S1, T1, dim / 2, dim / 2, dim / 2, dim / 2);
    M2 = multiplicacion_clasica(S2, matriz_b11, dim / 2, dim / 2, dim / 2, dim / 2);
    M3 = multiplicacion_clasica(matriz_a11, T5, dim / 2, dim / 2, dim / 2, dim / 2);
    M4 = multiplicacion_clasica(matriz_a22, T4, dim / 2, dim / 2, dim / 2, dim / 2);
    M5 = multiplicacion_clasica(S3, matriz_b22, dim / 2, dim / 2, dim / 2, dim / 2);
    M6 = multiplicacion_clasica(S4, T3, dim / 2, dim / 2, dim / 2, dim / 2);
    M7 = multiplicacion_clasica(S5, T2, dim / 2, dim / 2, dim / 2, dim / 2);

    // Recombinacion de Strassen
    aux = sumaMatrices(M1, M4, dim / 2, dim / 2);
    aux2 = restaMatrices(M7, M5, dim / 2, dim / 2);
    C11 = sumaMatrices(aux, aux2, dim / 2, dim / 2);
    C12 = sumaMatrices(M3, M5, dim / 2, dim / 2);
    C21 = sumaMatrices(M2, M4, dim / 2, dim / 2);
    aux = restaMatrices(M1, M2, dim / 2, dim / 2);
    aux2 = sumaMatrices(M3, M6, dim / 2, dim / 2);
    C22 = sumaMatrices(aux, aux2, dim / 2, dim / 2);

    matrizResultado = recombinarMatriz(C11, C12, C21, C22, dim);
    return matrizResultado; 
}

// long long **sumaMatrices(long long **matriz1, long long **matriz2, int filas, int columnas)
// {
//     long long **Mresultado;
//     Mresultado = asignar_matriz(filas, columnas);
//     for (int i = 0; i < filas; i++)
//     {
//         for (int j = 0; j < columnas; j++)
//         {
//             Mresultado[i][j] = matriz1[i][j] + matriz2[i][j];
//         }
//     }
//     return Mresultado;
// }

long long **sumaMatrices(long long **matriz1, long long **matriz2, int filas, int columnas)
{
    long long **matrizResultado;
    matrizResultado = asignar_matriz(filas, columnas);
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            matrizResultado[i][j] = matriz1[i][j] + matriz2[i][j];
        }
    }
    return matrizResultado;
}

// long long **restaMatrices(long long **matriz1, long long **matriz2, int filas, int columnas)
// {
//     long long resta = 0, **matrizResultado;
//     matrizResultado = asignar_matriz(filas, columnas);
//     for (int i = 0; i < filas; i++)
//     {
//         for (int j = 0; j < columnas; j++)
//         {
//             resta = RestaP(matriz1[i][j], matriz2[i][j]);
//             matrizResultado[i][j] = matrizResultado[i][j];
//             printf("\nMatriz : %lld ", matrizResultado[i][j]);
//         }
//     }
//     return matrizResultado;
// }

long long **restaMatrices(long long **matriz1, long long **matriz2, int filas, int columnas)
{
    long long **matrizResultado;
    matrizResultado = asignar_matriz(filas, columnas);
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            matrizResultado[i][j] = matriz1[i][j] - matriz2[i][j];
        }
    }
    return matrizResultado;
}

long long **recombinarMatriz(long long **C11, long long **C12, long long **C21, long long **C22, int dim)
{
    long long **matrizResultado;
    int val;
    val = dim / 2;
    matrizResultado = asignar_matriz(dim, dim);
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (i < dim / 2 && j < dim / 2)
            {
                matrizResultado[i][j] = C11[i][j];
            }
            else if (i < dim / 2 && j >= dim / 2)
            {
                matrizResultado[i][j] = C12[i][j - val];
            }
            else if (i >= dim / 2 && j < dim / 2)
            {
                matrizResultado[i][j] = C21[i - val][j];
            }
            else
            {
                matrizResultado[i][j] = C22[i - val][j - val];
            }
        }
    }
    return matrizResultado;
}

long long** matriz_par(long long **matriz, int filas, int columnas)
{
    long long **matriz_par;
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            // *averiguando si es legal(no estoy seguro si se ponerlo aqui o en el otro for *
            if (powerOfTwo(filas)==0 &&powerOfTwo(columnas)==0)
            {
              matriz_par[filas+1][j]  = (long long **)calloc(filas, sizeof(long long)); 
            }
        }
    }
}

int powerOfTwo(int n)
    {
        if(n==0) { return 0; }
        while(n != 1)
        {
            n = n/2;
            if(n%2 != 0 && n != 1){ return 0; }
        }
        return 1;
    }
    

void dividir_matriz(long long **matrizO, long long **matriz_11, long long **matriz_12, long long **matriz_21, long long **matriz_22, int dim)
{
    llenar_submatriz(matriz_11, matrizO, 0, 0, dim / 2, dim / 2);
    llenar_submatriz(matriz_12, matrizO, 0, dim / 2, dim / 2, dim / 2);
    llenar_submatriz(matriz_21, matrizO, dim / 2, 0, dim / 2, dim / 2);
    llenar_submatriz(matriz_22, matrizO, dim / 2, dim / 2, dim / 2, dim / 2);
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