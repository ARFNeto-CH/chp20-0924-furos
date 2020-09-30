#pragma once
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

#include "Ponto.h"

class Percurso
{
public:
	string			arquivo;
	vector<Ponto>	melhor_sequencia;
	vector<Ponto>	pontos;
	float			menor_percurso{};

public:
	Percurso() : arquivo(""), melhor_sequencia({}), pontos({}) {};
	Percurso(string arquivo);

	float	comprimento(vector<int>&);
	friend	ostream& operator<<(ostream&, const vector<Ponto>&);
};

float		Percurso::comprimento(vector<int>& idx)
{
	// calcula o deslocamento total do broca, indo
	// da origem ate cada ponto na ordem do vetor 
	// de indices e voltando ate a origem ao final
	if (pontos.size() == 0) return 0.; // sem furos sem distancia
	float total = 0;
	float segmento = 0;
	Ponto A{ 0.,0. }; // comeca na origem
	// soma os segmentos
	for_each(idx.begin(), idx.end(), [&](int ix)
		{	total += A>>(pontos[ix]);
			A = pontos[ix];
		});
	// e volta para a origem
	total += A.distanciaDaOrigem();
	return total;
};	// comprimento()

Percurso::Percurso(string arquivo) : arquivo(arquivo), melhor_sequencia({})
{
	auto monta = [this](float s)
	{ 	
		static bool impar = true;
		static Ponto p;
		if (impar)
			p.x = s;
		else
		{
			p.y = s;
			pontos.push_back(p);
		};
		impar = !impar;
	};

	int N;
	ifstream entrada{ arquivo };
	entrada >> N;
	cout << "Esperados " << N << " pontos\n";
	istream_iterator<float> in{ entrada };
	istream_iterator<float> fim{};
	for_each(in, fim, monta);
	cout << "Lidos " << pontos.size() << " pontos\n";
};


ostream&	operator<<(ostream& out, const vector<Ponto>& P)
{
	Ponto	A{ 0.,0. };
	float	total = 0.f;
	float	parcela = 0.f;
	out << fixed << setprecision(2);
	out << "\nTotal de " << P.size() << " pontos\n\nPercurso:\n\n";

	out << "(0.00,0.00)\n"; // origem

	for (auto B : P)
	{
		parcela = (A >> B);
		total += parcela;
		out << "(" << B.x << "," << B.y << ") Dist. da origem = "
			<< B.distanciaDaOrigem() <<
			" +" << parcela << " =" << total << "\n";
		A = B;
	};	// for()

	Ponto B{ 0.,0. }; // volta para origem
	parcela = (A >> B);
	total += parcela;
	out << "(" << B.x << "," << B.y << ") Dist. da origem = "
		<< A.distanciaDaOrigem() <<
		" +" << parcela << " =" << total << "\n";
	out << "\nTotal do percurso = " << total << "\n\n";
	return out;
}


