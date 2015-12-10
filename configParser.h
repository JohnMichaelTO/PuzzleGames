#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

class ClassConfigParser
{
    public :
        // Constructeur
        ClassConfigParser();
        // Destructeur
        ~ClassConfigParser();
        // Comparer les caract�res
        bool CompareCaractere(char c);
        // Comparer les cases indisponibles (X) dans deux LSC
        bool CompareCasesIndisponibles(LSC liste1, LSC liste2);
        // Cr�ation d'une liste des pi�ces utilis�es dans le plateau
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
        // D�finir la longueur du plateau
        void SetLongueur(int l);
        // D�finit la hauteur du plateau
        void SetHauteur(int h);
        // Retourner la longueur du plateau
        int RetournerLongueur();
        // Retourner la hauteur du plateau
        int RetournerHauteur();
        // R�cup�rer une pile
        void GetPile(t_pile PileARecuperer);
        // Retourne le lien du fichier de configuration charg�
        std::string RetournerURL();
        // Modifie le lien du fichier de configuration charg�
        void setURL(std::string url);
        // Retourne un bool�en qui indique si un fichier a �t� charg�
        bool ChargementOK();
        // D�charger un fichier
        void Decharger();
        // Retourne l'�tat initial
        LSC RetournerEtatInitial();
        // Retourne l'�tat final
        LSC RetournerEtatFinal();
        // Retourner la liste des pi�ces utilis�es dans l'Etat Final (utilis�e par l'IA)
        LSC RetournerListePiecesUtilisees();
        // Retourne le bool�en pour l'autorisation de m�lange
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
        // LSC + maillon r�cup�rant un caract�re
        ClassListeSimple p;
        ClassListeSimple pTemp;
        // LSC �tats initial et final
        LSC EtatInitial;
        LSC EtatFinal;
        bool FichierCharge;
        LSC ListePieces;
        bool melanger;
};

#endif // CONFIGPARSER_H
