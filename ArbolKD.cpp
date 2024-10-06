#include "ArbolKD.h"
#include <iostream>
#include <limits>

ArbolKD::ArbolKD() {
    this->raiz = NULL;
}

ArbolKD::ArbolKD(Vertice val) {
    NodoKD nodoRaiz(val);
    this->raiz = &nodoRaiz;
}

ArbolKD::~ArbolKD() {
    if (this->raiz != NULL) {
        delete this->raiz;
        this->raiz = NULL;
    }
}

Vertice ArbolKD::datoRaiz() {
    return (this->raiz)->obtenerDato();
}

NodoKD* ArbolKD::obtenerRaiz() {
    return this->raiz;
}

void ArbolKD::fijarRaiz(NodoKD *n_raiz) {
    this->raiz = n_raiz;
}

bool ArbolKD::esVacio() {
    return this->raiz == NULL;
}

bool ArbolKD::insertar(Vertice val) {
    bool insertado = false;
    this->raiz = insertarRec(this->raiz, val, insertado, 'x');
    return insertado;
}

NodoKD* ArbolKD::insertarRec(NodoKD* nodo, Vertice val, bool& insertado, char dimension) {
    if (nodo == NULL) {
        insertado = true;
        return new NodoKD(val);
    }

    if (val.getX() == nodo->obtenerDato().getX() &&
        val.getY() == nodo->obtenerDato().getY() &&
        val.getZ() == nodo->obtenerDato().getZ()) {
        insertado = false; //DUPLICADO
        return nodo;
    }

    if (dimension == 'x') {
        if (val.getX() <= nodo->obtenerDato().getX()) {
            nodo->fijarHijoIzq(insertarRec(nodo->obtenerHijoIzq(), val, insertado, 'y'));
        } else {
            nodo->fijarHijoDer(insertarRec(nodo->obtenerHijoDer(), val, insertado, 'y'));
        }
    }
    if (dimension == 'y') {
        if (val.getY() <= nodo->obtenerDato().getY()) {
            nodo->fijarHijoIzq(insertarRec(nodo->obtenerHijoIzq(), val, insertado, 'z'));
        } else {
            nodo->fijarHijoDer(insertarRec(nodo->obtenerHijoDer(), val, insertado, 'z'));
        }
    }
    if (dimension == 'z') {
        if (val.getZ() <= nodo->obtenerDato().getZ()) {
            nodo->fijarHijoIzq(insertarRec(nodo->obtenerHijoIzq(), val, insertado, 'x'));
        } else {
            nodo->fijarHijoDer(insertarRec(nodo->obtenerHijoDer(), val, insertado, 'x'));
        }        
    }

    return nodo;
}

NodoKD* ArbolKD::cercano(NodoKD* n1, NodoKD* n2, Vertice val) {
    if (n2 == NULL) 
        return n1;
    if (n1 == NULL) 
        return n2;

    int distN1 = n1->obtenerDato().distanciaEuclidiana(val);
    int distN2 = n2->obtenerDato().distanciaEuclidiana(val);

    if (distN1 < distN2) {
        return n1;
    } else {
        return n2;
    }
}

NodoKD* ArbolKD::vecinoCercano(NodoKD* nodo, Vertice val) {
    NodoKD* mejorNodo = NULL;
    int mejorD = std::numeric_limits<int>::max();
    vecinoCercanoRec(raiz, val, 'x', mejorNodo, mejorD);
    return mejorNodo;
}

void ArbolKD::vecinoCercanoRec(NodoKD* nodo, Vertice val, char dimension, NodoKD*& mejorNodo, int& mejorDist) {
    NodoKD* sigRama = NULL;
    NodoKD* otraRama = NULL;

    if (nodo == NULL) return;

    int distActual = val.distanciaEuclidiana(nodo->obtenerDato());
    if (distActual < mejorDist) {
        mejorDist = distActual;
        mejorNodo = nodo;
    }
    
    //Buscar nodo raiz cercano
    if (val.getX() == nodo->obtenerDato().getX() && 
        val.getY() == nodo->obtenerDato().getY() &&
        val.getZ() == nodo->obtenerDato().getZ() ) {
        std::cout<<"Se encontro un punto igual"<<std::endl;
        mejorNodo = nodo;
        return;
    } else if (dimension == 'x') {
        if (val.getX() <= nodo->obtenerDato().getX()) {
            sigRama = nodo->obtenerHijoIzq();
            otraRama = nodo->obtenerHijoDer();
        } else {
            sigRama = nodo->obtenerHijoDer();
            otraRama = nodo->obtenerHijoIzq();
        }

    } else if (dimension == 'y') {
        if (val.getY() <= nodo->obtenerDato().getY()) {
            sigRama = nodo->obtenerHijoIzq();
            otraRama = nodo->obtenerHijoDer();
        } else {
            sigRama = nodo->obtenerHijoDer();
            otraRama = nodo->obtenerHijoIzq();
        }
    } else if (dimension == 'z') {
        if (val.getZ() <= nodo->obtenerDato().getZ()) {
            sigRama = nodo->obtenerHijoIzq();
            otraRama = nodo->obtenerHijoDer();            
        } else {
            sigRama = nodo->obtenerHijoDer();
            otraRama = nodo->obtenerHijoIzq();            
        }
    }

    char nuevaDimension;
    if (dimension == 'x') {
        nuevaDimension = 'y';
    } else if (dimension == 'y') {
        nuevaDimension = 'z';
    } else if (dimension == 'z') {
        nuevaDimension = 'x';
    }

    vecinoCercanoRec(sigRama, val, nuevaDimension, mejorNodo, mejorDist);
    NodoKD* nodoVecino = cercano(mejorNodo, nodo, val);

    //Distancia entre la recta y el punto
    int distEje;
    if (dimension == 'x') {
        distEje = abs(val.getX() - nodo->obtenerDato().getX());
    } else if (dimension == 'y') {
        distEje = abs(val.getY() - nodo->obtenerDato().getY());
    } else {
        distEje = abs(val.getZ() - nodo->obtenerDato().getZ());
    }
    
    if (distEje < distActual) {
        vecinoCercanoRec(otraRama, val, nuevaDimension, mejorNodo, mejorDist);
        nodoVecino = cercano(mejorNodo, nodo, val);
    }
}

//Recorridos
void ArbolKD::preOrden() {
    if(!this->esVacio()) {
        this->preOrden(this->raiz);
    }
}


void ArbolKD::preOrden(NodoKD* nodo) {
    std::cout << nodo->obtenerDato() << " " << std::endl;

    if (nodo->obtenerHijoIzq() != NULL) {
        this->preOrden(nodo->obtenerHijoIzq());
    }

    if (nodo->obtenerHijoDer() != NULL) {
        this->preOrden(nodo->obtenerHijoDer());
    }
}


void ArbolKD::inOrden() {
    if (!this->esVacio()) {
        this->inOrden(this->raiz);
    }
}


void ArbolKD::inOrden(NodoKD *nodo) {
    if (nodo != NULL) {
        this->inOrden(nodo->obtenerHijoIzq());
        std::cout << nodo->obtenerDato() << " " << std::endl;
        this->inOrden(nodo->obtenerHijoDer());
    }
}


void ArbolKD::posOrden() {
    if(!this->esVacio()) {
        this->posOrden(this->raiz);
    }
}


void ArbolKD::posOrden(NodoKD *nodo) {
    if (nodo->obtenerHijoIzq() != NULL) {
        this->posOrden(nodo->obtenerHijoIzq());
    }

    if (nodo->obtenerHijoDer() != NULL) {
        this->posOrden(nodo->obtenerHijoDer());
    }

    std::cout << nodo->obtenerDato() << " " << std::endl;
}


void ArbolKD::nivelOrden() {
    if (!this->esVacio()) {
        std::queue<NodoKD*> cola;
        cola.push(this->raiz);
        NodoKD* nodo;

        while(!cola.empty()) {
            nodo = cola.front();
            cola.pop();
            std::cout << nodo->obtenerDato() << std::endl;

            if (nodo->obtenerHijoIzq() != NULL) {
                cola.push(nodo->obtenerHijoIzq());
            }

            if (nodo->obtenerHijoDer() != NULL) {
                cola.push(nodo->obtenerHijoDer());
            }
        }
    }
}