/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#if !defined(__STOCK_H__)
#define __STOCK_H__

#include <iostream>

#include "Medicament.h"

// noeud de arbre de medicament
struct MedicamentNoeud
{
    int nbMedicament;
    Medicament* medicaments;

    MedicamentNoeud* parent;
    MedicamentNoeud* gauche;
    MedicamentNoeud* droite;
};

class Stock
{
protected:
    // arbre de medicament
    MedicamentNoeud* stockMedicament;

  public:
	Stock& operator+=(const Stock& autre);

    // ajoute des medicaments avec nom, quantite, expiration

    // 

    // nombre de medicaments en fonction du nom et date

    // nombre de medicaments en fonction du nom
    
    // tableau des medicaments valide entre aujourdhui et une date

  private:

  friend std::ostream& operator << (std::ostream&, Stock&);
};

#endif

