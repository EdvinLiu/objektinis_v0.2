#include "library.h"
#include "Functions.h"
#include "Studentas.h"

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
        output << studentas.vardas() << " " << studentas.pavarde() << " " << studentas.galutinis() << endl;
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
                string vardas, pavarde;
                double egzaminas;
                vector<double> namuDarbai;
                line_stream >> vardas >> pavarde;

                double pazym;
                while (line_stream >> pazym) {
                    namuDarbai.push_back(pazym);  // Dedame pažymius
                }

                // Egzamino pažymys yra paskutinis, todėl priskiriame jį atskirai
                if (!namuDarbai.empty()) {
                    egzaminas = namuDarbai.back();  // Paskutinis pažymys yra egzaminas
                    namuDarbai.pop_back();  // Pašaliname egzaminą iš namų darbų sąrašo
                }

                studentai.emplace_back(vardas, pavarde, egzaminas, namuDarbai, 0);  // Pridedame studentą į vektorių
            }
        }
    }

    failas.close();  // Uždaryti failą
}

template <typename Container>
void ekranospausdinimas(Container& studentai) {
    for (const auto& studentas : studentai) {
        cout << studentas.vardas() << " " << studentas.pavarde() << " " << studentas.galutinis() << endl;
    }
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
        string pavarde, vardas;
        double egzaminas;
        vector<double> namuDarbai;

        int studentuSkaicius;
        cout << "Iveskite studentu skaiciu: ";
        cin >> studentuSkaicius;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < studentuSkaicius; i++) {
            cout << "Studentas " << i + 1 << ":\n";
            cout << "Iveskite studento varda: ";
            getline(cin, vardas);

            cout << "Iveskite studento pavarde: ";
            getline(cin, pavarde);

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
                        vector<double> namuDarbai;
                        namuDarbai.push_back(pazym);
                    }
                    catch (runtime_error& e) {
                        cout << "Klaida " << e.what() << endl;
                        cout << "Iveskite pazymi dar karta: ";
                    }
                }

                cout << "Iveskite egzamino pazymi: ";
                try {
                    cin >> egzaminas;
                    if (egzaminas < 0)
                        throw runtime_error("Ivestas neigiamas skaicius");
                    if (egzaminas > 10)
                        throw runtime_error("Pazymiai negali buti > 10");
                }
                catch (runtime_error& e) {
                    cout << "Klaida " << e.what() << endl;
                    cout << "Iveskite egzamino ivertinima dar karta: ";
                    cin >> egzaminas;
                }
            }
            else {
                int ndSk = generuoti_atsitiktini(1, 10);
                for (int j = 0; j < ndSk; j++) {
                    int pazymys = generuoti_atsitiktini(1, 10);
                    namuDarbai.push_back(pazymys);
                }

                egzaminas = generuoti_atsitiktini(1, 10);
            }

            studentai.emplace_back(vardas,pavarde,egzaminas,namuDarbai,0);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cout << "Pasirinkite, kaip skaiciuoti bala (v - vidurkis, m - mediana): ";
    cin >> pasirinkite;
    if (pasirinkite == 'v') {
        for (auto& studentas : studentai)
        {
            double galut = galutinis(studentas.nd(), studentas.egzaminas());
            studentas.setGalutinis(galut);
        }
    }
    else {
        for (auto& studentas : studentai)
        {
            double galutinis = mediana(studentas.nd(), studentas.egzaminas());
            studentas.setGalutinis(galutinis);
        }
    }

    cout << "Pasirinkite skaidymo strategija (1, 2 arba 3): ";
    int strategija;
    cin >> strategija;

    char rusiavimas;
    cout << "Rusiuoti pagal: varda (v), pavarde (p) arba galutini (g)? ";
    cin >> rusiavimas;
    if constexpr (is_same<Container, vector<Studentas>>::value) {
        if (rusiavimas == 'v') {
            sort(studentai.begin(), studentai.end(), pagal_varda);
        }
        if (rusiavimas == 'p') {
            sort(studentai.begin(), studentai.end(), pagal_pavarde);
        }
        if (rusiavimas == 'g') {
            sort(studentai.begin(), studentai.end(), pagal_galutini);
        }
    }
    else if constexpr (is_same<Container, list<Studentas>>::value) {
        if (rusiavimas == 'v') {
            studentai.sort(pagal_varda);
        }
        if (rusiavimas == 'p') {
            studentai.sort(pagal_pavarde);
        }
        if (rusiavimas == 'g') {
            studentai.sort(pagal_galutini);
        }
    }
    cout << "Ar reikia papildomai atspausdinti viska ekrane? (y/n) : ";
    char pas;
    cin >> pas;
    if (pas == 'y') {
        ekranospausdinimas(studentai);
    }
    if (strategija == 1) {
        Container vargsiukai; // Studentai su galutiniu balu < 5
        Container kietiakiai; // Studentai su galutiniu balu >= 5
        auto start = high_resolution_clock::now();
        for (const auto& studentas : studentai) {
            if (studentas.galutinis() < 5.0) {
                vargsiukai.push_back(studentas);
            }
            else {
                kietiakiai.push_back(studentas);
            }
        }
        auto end = high_resolution_clock::now();

        duration<double> duration = end - start;
        cout << fixed << setprecision(4);
        cout << "Rusiavimas i vargsiukus ir kietiakius uztruko: " << duration.count() << endl;



        start = high_resolution_clock::now();
        failo_spausdinimas(vargsiukai, "vargsiukai.txt", pasirinkite);
        failo_spausdinimas(kietiakiai, "kietiakiai.txt", pasirinkite);
        end = high_resolution_clock::now();
        duration = end - start;
        cout << fixed << setprecision(4);
        cout << "Spausdinimas i failus uztruko: " << duration.count() << endl;
    }
    else if (strategija == 2) {
        Container vargsiukai; // Studentai su galutiniu balu < 5
        auto start = high_resolution_clock::now();
        for (auto it = studentai.begin(); it != studentai.end();) {
            if (it->galutinis() < 5.0) {
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
        cout << "Rusiavimas uztruko: " << duration.count() << endl;

        char rusiavimas;
        cout << "Rusiuoti pagal: varda (v), pavarde (p) arba galutini (g)? ";
        cin >> rusiavimas;


        start = high_resolution_clock::now();
        failo_spausdinimas(vargsiukai, "vargsiukai.txt", pasirinkite);
        failo_spausdinimas(studentai, "kietiakiai.txt", pasirinkite);
        end = high_resolution_clock::now();
        duration = end - start;
        cout << fixed << setprecision(4);
        cout << "Isvedimas uztruko: " << duration.count() << endl;
    }
    else {
        auto start = high_resolution_clock::now();

        // Partition atskiria studentus vietoje ir grąžina iteratorių į pirmą "kietiakių" elementą
        auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& s) {
            return s.galutinis() < 5.0;
            });

        // Sukuriame „vargsiukų“ ir „kietiakių“ konteinerius ir kopijuojame pagal rūšiavimo rezultatą
        Container vargsiukai;
        Container kietiakiai;
        std::copy(studentai.begin(), it, std::back_inserter(vargsiukai));
        std::copy(it, studentai.end(), std::back_inserter(kietiakiai));

        auto end = high_resolution_clock::now();
        duration<double> duration = end - start;
        cout << fixed << setprecision(4);

        cout << "Rusiavimas su partition uztruko: " << duration.count() << " sek." << endl;

        char rusiavimas;
        cout << "Rusiuoti pagal: varda (v), pavarde (p) arba galutini (g)? ";
        cin >> rusiavimas;


        // Failų spausdinimas naudojant copy_if algoritmą
        start = high_resolution_clock::now();
        failo_spausdinimas(vargsiukai, "vargsiukai.txt", pasirinkite);
        failo_spausdinimas(kietiakiai, "kietiakiai.txt", pasirinkite);
        end = high_resolution_clock::now();
        duration = end - start;
        cout << fixed << setprecision(4);
        cout << "Spausdinimas i failus uztruko: " << duration.count() << " sek." << endl;
    }
}

int main() {
    char pasirinkimas;
    cout << "Pasirinkite studentu konteineri (v - vector, l - list): ";
    cin >> pasirinkimas;

    if (pasirinkimas == 'v') {
        vector<Studentas> studentai;
        vykdyti_programa(studentai);

        vector<Studentas> copystudentai = studentai;
        ekranospausdinimas(copystudentai);

        vector<Studentas> operatorstudentai;
        operatorstudentai = studentai;
        ekranospausdinimas(operatorstudentai);
    }
    else if (pasirinkimas == 'l') {
        list<Studentas> studentai;
        vykdyti_programa(studentai);

        list<Studentas> copystudentai = studentai;
        ekranospausdinimas(studentai);

        list<Studentas> operatorstudentai;
        operatorstudentai = studentai;
        ekranospausdinimas(studentai);
    }
    else {
        cout << "Pasirinkimas neteisingas." << endl;
    }

    return 0;
}
