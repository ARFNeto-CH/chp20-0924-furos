#pragma once
#include <iostream>
#include <math.h>
using namespace std;
class Ponto
{
public:
	float x;
	float y;

public:
	Ponto() : x(0.), y(0.) {};
	Ponto(float a, float b) : x(a), y(b) {};

	float distanciaDaOrigem() { return sqrt(x * x + y * y); };
	friend float operator>>(const Ponto&, const Ponto&);
};

float operator>>(const Ponto& A, const Ponto& B)
{
	return sqrt(
		(A.x - B.x) * (A.x - B.x) +
		(A.y - B.y) * (A.y - B.y)
	);
};