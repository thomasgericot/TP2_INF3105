#include "Medicament.h"
#include <algorithm>

Medicament::Medicament(std::string nom)
    : m_nomMedicament(nom)
    , m_nombreDelots(0)
{
}


Medicament::Medicament(std::string nom, Date expiration, int quantite, Date aujourdhui)
    : m_nomMedicament(nom)
    , m_nombreDelots(0)
{
    m_lots[m_nombreDelots].expiration = expiration;
    m_lots[m_nombreDelots].quantite = quantite;
    m_lots[m_nombreDelots].testExpire(aujourdhui);

    m_nombreDelots++;
}

void Medicament::mettreEtatExpirationAJour(Date aujourdhui)
{
    for (int i = 0; i < m_nombreDelots; ++i)
    {
        m_lots[i].testExpire(aujourdhui);
    }
}

int Medicament::trouverPremierExpire()
{
    int index = -1;
    for (int i = 0; (i < m_nombreDelots) && (index == -1); ++i)
    {
        if (m_lots[i].etat == Etat::expire)
            index = i;
    }
    return index;
}

void Medicament::afficherEtatStock(bool uniquementValide)
{
    for (int i = 0; i < m_nombreDelots; ++i)
    {
        if (uniquementValide && (m_lots[i].etat == Etat::expire))
        {
            continue;
        }
        if (m_lots[i].quantite == 0)
        {
            continue;
        }

        std::cout << m_nomMedicament << " " << m_lots[i].quantite << " " << m_lots[i].expiration << std::endl;
    }
}

void Medicament::ajusterStocks(int totalDoseAEnlever, Date finTraitement)
{
    do
    {
        int lePlusProche = -1;
        int diff = 99999999;
        for (int i = 0; i < m_nombreDelots; ++i)
        {
            if (m_lots[i].etat == Etat::valide)
            {
                int n = m_lots[i].expiration - finTraitement;
                if (n < diff)
                {
                    diff = n;
                    lePlusProche = i;
                }
            }
        }

        int totalAEnleve = (int)std::min(totalDoseAEnlever, m_lots[lePlusProche].quantite);
        m_lots[lePlusProche].quantite -= totalAEnleve;
        if (m_lots[lePlusProche].quantite == 0)
            m_lots[lePlusProche].etat = Etat::vide;
        else
            m_lots[lePlusProche].etat = Etat::valide;

        totalDoseAEnlever -= totalAEnleve;
    } while (totalDoseAEnlever);
}

int Medicament::totalDosesDisponible(Date finTraitement)
{
    int totalDisponible = 0;
    for (int i = 0; i < m_nombreDelots; ++i)
    {
        if ((m_lots[i].etat == Etat::valide) && (finTraitement < m_lots[i].expiration))
        {
            totalDisponible += m_lots[i].quantite;
        }
    }
    return totalDisponible;
}

void Medicament::ajouterLot(Date expiration, int quantite, Date aujourdhui)
{
    int lotExpire = trouverPremierExpire();
    if (lotExpire != -1)
    {
        m_lots[lotExpire].expiration = expiration;
        m_lots[lotExpire].quantite = quantite;
        if (m_lots[lotExpire].quantite == 0)
            m_lots[lotExpire].etat = Etat::vide;
        else
            m_lots[lotExpire].etat = Etat::valide;
    }
    else
    {
        if (m_nombreDelots < MAX_LOTS)
        {
            m_lots[m_nombreDelots].expiration = expiration;
            m_lots[m_nombreDelots].quantite = quantite;
            if (m_lots[m_nombreDelots].quantite == 0)
                m_lots[m_nombreDelots].etat = Etat::vide;
            else
                m_lots[m_nombreDelots].etat = Etat::valide;

            m_lots[m_nombreDelots].testExpire(aujourdhui);
            m_nombreDelots++;
        }
    }
}


std::string Medicament::nom()
{
    return m_nomMedicament;
}

/*int Medicament::totalDosesDisponible2(Date finTraitement, int dose, int rep)
{

    int tab[64];
    
    int m = 0;
    for (int i = 0; i < m_nombreDelots; ++i)
    {
        if ((m_lots[i].etat == Etat::valide) && (m_lots[i].expiration - finTraitement > 0))
        {
            tab[i] = m_lots[i].expiration - finTraitement;
            
            m++;
        }
    }

    if (m!= 0)
    {

        int MIN = 0;
        int i;
        for (int i = 1; i < m; ++i)
        {
            int MIN = 0;


            if (tab[i] < tab[MIN]) MIN = i;
        }





        int o = 0;
        while (m_lots[o].expiration - finTraitement != tab[MIN])
        {
            o++;
        }
        if (m_lots[o].quantite >= dose * rep)
        {
            m_lots[o].quantite = m_lots[o].quantite - (dose * rep);
            return 1;
        }
        else
        {
            
            return 0;
        }


        


        


        return 1;

    }
    else
        return dose * rep;



}
*/
/*}
int leplusproche = m_lots[0].quantite;
for (int i = 1; i < m_nombreDelots - 1; ++i)
{
    if ((m_lots[i].etat == Etat::valide) && (finTraitement < m_lots[i].expiration))
    {
        min = min(
    }
}
*/




 /*void ::Medicament:: ajusterStocks1( int nbTotalDose, Date finTraitement,int doseTraitement)
{
    for (int i = 0; i < m_nombreDelots; i++)
    {
        if (m_lots[i].quantite = nbTotalDose)
        {
            m_lots[i].quantite = m_lots[i].quantite -doseTraitement;
        }
    }


}
*/