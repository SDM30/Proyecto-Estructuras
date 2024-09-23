#ifndef __VERTICE__H__
#define __VERTICE__H__

class Vertice {
private:
  unsigned int ind_ver;
  double x, y, z;

public:
  Vertice(unsigned int ind_ver, double x, double y, double z);
  Vertice();
  // getters
  unsigned int getInd_ver();
  double getX();
  double getY();
  double getZ();
};

#endif