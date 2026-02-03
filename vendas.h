#pragma once

#include <iostream>
#include <string>

using namespace std;

//Função para listar produtos

struct Stock
{
    int cod_Produto;
    string nome_Produto;
    int stock_Produto;
    float preco_Produto;
};

Stock produtos[6]={
    {1, "Produto A", 10, 5.99},
    {2, "Produto B", 20, 3.49},
    {3, "Produto C", 15, 7.89},
    {4, "Produto D", 25, 9.99},
    {5, "Produto E", 30, 12.99},
    {6, "Produto F", 35, 15.99}
};

void listarProdutos() {

    cout << "\nLista de Produtos Disponiveis:" << endl << endl;

    for (const auto& Stock : produtos) {
        cout << "Codigo: " << Stock.cod_Produto;
        cout << ", Nome: " << Stock.nome_Produto;
        cout << ", Stock: " << Stock.stock_Produto;
        cout << ", Preco: $" << Stock.preco_Produto << endl;
    }

    cout << "\nPressione Enter para escolher o produto..." << endl;
    cin.ignore();
    cin.get();
}