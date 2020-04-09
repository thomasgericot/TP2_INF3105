#if !defined(__PRESCRIPTION_H__)
#define __PRESCRIPTION_H__
#include"Medicament.h"


class prescription
{
protected:
    int NbCycles;
    int NbRepetitions;
    std::string nomMedicament;
    

public:
    
    prescription(std::string nom, int cycles, int repetitions);

};




#endif