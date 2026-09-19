/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

/*
Implementa��o de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjac�ncia
e m�todos para utiliza��o de um grafo dirigido.
*/
#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___

// defini��o de uma estrutura para armezanar um grafo
// Tamb�m seria poss�vel criar um arquivo grafo.h 
// e fazer a inclus�o "#include <grafo.h>"
class TGrafo{
	private:
		int n; // quantidade de v�rtices
		int m; // quantidade de arestas
		int **adj; //matriz de adjac�ncia
		bool _reduzido_caminho(int x, int y);
	public:
		TGrafo( int n);
		void insereA(int v, int w);
		void removeA(int v, int w);
		void show();
		int inDegree(int v);
		int outDegree(int v);
		int degree(int v);
		bool Fonte_check(int v);
		bool Sorvedouro(int v);
		int isSymetric();
		void removeV(int v);
		bool isComplete();
		int** complemento();
		int conexidade_nao_direcionado();
		int conexidade_direcionado();
		int** reduzido(int& quantidadeComponentes);
		void _printMatriz(int** matriz, int tamanho);
		void _show();
		~TGrafo();		
};	

class TGrafo_ND{
	private:
		int n; // quantidade de v�rtices
		int m; // quantidade de arestas
		int **adj; //matriz de adjac�ncia
	public:
		TGrafo_ND( int n);
		void insereA(int v, int w);
		void removeA(int v, int w);
		void readfile(const char* grafo_example);
		int degree(int v);
		void removeV(int v);
		void show();
		bool isComplete();
		int** complemento();
		int conexidade_nao_direcionado();
		void _printMatriz(int** matriz, int tamanho);
		void _show();
		~TGrafo_ND();			
};	

#endif

