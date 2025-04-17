#include <stdio.h>
#include <semaphore.h>  // semáforos
#include <pthread.h>    // hilos
#include <unistd.h>     // sleep

// Declaración semáforos
sem_t semA, semB;

// Declaración de variables globales
int count_B = 0; 

void esperar_enfriar() {
    printf("Esperando a que la fotocopiadora B se enfríe...\n");
    sleep(5); // Simula el tiempo de enfriamiento
    printf("Fotocopiadora B se ha enfriado.\n");
}

void* usar_fotocopiadora(void* arg) {
    char tipo = *(char*)arg; // Tipo de fotocopiadora (A o B)

    for (int i = 0; i < 5; i++) {
        if (tipo == 'A') {
            sem_wait(&semA); // Espera al semáforo A
            printf("Dino usa fotocopiador Tipo: A\n");
            sleep(3); // Simula el uso de la fotocopiadora A
            sem_post(&semB); // Libera el semáforo B
        } else if (tipo == 'B') {
            sem_wait(&semB); // Espera al semáforo B
            count_B++;
            printf("Dino usa fotocopiador Tipo: B\n");
            sleep(3); // Simula el uso de la fotocopiadora B

            if (count_B == 2) {
                esperar_enfriar(); // Enfría la fotocopiadora después de 2 usos
            } else if (count_B > 2) {
                printf("Se ha usado la fotocopiadora B más de 3 veces. Cambiando a Tipo A.\n");
                sem_post(&semA); // Libera el semáforo A para cambiar a Tipo A
                count_B = 0; // Reinicia el contador de B después de imprimir
            } else {
                sem_post(&semB); // Libera el semáforo B para continuar con Tipo B
            }
        }
    }

    pthread_exit(NULL);
}

void colocar_trabajo_en_bandeja() {
    printf("Colocando trabajo en la bandeja...\n");
    sleep(2); // Simula el tiempo de colocación del trabajo

    // Decidir qué tipo de fotocopiadora usar
    if (count_B >= 2) {
        printf("Decidiendo usar fotocopiadora Tipo: A\n");
        sem_post(&semA); // Libera el semáforo A para usar la fotocopiadora A
    } else {
        printf("Decidiendo usar fotocopiadora Tipo: B\n");
        sem_post(&semB); // Libera el semáforo B para usar la fotocopiadora B
    }
}

int main() {
    pthread_t tpid_A, tpid_B;
    char tipoA = 'A'; // Tipo de fotocopiadora A
    char tipoB = 'B'; // Tipo de fotocopiadora B

    // Inicialización de los semáforos
    sem_init(&semA, 0, 1); // Inicializa semáforo A en 1 (activo)
    sem_init(&semB, 0, 0); // Inicializa semáforo B en 0 (bloqueado)

    // Creación de los hilos
    pthread_create(&tpid_A, NULL, usar_fotocopiadora, &tipoA);
    pthread_create(&tpid_B, NULL, usar_fotocopiadora, &tipoB);

    // Simula la colocación de trabajos en la bandeja
    for (int i = 0; i < 5; i++) {
        colocar_trabajo_en_bandeja();
    }

    // Espera a que los hilos terminen
    pthread_join(tpid_A, NULL);
    pthread_join(tpid_B, NULL);

    // Destruye los semáforos
    sem_destroy(&semA);
    sem_destroy(&semB);

    printf("\n"); // Salto de línea final
    return 0;
}