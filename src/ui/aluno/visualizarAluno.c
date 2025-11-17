#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "limparTela.h"
#include "cadastrarAluno.h"
#include "src/ui/plano/cadastrarPlano.h"

void telaVisualizarAluno(void)
{
    if (total_alunos == 0)
    {
        limparTela();
        printf("=========================================================================\n");
        printf("===                        VISUALIZAR ALUNO                           ===\n");
        printf("=========================================================================\n");
        printf("===                      NENHUM ALUNO CADASTRADO                      ===\n");
        printf("=========================================================================\n");
        getchar();
        limparTela();
        return;
    }

    limparTela();
    printf("=========================================================================\n");
    printf("===                        VISUALIZAR ALUNO                           ===\n");
    printf("=========================================================================\n");

    // ---------- TABELA ALINHADA ----------
    printf("\n%-12s | %-35s | %-10s\n", "ID", "NOME", "STATUS");
    printf("-------------------------------------------------------------------------------\n");

    int algum_ativo = 0;
    for (int i = 0; i < total_alunos; i++)
    {
        if (lista_alunos[i].ativo)
        {
            printf("%-12s | %-35s | %-10s\n",
                   lista_alunos[i].id,
                   lista_alunos[i].nome,
                   "ATIVO");

            algum_ativo = 1;
        }
    }

    printf("-------------------------------------------------------------------------------\n");

    if (!algum_ativo)
    {
        printf("===                 NENHUM ALUNO ATIVO ENCONTRADO                    ===\n");
        printf("=========================================================================\n");
        getchar();
        limparTela();
        return;
    }

    // ---------- BUSCA ----------
    printf("\n>>> Digite o ID do aluno que deseja visualizar: ");
    char id_busca[1024];
    fgets(id_busca, sizeof(id_busca), stdin);
    id_busca[strcspn(id_busca, "\r\n")] = '\0';

    int encontrado = 0;

    for (int i = 0; i < total_alunos; i++)
    {
        if (strcmp(lista_alunos[i].id, id_busca) == 0 && lista_alunos[i].ativo)
        {
            limparTela();
            printf("=========================================================================\n");
            printf("===                        INFORMAÇÕES DO ALUNO                       ===\n");
            printf("=========================================================================\n");

            // ---------- DETALHES ALINHADOS EM 2 COLUNAS ----------
            printf("%-22s : %s\n", "ID", lista_alunos[i].id);
            printf("%-22s : %s\n", "Nome", lista_alunos[i].nome);
            printf("%-22s : %s\n", "Data de nascimento", lista_alunos[i].idade);
            printf("%-22s : %s\n", "CPF", lista_alunos[i].cpf);
            printf("%-22s : %s\n", "Telefone", lista_alunos[i].telefone);
            printf("%-22s : %s\n", "Endereço", lista_alunos[i].endereco);
            printf("%-22s : %s\n", "Email", lista_alunos[i].email);

            // Plano
            char nome_plano[MAX_BUFFER] = "Nenhum";
            if (strcmp(lista_alunos[i].plano_id, "0") != 0)
            {
                for (int j = 0; j < total_planos; j++)
                {
                    if (lista_planos[j].ativo &&
                        strcmp(lista_planos[j].id, lista_alunos[i].plano_id) == 0)
                    {
                        strcpy(nome_plano, lista_planos[j].nome);
                        break;
                    }
                }
            }

            printf("%-22s : %s\n", "Plano associado", nome_plano);

            printf("=========================================================================\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("=========================================================================\n");
        printf("===                      NENHUM ALUNO ENCONTRADO                      ===\n");
        printf("=========================================================================\n");
    }

    getchar();
    limparTela();
}
