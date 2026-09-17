/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

#include "TGrafo.h"

int main(){
    //  chama o construtor para criar um grafo 4x4
    TGrafo g(8);

    //insere as arestas do grafo
    //A={(0,1),(0,2),(2,1),(2,3),(1,3)}
    g.insereA(0, 1);
    g.insereA(0, 2);
    g.insereA(0, 4);
    g.insereA(1, 3);
    g.insereA(1, 4);
    g.insereA(2, 5);
    g.insereA(2, 6);
    g.insereA(3, 7);
    g.insereA(4, 7);
    g.insereA(5, 4);
    g.insereA(5, 6);
    g.insereA(6, 0);
    g.insereA(6, 7);
    //---------------------------------------------//

    g.show();

    return 0;
}
