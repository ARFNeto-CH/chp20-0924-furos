#include "Permuta.h"

Permuta::Permuta(int N)
{
	for (int i = 0; i < N; i += 1) _Sequencia.push_back(i);
	_Pos = 0;
	_TP = (unsigned) fatorial(N);
};


Permuta::Iterator Permuta::begin()
{
	return Iterator(1, this);
}

Permuta::Iterator Permuta::end()
{
	return Iterator(_TP, this);
}


Permuta& Permuta::get(unsigned qual)
{

	if (_Pos > qual)
	{	
		// esta adiante: precisa voltar
		reinicia();
		while (_Pos < qual) proxima();
		return *this;
	};
	while (_Pos < qual)	proxima();
	return *this;
	};


bool		Permuta::proxima()
{
	if (_Final) return false;
	_Final = next_permutation(_Sequencia.begin(), _Sequencia.end()) == false;
	_Pos += 1;
	return true;
}


void		Permuta::reinicia()
{
	for (unsigned i = 0; i < _Sequencia.size(); i += 1)
		_Sequencia[i] = i;
	_Pos = 0;
	_Final = false;
	return;
};


unsigned	Permuta::size()
{
	return _Sequencia.size();
}


Permuta::Iterator::Iterator(unsigned pos, Permuta* perm) :
		_it_pos(pos), _Controle(perm)
{
	//cout << "Iterator constructor pos = " << pos << "\n";

	if (pos > perm->_TP) return;
	if (pos == _it_pos   ) return;
	if ( pos == 1)
	{
		_Controle->reinicia(); 
		_Sentinela = (Permuta*) new Permuta{ *_Controle };
		_Sentinela->_Pos = perm->_TP;
		_Sentinela->_Final = false;
		_Controle->proxima();
		// cria o outro registro
		_it_pos = 1;
		return;
	};

	if ( pos == perm->_TP)
	{
		*_Controle = *_Sentinela;
		_it_pos = pos;
		//printVector(&_Controle->_Sequencia);
		return;
	};

	_Controle->get(pos);
	_it_pos = pos;
	//printVector(&_Controle->_Sequencia);
	return;
};


void		printVector(const vector<int>* P)
{
	//cout << "\nTotal de " << P->size() << " pontos\n\n"; // origem
	cout << "[ ";
	for (auto B : *P)
	{
		cout << B << " ";
	};	// for()
	cout << "]\n";
	return;
}


unsigned long long fatorial(int N)
{
	if (N > 12)  return 0; // 13 passa do que cabe em unsigned int
	if (N == 0) return 1;
	return N * fatorial(N - 1);
};
