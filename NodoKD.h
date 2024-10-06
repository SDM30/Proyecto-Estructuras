#ifndef __NODOKD__H__
#define __NODOKD__H__
#include "Vertice.h" 

class NodoKD {
    protected:
        Vertice dato;
        NodoKD* hijoIzq;
        NodoKD* hijoDer;
    public:
        NodoKD();
        NodoKD(Vertice val);
        ~NodoKD();
        bool esHoja();
        Vertice obtenerDato();
        void fijarDato(Vertice val);
        NodoKD* obtenerHijoIzq();
        NodoKD* obtenerHijoDer();
        void fijarHijoIzq(NodoKD* izq);
        void fijarHijoDer(NodoKD* der);
 };

#endif