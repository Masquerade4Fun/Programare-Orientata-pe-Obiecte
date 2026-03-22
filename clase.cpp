#include "clase.h"
#include <iostream>
#include <cstring>


Parcela::Parcela(char* nume_adresa, int val, int suprafata, int idCadastra, int pret){
    this->localitate= new char[strlen(nume_adresa)+1];
    strcpy(this->localitate,nume_adresa);
    this->ValoareImpozitare=val;
    this->suprafataTotala=suprafata;
    this->idCadastral=idCadastra;
    this->pret_permetru_patrat=pret;
}

int Parcela::CalculImpozit() const {
    float zona = 1.0;
    if (this->pret_permetru_patrat > 100) zona = 1.2;  //zicem ca este ca la bogati
    else if (this->pret_permetru_patrat < 20) zona = 0.8; //ca la mine acasa 
    
    return (int)((this->suprafataTotala * this->pret_permetru_patrat) * zona);
}

Parcela::Parcela(const Parcela& altul) {
    this->localitate = new char[strlen(altul.localitate) + 1];
    strcpy(this->localitate, altul.localitate);
    this->ValoareImpozitare = altul.ValoareImpozitare;
    this->suprafataTotala = altul.suprafataTotala;
    this->idCadastral = altul.idCadastral;
    this->pret_permetru_patrat = altul.pret_permetru_patrat;
}

Parcela& Parcela::operator=(const Parcela& altul) {
    if (this != &altul) {
        delete[] this->localitate; 
        this->localitate = new char[strlen(altul.localitate) + 1];
        strcpy(this->localitate, altul.localitate);
        this->ValoareImpozitare = altul.ValoareImpozitare;
        this->suprafataTotala = altul.suprafataTotala;
        this->idCadastral = altul.idCadastral;
        this->pret_permetru_patrat = altul.pret_permetru_patrat;
    }
    return *this;
}
void Parcela::getTeren()const{
    std::cout<<"Localitatea unde se afla terenu este:"<<this->localitate<<"cu ID:"<<this->idCadastral;
}

void Parcela::setNouPret(const int nou_pretPerMetru){
    this->pret_permetru_patrat=nou_pretPerMetru;
}

std::ostream& operator<<(std::ostream& out, const Parcela& p) {
    out << "Localitatea: " << (p.localitate ? p.localitate : "Necunoscuta")
        << " cu Valoare impozit: " << p.ValoareImpozitare 
        << " cu Suprafata: " << p.suprafataTotala 
        << " cu Id: " << p.idCadastral 
        << " si in final cu pret/mp: " << p.pret_permetru_patrat;
    return out; 
}


Parcela::~Parcela(){
    delete[] this->localitate;
    std::cout<<"Memoria dinamica a fost scoasa din heap"<<std::endl;
};


Proprietar::Proprietar(char* nume_proprietar, char* pus_cnp, int telefon_proprietar){
    this->nume = new char[strlen(nume_proprietar) + 1];
    strcpy(this->nume, nume_proprietar);
    this->cnp = new char[strlen(pus_cnp) + 1]; 
    strcpy(this->cnp, pus_cnp); 
    
    this->numar_telefon = telefon_proprietar;
}

char* Proprietar::getNumeProprietar() const{
    return this->nume;
}

void Proprietar::setTelefonNou(int numar_nou){
    this->numar_telefon=numar_nou;
}

void Proprietar::setNouProprietar(const char* new_proprietar, const char* new_cnp, int telefon_nou){
    delete[] this->nume;
    delete[] this->cnp;
    this->nume=new char[strlen(new_proprietar)+1];
    strcpy(this->nume,new_proprietar);
    this->cnp=new char[strlen(new_cnp)+1];
    strcpy(this->cnp,new_cnp);
    this->numar_telefon=telefon_nou;
}


std::ostream& operator<<(std::ostream& out, const Proprietar& p){
    out << "Proprietaru are numele: " << p.nume
        << " cu CNP: " << p.cnp 
        << " si poate fi sunat la: " << p.numar_telefon ;
    return out; 
}
int Parcela::getId()const{
    return this->idCadastral;
}
Proprietar::Proprietar(const Proprietar& altul) {
    this->nume = new char[strlen(altul.nume) + 1];
    strcpy(this->nume, altul.nume);
    this->cnp = new char[strlen(altul.cnp) + 1];
    strcpy(this->cnp, altul.cnp);
    this->numar_telefon = altul.numar_telefon;
}

Proprietar& Proprietar::operator=(const Proprietar& altul) {
    if (this != &altul) {
        delete[] this->nume;
        delete[] this->cnp;
        this->nume = new char[strlen(altul.nume) + 1];
        strcpy(this->nume, altul.nume);
        this->cnp = new char[strlen(altul.cnp) + 1];
        strcpy(this->cnp, altul.cnp);
        this->numar_telefon = altul.numar_telefon;
    }
    return *this;
}



Proprietar::~Proprietar(){
    delete[] this->nume;
    delete[] this->cnp;
}

SistemGestionare::SistemGestionare(){
    this->nrCurent=0;
    this->capacitate=10;
    this->sistem_struct=nullptr;
}

void SistemGestionare::AdaugaInregistrare(Parcela* p, Proprietar* pr) {
    if(this->nrCurent>=capacitate){
        std::cout<<"Nu mai putem adauga alte parcele limita a fost atinsa!";
        return;
    }
    gestionare* nod = new gestionare;
    nod->parcela = p;
    nod->proprietar_curent = pr;
    nod->urmatorul = this->sistem_struct;
    this->sistem_struct = nod;
    this->nrCurent++;
}

int SistemGestionare::CalculImpozit(int id_cautat) const {
    gestionare* curent = this->sistem_struct;
    if (curent == nullptr) {
        return 0;
    }
    while (curent != nullptr) {
        if (curent->parcela->getId() == id_cautat) {
            return curent->parcela->CalculImpozit();
        }
        curent = curent->urmatorul;
    }
    return 0; 
}

int SistemGestionare::getgasesteCeaMaiMareParcela()const{
    gestionare* tmp = this->sistem_struct;
    if (tmp == nullptr) {
        return 0;
    }
    int maxim=0;
    while(tmp!=nullptr){
        int val=tmp->parcela->getSuprafata();
        if(val>maxim){
            maxim=val;
        }
        tmp = tmp->urmatorul;
    }
    return maxim;
}

std::ostream& operator<<(std::ostream& out, const SistemGestionare& sist) {
    SistemGestionare::gestionare* tmp = sist.sistem_struct;
    if (tmp == nullptr) {
        out << "Sistemu este gol.Incearca sa adaugi elemente prim metoda buna." << std::endl;
        return out;
    }
    while (tmp != nullptr) {
        out << "Inregistrare:" << std::endl;
        out << "  " << *(tmp->parcela) << std::endl;
        out << "  " << *(tmp->proprietar_curent) << std::endl;
        out << "" << std::endl;
        tmp = tmp->urmatorul; 
    }
    return out;
}

SistemGestionare::~SistemGestionare() {
    gestionare* curent = this->sistem_struct;
    while (curent != nullptr) {
        gestionare* deSters = curent;
        curent = curent->urmatorul;
        delete deSters;
    }
    std::cout << "Sistemul a fost sters din memorie.\n";
}


SistemGestionare::SistemGestionare(const SistemGestionare& altul) {
    this->sistem_struct = nullptr;
    this->nrCurent = 0;
    this->capacitate = altul.capacitate;
    gestionare* temp = altul.sistem_struct;
    while (temp != nullptr) {
        this->AdaugaInregistrare(temp->parcela, temp->proprietar_curent);
        temp = temp->urmatorul;
    }
}

SistemGestionare& SistemGestionare::operator=(const SistemGestionare& altul) {
    if (this != &altul) {
        gestionare* curent = this->sistem_struct;
        while (curent != nullptr) {
            gestionare* deSters = curent;
            curent = curent->urmatorul;
            delete deSters;
        }
        this->sistem_struct = nullptr;
        this->nrCurent = 0;

        gestionare* temp = altul.sistem_struct;
        while (temp != nullptr) {
            this->AdaugaInregistrare(temp->parcela, temp->proprietar_curent);
            temp = temp->urmatorul;
        }
    }
    return *this;
}