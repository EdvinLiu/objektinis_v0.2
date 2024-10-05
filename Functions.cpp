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
    srand(time(nullptr)); 
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

string generuoti_varda_pavarde(int studento_numeris) {
    return "Vardas" + to_string(studento_numeris) + " Pavarde" + to_string(studento_numeris);
}

// Funkcija, kuri sugeneruoja atsitiktinius namų darbų pažymius ir egzaminą
vector<int> generuoti_atsitiktinius_pazymius() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> pazymiai_dist(1, 10); // Pažymiai tarp 1 ir 10

    vector<int> pazymiai;
    int namu_darbai_count = 5;  // 5 namų darbai
    for (int i = 0; i < namu_darbai_count; ++i) {
        pazymiai.push_back(pazymiai_dist(gen));
    }

    int egzaminas = pazymiai_dist(gen);  // Egzamino pažymys
    pazymiai.push_back(egzaminas);  // Paskutinis pažymys yra egzaminas

    return pazymiai;
}

// Funkcija, kuri sugeneruoja failą su atsitiktiniais studentais
void generuoti_studentus_failui(const string& failo_pavadinimas, int studentu_skaicius) {
    ofstream failas(failo_pavadinimas);

    // Pirmoji eilutė - antraštė
    failas << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egzaminas" << endl;

    for (int i = 0; i < studentu_skaicius; ++i) {
        string vardas_ir_pavarde = generuoti_varda_pavarde(i + 1); // Pridedame 1, kad numeriai prasidėtų nuo 1
        vector<int> pazymiai = generuoti_atsitiktinius_pazymius();

        failas << vardas_ir_pavarde << " ";
        for (size_t j = 0; j < pazymiai.size(); ++j) {
            failas << pazymiai[j];
            if (j != pazymiai.size() - 1) failas << " ";  // Tarp pažymių dedame tarpą
        }
        failas << endl;
    }

    failas.close();
}
