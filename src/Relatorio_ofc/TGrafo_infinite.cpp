#include <iostream>
#include "TGrafo_infinite.h"
#include <fstream>
#include <limits>

/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

// ===========================================================
// TGrafo: grafo dirigido, com peso (float) nas arestas
// ===========================================================

// definicao do membro estatico (so existe UMA copia, compartilhada
// por todos os objetos TGrafo; e por isso que nao repete o
// numeric_limits<float>::infinity() em cada metodo)
const float TGrafo::INF = std::numeric_limits<float>::infinity();

// Construtor do TGrafo
TGrafo::TGrafo( int n ){
    this->n = n;
    // No inicio dos tempos nao ha arestas
    this->m = 0;
    // aloca a matriz do TGrafo
    float **adjac = new float*[n];
    for(int i = 0; i < n; i++)
    	adjac[i]= new float[n];
    adj = adjac;

    // Inicia a matriz com infinito: infinito == "nao existe aresta".
    // Antes usava 0 pra "sem aresta", mas agora 0 pode ser um peso
    // valido (por exemplo, uma aresta de custo zero), entao nao
    // serve mais como marcador de ausencia de aresta.
	for(int i = 0; i< n; i++)
		for(int j = 0; j< n; j++)
			adj[i][j] = INF;
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

	std::cout << "espaco liberado" << std::endl;
}

// Insere uma aresta rotulada (com peso) no Grafo, tal que
// v e adjacente a w com o peso informado
void TGrafo::insereA(int v, int w, float peso){
    // testa se ainda nao temos a aresta (infinito == "vazio")
    if(adj[v][w] == INF){
        adj[v][w] = peso;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo (volta a valer infinito)
void TGrafo::removeA(int v, int w){
    // testa se temos a aresta
    if(adj[v][w] != INF){
        adj[v][w] = INF;
        m--; // atualiza qtd arestas
    }
}

// EXERCICIO 1 - RELATORIO
int TGrafo::inDegree(int v){
    int ingrau = 0;
    for(int t = 0; t < n; t++){
        // verifica se "chega"
        // um 't' que chega em 'v' (alvo):
        // (0,0), (1,0)...
        if(adj[t][v] != INF)
            ingrau++;
    }
    return ingrau;
}

// EXERCICIO 2 - RELATORIO
int TGrafo::outDegree(int v){
    int outgrau = 0;
    for(int t = 0; t < n; t++){
        // verifica se "sai"
        // de 'v' e chega em 't' (alvo):
        // (0,0), (0,1), (0,2)...
        if(adj[v][t] != INF)
            outgrau++;
    }
    return outgrau;
}

// EXERCICIO 3 - RELATORIO
int TGrafo::degree(int v){
    int grau_total = 0;
    for(int t = 0; t < n; t++){
        if(adj[v][t] != INF)
            grau_total++;

        if(adj[t][v] != INF)
            grau_total++;
    }
    return grau_total;
}

void TGrafo::show(){
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    std::cout << "\n--GRAFO Direcionado--\n";
    for( int i = 0; i < n; i++){
        std::cout << "\n";
        for( int w=0; w < n; w++){
            std::cout << "Adj[" << i<< "," << w << "]= ";
            if(adj[i][w] == INF)
                std::cout << "inf" << " ";
            else
                std::cout << adj[i][w] << " ";
        }
    }

    std::cout << "\n";
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

    std::cout << "\nfim da impressao dos grafos." << std::endl;
}
