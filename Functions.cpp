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

    string line;
    while (getline(failas, line)) {
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

            studentai.push_back(studentas);  // Pridedame studentą į sąrašą
        }
    }

    failas.close();  // Uždaryti failą
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
        string vardas_ir_pavarde = "Vardas" + to_string(i + 1) + " Pavarde" + to_string(i + 1);
        vector<int> pazymiai;
        for (int j = 0; j < 5; ++j) {
            pazymiai.push_back(generuoti_atsitiktini(1, 10));  // Namu darbai
        }
        pazymiai.push_back(generuoti_atsitiktini(1, 10));  // Egzaminas

        failas << vardas_ir_pavarde << " ";
        for (auto& pazymys : pazymiai) {
            failas << pazymys << " ";
        }
        failas << endl;
    }

    failas.close();
}
void suskirstyti_studentus(const vector<Studentas>& studentai, char pasirinkite) {
    vector<Studentas> vargsiukai; // Studentai su galutiniu balu < 5
    vector<Studentas> kietiakiai; // Studentai su galutiniu balu >= 5

    for (const auto& studentas : studentai) {
        if (studentas.galutinis < 5.0) {
            // Pridedame studentą į vargšiukų vektorių
            vargsiukai.push_back(studentas);
        }
        else {
            // Pridedame studentą į kietiakio vektorių
            kietiakiai.push_back(studentas);
        }
    }
    failo_spausdinimas(vargsiukai, "vargsiukai.txt", pasirinkite);
    failo_spausdinimas(kietiakiai, "kietiakiai.txt", pasirinkite);

}
void failo_spausdinimas(const vector<Studentas>& studentai, string failas, char pasirinkite)
{
    ofstream fr(failas);
    fr << setw(15) << left << "Vardas" << setw(15) << "Pavarde" << setw(15)
        << (pasirinkite == 'v' ? "galutinis(Vid.)" : "Galutinis(Med.)") << endl;
    for (const auto& studentas : studentai) {
        fr << setw(15) << left << studentas.vardas << setw(15) << studentas.pavarde
            << setw(10) << fixed << setprecision(2) << studentas.galutinis << endl;
    }
    fr.close();
}
