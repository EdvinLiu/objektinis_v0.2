#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <vector>
#include <string>

using namespace std;

class Studentas {
private:
	std::string vardas_;
	std::string pavarde_;
	double egzaminas_;
	std::vector<double> nd_;
	double galutinis_;
	// interfeisas
public:
	Studentas(): vardas_(""), pavarde_(""), egzaminas_(0), nd_(0), galutinis_(0.0) {}

	Studentas(const std::string& vardas, const std::string& pavarde, double egzaminas, const std::vector<double>& nd)
		: vardas_(vardas), pavarde_(pavarde), egzaminas_(egzaminas), nd_(nd), galutinis_(0.0) {}

	Studentas(const std::string& vardas, const std::string& pavarde, double egzaminas, const std::vector<double>& nd, const int galutinis)
		: vardas_(vardas), pavarde_(pavarde), egzaminas_(egzaminas), nd_(nd), galutinis_(galutinis) {}
	
	~Studentas(){}

	Studentas(const Studentas& other)
		: vardas_(other.vardas_), pavarde_(other.pavarde_),
		egzaminas_(other.egzaminas_), nd_(other.nd_), galutinis_(other.galutinis_) {}
	Studentas& operator=(const Studentas& other) {
		if (this == &other) return *this;  // Pats sau nepriskiria
		vardas_ = other.vardas_;
		pavarde_ = other.pavarde_;
		egzaminas_ = other.egzaminas_;
		nd_ = other.nd_;
		galutinis_ = other.galutinis_;
		return *this;
	}

	// Getteriai
	std::string vardas() const { return vardas_; }
	std::string pavarde() const { return pavarde_; }
	double egzaminas() const { return egzaminas_; }
	std::vector<double> nd() const { return nd_; }
	double galutinis() const { return galutinis_; }

	void setVardas(string vardas) {
		vardas_ = vardas;
	}
	void setPavarde(string pavarde) {
		pavarde_ = pavarde;
	}
	void setEgzaminas(double egzaminas) {
		egzaminas_ = egzaminas;
	}
	void setnd(vector<double> nd) {
		nd_ = nd;
	}
	void setGalutinis(double galutinis) {
		galutinis_ = galutinis;
	}
};

#endif //STUDENTAS_H

