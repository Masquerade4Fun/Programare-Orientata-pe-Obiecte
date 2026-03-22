#include <iostream>
class Parcela {
    char* localitate;
    int ValoareImpozitare;
    int suprafataTotala;
    int idCadastral;
    int pret_permetru_patrat;

public:
    Parcela(const Parcela& altul); 
    Parcela& operator=(const Parcela& altul); 
    Parcela(char* localitate, int val, int suprafata, int idCadastral,int pret);
    ~Parcela(); 
    int CalculImpozit()const;
    void getTeren() const;
    int getId()const;
    void setNouPret(const int nou_pretPerMetru);
    inline int getSuprafata() const { return this->suprafataTotala; }
    friend std::ostream& operator<<(std::ostream& out, const Parcela& p);   
};

class Proprietar {
    char* nume;
    char* cnp;
    int numar_telefon;

public:
    Proprietar(const Proprietar& altul);
    Proprietar& operator=(const Proprietar& altul);
    Proprietar(char* nume_proprietar, char* pus_cnp, int telefon_proprietar);
    ~Proprietar(); 
    char* getNumeProprietar() const;
    void setTelefonNou(int numar_nou);
    void setNouProprietar(const char* new_proprietar, const char* new_cnp, int telefon_nou);
    friend std::ostream& operator<<(std::ostream& out, const Proprietar& p);
};

class SistemGestionare {
    struct gestionare {
        Parcela* parcela;
        Proprietar* proprietar_curent; 
        gestionare* urmatorul;
    };

    gestionare* sistem_struct; //ptr pentru structura(inspirat din liste simpl)
    int nrCurent;
    int capacitate;

public:
    SistemGestionare(const SistemGestionare& altul);
    SistemGestionare& operator=(const SistemGestionare& altul);
    SistemGestionare();
    ~SistemGestionare();
    void AdaugaInregistrare(Parcela* p, Proprietar* pr);
    int CalculImpozit(int id_cautat) const;
    int getgasesteCeaMaiMareParcela() const;
    friend std::ostream& operator<<(std::ostream& out, const SistemGestionare& sist);

};

