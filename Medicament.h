#if !defined(__MEDICAMENT_H__)
#define __MEDICAMENT_H__


#include <iostream>
#include <string>

#include "date.h"

enum Etat
{
    valide,
    expire
};

class Medicament
{
protected:
    Date    dateExpiration;
    std::string nomMedicament;
public:
    Medicament(std::string nom);
    Medicament(std::string,Date);

    Etat    testExpire(Date d);

    std::string nom();
};

#endif
