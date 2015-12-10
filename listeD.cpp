#include <iostream>
#include "listeD.h"

// Constructeur
ClassListeDeplacement::ClassListeDeplacement()
{
    size = 0;
    Initialiser();
}

// Destructeur
ClassListeDeplacement::~ClassListeDeplacement()
{
    // Vider();
}

// Initialisation
void ClassListeDeplacement::Initialiser()
{
    liste = NULL;
}

// Récupération
void ClassListeDeplacement::Get(LSCD p)
{
    liste = p;
}

// Retourner
LSCD ClassListeDeplacement::Retourner()
{
    return liste;
}

// Retourner la longueur de la liste
int ClassListeDeplacement::RetournerLongueur()
{
    int i(0);
    LSCD p;
    if(liste == NULL) return 0;
    else
    {
        p = liste;
        while(p != NULL)
        {
            i++;
            p = p->succ;
        }
    }
    return i;
}

// Création d'une LSCD
void ClassListeDeplacement::Creer(t_coordonnees e)
{
    CelluleD *maillon;

    maillon = new CelluleD;
    maillon->info = e;
    maillon->succ = NULL;
    liste = maillon;
    size = size + 1;
}

// Création d'une LSCD
void ClassListeDeplacement::Creer(LSCD *liste2, t_coordonnees e)
{
    CelluleD *maillon;

    maillon = new CelluleD;
    maillon->info = e;
    maillon->succ = NULL;
    *liste2 = maillon;
    size = size + 1;
}

// Affichage d'une LSCD
void ClassListeDeplacement::Afficher()
{
    LSCD p;
    if(liste == NULL)
        std::cout << "LA LISTE EST VIDE \n\n";
    else
    {
        p = liste;
        while(p != NULL)
        {
            std::cout << "(" << p->info.x << ", " << p->info.y << ") -> ";
            p = p->succ;
        }
        std::cout << "NULL\n\n";
    }
}

// Affichage d'une LSCD sous forme de tableau
void ClassListeDeplacement::AfficherTab(int longueur)
{
    LSCD p;
    int i(0);
    if(liste != NULL)
    {
        p = liste;
        while(p != NULL)
        {
            std::cout << "(" << p->info.x << ", " << p->info.y << ") ";
            p = p->succ;
            i++;
            if(i % longueur == 0)
            {
                std::cout << std::endl;
            }
        }
    }
}

// Insertion en tête de liste
void ClassListeDeplacement::InsererTete(LSCD liste2)
{
    LSCD p;
    if(liste2 == NULL)
        return;
    else
    {
        p = liste2;

        while(p->succ != NULL)
        {
            p = p->succ;
        }
        p->succ = liste;
        liste = liste2;
        size = size + 1;
    }
    return;
}

// Insertion en queue de liste
void ClassListeDeplacement::InsererQueue(LSCD liste2)
{
    LSCD p;
    if(liste == NULL)
    {
        liste = liste2;
    }
    else
    {
        p = liste;

        while(p->succ != NULL)
        {
            p = p->succ;
        }
        p->succ = liste2;
        size = size + 1;
    }
    return;
}

// Insertion en queue de liste
void ClassListeDeplacement::InsererQueue(LSCD *liste1, LSCD liste2)
{
    LSCD p;
    if(*liste1 == NULL)
    {
        *liste1 = liste2;
    }
    else
    {
        p = *liste1;

        while(p->succ != NULL)
        {
            p = p->succ;
        }
        p->succ = liste2;
        size = size + 1;
    }
    return;
}

// Supprimer la tête de liste
void ClassListeDeplacement::SupprimerTete()
{
    LSCD p;
    p = liste;
    liste = liste->succ;
    delete p;
    p = NULL;
    size = size - 1;
}

// Vider
void ClassListeDeplacement::Vider()
{
    while(liste != NULL)
    {
        SupprimerTete();
    }
    size = 0;
}

// Copier et retourner une nouvelle LSCD
LSCD ClassListeDeplacement::CopierLSCD()
{
    LSCD p(NULL), liste2(NULL), listeTemp;
    if(liste == NULL)
        return NULL;
    else
    {
        p = liste;
        Creer(&liste2, p->info);
        p = p->succ;
        while(p != NULL)
        {
            Creer(&listeTemp, p->info);
            InsererQueue(&liste2, listeTemp);
            p = p->succ;
        }
        return liste2;
    }
}
