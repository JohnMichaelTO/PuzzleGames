#include <iostream>
#include "liste.h"

// Constructeur
ClassListeSimple::ClassListeSimple()
{
    Initialiser();
}

// Destructeur
ClassListeSimple::~ClassListeSimple()
{
    // Vider();
}

// Initialisation
void ClassListeSimple::Initialiser()
{
    liste = NULL;
}

// Récupération
void ClassListeSimple::Get(LSC p)
{
    liste = p;
}

// Retourner
LSC ClassListeSimple::Retourner()
{
    return liste;
}

// Retourner la longueur de la liste
int ClassListeSimple::RetournerLongueur()
{
    int i(0);
    LSC p;
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

// Recherche d'un élément dans la LSC
bool ClassListeSimple::Rechercher(char e)
{
    LSC p;
    if(liste == NULL) return false;
    else
    {
        p = liste;
        while(p != NULL)
        {
            if(p->info == e) return true;
            p = p->succ;
        }
    }
    return false;
}

// Création d'une LSC
void ClassListeSimple::Creer(char e)
{
    Cellule *maillon;

    maillon = new Cellule;
    maillon->info = e;
    maillon->succ = NULL;
    liste = maillon;
}

// Création d'une LSC
void ClassListeSimple::Creer(LSC *listeT, char e)
{
    Cellule *maillon;

    maillon = new Cellule;
    maillon->info = e;
    maillon->succ = NULL;
    *listeT = maillon;
}

// Affichage d'une LSC
void ClassListeSimple::Afficher()
{
    LSC p;
    if(liste == NULL)
        std::cout << "LA LISTE EST VIDE \n\n";
    else
    {
        p = liste;
        while(p != NULL)
        {
            std::cout << p->info << " -> ";
            p = p->succ;
        }
        std::cout << "NULL\n\n";
    }
}

// Affichage d'une LSC sous forme de tableau
void ClassListeSimple::AfficherTab(int longueur)
{
    LSC p;
    int i(0);
    if(liste != NULL)
    {
        p = liste;
        while(p != NULL)
        {
            std::cout << p->info;
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
void ClassListeSimple::InsererTete(LSC liste2)
{
    LSC p;
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
    }
    return;
}

// Insertion en queue de liste
void ClassListeSimple::InsererQueue(LSC liste2)
{
    LSC p;
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
    }
    return;
}

// Insertion en queue de liste
void ClassListeSimple::InsererQueue(LSC *liste1, LSC liste2)
{
    LSC p;
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
    }
    return;
}

// Supprimer la tête de liste
void ClassListeSimple::SupprimerTete()
{
    LSC p;
    p = liste;
    liste = liste->succ;
    delete p;
    p = NULL;
}

// Supprimer la queue de liste
void ClassListeSimple::SupprimerQueue()
{
    LSC cour, prec;
    prec = liste;
    cour = liste->succ;
    while(cour->succ != NULL)
    {
        cour = cour->succ;
        prec = prec->succ;
    }
    delete cour;
    prec->succ = NULL;
}

// Vider
void ClassListeSimple::Vider()
{
    while(liste != NULL)
    {
        SupprimerTete();
    }
}

// Permuter le contenu de deux éléments
void ClassListeSimple::Permuter(LSC e1, LSC e2)
{
    char temp;
    temp = e1->info;
    e1->info = e2->info;
    e2->info = temp;
}

// Créer un tableau d'adresse à 2 dimensions à partir d'une LSC
LSC** ClassListeSimple::CopierVersTab(int Longueur, int Hauteur)
{
    int i, x(0), y(0);
    LSC **p(NULL), Temp(NULL);

    if(liste != NULL)
    {
        // Réservation
        p = new LSC*[Longueur];
        for(i = 0; i < Longueur; i++)
        {
            p[i] = new LSC[Hauteur];
        }

        // Initialisation : Copiage des adresses de la LSC principale
        Temp = liste;
        while(Temp != NULL)
        {
            p[x][y] = Temp;
            Temp = Temp->succ;
            x++;
            if(x % Longueur == 0)
            {
                x = 0;
                y++;
            }
        }
    }
    return p;
}

// Copier et retourner une nouvelle LSC
LSC ClassListeSimple::CopierLSC()
{
    LSC p(NULL), liste2(NULL), listeTemp;
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
