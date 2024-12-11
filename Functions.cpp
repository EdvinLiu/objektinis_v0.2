#include "library.h"
#include "Functions.h"

using namespace std;

/**
 * @brief Apskaičiuoja galutinį balą pagal vidurkį.
 *
 * Ši funkcija apskaičiuoja studento galutinį balą, naudojant namų darbų vidurkį (svoris 0.4)
 * ir egzamino balą (svoris 0.6).
 *
 * @param nd Vektorius su studento namų darbų pažymiais.
 * @param egzaminas Studentas egzamino balas.
 * @return Galutinis balas.
 */
double galutinis(const vector<double>& nd, int egzaminas) {
    double suma_nd = accumulate(nd.begin(), nd.end(), 0);
    return (suma_nd / nd.size()) * 0.4 + 0.6 * egzaminas;
}

/**
 * @brief Apskaičiuoja galutinį balą pagal medianą.
 *
 * Ši funkcija apskaičiuoja studento galutinį balą, naudojant namų darbų medianą (svoris 0.4)
 * ir egzamino balą (svoris 0.6).
 *
 * @param nd Vektorius su studento namų darbų pažymiais.
 * @param egzaminas Studentas egzamino balas.
 * @return Galutinis balas.
 */
double mediana(const vector<double>& nd, int egzaminas) {
    vector<double> sortednd = nd;
    sort(sortednd.begin(), sortednd.end());
    size_t size = sortednd.size();

    if (size % 2 == 0)
        return (sortednd[size / 2 - 1] + sortednd[size / 2]) / 2.0 * 0.4 + 0.6 * egzaminas;
    else
        return (sortednd[size / 2]) * 0.4 + 0.6 * egzaminas;
}

/**
 * @brief Generuoja atsitiktinius namų darbų pažymius ir egzamino balą.
 *
 * Funkcija generuoja atsitiktinius namų darbų pažymius (nuo 1 iki 10) ir grąžina juos
 * vektoriuje. Ši funkcija naudojama generuoti studentų duomenims.
 *
 * @return Vektorius su atsitiktiniais namų darbų pažymiais.
 */
vector<int> generuoti_atsitiktinius_pazymius() {
    random_device rd;

    // Initialize Mersenne Twister pseudo-random number generator
    mt19937 gen(rd());

    // Generate pseudo-random numbers
    // uniformly distributed in range (1, 100)
    uniform_int_distribution<> dis(1, 10);

    // Generate ten pseudo-random numbers
    vector<int> randomX;
    for (int i = 0; i < 6; i++)
    {
        randomX.push_back(dis(gen));
    }
    return randomX;
}

/**
 * @brief Generuoja failą su atsitiktiniais studentų duomenimis.
 *
 * Ši funkcija sugeneruoja failą su atsitiktiniais studentų duomenimis. Kiekvienas studentas
 * turi atsitiktinius namų darbų pažymius ir egzamino balą.
 *
 * @param failo_pavadinimas Failo pavadinimas, į kurį bus išrašyti duomenys.
 * @param studentu_skaicius Skaičius studentų, kuriems sugeneruojami duomenys.
 */
void generuoti_studentus_failui(const string& failo_pavadinimas, int studentu_skaicius) {
    ofstream failas(failo_pavadinimas);

    // Pirmoji eilutė - antraštė
    failas << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egzaminas" << endl;

    for (int i = 0; i < studentu_skaicius; ++i) {
        string vardas_ir_pavarde = "Vardas" + to_string(i + 1) + " Pavarde" + to_string(i + 1);
        vector<int> pazymiai;
        pazymiai = generuoti_atsitiktinius_pazymius();
        failas << vardas_ir_pavarde << " ";
        for (auto& pazymys : pazymiai) {
            failas << pazymys << " ";
        }
        failas << endl;
    }

    failas.close();
}

/**
 * @brief Palygina studentus pagal vardą.
 *
 * Ši funkcija palygina du studentus pagal jų vardus. Jei vardai vienodi, palygina pagal pavardes.
 *
 * @param s Pirmas studentas.
 * @param s2 Antras studentas.
 * @return 1, jei pirmas studentas turi būti prieš antrą pagal abėcėlę, kitaip 0.
 */
int pagal_varda(Studentas& s, Studentas& s2) {
    if (s.vardas() != s2.vardas())
    {
        return s.vardas() < s2.vardas();
    }
    else {
        return s.pavarde() < s2.pavarde();
    }
}

/**
 * @brief Palygina studentus pagal pavardę.
 *
 * Ši funkcija palygina du studentus pagal jų pavardes. Jei pavardės vienodos, palygina pagal vardus.
 *
 * @param s Pirmas studentas.
 * @param s2 Antras studentas.
 * @return 1, jei pirmas studentas turi būti prieš antrą pagal abėcėlę, kitaip 0.
 */
int pagal_pavarde(Studentas& s, Studentas& s2) {
    if (s.pavarde() != s2.pavarde())
    {
        return s.pavarde() < s2.pavarde();
    }
    else {
        return s.vardas() < s2.vardas();
    }
}

/**
 * @brief Palygina studentus pagal galutinį balą.
 *
 * Ši funkcija palygina studentus pagal jų galutinį balą. Jei balai vienodi, palygina pagal pavardes.
 *
 * @param s Pirmas studentas.
 * @param s2 Antras studentas.
 * @return 1, jei pirmas studentas turi būti prieš antrą pagal galutinį balą, kitaip 0.
 */
int pagal_galutini(Studentas& s, Studentas& s2) {
    if (s.galutinis() != s2.galutinis())
    {
        return s.galutinis() < s2.galutinis();
    }
    else {
        return s.galutinis() > s2.galutinis();
    }
}
