#ifndef CLASSLISTASTAR_H
#define CLASSLISTASTAR_H

// Définition d'un noeud
typedef struct s_noeud
{
    int f, g, h;
    LSC plateau;
    struct s_noeud *parent;
} t_noeud;

// Définition d'une cellule
typedef struct s_Astar
{
    t_noeud *info;
    struct s_Astar *succ;
} t_Astar;

// Définition d'un type ListeAStar
typedef t_Astar* ListeAStar;

class ClassListAStar
{
    public :
        // Constructeur
        ClassListAStar();
        // Destructeur
        ~ClassListAStar();
        // Initialisation
        void Initialiser();
        // Récupération
        void Get(ListeAStar p);
        // Retourner
        ListeAStar Retourner();
        // Retourner la longueur de la liste
        int RetournerLongueur();
        // Retourner la longueur de la liste
        int RetournerLongueur(ListeAStar liste1);
        // Recherche d'un élément dans la ListeAStar
        bool Rechercher(t_noeud *e);
        // Création d'une ListeAStar
        void Creer(t_noeud *e);
        // Affichage d'une ListeAStar
        void Afficher(int Longueur);
        // Insertion en tête de liste
        void InsererTete(ListeAStar liste2);
        // Insertion en queue de liste
        void InsererQueue(ListeAStar liste2);
        // Supprimer la tête de liste
        void SupprimerTete();
        // Vider
        void Vider();
        // Permuter le contenu de deux éléments
        void Permuter(ListeAStar e1, ListeAStar e2);
        // Retourner le meilleur noeud possible selon le coût f
        t_noeud* RetournerMeilleurNoeud();
        // Insertion triée dans une liste triée
        void InsertionTriee(ListeAStar listeInseree); // La liste doit être ordonnée selon le coût f en entrée
        // Sépare une liste en deux listes à peu près égales (~différence de 1)
        ListeAStar TriFusion(ListeAStar l1);
        // Fusion de deux listes ListeAStar
        ListeAStar Fusionner(ListeAStar l1, ListeAStar l2);
    private :
        ListeAStar liste;
        int size;
};

#endif // CLASSLISTASTAR_H
