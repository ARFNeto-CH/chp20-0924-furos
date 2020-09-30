#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include "Ponto.h"
#include "Percurso.h"
#include "Permuta.h"

using namespace std;

class Calcula
{
public:
    float       este_percurso{};
    Percurso*   percurso;

public:
    Calcula() : este_percurso(0), percurso(nullptr){}

    void operator()(const Permuta& perm)
    {
        vector<int> V = perm._Sequencia;
        este_percurso = percurso->comprimento(V);
        if (este_percurso < percurso->menor_percurso)
        {
            percurso->menor_percurso = este_percurso;
            percurso->melhor_sequencia.clear();
            for_each(V.begin(), V.end(),
                [&](int ix) { percurso->melhor_sequencia
                    .push_back(percurso->pontos[ix]); }
            );  // for_each()
        };  // if()
    };
};

int main(int argc, char** argv)
{
    // usa Calcula() para avaliar os percursos
    Calcula  cmp;
    string arquivo = "";
    if (argc > 1)
        arquivo = argv[1];
    else
        arquivo = "quadrado.txt";

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
[classificado por distancia da origem] Total do percurso acima: "
<< percurso.comprimento(idx) << "\n\n";

    // tabela todos os percursos possiveis
    Permuta P(percurso.pontos.size()); // prepara as permutacoes
    percurso.menor_percurso = 10e20f;
    cmp.percurso = &percurso;
    cmp.este_percurso = 0.f;
    for_each(P.begin(), P.end(), cmp );
    cout << "\n\n() ==> Percurso com deslocamento MINIMO: "
        << percurso.menor_percurso << "mm\n\n";
    cout << percurso.melhor_sequencia;
    return 0;
};  // main()

// fim
