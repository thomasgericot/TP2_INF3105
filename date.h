/*  AUTEUR(S):
    1) Nom + Code permanent du l'Útudiant.e 1
    2) Nom + Code permanent du l'Útudiant.e 2
*/

#if !defined(__DATE_H__)
#define __DATE_H__

#include <iostream>

class Date{
  public:
	Date();
	// └ complÚter
    bool operator <(const Date& date) const;
    int operator - (const Date& date)const;

  private:

  friend std::ostream& operator << (std::ostream&, const Date& date);
  friend std::istream& operator >> (std::istream&, Date& date);
};

#endif
