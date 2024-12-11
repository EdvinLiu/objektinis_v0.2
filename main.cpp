#include "library.h"
#include "Functions.h"
#include "Studentas.h"

using namespace std;
using namespace std::chrono;

/**
 * @brief Išspausdina studentų informaciją į failą.
 *
 * Ši funkcija išspausdina visų studentų informaciją į nurodytą failą.
 *
 * @tparam Container Studentų konteinerio tipas (pvz., vector ar list).
 * @param studentai Konteineris, kuriame saugomi studentų duomenys.
 * @param failas Failo pavadinimas, kuriame bus išspausdinta informacija.
 * @param pasirinkite Pasirinkimas, ar norima spausti į failą, ar atlikti kitus veiksmus.
 */
template <typename Container>
void failo_spausdinimas(const Container& studentai, const string& failas, char pasirinkite) {
    ofstream output(failas);
    if (!output.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failas << endl;
        return;
    }

    for (const auto& studentas : studentai) {
        output << studentas << endl;
    }

    output.close();
}

/**
 * @brief Nuskaityti studentų duomenis iš failo.
 *
 * Ši funkcija nuskaityti studentų duomenis iš failo ir įrašyti juos į nurodytą konteinerį.
 *
 * @tparam Container Studentų konteinerio tipas (pvz., vector ar list).
 * @param failo_pavadinimas Failo pavadinimas, iš kurio bus nuskaitomi studentų duomenys.
 * @param studentai Konteineris, į kurį bus įrašyti studentų duomenys.
 */
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

        Studentas temp;
        string line;

        while (getline(iss, line)) {
            if (!line.empty()) {
                istringstream line_stream(line);  // Sukuriame srautą eilutei
                string vardas, pavarde;
                double egzaminas;
                vector<double> namuDarbai;
                line_stream >> temp;
                studentai.push_back(temp);
            }
        }
    }

    failas.close();  // Uždaryti failą
}

/**
 * @brief Išspausdina studentų informaciją į ekraną.
 *
 * Ši funkcija išspausdina studentų informaciją į ekraną, rodydama vardą, pavardę ir galutinį balą.
 *
 * @tparam Container Studentų konteinerio tipas (pvz., vector ar list).
 * @param studentai Konteineris, kuriame yra studentų duomenys.
 */
template <typename Container>
void ekranospausdinimas(Container& studentai) {
    for (const auto& studentas : studentai) {
        cout << studentas.vardas() << " " << studentas.pavarde() << " " << studentas.galutinis() << endl;
    }
}

/**
 * @brief Vykdo pagrindinę programą, valdydama studentų duomenų nuskaitymą, apdorojimą ir išvedimą.
 *
 * Ši funkcija leidžia vartotojui pasirinkti, kaip bus nuskaityti ir apdorojami studentų duomenys,
 * bei kokiu būdu bus apskaičiuotas galutinis balas.
 *
 * @tparam Container Studentų konteinerio tipas (pvz., vector ar list).
 * @param studentai Konteineris, kuriame bus saugomi studentų duomenys.
 */
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
        Studentas temp;
        int studentu_sk;
        cout << "Iveskite Studentu skaiciu:" << endl;
        cin >> studentu_sk;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int i = 0; i < studentu_sk; i++) {
            cin >> temp;
            studentai.push_back(temp);
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

/**
 * @brief Pagrindinė funkcija, paleidžianti programą.
 *
 * Ši funkcija leidžia pasirinkti konteinerį, kuriame bus saugomi studentų duomenys (vector arba list),
 * ir pradeda programos vykdymą.
 *
 * @return 0, jei programa baigta sėkmingai.
 */
int main() {
    char pasirinkimas;
    cout << "Pasirinkite studentu konteineri (v - vector, l - list): ";
    cin >> pasirinkimas;

    if (pasirinkimas == 'v') {
        vector<Studentas> studentai;
        vykdyti_programa(studentai);

        //vector<Studentas> copystudentai = studentai;  //copy constructor
        //ekranospausdinimas(copystudentai);

        //vector<Studentas> operatorstudentai; //copy assignment operator
        //operatorstudentai = studentai;
        //ekranospausdinimas(operatorstudentai);
    }
    else if (pasirinkimas == 'l') {
        list<Studentas> studentai;
        vykdyti_programa(studentai);

        //list<Studentas> copystudentai = studentai;
        //ekranospausdinimas(studentai);

        //list<Studentas> operatorstudentai;
        //operatorstudentai = studentai;
        //ekranospausdinimas(studentai);
    }
    else {
        cout << "Pasirinkimas neteisingas." << endl;
    }

    return 0;
}
