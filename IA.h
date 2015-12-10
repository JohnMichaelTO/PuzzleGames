#ifndef IA_H
#define IA_H
#include "pile.h"

// Heuristique 1 : Calcule et retourne le nombre de plaquettes mal plac�es
int Heuristique(LSC lFinal, LSC lCours);

// Heuristique 2 : Calcule et retourne la distance de Manhattan + optimisation avec une pond�ration de l'heuristique
int Heuristique2(LSC lFinal, LSC lCours, LSC ListePieces, int Longueur, int Hauteur, double ponderationHeuristique);

// G�n�ration d'une liste AStar contenant les noeuds successeurs
ListeAStar GenererSuccesseurs(LSC EtatFinal, ListeAStar ListeFermee, LSC ListePieces, int Longueur, int Hauteur, t_noeud *prec, double ponderationHeuristique);

// G�n�ration d'un d�placement (gauche, droite, haut, bas) : Retourne NULL si un d�placement n'est pas possible, sinon retourne l'adresse d'une LSC
LSC GenererDeplacement(LSC liste, int Longueur, int Hauteur, int x, int y, char type);

// Remplir un noeud
t_noeud* RemplirNoeud(LSC EtatFinal, LSC EtatCourant, t_noeud *parent, LSC ListePieces, int Longueur, int Hauteur, double ponderationHeuristique);

// Compare un noeud
bool CompareNoeud(t_noeud *noeud1, t_noeud *noeud2);

// Compare une ListeAStar avec un noeud
bool CompareListeAStar(ListeAStar liste, t_noeud *noeudCompare);

// R�servation d'un noeud
t_noeud* ReserverNoeud();

// Suppression d'un noeud
void SupprimerNoeud(t_noeud *NoeudDelete);

// R�solution par l'algorithme A* modifi�e
t_pile ResoudreParAStar(LSC EtatFinal, LSC EtatCourant, LSC ListePiecesUtilisees, int Longueur, int Hauteur, double ponderationHeuristique);

#endif // IA_H
