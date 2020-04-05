/*  
     GERICOT thomas
     Gericot + GERT10089801
*/
#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>
#include <ctime>

//Date sans argument: initialise une date avec les données de la date actuelle
Date::Date()
{
	time_t now = time(0);
	tm* dt = localtime(&now);
	annee = 1900 + dt->tm_year;
	mois = 1+dt->tm_mon;
	jour = dt->tm_mday;
}

Date::Date(int a, int m, int j)
    : annee(a)
    , mois(m)
    , jour(j)
{
}

void Date::regler(int a, int m, int j)
{
    annee = a;
    mois = m;
    jour = j;
}

int Date::getAnnee()
{
    return annee;
}
int Date::getMois()
{
    return mois;
}
int Date::getJour()
{
    return jour;
}

bool Date::operator <(const Date& d) const
{
    return ((*this)-d)<0;
}

int Date::operator - (const Date& date) const
{
    //Date -> tm -> time_t
    tm temp;
    temp.tm_hour = 0;
    temp.tm_min = 0;
    temp.tm_sec = 0;
    temp.tm_year = this->annee - 1900;
    temp.tm_mon = this->mois - 1;
    temp.tm_mday = this->jour;
    time_t moi_meme = mktime(&temp);

    temp.tm_hour = 0;
    temp.tm_min = 0;
    temp.tm_sec = 0;
    temp.tm_year = date.annee - 1900;
    temp.tm_mon = date.mois - 1;
    temp.tm_mday = date.jour;
    time_t date_time = mktime(&temp);

    double nbSecondes = difftime(moi_meme,date_time);
	return (int)(nbSecondes/ (3600.0 * 24.0));
}
std::ostream& operator << (std::ostream& os, const Date& d){
    int a=d.annee, m=d.mois, j=d.jour;
    char chaine[40] = { 0 };
    sprintf(chaine, "%04d-%02d-%02d", a, m, j);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    int a=0, m=0, j=0;
    char t1=0,t2=0;
    is >> a >> t1 >> m >> t2 >> j;
    assert(t1=='-');
    assert(t2=='-');
    /*
    d.annee = a >= 1900 ? a : d.annee;
    d.mois = (1<=m) && (m<=12) ? m : d.mois;
    d.jour = (1 <= j) && (j <= 31) ? j : d.jour;
    */

    d.annee =  a;
    d.mois =  m;
    d.jour =  j;
    return is;
}



