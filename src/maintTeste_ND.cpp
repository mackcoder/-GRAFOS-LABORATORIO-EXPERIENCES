/*
- Andre Doerner Duarte - 10427938
- Matheus Leonardo Cardoso Kroeff - 10426434
- Naoto Ushizaki - 10437445
*/

#include "TGrafo_ND.h"

int main(){
    //  chama o construtor para criar um grafo 4x4
    TGrafo_ND g2(6);

    //---------------------------------------------//

    g2.readfile("src/grafo_example.txt");

    g2.NDshow(); 


    return 0;
}
