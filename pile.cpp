#include <iostream>
#include "liste.h"
#include "pile.h"

// Constructeur
ClassPile::ClassPile()
{
    Initialiser();
}

// Destructeur
ClassPile::~ClassPile()
{

}

// Récupération d'une pile
void ClassPile::Get(t_pile pile)
{
    p = pile;
    p.hauteur = pile.hauteur;
}

// Retourner une pile
t_pile ClassPile::Retourner()
{
    return p;
}

// Retourner la hauteur de la pile
unsigned ClassPile::RetournerHauteur()
{
    return p.hauteur;
}

// Initialisation d'une pile
void ClassPile::Initialiser()
{
    p.sommet = NULL;
    p.hauteur = 0;
}

// Test d'une pile vide
bool ClassPile::EstVide()
{
    if(p.hauteur == 0) return true;
    else return false;
}

// Empiler
void ClassPile::Empiler(LSC e)
{
    CellulePile *maillon;

    maillon = new CellulePile;
    maillon->info = e;
    maillon->succ = p.sommet;
    p.sommet = maillon;
    p.hauteur = p.hauteur + 1;
}

// Empiler
void ClassPile::Empiler(t_pile *pile, LSC e)
{
    CellulePile *maillon;

    maillon = new CellulePile;
    maillon->info = e;
    maillon->succ = pile->sommet;
    pile->sommet = maillon;
    pile->hauteur = pile->hauteur + 1;
}

// Dépiler
LSC ClassPile::Depiler()
{
    LSC e;
    if(EstVide()) return NULL;
    else
    {
        CellulePile *maillon;
        maillon = p.sommet;
        e = maillon->info;
        p.sommet = maillon->succ;
        delete maillon;

        p.hauteur = p.hauteur - 1;
        return e;
    }
}

// Dépiler
LSC ClassPile::DepilerSansDelete(t_pile *pile)
{
    LSC e;
    if(pile->hauteur == 0)
    {
        return NULL;
    }
    else
    {
        CellulePile *maillon;
        maillon = pile->sommet;
        e = maillon->info;
        pile->sommet = maillon->succ;
        pile->hauteur = pile->hauteur - 1;
        return e;
    }
}

// Vider
void ClassPile::Vider()
{
    ClassListeSimple liste;
    while(!EstVide())
    {
        liste.Get(Depiler());
        liste.Vider();
    }
}

// Retourner la liste contenue au dessus de la pile
LSC ClassPile::RetournerLSC()
{
    if(EstVide()) return NULL;
    else
    {
        return p.sommet->info;
    }
}

// Copier une pile et retourne l'adresse de la pile copiée
t_pile ClassPile::CopierPile()
{
    t_pile pile, pileT;
    pileT.sommet = p.sommet;
    pileT.hauteur = p.hauteur;
    pile.hauteur = 0;
    pile.sommet = NULL;

    LSC tab[p.hauteur];

    int i;
    for(i = 0; i < p.hauteur; i++)
    {
        tab[i] = DepilerSansDelete(&pileT);
    }

    for(i = (p.hauteur - 1); i >= 0; i--)
    {
        Empiler(&pile, tab[i]);
    }

    pile.hauteur = p.hauteur;

    return pile;
}

// Inverser une pile
t_pile ClassPile::InverserPile()
{
    t_pile pile, pileT;
    pileT.sommet = p.sommet;
    pileT.hauteur = p.hauteur;
    pile.hauteur = 0;
    pile.sommet = NULL;

    LSC tab[p.hauteur];

    int i;
    for(i = 0; i < p.hauteur; i++)
    {
        tab[i] = DepilerSansDelete(&pileT);
        Empiler(&pile, tab[i]);
    }
    pile.hauteur = p.hauteur;

    return pile;
}
