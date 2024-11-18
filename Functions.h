#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "library.h"
#include "Studentas.h"

// Function declarations
double galutinis(const std::vector<int>& nd, int egzaminas);
double mediana(const std::vector<int>& nd, int egzaminas);
int generuoti_atsitiktini(int min, int max);
void nuskaityti_faila(const std::string& failo_pavadinimas, std::vector<Studentas>& studentai);
void generuoti_studentus_failui(const string& failo_pavadinimas, int studentu_skaicius);
void suskirstyti_studentus(const vector<Studentas>& studentai, char pasirinkite);
void failo_spausdinimas(const vector<Studentas>& studentai, string failas, char pasirinkite);
int pagal_pavarde(Studentas& s, Studentas& s2);
int pagal_varda(Studentas& s, Studentas& s2);
int pagal_galutini(Studentas& s, Studentas& s2);

#endif // FUNCTIONS_H_INCLUDED
