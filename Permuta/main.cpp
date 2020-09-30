#include <iostream>
#include "Permuta.h"

using namespace std;

int main(void)
{
	unsigned pos = 0;
	unsigned furos = 4;
	Permuta		p(furos);

	while (p.proxima())
	{
		cout << "Pos: " << setw(2) << p._Pos << " Final: " << p._Final << " ";
		printVector(&p._Sequencia);
	};

	// ==================================================================
	
	cout << "\n\n\n===== Usando classe Iterator =====\n\n";

	cout << "\n\tUsando iterator\n\n";
	for (Permuta::Iterator iter = p.begin(); iter != p.end(); iter++)
	{
		printVector(&(*iter)._Sequencia);
	};

	cout << "\n\tUsando for:range\n\n";
	for (auto& iter : p)
	{
		printVector( &iter._Sequencia);
	};

	return 0;
};	// main()