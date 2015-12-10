#ifndef CLASSLISTASTAR_H
#define CLASSLISTASTAR_H

// D�finition d'un noeud
typedef struct s_noeud
{
    int f, g, h;
    LSC plateau;
    struct s_noeud *parent;
} t_noeud;

// D�finition d'une cellule
typedef struct s_Astar
{
    t_noeud *info;
    struct s_Astar *succ;
} t_Astar;

// D�finition d'un type ListeAStar
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
        // R�cup�ration
        void Get(ListeAStar p);
        // Retourner
        ListeAStar Retourner();
        // Retourner la longueur de la liste
        int RetournerLongueur();
        // Retourner la longueur de la liste
        int RetournerLongueur(ListeAStar liste1);
        // Recherche d'un �l�ment dans la ListeAStar
        bool Rechercher(t_noeud *e);
        // Cr�ation d'une ListeAStar
        void Creer(t_noeud *e);
        // Affichage d'une ListeAStar
        void Afficher(int Longueur);
        // Insertion en t�te de liste
        void InsererTete(ListeAStar liste2);
        // Insertion en queue de liste
        void InsererQueue(ListeAStar liste2);
        // Supprimer la t�te de liste
        void SupprimerTete();
        // Vider
        void Vider();
        // Permuter le contenu de deux �l�ments
        void Permuter(ListeAStar e1, ListeAStar e2);
        // Retourner le meilleur noeud possible selon le co�t f
        t_noeud* RetournerMeilleurNoeud();
        // Insertion tri�e dans une liste tri�e
        void InsertionTriee(ListeAStar listeInseree); // La liste doit �tre ordonn�e selon le co�t f en entr�e
        // S�pare une liste en deux listes � peu pr�s �gales (~diff�rence de 1)
        ListeAStar TriFusion(ListeAStar l1);
        // Fusion de deux listes ListeAStar
        ListeAStar Fusionner(ListeAStar l1, ListeAStar l2);
    private :
        ListeAStar liste;
        int size;
};

#endif // CLASSLISTASTAR_H
