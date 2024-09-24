#include "library.h"
#include "Functions.h"

using namespace std;

double galutinis(const vector<int>& nd, int egzaminas) {
    double suma_nd = accumulate(nd.begin(), nd.end(), 0);
    return (suma_nd / nd.size()) * 0.4 + 0.6 * egzaminas;
}

double mediana(const vector<int>& nd, int egzaminas) {
    vector<int> sortednd = nd;
    sort(sortednd.begin(), sortednd.end());
    size_t size = sortednd.size();

    if (size % 2 == 0)
        return (sortednd[size / 2 - 1] + sortednd[size / 2]) / 2.0 * 0.4 + 0.6 * egzaminas;
    else
        return (sortednd[size / 2]) * 0.4 + 0.6 * egzaminas;
}

int generuoti_atsitiktini(int min, int max) {
    srand(time(nullptr)); // Set seed for random number generator
    return min + rand() % (max - min + 1);
}

void nuskaityti_faila(const string& failo_pavadinimas, vector<Studentas>& studentai) {
    ifstream failas(failo_pavadinimas);
    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo:" << endl;
        return;
    }

    string pavarde, vardas;
    int nd;

    failas.ignore(numeric_limits<streamsize>::max(), '\n');

    while (failas >> pavarde >> vardas) {
        Studentas studentas;
        studentas.pavarde = pavarde;
        studentas.vardas = vardas;

        while (failas >> nd) {
            if (failas.peek() == '\n') break;
            studentas.namuDarbai.push_back(nd);
        }

        studentas.egzaminas = studentas.namuDarbai.back(); // Assign last value to exam score
        studentas.namuDarbai.pop_back(); // Remove last value from homework

        studentai.push_back(studentas);

        failas.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    failas.close();
}
