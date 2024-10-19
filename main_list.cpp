#include <iostream>
#include <list>
#include <string>
#include <limits>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <stdexcept>
#include <random>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

struct Studentas {
    string vardas;
    string pavarde;
    list<int> namuDarbai;
    int egzaminas;
    double galutinis;
};

double galutinis(const list<int>& nd, int egzaminas) {
    double suma_nd = accumulate(nd.begin(), nd.end(), 0);
    return (suma_nd / nd.size()) * 0.4 + 0.6 * egzaminas;
}

double mediana(const list<int>& nd, int egzaminas) {
    list<int> sortednd = nd;
    sortednd.sort();
    size_t size = sortednd.size();
    auto it = sortednd.begin();
    advance(it, size / 2); // Naudojame `advance` list tipo iteracijai

    if (size % 2 == 0) {
        auto prev_it = it;
        advance(prev_it, -1);
        return (*prev_it + *it) / 2.0 * 0.4 + 0.6 * egzaminas;
    }
    else {
        return (*it) * 0.4 + 0.6 * egzaminas;
    }
}

int generuoti_atsitiktini(int min, int max) {
    srand(time(nullptr));
    return min + rand() % (max - min + 1);
}

void nuskaityti_faila(const string& failo_pavadinimas, list<Studentas>& studentai) {
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

void generuoti_studentus_failui(const string& failo_pavadinimas, int studentu_skaicius) {
    ofstream failas(failo_pavadinimas);

    // Pirmoji eilutė - antraštė
    failas << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egzaminas" << endl;

    for (int i = 0; i < studentu_skaicius; ++i) {
        string vardas_ir_pavarde = "Vardas" + to_string(i + 1) + " Pavarde" + to_string(i + 1);
        list<int> pazymiai;
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
void failo_spausdinimas(const list<Studentas>& studentai, const string& failas, char pasirinkite) {
    ofstream fr(failas);
    fr << setw(15) << left << "Vardas" << setw(15) << "Pavarde" << setw(15)
        << (pasirinkite == 'v' ? "galutinis(Vid.)" : "Galutinis(Med.)") << endl;

    for (const auto& studentas : studentai) {
        fr << setw(15) << left << studentas.vardas << setw(15) << studentas.pavarde
            << setw(10) << fixed << setprecision(2) << studentas.galutinis << endl;
    }
    fr.close();
}

void suskirstyti_studentus(const list<Studentas>& studentai, char pasirinkite) {
    list<Studentas> vargsiukai; // Studentai su galutiniu balu < 5
    list<Studentas> kietiakiai; // Studentai su galutiniu balu >= 5

    for (const auto& studentas : studentai) {
        if (studentas.galutinis < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else {
            kietiakiai.push_back(studentas);
        }
    }
    failo_spausdinimas(vargsiukai, "vargsiukai.txt", pasirinkite);
    failo_spausdinimas(kietiakiai, "kietiakiai.txt", pasirinkite);
}

int main() {
    list<Studentas> studentai;
    char pasirinkite;

    cout << "Ar norite nuskaityti duomenis is failo (y/n)? ";
    cin >> pasirinkite;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (pasirinkite == 'y') {
        cout << "Ar norite skaityti is atsitiktiniu studento failo? (y/n):";
        cin >> pasirinkite;
        string failas;
        if (pasirinkite == 'y') {
            cout << "Iveskite kiek studentu sugeneruoti (pvz. 1 000, 10 000, 100 000, ... 10 000 000: ";
            int skaicius_studentu;
            cin >> skaicius_studentu;
            failas = "studentai_" + to_string(skaicius_studentu) + ".txt";
            auto start = high_resolution_clock::now();
            generuoti_studentus_failui(failas, skaicius_studentu);
            auto end = high_resolution_clock::now();
            duration<double> duration = end - start;
            cout << fixed << setprecision(4);
            cout << "Atsitiktiniu studentu irasymo funkcija i faila uztruko: " << duration.count() << endl;
        }
        else {
            cout << "Failo pavadinimas: ";
            cin >> failas;
        }

        auto start = high_resolution_clock::now();
        nuskaityti_faila(failas, studentai);
        auto end = high_resolution_clock::now();
        duration<double> duration = end - start;
        cout << fixed << setprecision(4);
        cout << "Nuskaitymo funkcija uztruko: " << duration.count() << endl;
    }
    else {
        int studentuSkaicius;
        cout << "Iveskite studentu skaiciu:";
        cin >> studentuSkaicius;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < studentuSkaicius; i++) {
            Studentas temp;
            cout << "Studentas " << i + 1 << ":\n";
            cout << "Iveskite studento varda: ";
            getline(cin, temp.vardas);

            cout << "Iveskite studento pavarde: ";
            getline(cin, temp.pavarde);

            char pasirinkimas;
            cout << "Ar norite patys ivesti namu darbu ir egzamino pazymius? (t/n): ";
            cin >> pasirinkimas;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (pasirinkimas == 't') {
                cout << "Iveskite namu darbu pazymius (norint baigti spauskite Enter):\n";
                int pazym;
                while (true) {
                    string input;
                    getline(cin, input);
                    if (input.empty()) break;

                    pazym = stoi(input);

                    try
                    {
                        if (pazym > 10)
                            throw runtime_error("Pazymiai negali buti > 10");
                        if (pazym < 0)
                            throw runtime_error("Pazymiai negali buti < 0");
                        temp.namuDarbai.push_back(pazym);
                    }
                    catch (runtime_error& e)
                    {
                        cout << " Klaida " << e.what() << endl;
                        cout << "Iveskite pazymi dar karta: ";
                        cin >> pazym;
                    }
                }

                cout << "Iveskite egzamino pazymi: ";
                try
                {
                    cin >> temp.egzaminas;
                    if (temp.egzaminas < 0)
                        throw runtime_error("Ivestas neigiamas skaicius");
                    if (temp.egzaminas > 10)
                        throw runtime_error("Pazymiai negali buti > 10");
                }
                catch (runtime_error& e) {
                    cout << "Klaida " << e.what() << endl;
                    cout << "Ivesk egzamino ivertinima dar karta: ";
                    cin >> temp.egzaminas;
                }
            }
            else {
                int ndSk = generuoti_atsitiktini(1, 10);
                for (int j = 0; j < ndSk; j++) {
                    int pazymys = generuoti_atsitiktini(1, 10);
                    temp.namuDarbai.push_back(pazymys);
                }

                temp.egzaminas = generuoti_atsitiktini(1, 10);
            }

            studentai.push_back(temp);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    studentai.sort([](const Studentas& a, const Studentas& b)
        {
            return a.pavarde < b.pavarde;
        });

    cout << "Pasirinkite, kaip skaiciuoti bala ( v - vidurkis, m - mediana):";
    cin >> pasirinkite;
    if (pasirinkite == 'v')
    {
        for (auto& studentas : studentai)
            studentas.galutinis = galutinis(studentas.namuDarbai, studentas.egzaminas);
    }
    else
    {
        for (auto& studentas : studentai)
            studentas.galutinis = mediana(studentas.namuDarbai, studentas.egzaminas);
    }

    list<Studentas> vargsiukai; // Studentai su galutiniu balu < 5
    list<Studentas> kietiakiai; // Studentai su galutiniu balu >= 5
    auto start = high_resolution_clock::now();
    for (const auto& studentas : studentai) {
        if (studentas.galutinis < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else {
            kietiakiai.push_back(studentas);
        }
    }
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;
    cout << fixed << setprecision(4);
    cout << "Rusiavimas i dvi grupes uztruko: " << duration.count() << endl;

    start = high_resolution_clock::now();
    failo_spausdinimas(vargsiukai, "vargsiukai.txt", pasirinkite);
    failo_spausdinimas(kietiakiai, "kietiakiai.txt", pasirinkite);
    end = high_resolution_clock::now();

    duration = end - start;
    cout << fixed << setprecision(4);
    cout << "Spausdinimas i du failus uztruko: " << duration.count() << endl;
    return 0;
}
