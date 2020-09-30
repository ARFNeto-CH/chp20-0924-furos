#pragma once
#define NOT !
#define _MAXIMO_FUROS_ 12
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Permuta
{
public:
	bool		_Final{};
	unsigned	_TP;
	unsigned	_Pos{};
	vector<int> _Sequencia{};

public:
	class       Iterator;
	Iterator	begin();
	Iterator	end();

	Permuta&    get(unsigned);
	bool		proxima();
	void		reinicia();
	unsigned	size();

public:
	Permuta(int N);
	~Permuta(){};

private:
};	// Permuta{}


class Permuta::Iterator
{
private:
	Permuta*        _Controle{};
	Permuta*        _Sentinela{};
	unsigned		_it_pos{};

public:
	Iterator(unsigned pos, Permuta* perm);

	Permuta&	operator*()	{ return _Controle->get(_it_pos); };


	Iterator& operator++(int)
	{
		_Controle->_Pos += 1;
		_Controle->_Final = next_permutation(_Controle->_Sequencia.begin(), _Controle->_Sequencia.end());
		_it_pos += 1;
		return *this;
	};

	Iterator& operator++()
	{
		_Controle->_Pos += 1;
		_Controle->_Final = next_permutation(_Controle->_Sequencia.begin(), _Controle->_Sequencia.end());
		_it_pos += 1;
		return *this;
	};

	bool		operator!=(const Iterator& outro) const
	{
		return _it_pos != outro._it_pos;
	};
};

// funcoes auxiliares

unsigned long long fatorial(int); // para o total de permutacoes

void		printVector(const vector<int>* P); // para testes

