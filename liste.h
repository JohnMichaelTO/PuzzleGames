#ifndef LISTE_H
#define LISTE_H

// Definition d�une cellule
typedef struct e
{
    char info;
    struct e *succ;
} Cellule;

// D�finition d�un type LSC
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
        // R�cup�ration
        void Get(LSC p);
        // Retourner
        LSC Retourner();
        // Retourner la longueur de la liste
        int RetournerLongueur();
        // Recherche d'un �l�ment dans la LSC
        bool Rechercher(char e);
        // Cr�ation d'une LSC
        void Creer(char e);
        // Cr�ation d'une LSC
        void Creer(LSC *listeT, char e);
        // Affichage d'une LSC
        void Afficher();
        // Affichage d'une LSC sous forme de tableau
        void AfficherTab(int longueur);
        // Insertion en t�te de liste
        void InsererTete(LSC liste2);
        // Insertion en queue de liste
        void InsererQueue(LSC liste2);
        // Insertion en queue de liste
        void InsererQueue(LSC *liste1, LSC liste2);
        // Supprimer la t�te de liste
        void SupprimerTete();
        // Supprimer la queue de liste
        void SupprimerQueue();
        // Vider
        void Vider();
        // Permuter le contenu de deux �l�ments
        void Permuter(LSC e1, LSC e2);
        // Cr�er un tableau d'adresse � 2 dimensions � partir d'une LSC
        LSC** CopierVersTab(int Longueur, int Hauteur);
        // Copier et retourner une nouvelle LSC
        LSC CopierLSC();
    private :
        LSC liste;
};

#endif // LISTE_H
