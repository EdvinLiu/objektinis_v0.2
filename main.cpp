#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>

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

	cout << "\nRezultatai:\n";
	for (const auto& studentas : studentai)
	{
		double galutinisBalas = galutinis(studentas.namuDarbai, studentas.egzaminas);
		cout << studentas.vardas << " " << studentas.pavarde
			<< " galutinis balas: " << fixed << setprecision(2)
			<< galutinisBalas << endl;
	}

	return 0;


}
