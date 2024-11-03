#include "library.h"
#include "Functions.h"
#include "Studentas.h"


template <typename Container>
void nuskaityti_faila(const std::string& failoPavadinimas, Container& studentai) {
    std::ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        std::cout << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
        return;
    }

    Studentas studentas;
    while (failas >> studentas.vardas >> studentas.pavarde) {
        studentas.namuDarbai.clear();
        for (int i = 0; i < 5; ++i) { // Tarkime, kad namų darbų yra 5
            int pazymys;
            failas >> pazymys;
            studentas.namuDarbai.push_back(pazymys);
        }
        failas >> studentas.egzaminas;
        studentai.push_back(studentas);
    }

    failas.close();
}


template <typename Container>
void generuoti_studentus_failui(const std::string& failoPavadinimas, int kiekis, Container& studentai) {
    std::ofstream failas(failoPavadinimas);
    for (int i = 0; i < kiekis; ++i) {
        Studentas studentas;
        studentas.vardas = "Vardas" + std::to_string(i + 1);
        studentas.pavarde = "Pavarde" + std::to_string(i + 1);
        studentas.namuDarbai = { generuoti_atsitiktini(1, 10), generuoti_atsitiktini(1, 10),
                                 generuoti_atsitiktini(1, 10), generuoti_atsitiktini(1, 10),
                                 generuoti_atsitiktini(1, 10) };
        studentas.egzaminas = generuoti_atsitiktini(1, 10);
        studentai.push_back(studentas);
    }
    


// Funkcija, kuri vykdo pagrindinę programą
template <typename Container>
void vykdyti_programa(Container& studentai) {
        char pasirinkite;

        cout << "Ar norite nuskaityti duomenis is failo (y/n)? ";
        cin >> pasirinkite;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pasirinkite == 'y') {
            cout << "Ar norite skaityti is atsitiktiniu studento failo? (y/n):";
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

        vector<Studentas> vargsiukai; // Studentai su galutiniu balu < 5
        vector<Studentas> kietiakiai; // Studentai su galutiniu balu >= 5
        auto start = high_resolution_clock::now();
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
}

int main() {
    char konteineris;
    cout << "Pasirinkite duomenu struktura (v - vector, l - list): ";
    cin >> konteineris;

    // Apibrėžiamas studentų konteineris, remiantis vartotojo pasirinkimu
    if (konteineris == 'v') {
        vector<Studentas> studentai;
        vykdyti_programa(studentai); // Funkcija, kuri vykdo pagrindinį kodą
    }
    else if (konteineris == 'l') {
        list<Studentas> studentai;
        vykdyti_programa(studentai); // Funkcija, kuri vykdo pagrindinį kodą
    }
    else {
        cout << "Neteisingas pasirinkimas." << endl;
        return 1;
    }

    return 0;
}
failas.close();
}


template <typename Container>
void failo_spausdinimas(const Container& studentai, const std::string& failas, char pasirinkite) {
    std::ofstream output(failas);
    if (!output.is_open()) {
        std::cout << "Nepavyko atidaryti failo: " << failas << std::endl;
        return;
    }

    for (const auto& studentas : studentai) {
        output << studentas.vardas << " " << studentas.pavarde << " ";
        for (const auto& nd : studentas.namuDarbai) {
            output << nd << " ";
        }
        output << studentas.egzaminas << std::endl;
    }

    output.close();
}
