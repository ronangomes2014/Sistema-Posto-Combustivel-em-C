#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_VENDAS 100

// Estrutura para representar um cliente
typedef struct {
    char placa[10];
} Cliente;

// Estrutura para representar uma transação de venda
typedef struct {
    char placaCliente[10];
    double litros;
    double precoLitro;
    double valor;
} Venda;

// Estrutura para representar o tipo de combustível
typedef enum {
    GASOLINA,
    ALCOOL,
    DIESEL
} TipoCombustivel;

// Função para adicionar um novo cliente
void adicionarCliente(Cliente clientes[], int* numClientes) {
    if (*numClientes == MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }

    printf("Digite a placa do veiculo: ");
    scanf("%s", clientes[*numClientes].placa);

    (*numClientes)++;
    printf("Cliente adicionado com sucesso!\n");
}

// Função para registrar uma venda
void registrarVenda(Venda vendas[], Cliente clientes[], int* numVendas, int numClientes, double precos[], TipoCombustivel tipo) {
    if (numClientes == 0) {
        printf("Nenhum cliente cadastrado. Por favor, adicione um cliente antes de registrar uma venda.\n");
        return;
    }

    if (*numVendas == MAX_VENDAS) {
        printf("Limite de vendas atingido.\n");
        return;
    }

    char placa[10];
    printf("Digite a placa do veiculo: ");
    scanf("%s", placa);

    int clienteEncontrado = 0;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].placa, placa) == 0) {
            clienteEncontrado = 1;
            strcpy(vendas[*numVendas].placaCliente, placa);
            printf("Digite a quantidade de litros vendidos: ");
            scanf("%lf", &vendas[*numVendas].litros);
            vendas[*numVendas].precoLitro = precos[tipo];
            vendas[*numVendas].valor = vendas[*numVendas].litros * vendas[*numVendas].precoLitro;
            (*numVendas)++;
            printf("Venda registrada com sucesso!\n");
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

// Função para exibir o relatório de vendas
void exibirRelatorio(Venda vendas[], int numVendas) {
    if (numVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    printf("Relatorio de Vendas:\n");
    for (int i = 0; i < numVendas; i++) {
        printf("Placa do veiculo: %s\n", vendas[i].placaCliente);
        printf("Litros vendidos: %.2lf\n", vendas[i].litros);
        printf("Preco do litro: R$ %.2lf\n", vendas[i].precoLitro);
        printf("Valor total da venda: R$ %.2lf\n", vendas[i].valor);
        printf("------------------------\n");
    }
}

int main() {
    Cliente clientes[MAX_CLIENTES];
    Venda vendas[MAX_VENDAS];
    int numClientes = 0;
    int numVendas = 0;
    double precos[3]; // Preços para gasolina, álcool e diesel
    int opcao;

    printf("Digite o preco da gasolina: ");
    scanf("%lf", &precos[GASOLINA]);
    printf("Digite o preco do alcool: ");
    scanf("%lf", &precos[ALCOOL]);
    printf("Digite o preco do diesel: ");
    scanf("%lf", &precos[DIESEL]);

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar cliente\n");
        printf("2. Registrar venda (Gasolina)\n");
        printf("3. Registrar venda (Alcool)\n");
        printf("4. Registrar venda (Diesel)\n");
        printf("5. Exibir relatorio de vendas\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarCliente(clientes, &numClientes);
                break;
            case 2:
                registrarVenda(vendas, clientes, &numVendas, numClientes, precos, GASOLINA);
                break;
            case 3:
                registrarVenda(vendas, clientes, &numVendas, numClientes, precos, ALCOOL);
                break;
            case 4:
                registrarVenda(vendas, clientes, &numVendas, numClientes, precos, DIESEL);
                break;
            case 5:
                exibirRelatorio(vendas, numVendas);
                break;
            case 6:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 6);

    return 0;
}
