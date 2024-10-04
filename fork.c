#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sched.h>
#include <time.h>

// Função para medir tempo usando gettimeofday()
double calcular_tempo_gettimeofday(struct timeval inicio, struct timeval fim) {
    return (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000000.0;
}

// Função para medir tempo usando clock()
double calcular_tempo_clock(clock_t inicio, clock_t fim) {
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// Teste para fork()
void teste_fork() {
    struct timeval inicio_tv, fim_tv;
    clock_t inicio_clock, fim_clock;

    gettimeofday(&inicio_tv, NULL);
    inicio_clock = clock();

    pid_t pid = fork();
    if (pid == 0) {
        // Código do processo filho
        exit(0);
    } else {
        wait(NULL);
        gettimeofday(&fim_tv, NULL);
        fim_clock = clock();

        printf("Fork -> Tempo real: %f segundos\n", calcular_tempo_gettimeofday(inicio_tv, fim_tv));
        printf("Fork -> Tempo de CPU: %f segundos\n", calcular_tempo_clock(inicio_clock, fim_clock));
    }
}

int main() {
    printf("Testando system calls...\n");

    // Testando fork()
    teste_fork();


    return 0;
}