// Biblioteca para entrada e saída de dados (ex: printf, scanf)
#include <stdio.h>
// Biblioteca para funções como malloc e rand
#include <stdlib.h>
// Biblioteca para manipulação de strings (ex: strcpy, strlen)
#include <string.h>

// Tamanho máximo de textos, produtos, quantidades, etc
#define MAX_NOME 100
#define MAX_PRODUTOS 100
#define MAX_ITENS 100
#define MAX_PAGAMENTOS 100

// Estrutura de Dados do Cliente
typedef struct {
    // Código do cliente (gerado automaticamente)
    int codigo;
    // Nome completo do cliente
    char nomeCompleto[MAX_NOME];
    // Nome social (caso queira ser chamado diferente)
    char nomeSocial[MAX_NOME];
    // CPF do cliente
    char cpf[20];
    // Endereço com rua e número
    char endereco[100];
    // Bairro onde mora
    char bairro[MAX_NOME];
    // Celular ou WhatsApp para contato
    char celular[20];
} StructCliente;

// Estrutura de Dados do Produto
typedef struct {
    // Código único do produto
    int codigo;
    // Nome do produto
    char descricao[MAX_NOME];
    // Tipo: Alimento, Limpeza, Panificação
    char categoria[30];
    // Quanto o mercado cobrará pelo produto
    float precoCompra;
    // Percentual que será adicionado (lucro)
    float margemLucro;
    // Quantidade atual no estoque
    int quantidade;
    // Quantidade mínima antes de alertar
    int estoqueMinimo;
} StructProduto;

// Estrutura de Dados do Item da Venda
typedef struct {
    // Identificador da venda
    int codigoVenda;
    // Produto vendido
    int codigoProduto;
    // Nome do produto
    char descricaoProduto[MAX_NOME];
    // Valor de venda (com lucro)
    float precoVenda;
    // Quantidade comprada
    int quantidadeVendida;
    // Total (preço x quantidade)
    float totalItem;
    // 'a' = em aberto, 'p' = pago
    char statusPagamento;
} StructItemVenda;

// Estrutura de Dados do Pagamento
typedef struct {
    // Venda correspondente
    int codigoVenda;
    // Valor total pago
    float valorPago;
    // Tipo: d (dinheiro), c (cartão), dc (misto)
    char tipoPagamento[3];
} StructPagamento;

// Variáveis globais
StructProduto produtos[MAX_PRODUTOS];
int totalProdutos = 0;

StructItemVenda itensVenda[MAX_ITENS];
int totalItens = 0;

StructPagamento pagamentos[MAX_PAGAMENTOS];
int totalPagamentos = 0;

float caixa = 0;
float abertura = 0;
int caixaAberto = 0;

// Protótipos das Funções
void menuPrincipal();
void submenuCadastros();
void submenuVendas();
void submenuCaixa();
void submenuRelatorios();

// Funções de Cadastro
void cadastrarCliente();
void cadastrarProduto();

void novaVenda();
void pagamentoVenda();
void retiradaCaixa();
void abrirCaixa();
void fecharCaixa();
void listarClientes();
void listarProdutos();

float calcularPrecoVenda(float precoCompra, float margem);

// Função com ponteiro que percorre o arquivo para buscar e verificar o código do produto que o cliente escolheu
StructProduto* buscarProdutoPorCodigo(int codigo);

// Funções de salvamento de dados em arquivos
void salvarClienteEmArquivo(StructCliente cliente);
void salvarProdutoEmArquivo(StructProduto produto);
void salvarPagamentoEmArquivo(StructPagamento pag);

// Função Principal
int main() {
    // Variável do tipo inteiro que armazenará a escolha do usuário
    int opcao;

    // Início do loop Do While
    do {
        // Função que exibe o Menu Principal
        menuPrincipal();
        // Função que faz a leitura da escolha do usuário
        scanf("%d", &opcao);
        // Função que limpa o buffer do teclado (os espaços)
        getchar();

        // Switch da escolha do usuário do Menu Principal
        switch(opcao) {
            // Caso o usuário escolha a opção '1. Cadastros'
            case 1:
                submenuCadastros();
                break;

            // Caso o usuário escolha a opção '2. Vendas'
            case 2:
                submenuVendas();
                break;

            // Caso o usuário escolha a opção '3. Abertura de Caixa'
            case 3:
                submenuCaixa();
                break;

            // Caso o usuário escolha a opção '4. Fechamento de Caixa'
            case 4:
                fecharCaixa();
                break;

            // Caso o usuário escolha a opção '5. Relatórios'
            case 5:
                submenuRelatorios();
                break;

            // Caso o usuário escolha a opção '6. Sair'
            case 6: {
                // Variável do tipo caractere para armazenar a escolha da Dona Berê
                char guardarDados;
                // Pergunta se deseja guardar os dados cadastrados do dia
                printf("Deseja guardar as informacoes de Clientes, Produtos, Vendas e Pagamentos? (s/n): ");
                // Função que faz a leitura da escolha do usuário
                scanf(" %c", &guardarDados);

                // Se a Dona Berê desejar salvar todos os dados do dia, entrará aqui
                if (guardarDados == 's' || guardarDados == 'S') {
                    printf("Dados salvos com sucesso!\n");
                }
                // Exibe uma mensagem de agradecimento
                printf("Obrigado por comprar na Mercearia da Dona Bere! Volte sempre!\n");
                break;
            }

            // Caso o usuário não escolha nenhuma das opções acima
            default:
                printf("Opcao invalida. Tente novamente\n\n");
        }
    } while (opcao != 6); // Enquanto não escolher '6. Sair', repete o loop
    return 0;
}

// Função que exibe as categorias do Menu Principal
void menuPrincipal() {
    printf("\n=========== MENU PRINCIPAL ===========\n\n");
    printf(" 1. Cadastros\n 2. Vendas\n 3. Abertura de Caixa\n 4. Fechamento de Caixa\n 5. Relatorios\n 6. Sair\n\n");

    // Pergunta ao usuário qual opção do menu deseja escolher
    printf("Escolha uma opcao: ");
}

// Função do submenu da opção '1. Cadastros'
void submenuCadastros() {
    // Variável do tipo inteiro que armazenará a escolha do usuário
    int opcao;

    // Início do loop Do While
    do {
        printf("\n===== CADASTROS =====\n\n");
        printf(" 1. Cadastro de Clientes\n 2. Cadastro de Produtos\n 3. Retornar ao Menu Principal\n\n");

        // Pergunta ao usuário qual opção do menu deseja escolher
        printf("Escolha uma opcao: ");
        // Função que faz a leitura da escolha do usuário
        scanf("%d", &opcao);
        // Função que limpa o buffer do teclado (os espaços)
        getchar();

        // Switch da escolha do usuário do submenu da opção '1. Cadastros'
        switch(opcao) {
            // Caso o usuário escolha o opção 1. Cadastro de Clientes
            case 1:
                cadastrarCliente();
                break;

            // Caso o usuário escolha a opção 2. Cadastro de Produtos
            case 2:
                cadastrarProduto();
                break;
        }
    } while(opcao != 3); // Enquanto não escolher '3. Retornar ao Menu Principal', repete o loop
}

// Função do submenu da opção '2.Vendas'
void submenuVendas() {
    // Variável do tipo inteiro que armazenará a escolha do usuário
    int opcao;

    // Início do loop Do While
    do {
        printf("\n===== VENDAS =====\n\n");
        printf(" 1. Nova Venda\n 2. Retirada de Caixa (Sangria)\n 3. Pagamento\n 4. Retornar ao Menu Principal\n\n");

        // Pergunta ao usuário qual opção do menu deseja escolher
        printf("Escolha uma opcao: ");
        // Função que faz a leitura da escolha do usuário
        scanf("%d", &opcao);
        // Função que limpa o buffer do teclado (os espaços)
        getchar();

        // Switch da escolha do usuário do submenu da opção '2. Vendas'
        switch(opcao) {
            // Caso o usuário escolha o opção 1. Nova Venda
            case 1:
                novaVenda();
                break;

            // Caso o usuário escolha o opção 2. Retirada de Caixa (Sangria)
            case 2:
                retiradaCaixa();
                break;

            // Caso o usuário escolha o opção 3. Pagamento
            case 3:
                pagamentoVenda();
                break;
        }
    } while(opcao != 4); // Enquanto não escolher '4. Retornar ao Menu Principal', repete o loop
}

// // Função do submenu da opção '3. Abertura de Caixa'
void submenuCaixa() {
    abrirCaixa();
}

// Função do submenu da opção '4. Fechamento de Caixa'
void submenuRelatorios() {
    listarClientes();
    listarProdutos();
}

// Função para cadastrar os dados do Cliente
void cadastrarCliente() {
    StructCliente novo;

    // Abre o arquivo para adicionar o cliente
    FILE *f = fopen("clientes.txt", "a");

    // Se der erro no arquivo, exibirá uma mensagem de erro
    if(!f) {
        printf("Erro ao abrir arquivo");
        return;
    }

    printf("\n===== Cadastrar Cliente =====\n\n");

    printf("Nome completo: ");
    fgets(novo.nomeCompleto, MAX_NOME, stdin);

    printf("Nome social: ");
    fgets(novo.nomeSocial, MAX_NOME, stdin);

    printf("CPF: ");
    fgets(novo.cpf, 20, stdin);

    printf("Rua e numero: ");
    fgets(novo.endereco, 100, stdin);

    printf("Bairro: ");
    fgets(novo.bairro, MAX_NOME, stdin);

    printf("Celular/WhatsApp: ");
    fgets(novo.celular, 20, stdin);

    /* Gera um código aleatório para o cliente,
    rand() % 10000 é uma expressão que gera um número inteiro pseudoaleatório no intervalo de 0 a 9999 */
    novo.codigo = rand() % 10000;

    // Salva os dados do cliente no arquivo
    salvarClienteEmArquivo(novo);

    // Código do Cliente
    printf("\nCliente cadastrado com codigo: %d\n\n", novo.codigo);

    // Função que fecha o arquivo
    fclose(f);
}

// Função para cadastrar os dados do Produto
void cadastrarProduto() {
    StructProduto p;

    printf("\n===== Cadastrar Produto =====\n\n");

    printf("Descricao do Produto: ");
    fgets(p.descricao, MAX_NOME, stdin);

    printf("Categoria (Alimento, Limpeza, Panificacao): ");
    fgets(p.categoria, 30, stdin);

    printf("Preco de compra: R$ ");
    scanf("%f", &p.precoCompra);

    printf("Margem de lucro (%%): ");
    scanf("%f", &p.margemLucro);

    printf("Estoque atual: ");
    scanf("%d", &p.quantidade);

    printf("Estoque minimo: ");
    scanf("%d", &p.estoqueMinimo);

    // Gera um código aleatório para o produto
    p.codigo = rand() % 1000 + 1000;

    produtos[totalProdutos++] = p;

    // Salva os dados do produto no arquivo
    salvarProdutoEmArquivo(p);

    // Código do Produto
    printf("\nProduto cadastrado com codigo: %d\n\n", p.codigo);
}

// Função para fazer as compras dos Produtos
void novaVenda() {
    // Se o caixa for aberto vazio (nenhum dinheiro)
    if(!caixaAberto) {
        printf("Abra o caixa antes de vender\n\n");
        return;
    }

    int codigo, qtd;
    char continuar = 's';
    float total = 0;

    while(continuar == 's') {
        // Solicita ao usuário o código do produto que deseja
        printf("Informe o codigo do produto a ser comprado: ");
        // Função que faz a leitura da escolha do usuário
        scanf("%d", &codigo);

        StructProduto *p = buscarProdutoPorCodigo(codigo);

        // Se o código do produto que o usuário buscou não estiver no estoque
        if(!p || p->quantidade <= 0){
            printf("Produto indisponivel.\n");
            continue;
        }

        float precoVenda = calcularPrecoVenda(p->precoCompra, p->margemLucro);

        printf(" Descricao: %s Preco: R$ %.2f\n Estoque: %d\n\n", p->descricao, precoVenda, p->quantidade);

        // Solicita ao usuário a quantidade de produtos que deseja
        printf("Informe a quantidade: ");
        // Função que faz a leitura da escolha do usuário
        scanf("%d", &qtd);

        // O traço angular direito serve para apontar para o endereço da variável
        if(qtd > p->quantidade) qtd = p->quantidade;
        p->quantidade -= qtd;
        float subtotal = qtd * precoVenda;
        total += subtotal;

        // Exibe o total da compra e pergunta ao usuário se ele deseja adicionar mais produtos
        printf("Subtotal: R$ %.2f\nDeseja adicionar mais produtos? (s/n): ", subtotal);
        // Função que faz a leitura da escolha do usuário
        scanf(" %c", &continuar);
    }
    printf("Total da venda: R$ %.2f\n\n", total);
    caixa += total;
}

// Função da opção do submenu 2.Venda
void pagamentoVenda() {
    int codigoVenda;
    float totalVenda = 0;
    int encontrada = 0;

    printf("\n===== PAGAMENTO DE VENDA =====\n\n");

    // Listar vendas em aberto
    for (int i = 0; i < totalItens; i++) {
        if (itensVenda[i].statusPagamento == 'a') {
            printf("Venda %d - Produto: %s - Total: R$ %.2f\n", itensVenda[i].codigoVenda, itensVenda[i].descricaoProduto, itensVenda[i].totalItem);
        }
    }

    // Solicita ao usuário o código do produto que ele comprou
    printf("\nDigite o codigo da venda para pagamento: ");
    // Função que faz a leitura da escolha do usuário
    scanf("%d", &codigoVenda);

    // Calcular o total da venda
    for (int i = 0; i < totalItens; i++) {
        if (itensVenda[i].codigoVenda == codigoVenda) {
            totalVenda += itensVenda[i].totalItem;
            encontrada = 1;
        }
    }

    // Se o produto não foi encontrado ou já foi paga
    if (!encontrada) {
        printf("Venda nao encontrada ou ja paga.\n");
        return;
    }

    int opcao;
    float valorPago = 0;
    char tipoPagamento[3];

    // Início do Do While
    do {
        printf("\n1. Pagamento no cartao\n2. Pagamento em dinheiro\n3. Retornar ao Menu Principal\nInforme a opcao: ");
        // Função que faz a leitura da escolha do usuário
        scanf("%d", &opcao);

        // Se escolher o pagamento no cartão
        if (opcao == 1) {
            int confirmado;
            printf("Pagamento realizado na maquininha? (1 - Sim, 0 - Nao): ");
            scanf("%d", &confirmado);
            // Se o pagamento foi bem sucessido
            if (confirmado == 1) {
                valorPago = totalVenda;
                strcpy(tipoPagamento, "c");
                break;
            // Se o pagamento deu erro
            } else {
                printf("Pagamento nao confirmado. Escolha outra forma.\n");
            }
        // Se escolher o pagamento em dinheiro
        } else if (opcao == 2) {
            float recebido;
            printf("Informe o valor recebido em dinheiro: R$ ");
            scanf("%f", &recebido);

            // Se o usuário não tiver condições de conseguir pagar o valor inteiro da compra no dinheiro, o resto poderá ser no cartão
            if (recebido < totalVenda) {
                float restante = totalVenda - recebido;
                printf("Faltam R$ %.2f. Deseja pagar o restante no cartao? (1 - Sim, 0 - Nao): ", restante);
                int resposta;
                scanf("%d", &resposta);

                // Se ele conseguir pagar o restante com o cartão
                if (resposta == 1) {
                    valorPago = totalVenda;
                    strcpy(tipoPagamento, "dc");
                    float troco = 0;
                    printf("Valor pago R$ %.2f em dinheiro e R$ %.2f no cartao.\n", recebido, restante);
                    break;
                // Se ele não conseguir pagar de jeito nenhum
                } else {
                    printf("Pagamento insuficiente. Operacao cancelada.\n");
                    return;
                }
            } else {
                valorPago = totalVenda;
                strcpy(tipoPagamento, "d");
                float troco = recebido - totalVenda;
                printf("Troco: R$ %.2f\n", troco);
                break;
            }
        } else if (opcao == 3) {
            return;
        } else {
            printf("Opcao invalida. Tente novamente\n");
        }
    } while(1);

    // Marcar itens como pagos
    for (int i = 0; i < totalItens; i++) {
        if (itensVenda[i].codigoVenda == codigoVenda) {
            itensVenda[i].statusPagamento = 'p';
        }
    }

    StructPagamento pag;
    pag.codigoVenda = codigoVenda;
    pag.valorPago = valorPago;
    strcpy(pag.tipoPagamento, tipoPagamento);
    pagamentos[totalPagamentos++] = pag;
    salvarPagamentoEmArquivo(pag);
    caixa += valorPago;

    // Depois de todo o processo, exibe uma mensagem de pagamento concluído
    printf("Pagamento registrado com sucesso!\n");
}

// Função que salva os dados do pagamento em arquivo
void salvarPagamentoEmArquivo(StructPagamento pag) {
    // Abre o arquivo e adiciona os dados dos pagamentos no final
    FILE *f = fopen("pagamentos.txt", "a");
    // Se houver erro ao abrir o arquivo
    if (!f) {
        printf("Erro ao abrir arquivo de pagamentos.\n");
        return;
    }
    fprintf(f, "Venda %d - Valor Pago: R$ %.2f - Tipo: %s\n", pag.codigoVenda, pag.valorPago, pag.tipoPagamento);
    fclose(f);
}

// Função do dinheiro disponível que está no caixa, especialmente para troco
void retiradaCaixa() {
    float valor;
    printf("Valor para retirada (minimo R$ 50 deve permanecer): ");
    scanf("%f", &valor);

    if(valor <= caixa - 50) {
        caixa -= valor;
        printf("Sangria realizada. Caixa atual: R$ %.2f\n\n", caixa);
    } else {
        printf("Valor excede o limite permitido.\n\n");
    }
}

// Função de Abertura de Caixa
void abrirCaixa() {
    // Se o caixa já está aberto com dinheiro
    if(caixaAberto) {
        printf("Caixa já está aberto.\n");
        return;
    }

    // Solicita a Dona Berê o valor que ocorrerá a abertura de caixa
    printf("Digite o valor de abertura do caixa: R$ ");
    // Função que faz a leitura da escolha do usuário
    scanf("%f", &abertura);

    caixa = abertura;
    caixaAberto = 1;

    // Exibe com quantos Reais o caixa foi aberto
    printf("Caixa aberto com R$ %.2f\n\n", caixa);
}

// Função de Fechamento de Caixa, exibindo os saldos do dia
void fecharCaixa() {
    printf("\n===== FECHAMENTO DE CAIXA =====\n\n");
    printf("Valor inicial: R$ %.2f\n", abertura);
    printf("Valor final em caixa: R$ %.2f\n", caixa);
    printf("Total movimentado: R$ %.2f\n\n", caixa - abertura);
    caixaAberto = 0;
}

// Função que exibe a lista de Clientes no Terminal quando o usuário escolhe a opção '5. Relatórios'
void listarClientes() {
    FILE *f = fopen("clientes.txt", "r");
    if(!f) return;
    char linha[200];
    printf("\n===== CLIENTES =====\n\n");
    while(fgets(linha, sizeof(linha), f)) printf("%s", linha);
    fclose(f);
}

// Função que exibe a lista de produtos no Terminal quando o usuário escolhe a opção '5. Relatórios'
void listarProdutos() {
    FILE *f = fopen("produtos.txt", "r");
    if(!f) return;
    char linha[200];
    printf("\n===== PRODUTOS =====\n\n");
    while(fgets(linha, sizeof(linha), f)) printf("%s", linha);
    fclose(f);
}

// Função que faz o cálculo do Preço de Venda com Lucro
float calcularPrecoVenda(float precoCompra, float margem) {
    return precoCompra + (precoCompra * margem / 100);
}

// Faz com que percorra por toda a estrutura para achar o código do produto específico
StructProduto* buscarProdutoPorCodigo(int codigo) {
    for(int i = 0; i < totalProdutos; i++) {
        if(produtos[i].codigo == codigo)return &produtos[i];
    }
    return NULL;
}

// Função que salva os dados do Cliente em arquivo
void salvarClienteEmArquivo(StructCliente c) {
    // Abre o arquivo de Clientes
    FILE *f = fopen("clientes.txt", "a");
    if(!f) return;
    fprintf(f, "Codigo: %d\nNome Completo: %sNome Social: %sCPF: %sEndereco: %sBairro: %sCelular: %s\n\n", c.codigo, c.nomeCompleto, c.nomeSocial, c.cpf, c.endereco, c.bairro, c.celular);
    // Função que fecha o arquivo
    fclose(f);
}

// Função que salva os dados do Produto em arquivo
void salvarProdutoEmArquivo(StructProduto p) {
    // Abre o arquivo de Produtos
    FILE *f = fopen("produtos.txt", "a");
    if(!f) return;
    float precoVenda = calcularPrecoVenda(p.precoCompra, p.margemLucro);
    fprintf(f, "Codigo: %d\nDescricao: %sCategoria: %sPreco Compra: %.2f\nMargem: %.2f%%\nPreco Venda: %.2f\nEstoque: %d (min %d)\n\n", p.codigo, p.descricao, p.categoria, p.precoCompra, p.margemLucro, precoVenda, p.quantidade, p.estoqueMinimo);
    // Função que fecha o arquivo
    fclose(f);
}
