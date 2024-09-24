#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "library.h"
#include "Studentas.h"

// Function declarations
double galutinis(const std::vector<int>& nd, int egzaminas);
double mediana(const std::vector<int>& nd, int egzaminas);
int generuoti_atsitiktini(int min, int max);
void nuskaityti_faila(const std::string& failo_pavadinimas, std::vector<Studentas>& studentai);

#endif // FUNCTIONS_H_INCLUDED