#include "Vertice.h"
#include <cmath>

// Implementación del constructor
Vertice::Vertice(unsigned int ind_ver, double x, double y, double z) {
  this->ind_ver = ind_ver;
  this->x = x;
  this->y = y;
  this->z = z;
}

Vertice::Vertice() {}

// Implementación de los getters
unsigned int Vertice::getInd_ver() const { return ind_ver; }

double Vertice::getX() const { return x; }

double Vertice::getY() const { return y; }

double Vertice::getZ() const { return z; }

void Vertice::setIndVer(unsigned int ind_ver) {this->ind_ver = ind_ver;}
void Vertice::setX(double x) {this->x = x;}
void Vertice::setY(double y) {this->y = y;}
void Vertice::setZ(double z) {this->z = z;}

double Vertice::distanciaEuclidiana(Vertice val2) {
  return sqrt((pow(this->x - val2.getX(), 2)) + 
              (pow(this->y - val2.getY(), 2)) + 
              (pow(this->z - val2.getZ(), 2)));
}

// Sobrecarga del operador << para imprimir un vértice
std::ostream& operator<<(std::ostream& os, const Vertice& v) {
    os << v.ind_ver;
    return os;
}

bool Vertice::operator==(const Vertice otro) const {
  return this->ind_ver == otro.ind_ver;
}

bool Vertice::operator<(const Vertice& otro) const {
  return this->ind_ver < otro.ind_ver;
}