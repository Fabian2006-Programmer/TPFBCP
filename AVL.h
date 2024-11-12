#pragma once
#include "NodoArbol.h"
using namespace std;
template <class T>
class ArbolAVL {
public:
	NodoArbol<T>* root;
ArbolAVL(){
	root = NULL;
}
bool EstaVacio() {
	if (root == NULL) {
		return true;
	}
	else {
		return false;
	}
}
int Altura(NodoArbol<T>* raiz) {
	if (raiz == NULL) {
		return -1;
	}
	else {
		int AlturaIzq = Altura(raiz->izquierda);
		int AlturaDer = Altura(raiz->derecha);
		if (AlturaIzq > AlturaDer)
			return (AlturaIzq + 1);
		else
			return (AlturaDer + 1);
	}
}
int ObtFactorEquil(NodoArbol<T>* raiz) {
	if (raiz == NULL)
		return -1;
	return Altura(raiz->izquierda) - Altura(raiz->derecha);
}
NodoArbol<T>* RotarDer(NodoArbol<T>* y) {
	NodoArbol<T>* x = y->izquierda;
	NodoArbol<T>* temp = x->derecha;
	x->derecha = y;
	y->izquierda = temp;
	return x;
}
NodoArbol<T>* RotarIzq(NodoArbol<T>* x) {
	NodoArbol<T>* y = x->derecha;
	NodoArbol<T>* temp = y->izquierda;
	y->izquierda = x;
	x->derecha = temp;
	return y;
}
NodoArbol<T>* Insertar(NodoArbol<T>* raiz, NodoArbol<T>* nuevo) {
	if (raiz == NULL) {
		raiz = nuevo;
		return raiz;
	}
	if (nuevo->dato < raiz->dato) {
		raiz->izquierda = Insertar(raiz->izquierda, nuevo);
	}
	else if (nuevo->dato > raiz->dato) {
		raiz->derecha = Insertar(raiz->derecha, nuevo);
	}
	else {
		cout << "LOS DATOS SE REPITEN...\n";
		return raiz;
	}
	int FE = ObtFactorEquil(raiz);
	//CASO LL
	if (FE > 1 && nuevo->dato < raiz->izquierda->dato) {
		return RotarDer(raiz);
	}
	//CASO RR
	if (FE < -1 && nuevo->dato > raiz->derecha->dato) {
		return RotarDer(raiz);
	}
	//CASO LR
	if (FE > 1 && nuevo->dato > raiz->izquierda->dato) {
		raiz->izquierda = RotarIzq(raiz->izquierda);
		return RotarDer(raiz);
	}
	//CASO RL
	if (FE < -1 && nuevo->dato < raiz->derecha->dato) {
		raiz->derecha = RotarDer(raiz->derecha);
		return RotarIzq(raiz);
	}
	return raiz;
}
//Hallar el valor más izquierdo del arbol (util para las demás funciones)
NodoArbol<T>* ValorIzq(NodoArbol<T>* raiz) {
	NodoArbol<T>* temp = raiz;
	while (temp->izquierda != NULL) {
		temp = temp->izquierda;
	}
	return temp;
}
//Borrar Nodo del arbol y acomodar el arbol
NodoArbol<T>* Borrar(NodoArbol<T>* raiz, T valor) {
	if (raiz == NULL) {
		return NULL;
	}
	else if (valor < raiz->dato) {
		raiz->izquierda = Borrar(raiz->izquierda, valor);
	}
	else if (valor > raiz->dato) {
		raiz->derecha = Borrar(raiz->derecha, valor);
	}
	else {
		if (raiz->izquierda == NULL) {
			NodoArbol<T>* temp = raiz->derecha;
			delete raiz;
			return temp;
		}
		else if (raiz->derecha == NULL) {
			NodoArbol<T>* temp = raiz->izquierda;
			delete raiz;
			return temp;
		}
		else {
			NodoArbol<T>* temp = ValorIzq(raiz->derecha);
			raiz->dato = temp->dato;
			raiz->derecha = Borrar(raiz->derecha, temp->dato);
		}
	}
	int FE = ObtFactorEquil(raiz);
	if (FE == 2 && ObtFactorEquil(raiz->izquierda) >= 0) {
		return RotarDer(raiz);
	}
	else if (FE == 2 && ObtFactorEquil(raiz->izquierda) == -1) {
		raiz->izquierda = RotarIzq(raiz->izquierda);
		return RotarDer(raiz);
	}
	else if (FE == -2 && ObtFactorEquil(raiz->derecha) <= 0) {
		return RotarIzq(raiz);
	}
	else if (FE == -2 && ObtFactorEquil(raiz->derecha) == 1) {
		raiz->derecha = RotarDer(raiz->derecha);
		return RotarIzq(raiz);
	}
	return raiz;
}
	void ImpPreorden(NodoArbol<T>*raiz) {
		if (raiz == NULL) {
			return;
		}
		cout << raiz->dato << " ";
		ImpPreorden(raiz->izquierda);
		ImpPreorden(raiz->derecha);
	}
	void ImpEnorden(NodoArbol<T>* raiz){
		if (raiz == NULL) {
			return;
		}
		ImpEnorden(raiz->izquierda);
		cout << raiz->dato << " ";
		ImpEnorden(raiz->derecha);
	}
	void ImpPostorden(NodoArbol<T>* raiz) {
		if (raiz == NULL) {
			return;
		}
		ImpPostorden(raiz->izquierda);
		ImpPostorden(raiz->derecha);
		cout << raiz->dato << " ";
	}
NodoArbol<T>* BuscaRecursiva(NodoArbol<T>* raiz, T valor) {
	if (raiz == NULL || raiz->dato == valor) {
		return raiz;
	}
	else if (valor < raiz->dato) {
		BuscaRecursiva(raiz->izquierda, valor);
	}
	else {
		BuscaRecursiva(raiz->derecha, valor);
	}
}	
};
/*
//IMPLEMENTACION EN CASO DE OLVIDEARME===================
	ArbolAVL<int> arbol;
	//RECIBE EL DATO PARA BUSCAR
	int valor;
	NodoArbol<int>* nuevo_nodo = new NodoArbol;
	while (1) {
		int op; cin >> op;
		switch (op) {
		case 1:
			//INSERTAR===============================================
			cin >> valor;
			nuevo_nodo->dato = valor;
			arbol.root = arbol.Insertar(arbol.root, nuevo_nodo);
			break;
		case 2:
			//BUSCAR=================================================
			cin >> valor;
			nuevo_nodo = arbol.BuscaRecursiva(arbol.root, valor);0
			if (nuevo_nodo != NULL)
				cout << "NODO ENCONTRADO\n";
			else
				cout << "NODO NO ENCONTRADO\n";
			break;
		case 3:
			//BORRAR=================================================
			cin >> valor;
			nuevo_nodo = arbol.BuscaRecursiva(arbol.root, valor);
			if (nuevo_nodo != NULL) {
				cout << "NODO ENCONTRADO\n";
				arbol.root = arbol.Borrar(arbol.root; valor);
				cout << "NODO BORRADO\n";
			}
			else
				cout << "NODO NO ENCONTRADO\n";
			break;
		case 4:
			//IMPRIMIR===============================================
			arbol.ImpPreorden(arbol.root);
			arbol.ImpEnorden(arbol.root);
			arbol.ImpPostorden(arbol.root);
			break;
		}
	}
*/