#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "library.h"
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Bazinė klasė, apibūdinanti žmogų.
 *
 * Klasė Zmogus yra abstrakti klasė, kuri neleidžia kurti jos objektų tiesiogiai.
 * Tai bus tik pagrindas kitoms klasėms, pavyzdžiui, Studentas.
 */
class Zmogus {
protected:
	string vardas_; /**< Studentas vardas */
	string pavarde_; /**< Studentas pavardė */

public:
	/**
	 *@brief Konstruktorius be parametrų, inicijuoja vardą ir pavardę kaip tuščius stringus.
	 */
	Zmogus() : vardas_(""), pavarde_("") {}

	/**
	 * @brief Konstruktorius su parametrais, kuris nustato vardą ir pavardę.
	 *
	 * @param vardas Studentas vardas.
	 * @param pavarde Studentas pavardė.
	 */
	Zmogus(const string& vardas, const string& pavarde) : vardas_(vardas), pavarde_(pavarde) {}

	/**
	* @brief Virtualus destruktorius, kad užtikrintų teisingą atminties valdymą išvestinėse klasėse.
	*/
	virtual ~Zmogus() = default;

	virtual void print() const = 0;

	/**@brief vardo ir pavardes setteriai
	*/
	string vardas() const { return vardas_; }
	string pavarde() const { return pavarde_; }

};

/**
 * @brief Klasė, apibūdinanti studentą, paveldinčią Zmogus klasę.
 *
 * Studentas klasė turi papildomus duomenis, tokius kaip egzaminų ir namų darbų pažymiai,
 * bei metodus, skirtus manipuliuoti šiais duomenimis.
 */
class Studentas : public Zmogus {
private:
	double egzaminas_; /**< Egzamino pažymys */
	vector<double> nd_; /**< Namų darbų pažymiai */
	double galutinis_; /**< Galutinis pažymys */
public:
	/**
	 * @brief Konstruktorius, kuris nustato pradinius parametrus.
	 */
	Studentas(): Zmogus(), egzaminas_(0), nd_(0), galutinis_(0.0) {}

	Studentas(const std::string& vardas, const std::string& pavarde, double egzaminas, const std::vector<double>& nd)
		: Zmogus(vardas, pavarde), egzaminas_(egzaminas), nd_(nd), galutinis_(0.0) {}

	Studentas(const std::string& vardas, const std::string& pavarde, double egzaminas, const std::vector<double>& nd, const int galutinis)
		: Zmogus(vardas, pavarde), egzaminas_(egzaminas), nd_(nd), galutinis_(galutinis) {}


	/**
	 * @brief Destruktorius, kuris išvalys namų darbų vektorių.
	 */
	~Studentas(){
		nd_.clear();
	}
	
	/**
	 * @brief Kopijavimo konstruktorius.
	 *
	 * @param other Kitas Studentas objektas, kurio duomenys bus nukopijuoti.
	 */
	Studentas(const Studentas& other) //copy constructor
		: Zmogus(other.vardas_, other.pavarde_),
		egzaminas_(other.egzaminas_), nd_(other.nd_), galutinis_(other.galutinis_) {}

	/**
	 * @brief Kopijavimo priskyrimo operatorius.
	 *
	 * @param other Kitas Studentas objektas, kurio duomenys bus priskiriami.
	 * @return Studentas& Grąžina šį objektą.
	 */
	Studentas& operator=(const Studentas& other) { //copy assignment operator
		if (this == &other) return *this;  // Pats sau nepriskiria
		vardas_ = other.vardas_;
		pavarde_ = other.pavarde_;
		egzaminas_ = other.egzaminas_;
		nd_ = other.nd_;
		galutinis_ = other.galutinis_;
		return *this;
	}


	/** Getteriai ir setteriai
	*/
	double egzaminas() const { return egzaminas_; }
	std::vector<double> nd() const { return nd_; }
	double galutinis() const { return galutinis_; }
	
	//Setteriai
	void setEgzaminas(double egzaminas) {
		egzaminas_ = egzaminas;
	}
	void setnd(vector<double> nd) {
		nd_ = nd;
	}
	void setGalutinis(double galutinis) {
		galutinis_ = galutinis;
	}

	template <typename Container>
	friend void failo_spausdinimas(const Container& studentai, const string& failas, char pasirinkite);
	template <typename Container>
	friend void nuskaityti_faila(const string& failo_pavadinimas, Container& studentai);

	void print() const override {
		cout << "Studentas: " << vardas_ << " " << pavarde_ << ", egzaminas: " << egzaminas_ << ", galutinis: " << galutinis_ << endl;
	}

	/**
	 * @brief Įveda studento duomenis.
	 */
	friend istream& operator>>(istream& in, Studentas& studentas) {
		string vardas, pavarde;
		double egzaminas;
		vector<double> namuDarbai;

		if (&in == &cin) {
			cout << "Iveskite studento varda: ";
			getline(in, vardas);
			cout << "Iveskite studento pavarde: ";
			getline(in, pavarde);
			char pasirinkimas;
			cout << "Ar norite patys ivesti namu darbu ir egzamino pazymius? (t/n): ";
			in >> pasirinkimas;
			in.ignore(numeric_limits<streamsize>::max(), '\n');

			if (pasirinkimas == 't') {
				cout << "Iveskite namu darbu pazymius (norint baigti spauskite Enter):\n";
				while (true) {
					string input;
					getline(in, input);
					if (input.empty()) break;

					try {
						int pazym = stoi(input);
						if (pazym > 10 || pazym < 0)
							throw runtime_error("Pažymiai turi būti tarp 0 ir 10.");
						namuDarbai.push_back(pazym);
						}
					catch (exception& e) {
						cout << "Klaida: " << e.what() << "\nĮveskite pažymį dar kartą: ";
						}
					}

				cout << "Įveskite egzamino pazymi: ";
				while (true) {
					try {
						in >> egzaminas;
						if (egzaminas < 0 || egzaminas > 10)
							throw runtime_error("Egzamino pažymys turi būti tarp 0 ir 10.");
						break;
					}
					catch (exception& e) {
						cout << "Klaida: " << e.what() << "\nĮveskite egzamino pažymį dar kartą: ";
						in.clear();
						in.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}
			}
			else {
				srand(time(nullptr));
				for (int j = 0; j < 5; j++) {
					namuDarbai.push_back(rand() % 11);
				}
				egzaminas = rand() % 11;
			}
			studentas.vardas_ = vardas;
			studentas.pavarde_ = pavarde;
			studentas.setnd(namuDarbai);
			studentas.setEgzaminas(egzaminas);
			studentas.setGalutinis(0);
				namuDarbai.clear();
		}
		else {
			in >> vardas >> pavarde;
			double pazym;
			while (in >> pazym) {
				namuDarbai.push_back(pazym);
			}

			// Egzaminas yra paskutinis pažymys
			if (!namuDarbai.empty()) {
				egzaminas = namuDarbai.back();
				namuDarbai.pop_back();
			}

			studentas.vardas_ = vardas;
			studentas.pavarde_ = pavarde;
			studentas.setnd(namuDarbai);
			studentas.setEgzaminas(egzaminas);
			studentas.setGalutinis(0);

		}
		return in;
	}

	/**
	 * @brief Išveda studento informaciją
	 */
	friend ostream& operator<<(ostream& os, const Studentas& s) {
		os << left << setw(15) << s.vardas_
			<< left << setw(20) << s.pavarde_
			<< right << setw(10) << fixed << setprecision(2) << s.galutinis_;
		return os;
	}

};

#endif // STUDENTAS_H

