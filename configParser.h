#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

class ClassConfigParser
{
    public :
        // Constructeur
        ClassConfigParser();
        // Destructeur
        ~ClassConfigParser();
        // Comparer les caractères
        bool CompareCaractere(char c);
        // Comparer les cases indisponibles (X) dans deux LSC
        bool CompareCasesIndisponibles(LSC liste1, LSC liste2);
        // Création d'une liste des pièces utilisées dans le plateau
        void CreerListePiecesUtilisees();
        // Chargement d'un fichier de configuration
        bool Charger(std::string url);
        // Sauvegarder un fichier de configuration
        bool Sauvegarder(std::string url, bool resolution);
        // Retourner une ClassPile depuis le fichier de configuration
        ClassPile Retourner();
        // Retourner une pile depuis le fichier de configuration
        t_pile RetournerPile();
        // Vider
        void Vider();
        // Définir la longueur du plateau
        void SetLongueur(int l);
        // Définit la hauteur du plateau
        void SetHauteur(int h);
        // Retourner la longueur du plateau
        int RetournerLongueur();
        // Retourner la hauteur du plateau
        int RetournerHauteur();
        // Récupérer une pile
        void GetPile(t_pile PileARecuperer);
        // Retourne le lien du fichier de configuration chargé
        std::string RetournerURL();
        // Modifie le lien du fichier de configuration chargé
        void setURL(std::string url);
        // Retourne un booléen qui indique si un fichier a été chargé
        bool ChargementOK();
        // Décharger un fichier
        void Decharger();
        // Retourne l'état initial
        LSC RetournerEtatInitial();
        // Retourne l'état final
        LSC RetournerEtatFinal();
        // Retourner la liste des pièces utilisées dans l'Etat Final (utilisée par l'IA)
        LSC RetournerListePiecesUtilisees();
        // Retourne le booléen pour l'autorisation de mélange
        bool RetournerMelange();

    private :
        // Pile contenant les listes du plateau
        ClassPile pile;
        // Lien du fichier de configuration
        std::string urlBase;
        // Longueur du plateau
        int Longueur;
        // Hauteur du plateau
        int Hauteur;
        // LSC + maillon récupérant un caractère
        ClassListeSimple p;
        ClassListeSimple pTemp;
        // LSC états initial et final
        LSC EtatInitial;
        LSC EtatFinal;
        bool FichierCharge;
        LSC ListePieces;
        bool melanger;
};

#endif // CONFIGPARSER_H
