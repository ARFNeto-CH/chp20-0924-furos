#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include "Ponto.h"
#include "Percurso.h"
using namespace std;

int main(int argc, char** argv)
{
    string arquivo = "";
    if (argc > 1)
        arquivo = argv[1];
    else
        arquivo = "seis.txt";

    Percurso percurso(arquivo);
    vector<int> idx;
    for (unsigned i = 0; i < percurso.pontos.size(); i += 1)
        idx.push_back(i);
    cout << "Entrada: '" << arquivo << "'\n";
    cout << percurso.pontos;
    cout << "\n\
[inicio] Total do percurso acima: " 
    << percurso.comprimento(idx) << "\n\n";

    // classificando os pontos por distancia da origem
    sort(percurso.pontos.begin(), percurso.pontos.end(),
        [](Ponto a, Ponto b) { return a.distanciaDaOrigem() < b.distanciaDaOrigem(); });
    cout << percurso.pontos;
    cout << "\n\
[classificado por distancia da main] Total do percurso acima: "
    << percurso.comprimento(idx) << "\n\n";

    percurso.menor_percurso = 10e20f;
    float este_percurso = 0.f;
    
    // computa as distancias para todos os possiveis percursos
    int testes = 0;
    do
    {
        testes += 1;
        este_percurso = percurso.comprimento(idx);
        if (este_percurso < percurso.menor_percurso)
        {   
            percurso.menor_percurso = este_percurso;
            percurso.melhor_sequencia.clear();
            for_each( idx.begin(), idx.end(),
                [&](int ix) { percurso.melhor_sequencia.push_back(percurso.pontos[ix]); }
            );  // for_each()
        };  // if()

    } while (std::next_permutation(idx.begin(), idx.end()));

    cout << "\n\n==> Percurso com deslocamento MINIMO: " 
        << percurso.menor_percurso << "mm\n\n";
    cout << percurso.melhor_sequencia;

    return 0;
};  // main()

// fim
