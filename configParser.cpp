#include <iostream>
#include <fstream>
#include <string>
#include "liste.h"
#include "pile.h"
#include "configParser.h"
//#include <QtDebug>

using namespace std;

// Constructeur
ClassConfigParser::ClassConfigParser()
{
    Longueur = -1;
    Hauteur = -1;
    // pile.Initialiser();
    FichierCharge = false;
}

// Destructeur
ClassConfigParser::~ClassConfigParser()
{

}

// Comparer les caractères
bool ClassConfigParser::CompareCaractere(char c)
{
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '#' || c == '.' || c == '\n')
    {
        return true;
    }
    return false;
}

// Comparer les cases indisponibles (X) dans deux LSC
bool ClassConfigParser::CompareCasesIndisponibles(LSC liste1, LSC liste2)
{
    LSC p1, p2;

    if(liste1 != NULL && liste2 != NULL)
    {
        p1 = liste1;
        p2 = liste2;
        while(p1 != NULL)
        {
            // std::cout << p1->info << "|" << p2->info << "\n";
            if(p1->info == 'X' || p2->info == 'X')
            {
                if((p1->info != '#' || p2->info != 'X') && (p1->info != 'X' || p2->info != '#'))
                {
                    if(p1->info != p2->info) return false;
                }
            }
            p1 = p1->succ;
            p2 = p2->succ;
        }
        return true;
    }
    return false;
}

// Création d'une liste des pièces utilisées dans le plateau
void ClassConfigParser::CreerListePiecesUtilisees()
{
    LSC liste;
    ClassListeSimple action, actionTemp;

    if(EtatFinal != NULL)
    {
        action.Initialiser();
        actionTemp.Initialiser();

        liste = EtatFinal;
        while(liste != NULL)
        {
            if(liste->info != '#' && liste->info != '.' && liste->info != 'X')
            {
                if(!action.Rechercher(liste->info))
                {
                    actionTemp.Creer(liste->info);
                    action.InsererQueue(actionTemp.Retourner());
                    actionTemp.Initialiser();
                }
            }
            liste = liste->succ;
        }
        ListePieces = action.Retourner();
    }
}

// Chargement d'un fichier de configuration
bool ClassConfigParser::Charger(string url)
{
    char caractere;
    int nbCol(0), nbLig(0), nbVideT(0), nbVide(-1);
    bool diese(false);

    melanger = false;

    // Chargement du fichier
    ifstream fichier(url.c_str(), ios::in);

    if(fichier)
    {
        urlBase = url;

        while(fichier.get(caractere))
        {
            // Vérification 1 : Caractères interdits
            if(!CompareCaractere(caractere))
            {
                //qDebug("Vérification 1 : Caractères interdits");
                Vider();
                return false;
            }

            // Autorisation de la fonction mélanger lors de l'utilisation des minuscules
            if(caractere >= 'a' && caractere <= 'z') melanger = true;

            // Condition : Lors d'un retour à la ligne
            if(caractere == '\n')
            {
                if(nbCol == 0)
                {
                    // Vérification : Nombre de lignes identiques pour un plateau dans le fichier
                    if(Hauteur != -1 && nbLig != Hauteur)
                    {
                        //qDebug("Vérification : Nombre de lignes identiques pour un plateau dans le fichier");
                        Vider();
                        return false;
                    }
                    Hauteur = nbLig;
                }
                // Vérification : Nombre de colonnes identiques dans chaque ligne du fichier
                if(Longueur != -1 && nbLig > 0 && nbCol != 0 && nbCol != Longueur)
                {
                    //qDebug("Vérification : Nombre de colonnes identiques dans chaque ligne du fichier");
                    Vider();
                    return false;
                }

                nbLig++;
                if(nbCol == 0)
                {
                    // Vérification du nombre de cases vides s'il n'y a pas de dièse
                    if(!diese)
                    {
                        // Vérifie qu'il y a le même nombre de cases vides sur chaque état
                        if(nbVide != -1 && nbVide != nbVideT)
                        {
                            //qDebug("Vérification : Même nombre de cases vides sur chaque état");
                            Vider();
                            return false;
                        }
                    }

                    diese = false;
                    nbVide = nbVideT;
                    nbVideT = 0;

                    // Compare l'emplacement des cases indisponibles avec la LSC précédente
                    if(pile.RetournerHauteur() > 0)
                    {
                        if(!CompareCasesIndisponibles(p.Retourner(), pile.RetournerLSC())) { Vider(); return false; }
                    }

                    // Stockage de la liste créée dans la pile
                    pile.Empiler(p.Retourner());
                    // Stockage de la liste définissant l'Etat Initial du jeu
                    if(pile.RetournerHauteur() == 1)
                    {
                        EtatInitial = pile.RetournerLSC();
                    }
                    // Réinitialisation pour créer une nouvelle liste
                    p.Initialiser();
                    nbLig = 0;
                }

                Longueur = nbCol;
                nbCol = 0;
            }
            else
            {
                // Compte le nombre de caractères vides
                if(caractere == '.') nbVideT = nbVideT + 1;
                else if(caractere == '#') diese = true;

                nbCol++;
                // Création d'un maillon contenant un caractère
                pTemp.Creer(caractere);
                // Insertion dans la liste le maillon créé
                p.InsererQueue(pTemp.Retourner());
            }
        }
        nbLig++;

        // Vérification du nombre de cases vides s'il n'y a pas de dièse
        if(!diese)
        {
            // Vérifie qu'il y a le même nombre de cases vides sur chaque état
            if(nbVide != -1 && nbVide != nbVideT) { Vider(); return false; }
        }

        // Compare l'emplacement des cases indisponibles avec la LSC précédente
        if(pile.RetournerHauteur() > 0)
        {
            if(!CompareCasesIndisponibles(p.Retourner(), pile.RetournerLSC())) { Vider(); return false; }
        }

        // Stockage de la liste créée dans la pile
        pile.Empiler(p.Retourner());
        // Réinitialisation pour créer une nouvelle liste
        p.Initialiser();
        if(nbCol == 0)
        {
            nbLig--;
        }
        // Vérification : Hauteur dans la dernière ligne du fichier
        if(Hauteur != -1 && nbLig != Hauteur)
        {
            //qDebug("Vérification : Hauteur dans la dernière ligne du fichier");
            Vider();
            return false;
        }
        // Vérification : Il faut deux états minimum dans la pile (Etat Initial et Final)
        if(pile.RetournerHauteur() < 2)
        {
            Vider();
            return false;
        }

        // Stockage de la liste définissant l'Etat Final du jeu
        EtatFinal = pile.Depiler();

        // Création de la liste des pièces utilisées dans l'Etat Final (utilisation de cette liste pour l'IA)
        CreerListePiecesUtilisees();
    }
    else
    {
        // cout << "Erreur dans l'ouverture du fichier : " << url << endl;
        //qDebug("Erreur dans l'ouverture du fichier");
        fichier.clear();
        return false;
    }
    FichierCharge = true;
    return true;
}

// Sauvegarder un fichier de configuration
bool ClassConfigParser::Sauvegarder(string url, bool resolution = false)
{
    ClassListeSimple liste;
    ClassPile pileTemp;
    LSC l, lTemp;
    // Chargement du fichier à sauvegarder
    ofstream fichier(url.c_str());

    if(fichier)
    {
        if(resolution == false)
        {
            pile.Empiler(EtatFinal);
            pileTemp.Get(pile.InverserPile());
            pile.Depiler();
        }
        else
        {
            pileTemp.Get(pile.CopierPile());
        }

        while(!pileTemp.EstVide())
        {
            liste.Get(pileTemp.Depiler());
            int i(0);
            l = liste.Retourner();

            if(l != NULL)
            {
                lTemp = l;
                while(lTemp != NULL)
                {
                    fichier << lTemp->info;
                    lTemp = lTemp->succ;
                    i++;
                    if(i % Longueur == 0)
                    {
                        fichier << std::endl;
                    }
                }
            }

            if(!pileTemp.EstVide()) fichier << "\n";
        }
    }
    else
    {
        // cout << "Erreur dans l'ouverture du fichier : " << url << endl;
        //qDebug("Erreur dans l'ouverture du fichier");
        fichier.clear();
        return false;
    }

    fichier.close();
    return true;
}


// Retourner une ClassPile depuis le fichier de configuration
ClassPile ClassConfigParser::Retourner()
{
    return pile;
}

// Retourner une pile depuis le fichier de configuration
t_pile ClassConfigParser::RetournerPile()
{
    return pile.Retourner();
}

// Vider
void ClassConfigParser::Vider()
{
    pile.Vider();
    p.Vider();
    // qDebug("Vidage de la pile effectué");
}

// Définir la longueur du plateau
void ClassConfigParser::SetLongueur(int l)
{
    Longueur = l;
}

// Définit la hauteur du plateau
void ClassConfigParser::SetHauteur(int h)
{
    Hauteur = h;
}

// Retourner la longueur du plateau
int ClassConfigParser::RetournerLongueur()
{
    return Longueur;
}

// Retourner la hauteur du plateau
int ClassConfigParser::RetournerHauteur()
{
    return Hauteur;
}

// Récupérer une pile
void ClassConfigParser::GetPile(t_pile PileARecuperer)
{
    pile.Get(PileARecuperer);
}

// Retourne le lien du fichier de configuration chargé
string ClassConfigParser::RetournerURL()
{
    return urlBase;
}

// Modifie le lien du fichier de configuration chargé
void ClassConfigParser::setURL(string url)
{
    urlBase = url;
}

// Retourne un booléen qui indique si un fichier a été chargé
bool ClassConfigParser::ChargementOK()
{
    return FichierCharge;
}

// Décharger un fichier
void ClassConfigParser::Decharger()
{
    ClassListeSimple listeDecharge;
    Longueur = -1;
    Hauteur = -1;
    FichierCharge = false;
    urlBase = "";

    listeDecharge.Get(EtatFinal);
    listeDecharge.Vider();
    pile.Vider();
}

// Retourne l'état initial
LSC ClassConfigParser::RetournerEtatInitial()
{
    return EtatInitial;
}

// Retourne l'état final
LSC ClassConfigParser::RetournerEtatFinal()
{
    return EtatFinal;
}

// Retourner la liste des pièces utilisées dans l'Etat Final (utilisée par l'IA)
LSC ClassConfigParser::RetournerListePiecesUtilisees()
{
    return ListePieces;
}

// Retourne le booléen pour l'autorisation de mélange
bool ClassConfigParser::RetournerMelange()
{
    return melanger;
}
