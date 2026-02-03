#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <vector>

#include <iomanip>

#include <limits>

#include <string>

#include <ctime>

#include <cctype>

using namespace std;

struct Stock{
    int cod_Produto;
   string nome_Produto;
   int stock_Produto;
   double preco_Produto;
};

//Estoque inicial

vector<Stock> produtos = {
    {1, "MOUSE", 50, 12.00},
    {2, "TECLADO", 30, 18.20},
    {3, "HEADSET", 20, 20.80}
};

//Verificação de inteiro

int lerQuantidade() {

    int valor;

    while (true) {

        cin >> valor;

        if (cin.fail() || cin.peek() != '\n') {
            cout << "Erro: Entrada invalida! Digite apenas numeros inteiros.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        else if (valor < 0) { // Alterado para permitir 0 (sair)
            cout << "Erro: A quantidade deve ser maior ou igual a zero.\n";
        }

        else {
            return valor;
        }
    }
}

//Verificação de números

double lerQuantidadeDouble() {

    double valor;

    while (true) {

        cin >> valor;

        if (cin.fail() || cin.peek() != '\n') {
            cout << "Erro: Entrada invalida! Digite apenas numeros inteiros.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        else if (valor <= 0) {
            cout << "Erro: A quantidade deve ser maior que zero.\n";
        }

        else {
            return valor;
        }

    }

}

//Validacao de um produto ja existente

bool nomeProdutoExistente(string nome) {

    for (const auto& s : produtos)

    {
        if (s.nome_Produto == nome){
            return true;
        }
    }

    return false;
}

//Função para adicionar produtos

void adicionarProduto() {

    Stock novo;

    cout << "\nAdicionar novo produto\n";

    cout << "---------------------------------" << endl;

    do{

        cout << "\nNome do produto: " << endl;
        cin >> novo.nome_Produto;
        
        // --- BLOCO PARA TRANSFORMAR EM MAIUSCULA ---
        for (auto &c : novo.nome_Produto) {
            c = toupper(c);
        }

        if (nomeProdutoExistente(novo.nome_Produto)){
            cout << "\nProduto ja existente! \n";
        }

    } while (nomeProdutoExistente(novo.nome_Produto));

    novo.cod_Produto = produtos.size() + 1;

    cout << "\nQuantidade inicial em stock: " << endl;
    novo.stock_Produto = lerQuantidade();

    cout << "\nPreco de custo: " << endl;
    novo.preco_Produto = lerQuantidadeDouble();

    produtos.push_back(novo);

    cout << "\nProduto adicionado com sucesso! \n";
}

//Função para editar produtos

void editarProduto() {
    int cod_Busca;

    cout << "\nEditar produto existente\n";

    cout << "---------------------------------" << endl;

    bool encontrado = false;

    do
    {
        cout << "\nDigite o codigo do produto que deseja editar: " << endl;
        cod_Busca = lerQuantidade();

        for (auto& produto : produtos) {

            if (cod_Busca == produto.cod_Produto) {

                encontrado = true;

                cout << "\nNovo nome do produto: " << endl;
                cin >> produto.nome_Produto;

                // --- BLOCO PARA TRANSFORMAR EM MAIUSCULA ---
                for (auto &c : produto.nome_Produto) {
                    c = toupper(c);
                }

                cout << "\nNova quantidade em stock: " << endl;
                produto.stock_Produto = lerQuantidade();

                cout << "\nNovo preco de custo: " << endl;
                produto.preco_Produto = lerQuantidadeDouble();

                cout << "\n*** Produto editado com sucesso! ***" << endl;
                return;
            }
        }

        cout << "\nProduto com o codigo " << cod_Busca << " nao encontrado." << endl;
    } while (encontrado == false);
}

//Função para deletar produtos

void deletarProduto() {
    int cod_Busca;

    cout << "\nDeletar produto existente\n";

    cout << "---------------------------------" << endl;

    bool encontrado = false;

    //REVER ESSA FUNÇÃO DE DELETAR PRODUTOS

    // do
    // {
    //     cout << "\nDigite o codigo do produto que deseja deletar: " << endl;
    //     cod_Busca = lerQuantidade();

    //     for (auto it = produtos.begin(); it != produtos.end(); ++it) {

    //         if (cod_Busca == it->cod_Produto) {

    //             encontrado = true;

    //             produtos.erase(it);

    //             cout << "\n*** Produto deletado com sucesso! ***" << endl;
    //             return;
    //         }
    //     }

    //     cout << "\nProduto com o codigo " << cod_Busca << " nao encontrado." << endl;
    // } while (encontrado == false);
}

//Função para calcular preço de venda e IVA

double calculaPrecoVenda(double precoCusto) {
    return precoCusto * 1.3;
}

double calcularPrecoVendaIVA(double precoVenda) {
    return precoVenda * 1.23;
}

//Função para carrinho de compras

struct Carrinho{
    int cod_Produto;
    string nome_Produto;
    int quantidade_Produto;
    double preco_Produto;
};

vector<Carrinho> itemCarrinho;

void listarCarrinho() {

    cout << "\nItens no Carrinho:" << endl << endl;

    double total_Carrinho = 0;

    for (const auto& Item : itemCarrinho) {
        cout << "Codigo: " << Item.cod_Produto;
        cout << ", Nome: " << Item.nome_Produto;
        cout << ", Quantidade: " << Item.quantidade_Produto;

        double precoVenda = calculaPrecoVenda(Item.preco_Produto / Item.quantidade_Produto);
        double precoIVA = calcularPrecoVendaIVA(precoVenda) * Item.quantidade_Produto;

        cout << ", Preco: $" << precoVenda * Item.quantidade_Produto << endl;
        cout << ", Preco IVA: $" << precoIVA - (precoVenda * Item.quantidade_Produto) << endl;

        total_Carrinho += precoIVA;
    }

    cout << "\nValor total com IVA: $" << total_Carrinho << endl;
}

double totalCarrinho() {

    double total = 0;

    for (const auto& Item : itemCarrinho) {
        double precoVenda = calculaPrecoVenda(Item.preco_Produto / Item.quantidade_Produto);
        total += calcularPrecoVendaIVA(precoVenda) * Item.quantidade_Produto;
    }

    return total;
}

//Função para listar produtos

void listarProdutos() {

    cout << "\nLista de Produtos Disponiveis:" << endl << endl;

    for (const auto& s : produtos) {
        cout << "Codigo: " << s.cod_Produto;
        cout << ", Nome: " << s.nome_Produto;
        cout << ", Stock: " << s.stock_Produto;

        double precoIVA = calcularPrecoVendaIVA(calculaPrecoVenda(s.preco_Produto));

        cout << ", Preco: $" << precoIVA << endl;
    }

    cout << "\nPressione Enter para escolher o produto..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cin.get();
}

//Função para vender produtos

void venderProduto() {

    listarProdutos();

    int cod_Busca, qtd_Desejada;

    do {
        cout << "\nDigite o codigo do produto que deseja comprar (0 para sair): " << endl;
        cod_Busca = lerQuantidade();

        if (cod_Busca == 0){
            return;
        }

        bool encontrado = false;

        for (auto& produto : produtos) {

            if (cod_Busca == produto.cod_Produto) {
                encontrado = true;

                do {
                    cout << "\nDigite a quantidade que deseja comprar (stock atual: " << produto.stock_Produto << "): " << endl;
                    qtd_Desejada = lerQuantidade();

                    if (qtd_Desejada > produto.stock_Produto) {
                        cout << "Quantidade solicitada excede o stock disponivel." << endl;
                    }

                } while (qtd_Desejada > produto.stock_Produto);

                Carrinho novoItem;

                novoItem.cod_Produto = produto.cod_Produto;
                novoItem.nome_Produto = produto.nome_Produto;
                novoItem.quantidade_Produto = qtd_Desejada;
                novoItem.preco_Produto = produto.preco_Produto * qtd_Desejada;

                itemCarrinho.push_back(novoItem);

                double precoVendaIVA = calcularPrecoVendaIVA(calculaPrecoVenda(produto.preco_Produto));
                double total = precoVendaIVA * qtd_Desejada;

                cout << "\nProduto adicionado ao carrinho. Total: $" << total << "\nDeseja continuar comprando? (1 - Sim, 0 - Nao): " << endl;
                int continuar;

                cin >> continuar;

                if (continuar == 1) {
                  venderProduto();
                }else {

                    listarCarrinho();

                    cout << "\nDigite 1 para continuar comprando ou 0 para finalizar a compra..." << endl;
                    int opcao = lerQuantidade();

                    if (opcao != 0) {
                        venderProduto();
                    }else {
 
                        if (!itemCarrinho.empty()) {
 
                            listarCarrinho();
 
                            cout << "\nDeseja realizar pagamento? (1 - Sim / 0 - Cancelar tudo)" << endl;
                            int confirmar = lerQuantidade();
 
                            if (confirmar == 1) {
 
                            double totalGeral = totalCarrinho();                                 
                                 
                            double valorPago = 0;
                            double troco = 0;
 
                            int sorteio = rand() % 100 + 1;
       
                            if (sorteio == 7) {
                                cout << "\n***********************************" << endl;
                                cout << "PARABENS! Voce foi sorteado!" << endl;
                                cout << "Esta venda e por conta da casa (Total: $0.00)" << endl;
                                cout << "***********************************" << endl;
                                totalGeral = 0; // Zera o total para o recibo e pagamento
                            }
 
                            if (totalGeral > 0) {
                                cout << "Valor entregue pelo cliente: ";

                                do
                                {
                                    valorPago = lerQuantidadeDouble();
                                    if(valorPago < totalGeral) cout << "Valor insuficiente! Insira um novo valor\n";
                                } while (valorPago < totalGeral);

                                troco = valorPago - totalGeral;

                                cout << "\nTroco: " << troco << " euros\n";
                            }
 
                            cout << "\nDeseja fatura? (1 - Sim / 0 - Nao)" << endl;
 
                            if (lerQuantidade() == 1) {

                                int contadorVenda = 1;

                                cout << "Inserir NIF: ";
                                int NIF = lerQuantidade();

                                cout << "\n-------------------------------\n";
                                cout << "        RECIBO DE VENDA        \n";
                                cout << "-------------------------------\n";
                                cout << "Numero de fatura: FT0026" << contadorVenda << endl;
                                cout << "NIF Cliente: " << NIF << endl;

                                time_t agora = time(0);
                                char* dt = ctime(&agora);
                                cout << "Data e hora: " << dt;

                                cout << "-------------------------------\n";
                                listarCarrinho();
                                cout << "-------------------------------\n";
                                cout << "Total a pagar: " << totalGeral << " euros\n";
                                cout << "Valor entregue: " << valorPago << " euros\n";
                                cout << "Troco: " << troco << " euros\n";
                                cout << "Obrigado e volte sempre!\n";
                            }

                            for (const auto& item : itemCarrinho) {

                                for (auto& p : produtos) {
                                    if (p.cod_Produto == item.cod_Produto) p.stock_Produto -= item.quantidade_Produto;
                                }
                            }
                            itemCarrinho.clear();
                        }
                    }}
                }
                return;
            }
        }

        if (!encontrado){
            cout << "\nProduto com o codigo " << cod_Busca << " nao encontrado." << endl;
        }

    } while (true);
}

//Função do menu de produtos

void menuProdutos(){
    int escolha;

    do {
        
        cout << "-------------------------------\n";
        cout << "Vendinha do E&G TECH" << endl;
        cout << "\n--- MENU PRODUTOS ---" << endl;
        cout << "1 - Editar produto \n2 - Adicionar produto \n3 - Deletar produto \n0 - Sair\n";
        cout << "-------------------------------\n";
        escolha = lerQuantidade();
        
        switch (escolha)
        {
            case 1:
                editarProduto();
                break;
            
            case 2:
                adicionarProduto();
                break;

            case 3:
                deletarProduto();
                break;

            case 0:
                cout << "Sair" << endl;
                break;
            
            default:
                cout << "Opcao invalida." << endl;
                break;
        }
    } while (escolha != 0);
}
    
void menuPrincipal(int Op) {

    switch (Op) {

    case 1: 
        venderProduto();
        break;

    case 2:
        menuProdutos();
        break;

    case 0:
        cout << "Sair" << endl;
        break;

    default:
        cout << "Opcao invalida." << endl;
        break;
    }
}

int main() {

    cout << fixed << setprecision(2);
    int Op;

    do {

        cout << "-------------------------------\n";
        cout << "Vendinha do E&G TECH" << endl;
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1 - Venda \n2 - Produtos \n0 - Sair\n";
        cout << "-------------------------------\n";
        Op = lerQuantidade();

        menuPrincipal(Op);

    } while (Op != 0);
}