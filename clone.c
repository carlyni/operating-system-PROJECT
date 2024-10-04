#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

// Tamanho da pilha para o clone
#define STACK_SIZE (1024 * 1024)

// Variável global para testar o compartilhamento de memória
int var_compartilhada = 0;

// Função para calcular o tempo decorrido usando gettimeofday()
double calcular_tempo(struct timeval inicio, struct timeval fim) {
    return (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000000.0;
}

// Função que será executada pelo processo filho
int funcao_clone(void *arg) {
    struct timeval inicio, fim;
    clock_t inicio_clock, fim_clock;

    // Início da medição de tempo
    gettimeofday(&inicio, NULL);
    inicio_clock = clock();

    printf("Processo filho: PID %d, var_compartilhada = %d\n", getpid(), var_compartilhada);
    var_compartilhada += 10;  // Modifica a variável compartilhada
    printf("Processo filho: var_compartilhada modificada para %d\n", var_compartilhada);

    // Fim da medição de tempo
    gettimeofday(&fim, NULL);
    fim_clock = clock();

    // Exibe o tempo decorrido
    printf("Processo filho: Tempo de execução (gettimeofday) = %f segundos\n", calcular_tempo(inicio, fim));
    printf("Processo filho: Tempo de execução (clock) = %f segundos\n", (double)(fim_clock - inicio_clock) / CLOCKS_PER_SEC);

    return 0;
}

void teste_clone_compartilhamento_memoria() {
    struct timeval inicio, fim;
    clock_t inicio_clock, fim_clock;

    // Alocação de stack para o clone
    char *stack = (char *)malloc(STACK_SIZE);
    if (!stack) {
        perror("Erro ao alocar stack");
        exit(1);
    }

    // Flags para o clone: CLONE_VM para compartilhar o espaço de memória
    int flags = CLONE_VM | SIGCHLD;

    printf("Processo pai: PID %d, var_compartilhada = %d\n", getpid(), var_compartilhada);

    // Início da medição de tempo no processo pai
    gettimeofday(&inicio, NULL);
    inicio_clock = clock();

    // Cria o processo filho com clone()
    int pid = clone(funcao_clone, stack + STACK_SIZE, flags, NULL);

    if (pid == -1) {
        perror("Erro no clone()");
        free(stack);
        exit(1);
    }

    // Espera o processo filho terminar
    wait(NULL);

    // Fim da medição de tempo no processo pai
    gettimeofday(&fim, NULL);
    fim_clock = clock();

    // O processo pai verifica se a variável compartilhada foi modificada
    printf("Processo pai: var_compartilhada após o filho = %d\n", var_compartilhada);

    // Exibe o tempo decorrido no processo pai
    printf("Processo pai: Tempo total de execução (gettimeofday) = %f segundos\n", calcular_tempo(inicio, fim));
    printf("Processo pai: Tempo total de execução (clock) = %f segundos\n", (double)(fim_clock - inicio_clock) / CLOCKS_PER_SEC);

    // Libera a memória da stack
    free(stack);
}

int main() {
    printf("Testando clone com compartilhamento de memória...\n");
    teste_clone_compartilhamento_memoria();
    return 0;
}
