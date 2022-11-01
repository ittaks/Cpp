#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;

/* Z1
Napišite predložak funkcije "NeparniElementi" koji prima vektor podataka
bilo kojeg tipa, a vraæa samo neparne elemente tog vektora.
*/

template <class T>
vector<T> NeparniElementi(vector<T> vektor) {
	vector<T> pomocni;
	for (int i = 0; i < vektor.size(); i++) {
		if (vektor[i] % 2 != 0)
			pomocni.push_back(vektor[i]);
	}
	return pomocni;
}

void zadatak1() {
	vector<int> vektor = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	vector<int> neparni = NeparniElementi(vektor);
	for (int i = 0; i < neparni.size(); i++) {
		cout << neparni[i] << " ";
	}

}

/* Z2
Potrebno je nadopunit donji programski odsjecak na nacin da napisete funkciju
"izdvoji", za koju vrijedi sljedece:

vraca vector<int> (novi vektor)
prvi argument: vector<int>&
drugi argument: funkcija

Funkcija izdvojiti mora iz vektora "brojevi" izdvojiti samo one koji nisu
djeljivi sa 2, 3 ili 5. Drugi argumenti funkcije potrebno je poslati kao
lambda izraz(nadopuniti)

*/
vector<int> izdvoji(vector<int>& vektor, function<bool(int)> lambda) {
	vector<int> pom;
	for (int i = 0; i < vektor.size(); i++) {
		if (lambda(vektor[i]) == true)
			pom.push_back(vektor[i]);
	}
	return pom;
}

void zadatak2() {
	vector<int> brojevi = { 1,4,5,7,3,6,12,65,32,8,87,55,23,22,1,1,433,66,7,433,3,32,76,8,72,256,42 };
	vector<int> rez = izdvoji(brojevi, [](int n) {
		if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0)
			return false;
		return (true);
		});
	for (int i = 0; i < rez.size(); i++) {
		cout << rez[i] << " ";

		//ispis: 1 7 23 1 1 433 7 433
	}
}

/* Z3
Napisite predlozak klase Red koja ima mogucnost dodavanja novog elementa na kraj
reda metodom Dodaj, te uklanjanja zadnje elementa u redu metodom Brisi.
Navedena klasa takoder mora imati podatklovni clan BrojElemenata koji vraca
trenutni broj elemenata u nizu
*/

template <class T>
class Red {
private:
	vector<T> lista;
public:
	int BrojElemenata;
	Red& Dodaj(T parametar) {
		lista.push_back(parametar);
		BrojElemenata++;
		return *this;
	}
	Red& Brisi() {
		lista.pop_back();
		BrojElemenata--;
		return *this;
	}
	void brEl() {
		cout << BrojElemenata << endl;
	}
};
void zadatak3() {
	Red<string> red;
	red.Dodaj("kokos").Dodaj("banana").Dodaj("jabka").Dodaj("kivi");
	red.brEl();

	red.Brisi().Brisi();
	red.brEl();
}

/* Z4
Napisite lambda funkciju koja ce izracunati broj brojeva u vektoru koji su u
zadanom intervalu (veci ili jednako od low, manji ili jednako od high). Vektor
se prenosi u lambda funkciju preko parametara funkcije, dok se rezultat (brInterval)
prenosi preko reference u klauzuli hvatanja. Varijable low i high se prenose preko
vrijednosti u klauzuli hvatanja.
*/

void zadatak4() {
	vector<int> brojevi = { 1,4,5,7,3,6,12,65,32,8,87,55,23,22,1,1,433,66,7,433,3,32,76,8,72,256,42 };

	int brInterval = 0;
	int low, high;

	cin >> low >> high; //primjerice 10, 100

	[&brInterval, low, high](vector<int> v) {
		for (size_t i : v)
			if (i >= low && i <= high)
				brInterval++;
	}(brojevi);

	cout << brInterval << endl; //12
}

/* Z5
Napisite program za pretrazivanje studenata tako da radi kako je ispod prikazano.
*/

class Student {
public:
	string ime1, prezime1, jmbag1;
	Student(string i, string p, string j) {
		ime1 = i;
		prezime1 = p;
		jmbag1 = j;
	};
	Student() {};
	string ime() {
		return ime1;
	}
	string prezime() {
		return prezime1;
	}
	string jmbag() {
		return jmbag1;
	}
};

vector<Student*> nadji(vector<Student>& v, function<bool(Student*)> usporedba) {
	vector<Student*> pom;
	for (int i = 0; i < v.size(); i++)
		if (usporedba(&v[i]) == true) {
			pom.push_back(&v[i]);
		}
	return pom;
};

void zadatak5() {
	vector<Student> v = { Student("Pero", "Peric", "3882"),
	Student("Ivo", "Ivic", "10991"),
	Student("Mara", "Maric", "40991"),
	Student("Ivan", "Juric", "93877"),
	Student("Ivo", "Kalic", "20991"),
	};
	//nadi sve studente koji se zovu ivo
	vector<Student*> r = nadji(v, [](Student* s) {return s->ime() == "Ivo"; });
	//ispisuje Ivo Ivic 10991 i Ivo Kalic 20991
	for (Student* s : r) {
		cout << s->ime() << " " << s->prezime() << " " << s->jmbag() << endl;
	}
}

int main()
{
	cout << "ZADATAK 1" << endl;
	zadatak1();
	cout << endl << "ZADATAK 2" << endl;
	zadatak2();
	cout << endl << "ZADATAK 3" << endl;
	zadatak3();
	cout << "ZADATAK 4" << endl;
	zadatak4();
	cout << "ZADATAK 5" << endl;
	zadatak5();
}
