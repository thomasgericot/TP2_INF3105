/*
  INF3105 - Structures de données et algorithmes
  Hiver 2020.
  TP2
*/
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <limits>
#include "date.h"
#include "stock.h"

using namespace std;

struct CommandeMedicament
{
    std::string nom;
    int quantite;
};
     
struct Commande
{
    Date dateDeCommande;
    CommandeMedicament* medicaments=NULL;
    int nbMedicaments=0;
};


void afficherCommandeEnCours(Commande& commande)
{
    std::cout << commande.dateDeCommande << " COMMANDES:" << std::endl;
    for (int i = 0; i < commande.nbMedicaments; ++i)
    {
        std::cout << commande.medicaments[i].nom << " " << commande.medicaments[i].quantite << std::endl;
    }
}

int trouverMedicamentDansCommande(Commande& commande, std::string nom)
{
    int index = -1;
    for (int i = 0; (i < commande.nbMedicaments) && (index==-1); ++i)
    {
        if (commande.medicaments[i].nom == nom)
        {
            index = i;
        }
    }
    return index;
}

void ajouterACommandeEnCours(Commande& commande, std::string nom, int quantite, Date dateCommande)
{
    int index = trouverMedicamentDansCommande(commande, nom);
    if (index >= 0)
    {
        // medicament deja en commande, ajuste la quantite
        commande.medicaments[index].quantite += quantite;
    }
    else
    {
        CommandeMedicament* copyTemp = NULL;
        if (commande.nbMedicaments)
        {
            copyTemp = new CommandeMedicament[commande.nbMedicaments];
            for (int i = 0; i < commande.nbMedicaments; ++i)
            {
                copyTemp[i].quantite = commande.medicaments[i].quantite;
                copyTemp[i].nom = commande.medicaments[i].nom;
            }
        }
        else
        {
            commande.dateDeCommande = dateCommande;
        }

        if (commande.medicaments)
            delete[] commande.medicaments;
        commande.medicaments = new CommandeMedicament[commande.nbMedicaments + 1];
        for (int i = 0; i < commande.nbMedicaments; ++i)
        {
            commande.medicaments[i].quantite = copyTemp[i].quantite;
            commande.medicaments[i].nom = copyTemp[i].nom;
        }
        commande.medicaments[commande.nbMedicaments].quantite = quantite;
        commande.medicaments[commande.nbMedicaments].nom = nom;
        commande.nbMedicaments++;

        if (copyTemp)
            delete[] copyTemp;
        copyTemp = NULL;
    }
}

int tp2(istream& entree)
{
    Commande commandeEnCours;
    Date maintenant;
    avl_tree stock(maintenant);


    while (entree)
    {
        string typecommande;
        entree >> typecommande;
        if (!entree) break; // détection fin ==> sortie

        if (typecommande == "PRESCRIPTION")
        {
            std::cout << "PRESCRIPTION" << std::endl;
            char deuxpoints = 0;
            entree >> deuxpoints;
            assert(deuxpoints == ':');
            string nomMed;
            entree >> nomMed;
            while (entree && nomMed != ";")
            {
                int dose=0;
                int rep=0;
                entree >> dose >> rep;
                int nbTotalDose = dose * rep;
                int totalCycle = nbTotalDose;
                
                // sortie
                std::cout << nomMed << " " << dose << " " << rep;

                bool commander = true;
                Medicament* medicament = stock.trouverMedicament(nomMed);
                if (medicament)
                {  
                    Date finTraitement = maintenant + totalCycle;
                    int totalDosesDisponible = medicament->totalDosesDisponible(finTraitement);
                    /*/int totalDosesDisponible = medicament->totalDosesDisponible2(finTraitement, dose, rep);
                    if (totalDosesDisponible == 1)
                    {
                        std::cout << "OK" << std::endl;
                    }
                    else
                    {
                        std::cout << "COMMANDE" << std::endl;
                        ajouterACommandeEnCours(commandeEnCours, nomMed, nbTotalDose, maintenant);
                    }
                    */
                    if (nbTotalDose < totalDosesDisponible)
                    {
                        commander = false;
                        medicament->ajusterStocks( nbTotalDose,  finTraitement);
                        

                        


                        std::cout<< " OK" << std::endl;
                    }
                    
                    
                        
                    
                        

                
                }                
                
                if(commander)
                {
                    std::cout << " COMMANDE" << std::endl;
                    ajouterACommandeEnCours(commandeEnCours, nomMed, nbTotalDose, maintenant);
                }
                entree >> nomMed;
                
            }
        }
        else if (typecommande == "APPROV")
        {
            string nomMed;
            char deuxpoints = 0;
            entree >> deuxpoints;
            assert(deuxpoints == ':');
            entree >> nomMed;
            while (entree && nomMed != ";")
            {
                int quantite=0;
                Date dateexpiration;
                entree >> quantite >> dateexpiration;
                
                // inserer le medicament
                stock.insererMedicament(nomMed, quantite, dateexpiration);

                entree >> nomMed;
            }            
            cout << "APPROV OK";
        }
        else if (typecommande == "STOCK")
        {
            char pointvirgule = 0;
            entree >> pointvirgule;
            assert(pointvirgule == ';');
            
            cout << "STOCK "<<maintenant<<std::endl;
            stock.afficherMedicamentsValide();
        }
        else if (typecommande == "DATE")
        {
            char pointvirgule = 0;
            entree >> maintenant >> pointvirgule;
            assert(pointvirgule == ';');

            stock.mettreAjourEtat(maintenant); // actualise l'etat des medicaments
            if (commandeEnCours.nbMedicaments == 0)
            {
                std::cout << maintenant << " OK" << std::endl;
            }
            else
            {
                afficherCommandeEnCours(commandeEnCours);
            }
        }
        else
        {
            cout << "Transaction '" << typecommande << "' invalide!" << endl;
            return 2;
        }
        cout << endl;
        entree >> ws; // force la lecture d'un espace blanc.
    }
    return 0;
}
// syntaxe d'appel : ./tp2 [nomfichier.txt]
int main(int argc, const char** argv)
{
    // Gestion de l'entrée :
    //  - lecture depuis un fichier si un argument est spécifié;
    //  - sinon, lecture depuis std::cin.
    if (argc > 1)
    {
        std::ifstream entree_fichier(argv[1]);
        if (entree_fichier.fail())
        {
            std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
            return 1;
        }
        return tp2(entree_fichier);
    }
    else
        return tp2(std::cin);

    return 0;
}




