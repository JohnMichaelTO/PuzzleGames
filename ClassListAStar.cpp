#include <iostream>
#include "liste.h"
#include "ClassListAStar.h"
#include "IA.h"

// Constructeur
ClassListAStar::ClassListAStar()
{
    Initialiser();
}

// Destructeur
ClassListAStar::~ClassListAStar()
{
    // Vider();
}

// Initialisation
void ClassListAStar::Initialiser()
{
    liste = NULL;
}

// Récupération
void ClassListAStar::Get(ListeAStar p)
{
    liste = p;
}

// Retourner
ListeAStar ClassListAStar::Retourner()
{
    return liste;
}

// Retourner la longueur de la liste
int ClassListAStar::RetournerLongueur()
{
    int i(0);
    ListeAStar p;
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

// Retourner la longueur de la liste
int ClassListAStar::RetournerLongueur(ListeAStar liste1)
{
    int i(0);
    ListeAStar p;
    if(liste1 == NULL) return 0;
    else
    {
        p = liste1;
        while(p != NULL)
        {
            i++;
            p = p->succ;
        }
    }
    return i;
}

// Création d'une ListeAStar
void ClassListAStar::Creer(t_noeud *e)
{
    t_Astar *maillon;

    maillon = new t_Astar;
    maillon->info = e;
    maillon->succ = NULL;
    liste = maillon;
}

// Affichage d'une ListeAStar
void ClassListAStar::Afficher(int Longueur)
{
    ListeAStar p;
    ClassListeSimple action;
    if(liste == NULL)
        std::cout << "LA LISTE EST VIDE \n\n";
    else
    {
        p = liste;
        while(p != NULL)
        {
            action.Get(p->info->plateau);
            std::cout << "\nCout : " << p->info->g << " + " << p->info->h << " = " << p->info->f << "\n";
            action.AfficherTab(Longueur);
            p = p->succ;
        }
    }
}

// Insertion en tête de liste
void ClassListAStar::InsererTete(ListeAStar liste2)
{
    ListeAStar p;
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
void ClassListAStar::InsererQueue(ListeAStar liste2)
{
    ListeAStar p;
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

// Supprimer la tête de liste
void ClassListAStar::SupprimerTete()
{
    ListeAStar p;
    p = liste;
    SupprimerNoeud(p->info);
    liste = liste->succ;
    delete p;
    p = NULL;
}

// Vider
void ClassListAStar::Vider()
{
    while(liste != NULL)
    {
        SupprimerTete();
    }
}

// Permuter le contenu de deux éléments
void ClassListAStar::Permuter(ListeAStar e1, ListeAStar e2)
{
    t_noeud *temp;
    temp = e1->info;
    e1->info = e2->info;
    e2->info = temp;
}

// Retourner le meilleur noeud possible selon le coût f
t_noeud* ClassListAStar::RetournerMeilleurNoeud()
{
    int meilleurF;
    t_noeud *meilleurNoeud = ReserverNoeud();
    meilleurNoeud->plateau = NULL;
    meilleurNoeud->parent = NULL;

    ListeAStar p(NULL);
    if(liste == NULL) return meilleurNoeud;
    else
    {
        p = liste;
        meilleurF = p->info->f;
        meilleurNoeud = p->info;
        liste = liste->succ;
    }
    return meilleurNoeud;
}

// Insertion triée dans une liste triée
void ClassListAStar::InsertionTriee(ListeAStar listeInseree) // La liste doit être ordonnée selon le coût f en entrée
{
    ListeAStar p, p2, temp;

    if(listeInseree == NULL) return;
    if(liste == NULL) InsererTete(listeInseree); // Cas de la liste vide
    else
    {
        p = listeInseree;
        while(p != NULL)
        {
            p2 = liste;

            // Gestion de la tête de liste
            if(p->info->f < p2->info->f)
            {
                temp = p->succ;
                p->succ = p2;
                liste = p;
                p = temp;
            }
            else
            {
                // On itère jusqu'au point d'ajout
                while(p2->succ != NULL && p->info->f > p2->succ->info->f)
                {
                    p2 = p2->succ;
                }

                // Raccordement du maillon
                temp = p->succ;
                p->succ = p2->succ;
                p2->succ = p;

                p = temp;
            }
        }
    }
}

// Sépare une liste en deux listes à peu près égales (~différence de 1)
ListeAStar ClassListAStar::TriFusion(ListeAStar l1)
{
    int i(1), L;
    ListeAStar p(NULL);

    L = RetournerLongueur(l1);
    if(L <= 1) return l1;

    ListeAStar gauche(NULL), droite(NULL);
    int milieu = L / 2;

    if(l1 != NULL)
    {
        p = l1;
        gauche = p;

        while(i <= milieu)
        {
            p = p->succ;
            i++;
        }

        droite = p->succ;
        p->succ = NULL;
        p = droite;

        while(p != NULL)
        {
            p = p->succ;
        }

        gauche = TriFusion(gauche);
        droite = TriFusion(droite);
    }
    return Fusionner(gauche, droite);
}

// Fusion de deux listes ListeAStar
ListeAStar ClassListAStar::Fusionner(ListeAStar l1, ListeAStar l2)
{
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;
    if(l1->info->f < l2->info->f)
    {
        l1->succ = Fusionner(l1->succ, l2);
        return l1;
    }
    else
    {
        l2->succ = Fusionner(l1, l2->succ);
        return l2;
    }
}
