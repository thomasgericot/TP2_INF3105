#if !defined(__MEDICAMENT_H__)
#define __MEDICAMENT_H__


#include <iostream>
#include <string>
#include "date.h"

enum class Etat
{
    valide,
    expire,
    vide
};

struct Lot
{
    int quantite = 0;
    Etat etat = Etat::vide;
    Date expiration;

    Etat    testExpire(Date d)
    {
        etat = (d < expiration) ? etat : Etat::expire;
        return etat;
    }
};

static const int MAX_LOTS = 32;

class Medicament
{
protected:         
    std::string m_nomMedicament;
    Lot m_lots[MAX_LOTS];
    int m_nombreDelots;

public:    
    Medicament(std::string nom);
    Medicament(std::string nom,Date d,int quantite, Date aujourdhui=Date());

    void afficherEtatStock(bool uniquementValide);        
    int trouverPremierExpire();
    void ajouterLot(Date expiration, int quantite, Date aujourdhui);
   
    void ajusterStocks(int totalDoseAEnlever, Date finTraitement);
    void ajusterStocks1(int totalDoseAEnlever, Date finTraitement);
    int totalDosesDisponible(Date finTraitement);

    void mettreEtatExpirationAJour(Date aujourdhui);
    int totalDosesDisponible2(Date finTraitement , int dose, int cycle);
    std::string nom();
    
};

#endif
