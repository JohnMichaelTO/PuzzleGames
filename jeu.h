#ifndef JEU_H
#define JEU_H

// Retourne le type de déplacement (0 : aucun; 1 : horizontale; 2 : verticale)
int TypeDeDeplacement(t_coordonnees point, int x, int y);

// Permutation de deux LSCD pour le jeu
LSC PermuterDeuxLSCD(LSC Plateau, int Longueur, int Hauteur, LSCD liste1, LSCD liste2);

// Fonction d'échange entre deux char
void swap(char *e1, char *e2);

// Vérifie dans les coordonnées si c'est une pièce ou non
bool VerifPiece(LSC **Plateau, int x, int y);

// Vérifie si un déplacement est correct
bool VerifUnDeplacement(LSC **Plateau, int xD, int yD, int xA, int yA);

// Renvoie le type de déplacement (0 : aucun, h : haut, b : bas, g : gauche, d : droite)
char VerifTypeDeplacement(int xD, int yD, int xA, int yA);

// Retourne la différence entre le point de départ et l'arrivée lors d'un déplacement
t_coordonnees RetournerEcartDeplacement(int xD, int yD, int xA, int yA);

// Rectifie les coordonnées pour avoir des coordonnées "correctes" lors d'un dépassement
t_coordonnees RectifCoordonnees(int Longueur, int Hauteur, int x, int y, bool tore);

// Vérifie s'il n'y a pas de dépassement des bornes du plateau
bool VerifDepassement(int Longueur, int Hauteur, int x, int y, bool tore);

// Créer une liste contenant les coordonnées des pièces à déplacer
LSCD CreerListeDepart(LSC **Plateau, int Longueur, int Hauteur, int x, int y);

// Créer une liste contenant les coordonnées des pièces où l'on déplace
LSCD CreerListeArrivee(LSC **Plateau, int Longueur, int Hauteur, int x, int y, LSCD listeDepart, bool tore);

// Retourner la valeur absolue d'un nombre
int ValeurAbsolue(int x);

// Vérifie une fin de partie - Compare deux LSC
bool VerifFinPartie(LSC EtatFinal, LSC Etat);

// Fonction de Mélange du plateau
void MelangerPlateau(LSC **Plateau, int Longueur, int Hauteur);

#endif // JEU_H
