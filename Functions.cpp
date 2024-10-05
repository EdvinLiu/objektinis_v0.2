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
        cout << "Nepavyko atidaryti failo: " << failo_pavadinimas << endl;
        return;
    }
   
    string antraste;
    getline(failas, antraste);

    int Buffer_size = 1000000;  // Buferio dydis
    vector<char> buffer(Buffer_size);  // Buferis duomenims laikyti
    istringstream iss;  // Įvesties srautas eilučių apdorojimui

    while (failas.read(buffer.data(), Buffer_size) || failas.gcount() > 0) {
        streamsize bytes_read = failas.gcount();  // Kiek duomenų nuskaityta
        iss.clear();  // Išvalome srauto būseną
        iss.str(string(buffer.data(), bytes_read));  // Sukuriame srautą iš nuskaityto buferio

        string line;
        while (getline(iss, line)) {
            if (!line.empty()) {
                istringstream line_stream(line);  // Sukuriame srautą eilutei
                Studentas studentas;
                line_stream >> studentas.vardas >> studentas.pavarde;  // Nuskaitome vardą ir pavardę

                int pazym;
                while (line_stream >> pazym) {
                    studentas.namuDarbai.push_back(pazym);  // Dedame pažymius
                }

                // Egzamino pažymys yra paskutinis, todėl priskiriame jį atskirai
                if (!studentas.namuDarbai.empty()) {
                    studentas.egzaminas = studentas.namuDarbai.back();  // Paskutinis pažymys yra egzaminas
                    studentas.namuDarbai.pop_back();  // Pašaliname egzaminą iš namų darbų sąrašo
                }

                studentai.push_back(studentas);  // Pridedame studentą į vektorių
            }
        }
    }

    failas.close();  // Uždaryti failą
}
