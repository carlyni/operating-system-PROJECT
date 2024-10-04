Contexto do Tema

A avaliação de desempenho por meio de System Calls em sistemas Linux é uma área crítica para entender como o sistema operacional gerencia recursos e executa processos. As System Calls são as interfaces entre o kernel e os aplicativos, permitindo que os programas solicitem serviços do sistema, como a criação de novos processos, manipulação de arquivos e comunicação entre processos. Em particular, as chamadas fork, clone e exec são fundamentais para a criação e gerenciamento de processos em sistemas Linux.

Planejamento dos Experimentos
Objetivos

    Avaliar o desempenho das System Calls fork, clone e exec em diferentes cenários.

    Medir o tempo real e o tempo de CPU para entender melhor o custo associado a cada operação.

Cenários

    Cenário 1: Utilização do fork() para criar um processo filho que executa um código simples para medir o tempo de execução de ambos os processos (pai e filho).

    Cenário 2: Utilização do clone() com a flag CLONE_VM para criar uma thread que compartilha o espaço de memória com o processo pai. O teste envolverá a execução de um código que altera um valor compartilhado, permitindo observar a comunicação entre threads.

    Cenário 3: Uso do exec() para substituir o conteúdo de um processo em execução por um novo programa. Isso permitirá medir o tempo necessário para a substituição do processo.

Métricas de Desempenho

    Tempo Real: Medido usando a função gettimeofday(), que fornece a hora atual e permite calcular o tempo total de execução de cada cenário.

    Tempo de CPU: Medido usando clock(), que contabiliza o tempo de CPU consumido pelo processo durante a execução.

    Uso do strace para observar quais systemcalls foram utilizadas durante a execução dos programas

Coleta de Dados

    Executar cada cenário 2 vezes para garantir a consistência dos resultados.

    Armazenar os dados de tempo real e tempo de CPU em tabelas para serem analisados.

Análise dos Resultados

    Comparar os tempos de execução e o uso de CPU entre os cenários para avaliar o desempenho relativo das System Calls.

    Utilizar o Jupyter Notebook para gerar gráficos que representem visualmente os dados coletados, permitindo uma análise intuitiva.

