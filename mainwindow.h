#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "vue.h"

class mainwindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit mainwindow(QWidget *parent = 0);
        // Mise en pause de la partie
        void MettrePause();
        void AfficheNbDeplacements();
        // Réinitialise les paramètes par défaut de la souris
        void ReInitSouris();

    signals:
        //void coordScene(int x, int y);

    public slots:
        void receiveCoord(QPointF);
        void EnregistrerMouvementDansPile();

        // Slots Fichier
        void OuvrirFichier();
        void Enregistrer();
        void EnregistrerSous();
        void Quitter();

        // Slots jeu
        void MettreEnPauseContinue();
        void AfficherEtatFinal();
        void Melanger();
        void chrono();
        void Annuler();
        void Retablir();

        // Slots zoom
        void Zoom();
        void Dezoom();

    protected:
        // Modifie l'event sur la croix fermer
        virtual void closeEvent(QCloseEvent *Event);

    private:
        // Fonctions création du menu
        void creerMenu();
        void creerMenuActions();
        void addActionToMenu();
        void addActionToToolbar();
        void creerRaccourciMenu();
        void creerIconeMenu();
        void creerInfo();
        void creerMenuSlots();
        void creerStatusBar();

        // Création du dock Eléments
        void creerDockElements();

        // Toolbar
        QToolBar *toolBarFichier;
        QToolBar *toolBarJeu;
        QToolBar *toolBarAffichage;
        QToolBar *toolBarCoordonnees;
        QStatusBar *barreEtat;

        // Barres du menu
        QMenu *menuFichier;
        QMenu *menuJeu;
        QMenu *menuAffichage;

        // Actions menu Fichier
        QAction *OpenAction;
        QAction *SaveAction;
        QAction *SaveAsAction;
        QAction *QuitAction;

        // Actions menu Jeu
        QAction *UndoAction;
        QAction *DoAction;

        // Actions menu Affichage
        QAction *ZoomAction;
        QAction *DezoomAction;

        // Scene
        Vue *vue;
        QPoint pos;
        QMouseEvent *Event;

        // Coordonnées
        QLineEdit *CoordonneesX;
        QLineEdit *CoordonneesY;

        // Dock Eléments
        QDockWidget *dockElements;
        QTabWidget *tabElements;
        QWidget *plateauElements;
        QWidget *piecesElements;

        QVBoxLayout *plateauLayout;
        QPushButton *pauseButton;
        QPushButton *melangeButton;
        QPushButton *EtatFinalButton;

        // Plateau du jeu
        int LongueurPlateau;
        int HauteurPlateau;
        ClassPile pile;
        ClassPile pileRetablir;
        ClassConfigParser ConfigFile;
        ClassListeSimple PlateauCourant;
        LSC **PlateauTab;
        ClassListeDeplacement listePiece;
        ClassListeDeplacement listeArrivee;
        t_coordonnees CoordonneesSelection;
        char DernierePieceJouee;

        bool SauvegardeEffectue;
        bool Pause;
        bool EtatFinalAffiche;

        // Chronomètre
        int secondes;
        int minutes;
        int heures;
        QTimer *timer;
        QLabel *label;

        // Affichage
        QLabel *nbDeplacements;
        QString FichierOuvert;
};

#endif // MAINWINDOW_H

