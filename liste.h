#ifndef LISTE_H
#define LISTE_H

// Definition d’une cellule
typedef struct e
{
    char info;
    struct e *succ;
} Cellule;

// Définition d’un type LSC
typedef Cellule* LSC;

class ClassListeSimple
{
    public :
        // Constructeur
        ClassListeSimple();
        // Destructeur
        ~ClassListeSimple();
        // Initialisation
        void Initialiser();
        // Récupération
        void Get(LSC p);
        // Retourner
        LSC Retourner();
        // Retourner la longueur de la liste
        int RetournerLongueur();
        // Recherche d'un élément dans la LSC
        bool Rechercher(char e);
        // Création d'une LSC
        void Creer(char e);
        // Création d'une LSC
        void Creer(LSC *listeT, char e);
        // Affichage d'une LSC
        void Afficher();
        // Affichage d'une LSC sous forme de tableau
        void AfficherTab(int longueur);
        // Insertion en tête de liste
        void InsererTete(LSC liste2);
        // Insertion en queue de liste
        void InsererQueue(LSC liste2);
        // Insertion en queue de liste
        void InsererQueue(LSC *liste1, LSC liste2);
        // Supprimer la tête de liste
        void SupprimerTete();
        // Supprimer la queue de liste
        void SupprimerQueue();
        // Vider
        void Vider();
        // Permuter le contenu de deux éléments
        void Permuter(LSC e1, LSC e2);
        // Créer un tableau d'adresse à 2 dimensions à partir d'une LSC
        LSC** CopierVersTab(int Longueur, int Hauteur);
        // Copier et retourner une nouvelle LSC
        LSC CopierLSC();
    private :
        LSC liste;
};

#endif // LISTE_H
