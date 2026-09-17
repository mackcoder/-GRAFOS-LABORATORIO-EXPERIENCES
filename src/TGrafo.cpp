#include <iostream>
#include "TGrafo.h"
#include <fstream>
#include <stdexcept>

/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

// Construtor do TGrafo
TGrafo::TGrafo( int n ){
    this->n = n;
    // No in�cio dos tempos n�o h� arestas
    this->m = 0; 
    // aloca da matriz do TGrafo
    int **adjac = new int*[n];
    for(int i = 0; i < n; i++)
    	adjac[i]= new int[n];
    adj = adjac;
    // Inicia a matriz com zeros
	for(int i = 0; i< n; i++)
		for(int j = 0; j< n; j++)
			adj[i][j]=0;	
}

// Destructor, respons�vel por
// liberar a mem�ria alocada para a matriz
TGrafo::~TGrafo(){
	n = 0;
	m = 0;
	delete [] *adj;
	std::cout << "espa�o liberado";
}

// Insere uma aresta no Grafo tal que
// v � adjacente a w
void TGrafo::insereA(int v, int w){
    // testa se nao temos a aresta
    if(adj[v][w] == 0 ){
        adj[v][w] = 1;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w){
    // testa se temos a aresta
    if(adj[v][w] == 1 ){
        adj[v][w] = 0;
        m--; // atualiza qtd arestas
    }
}

// ⚠️EXERCICIO 1 - RELATORIO
int TGrafo::inDegree(int v){
    int ingrau = 0;
    for(int t = 0; t < n; t++){
        if(adj[t][v] == 1)  
            ingrau++;
    }
    return ingrau;
}

// ⚠️EXERCICIO 2 - RELATORIO
int TGrafo::outDegree(int v){
    int outgrau = 0;
    for(int t = 0; t < n; t++){
        if(adj[v][t] == 1)  
            outgrau++;
    }
    return outgrau;
}

// ⚠️EXERCICIO 3 - RELATORIO
int TGrafo::degree(int v){
    int grau_total = 0;
    for(int t = 0; t < n; t++){
        if(adj[v][t] == 1)  
            grau_total++;

        if(adj[t][v] == 1)
            grau_total++;
    }
    return grau_total;
}

// ⚠️EXERCICIO 4 - RELATORIO
bool TGrafo::Fonte_check(int v){
    int outgrau = 0;
    for(int t = 0; t < n; t++){
        if(adj[v][t] == 1)  
            outgrau++;
    }

    int ingrau = 0;
    for(int t = 0; t < n; t++){
        if(adj[t][v] == 1)  
            ingrau++;
    }
    if (outgrau > 0 && ingrau == 0)
        return 1;
    else
        return 0;

}

// ⚠️EXERCICIO 5 - RELATORIO
bool TGrafo::Sorvedouro(int v){
    int outgrau = 0;
    for(int t = 0; t < n; t++){
        if(adj[v][t] == 1)  
            outgrau++;
    }

    int ingrau = 0;
    for(int t = 0; t < n; t++){
        if(adj[t][v] == 1)  
            ingrau++;
    }
    if (outgrau == 0 && ingrau > 0)
        return 1;
    else
        return 0;
}

// ⚠️EXERCICIO 6 - RELATORIO
int TGrafo::isSymetric(){
    for(int a = 0; a < n; a++){
        for(int b = 0; b < n; b++){
            // Checando se todo o grafo é simétrico:
            if(adj[a][b] != adj[b][a])
                return 0;
        }
    }
    return 1;
}

// ⚠️EXERCICIO 10 - RELATORIO

// ⚠️EXERCICIO 11 - RELATORIO
void TGrafo::removeV(int v) {
    if (v < 0 || v >= this->n) {
        throw std::runtime_error("Vertice fora dos limites\n");
    }

    for (int i = 0; i < this->n; i++) {
        if (adj[v][i] == 1)
            this->m--;

        if (adj[i][v] == 1)
            this->m--;
    }
    
    if (v < this->n-1) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1; j++) {
                adj[i][j] = adj[i + (i >= v)][j + (j >= v)];
            }
        }
    }

    this->n--;
}

// ⚠️EXERCICIO 12 - RELATORIO
// ⚠️EXERCICIO 13 - RELATORIO
bool TGrafo::isComplete() {
    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++) {
            // Diagonal principal = 0
            if (i == j) {
                if (this->adj[i][j] != 0) return false; 
            }
            
            // Outros valores na matriz == 1
            else
                if (this->adj[i][j] != 1) return false;
        }
    }

    return true;
}

// ⚠️EXERCICIO 14 - RELATORIO
int** TGrafo::complemento() {
    int** adjComp = new int*[this->n];

    for (int i = 0; i < this->n; i++) {
        adjComp[i] = new int[this->n];

        for (int j = 0; j < this->n; j++) {
            if (i == j)
                adjComp[i][j] = 0;
            else
                adjComp[i][j] = this->adj[i][j] ? 0 : 1;
        }
    }

    return adjComp;
}

void _show();
void _printMatriz(int** matriz);
// Apresenta o Grafo contendo
// n�mero de v�rtices, arestas
// e a matriz de adjac�ncia obtida
void TGrafo::show(){
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for( int i=0; i < n; i++){
        std::cout << "\n";
        for( int w=0; w < n; w++)
            if(adj[i][w] == 1)
                std::cout << "Adj[" << i<< "," << w << "]= 1" << " ";
            else std::cout << "Adj[" << i<< "," << w << "]= 0" << " ";
    }

    std::cout << "\n";
    // Funções sobre Grau:
    // Resposta 1)
    std::cout << "\nRESPOSTA 1)\n";
    for(int index = 0; index < n; index++){
        
        std::cout << "Grau de Entrada do vertice " << index << ": "<< inDegree(index) << std::endl; 
    }
    
    // Resposta 2)
    std::cout << "\nRESPOSTA 2)\n";
     for(int index = 0; index < n; index++){
        std::cout << "Grau de Saida do vertice " << index << ": "<< outDegree(index) << std::endl; 
    }
    
    // Resposta 3)
    std::cout << "\nRESPOSTA 3)\n";
    for(int v = 0; v < n; v++){
        std::cout << "Grau total do vertice " << v << ": " << degree(v) << std::endl;
    }

    //-----------------------------------------------------------------------------------//
    // Função Checa Fonte e Sorvedouro:
    // Resposta 4) && 5)
    std::cout << "\nRESPOSTA 4 e 5)\n";
    for(int v = 0; v < n; v++){
        std::cout << "Vertice " << v << " -> Fonte: " << Fonte_check(v) << "|| Sorvedouro: " << Sorvedouro(v) << std::endl;
    }

    // Função Checa Simétrico:
    // Resposta 6)
    std::cout << "\nRESPOSTA 6)\n";
    if(isSymetric())
        std::cout << "Retorno de checagem de simetria -> Return: " << isSymetric() <<std::endl; 
    else    
        std::cout << "Retorno de checagem de simetria -> Return: " << isSymetric() <<std::endl; 
    // Resposta 10)
    std::cout << "\nRESPOSTA 10)";

    // Resposta 11)
    std::cout << "\nRESPOSTA 11)\n";
    removeV(3);
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for( int i=0; i < n; i++){
        std::cout << "\n";
        for( int w=0; w < n; w++)
            if(adj[i][w] == 1)
                std::cout << "Adj[" << i<< "," << w << "]= 1" << " ";
            else std::cout << "Adj[" << i<< "," << w << "]= 0" << " ";
    }

    // Resposta 12)
    std::cout << "\n\nRESPOSTA 12)\n";
    std::cout << "O grafo G " << (isComplete() ? "" : "nao ") << "eh completo!" << std::endl;


    // Resposta 13)
    std::cout << "\n\nRESPOSTA 13)\n";
    std::cout << "O grafo G " << (isComplete() ? "" : "nao ") << "eh completo!" << std::endl;

    // Resposta 13)
    std::cout << "\n\nRESPOSTA 13)\n";
    int** comp = complemento();

    std::cout << "Matriz original:" << std::endl;
    _show();

    std::cout << "\nMatriz complemento:" << std::endl;
    _printMatriz(comp);

    for (int i = 0; i < this->n; i++)
        delete[] comp[i];
    delete[] comp;
    
    std::cout << "\nfim da impressao do grafo." << std::endl;
}

void TGrafo::_printMatriz(int** matriz) {
    std::cout << "   ";

    for (int j = 0; j < this->n; j++) {
        if (j > 0)
            std::cout << " ";
        std::cout << j;
    }

    std::cout << std::endl;

    for (int i = 0; i < this->n; i++) {
        std::cout << i << " [";

        for (int j = 0; j < this->n; j++) {
            if (j > 0)
                std::cout << " ";
            std::cout << matriz[i][j];
        }

        std::cout << "]" << std::endl;
    }
}

// ⚠️ Remover depois
void TGrafo::_show(){
    std::cout << "   ";

    for(int w = 0; w < this->n; w++){
        if(w > 0)
            std::cout << " ";
        std::cout << w;
    }

    std::cout << std::endl;

    for(int i = 0; i < this->n; i++){
        std::cout << i << " [";

        for(int w = 0; w < this->n; w++){
            if(w > 0)
                std::cout << " ";
            std::cout << this->adj[i][w];
        }

        std::cout << "]" << std::endl;
    }
}
