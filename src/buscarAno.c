#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui/funcionario/cadastrarFuncionario.h"
#include "ui/aluno/cadastrarAluno.h"
#include "limparTela.h"

void buscarNascimentoAno(void)
{
    limparTela();
    printf("=========================================================================\n");
    printf("===              RELATÓRIO: NASCIDOS EM UM ANO ESPECÍFICO            ===\n");
    printf("=========================================================================\n");

    char ano_str[6];
    int ano;

    printf(">>> Digite o ano (ex: 2003): ");
    fgets(ano_str, sizeof(ano_str), stdin);
    ano_str[strcspn(ano_str, "\n")] = '\0';

    ano = atoi(ano_str);

    if (ano < 1900 || ano > 2100)
    {
        printf("\nAno inválido!\n");
        printf(">>> Pressione <ENTER> para continuar...");
        getchar();
        limparTela();
        return;
    }

    printf("\nListando nascidos em %d...\n\n", ano);

    int encontrou = 0;

    // =====================================================
    //                   FUNCIONÁRIOS (TABELA)
    // =====================================================

    printf("================================ FUNCIONÁRIOS ================================\n");
    printf("%-14s | %-25s | %-10s | %-15s | %-8s\n",
           "ID", "Nome", "Nasc.", "Cargo", "Status");
    printf("-----------------------------------------------------------------------------\n");

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

    printf("\n");

    // =====================================================
    //                        ALUNOS (TABELA)
    // =====================================================

    printf("=================================== ALUNOS ==================================\n");
    printf("%-14s | %-25s | %-10s | %-8s | %-8s\n",
           "ID", "Nome", "Nasc.", "Plano", "Status");
    printf("-----------------------------------------------------------------------------\n");

    for (int i = 0; i < total_alunos; i++)
    {
        int ano_nasc = atoi(lista_alunos[i].idade + 6); // idade contém a data

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
        printf("=========================================================================\n");
        printf("===     NINGUÉM NASCEU NO ANO INFORMADO (%d)                          ===\n", ano);
        printf("=========================================================================\n\n");
    }

    printf(">>> Pressione <ENTER> para continuar...");
    getchar();
    limparTela();
}
