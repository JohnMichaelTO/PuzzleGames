#ifndef IA_H
#define IA_H
#include "pile.h"

// Heuristique 1 : Calcule et retourne le nombre de plaquettes mal placées
int Heuristique(LSC lFinal, LSC lCours);

// Heuristique 2 : Calcule et retourne la distance de Manhattan + optimisation avec une pondération de l'heuristique
int Heuristique2(LSC lFinal, LSC lCours, LSC ListePieces, int Longueur, int Hauteur, double ponderationHeuristique);

// Génération d'une liste AStar contenant les noeuds successeurs
ListeAStar GenererSuccesseurs(LSC EtatFinal, ListeAStar ListeFermee, LSC ListePieces, int Longueur, int Hauteur, t_noeud *prec, double ponderationHeuristique);

// Génération d'un déplacement (gauche, droite, haut, bas) : Retourne NULL si un déplacement n'est pas possible, sinon retourne l'adresse d'une LSC
LSC GenererDeplacement(LSC liste, int Longueur, int Hauteur, int x, int y, char type);

// Remplir un noeud
t_noeud* RemplirNoeud(LSC EtatFinal, LSC EtatCourant, t_noeud *parent, LSC ListePieces, int Longueur, int Hauteur, double ponderationHeuristique);

// Compare un noeud
bool CompareNoeud(t_noeud *noeud1, t_noeud *noeud2);

// Compare une ListeAStar avec un noeud
bool CompareListeAStar(ListeAStar liste, t_noeud *noeudCompare);

// Réservation d'un noeud
t_noeud* ReserverNoeud();

// Suppression d'un noeud
void SupprimerNoeud(t_noeud *NoeudDelete);

// Résolution par l'algorithme A* modifiée
t_pile ResoudreParAStar(LSC EtatFinal, LSC EtatCourant, LSC ListePiecesUtilisees, int Longueur, int Hauteur, double ponderationHeuristique);

#endif // IA_H
