#ifndef __ARBOLKD__H__
#define __ARBOLKD__H__
#include "NodoKD.h"
#include <iostream>
#include <queue>

class ArbolKD
{
protected:
    NodoKD *raiz;

public:
    ArbolKD();
    ArbolKD(Vertice val);
    ~ArbolKD();
    Vertice datoRaiz();
    NodoKD *obtenerRaiz();
    void fijarRaiz(NodoKD *n_raiz);
    bool esVacio();
    bool insertar(Vertice val);
    NodoKD *insertarRec(NodoKD* nodo, Vertice val, bool& insertado, char dimension);
    NodoKD *cercano(NodoKD* n1, NodoKD* n2, Vertice val);
    NodoKD *vecinoCercano(NodoKD* nodo, Vertice val);
    void vecinoCercanoRec(NodoKD* nodo, Vertice val, char dimension, NodoKD*& mejorNodo, int& mejorDist);
    //Recorridos
    void preOrden();
    void preOrden(NodoKD *nodo);
    void inOrden();
    void inOrden(NodoKD *nodo);
    void posOrden();
    void posOrden(NodoKD *nodo);
    void nivelOrden();
};

#endif