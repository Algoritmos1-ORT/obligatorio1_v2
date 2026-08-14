#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#include <iostream>
using namespace std;
#include <string.h>
#include <assert.h>

inline constexpr char NoImplementado[] = "Implementar";

struct NodoLista
{
	int dato;
	NodoLista *sig;
	NodoLista() : dato(0), sig(nullptr) {}
	NodoLista(int d) : dato(d), sig(nullptr) {}
};

struct NodoAB
{
	int dato;
	NodoAB *izq;
	NodoAB *der;
	NodoAB() : dato(0), izq(nullptr), der(nullptr) {}
	NodoAB(int d) : dato(d), izq(nullptr), der(nullptr) {}
};

struct NodoAG
{
	int dato;
	NodoAG *ph;
	NodoAG *sh;
	NodoAG() : dato(0), ph(nullptr), sh(nullptr) {}
	NodoAG(int d) : dato(d), ph(nullptr), sh(nullptr) {}
};

struct NodoListaDobleDato
{
	int dato1;
	int dato2;
	NodoListaDobleDato *sig;
	NodoListaDobleDato() : dato1(0), dato2(0), sig(nullptr) {}
	NodoListaDobleDato(int d1, int d2) : dato1(d1), dato2(d2), sig(nullptr) {}
};

struct NodoABDobleDato
{
	int dato1;
	int dato2;
	NodoABDobleDato *izq;
	NodoABDobleDato *der;
	NodoABDobleDato() : dato1(0), dato2(0), izq(nullptr), der(nullptr) {}
	NodoABDobleDato(int d1, int d2) : dato1(d1), dato2(d2), izq(nullptr), der(nullptr) {}
};

#endif