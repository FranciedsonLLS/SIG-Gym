#include <stdio.h>
#include <stdlib.h>

#include "limparTela.h"

// Funções reais dos relatórios:
#include "buscar.h"            // buscarPorCPF()
#include "buscarAlunoPlano.h"  // buscarAlunoPorPlano()
#include "buscarAniversario.h" // Aniversariantes
#include "buscarAno.h"         // Nascidos em ano
#include "buscarPPNome.h"      // <<---- NOVO (Busca por primeiro nome)
// #include "buscarFuncionarioCargo.h"

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
    printf("===   [4]  Aniversariantes do mês                                     ===\n");
    printf("===   [5]  Listar nascidos em um ANO (Alunos + Funcionários)          ===\n");
    printf("===   [6]  Buscar pessoas pelo PRIMEIRO NOME                          ===\n");
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

        case '4':
            buscarAniversario();
            break;

        case '5':
            buscarNascimentoAno();
            break;

        case '6':
            buscarPPNome(); // <<---- NOVO
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
