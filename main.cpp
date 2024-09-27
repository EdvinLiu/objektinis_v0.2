#include "library.h"
#include "Functions.h"
#include "Studentas.h"

using namespace std;

int main() {
    vector<Studentas> studentai;
    char pasirinkite;

    cout << "Ar norite nuskaityti duomenis is failo (y/n)? ";
    cin >> pasirinkite;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (pasirinkite == 'y') {
        cout << "failo pavadinimas: ";
        string failas;
        cin >> failas;
        nuskaityti_faila(failas, studentai);
    }
    else {
        int studentuSkaicius;
        cout << "Iveskite studentu skaiciu:";
        cin >> studentuSkaicius;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        studentai.resize(studentuSkaicius);

        for (int i = 0; i < studentuSkaicius; i++) {
            cout << "Studentas " << i + 1 << ":\n";
            cout << "Iveskite studento varda: ";
            getline(cin, studentai[i].vardas);

            cout << "Iveskite studento pavarde: ";
            getline(cin, studentai[i].pavarde);

            char pasirinkimas;
            cout << "Ar norite patys ivesti namu darbu ir egzamino pazymius? (t/n): ";
            cin >> pasirinkimas;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (pasirinkimas == 't') {
                cout << "Iveskite namu darbu pazymius (norint baigti spauskite Enter):\n";
                int pazymys;
                while (true) {
                    string input;
                    getline(cin, input);
                    if (input.empty()) break;

                    pazymys = stoi(input);

                    try
                    {
                        if (pazymys > 10)
                            throw runtime_error("Pazymiai negali buti > 10");
                        if (pazymys < 0) 
                            throw runtime_error("Pazymiai negali buti < 0");
                        studentai[i].namuDarbai.push_back(pazymys);
                    }
                    catch (runtime_error& e)
                    {
                        cout << " Klaida" << e.what() << endl;
                    }
                }

                cout << "Iveskite egzamino pazymi: ";
                try
                {
                    cin >> studentai[i].egzaminas;
                    if (studentai[i].egzaminas < 0)
                        throw runtime_error("Ivestas neigiamas skaicius");
                    if (studentai[i].egzaminas > 10)
                        throw runtime_error("Pazymiai negali buti > 10");
                }
                catch(runtime_error& e) {
                    cout << "Klaida" << e.what() << endl;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                int ndSk = generuoti_atsitiktini(1, 10);
                for (int j = 0; j < ndSk; j++) {
                    int pazymys = generuoti_atsitiktini(1, 10);
                    studentai[i].namuDarbai.push_back(pazymys);
                }

                studentai[i].egzaminas = generuoti_atsitiktini(1, 10);
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b)
    {
        return a.vardas < b.vardas;
    });

    cout << "Pasirinkite, kaip skaiciuoti bala ( v - vidurkis, m - mediana):";
    cin >> pasirinkite;
    cout << setw(15) << left << "Vardas" << setw(15) << "Pavarde" << setw(15)
        << (pasirinkite == 'v' ? "galutinis(Vid.)" : "Galutinis(Med.)") << endl;

    for (const auto& studentas : studentai) {
        double galutinisBalas = (pasirinkite == 'v') ? galutinis(studentas.namuDarbai, studentas.egzaminas) : mediana(studentas.namuDarbai, studentas.egzaminas);
        cout << setw(15) << left << studentas.vardas << setw(15) << studentas.pavarde
            << setw(10) << fixed << setprecision(2) << galutinisBalas << endl;
    }

    return 0;
}
