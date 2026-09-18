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
// TGrafo_ND.h
#ifndef ___GRAFO_ND___
#define ___GRAFO_ND___

// defini��o de uma estrutura para armezanar um grafo
// Tamb�m seria poss�vel criar um arquivo grafo.h 
// e fazer a inclus�o "#include <grafo.h>"
class TGrafo_ND{
	private:
		int n; // quantidade de v�rtices
		int m; // quantidade de arestas
		int **adj; //matriz de adjac�ncia
	public:
		TGrafo_ND( int n);
		void NDinsereA(int v, int w);
		void NDremoveA(int v, int w);
		void readfile(const char* grafo_example);
		int degree(int v);
		void removeV(int v);
		void NDshow();
		bool isComplete();
		int** complemento();
		int conexidade_nao_direcionado();
		void _printMatriz(int** matriz);
		void _show();
		~TGrafo_ND();		
};	

#endif

