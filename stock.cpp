/*  Gericot
Gericot thomas
*/


#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include "stock.h"

#include "medicament.h"

Medicament* avl_tree::trouverMedicament(std::string NomMedicament)
{
    MedicamentNoeud* noeud = trouverNomMedicament(m_root, NomMedicament);
    return noeud ? noeud->medicaments : NULL;
}


void avl_tree::insererMedicament(std::string nom, int quantite, Date expiration)
{
    m_root = inserer(m_root, nom, quantite, expiration);
}

void avl_tree::mettreAjourEtat(Date aujourdhui)
{
    m_aujourdhui = aujourdhui;
    mettreAjourEtat_inorder(m_root);
}

void avl_tree::afficherMedicamentsValide()
{
    afficherMedicamentsValide_inorder(m_root);
}

void avl_tree::afficherMedicamentsValide_inorder(MedicamentNoeud* t)
{
    if (t == NULL)
        return;
    afficherMedicamentsValide_inorder(t->gauche);

    if (t->medicaments)
    {
        t->medicaments->afficherEtatStock();
    }

    afficherMedicamentsValide_inorder(t->droite);
}

void avl_tree::mettreAjourEtat_inorder(MedicamentNoeud* t)
{
    if (t == NULL)
        return;
    mettreAjourEtat_inorder(t->gauche);

    if(t->medicaments)
        t->medicaments->mettreEtatMedicament(m_aujourdhui);

    mettreAjourEtat_inorder(t->droite);
}


int avl_tree::height(MedicamentNoeud* t)
{
    int h = 0;
    if (t != NULL)
    {
        int l_height = height(t->gauche);
        int r_height = height(t->droite);
        int max_height = std::max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
int avl_tree::difference(MedicamentNoeud* t)
{
    int l_height = height(t->gauche);
    int r_height = height(t->droite);
    int b_factor = l_height - r_height;
    return b_factor;
}
MedicamentNoeud* avl_tree::rr_rotat(MedicamentNoeud* parent)
{
    MedicamentNoeud* t;
    t = parent->droite;
    parent->droite = t->gauche;
    t->gauche = parent;
    return t;
}
MedicamentNoeud* avl_tree::ll_rotat(MedicamentNoeud* parent)
{
    MedicamentNoeud* t;
    t = parent->gauche;
    parent->gauche = t->droite;
    t->droite = parent;    
    return t;
}
MedicamentNoeud* avl_tree::lr_rotat(MedicamentNoeud* parent)
{
    MedicamentNoeud* t;
    t = parent->gauche;
    parent->gauche = rr_rotat(t);
    return ll_rotat(parent);
}
MedicamentNoeud* avl_tree::rl_rotat(MedicamentNoeud* parent)
{
    MedicamentNoeud* t;
    t = parent->droite;
    parent->droite = ll_rotat(t);    
    return rr_rotat(parent);
}

MedicamentNoeud* avl_tree::inserer(MedicamentNoeud* r, std::string v, int quantite, Date expiration)
{
    if (r == NULL)
    {
        r = new MedicamentNoeud;
        r->medicaments = new Medicament(v);
        r->medicaments->ajouterLot(expiration, quantite,Date());
        r->gauche = NULL;
        r->droite = NULL;
        return r;
    }
    else if (v < r->medicaments->nom())
    {
        r->gauche = inserer(r->gauche, v, quantite, expiration);
        r = balance(r);
    }
    else if (v >= r->medicaments->nom())
    {
        r->droite = inserer(r->droite, v, quantite, expiration);
        r = balance(r);
    } 
    return r;
}

MedicamentNoeud* avl_tree::balance(MedicamentNoeud* t)
{
    int bal_factor = difference(t);
    if (bal_factor > 1)
    {
        if (difference(t->gauche) > 0)
            t = ll_rotat(t);
        else
            t = lr_rotat(t);
    }
    else if (bal_factor < -1)
    {
        if (difference(t->droite) > 0)
            t = rl_rotat(t);
        else
            t = rr_rotat(t);
    }
    return t;
}

MedicamentNoeud* avl_tree::trouverNomMedicament(MedicamentNoeud* t, std::string NomMedicament)
{
    if (t)
    {
        if (NomMedicament > t->medicaments->nom())
        {
            return trouverNomMedicament(t->droite, NomMedicament);
        }
        if (NomMedicament < t->medicaments->nom())
        {
            return trouverNomMedicament(t->gauche, NomMedicament);
        }
        if (NomMedicament == t->medicaments->nom())
        {
            return t;
        }
    }
    return NULL;
}

avl_tree& avl_tree::operator+=(const avl_tree& autre)
{
    // À compléter.
    return *this;
}



std::ostream& operator << (std::ostream& os, avl_tree& stock){

	return os;
}
