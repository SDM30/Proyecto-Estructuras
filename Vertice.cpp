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
unsigned int Vertice::getInd_ver() { return ind_ver; }

double Vertice::getX() { return x; }

double Vertice::getY() { return y; }

double Vertice::getZ() { return z; }

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
    os << "Vertice(ID: " << v.ind_ver << ", X: " << v.x << ", Y: " << v.y << ", Z: " << v.z << ")";
    return os;
}