// Tema: Rede UP - Pedidos de Eletrônicos e Periféricos 
// Structs - Clientes, Enderecos, Produtos
// Painéis - Cadastrar conta, Excluir/Desativar conta, Realizar pedido, Verificar conta, Acompanhar pedido, Verificar Estoque
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define tam 1

// Definir as structs
struct enderecos {
    int CEP;
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

// Função de comparação para a ordenação alfabética
int compararClientes(const void *a, const void *b) {
    return strcmp(((struct clientes*)a)->nome_cliente, ((struct clientes*)b)->nome_cliente);
}

void listarClientes(const char *arquivo, struct clientes *listaClientes, int numClientes) {
    FILE *banco_de_dados = fopen(arquivo, "r");
    if (banco_de_dados == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    char linha[100];
    int i = 0;

    // Ler o arquivo linha por linha
    while (fgets(linha, sizeof(linha), banco_de_dados) != NULL) {
        // Procurar pelo campo "NOME:"
        if (strstr(linha, "NOME:") != NULL) {
            // Extrair o valor do campo "NOME:"
            sscanf(linha, "NOME: %[^\n]", listaClientes[i].nome_cliente);
            i++;
        }
        // Adicionar lógica para extrair outros campos se necessário
    }

    // Fechar o arquivo
    fclose(banco_de_dados);

    // Ordenar os clientes em ordem alfabética
    qsort(listaClientes, i, sizeof(struct clientes), compararClientes);
    printf("\n===================\n");

    for (int j = 0; j < i; j++) {
        printf("Nome: %s\n", listaClientes[j].nome_cliente);
    }
    printf("\n===================\n");
}

// Função para Cadastrar Conta
void cadastrarConta(struct clientes *Clientes, struct enderecos *Enderecos, int *numClientes) {
    struct clientes *novo_cliente = (struct clientes*)realloc(Clientes, (*numClientes + 1) * sizeof(struct clientes));
    struct enderecos *novo_endereco = (struct enderecos*)realloc(Enderecos, (*numClientes + 1) * sizeof(struct enderecos));

    FILE *banco_de_dados = fopen("banco_de_dados.txt", "a");

    if (banco_de_dados == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    limparBufferEntrada();
    rewind(banco_de_dados);
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
    scanf("%d", &Enderecos[*numClientes].CEP);
    limparBufferEntrada();
    fprintf(banco_de_dados, "CEP: %d\n", Enderecos[*numClientes].CEP);
    printf("-----------------------\n");

    // UF
    printf("Insira a UF (unidade federal): \n");
    fgets(Enderecos[*numClientes].strEstado, sizeof(Enderecos[*numClientes].strEstado), stdin);
    limparBufferEntrada();
        // Deixa a UF em letra maiúscula
    for(int i = 0; i < 2; i++){
        Enderecos[*numClientes].strEstado[i] = toupper(Enderecos[*numClientes].strEstado[i]);
    }
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
    Enderecos[*numClientes].strBairro[0] = toupper(Enderecos[*numClientes].strBairro[0]);
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
    fprintf(banco_de_dados, "\n");
    printf("-----------------------\n");
    *(numClientes)++;

    if (fclose(banco_de_dados) != 0) {
    // Tratar erro ao fechar o arquivo
        perror("Erro ao fechar o arquivo");
    // Pode ser interessante retornar ou tomar alguma ação específica neste caso
    }
    printf("Cliente cadastrado com sucesso!\n");

    limparBufferEntrada();
    
}

// Função excluirConta
void excluirConta(const char *arquivo, const char *arquivo_2) {

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
    while (fgets(linha, 100, banco_de_dados)) {
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
    // Algoritmo de desativação de conta
    else{

        char *cpf = (char*)malloc(16*sizeof(char));
        printf("Digite o CPF do usuário a ser desativado: \n");
        while(scanf("%s", cpf)){
            if(validarCPF(cpf) == 0){
                printf("CPF inválido!\n");
            }
            else{
                break;
            }
        }

    FILE *banco_de_dados = fopen(arquivo, "r");
    FILE *contas_desativadas = fopen(arquivo_2, "a+");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (banco_de_dados == NULL || contas_desativadas == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    char linha[100];
    int excluir = 0;
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), banco_de_dados)) {
        if (strstr(linha, cpf) != NULL) {
            excluir = 1;
            encontrado = 1;
        }

 
        if (!excluir) {
            fputs(linha, arquivoTemp);
        }

 
        if (strstr(linha, "NÚMERO:")) {
            excluir = 0;
        }
    }

    fclose(banco_de_dados);
    fclose(arquivoTemp);
    fclose(contas_desativadas);


    remove(arquivo);
    rename("temp.txt", arquivo);

   
    if (!encontrado) {
        printf("CPF não encontrado.\n");
    } else {
        printf("Conta desativada com sucesso!\n");
    }

    free(cpf);
    }
}

// Função realizar pedido
void realizarPedido(struct clientes *Clientes, int *numClientes, struct produtos *Produtos, int *numProdutos) {

    // Alocação das estruturas
    char *cpfCliente = (char*)malloc(16*sizeof(int));
    char *nomeCliente = (char*)malloc(50*sizeof(char));
    char *linha = (char*)malloc(100*sizeof(char));
    int input, cpfEncontrado = 0;
    int produtoEncontrado = 0;

    // Dados do produto
    char *nomeProdutoPedido = (char*)malloc(100*sizeof(char));
    float precoUnidadeProduto;
    int quantidadeProduto, quantidadeProdutoPedida;

    // Abre arquivo para leitura dos dados
    FILE *banco_de_dados = fopen("banco_de_dados.txt", "r");
    if (banco_de_dados == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *produtos = fopen("produtos.txt", "a+");
    if(produtos == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *pedidos = fopen("pedidos.txt", "a+");
    if(pedidos == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Loop com menu para digitar o CPF ou voltar para o menu principal
    do {
        printf("[1] Digitar CPF\n");
        printf("[0] Voltar\n");
        printf("Selecione uma opcao: ");
        scanf("%d", &input);

        switch(input){
            // Digitar CPF
            case 1:      
                printf("Digite o CPF: ");
                limparBufferEntrada();
                fgets(cpfCliente, 16, stdin);
                cpfCliente[strcspn(cpfCliente, "\n")] = '\0'; 

                while (fgets(linha, 100, banco_de_dados) != NULL) {
                    if (strstr(linha, "CPF:") != NULL && strstr(linha, cpfCliente) != NULL) {
                        // Exibe o CPF encontrado
                        printf("\n== Cliente encontrado! ==\n");
                        printf("%s", linha);

                        // Exibe os detalhes do cliente (Nome, Endereço, etc.)
                        for (int i = 0; i < 6; i++) {
                            fgets(linha, 100, banco_de_dados);
                            printf("%s", linha);
                        }

                        cpfEncontrado = 1;
                        break;  // CPF encontrado, sair do loop
                    }
                }

                if (!cpfEncontrado) {
                    printf("\nCPF nao encontrado no banco de dados.\n");
                    break;
                }

                // Solicitar um produto enquanto não encontrar um produto existente e com estoque
                do {
                    printf("\nDigite o nome do produto: ");
                    fgets(nomeProdutoPedido, 100, stdin);
                    nomeProdutoPedido[strcspn(nomeProdutoPedido, "\n")] = '\0';

               
                    rewind(produtos);
                    char *nomeProdutoEncontrado = (char*)malloc(100*sizeof(char));  

                    while (fgets(linha, 100, produtos) != NULL) {
                        if (strstr(linha, "NOME PRODUTO:") != NULL && strstr(linha, nomeProdutoPedido) != NULL) {
                            produtoEncontrado = 1;
                            
                            strcpy(nomeProdutoEncontrado, linha);
    
                            while (fgets(linha, 100, produtos) != NULL) {
                                if (strstr(linha, "PRECO/UNIDADE:") != NULL) {
                                if (sscanf(linha, "PRECO/UNIDADE: %f", &precoUnidadeProduto) == 1) {
                                    printf("Preço do produto: %.2f\n", precoUnidadeProduto);
                                    break;
                                } else {
                                    printf("Erro ao ler preço do produto.\n");
                                }
                            }
                            }
                            while (fgets(linha, 100, produtos) != NULL) {
                                if (strstr(linha, "QUANTIDADE DISPONIVEL:") != NULL) {
                                // Encontrou a linha com a quantidade disponível
                                if (sscanf(linha, "QUANTIDADE DISPONIVEL: %d", &quantidadeProduto) == 1) {
                                    // Aqui, quantidadeProduto contém o valor da quantidade disponível
                                    printf("Quantidade disponível: %d\n", quantidadeProduto);
                                    break;
                                } else {
                                    // Tratar erro na conversão
                                    printf("Erro ao ler a quantidade disponível.\n");
                                }
                            }
                            }
                        }
                    }

                    if (produtoEncontrado == 0) {
                        printf("Produto nao encontrado ou sem estoque.\n");
                        break;
                    }
                    while(1){
                    printf("Digite a quantidade de produtos a serem enviados: \n");
                    scanf("%d", &quantidadeProdutoPedida);
                    if(quantidadeProdutoPedida<=quantidadeProduto){
                        break;
                    }
                    printf("O número de pedidos deve ser menor ou igual ao estoque!\n");
                    }


                    int id_atual = 1;
                    rewind(pedidos);  
                    while (fgets(linha, 100, pedidos) != NULL) {
                        printf("Linha atual: ---%s\n", linha);
                        if (strstr(linha, "ID PEDIDO:") != NULL) {
                            sscanf(linha, "ID PEDIDO: %d", &id_atual);
                            id_atual += 1;
                        }
                    }
                    rewind(produtos);
                    while(fgets(linha,100,produtos)!= NULL){
                        if(strstr(linha, "NOME PRODUTO:") != NULL && strstr(linha, nomeProdutoPedido) != NULL){
                            fprintf(pedidos, "ID PEDIDO: %d\n", id_atual);
                            fprintf(pedidos, "STATUS: ENVIADO\n");
                            fprintf(pedidos, "%s", linha);
                            fgets(linha, 100, produtos); 
                            fprintf(pedidos, "%s", linha);
                            fgets(linha, 100, produtos); 
                            fprintf(pedidos, "%s", linha);
                            fgets(linha, 100, produtos);
                            fprintf(pedidos, "QUANTIDADE: %d\n", quantidadeProdutoPedida);
                            fprintf(pedidos, "VALOR DO PEDIDO: R$%.2f\n", quantidadeProdutoPedida*precoUnidadeProduto);
                        }
                    }
                    // Algoritmo para escrever dados do cliente
                    rewind(banco_de_dados);
                    while (fgets(linha, 100, banco_de_dados) != NULL) {
                        if (strstr(linha, "CPF:") != NULL && strstr(linha, cpfCliente) != NULL) {
                            fprintf(pedidos, "%s", linha);
                            while(fgets(linha, 100, banco_de_dados)!= NULL){
                                if (strstr(linha, "CEP:") != NULL){
                                    for(int i=0;i<5;i++){
                                        fgets(linha, 100, banco_de_dados);
                                        fprintf(pedidos, "%s", linha);
                                    }
                                }
                            }
                        }
                    }


                    // Atualiza o estoque no arquivo "produtos.txt"
                    FILE *temp_arquivo = fopen("temp.txt", "w");
                    rewind(produtos);
                    while(fgets(linha, 100, produtos) != NULL){
                        if(strstr(linha, "NOME PRODUTO:") != NULL && strstr(linha, nomeProdutoPedido) != NULL){
                            // COLOCA O NOME DO PRODUTO A ATUALIZAR NO TEMPORARIO
                            fprintf(temp_arquivo, "%s", linha);
                            fgets(linha, 100, produtos); // Pula para próxima linha (código)
                            // COLOCA O CÓDIGO DO PRODUTO A ATUALIZAR NO TEMPORARIO
                            fprintf(temp_arquivo, "%s", linha);
                            fgets(linha, 100, produtos); // Pula para próxima linha (preço)
                            // COLOCA O PREÇO DO PRODUTO A ATUALIZAR NO TEMPORARIO
                            fprintf(temp_arquivo, "%s", linha);
                            fgets(linha, 100, produtos); // Pula para próxima linha (Quantidade) --> Não será colocada no temporário, pois o valor será atualizado

                            fprintf(temp_arquivo, "QUANTIDADE DISPONIVEL: %d\n", quantidadeProduto - quantidadeProdutoPedida);
                            printf("Pedido realizado com sucesso!");
                        }
                        else {
                            fprintf(temp_arquivo, "%s", linha);
                        }
                    }

                    // Fecha os arquivos
                    fclose(produtos);
                    fclose(temp_arquivo);

                    // Substitui o arquivo original pelo temporário
                    remove("produtos.txt");
                    rename("temp.txt", "produtos.txt");

                } while (!produtoEncontrado);

                break;

            // Volta para o menu principal
            case 0:
                return;
        }
    } while(cpfEncontrado == 0);

    free(nomeProdutoPedido);

    fclose(pedidos);
    fclose(produtos);
    fclose(banco_de_dados);
    printf("\n");
}

// Função verificar conta
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
    while (fgets(linha, 100, banco_de_dados)) {
        if (strstr(linha, "CPF: ") != NULL && strstr(linha, cpf) != NULL) {
            imprimir = 1;
            encontrou = 1;
        }
        if (encontrou == 1) {
            printf("%s", linha);
        }
        if (strstr(linha, "NÚMERO: ") != NULL && encontrou == 1) {
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

void acompanharPedido(const char *arquivo) {
    int input;
    do {
        printf("[1] Consulta por ID de pedido.\n");
        printf("[0] Sair.\n");
        scanf("%d", &input);

        if (input == 1) {
            char id_do_pedido[1000];
            printf("Insira id do pedido: \n");
            limparBufferEntrada();
            scanf("%s", id_do_pedido);

            FILE *pedidos = fopen(arquivo, "r");
            if (pedidos == NULL) {
                printf("Erro ao abrir arquivo.");
                return;
            }

            // Indicadores
            char *linha = (char*)malloc(100 * sizeof(char));
            int imprimir = 0;
            int encontrou = 0;

            // Algoritmo para impressão
            while (fgets(linha, 100, pedidos) != NULL) {
                if (strstr(linha, "ID PEDIDO: ") != NULL && strstr(linha, id_do_pedido) != NULL) {
                    imprimir = 1;
                    encontrou = 1;
                    printf("\n");
                    printf("========\n");
                }
                if (encontrou == 1) {
                    printf("%s", linha);
                }
                if (strstr(linha, "NÚMERO: ") != NULL && encontrou == 1) {
                    imprimir = 0;
                    printf("========\n");
                    printf("\n");
                    break;
                }
            }

            // Encerramento da subrotina
            fclose(pedidos);

            if (encontrou == 0) {
                printf("Produto não encontrado.\n");
            }
            free(linha);
        }
    } while (input != 0);
    return;
}

// Função para adicionar estoque
void adicionarEstoque(struct produtos *Produtos, int *numProdutos){
        // Alocação dinâmica de struct
        struct produtos *novo_produto = (struct produtos*)realloc(Produtos, (*numProdutos + 1) * sizeof(struct produtos));
        if (novo_produto == NULL) {
            printf("Falha ao alocar memoria\n");
            return;
        }

    int input, nova_quantidade;
    char verificarNome[100];
    char linha[100];
    int verificarMenu = -1;

    FILE *produtos_arquivo = fopen("produtos.txt", "a+");
    if(produtos_arquivo == NULL){
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    do {

    printf("ADICIONAR ESTOQUE\n");
    printf("[1] Adicionar novo produto\n");
    printf("[0] Voltar\n");
    printf("Selecione uma opção: ");
    scanf("%d", &input);

    switch(input){

        case 1:
            
            /*printf("Insira o nome do produto: ");
            limparBufferEntrada();
            fgets(verificarNome, 100, stdin);
            verificarNome[strcspn(verificarNome, "\n")] = '\0';

            while(fgets(linha, 100, produtos_arquivo) != NULL){
                if(strstr(linha, "NOME PRODUTO:") != NULL && strstr(linha, verificarNome) != NULL){
                    printf("Produto encontrado!\n\n");
                    
                    printf("--> %s", linha); // PRINTA NOME
                    fgets(linha, sizeof(linha), produtos_arquivo);

                    printf("--> %s", linha); // PRINTA CÓDIGO
                    fgets(linha, sizeof(linha), produtos_arquivo);

                    printf("--> %s", linha); // PRINTA PREÇO
                    fgets(linha, sizeof(linha), produtos_arquivo);

                    printf("--> %s\n", linha); // PRINTA QUANTIDADE ATUAL
                    printf("-------------------------\n");

                    printf("Digite a nova quantidade do produto: ");
                    scanf("%d", &nova_quantidade);
                    limparBufferEntrada();
                    Produtos[*numProdutos].quantidade_produto = nova_quantidade;
                    break;
                }
            }
            rewind(produtos_arquivo);
            FILE *temp_arquivo = fopen("temp.txt", "w");
            if (temp_arquivo == NULL) {
                printf("Erro ao criar arquivo temporario.\n");
                return;
            }

            while(fgets(linha, sizeof(linha), produtos_arquivo) != NULL){

                if(strstr(linha, "NOME PRODUTO:") != NULL && strstr(linha, verificarNome) != NULL){
                    // COLOCA O NOME DO PRODUTO A ATUALIZAR NO TEMPORARIO
                    fprintf(temp_arquivo, "%s", linha);
                    fgets(linha, sizeof(linha), produtos_arquivo); // Pula para próxima linha (código)
                    // COLOCA O CÓDIGO DO PRODUTO A ATUALIZAR NO TEMPORARIO
                    fprintf(temp_arquivo, "%s", linha);
                    fgets(linha, sizeof(linha), produtos_arquivo); // Pula para próxima linha (preço)
                    // COLOCA O PREÇO DO PRODUTO A ATUALIZAR NO TEMPORARIO
                    fprintf(temp_arquivo, "%s", linha);
                    fgets(linha, sizeof(linha), produtos_arquivo); // Pula para próxima linha (Quantidade) --> Não será colocada no temporário, pois o valor será atualizado

                    fprintf(temp_arquivo, "QUANTIDADE DISPONIVEL: %d\n", nova_quantidade);
                }
                else {
                    fprintf(temp_arquivo, "%s", linha);
                }
            }

            // Fecha os arquivos
            fclose(produtos_arquivo);
            fclose(temp_arquivo);

            // Substitui o arquivo original pelo temporário
            remove("produtos.txt");
            rename("temp.txt", "produtos.txt");

            printf("Pressione Enter para continuar...\n");
            scanf("%*c");

            break;*/
            // Nome do produto
            printf("Insira o nome do produto: \n");
            limparBufferEntrada();
            fgets(Produtos[*numProdutos].nome_produto, sizeof(Produtos[*numProdutos].nome_produto), stdin);
            strtok(Produtos[*numProdutos].nome_produto, "\n");
            fprintf(produtos_arquivo, "\nNOME PRODUTO: %s\n", Produtos[*numProdutos].nome_produto);
            printf("-----------------------\n");

            // Código do produto
            printf("Insira o código do produto: \n");
            scanf("%d", &Produtos[*numProdutos].codigo_produto);
            fprintf(produtos_arquivo, "CÓDIGO: %d\n", Produtos[*numProdutos].codigo_produto);
            printf("-----------------------\n");
            getchar();

            // Preço
            printf("Insira o preço do produto: \n");
            scanf("%f", &Produtos[*numProdutos].preco_produto);
            fprintf(produtos_arquivo, "PRECO/UNIDADE: %.2f\n", Produtos[*numProdutos].preco_produto);
            printf("-----------------------\n");
            
            // Quantidade
            printf("Insira a quantidade do produto: \n");
            scanf("%d", &Produtos[*numProdutos].quantidade_produto);
            fprintf(produtos_arquivo, "QUANTIDADE DISPONIVEL: %d\n", Produtos[*numProdutos].quantidade_produto);
            printf("-----------------------\n");
            (*numProdutos)++;

            limparBufferEntrada();

            printf("\nPressione Enter para continuar...\n");
            break;
        default:
            printf("Opcao invalida.\n");
            printf("\nPressione Enter para continuar...\n");
            scanf("%*c");
    }
    } while(input != 0);

    fclose(produtos_arquivo);
}

// Função para verificar estoque
void verificarEstoque(const char *arquivo) {
    // Input de CPF
    char *produto = (char*)malloc(100*sizeof(char));
    printf("Digite o nome do produto a ser localizado: \n");
    while(scanf("%s", produto)){
        if(strlen(produto) == 0){
            printf("Preencha o campo do produto!\n");
        }
        else{
            break;
        }
    }

    // Abrir o arquivo
    FILE *produtos = fopen(arquivo, "r");
    if (produtos == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    // Indicadores
    char *linha = (char*)malloc(100*sizeof(char));
    int imprimir = 0;
    int encontrou = 0;

    // Algoritmo para impressão
    while (fgets(linha, 100, produtos)) {
        if (strstr(linha, "NOME PRODUTO: ") != NULL && strstr(linha, produto) != NULL) {
            imprimir = 1;
            encontrou = 1;
            printf("\n");
            printf("========\n");
        }
        if (encontrou == 1) {
            printf("%s", linha);
        }
        if (strstr(linha, "QUANTIDADE DISPONIVEL: ") != NULL && encontrou == 1) {
            imprimir = 0;
            printf("========\n");
            printf("\n");
            break;
        }
    }

    // Encerramento da subrotina
    fclose(produtos);

    if (encontrou == 0) {
        printf("Produto não encontrado.\n");
    }
    free(produto);
    free(linha);
}


int main() {

    // Alocação dinâmica das estruturas
    struct enderecos *Enderecos = (struct enderecos*)malloc(tam * sizeof(struct enderecos));
    struct produtos *Produtos = (struct produtos*)malloc(tam * sizeof(struct produtos));
    struct clientes *Clientes = (struct clientes*)malloc(tam * sizeof(struct clientes));
    int numClientes = 0;
    int numProdutos = 0;
    
    // Menu da da aplicação
    int input_usuario;
    int input_usuario_subrotina;
    do {
        ;

        printf("\n=== Rede UP - Pedidos de Eletronicos e Perifericos ===\n");
        printf("MENU PRINCIPAL\n\n");
        printf("1. Contas\n");
        printf("2. Produtos\n");
        printf("3. Pedidos\n");
        printf("0. Sair\n");
        printf("Selecione uma opção: \n");
        scanf("%d", &input_usuario);
        limparBufferEntrada();

        if(input_usuario == 1){
            input_usuario = -1;
            do{
            ;
            printf("=== Menu de Contas ===\n");
            printf("1. Cadastrar Conta\n");
            printf("2. Excluir/Desativar Conta\n");
            printf("3. Verificar Conta.\n");
            printf("4. Listar todos os clientes.\n");
            printf("0. Sair\n");
            printf("Selecione uma opção: \n");
            scanf("%d", &input_usuario_subrotina);

            switch(input_usuario_subrotina){
                case 1:
                    input_usuario_subrotina = -1;
                    ;
                    cadastrarConta(Clientes, Enderecos, &numClientes);
                    break;
                case 2:
                    input_usuario_subrotina = -1;
                    
                    excluirConta("banco_de_dados.txt", "contas_desativadas.txt");
                    break;
                case 3:
                    input_usuario_subrotina = -1;
                    verificarConta("banco_de_dados.txt");
                    break;
                case 4:
                    input_usuario_subrotina = -1;
                    listarClientes("banco_de_dados.txt", Clientes, &numClientes);
                    break;
                case 0:
                    break;
                default:
                    printf("Selecione uma opção válida!\n");
                    break;
            }
            }while(input_usuario_subrotina != 0);
        }
        else if(input_usuario == 2){
            input_usuario = -1;
            do{
        
            printf("=== Menu de Produtos ===\n");
            printf("1. Aumentar Estoque.\n");
            printf("2. Verificar Estoque\n");
            printf("0. Sair\n");
            printf("Selecione uma opção: \n");
            scanf("%d", &input_usuario_subrotina);
            switch (input_usuario_subrotina){
            case 1:
                input_usuario_subrotina = -1;
                adicionarEstoque(Produtos, &numProdutos);
                break;
            case 2:
                input_usuario_subrotina = -1;
                verificarEstoque("produtos.txt");
                break;
            case 0:
                break;
            default:
                printf("Pressione Enter para continuar...\n");
                scanf("%*c");
            }
            }while(input_usuario_subrotina != 0);
        }
        else if(input_usuario == 3){
            input_usuario = -1;
            do{
        
                
                printf("=== Menu de pedidos ===\n");
                printf("1. Realizar pedido.\n");
                printf("2. Acompanhar pedido.\n");
                printf("0. Sair.\n");
                scanf("%d", &input_usuario_subrotina);
                limparBufferEntrada();
                switch(input_usuario_subrotina){
                    case 1:
                        input_usuario_subrotina = -1;
                        realizarPedido(Clientes, numClientes, Produtos, numProdutos);
                        break;
                    case 2:
                        input_usuario_subrotina = -1;
                        acompanharPedido("pedidos.txt");
                        break;
                    case 0:
                        break;
                    default:
                        printf("Pressione Enter para continuar...\n");
                        scanf("%*c");
                }
            }while(input_usuario_subrotina != 0);
        }
        else if(input_usuario == 0){
            ;
            
            printf("Encerrando programa...\n");
        }
    } while(input_usuario!=0);
        

    free(Enderecos);
    free(Clientes);
    free(Produtos);
    
    return 0;
}
