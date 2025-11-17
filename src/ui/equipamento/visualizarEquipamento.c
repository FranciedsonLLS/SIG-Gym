#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "limparTela.h"
#include "cadastrarEquipamento.h"

void telaVisualizarEquipamento(void)
{
    if (total_equipamentos == 0)
    {
        limparTela();
        printf("=========================================================================\n");
        printf("===                  VISUALIZAR EQUIPAMENTOS                           ===\n");
        printf("=========================================================================\n");
        printf("===                 NENHUM EQUIPAMENTO CADASTRADO                      ===\n");
        printf("=========================================================================\n");
        getchar();
        limparTela();
        return;
    }

    limparTela();
    printf("=========================================================================\n");
    printf("===                  VISUALIZAR EQUIPAMENTOS                           ===\n");
    printf("=========================================================================\n");

    // ------------------ TABELA ALINHADA ------------------
    printf("\n%-12s | %-35s | %-10s\n", "ID", "NOME", "STATUS");
    printf("-------------------------------------------------------------------------------\n");

    int algum_ativo = 0;

    for (int i = 0; i < total_equipamentos; i++)
    {
        if (lista_equipamentos[i].ativo)
        {
            printf("%-12s | %-35s | %-10s\n",
                   lista_equipamentos[i].id,
                   lista_equipamentos[i].nome,
                   "ATIVO");

            algum_ativo = 1;
        }
    }

    printf("-------------------------------------------------------------------------------\n");

    if (!algum_ativo)
    {
        printf("===                   NENHUM EQUIPAMENTO ATIVO                         ===\n");
        printf("=========================================================================\n");
        getchar();
        limparTela();
        return;
    }

    // ------------------ BUSCA ------------------
    printf("\n>>> Digite o ID do equipamento que deseja visualizar: ");
    char id_busca[12];
    fgets(id_busca, sizeof(id_busca), stdin);
    id_busca[strcspn(id_busca, "\n")] = '\0';

    int encontrado = 0;

    for (int i = 0; i < total_equipamentos; i++)
    {
        if (strcmp(lista_equipamentos[i].id, id_busca) == 0 && lista_equipamentos[i].ativo)
        {
            limparTela();
            printf("=========================================================================\n");
            printf("===                  INFORMAÇÕES DO EQUIPAMENTO                        ===\n");
            printf("=========================================================================\n");

            // --------------- DETALHES ALINHADOS ----------------
            printf("%-25s : %s\n", "ID", lista_equipamentos[i].id);
            printf("%-25s : %s\n", "Nome", lista_equipamentos[i].nome);
            printf("%-25s : %s\n", "Última manutenção", lista_equipamentos[i].ultima_manutencao);
            printf("%-25s : %s\n", "Próxima manutenção", lista_equipamentos[i].proxima_manutencao);
            printf("%-25s : %s\n", "Categoria", lista_equipamentos[i].categoria);

            printf("=========================================================================\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("=========================================================================\n");
        printf("===                  VISUALIZAR EQUIPAMENTOS                           ===\n");
        printf("=========================================================================\n");
        printf("===                      EQUIPAMENTO NÃO ENCONTRADO                    ===\n");
        printf("=========================================================================\n");
    }

    getchar();
    limparTela();
}
