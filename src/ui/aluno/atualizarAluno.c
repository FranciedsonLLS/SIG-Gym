#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "limparTela.h"
#include "cadastrarAluno.h"
#include "src/ui/plano/cadastrarPlano.h"
#include "src/ui/utils/validarNome.h"
#include "src/ui/utils/validarCPF.h"
#include "src/ui/utils/validarNascimento.h"
#include "src/ui/utils/validarTelefone.h"
#include "src/ui/utils/validarEndereco.h"
#include "src/ui/utils/validarEmail.h"
#include "arquivoAluno.h"

void limparBufferEntrada(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void telaAtualizarAluno(void)
{
    if (total_alunos == 0)
    {
        limparTela();
        printf("=========================================================================\n");
        printf("===                        ATUALIZAR ALUNO                            ===\n");
        printf("=========================================================================\n");
        printf("===                       NENHUM ALUNO CADASTRADO                     ===\n");
        printf("=========================================================================\n");
        getchar();
        limparTela();
        return;
    }

    limparTela();
    printf("=========================================================================\n");
    printf("===                        ATUALIZAR ALUNO                            ===\n");
    printf("=========================================================================\n");

    for (int i = 0; i < total_alunos; i++)
    {
        if (lista_alunos[i].ativo)
        {
            printf("[%s] %s\n", lista_alunos[i].id, lista_alunos[i].nome);
        }
    }

    printf("=========================================================================\n");
    printf("===                        DIGITE O ID                                ===\n");
    printf("=========================================================================\n");
    char id_busca[1024];
    fgets(id_busca, sizeof(id_busca), stdin);
    id_busca[strcspn(id_busca, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < total_alunos; i++)
    {
        if (strcmp(lista_alunos[i].id, id_busca) == 0 && lista_alunos[i].ativo)
        {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1)
    {
        limparTela();
        printf("=========================================================================\n");
        printf("===                        ATUALIZAR ALUNO                            ===\n");
        printf("=========================================================================\n");
        printf("===                       ID  NAO  ENCONTRADO                         ===\n");
        printf("=========================================================================\n");
        getchar();
        limparTela();
        return;
    }

    struct aluno *aluno_sel = &lista_alunos[encontrado];
    char buffer[MAX_BUFFER];
    char opcao;

    do
    {
        limparTela();
        printf("=========================================================================\n");
        printf("===                        ATUALIZAR ALUNO                            ===\n");
        printf("=========================================================================\n");
        printf("Aluno selecionado: %s (%s)\n", aluno_sel->nome, aluno_sel->id);
        printf("Escolha o campo para atualizar:\n");
        printf("[1] Nome\n");
        printf("[2] Data de nascimento\n");
        printf("[3] CPF\n");
        printf("[4] Telefone\n");
        printf("[5] Endereco\n");
        printf("[6] Email\n");
        printf("[7] Plano\n");
        printf("[0] Voltar\n");
        printf("=========================================================================\n");
        scanf(" %c", &opcao);
        limparBufferEntrada();

        switch (opcao)
        {
        case '1': // Nome
        {
            bool nomeValido = false;
            do
            {
                limparTela();
                printf("=== Nome atual: %s ===\n", aluno_sel->nome);
                printf("Digite o novo nome:\n>>> ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                if (validarNome(buffer))
                {
                    strcpy(aluno_sel->nome, buffer);
                    nomeValido = true;
                }
                else
                {
                    printf("Nome inválido. Apenas letras e espaços.\n");
                    printf(">>> Pressione ENTER...");
                    getchar();
                }
            } while (!nomeValido);

            atualizarAlunoNoArquivo(*aluno_sel);
            break;
        }

        case '2': // Data
        {
            bool dataValida = false;
            do
            {
                limparTela();
                printf("=== Data atual: %s ===\n", aluno_sel->idade);
                printf("Digite nova data (DD/MM/AAAA):\n>>> ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                if (validarNascimento(buffer))
                {
                    strcpy(aluno_sel->idade, buffer);
                    dataValida = true;
                }
                else
                {
                    printf("Data inválida!\n>>> Pressione ENTER...");
                    getchar();
                }
            } while (!dataValida);

            atualizarAlunoNoArquivo(*aluno_sel);
            break;
        }

        case '3': // CPF
        {
            bool cpfValido = false;
            do
            {
                limparTela();
                printf("=== CPF atual: %s ===\n", aluno_sel->cpf);
                printf("Digite novo CPF:\n>>> ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                if (validarCPF(buffer))
                {
                    strcpy(aluno_sel->cpf, buffer);
                    cpfValido = true;
                }
                else
                {
                    printf("CPF inválido!\n>>> Pressione ENTER...");
                    getchar();
                }
            } while (!cpfValido);

            atualizarAlunoNoArquivo(*aluno_sel);
            break;
        }

        case '4': // Telefone
        {
            bool ok = false;
            do
            {
                limparTela();
                printf("=== Telefone atual: %s ===\n", aluno_sel->telefone);
                printf("Digite telefone:\n>>> ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                if (validarTelefone(buffer))
                {
                    strcpy(aluno_sel->telefone, buffer);
                    ok = true;
                }
                else
                {
                    printf("Telefone inválido!\n>>> Pressione ENTER...");
                    getchar();
                }
            } while (!ok);

            atualizarAlunoNoArquivo(*aluno_sel);
            break;
        }

        case '5': // Endereco
        {
            bool ok = false;
            do
            {
                limparTela();
                printf("=== Endereco atual: %s ===\n", aluno_sel->endereco);
                printf("Digite endereço:\n>>> ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                if (validarEndereco(buffer))
                {
                    strcpy(aluno_sel->endereco, buffer);
                    ok = true;
                }
                else
                {
                    printf("Endereco inválido!\n>>> Pressione ENTER...");
                    getchar();
                }
            } while (!ok);

            atualizarAlunoNoArquivo(*aluno_sel);
            break;
        }

        case '6': // Email
        {
            bool ok = false;
            do
            {
                limparTela();
                printf("=== Email atual: %s ===\n", aluno_sel->email);
                printf("Digite novo e-mail:\n>>> ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                if (validarEmail(buffer))
                {
                    strcpy(aluno_sel->email, buffer);
                    ok = true;
                }
                else
                {
                    printf("Email inválido!\n>>> Pressione ENTER...");
                    getchar();
                }
            } while (!ok);

            atualizarAlunoNoArquivo(*aluno_sel);
            break;
        }

        case '7': // Atualização do PLANO (usando lista_planos / total_planos)
        {
            if (total_planos == 0)
            {
                limparTela();
                printf("=========================================================================\n");
                printf("===                       NENHUM PLANO CADASTRADO                     ===\n");
                printf("=========================================================================\n");
                printf(">>> Pressione ENTER...");
                getchar();
                break;
            }

            limparTela();
            printf("=========================================================================\n");
            printf("===                        ATUALIZAR PLANO                            ===\n");
            printf("=========================================================================\n");
            printf("Aluno: %s (%s)\n", aluno_sel->nome, aluno_sel->id);
            printf("Plano atual: %s\n\n", aluno_sel->plano_id);

            printf("Planos disponíveis:\n");
            for (int i = 0; i < total_planos; i++)
            {
                printf("[%s] %s (%s às %s)\n",
                       lista_planos[i].id,
                       lista_planos[i].nome,
                       lista_planos[i].horario_inicio,
                       lista_planos[i].horario_fim);
            }

            printf("\nDigite o ID do novo plano:\n>>> ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';

            int idx = -1;
            for (int i = 0; i < total_planos; i++)
            {
                if (strcmp(lista_planos[i].id, buffer) == 0)
                {
                    idx = i;
                    break;
                }
            }

            if (idx == -1)
            {
                printf("Plano não encontrado!\n>>> Pressione ENTER...");
                getchar();
                break;
            }

            strcpy(aluno_sel->plano_id, lista_planos[idx].id);
            atualizarAlunoNoArquivo(*aluno_sel);

            printf("\nPlano atualizado com sucesso!\n>>> Pressione ENTER...");
            getchar();
            break;
        }

        case '0':
            break;

        default:
            printf("Opção inválida!\n>>> Pressione ENTER...");
            getchar();
        }

        /* Mensagem genérica de sucesso para as opções válidas (1..7),
           exceto quando já foi exibida mensagem/prompt dentro do case */
        if (opcao >= '1' && opcao <= '7')
        {
            limparTela();
            printf("=========================================================================\n");
            printf("===                    CAMPO ATUALIZADO COM SUCESSO                   ===\n");
            printf("=========================================================================\n");
            printf(">>> Pressione ENTER...");
            getchar();
        }

    } while (opcao != '0');

    limparTela();
}
