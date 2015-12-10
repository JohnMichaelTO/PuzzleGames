#ifndef JEU_H
#define JEU_H

// Retourne le type de d�placement (0 : aucun; 1 : horizontale; 2 : verticale)
int TypeDeDeplacement(t_coordonnees point, int x, int y);

// Permutation de deux LSCD pour le jeu
LSC PermuterDeuxLSCD(LSC Plateau, int Longueur, int Hauteur, LSCD liste1, LSCD liste2);

// Fonction d'�change entre deux char
void swap(char *e1, char *e2);

// V�rifie dans les coordonn�es si c'est une pi�ce ou non
bool VerifPiece(LSC **Plateau, int x, int y);

// V�rifie si un d�placement est correct
bool VerifUnDeplacement(LSC **Plateau, int xD, int yD, int xA, int yA);

// Renvoie le type de d�placement (0 : aucun, h : haut, b : bas, g : gauche, d : droite)
char VerifTypeDeplacement(int xD, int yD, int xA, int yA);

// Retourne la diff�rence entre le point de d�part et l'arriv�e lors d'un d�placement
t_coordonnees RetournerEcartDeplacement(int xD, int yD, int xA, int yA);

// Rectifie les coordonn�es pour avoir des coordonn�es "correctes" lors d'un d�passement
t_coordonnees RectifCoordonnees(int Longueur, int Hauteur, int x, int y, bool tore);

// V�rifie s'il n'y a pas de d�passement des bornes du plateau
bool VerifDepassement(int Longueur, int Hauteur, int x, int y, bool tore);

// Cr�er une liste contenant les coordonn�es des pi�ces � d�placer
LSCD CreerListeDepart(LSC **Plateau, int Longueur, int Hauteur, int x, int y);

// Cr�er une liste contenant les coordonn�es des pi�ces o� l'on d�place
LSCD CreerListeArrivee(LSC **Plateau, int Longueur, int Hauteur, int x, int y, LSCD listeDepart, bool tore);

// Retourner la valeur absolue d'un nombre
int ValeurAbsolue(int x);

// V�rifie une fin de partie - Compare deux LSC
bool VerifFinPartie(LSC EtatFinal, LSC Etat);

// Fonction de M�lange du plateau
void MelangerPlateau(LSC **Plateau, int Longueur, int Hauteur);

#endif // JEU_H
