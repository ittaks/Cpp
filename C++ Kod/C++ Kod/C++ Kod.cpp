#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

//  1)Neka postoji klasa Mobitel koja predstavlja prosirenje klase MobilniUredjaj. (2 boda)
//    Napisite funkciju najviseMemorije koja za zadani niz mobilnih uredjaja vraca najvecu memoriju
class MobilniUredjaj {
public:

    string marka;
    int gp;
    int km;
    MobilniUredjaj() {}
    MobilniUredjaj(string _marka, int _gp, int _km) :marka(_marka), gp(_gp), km(_km) {}
    ~MobilniUredjaj() {};
};

class Mobitel : public MobilniUredjaj {
public:

    Mobitel(string marka, int gp, int km) :MobilniUredjaj(marka, gp, km) {}
    ~Mobitel() {};
};

int najviseMemorije(vector<MobilniUredjaj*>uredjaj) {
    MobilniUredjaj* mob;
    int p = 0;

    for (int i = 0; i < uredjaj.size(); i++) {
        mob = uredjaj[i];
        if (mob->km > p) {
            p = mob->km;

        }
    }
    return p;
}


int prvi()
{
    MobilniUredjaj u1("Samsung Galaxy S10", 2017, 16);
    MobilniUredjaj u2("Samsung Galaxy S20", 2018, 32);
    MobilniUredjaj u3("Samsung Galaxy S30", 2019, 64);
    MobilniUredjaj u4("Samsung Galaxy S40", 2020, 128);

    Mobitel m1("Samsung Galaxy", 2017, 256);
    Mobitel m2("Huavwei X5", 2019, 64);
    vector<MobilniUredjaj*> uredjaji = { &u1, &u2, &u3, &u4, &m1, &m2 };

    cout << najviseMemorije(uredjaji) << endl; //16
    return 0;
}



// 2) Napišite predložak funkcije Najduži koja vraæa najduži niz od dva predana( 1 bod)
//    Proširite navedeni predložak tako da može raditi s neogranièenim brojem predanih argumenata. Funkcija Najduži prilikom 
//    usporeðivanja mora imati minimalno 2 argumenta (3 boda)

template<class T, class T2>
string Najduzi(T a, T2 b) {

    if (a.size() > b.size()) {
        return a;
    }
    else {
        return b;
    }
}

template<class T, class T2, class... T3>
string Najduzi(T a, T2 b, T3... argument) {
    if (a.size() > Najduzi(b, argument...).size()) {
        return a;
    }
    else {
        return Najduzi(b, argument...);
    }


    / return a.size() > Najduzi(b, argument) ? a.size() : Najduzi(b.size(), argument...); /
}

string Najduzi(string a, string b) { //vraca najduzi od DVA predana
    if (a.size() > b.size()) {
        return a;
    }
    else {
        return b;
    }
}

int drugi() {
    string s1 = "abcde";
    string s2 = "abc";
    string s3 = "abcdefghijk";
    string s4 = "bcdef";
    cout << Najduzi(s1, s2) << endl;  // abcde
    cout << Najduzi(s1, s3) << endl;  // abcdefghijk
    cout << Najduzi(s1, s2, s3, s4) << endl; // abcdefghijk

    return 0;
}




//3)	Neka postoje klase Knjiga i Polica.Klasa Knjiga sadrži podatke o naslovu, godini izdanja i ISBN broju, dok klasa Polica sadrži niz knjiga.
//    Deklarirajte navedene klase, te dodajte sve potrebne podatkovne èlanove i metode da se programski kod u nastavku može izvršavati kao što 
//    je predviðeno(4 boda).
class Knjiga {
public:
    string naslov;
    int g;
    long long ISBN;
    Knjiga(string n, int a, long long b) :naslov(n), g(a), ISBN(b) {}


};

class Polica {
public:
    vector<Knjiga>k;

    Polica& operator +=(vector<Knjiga>k) {
        vector<Knjiga>tmp = { k };
        for (int i = 0; i < tmp.size(); i++) {
            this->k.push_back(tmp[i]);
        }
        return *this;

    }
    friend ostream& operator << (ostream& izlaz, Polica d);


};
ostream& operator << (ostream& izlaz, Polica d) {
    for (int i = 0; i < d.k.size(); i++) {
        izlaz << d.k[i].naslov << ", " << d.k[i].g << ", " << d.k[i].ISBN << endl;
    }
    return izlaz;
}
int treci() {

    Knjiga knjiga1("Pripovjetke", 1970, 1234567890);
    Knjiga knjiga2("Ljeto", 1984, 1234512345);
    Knjiga knjiga3("Zima", 1940, 7890654321);

    Polica polica;
    polica += {knjiga1, knjiga2, knjiga3};
    cout << polica << endl;
    return 0;
}

/*Ispisuje:
Pripovjetke, 1970, 1234567890
Ljeto, 1984, 1234512345
Zima, 1940, 7890654321
*/
//}



//4)	Napišite funkciju getKnjige koja kao argument prima objekt tipa Polica i godinu izdanja, a vraæa novi objekt tipa Polica koji u sebi sadrži samo 
//    knjige koje su izdane nakon te godine.Tijelo funkcije getKnjige potrebno je implementirati unutar funkcije main!Demonstrirajte njen poziv. (3 boda)
Polica getKnjige(Polica p, int g) {
    Polica novaPolica;
    for (int i = 0; i < p.k.size(); i++) {
        if (p.k[i].g == g) {
            novaPolica += {p.k[i]};
        }
    }
    return novaPolica;

}
int cetvrti() {
    Knjiga knjiga1("Pripovjetke", 1940, 1234567890);
    Knjiga knjiga2("Ljeto", 1984, 1234512345);
    Knjiga knjiga3("Zima", 1940, 7890654321);

    Polica polica;
    polica += {knjiga1, knjiga2, knjiga3};

    Polica novaPolica;
    novaPolica = getKnjige(polica, 1940);
    cout << novaPolica << endl;
    return 0;
}
//5)	Napišite predložak klase Knjizara koja sadrži niz knjiga jednog žanra(primjerice Komedija ili Drama).Konstruktor navedene klase može primiti 0 ili 
//    više(neogranièeno) knjiga istog tipa(3 boda), a njena metoda "ispis" u zasebnom retku treba ispisati svaku knjigu koja se nalazi u toj knjizari. (1 bod).
//    Metodu ispis implementirajte van klase. (1 bod) 

template <class U>
class Knjizara {
public:
    vector<U>knjige;

    Knjizara() {}
    template <class T>
    Knjizara(T n) {
        knjige.push_back(n);
    }
    template <class T, class... T2>
    Knjizara(T n, T2... rest) {
        knjige.push_back(n);
        X(rest...);
    }

    void ispis() {
        for (int i = 0; i < knjige.size(); i++) {
            cout << knjige[i] << endl;
        }
    }

};



class Drama : Knjiga {
public:
    Drama(string n, int a, long long b) :Knjiga(n, a, b) {}

};

class Komedija : Knjiga {
public:
    Komedija(string n, int a, long long b) :Knjiga(n, a, b) {}
};



int peti() {

    Drama drama1("Ljeto", 1984, 1234512345);
    Drama drama2("Zima", 1940, 7890654321);

    Knjizara<Drama> drame(drama1, drama2);
    drame.ispis();
    // Ljeto, 1984, 1234512345
    // Zima, 1940, 7890654321

    Komedija komedija1("Pripovjetke", 1940, 1234567890);
    Komedija komedija2("Pripovjetke2", 1940, 1234567890);
    Komedija komedija3("Pripovjetke3", 1940, 1234567890);

    Knjizara<Komedija> komedije(komedija1);
    komedije.ispis();



    Knjizara<Komedija> komedije2(komedija2, komedija3);
    komedije2.ispis();
}

int main() {

    //prvi(); 
    //drugi(); 
    //treci(); 
    //cetvrti(); 
    //peti();
}