#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura que representa um item do inventario
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

#define MAX_ITENS 10

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
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
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

int main(void) {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao = 0;

    printf("Sistema de Inventario - Mochila Inicial\n");

    while (1) {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome\n");
        printf("5 - Sair\n");
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
                listarItens(mochila, totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                listarItens(mochila, totalItens);
                break;
            case 5:
                printf("Encerrando o sistema.\n");
                return 0;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }

    return 0;
}
