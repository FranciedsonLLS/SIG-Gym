#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui/funcionario/cadastrarFuncionario.h"
#include "ui/aluno/cadastrarAluno.h"
#include "limparTela.h"

// Cores ANSI
#define COR_TITULO "\033[1;36m"
#define COR_AMARELO "\033[1;33m"
#define COR_VERDE "\033[1;32m"
#define COR_VERMELHO "\033[1;31m"
#define COR_RESET "\033[0m"

void buscarNascimentoAno(void)
{
    limparTela();

    printf(COR_TITULO);
    printf("=========================================================================\n");
    printf("===              RELATÓRIO: NASCIDOS EM UM ANO ESPECÍFICO            ===\n");
    printf("=========================================================================\n\n");
    printf(COR_RESET);

    char ano_str[6];
    int ano;

    printf(">>> Digite o ano (ex: 2003): ");
    fgets(ano_str, sizeof(ano_str), stdin);
    ano_str[strcspn(ano_str, "\n")] = '\0';

    ano = atoi(ano_str);

    if (ano < 1900 || ano > 2100)
    {
        printf(COR_VERMELHO "\nAno inválido!\n" COR_RESET);
        printf(">>> Pressione <ENTER> para continuar...");
        getchar();
        limparTela();
        return;
    }

    printf("\nListando nascidos em %d...\n\n", ano);

    int encontrou = 0;

    // =====================================================
    //                   FUNCIONÁRIOS
    // =====================================================

    printf(COR_TITULO);
    printf("============================== FUNCIONÁRIOS ==============================\n");
    printf(COR_RESET);

    printf(COR_AMARELO);
    printf("%-14s | %-25s | %-10s | %-15s | %-8s\n",
           "ID", "Nome", "Nasc.", "Cargo", "Status");
    printf("-------------------------------------------------------------------------\n");
    printf(COR_RESET);

    for (int i = 0; i < total_funcionarios; i++)
    {
        int ano_nasc = atoi(lista_funcionarios[i].nascimento + 6);

        if (ano_nasc == ano)
        {
            printf("%-14s | %-25s | %-10s | %-15s | %-8s\n",
                   lista_funcionarios[i].id,
                   lista_funcionarios[i].nome,
                   lista_funcionarios[i].nascimento,
                   lista_funcionarios[i].cargo,
                   lista_funcionarios[i].ativo ? "ATIVO" : "INATIVO");

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
    printf("%-14s | %-25s | %-10s | %-8s | %-8s\n",
           "ID", "Nome", "Nasc.", "Plano", "Status");
    printf("-------------------------------------------------------------------------\n");
    printf(COR_RESET);

    for (int i = 0; i < total_alunos; i++)
    {
        int ano_nasc = atoi(lista_alunos[i].idade + 6); // idade contém data completa

        if (ano_nasc == ano)
        {
            printf("%-14s | %-25s | %-10s | %-8s | %-8s\n",
                   lista_alunos[i].id,
                   lista_alunos[i].nome,
                   lista_alunos[i].idade,
                   lista_alunos[i].plano_id,
                   lista_alunos[i].ativo ? "ATIVO" : "INATIVO");

            encontrou = 1;
        }
    }

    printf("\n");

    // =====================================================
    //                       NENHUM REGISTRO
    // =====================================================

    if (!encontrou)
    {
        printf(COR_AMARELO);
        printf("=========================================================================\n");
        printf("===     NINGUÉM NASCEU NO ANO INFORMADO (%d)                          ===\n", ano);
        printf("=========================================================================\n\n");
        printf(COR_RESET);
    }

    printf(">>> Pressione <ENTER> para continuar...");
    getchar();
    limparTela();
}
