#include <iostream>
#include <ctime>
#include "liste.h"
#include "pile.h"
#include "listeD.h"
#include "ClassListAStar.h"
#include "IA.h"
#include "jeu.h"

// Heuristique 1 : Calcule et retourne le nombre de plaquettes mal placées
int Heuristique(LSC lFinal, LSC lCours)
{
    int nb(0);
    LSC EtatFinal, EtatCourant;
    ClassListeSimple action, actionTemp;

    if(lFinal != NULL && lCours != NULL)
    {
        action.Initialiser();
        actionTemp.Initialiser();

        EtatFinal = lFinal;
        EtatCourant = lCours;
        while(EtatCourant != NULL)
        {
            if(EtatCourant->info != '#' && EtatCourant->info != '.' && EtatCourant->info != 'X')
            {
                if(!action.Rechercher(EtatCourant->info))
                {
                    if(EtatCourant->info != EtatFinal->info)
                    {
                        nb = nb + 1;
                        actionTemp.Creer(EtatCourant->info);
                        action.InsererQueue(actionTemp.Retourner());
                        actionTemp.Initialiser();
                    }
                }
            }
            EtatFinal = EtatFinal->succ;
            EtatCourant = EtatCourant->succ;
        }
        action.Vider();
    }
    return nb;
}

// Heuristique 2 : Calcule et retourne la distance de Manhattan + optimisation avec une pondération de l'heuristique
int Heuristique2(LSC lFinal, LSC lCours, LSC ListePieces, int Longueur, int Hauteur, double ponderationHeuristique = 1.)
{
    LSC Pieces, **PlateauFinal, **PlateauCourant;
    ClassListeSimple action;
    int x, y, xD(0), yD(0), xA(0), yA(0), distanceFinale(0);
    bool depart(false), arrivee(false);

    if(lFinal != NULL && ListePieces != NULL && lCours != NULL)
    {
        action.Get(lFinal);
        PlateauFinal = action.CopierVersTab(Longueur, Hauteur);

        action.Get(lCours);
        PlateauCourant = action.CopierVersTab(Longueur, Hauteur);

        Pieces = ListePieces;

        while(Pieces != NULL)
        {
            depart = false;
            arrivee = false;

            for(y = 0; y < Hauteur; y++)
            {
                for(x = 0; x < Longueur; x++)
                {
                    if(!depart && PlateauCourant[x][y]->info == Pieces->info)
                    {
                        xD = x;
                        yD = y;
                        depart = true;
                    }

                    if(!arrivee && PlateauFinal[x][y]->info == Pieces->info)
                    {
                        xA = x;
                        yA = y;
                        arrivee = true;
                    }
                }
            }

            if(depart && arrivee)
            {
                distanceFinale += ValeurAbsolue(xA - xD) + ValeurAbsolue(yA - yD);
            }
            Pieces = Pieces->succ;
        }
    }
    return ponderationHeuristique * distanceFinale;
}

// Génération d'une liste AStar contenant les noeuds successeurs
ListeAStar GenererSuccesseurs(LSC EtatFinal, ListeAStar ListeFermee, LSC ListePieces, int Longueur, int Hauteur, t_noeud *prec, double ponderationHeuristique = 1.)
{
    ClassListAStar action, actionTemp, actionListeFermee;
    int x, y;
    LSC gauche, droite, haut, bas, EtatCourant;
    ClassListeSimple actionListe;
    t_noeud *temp;
    EtatCourant = prec->plateau;

    action.Initialiser(); // Initialisation de la liste
    actionListeFermee.Get(ListeFermee);

    /**********************************************************************************/
    for(y = 0; y < Hauteur; y++)
    {
        for(x = 0; x < Longueur; x++)
        {
            gauche = GenererDeplacement(EtatCourant, Longueur, Hauteur, x, y, 'g');
            if(gauche != NULL)
            {
                temp = RemplirNoeud(EtatFinal, gauche, prec, ListePieces, Longueur, Hauteur, ponderationHeuristique);
                if(CompareListeAStar(action.Retourner(), temp) && CompareListeAStar(actionListeFermee.Retourner(), temp)) // On ajoute un noeud que si un même état n'est pas présente dans la liste
                {
                    actionTemp.Creer(temp);
                    action.InsertionTriee(actionTemp.Retourner());
                }
            }

            droite = GenererDeplacement(EtatCourant, Longueur, Hauteur, x, y, 'd');
            if(droite != NULL)
            {
                temp = RemplirNoeud(EtatFinal, droite, prec, ListePieces, Longueur, Hauteur, ponderationHeuristique);
                if(CompareListeAStar(action.Retourner(), temp) && CompareListeAStar(actionListeFermee.Retourner(), temp)) // On ajoute un noeud que si un même état n'est pas présente dans la liste
                {
                    actionTemp.Creer(temp);
                    action.InsertionTriee(actionTemp.Retourner());
                }
            }

            haut = GenererDeplacement(EtatCourant, Longueur, Hauteur, x, y, 'h');
            if(haut != NULL)
            {
                temp = RemplirNoeud(EtatFinal, haut, prec, ListePieces, Longueur, Hauteur, ponderationHeuristique);
                if(CompareListeAStar(action.Retourner(), temp) && CompareListeAStar(actionListeFermee.Retourner(), temp)) // On ajoute un noeud que si un même état n'est pas présente dans la liste
                {
                    actionTemp.Creer(temp);
                    action.InsertionTriee(actionTemp.Retourner());
                }
            }

            bas = GenererDeplacement(EtatCourant, Longueur, Hauteur, x, y, 'b');
            if(bas != NULL)
            {
                temp = RemplirNoeud(EtatFinal, bas, prec, ListePieces, Longueur, Hauteur, ponderationHeuristique);
                if(CompareListeAStar(action.Retourner(), temp) && CompareListeAStar(actionListeFermee.Retourner(), temp)) // On ajoute un noeud que si un même état n'est pas présente dans la liste
                {
                    actionTemp.Creer(temp);
                    action.InsertionTriee(actionTemp.Retourner());
                }
            }
        }
    }
    return action.Retourner();
    /**********************************************************************************/
}

// Génération d'un déplacement (gauche, droite, haut, bas) : Retourne NULL si un déplacement n'est pas possible, sinon retourne l'adresse d'une LSC
LSC GenererDeplacement(LSC liste, int Longueur, int Hauteur, int x, int y, char type)
{
    ClassListeSimple pCourant;
    LSC **Plateau, EtatCourant(NULL);
    LSCD depart(NULL), arrivee(NULL);

    pCourant.Get(liste);
    pCourant.Get(pCourant.CopierLSC());
    Plateau = pCourant.CopierVersTab(Longueur, Hauteur);

    if(VerifPiece(Plateau, x, y))
    {
        depart = CreerListeDepart(Plateau, Longueur, Hauteur, x, y);

        switch(type)
        {
            case 'g':
                arrivee = CreerListeArrivee(Plateau, Longueur, Hauteur, x - 1, y, depart, false);
                break;
            case 'd':
                arrivee = CreerListeArrivee(Plateau, Longueur, Hauteur, x + 1, y, depart, false);
                break;
            case 'h':
                arrivee = CreerListeArrivee(Plateau, Longueur, Hauteur, x, y - 1, depart, false);
                break;
            case 'b':
                arrivee = CreerListeArrivee(Plateau, Longueur, Hauteur, x, y + 1, depart, false);
                break;
        }

        EtatCourant = PermuterDeuxLSCD(pCourant.Retourner(), Longueur, Hauteur, depart, arrivee);

        return EtatCourant;
    }
    else
    {
        pCourant.Vider();
        return NULL;
    }
}

// Remplir un noeud
t_noeud* RemplirNoeud(LSC EtatFinal, LSC EtatCourant, t_noeud *parent, LSC ListePieces, int Longueur, int Hauteur, double ponderationHeuristique = 1.)
{
    t_noeud *racine = ReserverNoeud();

    racine->parent = parent;
    racine->plateau = EtatCourant;
    racine->h = Heuristique2(EtatFinal, EtatCourant, ListePieces, Longueur, Hauteur, ponderationHeuristique);
    racine->g = parent->g + 1;
    racine->f = racine->g + racine->h;

    return racine;
}

// Compare un noeud
bool CompareNoeud(t_noeud *noeud1, t_noeud *noeud2)
{
    // La fonction VerifFinPartie() permet de comparer deux LSC
    if(VerifFinPartie(noeud1->plateau, noeud2->plateau)) return true;
    return false;
}

// Compare une ListeAStar avec un noeud
bool CompareListeAStar(ListeAStar liste, t_noeud *noeudCompare)
{
    ListeAStar p;

    if(liste != NULL)
    {
        p = liste;
        while(p != NULL)
        {
            if(CompareNoeud(p->info, noeudCompare)) return false;
            p = p->succ;
        }
    }
    return true;
}

// Réservation d'un noeud
t_noeud* ReserverNoeud()
{
    t_noeud *NouveauNoeud;
    NouveauNoeud = new t_noeud;
    NouveauNoeud->parent = NULL;
    NouveauNoeud->plateau = NULL;
    NouveauNoeud->f = 0;
    NouveauNoeud->g = 0;
    NouveauNoeud->h = 0;

    return NouveauNoeud;
}

// Suppression d'un noeud
void SupprimerNoeud(t_noeud *NoeudDelete)
{
    delete NoeudDelete;
    NoeudDelete = NULL;
}

// Résolution par l'algorithme A* modifiée
t_pile ResoudreParAStar(LSC EtatFinal, LSC EtatCourant, LSC ListePiecesUtilisees, int Longueur, int Hauteur, double ponderationHeuristique = 1.)
{
    ClassListAStar action, ListeFermee, ListeOuverte, actionTemp;
    t_noeud *MeilleurNoeud = ReserverNoeud();
    bool CompareOK(false);
    int i(0);

    // Pile pour contenir le chemin de résolution
    ClassPile pile;
    pile.Initialiser();

    clock_t start = clock();
    {
        MeilleurNoeud->parent = NULL;
        MeilleurNoeud->plateau = EtatCourant;
        MeilleurNoeud->g = 0;
        MeilleurNoeud->h = Heuristique2(EtatFinal, EtatCourant, ListePiecesUtilisees, Longueur, Hauteur, ponderationHeuristique);
        MeilleurNoeud->f = MeilleurNoeud->g + MeilleurNoeud->h;

        ListeFermee.Creer(MeilleurNoeud);

        action.Get(GenererSuccesseurs(EtatFinal, ListeFermee.Retourner(), ListePiecesUtilisees, Longueur, Hauteur, MeilleurNoeud, ponderationHeuristique));
        ListeOuverte.Initialiser();
        ListeOuverte.InsererTete(action.Retourner());

        while(!CompareOK && ListeOuverte.Retourner() != NULL)
        {
            MeilleurNoeud = ListeOuverte.RetournerMeilleurNoeud();
            CompareOK = VerifFinPartie(EtatFinal, MeilleurNoeud->plateau);

            actionTemp.Creer(MeilleurNoeud);
            ListeFermee.InsererTete(actionTemp.Retourner());
            action.Get(GenererSuccesseurs(EtatFinal, ListeFermee.Retourner(), ListePiecesUtilisees, Longueur, Hauteur, MeilleurNoeud, ponderationHeuristique));
            ListeOuverte.InsertionTriee(action.Retourner());
            i++;
        }

        if(CompareOK)
        {
            std::cout << "\nSolution OK\n";
            std::cout << "\nNombre de mouvements : " << MeilleurNoeud->g << "\n";
            std::cout << "\nNombre d'iterations : " << i << "\n";
        }
        else std::cout << "\nSolution non trouvee\n";
    }
    clock_t end = clock();
    clock_t duree = end - start;

    std::cout << "\nDuree : " << duree * 1.0 / CLOCKS_PER_SEC << " seconde(s).\n";

    // Empilement du chemin de résolution
    while(MeilleurNoeud != NULL)
    {
        pile.Empiler(MeilleurNoeud->plateau);
        MeilleurNoeud = MeilleurNoeud->parent;
    }

    // Libération
    SupprimerNoeud(MeilleurNoeud);
    ListeOuverte.Vider();
    ListeFermee.Vider();
    return pile.Retourner();
}
