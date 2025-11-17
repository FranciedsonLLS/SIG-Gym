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
    //                       Buscar alunos no plano
    // ---------------------------------------------------------------------
    int encontrou = 0;

    for (int i = 0; i < total_alunos; i++)
    {
        if (lista_alunos[i].ativo &&
            strcmp(lista_alunos[i].plano_id, plano_busca) == 0)
        {
            printf("=========================================================================\n");
            printf("===                     ALUNO MATRICULADO NO PLANO                     ===\n");
            printf("=========================================================================\n");

            printf("ID:          %s\n", lista_alunos[i].id);
            printf("Nome:        %s\n", lista_alunos[i].nome);
            printf("Idade:       %s\n", lista_alunos[i].idade);
            printf("CPF:         %s\n", lista_alunos[i].cpf);
            printf("Telefone:    %s\n", lista_alunos[i].telefone);
            printf("Endereço:    %s\n", lista_alunos[i].endereco);
            printf("Email:       %s\n", lista_alunos[i].email);
            printf("Plano ID:    %s\n", lista_alunos[i].plano_id);
            printf("Plano Nome:  %s\n", nome_plano_encontrado);

            printf("=========================================================================\n\n");

            encontrou = 1;
        }
    }

    // ---------------------------------------------------------------------
    //                   nenhum aluno está no plano
    // ---------------------------------------------------------------------
    if (!encontrou)
    {
        printf("=========================================================================\n");
        printf("===             NENHUM ALUNO MATRICULADO NESTE PLANO                  ===\n");
        printf("=========================================================================\n");
    }

    printf(">>> Pressione <ENTER> para continuar...");
    getchar();
    limparTela();
}
