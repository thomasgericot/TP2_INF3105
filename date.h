/*
    GERICOT thomas
    Gericot + GERT10089801
*/

#if !defined(__DATE_H__)
#define __DATE_H__

#include <iostream>

class Date
{
public:
    Date();
    Date(int a, int m, int j);

    // À compléter
    bool operator <(const Date& date) const;
    int operator - (const Date& date)const;

    Date operator + (const int& jours)const;

    void regler(int a, int m, int j);

    int getAnnee();
    int getMois();
    int getJour();

private:

    friend std::ostream& operator << (std::ostream&, const Date& date);
    friend std::istream& operator >> (std::istream&, Date& date);


protected:

    int annee;
    int mois;
    int jour;

};

#endif
