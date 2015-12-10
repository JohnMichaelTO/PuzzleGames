#include <iostream>
#include <cstdlib>
#include "liste.h"
#include "listeD.h"
#include "jeu.h"
//#include <QtDebug>

// Retourne le type de déplacement (0 : aucun; 1 : horizontale; 2 : verticale)
int TypeDeDeplacement(t_coordonnees point, int x, int y)
{
    if(point.y == y && (point.x == x + 1 || point.x == x - 1 || point.x != x))
    {
        // qDebug("Translation horizontale");
        return 1;
    }
    if(point.x == x && (point.y == y + 1 || point.y == y - 1 || point.y != y))
    {
        // qDebug("Translation verticale");
        return 2;
    }
    /*
    if(point.x == x && point.y == y)
    {
        qDebug("Pas de deplacement");
    }
    */
    return 0;
}

// Permutation de deux LSCD pour le jeu
LSC PermuterDeuxLSCD(LSC Plateau, int Longueur, int Hauteur, LSCD liste1, LSCD liste2)
{
    LSCD l1, l2;
    l1 = liste1;
    l2 = liste2;

    LSC **Plateau1, **Plateau2, listeTemp;
    ClassListeSimple Temp, Temp2;

    Temp.Get(Plateau);
    Plateau1 = Temp.CopierVersTab(Longueur, Hauteur);

    // Copie de la liste principale pour effectuer les déplacements
    Temp2.Get(Temp.CopierLSC());
    listeTemp = Temp2.Retourner();
    Plateau2 = Temp2.CopierVersTab(Longueur, Hauteur);

    if(l1 != NULL && l2 != NULL)
    {
        while(l1 != NULL)
        {
            if(!VerifUnDeplacement(Plateau1, l1->info.x, l1->info.y, l2->info.x, l2->info.y))
            {
                return NULL;
            }

            Plateau2[l1->info.x][l1->info.y]->info = '.';
            Plateau2[l2->info.x][l2->info.y]->info = '.';

            l1 = l1->succ;
            l2 = l2->succ;
        }

        l1 = liste1;
        l2 = liste2;

        while(l1 != NULL)
        {
            Plateau2[l2->info.x][l2->info.y]->info = Plateau1[l1->info.x][l1->info.y]->info;
            l1 = l1->succ;
            l2 = l2->succ;
        }

        Plateau = listeTemp;

        return Plateau;
    }
    return NULL;
}

// Fonction d'échange entre deux char
void swap(char *e1, char *e2)
{
    char temp;
    temp = *e1;
    *e1 = *e2;
    *e2 = temp;
}

// Vérifie dans les coordonnées si c'est une pièce ou non
bool VerifPiece(LSC **Plateau, int x, int y)
{
    if(Plateau[x][y]->info != 'X' && Plateau[x][y]->info != '.')
        return true;
    else
        return false;
}

// Vérifie si un déplacement est correct
bool VerifUnDeplacement(LSC **Plateau, int xD, int yD, int xA, int yA)
{
    if(Plateau[xA][yA]->info == '.' || Plateau[xA][yA]->info == Plateau[xD][yD]->info)
        return true;
    else
        return false;
}

// Renvoie le type de déplacement (0 : aucun, h : haut, b : bas, g : gauche, d : droite)
char VerifTypeDeplacement(int xD, int yD, int xA, int yA)
{
    char type('0');
    int xdiff = xA - xD;
    int ydiff = yA - yD;

    if(xdiff == 0 && ydiff < 0) type = 'h';
    else if(xdiff == 0 && ydiff > 0) type = 'b';
    else if(ydiff == 0 && xdiff < 0) type = 'g';
    else if(ydiff == 0 && xdiff > 0) type = 'd';
    return type;
}

// Retourne la différence entre le point de départ et l'arrivée lors d'un déplacement
t_coordonnees RetournerEcartDeplacement(int xD, int yD, int xA, int yA)
{
    t_coordonnees ecart;
    ecart.x = xA - xD;
    ecart.y = yA - yD;
    return ecart;
}

// Rectifie les coordonnées pour avoir des coordonnées "correctes" lors d'un dépassement
t_coordonnees RectifCoordonnees(int Longueur, int Hauteur, int x, int y, bool tore = false)
{
    t_coordonnees rectif;
    if(tore)
    {
        if(x < 0) x = Longueur - 1;
        if(y < 0) y = Hauteur - 1;
        if(x > (Longueur - 1)) x = 0;
        if(y > (Hauteur - 1)) y = 0;
    }
    else
    {
        if(x < 0) x = 0;
        if(y < 0) y = 0;
        if(x > (Longueur - 1)) x = Longueur - 1;
        if(y > (Hauteur - 1)) y = Hauteur - 1;
    }
    rectif.x = x;
    rectif.y = y;
    return rectif;
}

// Vérifie s'il n'y a pas de dépassement des bornes du plateau
bool VerifDepassement(int Longueur, int Hauteur, int x, int y, bool tore = false)
{
    // Le dépassement des limites n'existe pas pour le mode tore
    if(tore) return true;

    if(x < 0) return false;
    if(y < 0) return false;
    if(x > (Longueur - 1)) return false;
    if(y > (Hauteur - 1)) return false;

    return true;
}

// Créer une liste contenant les coordonnées des pièces à déplacer
LSCD CreerListeDepart(LSC **Plateau, int Longueur, int Hauteur, int x, int y)
{
    int i, j;
    t_coordonnees temp;
    ClassListeDeplacement action, actionTemp;
    LSCD liste;

    action.Initialiser();
    if(!VerifDepassement(Longueur, Hauteur, x, y, false)) { action.Vider(); return NULL; }
    temp.x = x;
    temp.y = y;
    action.Creer(temp);
    for(j = 0; j < Hauteur; j++)
    {
        for(i = 0; i < Longueur; i++)
        {
            if(!VerifDepassement(Longueur, Hauteur, i, j, false)) { action.Vider(); return NULL; }

            if((i != x || j != y) && Plateau[i][j]->info == Plateau[x][y]->info && VerifPiece(Plateau, i, j))
            {
                temp.x = i;
                temp.y = j;
                actionTemp.Creer(temp);
                action.InsererQueue(actionTemp.Retourner());
                actionTemp.Initialiser();
            }
        }
    }
    liste = action.CopierLSCD();
    action.Vider();
    return liste;
}

// Créer une liste contenant les coordonnées des pièces où l'on déplace
LSCD CreerListeArrivee(LSC **Plateau, int Longueur, int Hauteur, int x, int y, LSCD listeDepart, bool tore = false)
{
    t_coordonnees temp, ecart;
    ClassListeDeplacement action, actionTemp;
    LSCD liste, p;
    char type;

    if(listeDepart != NULL)
    {
        p = listeDepart;
        type = VerifTypeDeplacement(p->info.x, p->info.y, x, y);
        ecart = RetournerEcartDeplacement(p->info.x, p->info.y, x, y);

        action.Initialiser();

        while(p != NULL)
        {
            temp.x = p->info.x + ecart.x;
            temp.y = p->info.y + ecart.y;

            // Vérification d'un déplacement trop grand
            if(ValeurAbsolue(ecart.x) > 1) { action.Vider(); return NULL; }
            if(ValeurAbsolue(ecart.y) > 1) { action.Vider(); return NULL; }

            // Pas de déplacement en diagonal
            if(ValeurAbsolue(ecart.x) > 0 && ValeurAbsolue(ecart.y) > 0) { action.Vider(); return NULL; }

            // Vérification sur le dépassement des limites
            if(!VerifDepassement(Longueur, Hauteur, temp.x, temp.y, tore)) { action.Vider(); return NULL; }

            // Correction des coordonnées pour le cas d'un tore
            temp = RectifCoordonnees(Longueur, Hauteur, temp.x, temp.y, tore);

            // Vérification pour chaque élément de la liste
            if(!VerifUnDeplacement(Plateau, p->info.x, p->info.y, temp.x, temp.y)) { action.Vider(); return NULL; }

            // Vérification d'un déplacement identique pour tous les éléments de la liste
            if(VerifTypeDeplacement(p->info.x, p->info.y, temp.x, temp.y) != type) { action.Vider(); return NULL; }

            actionTemp.Creer(temp);
            action.InsererQueue(actionTemp.Retourner());
            actionTemp.Initialiser();
            p = p->succ;
        }

        liste = action.CopierLSCD();
        action.Vider();
        return liste;
    }
    return NULL;
}

// Retourner la valeur absolue d'un nombre
int ValeurAbsolue(int x)
{
    if(x < 0) return -x;
    return x;
}

// Vérifie une fin de partie - Compare deux LSC
bool VerifFinPartie(LSC EtatFinal, LSC Etat)
{
    LSC p1, p2;

    if(EtatFinal != NULL && Etat != NULL)
    {
        p1 = EtatFinal;
        p2 = Etat;
        while(p1 != NULL)
        {
            //std::cout << p1->info << "|" << p2->info << "\n";
            if(p1->info != '#')
            {
                if(p1->info != p2->info) return false;
            }
            p1 = p1->succ;
            p2 = p2->succ;
        }
    }
    return true;
}

// Fonction de Mélange du plateau
void MelangerPlateau(LSC **Plateau, int Longueur, int Hauteur)
{
    int l, rl, h, rh, parite(0);

    do
    {
        h = Hauteur;
        l = Longueur;
        for(h = h - 1; h > 0; h--)
        {
            for(l = l - 1; l > 0; l--)
            {
                rh = rand() % (h + 1);
                rl = rand() % (l + 1);

                swap(&(Plateau[l][h]->info), &(Plateau[rl][rh]->info));
                if((h + l) % 2 != (rh + rl) % 2)
                {
                    parite++;
                }
            }
        }
    } while(parite % 2 == 1);
}
