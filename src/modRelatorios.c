#include <stdio.h>
#include <stdlib.h>

#include "limparTela.h"

// Funções reais dos relatórios:
#include "buscar.h"                 // buscarPorCPF()
#include "buscarAlunoPlano.h"       // buscarAlunoPorPlano()
#include "buscarAniversario.h"      // Aniversariantes
#include "buscarAno.h"              // Nascidos em ano
#include "buscarPPNome.h"           // Busca por primeiro nome
#include "buscarFuncionarioCargo.h" // <<---- NOVO

#include <stdio.h>
#include <stdlib.h>
#include "limparTela.h"

// Cores ANSI
#define COR_TITULO "\033[1;36m"
#define COR_OPCAO "\033[1;33m"
#define COR_RESET "\033[0m"
#define COR_VERDE "\033[1;32m"
#define COR_CINZA "\033[1;90m"

char telaRelatorios(void)
{
    limparTela();

    printf(COR_TITULO);
    printf("===============================================================================\n");
    printf("===                               RELATÓRIOS                                ===\n");
    printf("===============================================================================\n");
    printf(COR_RESET);

    printf("===                                                                         ===\n");
    printf("===  " COR_VERDE ">> CONSULTAS INDIVIDUAIS" COR_RESET "                                               ===\n");
    printf("===      " COR_OPCAO "[1]" COR_RESET " Buscar perfil por CPF                                          ===\n");
    printf("===      " COR_OPCAO "[6]" COR_RESET " Buscar pelo PRIMEIRO NOME                                      ===\n");
    printf("===                                                                         ===\n");

    printf("===  " COR_VERDE ">> AGRUPAMENTOS / LISTAGENS" COR_RESET "                                            ===\n");
    printf("===      " COR_OPCAO "[2]" COR_RESET " Listar ALUNOS por PLANO                                        ===\n");
    printf("===      " COR_OPCAO "[3]" COR_RESET " Listar FUNCIONÁRIOS por CARGO                                  ===\n");
    printf("===      " COR_OPCAO "[7]" COR_RESET " Listar INATIVOS (Alunos + Funcionários)                        ===\n");
    printf("===                                                                         ===\n");

    printf("===  " COR_VERDE ">> RELATÓRIOS ESPECIAIS" COR_RESET "                                                ===\n");
    printf("===      " COR_OPCAO "[4]" COR_RESET " Aniversariantes do mês                                         ===\n");
    printf("===      " COR_OPCAO "[5]" COR_RESET " Nascidos em um ANO (Alunos + Funcionários)                     ===\n");
    printf("===                                                                         ===\n");

    printf("===  ---------------------------------------------------------------------  ===\n");
    printf("===      " COR_OPCAO "[0]" COR_RESET " Voltar ao menu anterior                                        ===\n");
    printf("===  ---------------------------------------------------------------------  ===\n");

    printf("===============================================================================\n");
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
            buscarFuncionarioCargo();
            break;

        case '4':
            buscarAniversario();
            break;

        case '5':
            buscarNascimentoAno();
            break;

        case '6':
            buscarPPNome();
            break;

        case '7':
            buscarInativos(); // <<< NOVO
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
