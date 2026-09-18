#include <iostream>
#include "TGrafo_ND.h"
#include <fstream>

/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

// Construtor do TGrafo Non-Oriented
TGrafo_ND::TGrafo_ND(int n){
    this->n = n;
    // No inicio dos tempos nao ha arestas
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

// Destructor, responsavel por
// liberar a memoria alocada para a matriz
TGrafo_ND::~TGrafo_ND(){
	n = 0;
	m = 0;
	delete [] *adj;
	std::cout << "espaco liberado";
}

// ⚠️EXERCICIO 7 - RELATORIO
void TGrafo_ND::readfile(const char* grafo_example){
    std::ifstream file(grafo_example);
    if(!file.is_open()){
        std::cout << "ERROR - Unable to access file" << std::endl;
        return;
    }

    int V;
    int A;
    file >> V;
    file >> A;

    int a1, a2;
    for(int y = 0; y < A; y++){
        file >> a1 >> a2;
        NDinsereA(a1, a2);
    }
    file.close();
}

// ⚠️EXERCICIO 8 (Funções ND) - RELATORIO

// Insere uma aresta no Grafo tal que
// v  adjacente a w
void TGrafo_ND::NDinsereA(int v, int w){
    // testa se nao temos a aresta
    if(adj[v][w] == 0 && adj[w][v] == 0){
        // Both ways
        adj[v][w] = 1;
        adj[w][v] = 1;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafo_ND::NDremoveA(int v, int w){
    // testa se temos a aresta
    if(adj[v][w] == 1 && adj[w][v] == 1){
        adj[v][w] = 0;
        adj[w][v] = 0;
        m--; // atualiza qtd arestas
    }
}

// ⚠️EXERCICIO 9 - RELATORIO
int TGrafo_ND::degree(int v){
    int ingrau_nd = 0;
    for(int b = 0; b < n; b++){
        if(adj[v][b] == 1){
            ingrau_nd++;
        }
    }
    return ingrau_nd;
}

// ⚠️EXERCICIO 11 - RELATORIO
void TGrafo_ND::removeV(int v) {
    if (v < 0 || v >= this->n) {
        throw std::runtime_error("Vertice fora dos limites\n");
    }

    for (int i = 0; i < this->n; i++) {
        if (adj[v][i] == 1)
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
    delete[] this->adj[this->n];
}

// ⚠️EXERCICIO 12 - RELATORIO
bool TGrafo_ND::isComplete() {
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
int** TGrafo_ND::complemento() {
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

// ⚠️EXERCICIO 15 - RELATORIO
int TGrafo_ND::conexidade_nao_direcionado() {
    if (this->n <= 1)
        return 0;

    bool* visitado = new bool[this->n]();
    int* fila = new int[this->n];
    int inicio = 0;
    int fim = 0;

    visitado[0] = true;
    fila[fim++] = 0;

    while (inicio < fim) {
        int vertice = fila[inicio++];

        for (int vizinho = 0; vizinho < this->n; vizinho++) {
            if (this->adj[vertice][vizinho] == 1 && !visitado[vizinho]) {
                visitado[vizinho] = true;
                fila[fim++] = vizinho;
            }
        }
    }

    int resultado = 0;
    for (int i = 0; i < this->n; i++) {
        if (!visitado[i]) {
            resultado = 1;
            break;
        }
    }

    delete[] visitado;
    delete[] fila;

    return resultado;
}

void _printMatriz();
void _show();
void TGrafo_ND::NDshow(){
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for( int i=0; i < n; i++){
        std::cout << "\n";
        for( int w=0; w < n; w++)
            if(adj[i][w] == 1)
                std::cout << "Adj[" << i<< "," << w << "]= 1" << " ";
            else std::cout << "Adj[" << i<< "," << w << "]= 0" << " ";
    }

    // Respota 9
    std::cout << "\nRESPOSTA 9)\n";
    for(int index = 0; index < n; index++){
        std::cout << "Grau do vertice " << index << ": " << degree(index) << std::endl;
    }

    // Resosta 11
    std::cout << "\nRESPOSTA 11)\n";
    _show();
    removeV(4);
    _show();

    // Resosta 12
    std::cout << "\nRESPOSTA 12)\n";
    std::cout << "O grafo G " << (isComplete() ? "" : "nao ") << "eh completo!" << std::endl;

    // Resposta 14)
    std::cout << "\n\nRESPOSTA 14)\n";
    int** comp = complemento();

    std::cout << "Matriz original:" << std::endl;
    _show();

    std::cout << "\nMatriz complemento:" << std::endl;
    _printMatriz(comp);

    for (int i = 0; i < this->n; i++)
        delete[] comp[i];
    delete[] comp;

    // Resposta 15)
    std::cout << "\nRESPOSTA 15)\n";
    std::cout << "O grafo G " << (conexidade_nao_direcionado() == 0 ? "eh conexo!" : "eh desconexo!") << std::endl;
    
    std::cout << "\nfim da impressao do grafo." << std::endl;
}

void TGrafo_ND::_printMatriz(int** matriz) {
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

void TGrafo_ND::_show() {
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