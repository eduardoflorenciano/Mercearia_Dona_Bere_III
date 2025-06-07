// Biblioteca para entrada e sa�da de dados (ex: printf, scanf)
#include <stdio.h>
// Biblioteca para fun��es como malloc e rand
#include <stdlib.h>
// Biblioteca para manipula��o de strings (ex: strcpy, strlen)
#include <string.h>

// Tamanho m�ximo de textos, produtos, quantidades, etc
#define MAX_NOME 100
#define MAX_PRODUTOS 100
#define MAX_ITENS 100
#define MAX_PAGAMENTOS 100

// Estrutura de Dados do Cliente
typedef struct {
    // C�digo do cliente (gerado automaticamente)
    int codigo;
    // Nome completo do cliente
    char nomeCompleto[MAX_NOME];
    // Nome social (caso queira ser chamado diferente)
    char nomeSocial[MAX_NOME];
    // CPF do cliente
    char cpf[20];
    // Endere�o com rua e n�mero
    char endereco[100];
    // Bairro onde mora
    char bairro[MAX_NOME];
    // Celular ou WhatsApp para contato
    char celular[20];
} StructCliente;

// Estrutura de Dados do Produto
typedef struct {
    // C�digo �nico do produto
    int codigo;
    // Nome do produto
    char descricao[MAX_NOME];
    // Tipo: Alimento, Limpeza, Panifica��o
    char categoria[30];
    // Quanto o mercado cobrar� pelo produto
    float precoCompra;
    // Percentual que ser� adicionado (lucro)
    float margemLucro;
    // Quantidade atual no estoque
    int quantidade;
    // Quantidade m�nima antes de alertar
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
    // Total (pre�o x quantidade)
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
    // Tipo: d (dinheiro), c (cart�o), dc (misto)
    char tipoPagamento[3];
} StructPagamento;

// Vari�veis globais
StructProduto produtos[MAX_PRODUTOS];
int totalProdutos = 0;

StructItemVenda itensVenda[MAX_ITENS];
int totalItens = 0;

StructPagamento pagamentos[MAX_PAGAMENTOS];
int totalPagamentos = 0;

float caixa = 0;
float abertura = 0;
int caixaAberto = 0;

// Prot�tipos das Fun��es
void menuPrincipal();
void submenuCadastros();
void submenuVendas();
void submenuCaixa();
void submenuRelatorios();

// Fun��es de Cadastro
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

// Fun��o com ponteiro que percorre o arquivo para buscar e verificar o c�digo do produto que o cliente escolheu
StructProduto* buscarProdutoPorCodigo(int codigo);

// Fun��es de salvamento de dados em arquivos
void salvarClienteEmArquivo(StructCliente cliente);
void salvarProdutoEmArquivo(StructProduto produto);
void salvarPagamentoEmArquivo(StructPagamento pag);

// Fun��o Principal
int main() {
    // Vari�vel do tipo inteiro que armazenar� a escolha do usu�rio
    int opcao;

    // In�cio do loop Do While
    do {
        // Fun��o que exibe o Menu Principal
        menuPrincipal();
        // Fun��o que faz a leitura da escolha do usu�rio
        scanf("%d", &opcao);
        // Fun��o que limpa o buffer do teclado (os espa�os)
        getchar();

        // Switch da escolha do usu�rio do Menu Principal
        switch(opcao) {
            // Caso o usu�rio escolha a op��o '1. Cadastros'
            case 1:
                submenuCadastros();
                break;

            // Caso o usu�rio escolha a op��o '2. Vendas'
            case 2:
                submenuVendas();
                break;

            // Caso o usu�rio escolha a op��o '3. Abertura de Caixa'
            case 3:
                submenuCaixa();
                break;

            // Caso o usu�rio escolha a op��o '4. Fechamento de Caixa'
            case 4:
                fecharCaixa();
                break;

            // Caso o usu�rio escolha a op��o '5. Relat�rios'
            case 5:
                submenuRelatorios();
                break;

            // Caso o usu�rio escolha a op��o '6. Sair'
            case 6: {
                // Vari�vel do tipo caractere para armazenar a escolha da Dona Ber�
                char guardarDados;
                // Pergunta se deseja guardar os dados cadastrados do dia
                printf("Deseja guardar as informacoes de Clientes, Produtos, Vendas e Pagamentos? (s/n): ");
                // Fun��o que faz a leitura da escolha do usu�rio
                scanf(" %c", &guardarDados);

                // Se a Dona Ber� desejar salvar todos os dados do dia, entrar� aqui
                if (guardarDados == 's' || guardarDados == 'S') {
                    printf("Dados salvos com sucesso!\n");
                }
                // Exibe uma mensagem de agradecimento
                printf("Obrigado por comprar na Mercearia da Dona Bere! Volte sempre!\n");
                break;
            }

            // Caso o usu�rio n�o escolha nenhuma das op��es acima
            default:
                printf("Opcao invalida. Tente novamente\n\n");
        }
    } while (opcao != 6); // Enquanto n�o escolher '6. Sair', repete o loop
    return 0;
}

// Fun��o que exibe as categorias do Menu Principal
void menuPrincipal() {
    printf("\n=========== MENU PRINCIPAL ===========\n\n");
    printf(" 1. Cadastros\n 2. Vendas\n 3. Abertura de Caixa\n 4. Fechamento de Caixa\n 5. Relatorios\n 6. Sair\n\n");

    // Pergunta ao usu�rio qual op��o do menu deseja escolher
    printf("Escolha uma opcao: ");
}

// Fun��o do submenu da op��o '1. Cadastros'
void submenuCadastros() {
    // Vari�vel do tipo inteiro que armazenar� a escolha do usu�rio
    int opcao;

    // In�cio do loop Do While
    do {
        printf("\n===== CADASTROS =====\n\n");
        printf(" 1. Cadastro de Clientes\n 2. Cadastro de Produtos\n 3. Retornar ao Menu Principal\n\n");

        // Pergunta ao usu�rio qual op��o do menu deseja escolher
        printf("Escolha uma opcao: ");
        // Fun��o que faz a leitura da escolha do usu�rio
        scanf("%d", &opcao);
        // Fun��o que limpa o buffer do teclado (os espa�os)
        getchar();

        // Switch da escolha do usu�rio do submenu da op��o '1. Cadastros'
        switch(opcao) {
            // Caso o usu�rio escolha o op��o 1. Cadastro de Clientes
            case 1:
                cadastrarCliente();
                break;

            // Caso o usu�rio escolha a op��o 2. Cadastro de Produtos
            case 2:
                cadastrarProduto();
                break;
        }
    } while(opcao != 3); // Enquanto n�o escolher '3. Retornar ao Menu Principal', repete o loop
}

// Fun��o do submenu da op��o '2.Vendas'
void submenuVendas() {
    // Vari�vel do tipo inteiro que armazenar� a escolha do usu�rio
    int opcao;

    // In�cio do loop Do While
    do {
        printf("\n===== VENDAS =====\n\n");
        printf(" 1. Nova Venda\n 2. Retirada de Caixa (Sangria)\n 3. Pagamento\n 4. Retornar ao Menu Principal\n\n");

        // Pergunta ao usu�rio qual op��o do menu deseja escolher
        printf("Escolha uma opcao: ");
        // Fun��o que faz a leitura da escolha do usu�rio
        scanf("%d", &opcao);
        // Fun��o que limpa o buffer do teclado (os espa�os)
        getchar();

        // Switch da escolha do usu�rio do submenu da op��o '2. Vendas'
        switch(opcao) {
            // Caso o usu�rio escolha o op��o 1. Nova Venda
            case 1:
                novaVenda();
                break;

            // Caso o usu�rio escolha o op��o 2. Retirada de Caixa (Sangria)
            case 2:
                retiradaCaixa();
                break;

            // Caso o usu�rio escolha o op��o 3. Pagamento
            case 3:
                pagamentoVenda();
                break;
        }
    } while(opcao != 4); // Enquanto n�o escolher '4. Retornar ao Menu Principal', repete o loop
}

// // Fun��o do submenu da op��o '3. Abertura de Caixa'
void submenuCaixa() {
    abrirCaixa();
}

// Fun��o do submenu da op��o '4. Fechamento de Caixa'
void submenuRelatorios() {
    listarClientes();
    listarProdutos();
}

// Fun��o para cadastrar os dados do Cliente
void cadastrarCliente() {
    StructCliente novo;

    // Abre o arquivo para adicionar o cliente
    FILE *f = fopen("clientes.txt", "a");

    // Se der erro no arquivo, exibir� uma mensagem de erro
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

    /* Gera um c�digo aleat�rio para o cliente,
    rand() % 10000 � uma express�o que gera um n�mero inteiro pseudoaleat�rio no intervalo de 0 a 9999 */
    novo.codigo = rand() % 10000;

    // Salva os dados do cliente no arquivo
    salvarClienteEmArquivo(novo);

    // C�digo do Cliente
    printf("\nCliente cadastrado com codigo: %d\n\n", novo.codigo);

    // Fun��o que fecha o arquivo
    fclose(f);
}

// Fun��o para cadastrar os dados do Produto
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

    // Gera um c�digo aleat�rio para o produto
    p.codigo = rand() % 1000 + 1000;

    produtos[totalProdutos++] = p;

    // Salva os dados do produto no arquivo
    salvarProdutoEmArquivo(p);

    // C�digo do Produto
    printf("\nProduto cadastrado com codigo: %d\n\n", p.codigo);
}

// Fun��o para fazer as compras dos Produtos
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
        // Solicita ao usu�rio o c�digo do produto que deseja
        printf("Informe o codigo do produto a ser comprado: ");
        // Fun��o que faz a leitura da escolha do usu�rio
        scanf("%d", &codigo);

        StructProduto *p = buscarProdutoPorCodigo(codigo);

        // Se o c�digo do produto que o usu�rio buscou n�o estiver no estoque
        if(!p || p->quantidade <= 0){
            printf("Produto indisponivel.\n");
            continue;
        }

        float precoVenda = calcularPrecoVenda(p->precoCompra, p->margemLucro);

        printf(" Descricao: %s Preco: R$ %.2f\n Estoque: %d\n\n", p->descricao, precoVenda, p->quantidade);

        // Solicita ao usu�rio a quantidade de produtos que deseja
        printf("Informe a quantidade: ");
        // Fun��o que faz a leitura da escolha do usu�rio
        scanf("%d", &qtd);

        // O tra�o angular direito serve para apontar para o endere�o da vari�vel
        if(qtd > p->quantidade) qtd = p->quantidade;
        p->quantidade -= qtd;
        float subtotal = qtd * precoVenda;
        total += subtotal;

        // Exibe o total da compra e pergunta ao usu�rio se ele deseja adicionar mais produtos
        printf("Subtotal: R$ %.2f\nDeseja adicionar mais produtos? (s/n): ", subtotal);
        // Fun��o que faz a leitura da escolha do usu�rio
        scanf(" %c", &continuar);
    }
    printf("Total da venda: R$ %.2f\n\n", total);
    caixa += total;
}

// Fun��o da op��o do submenu 2.Venda
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

    // Solicita ao usu�rio o c�digo do produto que ele comprou
    printf("\nDigite o codigo da venda para pagamento: ");
    // Fun��o que faz a leitura da escolha do usu�rio
    scanf("%d", &codigoVenda);

    // Calcular o total da venda
    for (int i = 0; i < totalItens; i++) {
        if (itensVenda[i].codigoVenda == codigoVenda) {
            totalVenda += itensVenda[i].totalItem;
            encontrada = 1;
        }
    }

    // Se o produto n�o foi encontrado ou j� foi paga
    if (!encontrada) {
        printf("Venda nao encontrada ou ja paga.\n");
        return;
    }

    int opcao;
    float valorPago = 0;
    char tipoPagamento[3];

    // In�cio do Do While
    do {
        printf("\n1. Pagamento no cartao\n2. Pagamento em dinheiro\n3. Retornar ao Menu Principal\nInforme a opcao: ");
        // Fun��o que faz a leitura da escolha do usu�rio
        scanf("%d", &opcao);

        // Se escolher o pagamento no cart�o
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

            // Se o usu�rio n�o tiver condi��es de conseguir pagar o valor inteiro da compra no dinheiro, o resto poder� ser no cart�o
            if (recebido < totalVenda) {
                float restante = totalVenda - recebido;
                printf("Faltam R$ %.2f. Deseja pagar o restante no cartao? (1 - Sim, 0 - Nao): ", restante);
                int resposta;
                scanf("%d", &resposta);

                // Se ele conseguir pagar o restante com o cart�o
                if (resposta == 1) {
                    valorPago = totalVenda;
                    strcpy(tipoPagamento, "dc");
                    float troco = 0;
                    printf("Valor pago R$ %.2f em dinheiro e R$ %.2f no cartao.\n", recebido, restante);
                    break;
                // Se ele n�o conseguir pagar de jeito nenhum
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

    // Depois de todo o processo, exibe uma mensagem de pagamento conclu�do
    printf("Pagamento registrado com sucesso!\n");
}

// Fun��o que salva os dados do pagamento em arquivo
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

// Fun��o do dinheiro dispon�vel que est� no caixa, especialmente para troco
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

// Fun��o de Abertura de Caixa
void abrirCaixa() {
    // Se o caixa j� est� aberto com dinheiro
    if(caixaAberto) {
        printf("Caixa j� est� aberto.\n");
        return;
    }

    // Solicita a Dona Ber� o valor que ocorrer� a abertura de caixa
    printf("Digite o valor de abertura do caixa: R$ ");
    // Fun��o que faz a leitura da escolha do usu�rio
    scanf("%f", &abertura);

    caixa = abertura;
    caixaAberto = 1;

    // Exibe com quantos Reais o caixa foi aberto
    printf("Caixa aberto com R$ %.2f\n\n", caixa);
}

// Fun��o de Fechamento de Caixa, exibindo os saldos do dia
void fecharCaixa() {
    printf("\n===== FECHAMENTO DE CAIXA =====\n\n");
    printf("Valor inicial: R$ %.2f\n", abertura);
    printf("Valor final em caixa: R$ %.2f\n", caixa);
    printf("Total movimentado: R$ %.2f\n\n", caixa - abertura);
    caixaAberto = 0;
}

// Fun��o que exibe a lista de Clientes no Terminal quando o usu�rio escolhe a op��o '5. Relat�rios'
void listarClientes() {
    FILE *f = fopen("clientes.txt", "r");
    if(!f) return;
    char linha[200];
    printf("\n===== CLIENTES =====\n\n");
    while(fgets(linha, sizeof(linha), f)) printf("%s", linha);
    fclose(f);
}

// Fun��o que exibe a lista de produtos no Terminal quando o usu�rio escolhe a op��o '5. Relat�rios'
void listarProdutos() {
    FILE *f = fopen("produtos.txt", "r");
    if(!f) return;
    char linha[200];
    printf("\n===== PRODUTOS =====\n\n");
    while(fgets(linha, sizeof(linha), f)) printf("%s", linha);
    fclose(f);
}

// Fun��o que faz o c�lculo do Pre�o de Venda com Lucro
float calcularPrecoVenda(float precoCompra, float margem) {
    return precoCompra + (precoCompra * margem / 100);
}

// Faz com que percorra por toda a estrutura para achar o c�digo do produto espec�fico
StructProduto* buscarProdutoPorCodigo(int codigo) {
    for(int i = 0; i < totalProdutos; i++) {
        if(produtos[i].codigo == codigo)return &produtos[i];
    }
    return NULL;
}

// Fun��o que salva os dados do Cliente em arquivo
void salvarClienteEmArquivo(StructCliente c) {
    // Abre o arquivo de Clientes
    FILE *f = fopen("clientes.txt", "a");
    if(!f) return;
    fprintf(f, "Codigo: %d\nNome Completo: %sNome Social: %sCPF: %sEndereco: %sBairro: %sCelular: %s\n\n", c.codigo, c.nomeCompleto, c.nomeSocial, c.cpf, c.endereco, c.bairro, c.celular);
    // Fun��o que fecha o arquivo
    fclose(f);
}

// Fun��o que salva os dados do Produto em arquivo
void salvarProdutoEmArquivo(StructProduto p) {
    // Abre o arquivo de Produtos
    FILE *f = fopen("produtos.txt", "a");
    if(!f) return;
    float precoVenda = calcularPrecoVenda(p.precoCompra, p.margemLucro);
    fprintf(f, "Codigo: %d\nDescricao: %sCategoria: %sPreco Compra: %.2f\nMargem: %.2f%%\nPreco Venda: %.2f\nEstoque: %d (min %d)\n\n", p.codigo, p.descricao, p.categoria, p.precoCompra, p.margemLucro, precoVenda, p.quantidade, p.estoqueMinimo);
    // Fun��o que fecha o arquivo
    fclose(f);
}
