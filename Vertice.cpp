#include "Vertice.h"

// Implementación del constructor
Vertice::Vertice(unsigned int ind_ver, double x, double y, double z) {
  this->ind_ver = ind_ver;
  this->x = x;
  this->y = y;
  this->z = z;
}

Vertice::Vertice() {}

// Implementación de los getters
unsigned int Vertice::getInd_ver() { return ind_ver; }

double Vertice::getX() { return x; }

double Vertice::getY() { return y; }

double Vertice::getZ() { return z; }