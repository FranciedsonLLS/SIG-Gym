#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui/aluno/cadastrarAluno.h"
#include "ui/plano/cadastrarPlano.h"
#include "limparTela.h"

// Cores ANSI (mantive as que você usou)
#define COR_TITULO "\033[1;36m"
#define COR_VERDE "\033[1;32m"
#define COR_VERMELHO "\033[1;31m"
#define COR_AMARELO "\033[1;33m"
#define COR_RESET "\033[0m"

void buscarAlunoPorPlano(void)
{
    limparTela();

    printf(COR_TITULO);
    printf("=========================================================================\n");
    printf("===                    BUSCAR ALUNOS POR PLANO                         ===\n");
    printf("=========================================================================\n\n");
    printf(COR_RESET);

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
        printf(COR_VERMELHO);
        printf("=========================================================================\n");
        printf("===                     PLANO NAO ENCONTRADO                           ===\n");
        printf("=========================================================================\n");
        printf(COR_RESET);

        printf(">>> Pressione <ENTER> para continuar...");
        getchar();
        limparTela();
        return;
    }

    // ---------------------------------------------------------------------
    //                 Buscar alunos do plano (salvar em vetor auxiliar)
    // ---------------------------------------------------------------------
    struct aluno **alunosEncontrados = NULL;
    int qtd = 0;

    if (total_alunos > 0)
    {
        alunosEncontrados = malloc(sizeof(struct aluno *) * total_alunos);
        if (!alunosEncontrados)
        {
            // falha de alocação (muito improvável, mas tratamos)
            printf(COR_VERMELHO "Erro de memoria. Impossivel listar alunos.\n" COR_RESET);
            printf(">>> Pressione <ENTER> para continuar...");
            getchar();
            limparTela();
            return;
        }
    }

    for (int i = 0; i < total_alunos; i++)
    {
        if (lista_alunos[i].ativo &&
            strcmp(lista_alunos[i].plano_id, plano_busca) == 0)
        {
            alunosEncontrados[qtd++] = &lista_alunos[i];
        }
    }

    // ---------------------------------------------------------------------
    //                  Ordenar os alunos por nome (alfabético)
    // ---------------------------------------------------------------------
    if (qtd > 1)
    {
        for (int i = 0; i < qtd - 1; i++)
        {
            for (int j = 0; j < qtd - i - 1; j++)
            {
                if (strcmp(alunosEncontrados[j]->nome, alunosEncontrados[j + 1]->nome) > 0)
                {
                    struct aluno *tmp = alunosEncontrados[j];
                    alunosEncontrados[j] = alunosEncontrados[j + 1];
                    alunosEncontrados[j + 1] = tmp;
                }
            }
        }
    }

    // ---------------------------------------------------------------------
    //                       Cabeçalho da tabela
    // ---------------------------------------------------------------------
    printf(COR_TITULO);
    printf("=========================================================================\n");
    printf("  Alunos matriculados no plano: %s (%s)\n", nome_plano_encontrado, plano_busca);
    printf("=========================================================================\n\n");
    printf(COR_RESET);

    printf(COR_AMARELO);
    printf("%-13s | %-25s | %-10s | %-13s | %-7s\n",
           "ID", "Nome", "Nasc.", "Telefone", "Status");
    printf("-------------------------------------------------------------------------------\n");
    printf(COR_RESET);

    // ---------------------------------------------------------------------
    //                       Exibir alunos ordenados
    // ---------------------------------------------------------------------
    if (qtd == 0)
    {
        printf(COR_AMARELO);
        printf("Nenhum aluno encontrado neste plano.\n");
        printf(COR_RESET);
    }
    else
    {
        for (int i = 0; i < qtd; i++)
        {
            struct aluno *a = alunosEncontrados[i];

            const char *corStatus = a->ativo ? COR_VERDE : COR_VERMELHO;

            printf("%-13s | %-25s | %-10s | %-13s | %s%-7s%s\n",
                   a->id,
                   a->nome,
                   a->idade,
                   a->telefone,
                   corStatus,
                   a->ativo ? "ATIVO" : "INATIVO",
                   COR_RESET);
        }
    }

    printf("-------------------------------------------------------------------------------\n");

    // ---------------------------------------------------------------------
    //                       EXIBIR QUANTIDADE FINAL
    // ---------------------------------------------------------------------
    printf(COR_TITULO);
    printf("\nTotal de alunos no plano '%s': %d\n", nome_plano_encontrado, qtd);
    printf(COR_RESET);

    // liberar o buffer auxiliar
    free(alunosEncontrados);

    printf("\n>>> Pressione <ENTER> para continuar...");
    getchar();
    limparTela();
}
