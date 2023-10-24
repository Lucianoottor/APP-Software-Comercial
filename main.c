// Tema: Rede UP - Pedidos de Eletrônicos e Periféricos 
// Structs - Clientes, Enderecos, Produtos
// Painéis - Cadastrar conta, Excluir/Desativar conta, Realizar pedido, Verificar conta, Acompanhar pedido, Verificar Estoque
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir as structs
struct enderecos {
    char CEP[15];
    char strEstado[3];
    char strCidade[30];
    char strBairro[30];
    char strRua[30];
    int num_res;
};

struct produtos {
    int codigo_produto;
    char nome_produto[100];
    float preco_produto;
    int quantidade_produto;
};

struct clientes {
    int id_cliente;
    char nome_cliente[100];
    char email_cliente[100];
    char cpf_cliente[15];
    struct enderecos strEndereco;  
};

// Funções do programa
void cadastrarConta(struct clientes *Clientes, int *numClientes, struct enderecos *Enderecos) {
    struct clientes *novo_cliente = (struct clientes*)realloc(Clientes, (*numClientes + 1) * sizeof(struct clientes));
    struct enderecos *novo_endereco = (struct enderecos*)realloc(Clientes, (*numClientes + 1) * sizeof(struct enderecos));

    printf("Digite o nome do cliente: \n");
    scanf("%s", Clientes[*numClientes - 1].nome_cliente);
    printf("Digite o e-mail do cliente: \n");
    scanf("%s", Clientes[*numClientes - 1].email_cliente);
    printf("Digite o CPF do cliente: \n");
    scanf("%s", Clientes[*numClientes - 1].cpf_cliente);
    printf("Digite o CEP: \n");
    scanf("%s", Enderecos[*numClientes -1].CEP);
    printf("Insira a UF (unidade federal): \n");
    scanf("%s", Enderecos[*numClientes -1].strEstado);
    printf("Insira a cidade: \n");
    scanf("%s", Enderecos[*numClientes -1].strCidade);
    printf("Insira o bairro: \n");
    scanf("%s", Enderecos[*numClientes -1].strBairro);
    printf("Insira o logradouro: \n");
    scanf("%s", Enderecos[*numClientes -1].strRua);
    printf("Insira o número da residência: \n");
    scanf("%d", Enderecos[*numClientes -1].num_res);

    FILE *banco_de_dados = fopen("banco_de_dados.txt", "a+");
    fprintf(banco_de_dados, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n", Clientes[*numClientes - 1].nome_cliente, 
                                                                    Clientes[*numClientes - 1].email_cliente, 
                                                                    Clientes[*numClientes - 1].cpf_cliente, 
                                                                    Enderecos[*numClientes - 1].CEP,
                                                                    Enderecos[*numClientes - 1].strEstado,
                                                                    Enderecos[*numClientes - 1].strCidade,
                                                                    Enderecos[*numClientes - 1].strBairro,
                                                                    Enderecos[*numClientes - 1].strRua,
                                                                    Enderecos[*numClientes - 1].num_res);
    fclose(banco_de_dados);

    printf("Cliente cadastrado com sucesso!\n");
}


void excluirConta(struct clientes Clientes[], int *numClientes) {
    char *consulta_cpf;
    printf("Digite o CPF do cliente que será excluído: \n");
    scanf("%s", consulta_cpf);
    
    FILE *banco_de_dados = fopen("banco_de_dados.txt", "a+");
    if(fgets(consulta_cpf, sizeof(consulta_cpf), banco_de_dados));
}

void realizarPedido(struct clientes Clientes[], int numClientes, struct produtos Produtos[], int numProdutos) {

}

void verificarConta(struct clientes Clientes[], int numClientes) {
  
}


void acompanharPedido(struct clientes Clientes[], int numClientes) {
 
}

void adicionarEstoque(struct produtos Produtos[], int numProdutos){
}

void verificarEstoque(struct produtos Produtos[], int numProdutos) {
}

int main() {

    // Passagem de parâmetros

    struct enderecos *Enderecos = (struct enderecos*)malloc(sizeof(struct enderecos));
    struct produtos *Produtos = (struct produtos*)malloc(sizeof(struct produtos));
    struct clientes *Clientes = (struct clientes*)malloc(sizeof(struct clientes));
    int numClientes = 0;
    int numProdutos = 0;
    
    // Menu da da aplicação
    int input_usuario;
    do {
        printf("\n=== Rede UP - Pedidos de Eletrônicos e Periféricos ===\n");
        printf("1. Cadastrar Conta\n");
        printf("2. Excluir/Desativar Conta\n");
        printf("3. Realizar Pedido\n");
        printf("4. Verificar Conta\n");
        printf("5. Acompanhar Pedido\n");
        printf("6. Verificar Estoque\n");
        printf("7. Aumentar Estoque\n");
        printf("0. Sair\n");
        printf("Selecione uma opção: ");
        scanf("%d", &input_usuario);
        
        switch(input_usuario) {
            case 1:
                cadastrarConta(Clientes, &numClientes, Enderecos);
                break;
            case 2:
                excluirConta(Clientes, &numClientes);
                break;
            case 3:
                realizarPedido(Clientes, numClientes, Produtos, numProdutos);
                break;
            case 4:
                verificarConta(Clientes, numClientes);
                break;
            case 5:
                acompanharPedido(Clientes, numClientes);
                break;
            case 6:
                verificarEstoque(Produtos, numProdutos);
                break;
            case 7:
                adicionarEstoque(Produtos, numProdutos);
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!!!\n");
        }
    } while (input_usuario != 0);

    free(Enderecos);
    free(Clientes);
    free(Produtos);
    
    return 0;
}
