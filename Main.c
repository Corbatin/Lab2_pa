// Nombres: Alvaro Soto Albornoz - Benjamín Melis Guerra
// Nombre Profesora: Nicolas Thériault
// IDE: Visual Studio Code 1.62.3
// SO: Windows 10
// Fecha: 21 de Diciembre - 2021
// Este programa genera dos matrices de un orden dado por el usuario y realiza multiplicaciones con dos algoritmos distintos, el algoritmo clasico y la multiplicacion de Strassen


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
void imprimir_matriz(long long **array, int filas, int columnas);                                                               // Funcion que imprime la matriz
void menu();                                                                                                                    // Menu para desplazarse entre las funciones del programa
long long **sumaMatrices(long long **matriz1, long long **matriz2, int filas, int columnas);                                    // Suma de Matrices
long long **restaMatrices(long long **matriz1, long long **matriz2, int filas, int columnas);                                   // Resta de matrices
long long **multiplicacion_clasica(long long **matriz_1, long long **matriz_2, int filas_1, int filas_2, int col_1, int col_2); // Multiplicacion de matrices de forma clasica
long long **Mult_Strassen(long long **matriz_1, long long **matriz_2, int dim);                                                 // Multiplicacion de matrices con el algoritmo de Strassen
long long **recombinarMatriz(long long **C11, long long **C12, long long **C21, long long **C22, int dim);                      // Funcion que recombina las 4 sub matrices en la matriz mas grande
long long **matriz_par(long long **matriz, int *dim); // Funcion que aumenta a un numero par las dimensiones de una matriz de orden impar

// ########### Funciones Profesor #######//
long long MultP(long long a, long long b);
long long RestaP(long long a, long long b);
long long SumaP(long long a, long long b);

int main()
{
    srand(time(0)); // metodo para generar numeros aleatorios
    menu();
    return 0;
}

void menu()
{
    int opcion, filas, columnas, el, filas_2, columnas_2; // Variables de dimension y de eleccion
    long long **Matriz_1, **Matriz_2, **Matriz_resultado; // Definicion de matrices
    clock_t tiempo1, tiempo2, tiempo3, tiempo4;           // Variables para tomar tiempos
    float tiempoClasica, tiempoStrassen;

    printf("\nEscoga la cantidad de filas de la matriz 1: ");
    scanf("%i", &filas);
    printf("\nEscoga la cantidad de columnas de la matriz 1: ");
    scanf("%i", &columnas);

    printf("\nEscoga la cantidad de filas de la matriz 2: ");
    scanf("%i", &filas_2);
    printf("\nEscoga la cantidad de columnas de la matriz 2: ");
    scanf("%i", &columnas_2);

    Matriz_1 = asignar_matriz(filas, columnas); // Se llena la matriz 1 con valores aleatorios
    llenar_matriz(Matriz_1, filas, columnas);
    Matriz_2 = asignar_matriz(filas_2, columnas_2); // Se llena la matriz 2 con valores aleatorios
    llenar_matriz(Matriz_2, filas_2, columnas_2);

    Matriz_resultado = asignar_matriz(filas_2, columnas);

    do
    {
        printf("\nQue desea ver?");
        printf("\n 1) Generar Nueva matriz 1. ");
        printf("\n 2) Generar Nueva matriz 2. ");
        printf("\n 3) Multiplicacion Matrices clasica.");
        printf("\n 4) Multiplicacion Matrices por Strassen.(solo valido para matrices cuadradas)");
        printf("\n 5) Comparar tiempos entre las dos multiplicaciones.(solo valido para matrices cuadradas)");
        printf("\n 0) Salir del programa.");
        scanf("%i", &opcion);
        switch (opcion)
        {
        case 1:
            for (int i = 0; i < filas; i++)
            {
                free(Matriz_1[i]);
            }
            free(Matriz_1);
            printf("\nEscoga la cantidad de filas de la matriz 1: ");
            scanf("%i", &filas);
            printf("\nEscoga la cantidad de columnas de la matriz 1: ");
            scanf("%i", &columnas);
            Matriz_1 = asignar_matriz(filas, columnas);
            llenar_matriz(Matriz_1, filas, columnas);
            break;
        case 2:
            for (int i = 0; i < filas_2; i++)
            {
                free(Matriz_2[i]);
            }
            free(Matriz_2);
            printf("\nEscoga la cantidad de filas de la matriz 2: ");
            scanf("%i", &filas_2);
            printf("\nEscoga la cantidad de columnas de la matriz 2: ");
            scanf("%i", &columnas_2);
            Matriz_2 = asignar_matriz(filas_2, columnas_2);
            llenar_matriz(Matriz_2, filas_2, columnas_2);
            break;
        case 3:
            if (filas != columnas_2) // Comprueba que las filas de 1 sean igual a las columnas de 2
            {
                printf("\nDimensiones incorrectas, no se puede realizar multiplicacion\n ");
                break;
            }
            else
            {
                printf("\nCalculando . . .\n");
                tiempo1 = clock();
                Matriz_resultado = multiplicacion_clasica(Matriz_1, Matriz_2, filas, filas, columnas, columnas);
                tiempo2 = clock();
                printf("\nDesea ver las matrices?\n");
                printf("\n1) Si\n");
                printf("\n2) No\n");
                scanf("%i", &el);
                if (el == 1)
                {

                    printf("\nMatriz 1: \n");
                    imprimir_matriz(Matriz_1, filas, columnas);
                    printf("\nMatriz 2: \n");
                    imprimir_matriz(Matriz_2, filas_2, columnas_2);
                    printf("\nMatriz Resultado: \n");
                    imprimir_matriz(Matriz_resultado, filas_2, columnas);
                }

                printf("\nTiempo de ejecucion: %f\n", ((double)tiempo2 - (double)tiempo1) / ((double)CLOCKS_PER_SEC));
            }
            break;
        case 4:
            if (filas == columnas && filas_2 == columnas_2 && filas == filas_2 && columnas == columnas_2) // Se pregunta si ambas matrices tienen las mismas dimensiones
            {
                printf("\nCalculando . . .\n");
                tiempo1 = clock();
                Matriz_resultado = Mult_Strassen(Matriz_1, Matriz_2, filas);
                tiempo2 = clock();
                printf("\nDesea ver las matrices?\n");
                printf("\n1) Si\n");
                printf("\n2) No\n");
                scanf("%i", &el);
                if (el == 1)
                {
                    printf("\nMatriz 1: \n");
                    imprimir_matriz(Matriz_1, filas, columnas);
                    printf("\nMatriz 2: \n");
                    imprimir_matriz(Matriz_2, filas_2, columnas_2);
                    printf("\nMatriz Resultado: \n");
                    imprimir_matriz(Matriz_resultado, filas_2, columnas);
                    printf("\n\nTiempo de ejecucion: %f\n", ((double)tiempo2 - (double)tiempo1) / ((double)CLOCKS_PER_SEC));
                    break;
                }
                else
                {
                    printf("\n\nTiempo de ejecucion: %f\n", ((double)tiempo2 - (double)tiempo1) / ((double)CLOCKS_PER_SEC));
                    break;
                }
            }
            else
            {
                printf("\nMatrices no aptas para multiplicar por metodo de strassen. Por favor ingrese matrices cuadradas. \n");
                break;
            }
            printf("\nTiempo de ejecucion: %f\n", ((double)tiempo2 - (double)tiempo1) / ((double)CLOCKS_PER_SEC));
            break;
        case 5:
            if (filas == columnas && filas_2 == columnas_2 && filas == filas_2 && columnas == columnas_2) // Se pregunta si ambas matrices tienen las mismas dimensiones
            {
                tiempo1 = clock();
                multiplicacion_clasica(Matriz_1, Matriz_2, filas, filas_2, columnas, columnas_2);
                tiempo2 = clock();
                printf("\n\nTiempo de ejecucion Multiplicacion Clasica : %f\n", ((double)tiempo2 - (double)tiempo1) / ((double)CLOCKS_PER_SEC));
                tiempo3 = clock();
                Mult_Strassen(Matriz_1, Matriz_2, filas);
                tiempo4 = clock();
                printf("\n\nTiempo de ejecucion Strassen: %f\n", ((double)tiempo4 - (double)tiempo3) / ((double)CLOCKS_PER_SEC));
                tiempoClasica = ((double)tiempo2 - (double)tiempo1) / ((double)CLOCKS_PER_SEC);
                tiempoStrassen = ((double)tiempo4 - (double)tiempo3) / ((double)CLOCKS_PER_SEC);
                if (tiempoClasica > tiempoStrassen)
                {
                    printf("\nLa multiplicacion de Strassen demoro menos que la multiplicacion clasica.\n");
                }
                else
                {
                    printf("\nLa multiplicacion clasica demoro menos que la multiplicacion de Strassen.\n");
                }
            }
            else
            {
                printf("\nLas matrices entregadas no son cuadradas.\n");
            }
            break;
        case 0:
            printf("\nPrograma terminado ......");
            break;
        default:
            printf("\nOpcion invalida , por favor seleccione otra .....\n");
            break;
        }
    } while (opcion);
    if (columnas > filas) // Liberar matriz 1
        filas = columnas;
    for (int i = 0; i < filas; i++)
    {
        free(Matriz_1[i]);
    }
    free(Matriz_1);

    if (columnas_2 > filas_2) // Liberar matriz 2
        filas_2 = columnas_2;
    for (int i = 0; i < filas_2; i++)
    {
        free(Matriz_2[i]);
    }
    free(Matriz_2);

    if (columnas > filas_2) // Liberar matriz resultado
        filas_2 = columnas;
    for (int i = 0; i < filas_2; i++)
    {
        free(Matriz_resultado[i]);
    }
    free(Matriz_resultado);
}

long long **asignar_matriz(int n, int m)
{
    int i, j;
    long long **array;
    array = (long long **)calloc(n, sizeof(long long *)); // se reserva memoria  para la matriz de x filas que contiene direcciones de memoria a las segundas dimensiones.
    for (i = 0; i < n; i++)
    {
        array[i] = (long long *)calloc(m, sizeof(long long)); // se reserva memoria para las segundas dimensiones , x columnas
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
            }
            Matriz_resultado[i][j] = SumaP(suma, Matriz_resultado[i][j]);
        }
    }
    return Matriz_resultado;
}

long long **Mult_Strassen(long long **matriz_1, long long **matriz_2, int dim)
{
    long long **matriz_a11, **matriz_a12, **matriz_a21, **matriz_a22;
    long long **matriz_b11, **matriz_b12, **matriz_b21, **matriz_b22;
    long long **matrizResultado;
    long long **S1, **S2, **S3, **S4, **S5, **T1, **T2, **T3, **T4, **T5, **M1, **M2, **M3, **M4, **M5, **M6, **M7, **C11, **C12, **C21, **C22, **aux, **aux2;
    int dim2, largo;

    if (dim <= 40)
    {
        matrizResultado = multiplicacion_clasica(matriz_1, matriz_2, dim, dim, dim, dim);
        return matrizResultado;
    }
    // Comprobar que la dimension de las matrices sea par
    dim2 = dim;
    matriz_1 = matriz_par(matriz_1, &dim);
    matriz_2 = matriz_par(matriz_2, &dim2);

    largo = dim / 2;

    // PASO 1: SUBMATRICES
    // Sub division de matrizes original en 4 submatrices cada una
    matriz_a11 = asignar_matriz(dim / 2, dim / 2);
    matriz_a12 = asignar_matriz(dim / 2, dim / 2);
    matriz_a21 = asignar_matriz(dim / 2, dim / 2);
    matriz_a22 = asignar_matriz(dim / 2, dim / 2);

    matriz_b11 = asignar_matriz(dim / 2, dim / 2);
    matriz_b12 = asignar_matriz(dim / 2, dim / 2);
    matriz_b21 = asignar_matriz(dim / 2, dim / 2);
    matriz_b22 = asignar_matriz(dim / 2, dim / 2);

    for (int i = 0; i < largo; i++)
    {
        for (int j = 0; j < largo; j++)
        {
            matriz_a11[i][j] = matriz_1[i][j];
            matriz_a12[i][j] = matriz_1[i][j + largo];
            matriz_a21[i][j] = matriz_1[i + largo][j];
            matriz_a22[i][j] = matriz_1[i + largo][j + largo];

            matriz_b11[i][j] = matriz_2[i][j];
            matriz_b12[i][j] = matriz_2[i][j + largo];
            matriz_b21[i][j] = matriz_2[i + largo][j];
            matriz_b22[i][j] = matriz_2[i + largo][j + largo];
        }
    }

    // Sumas de la matriz 1
    // Primer paso de suma de matrices de Strassen
    S1 = sumaMatrices(matriz_a11, matriz_a22, dim / 2, dim / 2);
    S2 = sumaMatrices(matriz_a21, matriz_a22, dim / 2, dim / 2);
    S3 = sumaMatrices(matriz_a11, matriz_a12, dim / 2, dim / 2);
    S4 = restaMatrices(matriz_a21, matriz_a11, dim / 2, dim / 2);
    S5 = restaMatrices(matriz_a12, matriz_a22, dim / 2, dim / 2);

    // Sumas de la matriz 2
    // Segundo paso de suma de matrices de Strassen
    T1 = sumaMatrices(matriz_b11, matriz_b22, dim / 2, dim / 2);
    T2 = sumaMatrices(matriz_b21, matriz_b22, dim / 2, dim / 2);
    T3 = sumaMatrices(matriz_b11, matriz_b12, dim / 2, dim / 2);
    T4 = restaMatrices(matriz_b21, matriz_b11, dim / 2, dim / 2);
    T5 = restaMatrices(matriz_b12, matriz_b22, dim / 2, dim / 2);

    // Multiplicaciones de Strassen
    M1 = Mult_Strassen(S1,T1,dim / 2);
    M2 = Mult_Strassen(S2, matriz_b11, dim / 2);
    M3 = Mult_Strassen(matriz_a11, T5, dim / 2);
    M4 = Mult_Strassen(matriz_a22, T4, dim / 2);
    M5 = Mult_Strassen(S3, matriz_b22, dim / 2);
    M6 = Mult_Strassen(S4, T3, dim / 2);
    M7 = Mult_Strassen(S5, T2, dim / 2);

    // Recombinacion de Strassen
    aux = sumaMatrices(M1, M4, dim / 2, dim / 2);
    aux2 = restaMatrices(M7, M5, dim / 2, dim / 2);
    C11 = sumaMatrices(aux, aux2, dim / 2, dim / 2);
    C12 = sumaMatrices(M3, M5, dim / 2, dim / 2);
    C21 = sumaMatrices(M2, M4, dim / 2, dim / 2);
    aux = restaMatrices(M1, M2, dim / 2, dim / 2);
    aux2 = sumaMatrices(M3, M6, dim / 2, dim / 2);
    C22 = sumaMatrices(aux, aux2, dim / 2, dim / 2);

    // Recombinacion de matrices en la matriz resultado
    matrizResultado = recombinarMatriz(C11, C12, C21, C22, dim);
    return matrizResultado;
}

long long **sumaMatrices(long long **matriz1, long long **matriz2, int filas, int columnas)
{
    long long **Mresultado;
    Mresultado = asignar_matriz(filas, columnas);
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            Mresultado[i][j] = SumaP(matriz1[i][j], matriz2[i][j]);
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
            matrizResultado[i][j] = RestaP(matriz1[i][j], matriz2[i][j]);
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
                // asigna los valores de la submatriz M11 a la matriz resultado
                matrizResultado[i][j] = C11[i][j];
            }
            else if (i < dim / 2 && j >= dim / 2)
            {
                // asigna los valores de la submatriz M12 a la matriz resultado
                matrizResultado[i][j] = C12[i][j - val];
            }
            else if (i >= dim / 2 && j < dim / 2)
            {
                // asigna los valores de la submatriz M21 a la matriz resultado
                matrizResultado[i][j] = C21[i - val][j];
            }
            else
            {
                // asigna los valores de la submatriz M22 a la matriz resultado
                matrizResultado[i][j] = C22[i - val][j - val];
            }
        }
    }
    return matrizResultado;
}

long long **matriz_par(long long **matriz, int *dim)
{
    long long **matriz_par;
    int Dim;
    Dim = *dim;
    if (Dim % 2 != 0) // Comprueba si la matriz tiene dimension par
    {
        matriz_par = asignar_matriz(Dim + 1, Dim + 1);        // Asigna la memoria para dejar la matriz con dimension par
        llenar_submatriz(matriz_par, matriz, 0, 0, Dim, Dim); // Rellena la matriz nueva con los valores de la original
        Dim++;
        *dim = Dim;        // Actualiza la dimension de la matriz
        return matriz_par; // Devuelve la matriz con la dimension par
    }
    else
        return matriz; // Devuelve la matriz orginal
}

// Funciones entregadas para los calculos en mod p.

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
