#include <iostream>
#include <fstream>

using namespace std;

// Classe do Nó para Lista Encadeada 
class TNo {
public:
    int w;
    TNo *prox;
};

// Classe TGrafo
class TGrafo {
private:
    int n;      // Quantidade de vértices
    int m;      // Quantidade de arestas
    TNo **adj;  // Vetor de ponteiros para as listas encadeadas

public:
    TGrafo(int n);
    ~TGrafo();
    void insereA(int v, int w);
    void show();
    
    // Exercício 18:
    int inDegree(int v);

    // Exercício 19:
    int outDegree(int v);

    // Exercício 20: 
    int degree(int v);

    // Exercício 21: 
    bool equals(const TGrafo& outro);

    // Exercício 22:
    static TGrafo* matrizParaLista(int** matriz, int n);

    // Exercício 23:
    void inverterListas();

    // Exercício 24:
    int ehFonte(int v);

    // Exercício 25:
    int ehSorvedouro(int v);

    // Exercício 26:
    int ehSimetrico();

    // Exercício 27:
    static TGrafo* carregarDeArquivo(const std::string& nomeArquivo);

    // Exercício 28:
    void removerVerticeND(int v);

    // Exercício 29:
    void removerVerticeD(int v);
    
    // Exercício 30:
    bool ehCompleto();
};

// ----------------------------------------------------
// IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE TGRAFO
// ----------------------------------------------------

// Construtor
TGrafo::TGrafo(int n) {
    this->n = n;
    this->m = 0;
    adj = new TNo*[n];
    for (int i = 0; i < n; i++) {
        adj[i] = nullptr;
    }
}

// Destrutor
TGrafo::~TGrafo() {
    for (int i = 0; i < n; i++) {
        TNo *no = adj[i];
        while (no) {
            TNo *ant = no;
            no = no->prox;
            delete ant;
        }
    }
    delete[] adj;
}

// Inserir aresta
void TGrafo::insereA(int v, int w) {
    TNo *no = adj[v];
    TNo *ant = nullptr;

    while (no && w >= no->w) {
        if (w == no->w) return;
        ant = no;
        no = no->prox;
    }

    TNo *novoNo = new TNo;
    novoNo->w = w;
    novoNo->prox = no;

    if (ant == nullptr) {
        adj[v] = novoNo;
    } else {
        ant->prox = novoNo;
    }
    m++;
}

// Exercício 18: Grau de Entrada
int TGrafo::inDegree(int v) {
    int count = 0;
    for (int u = 0; u < n; ++u) {
        TNo *no = adj[u];
        while (no != nullptr) {
            if (no->w == v) {
                count++;
            }
            no = no->prox;
        }
    }
    return count;
}

// Exercício 19: Grau de Saída
int TGrafo::outDegree(int v) {
    int count = 0;
    TNo *no = adj[v];
    while (no != nullptr) {
        count++;
        no = no->prox;
    }
    return count;
}

// Exercício 20: Grau Total
int TGrafo::degree(int v) {
    return inDegree(v) + outDegree(v);
}

// Exercício 21: Igualdade entre Grafos
bool TGrafo::equals(const TGrafo& outro) {
    // Verifica se número de vértices e arestas são iguais
    if (this->n != outro.n || this->m != outro.m) {
        return false;
    }

    // Compara a lista de adjacência de cada vértice u
    for (int u = 0; u < this->n; ++u) {
        TNo *no1 = this->adj[u];
        TNo *no2 = outro.adj[u];

        while (no1 != nullptr && no2 != nullptr) {
            if (no1->w != no2->w) {
                return false;
            }
            no1 = no1->prox;
            no2 = no2->prox;
        }

        if (no1 != nullptr || no2 != nullptr) {
            return false;
        }
    }

    return true;
}

// Exercício 22: Converção de uma Matriz de Adjacência em uma Lista de Adjacência
TGrafo* TGrafo::matrizParaLista(int** matriz, int n) {
    TGrafo* novoGrafo = new TGrafo(n);

    // Percorre a matriz de adjacência n x n
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Se houver aresta (valor 1 ou diferente de 0), insere na lista
            if (matriz[i][j] != 0) {
                novoGrafo->insereA(i, j);
            }
        }
    }

    return novoGrafo;
}

// Exercício 23: Inverter lista de adjacência
void TGrafo::inverterListas() {
    for (int i = 0; i < n; ++i) {
        TNo *ant = nullptr;
        TNo *atual = adj[i];
        TNo *prox = nullptr;

        while (atual != nullptr) {
            prox = atual->prox; 
            atual->prox = ant;  
            ant = atual;        
            atual = prox;       
        }

        adj[i] = ant;
    }
}

// Auxiliar para mostrar a lista
void TGrafo::show() {
    for (int i = 0; i < n; i++) {
        cout << "Adj[" << i << "]: ";
        TNo *no = adj[i];
        while (no != nullptr) {
            cout << no->w << " -> ";
            no = no->prox;
        }
        cout << "NULL" << endl;
    }
}

// Exercício 24: Verifica se o vértice v é uma fonte
int TGrafo::ehFonte(int v) {
    if (inDegree(v) == 0 && outDegree(v) > 0) {
        return 1;
    }
    return 0;
}

// Exercício 25: Verifica se o vértice v é um sorvedouro
int TGrafo::ehSorvedouro(int v) {
    if (inDegree(v) > 0 && outDegree(v) == 0) {
        return 1;
    }
    return 0;
}

// Exercício 26: Verifica se o grafo é simétrico
int TGrafo::ehSimetrico() {
    // Percorre cada vértice u
    for (int u = 0; u < n; ++u) {
        TNo *no = adj[u];
        
        // Para cada vizinho v de u (aresta u -> v)
        while (no != nullptr) {
            int v = no->w;
            
            // Verifica se existe a aresta de volta (v -> u)
            bool existeVolta = false;
            TNo *noVolta = adj[v];
            
            while (noVolta != nullptr) {
                if (noVolta->w == u) {
                    existeVolta = true;
                    break;
                }
                noVolta = noVolta->prox;
            }

            // Se não encontrou a aresta v -> u, o grafo não é simétrico
            if (!existeVolta) {
                return 0;
            }

            no = no->prox;
        }
    }

    return 1;
}


// ----------------------------------------------------
// EXECUÇÃO DO MAIN
// ----------------------------------------------------

int main() {
    // Criação do Grafo 1
    TGrafo g1(4);
    g1.insereA(0, 1);
    g1.insereA(0, 2);
    g1.insereA(0, 3);
    g1.insereA(2, 1);
    g1.insereA(2, 3);
    g1.insereA(1, 3);

    // Criação do Grafo 2 (idêntico ao Grafo 1)
    TGrafo g2(4);
    g2.insereA(0, 1);
    g2.insereA(0, 2);
    g2.insereA(0, 3);
    g2.insereA(2, 1);
    g2.insereA(2, 3);
    g2.insereA(1, 3);

    // Criação do Grafo 3 (diferente)
    TGrafo g3(4);
    g3.insereA(0, 1);
    g3.insereA(0, 2);

    // Teste Exercício 18
    cout << "--- Exercicio 18 ---" << endl;
    cout << "Grau de entrada do vertice 3: " << g1.inDegree(3) << endl;

    // Teste Exercício 19
    cout << "\n--- Exercicio 19 ---" << endl;
    cout << "Grau de saida do vertice 0: " << g1.outDegree(0) << endl;

    // Teste Exercício 20
    cout << "\n--- Exercicio 20 ---" << endl;
    cout << "Grau total do vertice 0: " << g1.degree(0) << endl;

    // Teste Exercício 21
    cout << "\n--- Exercicio 21 ---" << endl;
    cout << "g1 eh igual a g2? " << (g1.equals(g2) ? "Sim" : "Nao") << endl;
    cout << "g1 eh igual a g3? " << (g1.equals(g3) ? "Sim" : "Nao") << endl;

    // Teste Exercício 22
    int n = 3;

    // Aloca uma matriz de adjacência 3x3 de exemplo
    int** matriz = new int*[n];
    for (int i = 0; i < n; ++i) {
        matriz[i] = new int[n]{0};
    }

    // Arestas
    matriz[0][1] = 1;
    matriz[1][2] = 1;

    // Converte a matriz para a estrutura TGrafo (lista de adjacência)
    TGrafo* grafoLista = TGrafo::matrizParaLista(matriz, n);

    // Verifica a conversão com os métodos já criados
    cout << "Grau de saida do vertice 0: " << grafoLista->outDegree(0) << endl; // Retorna 1
    cout << "Grau de entrada do vertice 2: " << grafoLista->inDegree(2) << endl; // Retorna 1

    // Liberação de memória da matriz de teste
    for (int i = 0; i < n; ++i) delete[] matriz[i];
    delete[] matriz;
    delete grafoLista;

    // Teste Exercício 23

    cout << "\n--- Exercicio 23 ---" << endl;
    cout << "Lista de adjacencia ANTES da inversao:" << endl;
    g1.show();

    g1.inverterListas();

    cout << "\nLista de adjacencia DEPOIS da inversao:" << endl;
    g1.show();

    // Teste Exercício 24
    cout << "\n--- Exercicio 24 ---" << endl;
    cout << "O vertice 0 eh fonte em g1? " << g1.ehFonte(0) << endl;
    cout << "O vertice 3 eh fonte em g1? " << g1.ehFonte(3) << endl;

    // Teste Exercício 25
    cout << "\n--- Exercicio 25 ---" << endl;
    cout << "O vertice 3 eh sorvedouro em g1? " << g1.ehSorvedouro(3) << endl;
    cout << "O vertice 0 eh sorvedouro em g1? " << g1.ehSorvedouro(0) << endl; 

    // Teste Exercício 26
    cout << "\n--- Exercicio 26 ---" << endl;
    cout << "O grafo g1 eh simetrico? " << g1.ehSimetrico() << endl; 

    // Criando um grafo simétrico para teste
    TGrafo gSimetrico(2);
    gSimetrico.insereA(0, 1); // 0 -> 1
    gSimetrico.insereA(1, 0); // 1 -> 0
    cout << "O grafo gSimetrico eh simetrico? " << gSimetrico.ehSimetrico() << endl; 
    

    return 0;
}
