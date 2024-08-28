#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 1024
#define MAX_CAMPOS 9

typedef struct {
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
    int duracao;
    int prioridade;
    char nome[100];
    char descricao[100];
    char local[100];
} Compromisso;

//Se houver um arquivo "saida.csv", apagará
void apagar_arquivo_saida() {
    remove("saida.csv");
}

//Opção 1 - Adicionar compromisso
void adicionar_compromisso() {
    FILE *file = fopen("entrada.csv", "a");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo entrada.csv\n");
        return;
    }

    //Estrutura para armazenar os compromissos
    Compromisso novo_compromisso;

    printf("Insira as informações do compromisso separadas por ponto e vírgula (;) na seguinte ordem:\n");
    printf("Ano;Mês;Dia;Hora;Minuto;Duração (em horas);Prioridade;Nome;Descrição;Local\n");
    
    //Validação da quantidade de entradas com uso do %*c para evitar erros com as strings
    int num_campos_lidos = scanf("%d;%d;%d;%d;%d;%d;%d;%[^;\n]%*c%[^;\n]%*c%[^\n]",
                                  &novo_compromisso.ano, &novo_compromisso.mes, &novo_compromisso.dia,
                                  &novo_compromisso.hora, &novo_compromisso.minuto, &novo_compromisso.duracao,
                                  &novo_compromisso.prioridade, novo_compromisso.nome,
                                  novo_compromisso.descricao, novo_compromisso.local);

    if (num_campos_lidos != 10) {
        fprintf(stderr, "Número/tipo incorreto de campos fornecidos. O programa será encerrado.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    //Adicionando as entradas ao arquivo
    fprintf(file, "\n%d;%d;%d;%d;%d;%d;%d;%s;%s;%s",
            novo_compromisso.ano, novo_compromisso.mes, novo_compromisso.dia,
            novo_compromisso.hora, novo_compromisso.minuto, novo_compromisso.duracao,
            novo_compromisso.prioridade, novo_compromisso.nome,
            novo_compromisso.descricao, novo_compromisso.local);

    fclose(file);
    printf("Compromisso adicionado com sucesso!\n");
}

//Opção 2 - Remover compromisso
void remover_compromisso() {
    FILE *file = fopen("entrada.csv", "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo entrada.csv\n");
        return;
    }

    int linha_a_remover;
    printf("Insira o número da linha do compromisso que deseja remover: ");
    scanf("%d", &linha_a_remover);

    //Verificação da linha
    if (linha_a_remover <= 0) {
        fprintf(stderr, "Número de linha inválido. O programa será encerrado.\n");
        fclose(file);
        return;
    }

    //Cria arquivo temporário
    FILE *temp_file = fopen("temp.csv", "w");
    if (!temp_file) {
        fprintf(stderr, "Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }

    //Faz a mudança necessária no arquivo, removendo a linha pedida
    int contador_linhas = 0;
    char linha[MAX_LINHA];
    while (fgets(linha, MAX_LINHA, file) != NULL) {
        contador_linhas++;
        if (contador_linhas == linha_a_remover) {
            continue; // Pula a linha que será removida
        }
        fprintf(temp_file, "%s", linha);
    }

    //Substitui o arquivo principal pelo temporário com as mudanças
    fclose(file);
    fclose(temp_file);

    remove("entrada.csv");
    rename("temp.csv", "entrada.csv");

    printf("Compromisso removido com sucesso!\n");
}

//Opção 3 - Ordenar por data
void ordenar_por_data() {
    apagar_arquivo_saida();
    FILE *entrada = fopen("entrada.csv", "r");
    if (!entrada) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    //Estrutura para armazenar os compromissos
    Compromisso compromissos[MAX_LINHA];
    int num_compromissos = 0;

    //Ler os compromissos do arquivo de entrada
    char linha[MAX_LINHA];
    while (fgets(linha, MAX_LINHA, entrada) != NULL) {
        sscanf(linha, "%d;%d;%d;%d;%d;%d;%d;%[^;];%[^;];%[^\n]",
               &compromissos[num_compromissos].ano, &compromissos[num_compromissos].mes,
               &compromissos[num_compromissos].dia, &compromissos[num_compromissos].hora,
               &compromissos[num_compromissos].minuto, &compromissos[num_compromissos].duracao,
               &compromissos[num_compromissos].prioridade, compromissos[num_compromissos].nome,
               compromissos[num_compromissos].descricao, compromissos[num_compromissos].local);
        num_compromissos++;
    }

    fclose(entrada);

    //Ordenação dos compromissos por data
    for (int i = 0; i < num_compromissos - 1; i++) {
        for (int j = 0; j < num_compromissos - i - 1; j++) {
            if (compromissos[j].ano > compromissos[j + 1].ano ||
                (compromissos[j].ano == compromissos[j + 1].ano &&
                 compromissos[j].mes > compromissos[j + 1].mes) ||
                (compromissos[j].ano == compromissos[j + 1].ano &&
                 compromissos[j].mes == compromissos[j + 1].mes &&
                 compromissos[j].dia > compromissos[j + 1].dia)) {
                
                //Se necessário a troca dos compromissos é feita
                Compromisso temp = compromissos[j];
                compromissos[j] = compromissos[j + 1];
                compromissos[j + 1] = temp;
            }
        }
    }

    //Abrir o arquivo de saída
    FILE *saida = fopen("saida.csv", "w");
    if (!saida) {
        fprintf(stderr, "Erro ao criar o arquivo de saída.\n");
        return;
    }

    for (int i = 0; i < num_compromissos; i++) {
        fprintf(saida, "%d;%d;%d;%d;%d;%d;%d;%s;%s;%s\n",
                compromissos[i].ano, compromissos[i].mes, compromissos[i].dia,
                compromissos[i].hora, compromissos[i].minuto, compromissos[i].duracao,
                compromissos[i].prioridade, compromissos[i].nome, compromissos[i].descricao,
                compromissos[i].local);
    }

    fclose(saida);

    printf("Compromissos ordenados por data e escritos em 'saida.csv'.\n");
}

//Opção 4 - Ordenar por data e horário
void ordenar_por_data_e_horario() {
    apagar_arquivo_saida();
    FILE *entrada = fopen("entrada.csv", "r");
    if (!entrada) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    //Estrutura para armazenar os compromissos
    Compromisso compromissos[MAX_LINHA];
    int num_compromissos = 0;

    //Ler os compromissos do arquivo de entrada
    char linha[MAX_LINHA];
    while (fgets(linha, MAX_LINHA, entrada) != NULL) {
        sscanf(linha, "%d;%d;%d;%d;%d;%d;%d;%[^;];%[^;];%[^\n]",
               &compromissos[num_compromissos].ano, &compromissos[num_compromissos].mes,
               &compromissos[num_compromissos].dia, &compromissos[num_compromissos].hora,
               &compromissos[num_compromissos].minuto, &compromissos[num_compromissos].duracao,
               &compromissos[num_compromissos].prioridade, compromissos[num_compromissos].nome,
               compromissos[num_compromissos].descricao, compromissos[num_compromissos].local);
        num_compromissos++;
    }

    fclose(entrada);

    //Ordenação dos compromissos por data e horário
    for (int i = 0; i < num_compromissos - 1; i++) {
        for (int j = 0; j < num_compromissos - i - 1; j++) {
            if (compromissos[j].ano > compromissos[j + 1].ano ||
                (compromissos[j].ano == compromissos[j + 1].ano &&
                 compromissos[j].mes > compromissos[j + 1].mes) ||
                (compromissos[j].ano == compromissos[j + 1].ano &&
                 compromissos[j].mes == compromissos[j + 1].mes &&
                 compromissos[j].dia > compromissos[j + 1].dia) ||
                (compromissos[j].ano == compromissos[j + 1].ano &&
                 compromissos[j].mes == compromissos[j + 1].mes &&
                 compromissos[j].dia == compromissos[j + 1].dia &&
                 compromissos[j].hora > compromissos[j + 1].hora) ||
                (compromissos[j].ano == compromissos[j + 1].ano &&
                 compromissos[j].mes == compromissos[j + 1].mes &&
                 compromissos[j].dia == compromissos[j + 1].dia &&
                 compromissos[j].hora == compromissos[j + 1].hora &&
                 compromissos[j].minuto > compromissos[j + 1].minuto)) {

                //Se necessário a troca dos compromissos é feita
                Compromisso temp = compromissos[j];
                compromissos[j] = compromissos[j + 1];
                compromissos[j + 1] = temp;
            }
        }
    }

    //Abrir o arquivo de saída
    FILE *saida = fopen("saida.csv", "w");
    if (!saida) {
        fprintf(stderr, "Erro ao criar o arquivo de saída.\n");
        return;
    }

    for (int i = 0; i < num_compromissos; i++) {
        fprintf(saida, "%d;%d;%d;%d;%d;%d;%d;%s;%s;%s\n",
                compromissos[i].ano, compromissos[i].mes, compromissos[i].dia,
                compromissos[i].hora, compromissos[i].minuto, compromissos[i].duracao,
                compromissos[i].prioridade, compromissos[i].nome, compromissos[i].descricao,
                compromissos[i].local);
    }

    fclose(saida);

    printf("Compromissos ordenados por data e horário e escritos em 'saida.csv'.\n");
}

//Opção 5 - Ordenar por data e prioridade
void ordenar_por_data_e_prioridade() {
    apagar_arquivo_saida();
    FILE *entrada = fopen("entrada.csv", "r");
    if (!entrada) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    //Estrutura para armazenar os compromissos
    Compromisso compromissos[MAX_LINHA];
    int num_compromissos = 0;

    //Ler os compromissos do arquivo de entrada
    char linha[MAX_LINHA];
    while (fgets(linha, MAX_LINHA, entrada) != NULL) {
        sscanf(linha, "%d;%d;%d;%d;%d;%d;%d;%[^;];%[^;];%[^\n]",
               &compromissos[num_compromissos].ano, &compromissos[num_compromissos].mes,
               &compromissos[num_compromissos].dia, &compromissos[num_compromissos].hora,
               &compromissos[num_compromissos].minuto, &compromissos[num_compromissos].duracao,
               &compromissos[num_compromissos].prioridade, compromissos[num_compromissos].nome,
               compromissos[num_compromissos].descricao, compromissos[num_compromissos].local);
        num_compromissos++;
    }

    fclose(entrada);

    //Ordenação dos compromissos por data e prioridade
    for (int i = 0; i < num_compromissos - 1; i++) {
        for (int j = 0; j < num_compromissos - i - 1; j++) {
            if (compromissos[j].ano > compromissos[j + 1].ano ||
                (compromissos[j].ano == compromissos[j + 1].ano &&
                 compromissos[j].mes > compromissos[j + 1].mes) ||
                (compromissos[j].ano == compromissos[j + 1].ano &&
                 compromissos[j].mes == compromissos[j + 1].mes &&
                 compromissos[j].dia > compromissos[j + 1].dia) ||
                (compromissos[j].ano == compromissos[j + 1].ano &&
                 compromissos[j].mes == compromissos[j + 1].mes &&
                 compromissos[j].dia == compromissos[j + 1].dia &&
                 compromissos[j].prioridade < compromissos[j + 1].prioridade)) {

                //Se necessário a troca dos compromissos é feita
                Compromisso temp = compromissos[j];
                compromissos[j] = compromissos[j + 1];
                compromissos[j + 1] = temp;
            }
        }
    }

    //Abrir o arquivo de saída
    FILE *saida = fopen("saida.csv", "w");
    if (!saida) {
        fprintf(stderr, "Erro ao criar o arquivo de saída.\n");
        return;
    }

    for (int i = 0; i < num_compromissos; i++) {
        fprintf(saida, "%d;%d;%d;%d;%d;%d;%d;%s;%s;%s\n",
                compromissos[i].ano, compromissos[i].mes, compromissos[i].dia,
                compromissos[i].hora, compromissos[i].minuto, compromissos[i].duracao,
                compromissos[i].prioridade, compromissos[i].nome, compromissos[i].descricao,
                compromissos[i].local);
    }

    fclose(saida);

    printf("Compromissos ordenados por data e prioridade e escritos em 'saida.csv'.\n");
}

//Opção 6 - Ordenar por local, prioridade e duração
void ordenar_por_local_prioridade_e_duracao() {
    apagar_arquivo_saida();
    FILE *entrada = fopen("entrada.csv", "r");
    if (!entrada) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    //Estrutura para armazenar os compromissos
    Compromisso compromissos[MAX_LINHA];
    int num_compromissos = 0;

    //Ler os compromissos do arquivo de entrada
    char linha[MAX_LINHA];
    while (fgets(linha, MAX_LINHA, entrada) != NULL) {
        sscanf(linha, "%d;%d;%d;%d;%d;%d;%d;%[^;];%[^;];%[^\n]",
               &compromissos[num_compromissos].ano, &compromissos[num_compromissos].mes,
               &compromissos[num_compromissos].dia, &compromissos[num_compromissos].hora,
               &compromissos[num_compromissos].minuto, &compromissos[num_compromissos].duracao,
               &compromissos[num_compromissos].prioridade, compromissos[num_compromissos].nome,
               compromissos[num_compromissos].descricao, compromissos[num_compromissos].local);
        num_compromissos++;
    }

    fclose(entrada);

    //Ordenação dos compromissos por local, prioridade e duração (decrescente)
    for (int i = 0; i < num_compromissos - 1; i++) {
        for (int j = 0; j < num_compromissos - i - 1; j++) {
            //Verifica o local primeiro lexicograficamente
            int comparacao_local = strcmp(compromissos[j].local, compromissos[j + 1].local);
            if (comparacao_local > 0 ||
                (comparacao_local == 0 &&
                 (compromissos[j].prioridade < compromissos[j + 1].prioridade ||
                  (compromissos[j].prioridade == compromissos[j + 1].prioridade &&
                   compromissos[j].duracao < compromissos[j + 1].duracao)))) {

                //Se necessário a troca dos compromissos é feita
                Compromisso temp = compromissos[j];
                compromissos[j] = compromissos[j + 1];
                compromissos[j + 1] = temp;
            }
        }
    }

    //Abrir o arquivo de saída
    FILE *saida = fopen("saida.csv", "w");
    if (!saida) {
        fprintf(stderr, "Erro ao criar o arquivo de saída.\n");
        return;
    }

    for (int i = 0; i < num_compromissos; i++) {
        fprintf(saida, "%d;%d;%d;%d;%d;%d;%d;%s;%s;%s\n",
                compromissos[i].ano, compromissos[i].mes, compromissos[i].dia,
                compromissos[i].hora, compromissos[i].minuto, compromissos[i].duracao,
                compromissos[i].prioridade, compromissos[i].nome, compromissos[i].descricao,
                compromissos[i].local);
    }

    fclose(saida);

    printf("Compromissos ordenados por local, prioridade e duração e escritos em 'saida.csv'.\n");
}

//Menu
int main() {
    int opcao;
    
    do {
        printf("\nMenu:\n");
        printf("1. Adicionar compromisso\n");
        printf("2. Remover compromisso\n");
        printf("3. Ordenar por data\n");
        printf("4. Ordenar por data e horário\n");
        printf("5. Ordenar por data e prioridade\n");
        printf("6. Ordenar por local, prioridade e duração (decrescente)\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar_compromisso();
                break;
            case 2:
                remover_compromisso();
                break;
            case 3:
                ordenar_por_data();
                break;
            case 4:
                ordenar_por_data_e_horario();
                break;
            case 5:
                ordenar_por_data_e_prioridade();
                break;
            case 6:
                ordenar_por_local_prioridade_e_duracao();
                break;
            case 7:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
