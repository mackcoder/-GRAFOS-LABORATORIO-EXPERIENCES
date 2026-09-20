#include <iostream>
#include "TGrafo.h"
#include <fstream>
#include <stdexcept>
#include <vector>


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
    	adjac[i] = new int[n];
    adj = adjac;
    /*
    // Inicia a matriz com zeros
	for(int i = 0; i< n; i++)
		for(int j = 0; j< n; j++)
			adj[i][j]=0;	
    */

    // Iniciar matriz com infinito:
    for(int i = 0; i< n; i++)
		for(int j = 0; j< n; j++)
			adj[i][j] = 0;	
}

// Destructor, responsavel por
// liberar a memoria alocada para a matriz
TGrafo::~TGrafo(){
    for(int del = 0; del < n; del++){
        delete [] adj[del];
    }
    delete [] adj;
	n = 0;
	m = 0;

	std::cout << "espaco liberado (grafo direcionado)" << std::endl;
    std::cout << "\n ---END OF PROGRAM---" << std::endl;
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
        // verifica se "chega" 
        // um 't' que chega em 'v' (alvo):
        // (0,0), (1,0)...
        if(adj[t][v] != 0)  
            ingrau++;
    }
    return ingrau;
}

// ⚠️EXERCICIO 2 - RELATORIO
int TGrafo::outDegree(int v){
    int outgrau = 0;
    for(int t = 0; t < n; t++){
        // verifica se "sai" 
        // de 'v' e chega em 't' (alvo):
        // (0,0), (0,1), (0,2)...
        if(adj[v][t] != 0)  
            outgrau++;
    }
    return outgrau;
}

// ⚠️EXERCICIO 3 - RELATORIO
int TGrafo::degree(int v) {
    return inDegree(v) + outDegree(v);
}

// ⚠️EXERCICIO 4 - RELATORIO
bool TGrafo::Fonte_check(int v){
    // Calcula os ingrau e outgrau de novo
    int outgrau = outDegree(v);
    int ingrau = inDegree(v);
    
    // Faz a verificacao por fonte:
    if (outgrau > 0 && ingrau == 0)
        return 1;
    else
        return 0;
}

// ⚠️EXERCICIO 5 - RELATORIO
bool TGrafo::Sorvedouro(int v){
    int outgrau = outDegree(v);
    int ingrau = inDegree(v);
    // Faz a verificacao por sorvedouro:
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

// ⚠️EXERCICIO 16 - RELATORIO
int TGrafo::conexidade_direcionado() {
    if (this->n <= 1)
        return 3;

    std::vector<std::vector<bool>> alcance(this->n, std::vector<bool>(this->n, false));

    for (int i = 0; i < this->n; i++) {
        alcance[i][i] = true;
        for (int j = 0; j < this->n; j++)
            if (this->adj[i][j] == 1)
                alcance[i][j] = true;
    }

    // Warshall
    for (int k = 0; k < this->n; k++)
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->n; j++)
                alcance[i][j] = alcance[i][j] || (alcance[i][k] && alcance[k][j]);

    bool c3 = true;
    bool c2 = true;

    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++) {
            if (!alcance[i][j])
                c3 = false;
            if (!alcance[i][j] && !alcance[j][i])
                c2 = false;
        }
    }

    if (c3)
        return 3;
    if (c2)
        return 2;

    // Ignora a direcao das arestas para diferenciar C1 de C0.
    std::vector<bool> visitado(this->n, false);
    std::vector<int> fila;
    visitado[0] = true;
    fila.push_back(0);

    for (int posicao = 0; posicao < static_cast<int>(fila.size()); posicao++) {
        int vertice = fila[posicao];

        for (int vizinho = 0; vizinho < this->n; vizinho++) {
            if ((this->adj[vertice][vizinho] == 1
                    || this->adj[vizinho][vertice] == 1)
                    && !visitado[vizinho]) {
                visitado[vizinho] = true;
                fila.push_back(vizinho);
            }
        }
    }

    for (int i = 0; i < this->n; i++)
        if (!visitado[i])
            return 0;

    return 1;
}

// ⚠️EXERCICIO 17 - RELATORIO
bool TGrafo::_reduzido_caminho(int x, int y) {
    if (x < 0 || x >= this->n || y < 0 || y >= this->n)
        return false;

    std::vector<bool> visitado(this->n, false);
    std::vector<int> pilha = {x};
    visitado[x] = true;

    while (!pilha.empty()) {
        int atual = pilha.back();
        pilha.pop_back();

        if (atual == y)
            return true;

        for (int vizinho = 0; vizinho < this->n; vizinho++) {
            if (this->adj[atual][vizinho] != 0 && !visitado[vizinho]) {
                visitado[vizinho] = true;
                pilha.push_back(vizinho);
            }
        }
    }

    return false;
}

bool _reduzido_usado(const std::vector<std::vector<int>>& g, int index) {
    for (int i = 0; i < (int) g.size(); i++) {
        for (int j = 0; j < (int) g[i].size(); j++) {
            if (g[i][j] == index)
                return true;
        }
    }

    return false;
}

int** TGrafo::reduzido(int& quantidadeComponentes) {
    std::vector<std::vector<int>> g;

    for (int i = 0; i < this->n; i++) {
        // Pula vertices ja usados
        if (_reduzido_usado(g, i)) continue;

        std::vector<int> gx = {i};

        for (int j = 0; j < this->n; j++) {
            if (i == j) continue;

            // Adiciona a lista gx se forem N+ e N-
            if (_reduzido_caminho(i, j) && _reduzido_caminho(j, i))
                gx.push_back(j);
        }

        g.push_back(gx);
    }

    quantidadeComponentes = static_cast<int>(g.size());
    int** red = new int*[quantidadeComponentes];

    for (int i = 0; i < quantidadeComponentes; i++)
        red[i] = new int[quantidadeComponentes]{};

    // Cada posicao red[i][j] indica se existe uma aresta saindo de
    // algum vertice da componente i para algum vertice da componente j
    for (int i = 0; i < quantidadeComponentes; i++) {
        for (int j = 0; j < quantidadeComponentes; j++) {
            if (i == j) continue;

            bool encontrouAresta = false;

            for (int origem : g[i]) {
                for (int destino : g[j]) {
                    if (this->adj[origem][destino] == 1) {
                        red[i][j] = 1;
                        encontrouAresta = true;
                        break;
                    }
                }

                if (encontrouAresta) break;
            }
        }
    }

    return red;
}

// ===========================================================
// TGrafo_ND: grafo nao dirigido
// ===========================================================
 
// Construtor do TGrafo Non-Directed
TGrafo_ND::TGrafo_ND(int n){
    this->n = n;
    this->m = 0;
    int **adjac = new int*[n];
    for(int i = 0; i < n; i++)
        adjac[i] = new int[n];
    adj = adjac;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            adj[i][j] = 0;
        }
    }
}
 
// Destructor, responsavel por
// liberar a memoria alocada para a matriz
TGrafo_ND::~TGrafo_ND(){
    // mesma correcao aplicada ao TGrafo: antes tinha um
    // "delete [] *adj;" extra depois deste laco (double free)
    for(int i = 0; i < n; i++)
        delete [] adj[i];
    delete [] adj;
 
    n = 0;
    m = 0;
    std::cout << "espaco liberado (grafo nao-direcionado)" << std::endl;
}

// EXERCICIO 7 - RELATORIO
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
        insereA(a1, a2);
    }
    file.close();
}
 
// ⚠️EXERCICIO 8 - RELATORIO
// Insere uma aresta no Grafo tal que v e adjacente a w (nos dois sentidos)
void TGrafo_ND::insereA(int v, int w){
    if(adj[v][w] == 0 && adj[w][v] == 0){
        adj[v][w] = 1;
        adj[w][v] = 1;
        m++;
    }
}
 
void TGrafo_ND::removeA(int v, int w){
    if(adj[v][w] == 1 && adj[w][v] == 1){
        adj[v][w] = 0;
        adj[w][v] = 0;
        m--;
    }
}
 
// ⚠️EXERCICIO 9 - RELATORIO
int TGrafo_ND::degree(int v){
    // Em grafo nao direcionado, o grau e praticamente o
    // numero de vizinhos conectados em v
    int grau_nd = 0;
    for(int b = 0; b < n; b++){
        if(adj[v][b] == 1){
            grau_nd++;
        }
    }
    return grau_nd;
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

// Funcao que mostra Grafo nao Direcionado
void TGrafo_ND::show(){
    
    std::cout << "\n====================================================================" << std::endl;
    std::cout << "--GRAFO Nao Direcionado--\n";
    std::cout << "====================================================================\n" << std::endl;
    std::cout << "\n--GRAFO Nao Direcionado--\n";
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    
    for( int i=0; i < n; i++){
        std::cout << "\n";
        for( int w=0; w < n; w++)
            if(adj[i][w] == 1)
                std::cout << "Adj[" << i<< "," << w << "]= 1" << " ";
            else std::cout << "Adj[" << i<< "," << w << "]= 0" << " ";
    }

    // Resposta 9
    std::cout << "\n\nRESPOSTA 9)\n";
    for(int index = 0; index < n; index++){
        std::cout << "Grau do vertice " << index << ": " << degree(index) << std::endl;
    }

    // Resposta 11
    std::cout << "\nRESPOSTA 11)\n";
    std::cout << "--- GRAFO ANTES DA REMOCAO ---\n";
    _show();
    removeV(4);
    std::cout << "\n";
    std::cout << "--- GRAFO DEPOIS DA REMOCAO ---\n";
    _show();

    // Resposta 12
    std::cout << "\nRESPOSTA 12)\n";
    std::cout << "O grafo G " << (isComplete() ? "" : "nao ") << "eh completo!" << std::endl;

    // Resposta 14)
    std::cout << "\n\nRESPOSTA 14 (Grafo Nao-Dirigido)\n";
    int** comp = complemento();

    std::cout << "Matriz original:" << std::endl;
    _show();

    std::cout << "\nMatriz complemento:" << std::endl;
    _printMatriz(comp, this->n);

    for (int i = 0; i < this->n; i++)
        delete[] comp[i];
    delete[] comp;

    // Resposta 15)
    std::cout << "\nRESPOSTA 15)\n";
    std::cout << "O grafo G " << (conexidade_nao_direcionado() == 0 ? "eh conexo!" : "eh desconexo!") << std::endl;

    std::cout << "\nfim da impressao do grafo nao dirigido." << std::endl;
}

// Funcao que mostra Grafo Direcionado
void TGrafo::show(){
    std::cout << "\n=======================================================================================================================\n" << std::endl;
    std::cout << "\nEsse arquivo TGrafoo.cpp tem prints das respostas do 1 a 17 somente. - Respostas do 18 ao 30 no arquivo listas (Grafo.cpp)\n" << std::endl;
    std::cout << "\n=======================================================================================================================\n" << std::endl;

    std::cout << "\n====================================================================" << std::endl;
    std::cout << "--GRAFO Direcionado--\n";
    std::cout << "====================================================================\n" << std::endl;

    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;

    for(int i = 0; i < n; i++){
        std::cout << "\n";
        for(int w = 0; w < n; w++)
            if(adj[i][w] == 1)
                std::cout << "Adj[" << i<< "," << w << "]= 1" << " ";
            else std::cout << "Adj[" << i<< "," << w << "]= 0" << " ";
    }
    std::cout << "\n";

    // Resposta 1)
    std::cout << "\nRESPOSTA 1)\n";
    for(int index = 0; index < n; index++)
        std::cout << "Grau de Entrada do vertice " << index << ": "<< inDegree(index) << std::endl; 

    // Resposta 2)
    std::cout << "\nRESPOSTA 2)\n";
    for(int index = 0; index < n; index++)
        std::cout << "Grau de Saida do vertice " << index << ": "<< outDegree(index) << std::endl; 

    // Resposta 3)
    std::cout << "\nRESPOSTA 3)\n";
    for(int v = 0; v < n; v++)
        std::cout << "Grau total do vertice " << v << ": " << degree(v) << std::endl;

    // Resposta 4) e 5)
    std::cout << "\nRESPOSTA 4 e 5)\n";
    for(int v = 0; v < n; v++)
        std::cout << "Vertice " << v << " -> Fonte: " << Fonte_check(v) << "|| Sorvedouro: " << Sorvedouro(v) << std::endl;

    // Resposta 6)
    std::cout << "\nRESPOSTA 6)\n";
    std::cout << "Retorno de checagem de simetria -> Return: " << isSymetric() << std::endl;

    // Resposta 10)
    std::cout << "\nRESPOSTA 10)";

    // Resposta 11)
    std::cout << "\n\nRESPOSTA 11)\n";
    std::cout << "--- GRAFO ANTES DA REMOCAO ---\n";
    _show();
    removeV(3);
    std::cout << "--- GRAFO DEPOIS DA REMOCAO ---\n";
    _show();

    // Resposta 13)
    std::cout << "\n\nRESPOSTA 13)\n";
    std::cout << "O grafo G " << (isComplete() ? "" : "nao ") << "eh completo!" << std::endl;

    // Resposta 14)
    std::cout << "\n\nRESPOSTA 14 (Grafo Dirigido)\n";
    int** comp = complemento();
    std::cout << "Matriz original:" << std::endl;
    _show();
    std::cout << "\nMatriz complemento:" << std::endl;
    _printMatriz(comp, this->n);
    for (int i = 0; i < this->n; i++)
        delete[] comp[i];
    delete[] comp;

    // Resposta 16)
    std::cout << "\nRESPOSTA 16)\n";
    std::cout << "Categoria de conexidade do grafo G: C" << conexidade_direcionado() << std::endl;

    // Resposta 17)
    std::cout << "\n\nRESPOSTA 17)\n";
    int quantidadeComponentes;
    int** reduzida = reduzido(quantidadeComponentes);
    std::cout << "Matriz original:" << std::endl;
    _show();
    std::cout << "\nMatriz reduzida:" << std::endl;
    _printMatriz(reduzida, quantidadeComponentes);
    for (int i = 0; i < quantidadeComponentes; i++)
        delete[] reduzida[i];
    delete[] reduzida;
    std::cout << "\n====================================================================" << std::endl;
    std::cout << "fim da impressao dos resultados das operacoes com grafo direcionado\n." << std::endl;
    std::cout << "====================================================================\n" << std::endl;
}

void TGrafo::_printMatriz(int** matriz, int tamanho) {
    std::cout << "   ";

    for (int j = 0; j < tamanho; j++) {
        if (j > 0)
            std::cout << " ";
        std::cout << j;
    }

    std::cout << std::endl;

    for (int i = 0; i < tamanho; i++) {
        std::cout << i << " [";

        for (int j = 0; j < tamanho; j++) {
            if (j > 0)
                std::cout << " ";
            std::cout << matriz[i][j];
        }

        std::cout << "]" << std::endl;
    }
}

void TGrafo::_show() {
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

void TGrafo_ND::_printMatriz(int** matriz, int tamanho) {
    std::cout << "   ";

    for (int j = 0; j < tamanho; j++) {
        if (j > 0)
            std::cout << " ";
        std::cout << j;
    }
    std::cout << std::endl;

    for (int i = 0; i < tamanho; i++) {
        std::cout << i << " [";
        for (int j = 0; j < tamanho; j++) {
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
