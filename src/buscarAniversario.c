#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui/funcionario/cadastrarFuncionario.h"
#include "ui/aluno/cadastrarAluno.h"
#include "limparTela.h"

void buscarAniversario(void)
{
    limparTela();
    printf("=========================================================================\n");
    printf("===                 RELATÓRIO: ANIVERSARIANTES DO MÊS                 ===\n");
    printf("=========================================================================\n");

    char mes_str[4];
    int mes;

    printf(">>> Digite o mês (1 a 12): ");
    fgets(mes_str, sizeof(mes_str), stdin);
    mes_str[strcspn(mes_str, "\n")] = '\0';

    mes = atoi(mes_str);

    if (mes < 1 || mes > 12)
    {
        printf("\nMês inválido!\n");
        printf(">>> Pressione <ENTER> para continuar...");
        getchar();
        limparTela();
        return;
    }

    printf("\nListando aniversariantes do mês %02d...\n\n", mes);

    int encontrou = 0;

    // =====================================================
    //                 FUNCIONÁRIOS
    // =====================================================
    for (int i = 0; i < total_funcionarios; i++)
    {
        if (!lista_funcionarios[i].ativo)
            continue;

        // Data no formato DD/MM/AAAA
        int mes_nasc = atoi(lista_funcionarios[i].nascimento + 3);

        if (mes_nasc == mes)
        {
            printf("=========================================================================\n");
            printf("===                        FUNCIONÁRIO                                ===\n");
            printf("=========================================================================\n");

            printf("ID:        %s\n", lista_funcionarios[i].id);
            printf("Nome:      %s\n", lista_funcionarios[i].nome);
            printf("Cargo:     %s\n", lista_funcionarios[i].cargo);
            printf("Nascimento:%s\n", lista_funcionarios[i].nascimento);
            printf("Telefone:  %s\n", lista_funcionarios[i].telefone);
            printf("Email:     %s\n", lista_funcionarios[i].email);

            printf("=========================================================================\n\n");

            encontrou = 1;
        }
    }

    // =====================================================
    //                       ALUNOS
    // =====================================================
    for (int i = 0; i < total_alunos; i++)
    {
        if (!lista_alunos[i].ativo)
            continue;

        // Data no formato DD/MM/AAAA
        int mes_nasc = atoi(lista_alunos[i].idade + 3);

        if (mes_nasc == mes)
        {
            printf("=========================================================================\n");
            printf("===                           ALUNO                                    ===\n");
            printf("=========================================================================\n");

            printf("ID:        %s\n", lista_alunos[i].id);
            printf("Nome:      %s\n", lista_alunos[i].nome);
            printf("Nascimento:%s\n", lista_alunos[i].idade);
            printf("Telefone:  %s\n", lista_alunos[i].telefone);
            printf("Email:     %s\n", lista_alunos[i].email);
            printf("Plano:     %s\n", lista_alunos[i].plano_id);

            printf("=========================================================================\n\n");

            encontrou = 1;
        }
    }

    // =====================================================
    //                  NENHUM RESULTADO
    // =====================================================
    if (!encontrou)
    {
        printf("=========================================================================\n");
        printf("===            NINGUÉM FAZ ANIVERSÁRIO NESTE MÊS                       ===\n");
        printf("=========================================================================\n\n");
    }

    printf(">>> Pressione <ENTER> para continuar...");
    getchar();
    limparTela();
}
