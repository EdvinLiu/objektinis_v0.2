#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <algorithm>

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
	studentai.resize(studentuSkaicius);
	
	for (int i = 0; i < studentuSkaicius; i++)
	{
		cout << "Studentas " << i + 1 << ":\n";
		cout << "Iveskite studento varda: ";
		cin >> studentai[i].vardas;

		cout << "Iveskite studento pavarde: ";
		cin >> studentai[i].pavarde;

		int ndSk;
		cout << "Iveskite namu darbu skaiciu: ";
		cin >> ndSk;
		studentai[i].namuDarbai.resize(ndSk);

		cout << "Iveskite visu namu darbu pazymius: ";
		for (int j = 0; j < ndSk; j++)
		{
			cin >> studentai[i].namuDarbai[j];
		}

		cout << "Iveskite egzamino pazymi: ";
		cin >> studentai[i].egzaminas;
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
