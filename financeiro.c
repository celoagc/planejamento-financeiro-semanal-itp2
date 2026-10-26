#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAT 5
#define DIAS 7
#define TAM_NOME 50

// Função para limpar o buffer de entrada
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ler e validar os dados de entrada
void ler_dados(int qtd_cat, char categorias[][TAM_NOME], double gastos[][DIAS]) {
    
    const char *nomes_dias[DIAS] = {
        "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado", "Domingo"
    };

    for (int i = 0; i < qtd_cat; i++) {
        int nome_valido = 0;
        
        while (!nome_valido) {
            printf("\nDigite o nome da categoria %d: ", i + 1);
            if (fgets(categorias[i], TAM_NOME, stdin) != NULL) {
                size_t len = strlen(categorias[i]);
                if (len > 0 && categorias[i][len - 1] == '\n') {
                    categorias[i][len - 1] = '\0';
                    len--;
                } else {
                    limpar_buffer();
                }

                // Verifica se o nome não está vazio ou só com espaços
                for (size_t j = 0; j < len; j++) {
                    if (categorias[i][j] != ' ' && categorias[i][j] != '\t') {
                        nome_valido = 1;
                        break;
                    }
                }
            }
            if (!nome_valido) {
                printf("ERRO: O nome da categoria não pode ser vazio.\n");
            }
        }

        // Leitura dos gastos dos 7 dias para a categoria atual
        for (int d = 0; d < DIAS; d++) {
            double valor;
            int leitura_ok = 0;
            while (!leitura_ok) {
                printf("  Gasto em '%s' na %s (R$): ", categorias[i], nomes_dias[d]);
                if (scanf("%lf", &valor) == 1) {
                    if (valor >= 0.0) {
                        gastos[i][d] = valor;
                        leitura_ok = 1;
                    } else {
                        printf("  Erro: O valor não pode ser negativo.\n");
                    }
                } else {
                    printf("  Erro: Entrada inválida. Digite um número.\n");
                }
                limpar_buffer();
            }
        }
    }
}

// Função para calcular os totais por categoria, por dia e o total geral da semana
void calcular_resultados(int qtd_cat, double gastos[][DIAS], double *totais_cat, double *totais_dia, double *total_semana) {
    *total_semana = 0.0;

    for (int d = 0; d < DIAS; d++) {
        totais_dia[d] = 0.0;
    }

    for (int i = 0; i < qtd_cat; i++) {
        totais_cat[i] = 0.0;
        for (int d = 0; d < DIAS; d++) {
            totais_cat[i] += gastos[i][d];
            totais_dia[d] += gastos[i][d];
        }
        *total_semana += totais_cat[i];
    }
}

// Função para exibir o relatório completo
void exibir_relatorio(int qtd_cat, char categorias[][TAM_NOME], double *totais_cat, double *totais_dia, double total_semana) {
    
    const char *nomes_dias[DIAS] = {
        "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado", "Domingo"
    };

    printf("\n========================================\n");
    printf("       RESUMO DE GASTOS DA SEMANA       \n");
    printf("========================================\n");

    printf("\n--- Totais por Categoria ---\n");
    for (int i = 0; i < qtd_cat; i++) {
        double percentual = (total_semana > 0.0) ? (totais_cat[i] / total_semana) * 100.0 : 0.0;
        printf("%-20s: R$ %8.2f (%6.2f%%)\n", categorias[i], totais_cat[i], percentual);
    }

    printf("\n--- Totais por Dia ---\n");
    for (int d = 0; d < DIAS; d++) {
        printf("%-10s: R$ %8.2f\n", nomes_dias[d], totais_dia[d]);
    }

    printf("\nTotal Geral da Semana: R$ %.2f\n", total_semana);

    if (total_semana == 0.0) {
        printf("\nAviso: Não houve gastos na semana (todas as porcentagens são 0.00%%).\n");
    } else {
        // Descobre o maior valor gasto em uma categoria
        double maior_gasto = totais_cat[0];
        for (int i = 1; i < qtd_cat; i++) {
            if (totais_cat[i] > maior_gasto) {
                maior_gasto = totais_cat[i];
            }
        }

        double perc_maior = (maior_gasto / total_semana) * 100.0;
        printf("\n--- Categoria(s) com Maior Gasto ---\n");
        for (int i = 0; i < qtd_cat; i++) {
            if (totais_cat[i] == maior_gasto) {
                printf("- %s: R$ %.2f (%.2f%% do total)\n", categorias[i], totais_cat[i], perc_maior);
            }
        }
    }
    printf("========================================\n");
}

int main() {
    int qtd_cat = 0;
    char categorias[MAX_CAT][TAM_NOME];
    double gastos[MAX_CAT][DIAS] = {0};
    double totais_dia[DIAS] = {0};
    double total_semana = 0.0;

    printf("=== CONTROLE DE GASTOS SEMANAL ===\n");

    // Entrada de quantidade de categorias + parada forçada do programa
    while (qtd_cat < 1 || qtd_cat > MAX_CAT) {      
        printf("\n Informe a quantidade de categorias (1 a %d): ", MAX_CAT);
        
        if (scanf("%d", &qtd_cat) != 1) {
            printf("ERRO: Digite um numero inteiro válido.\n");
            qtd_cat = -1;
        } else if (qtd_cat == 0) {          
            printf("\nPrograma encerrado pelo usuário.\n");
            return 0;
        } else if (qtd_cat < 1 || qtd_cat > MAX_CAT) {
            printf("ERRO: A quantidade precisa ser entre 1 e %d.\n", MAX_CAT);
        }
        
        limpar_buffer();
    }

    // Alocar memória dinâmica da quantidade de categorias para armazenar os totais
    double *totais_cat = (double *)calloc(qtd_cat, sizeof(double));
    if (totais_cat == NULL) {
        printf("ERRO CRÍTICO: Falha ao alocar memória dinâmica.\n");
        return 1;
    }

    // Passos do programa
    // 1°: Lê e valida os dados de entrada
    ler_dados(qtd_cat, categorias, gastos);

    //2°: Calcula os totais por categoria, por dia e o total geral da semana
    calcular_resultados(qtd_cat, gastos, totais_cat, totais_dia, &total_semana);

    //3°: Exibe o relatório completo
    exibir_relatorio(qtd_cat, categorias, totais_cat, totais_dia, total_semana);

    // Liberar memória alocada
    free(totais_cat);
    totais_cat = NULL;

    return 0;
}