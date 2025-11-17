#include <stdio.h>
#include <stdlib.h>

#include "limparTela.h"

// Funções reais dos relatórios:
#include "buscar.h"           // buscarPorCPF()
#include "buscarAlunoPlano.h" // buscarAlunoPorPlano()
// #include "buscarFuncionarioCargo.h" // buscarFuncionarioPorCargo()

char telaRelatorios(void)
{
    limparTela();

    printf("=========================================================================\n");
    printf("===                           RELATÓRIOS                              ===\n");
    printf("=========================================================================\n");
    printf("===                                                                   ===\n");
    printf("===   [1]  Buscar perfil por CPF                                      ===\n");
    printf("===   [2]  Listar ALUNOS por PLANO                                    ===\n");
    printf("===   [3]  Listar FUNCIONÁRIOS por CARGO                              ===\n");
    printf("===                                                                   ===\n");
    printf("===   [0]  Voltar                                                     ===\n");
    printf("===                                                                   ===\n");
    printf("=========================================================================\n");
    printf("=========================================================================\n");
    printf(">>> Escolha uma opção: ");

    char op;
    scanf(" %c", &op);
    getchar();

    return op;
}

void moduloRelatorios(void)
{
    char op;

    do
    {
        op = telaRelatorios();

        switch (op)
        {
        case '1':
            buscarPorCPF();
            break;

        case '2':
            buscarAlunoPorPlano();
            break;

        case '3':
            // buscarFuncionarioPorCargo();
            break;

        case '0':
            break;

        default:
            printf("\n>>> Opção inválida!\n");
            break;
        }

        printf("\n>>> Pressione <ENTER> para continuar...");
        getchar();
        limparTela();

    } while (op != '0');
}
