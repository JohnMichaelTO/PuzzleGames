#include <iostream>
#include <ctime>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include "liste.h"
#include "pile.h"
#include "listeD.h"
#include "configParser.h"
#include "ClassListAStar.h"
#include "IA.h"
#include "jeu.h"

using namespace std;

int main()
{
    srand(time(NULL));

    string url;
    ClassConfigParser fichier;
    ClassPile pile;
    ClassListeSimple pFinal, pCourant;
    LSC **plateau, EtatFinal, EtatCourant;

    double ponderationHeuristique;

    int reponse;

    cout << "------------------------------------\n-- Generer un guide de resolution --\n------------------------------------\n\n";

    do
    {
        cout << "Charger un fichier : ";
        cin >> url;

        if(fichier.Charger(url))
        {
            pile.Get(fichier.RetournerPile());
            EtatFinal = fichier.RetournerEtatFinal();
            pFinal.Get(EtatFinal);
            pCourant.Get(pile.RetournerLSC());
            EtatCourant = pCourant.Retourner();

            int Longueur(fichier.RetournerLongueur()), Hauteur(fichier.RetournerHauteur());
            plateau = pCourant.CopierVersTab(Longueur, Hauteur);

            cout << "Longueur : " << Longueur << "\nHauteur : " << Hauteur << endl << endl;

            cout << "Etat Initial/Courant\n" << endl;
            pCourant.AfficherTab(Longueur);
            cout << endl;

            cout << "Etat Final\n" << endl;
            pFinal.AfficherTab(Longueur);
            cout << endl;

            do
            {
                cout << "Ponderation de l'heuristique (par defaut : >= 1.00) : ";
                cin >> ponderationHeuristique;
                cin.clear();
                cin.ignore(numeric_limits<double>::max(), '\n');
            } while(ponderationHeuristique < 1.00);

            cout << "\n------------------- Start IA -------------------\n\n";

            fichier.GetPile(ResoudreParAStar(EtatFinal, EtatCourant, fichier.RetournerListePiecesUtilisees(), Longueur, Hauteur, ponderationHeuristique));

            cout << "------------------- End IA -------------------\n\n";

            do
            {
                url = "";
                cout << "Chemin de sauvegarde du guide de resolution genere : ";
                cin >> url;
                cin.clear();
            } while(url == "");

            if(fichier.Sauvegarder(url, true))
            {
                cout << "\nLa sauvegarde a ete effectuee avec succes.\nChemin de la sauvegarde : " << url << endl;
            }
            else
            {
                cout << "\nUne erreur est survenue lors de la sauvegarde du guide de resolution" << endl;
            }
            fichier.Decharger();
        }
        else
        {
            cerr << "Erreur dans le fichier de configuration" << endl;
        }

        cout << "Voulez-vous charger un nouveau fichier ? (1 = oui/0 = non) : ";
        cin >> reponse;
        cin.clear();
        cin.ignore(numeric_limits<int>::max(), '\n');
        cout << "\n\n-------------------------------------------------------------\n\n";
    } while(reponse == 1);

    return 0;
}
