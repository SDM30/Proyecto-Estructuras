#include "Cara.h"

// Implementación del constructor
Cara::Cara(unsigned int num_ver, std::vector<unsigned int> ind_caras) {
  this->num_ver = num_ver;
  this->ind_caras = ind_caras;
}

// Implementación de los getters
unsigned int Cara::getNum_ver() { return num_ver; }

std::vector<unsigned int> Cara::getInd_caras() { return ind_caras; }
