#include <iostream>
using namespace std;

class Partito {
protected:
    string nome;
    string sigla;
    string presidente;

public:
    Partito(string nome, string sigla, string presidente) : nome(nome), sigla(sigla), presidente(presidente) {}

    Partito() {
        nome = "";
        sigla = "";
        presidente = "";
    }

    bool operator==(const Partito& other) const {
        return this->nome == other.nome && this->sigla == other.sigla && this->presidente == other.presidente;

    }

    string getSigla() const {
        return sigla;
    }
};

class PartitoDiSinistra : public Partito {
private:
    double voti;
public:
    PartitoDiSinistra(string nome, string sigla, string presidente, double voti) : Partito(nome,sigla,presidente), voti(voti) {}
};

class PartitoDiCentro : public Partito {
private:
    double voti;
public:
    PartitoDiCentro(string nome, string sigla, string presidente, double voti) : Partito(nome,sigla,presidente), voti(voti) {}
};

class PartitoDiDestra : public Partito {
private:
    double voti;
public:
    PartitoDiDestra(string nome, string sigla, string presidente, double voti) : Partito(nome, sigla, presidente), voti(voti) {}
};

class Parlamentare {
private:
    string nome;
    string cognome;
    Partito partito;
public:
    Parlamentare(string nome, string cognome, Partito partito) : partito(partito), nome(nome), cognome(cognome) {}

    void visualizzaDettagli(ostream& dest) {
        dest << "Nome: " << nome << endl << "Cognome: " << cognome << endl << "Sigla del partito: " << partito.getSigla() << endl;
    }

    bool operator==(const Parlamentare& other) const {
        return this->nome == other.nome && this->cognome == other.cognome && this->partito.getSigla() == other.partito.getSigla();
    }

     Partito getPartito() const {
        return partito;
    }

    Parlamentare() {
        nome = "";
        cognome = "";
        partito.getSigla() = "";
    }
};

class Parlamento {
private:
    Parlamentare* parlamentare;
    int size;

    bool contains(const Parlamentare& p) const {
        for(int i = 0; i < size; i++)
            if (p == parlamentare[i])
                return true;
        return false;
    }
public:
    Parlamento() {
        size = 0;
        parlamentare = new Parlamentare[0];
    }

    ~Parlamento() {
        delete[] parlamentare;
    }

    Parlamento(const Parlamento& other) {
        this->size = other.size;
        this->parlamentare = new Parlamentare[size];
        for (int i = 0; i < size; i++)
            this->parlamentare[i] = other.parlamentare[i];
    }

    Parlamento operator=(const Parlamento& other) {
        if (this != &other) {
            size = other.size;
            Parlamentare *new_array = new Parlamentare[size];
            for (int i = 0; i < size; i++)
                new_array[i] = other.parlamentare[i];
            delete[] this->parlamentare;
            this->parlamentare = new_array;
            return *this;
        }
    }

        void aggiungiParlamentare(const Parlamentare& p) {
            if (!contains(p)) {
                Parlamentare *new_array = new Parlamentare[size + 1];
                for (int i = 0; i < size; i++)
                    new_array[i] = this->parlamentare[i];
                delete[] parlamentare;
                this->parlamentare = new_array;
                this->parlamentare[size] = p;
                size++;
            }
        }

            void vissualizaParlamento(ostream &dest) const {
                for (int i = 0; i < size; i++)
                    this->parlamentare[i].Parlamentare::visualizzaDettagli(dest);
            }

            void vissualizaParlamentariDi(ostream& dest, const Partito& elem) const {
        dest << "Parlamentari sigla: " << elem.getSigla() << endl;
        for (int i = 0; i < size; i++)
            if (this->parlamentare[i].getPartito() == elem) {
                this->parlamentare[i].Parlamentare::visualizzaDettagli(dest);
            }
    }
};

int main() {
    Partito p1 = {"Unity", "UNT", "Barack Obama"};
    PartitoDiDestra p2 = {"Brotherhood", "BHD", "James Walker", 56.234};
    PartitoDiCentro p3 = {"Family", "FAM", "Vin Diesel", 65.251};
    PartitoDiSinistra p4 = {"For the best", "FTB", "John Crown", 48.595};

    Parlamentare p5 = {"Jeniffer", "Brown", p2};
    Parlamentare p6 = {"Marcus", "Kingston", p3};
    Parlamentare p7 = {"Chris", "Smith", p4};
    Parlamentare p8 = {"Arthur", "Morgan", p4};

    p5.visualizzaDettagli(cout);
    p6.visualizzaDettagli(cout);
    p7.visualizzaDettagli(cout);

    cout << endl;

    Parlamento p9;
    p9.aggiungiParlamentare(p5);
    p9.aggiungiParlamentare(p6);
    p9.aggiungiParlamentare(p7);
    p9.aggiungiParlamentare(p8);

    cout << endl;

    p9.vissualizaParlamento(cout);
    cout << endl;
    p9.vissualizaParlamentariDi(cout, p4);

    return 0;
}
