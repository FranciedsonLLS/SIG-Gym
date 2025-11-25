#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui/aluno/cadastrarAluno.h"
#include "ui/plano/cadastrarPlano.h"
#include "limparTela.h"

void buscarAlunoPorPlano(void)
{
    limparTela();

    printf("=========================================================================\n");
    printf("===                    BUSCAR ALUNOS POR PLANO                         ===\n");
    printf("=========================================================================\n");

    char plano_busca[12];

    printf(">>> Digite o ID do plano: ");
    fgets(plano_busca, sizeof(plano_busca), stdin);
    plano_busca[strcspn(plano_busca, "\n")] = '\0';

    printf("\n");

    // ---------------------------------------------------------------------
    //       Primeiro: verificar se o plano existe e obter seu nome
    // ---------------------------------------------------------------------
    char nome_plano_encontrado[MAX_BUFFER] = "DESCONHECIDO";
    int plano_existe = 0;

    for (int i = 0; i < total_planos; i++)
    {
        if (lista_planos[i].ativo &&
            strcmp(lista_planos[i].id, plano_busca) == 0)
        {
            strcpy(nome_plano_encontrado, lista_planos[i].nome);
            plano_existe = 1;
            break;
        }
    }

    if (!plano_existe)
    {
        printf("=========================================================================\n");
        printf("===                     PLANO NAO ENCONTRADO                           ===\n");
        printf("=========================================================================\n");
        printf(">>> Pressione <ENTER> para continuar...");
        getchar();
        limparTela();
        return;
    }

    // ---------------------------------------------------------------------
    //                       Cabeçalho da tabela
    // ---------------------------------------------------------------------
    printf("=========================================================================\n");
    printf(" Alunos matriculados no plano: %s (%s)\n", nome_plano_encontrado, plano_busca);
    printf("=========================================================================\n\n");

    printf("ID            | Nome                      | Nasc.      | Telefone      | Status\n");
    printf("-------------------------------------------------------------------------------\n");

    // ---------------------------------------------------------------------
    //                       Buscar alunos no plano
    // ---------------------------------------------------------------------
    int encontrou = 0;
    int qtd_alunos_plano = 0;

    for (int i = 0; i < total_alunos; i++)
    {
        if (lista_alunos[i].ativo &&
            strcmp(lista_alunos[i].plano_id, plano_busca) == 0)
        {
            printf("%-13s | %-25s | %-10s | %-13s | %-6s\n",
                   lista_alunos[i].id,
                   lista_alunos[i].nome,
                   lista_alunos[i].idade,
                   lista_alunos[i].telefone,
                   lista_alunos[i].ativo ? "ATIVO" : "INATIVO");

            encontrou = 1;
            qtd_alunos_plano++;
        }
    }

    printf("-------------------------------------------------------------------------------\n");

    // ---------------------------------------------------------------------
    //                   nenhum aluno está no plano
    // ---------------------------------------------------------------------
    if (!encontrou)
    {
        printf("Nenhum aluno encontrado neste plano.\n");
    }

    // ---------------------------------------------------------------------
    //                       EXIBIR QUANTIDADE FINAL
    // ---------------------------------------------------------------------
    printf("Total de alunos no plano '%s': %d\n",
           nome_plano_encontrado,
           qtd_alunos_plano);

    printf("\n>>> Pressione <ENTER> para continuar...");
    getchar();
    limparTela();
}
