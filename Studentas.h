#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include "library.h"

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> namuDarbai;
    int egzaminas;
    double galutinis;
    int tipas; //jei 0 tai galutinis balas yra < 5 (vargsiukas).   Jei >=5 tai 1 (kietiakiai)
};

#endif // STUDENTAS_H_INCLUDED

