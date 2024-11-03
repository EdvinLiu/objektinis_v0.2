#include "library.h"
#include "Functions.h"
#include "Studentas.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <chrono>
#include <limits>

using namespace std;
using namespace std::chrono;

template <typename Container>
void failo_spausdinimas(const Container& studentai, const string& failas, char pasirinkite) {
    ofstream output(failas);
    if (!output.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failas << endl;
        return;
    }

    for (const auto& studentas : studentai) {
        output << studentas.vardas << " " << studentas.pavarde << " " << studentas.galutinis << endl;
    }

    output.close();
}

template <typename Container>
void nuskaityti_faila(const string& failo_pavadinimas, Container& studentai) {
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


template <typename Container>
void vykdyti_programa(Container& studentai) {
    char pasirinkite;

    cout << "Ar norite nuskaityti duomenis is failo (y/n)? ";
    cin >> pasirinkite;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (pasirinkite == 'y') {
        cout << "Ar norite skaityti is atsitiktiniu studento failo? (y/n): ";
        cin >> pasirinkite;
        string failas;
        if (pasirinkite == 'y') {
            cout << "Iveskite kiek studentu sugeneruoti (pvz. 1 000, 10 000, 100 000, ... 10 000 000): ";
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
        cout << "Iveskite studentu skaiciu: ";
        cin >> studentuSkaicius;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < studentuSkaicius; i++) {
            Studentas studentas;
            cout << "Studentas " << i + 1 << ":\n";
            cout << "Iveskite studento varda: ";
            getline(cin, studentas.vardas);

            cout << "Iveskite studento pavarde: ";
            getline(cin, studentas.pavarde);

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

                    try {
                        if (pazym > 10)
                            throw runtime_error("Pazymiai negali buti > 10");
                        if (pazym < 0)
                            throw runtime_error("Pazymiai negali buti < 0");
                        studentas.namuDarbai.push_back(pazym);
                    }
                    catch (runtime_error& e) {
                        cout << "Klaida " << e.what() << endl;
                        cout << "Iveskite pazymi dar karta: ";
                    }
                }

                cout << "Iveskite egzamino pazymi: ";
                try {
                    cin >> studentas.egzaminas;
                    if (studentas.egzaminas < 0)
                        throw runtime_error("Ivestas neigiamas skaicius");
                    if (studentas.egzaminas > 10)
                        throw runtime_error("Pazymiai negali buti > 10");
                }
                catch (runtime_error& e) {
                    cout << "Klaida " << e.what() << endl;
                    cout << "Iveskite egzamino ivertinima dar karta: ";
                    cin >> studentas.egzaminas;
                }
            }
            else {
                int ndSk = generuoti_atsitiktini(1, 10);
                for (int j = 0; j < ndSk; j++) {
                    int pazymys = generuoti_atsitiktini(1, 10);
                    studentas.namuDarbai.push_back(pazymys);
                }

                studentas.egzaminas = generuoti_atsitiktini(1, 10);
            }

            studentai.push_back(studentas);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    if constexpr (std::is_same<Container, std::vector<Studentas>>::value) {
        std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.pavarde < b.pavarde;
            });
    }
    else if constexpr (std::is_same<Container, std::list<Studentas>>::value) {
        studentai.sort([](const Studentas& a, const Studentas& b) {
            return a.pavarde < b.pavarde;
            });
    }


    cout << "Pasirinkite, kaip skaiciuoti bala (v - vidurkis, m - mediana): ";
    cin >> pasirinkite;
    if (pasirinkite == 'v') {
        for (auto& studentas : studentai)
            studentas.galutinis = galutinis(studentas.namuDarbai, studentas.egzaminas);
    }
    else {
        for (auto& studentas : studentai)
            studentas.galutinis = mediana(studentas.namuDarbai, studentas.egzaminas);
    }

    cout << "Pasirinkite skaidymo strategija (1, 2 arba 3): ";
    int strategija;
    cin >> strategija;

    if (strategija == 1) {
        Container vargsiukai; // Studentai su galutiniu balu < 5
        Container kietiakiai; // Studentai su galutiniu balu >= 5
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
        cout << "Rusiavimas i vargšiukus ir kietiakius užtruko: " << duration.count() << endl;

        failo_spausdinimas(vargsiukai, "vargsiukai.txt", pasirinkite);
        failo_spausdinimas(kietiakiai, "kietiakiai.txt", pasirinkite);
    }
    else if (strategija == 2) {
        Container vargsiukai; // Studentai su galutiniu balu < 5
        auto start = high_resolution_clock::now();
        for (auto it = studentai.begin(); it != studentai.end();) {
            if (it->galutinis < 5.0) {
                vargsiukai.push_back(*it);
                it = studentai.erase(it); // Pašalinti studentą iš pagrindinės konteinerio
            }
            else {
                ++it;
            }
        }
        auto end = high_resolution_clock::now();


        duration<double> duration = end - start;
        cout << fixed << setprecision(4);
        cout << "Rusiavimas i vargšiukus užtruko: " << duration.count() << endl;

        failo_spausdinimas(vargsiukai, "vargsiukai.txt", pasirinkite);
        failo_spausdinimas(studentai, "kietiakiai.txt", pasirinkite)
    }
    else {
        cout << "Pasirinkta neteisinga strategija!" << endl;
    }
}

int main() {
    char pasirinkimas;
    cout << "Pasirinkite studentu konteineri (v - vector, l - list): ";
    cin >> pasirinkimas;

    if (pasirinkimas == 'v') {
        vector<Studentas> studentai;
        vykdyti_programa(studentai);
    }
    else if (pasirinkimas == 'l') {
        list<Studentas> studentai;
        vykdyti_programa(studentai);
    }
    else {
        cout << "Pasirinkimas neteisingas." << endl;
    }

    return 0;
}
