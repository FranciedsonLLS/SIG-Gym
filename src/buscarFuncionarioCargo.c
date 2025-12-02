#include <stdio.h>
#include <string.h>
#include "ui/funcionario/cadastrarFuncionario.h"
#include "limparTela.h"

// Cores ANSI
#define RESET "\x1b[0m"
#define COR_TITULO "\x1b[36m"
#define COR_CARGO "\x1b[33m"
#define COR_ID "\x1b[34m"
#define COR_NOME "\x1b[35m"
#define COR_ATIVO "\x1b[32m"
#define COR_INATIVO "\x1b[31m"

void buscarFuncionarioCargo(void)
{
    limparTela();

    printf(COR_TITULO);
    printf("=========================================================================\n");
    printf("===                 LISTA DE FUNCIONARIOS POR CARGO                   ===\n");
    printf("=========================================================================\n\n");
    printf(RESET);

    // Ordem fixa dos cargos
    const char *ordem_cargos[] = {"Gerente", "Atendente", "Personal"};
    const int total_ordem = 3;

    int opcao = 0;
    char cargoFiltro[20];

    // ---------------------------------------------------------------------
    // Perguntar ao usuário se deseja filtrar
    // ---------------------------------------------------------------------
    printf("Deseja filtrar por um cargo específico?\n");
    printf("1 - Sim\n");
    printf("2 - Nao (mostrar todos na ordem: Gerente, Atendente, Personal)\n");
    printf(">>> ");

    scanf("%d", &opcao);
    getchar(); // limpar \n

    printf("\n");

    int filtrar = 0;
    if (opcao == 1)
    {
        printf("Digite o cargo exatamente como salvo:\n");
        printf("Opcoes: Gerente | Atendente | Personal\n");
        printf(">>> ");
        fgets(cargoFiltro, sizeof(cargoFiltro), stdin);
        cargoFiltro[strcspn(cargoFiltro, "\n")] = '\0';

        filtrar = 1;
        printf("\nMostrando somente funcionários do cargo '" COR_CARGO "%s" RESET "'\n\n", cargoFiltro);
    }

    // ---------------------------------------------------------------------
    //                       Cabeçalho da tabela
    // ---------------------------------------------------------------------
    printf(COR_TITULO);
    printf("%-12s | %-12s | %-28s | %-15s | %-8s\n",
           "Cargo", "ID", "Nome", "Telefone", "Status");
    printf("-------------------------------------------------------------------------------\n");
    printf(RESET);

    int encontrou = 0;

    // ---------------------------------------------------------------------
    //                    FILTRAR POR CARGO ESPECÍFICO
    // ---------------------------------------------------------------------
    if (filtrar)
    {
        for (int i = 0; i < total_funcionarios; i++)
        {
            if (lista_funcionarios[i].ativo &&
                strcmp(lista_funcionarios[i].cargo, cargoFiltro) == 0)
            {
                const char *corStatus = lista_funcionarios[i].ativo ? COR_ATIVO : COR_INATIVO;

                printf(COR_CARGO "%-12s" RESET " | " COR_ID "%-12s" RESET " | " COR_NOME "%-28s" RESET " | "
                                 "%-15s | %s%-8s" RESET "\n",
                       lista_funcionarios[i].cargo,
                       lista_funcionarios[i].id,
                       lista_funcionarios[i].nome,
                       lista_funcionarios[i].telefone,
                       corStatus,
                       lista_funcionarios[i].ativo ? "ATIVO" : "INATIVO");

                encontrou = 1;
            }
        }
    }
    else
    {
        // ---------------------------------------------------------------------
        //                   MOSTRAR TODOS NA ORDEM FIXA
        // ---------------------------------------------------------------------
        for (int c = 0; c < total_ordem; c++)
        {
            for (int i = 0; i < total_funcionarios; i++)
            {
                if (lista_funcionarios[i].ativo &&
                    strcmp(lista_funcionarios[i].cargo, ordem_cargos[c]) == 0)
                {
                    const char *corStatus = lista_funcionarios[i].ativo ? COR_ATIVO : COR_INATIVO;

                    printf(COR_CARGO "%-12s" RESET " | " COR_ID "%-12s" RESET " | " COR_NOME "%-28s" RESET " | "
                                     "%-15s | %s%-8s" RESET "\n",
                           lista_funcionarios[i].cargo,
                           lista_funcionarios[i].id,
                           lista_funcionarios[i].nome,
                           lista_funcionarios[i].telefone,
                           corStatus,
                           lista_funcionarios[i].ativo ? "ATIVO" : "INATIVO");

                    encontrou = 1;
                }
            }
        }
    }

    printf("-------------------------------------------------------------------------------\n");

    if (!encontrou)
    {
        printf(COR_INATIVO "Nenhum funcionário encontrado.\n" RESET);
    }

    printf("\n>>> Pressione <ENTER> para continuar...");
    getchar();
    limparTela();
}
