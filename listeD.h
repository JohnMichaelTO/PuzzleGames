#ifndef LISTED_H
#define LISTED_H

// Définition de la structure coordonnées
typedef struct s_coordonnees
{
    int x, y;
} t_coordonnees;

// Definition d’une cellule
typedef struct eD
{
    t_coordonnees info;
    struct eD *succ;
} CelluleD;

// Définition d’un type LSCD
typedef CelluleD* LSCD;

class ClassListeDeplacement
{
    public :
        // Constructeur
        ClassListeDeplacement();
        // Destructeur
        ~ClassListeDeplacement();
        // Initialisation
        void Initialiser();
        // Récupération
        void Get(LSCD p);
        // Retourner
        LSCD Retourner();
        // Retourner la longueur de la liste
        int RetournerLongueur();
        // Création d'une LSCD
        void Creer(t_coordonnees e);
        // Création d'une LSCD
        void Creer(LSCD *liste2, t_coordonnees e);
        // Affichage d'une LSCD
        void Afficher();
        // Affichage d'une LSCD sous forme de tableau
        void AfficherTab(int longueur);
        // Insertion en tête de liste
        void InsererTete(LSCD liste2);
        // Insertion en queue de liste
        void InsererQueue(LSCD liste2);
        // Insertion en queue de liste
        void InsererQueue(LSCD *liste1, LSCD liste2);
        // Supprimer la tête de liste
        void SupprimerTete();
        // Vider
        void Vider();
        // Copier et retourner une nouvelle LSCD
        LSCD CopierLSCD();
    private :
        LSCD liste;
        int size;
};

#endif // LISTED_H
