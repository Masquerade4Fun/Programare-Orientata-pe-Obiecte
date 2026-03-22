
/*
Pentru claritate proiectul a fost structurat in 3 fisiere. Clasele sunt definite in clase.h iar functiile de tip getter si setter sunt implementate in clase.cpp. Toate datele de test si exemplele sunt incluse in file.cpp compilarea realizandu-se cu comanda:
             g++ -o program_cadastru file.cpp clase.cpp
Programul simuleaza sistemul de gestiune al unei primarii pentru proprietati din diferite localitati. Exista o limita maxima de 10 inregistrari iar impozitul este calculat in functie de pretul pe metru patrat.
Fiecare clasa are intre 3 si 4 metode. Pentru clasa Parcela putem accesa suprafata totala numele localitatii sau putem modifica pretul. Clasa Proprietar retine datele persoanei care detine parcela si permite modificarea acestora (de exemplu actualizarea numarului de telefon).

Pentru a se combina primele doua clase ne folosim de a treia clasa SistemGestionare. Aceasta functioneaza ca un sistem centralizat ce acceseaza elementele printr-o structura de lista simplu inlantuita (nodul gestionare contine pointeri catre parcela proprietar si adresa elementului urmator).

In file.cpp este simulat fluxul de lucru al unei primarii: se creeaza sistemul se adauga parcelele impreuna cu proprietarii lor si sunt demonstrate diverse operatii de modificare a datelor existente.
*/


#include <iostream>
#include "clase.h"

int main() {
    SistemGestionare* primarie = new SistemGestionare();
    Parcela* p1 = new Parcela("Bucuresti", 500, 120, 101, 150);
    Proprietar* prop1 = new Proprietar("Ion Popescu", "1900101123456", 722111222);

    Parcela* p2 = new Parcela("Cluj-Napoca", 800, 450, 67, 210);
    Proprietar* prop2 = new Proprietar("Maria Ionescu", "2950505654321", 744333444);

    Parcela* p3 = new Parcela("Sinaia", 67, 1000, 303, 80);
    Proprietar* prop3 = new Proprietar("Vasile Gheorghita", "1800202987654", 6767667676);

    primarie->AdaugaInregistrare(p1, prop1);
    primarie->AdaugaInregistrare(p2, prop2);
    primarie->AdaugaInregistrare(p3, prop3);

    Parcela p_copie = *p1; 
    std::cout << "Copie parc. 1: " << p_copie << "\n";

    SistemGestionare primarie_copie = *primarie;
    prop1->setTelefonNou(799111222);
    prop2->setNouProprietar("Elena Vasilescu", "2901010554433", 733444555);

    std::cout << "\n\n" << *primarie <<"\n";
    int idCautat = 202;
    std::cout << "\nImpozit Parcela " << idCautat << ": " << primarie->CalculImpozit(idCautat) << " lei\n";
    std::cout << "Cea mai mare parcela: " << primarie->getgasesteCeaMaiMareParcela() << " mp\n";



    delete primarie;
    delete p1; delete p2; delete p3;
    delete prop1; delete prop2; delete prop3;

    return 0;
}