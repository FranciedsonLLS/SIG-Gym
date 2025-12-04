#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // strcasecmp()
#include <ctype.h>   // tolower()

#include "ui/aluno/cadastrarAluno.h"
#include "ui/plano/cadastrarPlano.h"
#include "limparTela.h"

// Cores ANSI
#define COR_TITULO "\033[1;36m"
#define COR_VERDE "\033[1;32m"
#define COR_VERMELHO "\033[1;31m"
#define COR_AMARELO "\033[1;33m"
#define COR_RESET "\033[0m"

// ======================================================================
//  FUNÇÃO LOCAL: REMOVE \n, ESPAÇOS E ACENTOS (NÃO CONFLITA COM OUTROS .c)
// ======================================================================
static void limparString(char *str)
{
    // Remove quebra de linha
    str[strcspn(str, "\n")] = '\0';

    // Remove espaços no início
    while (*str == ' ')
    {
        memmove(str, str + 1, strlen(str));
    }

    // Remove espaços no final
    while (strlen(str) > 0 && str[strlen(str) - 1] == ' ')
    {
        str[strlen(str) - 1] = '\0';
    }

    // Remove acentos (normalização básica)
    static const char acentos[] = "áàâãäÁÀÂÃÄéèêëÉÈÊËíìîïÍÌÎÏóòôõöÓÒÔÕÖúùûüÚÙÛÜçÇ";
    static const char sem_acentos[] = "aaaaaAAAAAeeeeEEEEiiiiIIIIoooooOOOOOuuuuUUUUcC";

    for (int i = 0; i < strlen(str); i++)
    {
        char *p = strchr(acentos, str[i]);
        if (p)
        {
            int index = p - acentos;
            str[i] = sem_acentos[index];
        }
    }
}

// ======================================================================
//  COMPARAÇÃO SEM ACENTOS + CASE-INSENSITIVE
// ======================================================================
static int compararStrings(const char *a, const char *b)
{
    char A[256], B[256];
    strncpy(A, a, 255);
    strncpy(B, b, 255);
    A[255] = '\0';
    B[255] = '\0';

    limparString(A);
    limparString(B);

    return strcasecmp(A, B);
}

// ======================================================================
//  FUNÇÃO PRINCIPAL: BUSCAR ALUNOS POR PLANO (ORDENADO ALFABÉTICO)
// ======================================================================
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
    limparString(plano_busca);

    printf("\n");

    char nome_plano_encontrado[MAX_BUFFER] = "DESCONHECIDO";
    int plano_existe = 0;

    for (int i = 0; i < total_planos; i++)
    {
        if (lista_planos[i].ativo && compararStrings(lista_planos[i].id, plano_busca) == 0)
        {
            strcpy(nome_plano_encontrado, lista_planos[i].nome);
            limparString(nome_plano_encontrado);
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

    struct aluno **alunosEncontrados = NULL;
    int qtd = 0;

    if (total_alunos > 0)
    {
        alunosEncontrados = malloc(sizeof(struct aluno *) * total_alunos);
        if (!alunosEncontrados)
        {
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
            compararStrings(lista_alunos[i].plano_id, plano_busca) == 0)
        {
            limparString(lista_alunos[i].nome);
            alunosEncontrados[qtd++] = &lista_alunos[i];
        }
    }

    // ORDENAR
    if (qtd > 1)
    {
        for (int i = 0; i < qtd - 1; i++)
        {
            for (int j = 0; j < qtd - i - 1; j++)
            {
                if (compararStrings(alunosEncontrados[j]->nome,
                                    alunosEncontrados[j + 1]->nome) > 0)
                {
                    struct aluno *tmp = alunosEncontrados[j];
                    alunosEncontrados[j] = alunosEncontrados[j + 1];
                    alunosEncontrados[j + 1] = tmp;
                }
            }
        }
    }

    // ==========================================
    //           PRINTAR RESULTADOS
    // ==========================================
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
            printf("%-13s | %-25s | %-10s | %-13s | %s%-7s%s\n",
                   a->id,
                   a->nome,
                   a->idade,
                   a->telefone,
                   a->ativo ? COR_VERDE : COR_VERMELHO,
                   a->ativo ? "ATIVO" : "INATIVO",
                   COR_RESET);
        }
    }

    printf("-------------------------------------------------------------------------------\n");

    printf(COR_TITULO);
    printf("\nTotal de alunos no plano '%s': %d\n", nome_plano_encontrado, qtd);
    printf(COR_RESET);

    free(alunosEncontrados);

    printf("\n>>> Pressione <ENTER> para continuar...");
    getchar();
    limparTela();
}
