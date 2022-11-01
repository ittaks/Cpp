#include<iostream>
#include<vector>
#include<algorithm>

/*
Podatci o knjižnici sadrže naziv, adresu i popis ssadržanih knjiga, dok svaka knjiga ima naziv, autora i ISBN.
a)implementirajte klase Knjižnica i Knjige te njihove konstruktore koji trebaju inicijalizirati sve opisane
  podatkovne člaove osim popisa sadržanih knjiga(3 BODA)
b)Implementirajte konstruktor klase Knjižnica koji osim naziva i adrese može rimiti i spremiti neograničen broj knjiga. Implementaciju
  konstruktora potrebno je napisati van klase. (3 BODA)
C)U funkciji main kreirajte knjižnicu s barem 2 knjige, te preopterećenjem operatora << za tu knjižnicu ispišite sve sadržane knjige
  (svaku u svom retku) sortirane po ISBN-u( od veće vrijednosti prema manjoj( 4 BODA) Ukoliko se prilikom sortiranja za usporedbu podataka koristi
  lambda funkcija dobije se dodatan bod(1 BOD)
d)Prilikom definiranja ISBN-a knjige potrebno je demonstrirati enkapsulaciju na nacin da novi ISBN mora imati tocno 13 znamenki.
 Uprotivnom je potrebno baciti iznimku tipka IznimkaISBN koja metodom Ispis ispisuje odgovarajuću poruku korisniku.
  Uopisu poruke mora se nalaziti podatak o pogrešnom broju znamenaka. (3 BODA). Također, u opisu pouke potrebno je ispisati i redni broj generiran iznimke
  koji je u pošetku jednak null, a generiranjem svake nove iznimke ovog tipa povećava se za 1. Primjer prvog ispisa:
  "Iznimka 1 : 10 je pogresan broj znamenaka ISBN-a!" Demonstrirati u funkciji main.*/

  //d)Prilikom definiranja ISBN - a knjige potrebno je demonstrirati enkapsulaciju na nacin da novi ISBN mora imati tocno 13 znamenki.
  //Uprotivnom je potrebno baciti iznimku tipa IznimkaISBN koja metodom Ispis ispisuje odgovarajuću poruku korisniku.
  //Uopisu poruke mora se nalaziti podatak o pogrešnom broju znamenaka. (3 BODA).Također, u opisu pouke potrebno je ispisati i redni broj generiran iznimke
  //koji je u pošetku jednak null, a generiranjem svake nove iznimke ovog tipa povećava se za 1. Primjer prvog ispisa :
  //"Iznimka 1 : 10 JE POGREŠAN BROJ ZNAMENAKA ISBN-a!" Demonstrirati u funkciji main.

using namespace std;
class IznimkaISBN {
public:
	static int br;
	string naziv;
	IznimkaISBN(string a) : naziv(a) { br++; }
	void ispis() {
		cout << "Iznimka " << br << ": " << naziv.length() << " je pogresan broj znamenaka!" << endl;
	}
};
int IznimkaISBN::br = 0;
class Knjiga {
private:
public:
	string naziv, autor, isbn;
	Knjiga() {}
	Knjiga(string a, string b, string c) : naziv(a), autor(b), isbn(c) {}
	void setIsbn(string a) {
		try {
			if (a.length() != 13) {
				throw (IznimkaISBN(a));
			}
			naziv = a;
		}
		catch (IznimkaISBN a) {
			a.ispis();
		}
	}
};
class Knjiznica {
private:
public:
	string naziv, adresa;
	vector<Knjiga> knjige;
	Knjiznica(string a, string b) : naziv(a), adresa(b) {}
	template<class... Knjiga>
	Knjiznica(Knjiga... a);
	friend ostream& operator << (ostream& izlaz, Knjiznica a);
	virtual double getCijena() {
		return 0;
	}
};
template<class... Knjiga>
Knjiznica::Knjiznica(Knjiga... a) : knjige({ a... }) {}
class Stacionarna : public Knjiznica {
public:
	double cijena = 30;
	Stacionarna(string a, string b) : Knjiznica(a, b) {}
	double getCijena() {
		return cijena;
	}
};
class Mobilna : public Knjiznica {
public:
	double cijena = 50;
	Mobilna(string a, string b) : Knjiznica(a, b) {}
	double getCijena() {
		return cijena;
	}
};
double CijenaUkupno(const vector<Knjiznica*>& knjiznica) {
	double rez = 0;
	for (int i = 0; i < knjiznica.size(); i++) {
		rez += knjiznica[i]->getCijena();
	}
	return rez;
}
ostream& operator << (ostream& izlaz, Knjiznica a) {
	sort(a.knjige.begin(), a.knjige.end(), [](Knjiga a, Knjiga b)->bool
		{return a.isbn > b.isbn; });
	for (int i = 0; i < a.knjige.size(); i++) {
		izlaz << a.knjige[i].naziv << " " << a.knjige[i].autor << " " <<
			a.knjige[i].isbn << endl;
	}
	return izlaz;
}
class Muzej {
public:
	vector<Knjiga*> knjige;
	Muzej() {}
	Muzej(Muzej&& a) {
		for (int i = 0; i < a.knjige.size(); i++) {
			knjige.push_back(a.knjige[i]);
			a.knjige[i] = NULL;
		}
	}
	Muzej& operator = (const Muzej& a) {
		if (this != &a) {
			for (int i = 0; i < knjige.size(); i++) {
				delete knjige[i];
			}
			knjige.clear();
			for (int i = 0; i < a.knjige.size(); i++) {
				knjige.push_back(new Knjiga);
				*knjige[i] = *a.knjige[i];
			}
		}
		return *this;
	}
	~Muzej() {
		for (int i = 0; i < knjige.size(); i++) {
			delete knjige[i];
		}
		knjige.clear();
	}
};
int main() {
	Knjiznica a(Knjiga("a", "a", "123"), Knjiga("b", "b", "456"));
	cout << a;
	Knjiga pr1, pr2, pr3;
	pr1.setIsbn("12345");
	pr2.setIsbn("1234567890123");
	pr3.setIsbn("541644454");
	vector<Knjiznica*> knjiznica;
	Mobilna jedan("jedan", "ilica 123");
	Stacionarna dva("dva", "karlovacka 6753");
	knjiznica.push_back(&jedan);
	knjiznica.push_back(&dva);
	cout << CijenaUkupno(knjiznica) << endl;
	return 0;
}
