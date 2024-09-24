#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <limits>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;
struct Studentas
{
	string vardas;
	string pavarde;
	vector<int> namuDarbai;
	int egzaminas;
};

double galutinis(const vector<int>& nd, int egzaminas)
{
	double suma_nd = accumulate(nd.begin(), nd.end(), 0);
	return (suma_nd / nd.size()) * 0.4 + 0.6 * egzaminas;
}

double mediana(const vector<int>& nd, int egzaminas)
{
	vector<int> sortednd = nd;
	sort(sortednd.begin(), sortednd.end());
	size_t size = sortednd.size();

	if (size % 2 == 2) return (sortednd[size / 2 - 1] + sortednd[size / 2] / 2.0) * 0.4 + 0.6 * egzaminas;
	else return (sortednd[size / 2]) * 0.4 + 0.6 * egzaminas;;

}

int generuoti_atsitiktini(int min, int max)
{
	srand(time(nullptr)); // Nustatome atsitiktinį skaičių generatoriaus pradinę vertę
	// Sugeneruojame atsitiktinę reikšmę tarp min ir max
	return min + rand() % (max - min + 1);
}

void nuskaityti_faila(const string& failo_pavadinimas, vector <Studentas>& studentai)
{
	ifstream failas(failo_pavadinimas);;
	if (!failas.is_open())
	{
		cout << "Nepavyko atidaryti failo:" << endl;
		return;
	}
	string pavarde, vardas;
	int nd;

	failas.ignore(numeric_limits<streamsize>::max(), '\n');

	while (failas >> pavarde >> vardas)
	{
		Studentas studentas;
		studentas.pavarde = pavarde;
		studentas.vardas = vardas;

		while (failas >> nd)
		{
			if (failas.peek() == '\n') break;
			studentas.namuDarbai.push_back(nd);
		}

		studentas.egzaminas = studentas.namuDarbai.back(); // Paskutinę reikšmę priskiriame egzamino rezultatui
		studentas.namuDarbai.pop_back(); // Išimame paskutinę reikšmę iš namų darbų

		studentai.push_back(studentas);

		failas.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	failas.close();
}

int main()
{
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
	else 
	{
		int studentuSkaicius;
		cout << "Iveskite studentu skaiciu:";
		cin >> studentuSkaicius;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		studentai.resize(studentuSkaicius);

		for (int i = 0; i < studentuSkaicius; i++)
		{
			cout << "Studentas " << i + 1 << ":\n";
			cout << "Iveskite studento varda: ";
			getline(cin, studentai[i].vardas);

			cout << "Iveskite studento pavarde: ";
			getline(cin, studentai[i].pavarde);

			char pasirinkimas;
			cout << "Ar norite patys ivesti namu darbu ir egzamino pazymius? (t/n): ";
			cin >> pasirinkimas;

			if (pasirinkimas == 't')
			{
				cout << "Iveskite namu darbu pazymius (norint baigti, iveskite neigiama skaiciu arba spauskite Enter):\n";
				int pazymys;
				while (true)
				{
					string input;
					getline(cin, input);
					if (input.empty()) break;

					pazymys = stoi(input);

					if (pazymys < 0) break;

					studentai[i].namuDarbai.push_back(pazymys);

				}

				cout << "Iveskite egzamino pazymi: ";
				cin >> studentai[i].egzaminas;
			}
			else
			{
				int ndSk = generuoti_atsitiktini(1, 10);
				for (int j = 0; j < ndSk; j++)
				{
					int pazymys = generuoti_atsitiktini(1, 10);
					studentai[i].namuDarbai.push_back(pazymys);
				}

				studentai[i].egzaminas = generuoti_atsitiktini(1, 10);
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	
	cout << "Pasirinkite, kaip skaiciuoti bala ( v - vidurkis, m - mediana):";
	cin >> pasirinkite;
	cout << "Vardas		Pavarde		" << (pasirinkite == 'v' ? "galutinis (Vid.)" : "Galutinis (Med.)") << endl;

	for (const auto& studentas : studentai)
	{
		double galutinisBalas = (pasirinkite == 'v')? galutinis(studentas.namuDarbai, studentas.egzaminas) : mediana(studentas.namuDarbai, studentas.egzaminas);
		cout << studentas.vardas << "	" << studentas.pavarde
			<< "		" << fixed << setprecision(2)
			<< galutinisBalas << endl;
	}

	return 0;


}
