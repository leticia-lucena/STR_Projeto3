//////////////////////////////////////////////////////////////////////////////////////////////////
//            Aluna: Leticia Rebecca Medeiros de Lucena                                         //
//            Disciplina: Sistemas em Tempo Real                                                //
//            Projeto 3 - 2023.2                                                                //
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_TRENS 5 // Quantidade de trens gerada
#define NUM_CARROS 10 // Quantidade de carros gerada

// Direção do trem no cruzamento
#define LESTE_OESTE 0
#define OESTE_LESTE 1

// Direção do carro no cruzamento
#define NORTE 0
#define SUL 1

// Criação da struct com informações de direção do trem
typedef struct {
    pthread_t thread;
    int direcao;
} Trem;

// Criação da struct com informações de direção do carro
typedef struct {
    pthread_t thread;
    int direcao;
} Carro;

sem_t semaforo_cruzamento;
sem_t semaforo_cancela;
int cruzamento_ocupado = 0; // Indicação de estado do cruzamento: 0 = livre, 1 = ocupado por trem, 2 = ocupado por carro

// Função do fluxo de trens no cruzamento
void *funcao_fluxo_trem(void *arg) {
    Trem *trem = (Trem *)arg;

    printf("Trem se aproximando do cruzamento no sentido %s.\n", trem->direcao == LESTE_OESTE ? "leste-oeste" : "oeste-leste");

    sem_wait(&semaforo_cancela);
    sem_wait(&semaforo_cruzamento);

    printf("Trem cruzando o cruzamento no sentido %s.\n", trem->direcao == LESTE_OESTE ? "leste-oeste" : "oeste-leste");
    cruzamento_ocupado = 1;
    sleep(1); // Simulação de cruzamento
    cruzamento_ocupado = 0;

    sem_post(&semaforo_cruzamento);
    sem_post(&semaforo_cancela);

    printf("Trem passou pelo cruzamento.\n");

    pthread_exit(NULL);
}

// Função do fluxo de carros no cruzamento
void *funcao_fluxo_carro(void *arg) {
    Carro *carro = (Carro *)arg;

    printf("Carro se aproximando do cruzamento no sentido %s.\n", carro->direcao == NORTE ? "norte" : "sul");

    sem_wait(&semaforo_cancela);
    sem_wait(&semaforo_cruzamento);

    printf("Carro cruzando o cruzamento no sentido %s.\n", carro->direcao == NORTE ? "norte" : "sul");
    cruzamento_ocupado = 2;
    sleep(1); // Simulação de cruzamento
    cruzamento_ocupado = 0;

    sem_post(&semaforo_cruzamento);
    sem_post(&semaforo_cancela);

    printf("Carro passou pelo cruzamento.\n");

    pthread_exit(NULL);
}

// Função para atualizar o estado do cruzamento e do semáforo
void *funcao_estado_cruzamento(void *arg) {
    while (1) {
        if (cruzamento_ocupado == 0) {
            printf("Cruzamento livre. Semáforo: Verde.\n");
        } else if (cruzamento_ocupado == 1) {
            printf("Cruzamento ocupado por um trem. Semáforo: Vermelho.\n");
        } else if (cruzamento_ocupado == 2) {
            printf("Cruzamento ocupado por um carro. Semáforo: Verde.\n");
        }
        sleep(2); // Verificação a cada 2 segundos
    }
}


int main() {

    // Inicialização dos semáforos
    sem_init(&semaforo_cruzamento, 0, 1);
    sem_init(&semaforo_cancela, 0, 1);

    // Criação da thread para monitorar o estado do cruzamento
    pthread_t thread_estado_cruzamento;
    pthread_create(&thread_estado_cruzamento, NULL, funcao_estado_cruzamento, NULL);

    // Geração e inicialização dos trens
    Trem trens[NUM_TRENS];
    for (int i = 0; i < NUM_TRENS; i++) {
        int direcao_aleatoria = rand() % 2; // 0 = leste-oeste, 1 = oeste-leste

        trens[i].direcao = direcao_aleatoria;

        pthread_create(&trens[i].thread, NULL, funcao_fluxo_trem, (void *)&trens[i]);
        sleep(rand() % 3); // Intervalo aleatório para a chegada de um novo trem (entre 0 e 2seg)
    }

    // Geração e inicialização dos carros
    Carro carros[NUM_CARROS];
    for (int i = 0; i < NUM_CARROS; i++) {
        int direcao_aleatoria = rand() % 2; // 0 = norte, 1 = sul

        carros[i].direcao = direcao_aleatoria;

        pthread_create(&carros[i].thread, NULL, funcao_fluxo_carro, (void *)&carros[i]);
        sleep(rand() % 3); // Intervalo aleatório para a chegada de um novo carro (entre 0 e 2seg)
    }

    // Espera a criação das threads dos trens terminar
    for (int i = 0; i < NUM_TRENS; i++) {
        pthread_join(trens[i].thread, NULL);
    }

    // Espera a criação das threads dos carros terminar
    for (int i = 0; i < NUM_CARROS; i++) {
        pthread_join(carros[i].thread, NULL);
    }

    return 0;
}
