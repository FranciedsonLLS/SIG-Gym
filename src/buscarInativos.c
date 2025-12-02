// buscarInativos.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui/aluno/cadastrarAluno.h"
#include "ui/aluno/arquivoAluno.h"
#include "ui/funcionario/cadastrarFuncionario.h"
#include "ui/funcionario/arquivoFuncionario.h"
#include "limparTela.h"

// Cores ANSI usadas no projeto
#define COR_TITULO "\033[1;36m"
#define COR_CABEC "\033[1;33m"
#define COR_INFO "\033[0;37m"
#define COR_AVISO "\033[1;31m"
#define COR_SUCESSO "\033[1;32m"
#define COR_OPCAO "\033[1;32m"
#define COR_RESET "\033[0m"

// ============================================================================
//      ORDENAR FUNCIONÁRIOS INATIVOS EM ORDEM INVERSA (Maior → Menor ID)
// ============================================================================
static void ordenarFuncionariosInverso(struct funcionario lista[], int total)
{
    for (int i = 0; i < total - 1; i++)
    {
        for (int j = i + 1; j < total; j++)
        {
            if (strcmp(lista[i].id, lista[j].id) < 0) // inverso
            {
                struct funcionario tmp = lista[i];
                lista[i] = lista[j];
                lista[j] = tmp;
            }
        }
    }
}

// ============================================================================
//   Função para REATIVAR aluno ou funcionário (via ID)
// ============================================================================
static void reativarRegistro(const char *id)
{
    // ---------------- TENTA REATIVAR ALUNO ----------------
    for (int i = 0; i < total_alunos; i++)
    {
        char id_aluno[32];
        strncpy(id_aluno, lista_alunos[i].id, sizeof(id_aluno));
        id_aluno[31] = '\0';

        id_aluno[strcspn(id_aluno, "\r\n")] = '\0';

        if (strcmp(id_aluno, id) == 0 && lista_alunos[i].ativo == false)
        {
            lista_alunos[i].ativo = true;
            salvarAlunos(lista_alunos, total_alunos);

            printf(COR_SUCESSO "\n>>> ALUNO reativado com sucesso!\n" COR_RESET);
            return;
        }
    }

    // ---------------- TENTA REATIVAR FUNCIONÁRIO ----------------
    for (int i = 0; i < total_funcionarios; i++)
    {
        char id_func[32];
        strncpy(id_func, lista_funcionarios[i].id, sizeof(id_func));
        id_func[31] = '\0';

        id_func[strcspn(id_func, "\r\n")] = '\0';

        if (strcmp(id_func, id) == 0 && lista_funcionarios[i].ativo == false)
        {
            lista_funcionarios[i].ativo = true;
            salvarFuncionarios(lista_funcionarios, total_funcionarios);

            printf(COR_SUCESSO "\n>>> FUNCIONÁRIO reativado com sucesso!\n" COR_RESET);
            return;
        }
    }

    printf(COR_AVISO "\n>>> Nenhum registro INATIVO encontrado com esse ID.\n" COR_RESET);
}

// ============================================================================
//                 RELATÓRIO COMPLETO + OPÇÃO DE REATIVAR
// ============================================================================
void buscarInativos(void)
{
    limparTela();

    printf(COR_TITULO);
    printf("===============================================================================\n");
    printf("===                 RELATÓRIO: REGISTROS INATIVOS (ALUNOS/FUNC.)           ===\n");
    printf("===============================================================================\n\n");
    printf(COR_RESET);

    int encontrouAlgum = 0;

    // ============================================================================
    //                               ALUNOS INATIVOS
    // ============================================================================
    printf(COR_CABEC "================================== ALUNOS INATIVOS ===========================\n" COR_RESET);
    printf(COR_CABEC "%-13s | %-28s | %-10s | %-8s\n" COR_RESET, "ID", "Nome", "Nasc.", "Plano");
    printf("-------------------------------------------------------------------------------\n");

    int encontrouAluno = 0;

    for (int i = 0; i < total_alunos; i++)
    {
        if (!lista_alunos[i].ativo)
        {
            printf("%-13s | %-28s | %-10s | %-8s\n",
                   lista_alunos[i].id,
                   lista_alunos[i].nome,
                   lista_alunos[i].idade,
                   lista_alunos[i].plano_id);

            encontrouAluno = 1;
            encontrouAlgum = 1;
        }
    }

    if (!encontrouAluno)
        printf(COR_INFO "Nenhum aluno inativo.\n" COR_RESET);

    printf("\n>>> Pressione ENTER para continuar...");
    getchar();
    limparTela();

    // ============================================================================
    //                           FUNCIONÁRIOS INATIVOS
    // ============================================================================

    // >>>>>> AQUI ORDENAMOS ANTES DE MOSTRAR <<<<<<
    ordenarFuncionariosInverso(lista_funcionarios, total_funcionarios);

    printf(COR_CABEC "============================== FUNCIONÁRIOS INATIVOS =========================\n" COR_RESET);
    printf(COR_CABEC "%-13s | %-28s | %-10s | %-12s\n" COR_RESET, "ID", "Nome", "Nasc.", "Cargo");
    printf("-------------------------------------------------------------------------------\n");

    int encontrouFunc = 0;

    for (int i = 0; i < total_funcionarios; i++)
    {
        if (!lista_funcionarios[i].ativo)
        {
            printf("%-13s | %-28s | %-10s | %-12s\n",
                   lista_funcionarios[i].id,
                   lista_funcionarios[i].nome,
                   lista_funcionarios[i].nascimento,
                   lista_funcionarios[i].cargo);

            encontrouFunc = 1;
            encontrouAlgum = 1;
        }
    }

    if (!encontrouFunc)
        printf(COR_INFO "Nenhum funcionário inativo.\n" COR_RESET);

    printf("\n-------------------------------------------------------------------------------\n");

    if (!encontrouAlgum)
    {
        printf(COR_SUCESSO ">>> Não existem registros inativos no sistema.\n" COR_RESET);
        printf("\n>>> Pressione ENTER para continuar...");
        getchar();
        limparTela();
        return;
    }

    // ============================================================================
    //                           OPÇÃO DE REATIVAR
    // ============================================================================
    printf("\n" COR_OPCAO ">>> Deseja reativar alguém? (s/n): " COR_RESET);
    char resp;
    scanf(" %c", &resp);
    getchar();

    if (resp == 's' || resp == 'S')
    {
        printf("\n>>> Digite o ID para reativar: ");
        char id[64];
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\r\n")] = '\0';

        reativarRegistro(id);
    }

    printf("\n>>> Pressione ENTER para continuar...");
    getchar();
    limparTela();
}
