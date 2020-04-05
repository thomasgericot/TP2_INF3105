#include "Medicament.h"

Medicament::Medicament(std::string nom)
    : nomMedicament(nom)
{
}


Medicament::Medicament(std::string nom,Date expiration)
    : nomMedicament(nom)
    , dateExpiration(expiration)
{
}

Etat    Medicament::testExpire(Date d)
{
    return (d < dateExpiration) ? Etat::valide : Etat::expire;
}

std::string Medicament::nom()
{
    return nomMedicament;
}