#ifndef __CARA__H__
#define __CARA__H__
#include <vector>

class Cara {
private:
  unsigned int num_ver;
  std::vector<unsigned int> ind_caras;

public:
  Cara(unsigned int num_ver, std::vector<unsigned int> ind_caras);
  // getters
  unsigned int getNum_ver();
  std::vector<unsigned int> getInd_caras();
};

#endif