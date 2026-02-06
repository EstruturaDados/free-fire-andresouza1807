#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura que representa um item do inventario
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Item;

#define MAX_ITENS 10

// Criterios de ordenacao disponiveis
typedef enum {
    ORDENACAO_NENHUMA = 0,
    ORDENACAO_NOME = 1,
    ORDENACAO_TIPO = 2,
    ORDENACAO_PRIORIDADE = 3
} CriterioOrdenacao;

// Remove o caractere de nova linha de uma string lida com fgets
static void limparNovaLinha(char *texto) {
    size_t tamanho = strlen(texto);
    if (tamanho > 0 && texto[tamanho - 1] == '\n') {
        texto[tamanho - 1] = '\0';
    }
}

// Limpa o buffer de entrada apos uso do scanf
static void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Descarta caracteres restantes
    }
}

// Insere um item no inventario
void inserirItem(Item mochila[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("Mochila cheia. NNao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("Digite o nome do item: ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    limparNovaLinha(novoItem.nome);

    printf("Digite o tipo do item (arma, municao, cura, etc.): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    limparNovaLinha(novoItem.tipo);

    printf("Digite a quantidade: ");
    if (scanf("%d", &novoItem.quantidade) != 1) {
        printf("Quantidade invalida. Operacao cancelada.\n");
        limparBufferEntrada();
        return;
    }
    limparBufferEntrada();

    printf("Digite a prioridade (1 a 5): ");
    if (scanf("%d", &novoItem.prioridade) != 1) {
        printf("Prioridade invalida. Operacao cancelada.\n");
        limparBufferEntrada();
        return;
    }
    limparBufferEntrada();

    if (novoItem.prioridade < 1) {
        novoItem.prioridade = 1;
    } else if (novoItem.prioridade > 5) {
        novoItem.prioridade = 5;
    }

    mochila[*totalItens] = novoItem;
    (*totalItens)++;

    printf("Item cadastrado com sucesso.\n");
}

// Remove um item pelo nome
void removerItem(Item mochila[], int *totalItens) {
    if (*totalItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    limparNovaLinha(nomeBusca);

    int encontrado = -1;
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item nao encontrado.\n");
        return;
    }

    for (int i = encontrado; i < *totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*totalItens)--;
    printf("Item removido com sucesso.\n");
}

// Lista todos os itens cadastrados
void listarItens(const Item mochila[], int totalItens) {
    printf("\n--- Itens na Mochila (%d/%d) ---\n", totalItens, MAX_ITENS);
    if (totalItens == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

// Busca um item pelo nome usando busca sequencial
void buscarItem(const Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item para buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    limparNovaLinha(nomeBusca);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado. Verifique o nome e tente novamente.\n");
    }
}

// Ordena a mochila usando insertion sort e conta comparacoes
void ordenarMochila(Item mochila[], int totalItens, CriterioOrdenacao criterio, int *comparacoes) {
    *comparacoes = 0;

    for (int i = 1; i < totalItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        if (criterio == ORDENACAO_NOME) {
            while (j >= 0) {
                (*comparacoes)++;
                if (strcmp(mochila[j].nome, chave.nome) > 0) {
                    mochila[j + 1] = mochila[j];
                    j--;
                } else {
                    break;
                }
            }
        } else if (criterio == ORDENACAO_TIPO) {
            while (j >= 0) {
                (*comparacoes)++;
                if (strcmp(mochila[j].tipo, chave.tipo) > 0) {
                    mochila[j + 1] = mochila[j];
                    j--;
                } else {
                    break;
                }
            }
        } else if (criterio == ORDENACAO_PRIORIDADE) {
            while (j >= 0) {
                (*comparacoes)++;
                if (mochila[j].prioridade > chave.prioridade) {
                    mochila[j + 1] = mochila[j];
                    j--;
                } else {
                    break;
                }
            }
        }

        mochila[j + 1] = chave;
    }
}

// Busca binaria por nome (requer lista ordenada por nome)
void buscarItemBinario(const Item mochila[], int totalItens, bool ordenadoPorNome) {
    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    if (!ordenadoPorNome) {
        printf("Para usar busca binaria, ordene a mochila por nome primeiro.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item para buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    limparNovaLinha(nomeBusca);

    int inicio = 0;
    int fim = totalItens - 1;
    bool encontrado = false;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int comparacao = strcmp(mochila[meio].nome, nomeBusca);

        if (comparacao == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            encontrado = true;
            break;
        }

        if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado. Verifique o nome e tente novamente.\n");
    }
}

int main(void) {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao = 0;
    CriterioOrdenacao criterioAtual = ORDENACAO_NENHUMA;
    bool ordenadoPorNome = false;

    printf("Sistema de Inventario - Mochila Inicial\n");

    while (1) {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Ordenar mochila\n");
        printf("5 - Buscar item por nome (binaria)\n");
        printf("6 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            limparBufferEntrada();
            continue;
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                criterioAtual = ORDENACAO_NENHUMA;
                ordenadoPorNome = false;
                listarItens(mochila, totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                criterioAtual = ORDENACAO_NENHUMA;
                ordenadoPorNome = false;
                listarItens(mochila, totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
            {
                int criterio = 0;
                int comparacoes = 0;
                printf("Escolha o criterio de ordenacao:\n");
                printf("1 - Nome\n");
                printf("2 - Tipo\n");
                printf("3 - Prioridade\n");
                printf("Opcao: ");

                if (scanf("%d", &criterio) != 1) {
                    printf("Entrada invalida.\n");
                    limparBufferEntrada();
                    break;
                }
                limparBufferEntrada();

                if (criterio < 1 || criterio > 3) {
                    printf("Criterio invalido.\n");
                    break;
                }

                criterioAtual = (CriterioOrdenacao)criterio;
                ordenarMochila(mochila, totalItens, criterioAtual, &comparacoes);
                ordenadoPorNome = (criterioAtual == ORDENACAO_NOME);

                printf("Mochila ordenada. Comparacoes realizadas: %d\n", comparacoes);
                listarItens(mochila, totalItens);
                break;
            }
            case 5:
                buscarItemBinario(mochila, totalItens, ordenadoPorNome);
                listarItens(mochila, totalItens);
                break;
            case 6:
                printf("Encerrando o sistema.\n");
                return 0;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }

    return 0;
}
