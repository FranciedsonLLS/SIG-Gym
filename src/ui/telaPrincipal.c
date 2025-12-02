#include <stdio.h>
#include "limparTela.h"

char telaPrincipal(void)
{
    char op;

    printf("\n");

    printf("==========================================================================\n");
    printf("===                        <<  S I G - G Y M  >>                       ===\n");
    printf("==========================================================================\n");
    printf("===                                                                    ===\n");
    printf("===   [1]  ALUNOS                                                      ===\n");
    printf("===   [2]  PLANOS                                                      ===\n");
    printf("===   [3]  EQUIPAMENTOS                                                ===\n");
    printf("===   [4]  FUNCIONÁRIOS                                                ===\n");
    printf("===   [5]  SOBRE                                                       ===\n");
    printf("===   [6]  RELATÓRIOS                                                  ===\n");
    printf("===   [0]  SAIR                                                        ===\n");
    printf("===                                                                    ===\n");
    printf("==========================================================================\n");
    printf("==========================================================================\n");

    printf("Digite uma opção: ");
    scanf("%c", &op);
    getchar();

    limparTela();
    return op;
}
