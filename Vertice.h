#ifndef __VERTICE__H__
#define __VERTICE__H__
#include <iostream> 

class Vertice {
private:
  unsigned int ind_ver;
  double x, y, z;

public:
  Vertice(unsigned int ind_ver, double x, double y, double z);
  Vertice();
  // getters
  unsigned int getInd_ver() const;
  double getX() const;
  double getY() const;
  double getZ() const;
  void setIndVer(unsigned int ind_ver);
  void setX(double x);
  void setY(double y);
  void setZ(double z);
  double distanciaEuclidiana(Vertice val2);

  // Sobrecargar el operador << para imprimir los vértices
  friend std::ostream& operator<<(std::ostream& os, const Vertice& v);
  bool operator==(const Vertice otro) const;
  bool operator<(const Vertice& otro) const;
};

#endif