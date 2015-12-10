#ifndef PILE_H
#define PILE_H

// Definition d’un maillon pour la pile
typedef struct ePile
{
    LSC info;
    struct ePile *succ;
} CellulePile;

// Définition du type LSCPile
typedef CellulePile* LSCPile;

// Définition d'une pile
typedef struct s_pile
{
    LSCPile sommet;
    int hauteur;
} t_pile;

class ClassPile
{
    public :
        // Constructeur
        ClassPile();
        // Destructeur
        ~ClassPile();
        // Récupération d'une pile
        void Get(t_pile pile);
        // Retourner une pile
        t_pile Retourner();
        // Retourner la hauteur de la pile
        unsigned RetournerHauteur();
        // Initialisation d'une pile
        void Initialiser();
        // Test d'une pile vide
        bool EstVide();
        // Empiler
        void Empiler(LSC e);
        // Empiler
        void Empiler(t_pile *pile, LSC e);
        // Dépiler
        LSC Depiler();
        // Dépiler
        LSC DepilerSansDelete(t_pile *pile);
        // Vider
        void Vider();
        // Retourner la liste contenue au dessus de la pile
        LSC RetournerLSC();
        // Copier une pile et retourne l'adresse de la pile copiée
        t_pile CopierPile();
        // Inverser une pile
        t_pile InverserPile();

    private :
        t_pile p;
};

#endif // PILE_H
