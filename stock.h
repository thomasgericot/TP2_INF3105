/*  GERICOT
Thomas Gericot GERT10089801
*/

#if !defined(__STOCK_H__)
#define __STOCK_H__

#include <iostream>
#include<algorithm>
#include "medicament.h"


// noeud d'arbre de medicament


struct MedicamentNoeud{
    
    
    Medicament* medicaments=NULL;
    
    
    MedicamentNoeud* gauche=NULL;
    MedicamentNoeud* droite=NULL;
   // MedicamentNoeud* inserer(MedicamentNoeud* t, std::string nom);
    //MedicamentNoeud* AjoutStock(MedicamentNoeud* t, std::string medicament);
};


class avl_tree
{
public:
    avl_tree(Date aujourdhui)
        : m_aujourdhui(aujourdhui)
    {
        m_root = nullptr;
    }

    ~avl_tree()
    {
        if (m_root)
            delete m_root;
        m_root = nullptr;
    }

    void insererMedicament(std::string nom, int quantite, Date expiration);
    void afficherMedicamentsValide();
    Medicament* trouverMedicament(std::string NomMedicament);
    void mettreAjourEtat(Date aujourdhui);

protected:
    MedicamentNoeud* balance(MedicamentNoeud*);
    int height(MedicamentNoeud*);
    int difference(MedicamentNoeud*);

    MedicamentNoeud* rr_rotat(MedicamentNoeud*);
    MedicamentNoeud* ll_rotat(MedicamentNoeud*);
    MedicamentNoeud* lr_rotat(MedicamentNoeud*);
    MedicamentNoeud* rl_rotat(MedicamentNoeud*);
    MedicamentNoeud* inserer(MedicamentNoeud* t,std::string nom, int quantite, Date expiration);
    
    void mettreAjourEtat_inorder(MedicamentNoeud* t);

    void afficherMedicamentsValide_inorder(MedicamentNoeud* t);

    //void postorder(MedicamentNoeud* t);
    
    
    MedicamentNoeud* trouverNomMedicament(MedicamentNoeud* t, std::string NomMedicament);
    
    avl_tree& operator+=(const avl_tree& autre);
    

    

protected:
    MedicamentNoeud* m_root;
    Date m_aujourdhui;
};

/*class Stock
{
protected:
    // arbre de medicament
    MedicamentNoeud* stockMedicament;

  public:
	Stock& operator+=(const Stock& autre);

     


    // ajoute des medicaments avec nom, quantite, expiration
    avl_tree AjoutStock(string medicament);
    

    // nombre de medicaments en fonction du nom et date
    int StockDisponible(string NomMedicament, Date date);
    // nombre de medicaments en fonction du nom
    int StockMedicamentNom(string NomMedicament);
    // tableau des medicaments valide entre aujourdhui et une date
    void StockAffichage(avl *t);

  private:

  friend std::ostream& operator << (std::ostream&, Stock&);
};*/

#endif

