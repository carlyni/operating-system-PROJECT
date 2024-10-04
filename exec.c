#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

// Função para medir o tempo de parede
double calcular_tempo(struct timeval inicio, struct timeval fim) {
    return (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000000.0;
}

// Função para medir o tempo de CPU
double calcular_tempo_cpu(clock_t inicio, clock_t fim) {
    return ((double) (fim - inicio)) / CLOCKS_PER_SEC;
}

void teste_exec() {
    // Medição de tempo de parede
    struct timeval inicio_parede, fim_parede;
    gettimeofday(&inicio_parede, NULL);

    // Medição de tempo de CPU
    clock_t inicio_cpu, fim_cpu;
    inicio_cpu = clock();

    pid_t pid = fork();
    if (pid == 0) {
        // Processo filho
        execlp("/bin/ls", "ls", NULL);  // Substitui o processo por 'ls'
        perror("Erro no exec()");
        exit(1);
    } else {
        // Processo pai
        wait(NULL);
        gettimeofday(&fim_parede, NULL);
        fim_cpu = clock();

        // Exibe os tempos
        printf("Tempo de execução (exec) - tempo de parede: %f segundos\n", calcular_tempo(inicio_parede, fim_parede));
        printf("Tempo de execução (exec) - tempo de CPU: %f segundos\n", calcular_tempo_cpu(inicio_cpu, fim_cpu));
    }
}

int main() {
    printf("Testando system calls...\n");
    teste_exec();
    return 0;
}
