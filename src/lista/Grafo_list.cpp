/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

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
    int getN() { return n; }
    
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

// Exercício 27: Construcao da lista a partir de arquivo (grafo.txt)
TGrafo* TGrafo::carregarDeArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return nullptr;
    }

    int v, a;
    arquivo >> v; // Le a quantidade de vertices (linha 1)
    arquivo >> a; // Le a quantidade de arestas (linha 2)

    TGrafo* grafo = new TGrafo(v);

    int origem, destino;
    for (int i = 0; i < a; ++i) {
        if (arquivo >> origem >> destino) {
            grafo->insereA(origem, destino);
        }
    }

    arquivo.close();
    return grafo;
}

// Exercício 28: Remove um vértice de um grafo não-direcionado e suas arestas associadas
void TGrafo::removerVerticeND(int v) {
    if (v < 0 || v >= n) return;

    // Percorre os vizinhos de v para remover as arestas inversas 
    TNo *no = adj[v];
    while (no != nullptr) {
        int w = no->w;

        // Remove v da lista encadeada do vértice w 
        TNo *atual = adj[w];
        TNo *ant = nullptr;

        while (atual != nullptr) {
            if (atual->w == v) {
                if (ant == nullptr) {
                    adj[w] = atual->prox;
                } else {
                    ant->prox = atual->prox;
                }
                delete atual;
                m--; // Decrementa a contagem de arestas
                break;
            }
            ant = atual;
            atual = atual->prox;
        }

        no = no->prox;
    }

    // Libera toda a lista encadeada do próprio vértice v 
    TNo *atualV = adj[v];
    while (atualV != nullptr) {
        TNo *temp = atualV;
        atualV = atualV->prox;
        delete temp;
    }
    adj[v] = nullptr;
}

// Exercício 29: Remove um vértice de um grafo direcionado e ajusta suas arestas
void TGrafo::removerVerticeD(int v) {
    if (v < 0 || v >= n) return;

    // Libera a lista de adjacência do próprio vértice v 
    TNo *atualV = adj[v];
    while (atualV != nullptr) {
        TNo *temp = atualV;
        atualV = atualV->prox;
        delete temp;
        m--; // Decrementa o contador de arestas
    }
    adj[v] = nullptr;

    // Remove todas as arestas de outros vértices que apontam para v 
    for (int u = 0; u < n; ++u) {
        if (u == v) continue;

        TNo *atual = adj[u];
        TNo *ant = nullptr;

        while (atual != nullptr) {
            if (atual->w == v) {
                if (ant == nullptr) {
                    adj[u] = atual->prox;
                } else {
                    ant->prox = atual->prox;
                }
                delete atual;
                m--; // Decrementa o contador de arestas
                break;
            }
            ant = atual;
            atual = atual->prox;
        }
    }
}

// Exercício 30: Verifica se o grafo é completo
bool TGrafo::ehCompleto() {
    if (n <= 1) return true;

    // Para cada vértice u, o grau de saída deve ser exatamente n - 1
    for (int u = 0; u < n; ++u) {
        if (outDegree(u) != n - 1) {
            return false;
        }
    }

    return true;
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
    for (int v = 0; v < 4; v++) {
        cout << "Vertice " << v << ": " << g1.inDegree(v) << endl;
    }

    // Teste Exercício 19
    cout << "\n--- Exercicio 19 ---" << endl;
    for (int v = 0; v < 4; v++) {
        cout << "Vertice " << v << ": " << g1.outDegree(v) << endl;
    }

    // Teste Exercício 20
    cout << "\n--- Exercicio 20 ---" << endl;
    for (int v = 0; v < 4; v++) {
        cout << "Vertice " << v << ": " << g1.degree(v) << endl;
    }

    // Teste Exercício 21
    cout << "\n--- Exercicio 21 ---" << endl;
    cout << "g1 eh igual a g2? " << (g1.equals(g2) ? "Sim" : "Nao") << endl;
    cout << "g1 eh igual a g3? " << (g1.equals(g3) ? "Sim" : "Nao") << endl;

    // Teste Exercício 22: 
    cout << "\n--- Exercicio 22 ---" << endl;
    int nMatriz = 3;

    // Alocação e montagem da matriz de teste 3x3
    int** matriz = new int*[nMatriz];
    for (int i = 0; i < nMatriz; ++i) {
        matriz[i] = new int[nMatriz]{0};
    }
    matriz[0][1] = 1; // Aresta 0 -> 1
    matriz[1][2] = 1; // Aresta 1 -> 2
    matriz[2][0] = 1; // Aresta 2 -> 0

    // Exibe a matriz original
    cout << "Matriz de Adjacencia Original (" << nMatriz << "x" << nMatriz << "):" << endl;
    for (int i = 0; i < nMatriz; ++i) {
        for (int j = 0; j < nMatriz; ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    // Converte a matriz para a estrutura TGrafo
    TGrafo* grafoLista = TGrafo::matrizParaLista(matriz, nMatriz);

    // Exibe a lista de adjacência resultante
    cout << "\nLista de Adjacencia Gerada:" << endl;
    grafoLista->show();

    // Liberação de memória
    for (int i = 0; i < nMatriz; ++i) delete[] matriz[i];
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
    for (int v = 0; v < 4; v++) {
        cout << "Vertice " << v << " eh fonte? " << (g1.ehFonte(v) ? "Sim" : "Nao") << endl;
    }

    // Teste Exercício 25
    cout << "\n--- Exercicio 25 ---" << endl;
    for (int v = 0; v < 4; v++) {
        cout << "Vertice " << v << " eh sorvedouro? " << (g1.ehSorvedouro(v) ? "Sim" : "Nao") << endl;
    }

    // Teste Exercício 26
    cout << "\n--- Exercicio 26 ---" << endl;
    cout << "O grafo g1 eh simetrico? " << (g1.ehSimetrico() ? "SiM" : "Nao")<< endl; 

    // Criando um grafo simétrico para teste
    TGrafo gSimetrico(2);
    gSimetrico.insereA(0, 1); // 0 -> 1
    gSimetrico.insereA(1, 0); // 1 -> 0
    cout << "O grafo gSimetrico eh simetrico? " << (gSimetrico.ehSimetrico() ? "SiM" : "Nao") << endl; 
    
    // Teste Exercício 27
    cout << "\n--- Exercicio 27 ---" << endl;

    TGrafo* gArquivo = TGrafo::carregarDeArquivo("grafo.txt");

    if (gArquivo != nullptr) {
        cout << "Grafo carregado com sucesso!" << endl;
        gArquivo->show();

        cout << "\nResultados para todos os vertices do grafo do arquivo:" << endl;
        for (int v = 0; v < gArquivo->getN(); v++) { // Supondo 4 vértices conforme o arquivo
            cout << "Vertice " << v 
                 << " | Grau Entrada: " << gArquivo->inDegree(v)
                 << " | Grau Saida: " << gArquivo->outDegree(v)
                 << " | Grau Total: " << gArquivo->degree(v)
                 << " | Eh Fonte? " << (gArquivo->ehFonte(v) ? "Sim" : "Nao")
                 << " | Eh Sorvedouro? " << (gArquivo->ehSorvedouro(v) ? "Sim" : "Nao")
                 << endl; 
        }
        delete gArquivo;
    }

    // Teste Exercício 28
    cout << "\n--- Exercicio 28 ---" << endl;
    TGrafo gND(4);

    gND.insereA(0, 1); gND.insereA(1, 0);
    gND.insereA(1, 2); gND.insereA(2, 1);
    gND.insereA(2, 3); gND.insereA(3, 2);

    cout << "Grafo nao direcionado ANTES de remover o vertice 1:" << endl;
    gND.show();

    gND.removerVerticeND(1);

    cout << "\nGrafo nao direcionado DEPOIS de remover o vertice 1:" << endl;
    gND.show();

    // Teste Exercício 29

    cout << "\n--- Exercicio 29 ---" << endl;
    cout << "Grafo g1 ANTES de remover o vertice 2:" << endl;
    g1.show();

    g1.removerVerticeD(2);

    cout << "\nGrafo g1 DEPOIS de remover o vertice 2:" << endl;
    g1.show();

    // Teste Exercício 30
    cout << "\n--- Exercicio 30 ---" << endl;

    // Grafo Completo 
    TGrafo gCompleto(3);
    gCompleto.insereA(0, 1); gCompleto.insereA(0, 2);
    gCompleto.insereA(1, 0); gCompleto.insereA(1, 2);
    gCompleto.insereA(2, 0); gCompleto.insereA(2, 1);

    cout << "O grafo gCompleto eh completo? " << (gCompleto.ehCompleto() ? "Sim" : "Nao") << endl; 
    cout << "O grafo g3 eh completo? " << (g3.ehCompleto() ? "Sim" : "Nao") << endl;              
    

    return 0;
}   

