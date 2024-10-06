#include "NodoKD.h"
#include <iostream>

NodoKD::NodoKD(){
    Vertice p;
    p.setX(0);
    p.setY(0);
    p.setZ(0);

    this->dato = p;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

NodoKD::NodoKD(Vertice p) {
    this->dato = p;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}


NodoKD::~NodoKD(){
    if (this->hijoIzq != NULL) {
        delete this->hijoIzq;
    }
    if (this->hijoDer != NULL) {
        delete this->hijoDer;
    }
}


Vertice NodoKD::obtenerDato(){
    return dato;
}


void NodoKD::fijarDato(Vertice val){
    dato = val;
}


NodoKD* NodoKD::obtenerHijoIzq(){
    return hijoIzq;
}


void NodoKD::fijarHijoIzq(NodoKD* izq){
    this->hijoIzq = izq;
}


NodoKD* NodoKD::obtenerHijoDer(){
    return hijoDer;
}


void NodoKD::fijarHijoDer(NodoKD* der){
    this->hijoDer = der;
}


bool NodoKD::esHoja() {
    return (this->hijoDer == NULL) && (this->hijoIzq == NULL);
}