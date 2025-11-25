#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "buscarPPNome.h"
#include "ui/aluno/cadastrarAluno.h"
#include "ui/funcionario/cadastrarFuncionario.h"
#include "limparTela.h"

// ------------------------------------------------------
// CORES ANSI
// ------------------------------------------------------
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define BLUE "\033[34m"

// ------------------------------------------------------
// Remover diferenças entre maiúsculas/minúsculas
// ------------------------------------------------------
int iguaisIgnoreCase(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (tolower(*a) != tolower(*b))
            return 0;
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

// ------------------------------------------------------
// Extrair primeiro nome do nome completo
// ------------------------------------------------------
void primeiroNome(const char *nomeCompleto, char *dest)
{
    int i = 0;
    while (nomeCompleto[i] != '\0' && nomeCompleto[i] != ' ')
    {
        dest[i] = nomeCompleto[i];
        i++;
    }
    dest[i] = '\0';
}

// ------------------------------------------------------
// RELATÓRIO TABELADO + COLORIDO
// ------------------------------------------------------
void buscarPPNome(void)
{
    limparTela();

    printf(CYAN BOLD);
    printf("=========================================================================\n");
    printf("===                 BUSCAR PESSOAS PELO PRIMEIRO NOME                 ===\n");
    printf("=========================================================================\n" RESET);

    char nomeBusca[50];
    printf(YELLOW ">>> Digite o primeiro nome: " RESET);
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    if (strlen(nomeBusca) == 0)
    {
        printf(RED "\nEntrada inválida!\n" RESET);
        printf("Pressione ENTER...");
        getchar();
        return;
    }

    printf("\n" GREEN BOLD ">>> Resultados para o nome: '%s'\n\n" RESET, nomeBusca);

    // Cabeçalho da Tabela
    printf(MAGENTA BOLD);
    printf("======================================================================================\n");
    printf("%-12s | %-27s | %-13s | %-18s | %-6s\n",
           "ID", "Nome", "Tipo", "Plano/Cargo", "Status");
    printf("--------------------------------------------------------------------------------------\n" RESET);

    int encontrou = 0;

    // ---------------- ALUNOS ----------------
    for (int i = 0; i < total_alunos; i++)
    {
        if (!lista_alunos[i].ativo)
            continue;

        char pNome[40];
        primeiroNome(lista_alunos[i].nome, pNome);

        if (iguaisIgnoreCase(pNome, nomeBusca))
        {
            printf(BLUE);
            printf("%-12s | %-27s | %-13s | %-18s | %-6s\n",
                   lista_alunos[i].id,
                   lista_alunos[i].nome,
                   "ALUNO",
                   lista_alunos[i].plano_id,
                   "ATIVO");
            printf(RESET);

            encontrou = 1;
        }
    }

    // ---------------- FUNCIONÁRIOS ----------------
    for (int i = 0; i < total_funcionarios; i++)
    {
        if (!lista_funcionarios[i].ativo)
            continue;

        char pNome[40];
        primeiroNome(lista_funcionarios[i].nome, pNome);

        if (iguaisIgnoreCase(pNome, nomeBusca))
        {
            printf(CYAN);
            printf("%-12s | %-27s | %-13s | %-18s | %-6s\n",
                   lista_funcionarios[i].id,
                   lista_funcionarios[i].nome,
                   "FUNCIONÁRIO",
                   lista_funcionarios[i].cargo,
                   "ATIVO");
            printf(RESET);

            encontrou = 1;
        }
    }

    printf(MAGENTA BOLD "======================================================================================\n" RESET);

    if (!encontrou)
    {
        printf(RED BOLD "\nNenhuma pessoa encontrada com esse primeiro nome.\n" RESET);
    }

    printf("\nPressione ENTER para continuar...");
    getchar();
}
