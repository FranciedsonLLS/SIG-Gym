#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui/funcionario/cadastrarFuncionario.h"
#include "ui/aluno/cadastrarAluno.h"
#include "limparTela.h"

// Cores ANSI
#define COR_TITULO "\033[1;36m"
#define COR_VERDE "\033[1;32m"
#define COR_VERMELHO "\033[1;31m"
#define COR_AMARELO "\033[1;33m"
#define COR_RESET "\033[0m"

void buscarAniversario(void)
{
    limparTela();

    printf(COR_TITULO);
    printf("=========================================================================\n");
    printf("===                 RELATÓRIO: ANIVERSARIANTES DO MÊS                 ===\n");
    printf("=========================================================================\n\n");
    printf(COR_RESET);

    char mes_str[4];
    int mes;

    printf(">>> Digite o mês (1 a 12): ");
    fgets(mes_str, sizeof(mes_str), stdin);
    mes_str[strcspn(mes_str, "\n")] = '\0';

    mes = atoi(mes_str);

    if (mes < 1 || mes > 12)
    {
        printf(COR_VERMELHO "\nMês inválido!\n" COR_RESET);
        printf(">>> Pressione <ENTER> para continuar...");
        getchar();
        limparTela();
        return;
    }

    printf("\nListando aniversariantes do mês %02d...\n\n", mes);

    int encontrou = 0;

    // =====================================================
    //                   FUNCIONÁRIOS
    // =====================================================
    printf(COR_TITULO);
    printf("============================== FUNCIONÁRIOS ==============================\n");
    printf(COR_RESET);

    printf(COR_AMARELO);
    printf("%-14s | %-25s | %-10s | %-15s\n",
           "ID", "Nome", "Nasc.", "Cargo");
    printf("-------------------------------------------------------------------------\n");
    printf(COR_RESET);

    for (int i = 0; i < total_funcionarios; i++)
    {
        if (!lista_funcionarios[i].ativo)
            continue;

        int mes_nasc = atoi(lista_funcionarios[i].nascimento + 3);

        if (mes_nasc == mes)
        {
            printf("%-14s | %-25s | %-10s | %-15s\n",
                   lista_funcionarios[i].id,
                   lista_funcionarios[i].nome,
                   lista_funcionarios[i].nascimento,
                   lista_funcionarios[i].cargo);
            encontrou = 1;
        }
    }

    printf("\n>>> Pressione <ENTER> para ver os ALUNOS...");
    getchar();
    limparTela();

    // =====================================================
    //                       ALUNOS
    // =====================================================
    printf(COR_TITULO);
    printf("=============================== ALUNOS =================================\n");
    printf(COR_RESET);

    printf(COR_AMARELO);
    printf("%-14s | %-25s | %-10s | %-8s\n",
           "ID", "Nome", "Nasc.", "Plano");
    printf("-------------------------------------------------------------------------\n");
    printf(COR_RESET);

    for (int i = 0; i < total_alunos; i++)
    {
        if (!lista_alunos[i].ativo)
            continue;

        int mes_nasc = atoi(lista_alunos[i].idade + 3);

        if (mes_nasc == mes)
        {
            printf("%-14s | %-25s | %-10s | %-8s\n",
                   lista_alunos[i].id,
                   lista_alunos[i].nome,
                   lista_alunos[i].idade,
                   lista_alunos[i].plano_id);
            encontrou = 1;
        }
    }

    printf("\n");

    // =====================================================
    //                  NENHUM RESULTADO
    // =====================================================
    if (!encontrou)
    {
        printf(COR_AMARELO);
        printf("=========================================================================\n");
        printf("===            NINGUÉM FAZ ANIVERSÁRIO NESTE MÊS                       ===\n");
        printf("=========================================================================\n\n");
        printf(COR_RESET);
    }

    printf(">>> Pressione <ENTER> para continuar...");
    getchar();
    limparTela();
}
