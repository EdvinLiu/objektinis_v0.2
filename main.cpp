#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <limits>
#include <string>

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

int main()
{
	vector<Studentas> studentai;
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

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	char pasirinkite;
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
