// Tema: Rede UP - Pedidos de Eletrônicos e Periféricos 
// Structs - Clientes, Enderecos, Produtos
// Painéis - Cadastrar conta, Excluir/Desativar conta, Realizar pedido, Verificar conta, Acompanhar pedido, Verificar Estoque
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tam 1

// Definir as structs
struct enderecos {
    char CEP[20];
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
    char cpf_cliente[15];
    char nome_cliente[100];
    char email_cliente[100];
    struct enderecos strEndereco;  
};

// Funções do programa

// Limpador de buffer
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Validador de CPF
int validarCPF(const char *cpf) {

    if (strlen(cpf) != 11){
        return 0;
    }
    int i;
    for (i = 1; i < 11; i++) {
        if (cpf[i] != cpf[0])
            break;
    }
    if (i == 11){
        return 0;
    }

    int digito1 = 0, digito2 = 0;
    for (i = 0; i < 9; i++){
        digito1 += (cpf[i] - '0') * (10 - i);
        digito2 += (cpf[i] - '0') * (11 - i);
    }
    digito1 = (digito1 * 10) % 11;
    if (digito1 == 10){
        digito1 = 0;
    }
    digito2 += digito1 * 2;
    digito2 = (digito2 * 10) % 11;
    if (digito2 == 10){
        digito2 = 0;
    }
    return (digito1 == cpf[9] - '0' && digito2 == cpf[10] - '0');
}

// Função para Cadastrar Conta
void cadastrarConta(struct clientes *Clientes, struct enderecos *Enderecos, int *numClientes) {
    struct clientes *novo_cliente = (struct clientes*)realloc(Clientes, (*numClientes + 1) * sizeof(struct clientes));
    struct enderecos *novo_endereco = (struct enderecos*)realloc(Enderecos, (*numClientes + 1) * sizeof(struct enderecos));

    FILE *banco_de_dados = fopen("banco_de_dados.txt", "a+");

    if (banco_de_dados == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    limparBufferEntrada();

    // CPF com validador
    printf("Digite o CPF do cliente: \n");
    while(fgets(Clientes[*numClientes].cpf_cliente, sizeof(Clientes[*numClientes].cpf_cliente), stdin)){
        Clientes[*numClientes].cpf_cliente[strcspn(Clientes[*numClientes].cpf_cliente, "\n")] = '\0';
        if(validarCPF(Clientes[*numClientes].cpf_cliente) == 0){
            printf("Digite um CPF válido!\n");
        }else{
            fprintf(banco_de_dados, "CPF: %s\n", Clientes[*numClientes].cpf_cliente);
            printf("-----------------------\n");
            break;
        }
    }

    // Nome
    printf("Digite o nome do cliente: \n");
    fgets(Clientes[*numClientes].nome_cliente, sizeof(Clientes[*numClientes].nome_cliente), stdin);
    strtok(Clientes[*numClientes].nome_cliente, "\n");
    fprintf(banco_de_dados, "NOME: %s\n", Clientes[*numClientes].nome_cliente);
    printf("-----------------------\n");

    // Email
    printf("Digite o e-mail do cliente: \n");
    fgets(Clientes[*numClientes].email_cliente, sizeof(Clientes[*numClientes].email_cliente), stdin);
    strtok(Clientes[*numClientes].email_cliente, "\n");
    fprintf(banco_de_dados, "E-MAIL: %s\n", Clientes[*numClientes].email_cliente);
    printf("-----------------------\n");

    // CEP
    printf("Digite o CEP: \n");
    fgets(Enderecos[*numClientes].CEP, sizeof(Enderecos[*numClientes].CEP), stdin);
    strtok(Enderecos[*numClientes].CEP, "\n");
    fprintf(banco_de_dados, "CEP: %s\n", Enderecos[*numClientes].CEP);
    printf("-----------------------\n");

    // UF
    printf("Insira a UF (unidade federal): \n");
    fgets(Enderecos[*numClientes].strEstado, sizeof(Enderecos[*numClientes].strEstado), stdin);
    limparBufferEntrada();
    strtok(Enderecos[*numClientes].strEstado, "\n");
    fprintf(banco_de_dados, "UF: %s\n", Enderecos[*numClientes].strEstado);
    printf("-----------------------\n");

    // Cidade
    printf("Insira a cidade: \n");
    fgets(Enderecos[*numClientes].strCidade, sizeof(Enderecos[*numClientes].strCidade), stdin);
    strtok(Enderecos[*numClientes].strCidade, "\n");
    fprintf(banco_de_dados, "CIDADE: %s\n", Enderecos[*numClientes].strCidade);
    printf("-----------------------\n");

    // Bairro
    printf("Insira o bairro: \n");
    fgets(Enderecos[*numClientes].strBairro, sizeof(Enderecos[*numClientes].strBairro), stdin);
    strtok(Enderecos[*numClientes].strBairro, "\n");
    fprintf(banco_de_dados, "BAIRRO: %s\n", Enderecos[*numClientes].strBairro);
    printf("-----------------------\n");
    
    // Logradouro/rua
    printf("Insira o logradouro: \n");
    fgets(Enderecos[*numClientes].strRua, sizeof(Enderecos[*numClientes].strRua), stdin);
    strtok(Enderecos[*numClientes].strRua, "\n");
    fprintf(banco_de_dados, "LOGRADOURO: %s\n", Enderecos[*numClientes].strRua);
    printf("-----------------------\n");

    // Número de residência
    printf("Insira o número: \n");
    scanf("%d", &Enderecos[*numClientes].num_res);
    fprintf(banco_de_dados, "NÚMERO: %d\n", Enderecos[*numClientes].num_res);
    fclose(banco_de_dados);
    printf("Cliente cadastrado com sucesso!\n");
}

// Função excluirConta
void excluirConta(const char *arquivo) {

    // Input usuario
    int input_usuario;
    printf("Deseja excluir conta (1) ou desativar conta (2)?\n");
    scanf("%d", &input_usuario);

    // Desativar Conta
    if(input_usuario == 1){

    // Input do cpf
    char cpf[15];
    printf("Digite o CPF a ser excluído: ");
    scanf("%s", cpf);

    // Abrir arquivo que será lido
    FILE *banco_de_dados = fopen(arquivo, "r");
    if (banco_de_dados == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    // Criação de arquivo temporário para deletar conta
    char arquivoTemporario[] = "temp.txt";
    FILE *arquivoTemp = fopen(arquivoTemporario, "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(banco_de_dados);
        return;
    }

    // Indicadores para exclusão do cpf
    char linha[100];
    int excluir = 0; 
    int encontrado = 0; 

    // Algoritmo de exclusão
    while (fgets(linha, sizeof(linha), banco_de_dados)) {
        if (strstr(linha, cpf) != NULL) {
            excluir = 1;
            encontrado = 1;
        }
        if (!excluir) {
            fputs(linha, arquivoTemp);
        }

        if (strstr(linha, "NÚMERO: ")) {
            excluir = 0;
        }
    }

    // Encerrar subrotina
    fclose(banco_de_dados);
    fclose(arquivoTemp);

    remove(arquivo);
    rename(arquivoTemporario, arquivo);

    if (!encontrado) {
        printf("CPF não encontrado.\n");
        return;
    } else {
        printf("Conta excluída com sucesso!\n");
    }
    }
    /*else{
        // Código de desativação de conta
    }*/
}



/*
void realizarPedido(struct clientes Clientes[], int numClientes, struct produtos Produtos[], int numProdutos) {

}*/

void verificarConta(const char *arquivo) {

    // Input de CPF
    char cpf[15];
    printf("Digite o CPF da conta a ser localizada: \n");
    while(scanf("%s", cpf)){
        if(validarCPF(cpf) == 0){
            printf("CPF inválido, insira novamente: \n");
        }
        else{
            break;
        }
    }

    // Abrir o arquivo
    FILE *banco_de_dados = fopen(arquivo, "r");
    if (banco_de_dados == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    // Indicadores
    char linha[100];
    int imprimir = 0;
    int encontrou = 0;

    // Algoritmo para impressão
    while (fgets(linha, sizeof(linha), banco_de_dados)) {
        if (strstr(linha, "CPF: ") != NULL && strstr(linha, cpf) != NULL) {
            imprimir = 1;
            encontrou = 1;
        }
        if (encontrou) {
            printf("%s", linha);
        }
        if (strstr(linha, "NÚMERO: ") != NULL) {
            imprimir = 0;
            break;
        }
    }

    // Encerramento da subrotina
    fclose(banco_de_dados);

    if (encontrou == 0) {
        printf("Conta não encontrada.\n");
    }
}

/*
void acompanharPedido(struct clientes Clientes[], int numClientes) {
 
}

void adicionarEstoque(struct produtos Produtos[], int numProdutos){
}

void verificarEstoque(struct produtos Produtos[], int numProdutos) {
}
*/

int main() {

    // Passagem de parâmetros
    struct enderecos *Enderecos = (struct enderecos*)malloc(tam * sizeof(struct enderecos));
    struct produtos *Produtos = (struct produtos*)malloc(tam * sizeof(struct produtos));
    struct clientes *Clientes = (struct clientes*)malloc(tam * sizeof(struct clientes));
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
                cadastrarConta(Clientes, Enderecos, &numClientes);
                break;
            case 2:
                excluirConta("banco_de_dados.txt");
                break;
            /*case 3:
                realizarPedido(Clientes, numClientes, Produtos, numProdutos);
                break;*/
            case 4:
                verificarConta("banco_de_dados.txt");
                break;
            /*case 5:
                acompanharPedido(Clientes, numClientes);
                break;
            case 6:
                verificarEstoque(Produtos, numProdutos);
                break;
            case 7:
                adicionarEstoque(Produtos, numProdutos);
                break;*/
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
