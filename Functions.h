#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Studentas.h"
#include <vector>
#include <list>
#include <string>
#include <algorithm>


double galutinis(const std::vector<double>& nd, int egzaminas);
double mediana(const std::vector<double>& nd, int egzaminas);
void generuoti_studentus_failui(const string& failo_pavadinimas, int studentu_skaicius);
int pagal_pavarde(Studentas& s, Studentas& s2);
int pagal_varda(Studentas& s, Studentas& s2);
int pagal_galutini(Studentas& s, Studentas& s2);

#endif // FUNCTIONS_H
