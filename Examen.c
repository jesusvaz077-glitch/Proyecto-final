    #include <stdio.h>

#define MAX_OYENTES   100
#define NUM_CANCIONES 10

int esVotoValido(int primera, int segunda, int tercera);
void limpiarEntrada(void);
int leerVotos(int votos[][3]);
void calcularPuntosCanciones(int votos[][3], int numOyentes, int puntosCanciones[]);
void encontrarGanadoras(int puntosCanciones[], int *primera, int *segunda);
void calcularPuntosOyentes(int votos[][3], int numOyentes, int primera, int segunda, int puntosOyentes[]);
int encontrarGanador(int puntosOyentes[], int numOyentes);

int esVotoValido(int primera, int segunda, int tercera) {
    if (primera < 0 || primera >= NUM_CANCIONES ||
        segunda < 0 || segunda >= NUM_CANCIONES ||
        tercera < 0 || tercera >= NUM_CANCIONES) {
        return 0;
    }
    if (primera == segunda || primera == tercera || segunda == tercera) {
        return 0;
    }
    return 1;
}

void limpiarEntrada(void) {
    int caracter;
    while ((caracter = getchar()) != '\n' && caracter != EOF) {
    }
}

int leerVotos(int votos[][3]) {
    int numOyentes = 0;
    int a, b, c;
    int lectura;

    printf("Ingresa los votos (trio de canciones, -1 para terminar):\n");

    while (numOyentes < MAX_OYENTES) {
        printf("Oyente %d: ", numOyentes);
        lectura = scanf("%d", &a);

        if (lectura == EOF) break;

        if (lectura != 1) {
            printf("Entrada invalida. Intente de nuevo.\n");
            limpiarEntrada();
            continue;
        }

        if (a == -1) break;

        lectura = scanf("%d %d", &b, &c);

        if (lectura == EOF) break;

        if (lectura != 2) {
            printf("Entrada incompleta. Intente de nuevo.\n");
            limpiarEntrada();
            continue;
        }

        if (!esVotoValido(a, b, c)) {
            printf("Voto invalido. Use canciones del 0 al 9 y no repita canciones.\n");
            continue;
        }

        votos[numOyentes][0] = a;
        votos[numOyentes][1] = b;
        votos[numOyentes][2] = c;
        numOyentes++;
    }

    return numOyentes;
}

void calcularPuntosCanciones(int votos[][3], int numOyentes, int puntosCanciones[]) {
    int i;

    for (i = 0; i < NUM_CANCIONES; i++) {
        puntosCanciones[i] = 0;
    }

    for (i = 0; i < numOyentes; i++) {
        puntosCanciones[votos[i][0]] += 3;
        puntosCanciones[votos[i][1]] += 2;
        puntosCanciones[votos[i][2]] += 1;
    }
}

void encontrarGanadoras(int puntosCanciones[], int *primera, int *segunda) {
    int i;

    *primera = 0;
    *segunda = 1;

    if (puntosCanciones[1] > puntosCanciones[0]) {
        *primera = 1;
        *segunda = 0;
    }

    for (i = 2; i < NUM_CANCIONES; i++) {
        if (puntosCanciones[i] > puntosCanciones[*primera]) {
            *segunda = *primera;
            *primera = i;
        } else if (puntosCanciones[i] > puntosCanciones[*segunda]) {
            *segunda = i;
        }
    }
}

void calcularPuntosOyentes(int votos[][3], int numOyentes, int primera, int segunda, int puntosOyentes[]) {
    int i, j;
    int tienePrimera, tieneSegunda;

    for (i = 0; i < numOyentes; i++) {
        puntosOyentes[i] = 0;
        tienePrimera = 0;
        tieneSegunda = 0;

        for (j = 0; j < 3; j++) {
            if (votos[i][j] == primera) tienePrimera = 1;
            if (votos[i][j] == segunda) tieneSegunda = 1;
        }

        if (tienePrimera) puntosOyentes[i] += 30;
        if (tieneSegunda) puntosOyentes[i] += 20;
        if (tienePrimera && tieneSegunda) puntosOyentes[i] += 10;
    }
}

int encontrarGanador(int puntosOyentes[], int numOyentes) {
    int i;
    int ganador = 0;

    for (i = 1; i < numOyentes; i++) {
        if (puntosOyentes[i] > puntosOyentes[ganador]) {
            ganador = i;
        }
    }

    return ganador;
}

int main() {
    int votos[MAX_OYENTES][3];
    int puntosCanciones[NUM_CANCIONES];
    int puntosOyentes[MAX_OYENTES];
    int primera, segunda;
    int numOyentes;
    int ganador;
    int i;

    numOyentes = leerVotos(votos);

    if (numOyentes == 0) {
        printf("No participaron oyentes.\n");
        return 0;
    }

    calcularPuntosCanciones(votos, numOyentes, puntosCanciones);
    encontrarGanadoras(puntosCanciones, &primera, &segunda);
    calcularPuntosOyentes(votos, numOyentes, primera, segunda, puntosOyentes);
    ganador = encontrarGanador(puntosOyentes, numOyentes);

    printf("\n--- Votos por cancion ---\n");
    for (i = 0; i < NUM_CANCIONES; i++) {
        printf("Cancion %d: %d votos\n", i, puntosCanciones[i]);
    }

    printf("\n1a cancion mas votada: %d\n", primera);
    printf("2a cancion mas votada: %d\n", segunda);

    printf("\n--- Puntos por oyente ---\n");
    for (i = 0; i < numOyentes; i++) {
        printf("Oyente %d: %d puntos\n", i, puntosOyentes[i]);
    }

    printf("\nGanador: el oyente numero %d\n", ganador);

    return 0;
}

    
