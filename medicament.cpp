#include "medicament.h"
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

void Medicament::mettreEtatMedicament(Date aujourdhui)
{
    for (int i = 0; i < m_nombreDelots; ++i)
    {
        m_lots[i].etat = m_lots[i].quantite != 0 ? Etat::valide : Etat::vide;

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

void Medicament::afficherEtatStock()
{
    for (int i = 0; i < m_nombreDelots; ++i)
    {
        if (m_lots[i].etat == Etat::valide)
        {
            std::cout << m_nomMedicament << " " << m_lots[i].quantite << " " << m_lots[i].expiration << std::endl;
        }
    }
}

void Medicament::ajusterStocks(int index,int totalDoseAEnlever)
{
    if (index >= 0 && index < m_nombreDelots)
    {
        m_lots[index].quantite -= totalDoseAEnlever;
        if (m_lots[index].quantite == 0)
            m_lots[index].etat = Etat::vide;
        else
            m_lots[index].etat = Etat::valide;
    }
}

bool Medicament::trouveLotPourPrescription(int totalDoseTraitement,Date finTraitement)
{
    bool ok = false;
    int indexDuPlusProche = -1;
    Date expirationProche(2050,12,31);
    for (int i = 0; i < m_nombreDelots; ++i)
    {
        if ((m_lots[i].etat == Etat::valide) && (finTraitement < m_lots[i].expiration) && (totalDoseTraitement <= m_lots[i].quantite))
        {
            if ( (m_lots[i].expiration) < (expirationProche))
            {
                expirationProche = m_lots[i].expiration;
                indexDuPlusProche = i;
            }
        }
    }
    if (indexDuPlusProche != -1)
    {
        ok = true;
        ajusterStocks(indexDuPlusProche, totalDoseTraitement);
    }
    return ok;
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
