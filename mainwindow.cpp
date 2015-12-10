#include <iostream>
#include "mainwindow.h"
#include <QHBoxLayout>

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon(":icone.png"));

    creerMenu();
    creerMenuActions();
    addActionToMenu();
    addActionToToolbar();
    creerRaccourciMenu();
    creerInfo();
    creerIconeMenu();
    creerMenuSlots();
    creerStatusBar();
    creerDockElements();

    vue = new Vue();
    vue->setMouseTracking(true);
    QObject::connect(vue, SIGNAL(sendCoord(QPointF)), this, SLOT(receiveCoord(QPointF)));
    QObject::connect(vue, SIGNAL(EnregistrerMouvement()), this, SLOT(EnregistrerMouvementDansPile()));
    setCentralWidget(vue);
    vue->centerOn(QPointF(0, 0));
    secondes = 0;
    minutes = 0;
    heures = 0;

    LongueurPlateau = 99;
    HauteurPlateau = 99;
    CoordonneesSelection.x = 0;
    CoordonneesSelection.y = 0;

    SauvegardeEffectue = true;
    Pause = true;
    EtatFinalAffiche = false;
    DernierePieceJouee = 'X';
    FichierOuvert = "";
}

void mainwindow::creerMenu()
{
    // menu de la fenetre
    menuFichier = menuBar()->addMenu(tr("&Fichier"));
    menuJeu = menuBar()->addMenu(tr("&Jeu"));
    menuAffichage = menuBar()->addMenu(tr("A&ffichage"));
}

void mainwindow::creerMenuActions()
{
    // Actions menu Fichier
    OpenAction = new QAction(tr("&Ouvrir"), this);
    SaveAction = new QAction(tr("&Enregistrer"), this);
    SaveAsAction = new QAction(tr("Enregistrer &sous"), this);
    QuitAction = new QAction(tr("&Quitter"), this);

    // Actions menu Jeu
    UndoAction = new QAction(tr("&Annuler"), this);
    DoAction = new QAction(tr("&Rétablir"), this);

    // Actions menu Affichage
    ZoomAction = new QAction(tr("Zoom &+"), this);
    DezoomAction = new QAction(tr("Zoom &-"), this);

    // Coordonnées
    CoordonneesX = new QLineEdit;
    CoordonneesY = new QLineEdit;
    CoordonneesX->setEnabled(false);
    CoordonneesY->setEnabled(false);
    CoordonneesX->setMaximumWidth(60);
    CoordonneesY->setMaximumWidth(60);
}

void mainwindow::addActionToMenu()
{
    // Actions menu Fichier
    menuFichier->addAction(OpenAction);
    menuFichier->addSeparator();
    menuFichier->addAction(SaveAction);
    menuFichier->addAction(SaveAsAction);
    menuFichier->addSeparator();
    menuFichier->addAction(QuitAction);

    // Actions menu Jeu
    menuJeu->addAction(UndoAction);
    menuJeu->addAction(DoAction);

    // Actions menu Affichage
    menuAffichage->addAction(ZoomAction);
    menuAffichage->addAction(DezoomAction);
}

void mainwindow::addActionToToolbar()
{
    toolBarFichier = addToolBar("Fichier");
    toolBarFichier->addAction(OpenAction);
    toolBarFichier->addAction(SaveAction);

    toolBarJeu = addToolBar("Jeu");
    toolBarJeu->addAction(UndoAction);
    toolBarJeu->addAction(DoAction);

    toolBarAffichage = addToolBar("Affichage");
    toolBarAffichage->addAction(ZoomAction);
    toolBarAffichage->addAction(DezoomAction);

    toolBarCoordonnees = addToolBar("Coordonnées");
    toolBarCoordonnees->addWidget(CoordonneesX);
    toolBarCoordonnees->addWidget(CoordonneesY);
}

void mainwindow::creerRaccourciMenu()
{
    // Actions menu Fichier
    OpenAction->setShortcut(QKeySequence("Ctrl+O"));
    SaveAction->setShortcut(QKeySequence("Ctrl+S"));
    SaveAsAction->setShortcut(QKeySequence("Ctrl+Maj+S"));
    QuitAction->setShortcut(QKeySequence("Ctrl+Q"));

    // Actions menu Edition
    UndoAction->setShortcut(QKeySequence("Ctrl+Z"));
    DoAction->setShortcut(QKeySequence("Ctrl+Y"));

    // Actions menu Affichage
    ZoomAction->setShortcut(QKeySequence("Ctrl++"));
    DezoomAction->setShortcut(QKeySequence("Ctrl+-"));
}

void mainwindow::creerIconeMenu()
{
    // Actions menu Fichier
    OpenAction->setIcon(QIcon(":ouvrir.png"));
    SaveAction->setIcon(QIcon(":enregistrer.png"));
    SaveAsAction->setIcon(QIcon(":enregistrer.png"));
    QuitAction->setIcon(QIcon(":quitter.png"));

    // Actions menu Edition
    UndoAction->setIcon(QIcon(":annuler.png"));
    DoAction->setIcon(QIcon(":retablir.png"));

    // Actions menu Affichage
    ZoomAction->setIcon(QIcon(":zoom_plus.png"));
    DezoomAction->setIcon(QIcon(":zoom_moins.png"));
}

void mainwindow::creerInfo()
{
    // Actions menu Fichier
    OpenAction->setStatusTip(tr("Ouvrir un fichier de jeu/résolution/partie sauvegardée"));
    SaveAction->setStatusTip(tr("Sauvegarder la partie"));
    SaveAsAction->setStatusTip(tr("Sauvegarder la partie dans un nouveau fichier"));
    QuitAction->setStatusTip(tr("Quitter l'application"));

    // Actions menu Edition
    UndoAction->setStatusTip(tr("Annuler l'action effectuée"));
    DoAction->setStatusTip(tr("Rétablir l'action effectuée"));

    // Actions menu Affichage
    ZoomAction->setStatusTip(tr("Permet de zoomer"));
    DezoomAction->setStatusTip(tr("Permet de dézoomer"));
}

void mainwindow::creerMenuSlots()
{
    // Actions menu Fichier
    connect(OpenAction, SIGNAL(triggered()), this, SLOT(OuvrirFichier()));
    connect(SaveAction, SIGNAL(triggered()), this, SLOT(Enregistrer()));
    connect(SaveAsAction, SIGNAL(triggered()), this, SLOT(EnregistrerSous()));
    connect(QuitAction, SIGNAL(triggered()), this, SLOT(Quitter()));

    // Actions menu Jeu
    connect(UndoAction, SIGNAL(triggered()), this, SLOT(Annuler()));
    connect(DoAction, SIGNAL(triggered()), this, SLOT(Retablir()));

    // Actions zoom
    connect(ZoomAction, SIGNAL(triggered()), this, SLOT(Zoom()));
    connect(DezoomAction, SIGNAL(triggered()), this, SLOT(Dezoom()));
}

void mainwindow::creerStatusBar()
{
    barreEtat = statusBar();
}

void mainwindow::EnregistrerMouvementDansPile()
{
    pile.Empiler(PlateauCourant.CopierLSC());
    ConfigFile.GetPile(pile.Retourner());

    pileRetablir.Vider();
    SauvegardeEffectue = false;

    // Calcul de l'heuristique
    // qDebug() << Heuristique(ConfigFile.RetournerEtatFinal(), pile.RetournerLSC());
    AfficheNbDeplacements();

    if(!Pause && VerifFinPartie(ConfigFile.RetournerEtatFinal(), pile.RetournerLSC()))
    {
        MettrePause();
        pauseButton->setText(tr("Fin de la partie"));
        pauseButton->setDisabled(true);

        vue->InitPlateau(PlateauCourant.Retourner());

        std::string message, temp;
        std::stringstream ss;
        ss << (pile.RetournerHauteur() - 1);
        ss >> temp;

        message = "Félicitations !\n\nVous avez terminé le jeu avec " + temp;
        message += " déplacements en ";

        std::ostringstream oss;
        if(heures > 0)
        {
            oss << heures;
            message += oss.str();
            if(heures > 1) message += " heures ";
            else message += " heure ";
        }

        if(minutes > 0)
        {
            oss.flush();
            oss << (minutes % 60);
            message += oss.str();
            if((minutes % 60) > 1) message += " minutes ";
            else message += " minute ";
        }

        if(secondes > 0)
        {
            oss.flush();
            oss << (secondes % 60);
            message += oss.str();
            if((secondes % 60) > 1) message += " secondes";
            else message += " seconde";
        }
        message += ".";

        QMessageBox::information(this, tr("Partie terminée"), tr(message.c_str()), QMessageBox::Ok);
    }
}

void mainwindow::receiveCoord(QPointF point)
{
    if(!SauvegardeEffectue) setWindowTitle("Puzzle Games" + FichierOuvert + "*");
    else setWindowTitle("Puzzle Games" + FichierOuvert);

    int x, y;
    bool depassement(false);

    x = point.x();
    y = point.y();

    if(x < 0) { x = 0; depassement = true; }
    if(y < 0) { y = 0; depassement = true; }
    if(x > (LongueurPlateau - 1)) { x = LongueurPlateau - 1; depassement = true; }
    if(y > (HauteurPlateau - 1)) { y = HauteurPlateau - 1; depassement = true; }

    if(!Pause && ConfigFile.ChargementOK() && (CoordonneesSelection.x != x || CoordonneesSelection.y != y))
    {
        // Survol de la souris
        if(!depassement && !vue->RetournerEtatSourisPressed() && vue->RetournerEtatSourisRelachee() && PlateauTab[x][y]->info != 'X' && PlateauTab[x][y]->info != '.')
        {
            listePiece.Get(CreerListeDepart(PlateauTab, LongueurPlateau, HauteurPlateau, x, y));

            vue->setSourisSurbrillance(true);
            vue->MettreSurbrillanceAvantSelection(PlateauCourant.Retourner(), listePiece.Retourner());
            CoordonneesSelection.x = x;
            CoordonneesSelection.y = y;
        }
        // Clic enclenché
        else if(!depassement && vue->RetournerEtatSourisPressed())
        {
            LSCD temp;
            temp = CreerListeArrivee(PlateauTab, LongueurPlateau, HauteurPlateau, x, y, listePiece.Retourner(), false);
            if(temp != NULL)
            {
                listeArrivee.Get(temp);
                LSC temp;
                temp = PermuterDeuxLSCD(PlateauCourant.Retourner(), LongueurPlateau, HauteurPlateau, listePiece.CopierLSCD(), listeArrivee.CopierLSCD());
                if(temp != NULL)
                {
                    PlateauCourant.Vider();
                    PlateauCourant.Get(temp);
                    PlateauTab = PlateauCourant.CopierVersTab(LongueurPlateau, HauteurPlateau);
                }

                // Retire un mouvement si c'est une même pièce qui est redéplacée
                /*if(DernierePieceJouee == PlateauTab[x][y]->info && pile.RetournerHauteur() > 2)
                {
                    pileRetablir.Empiler(pile.Depiler());
                    pile.Depiler();
                    pile.Empiler(pileRetablir.Depiler());

                    ConfigFile.GetPile(pile.Retourner());
                }*/
                //DernierePieceJouee = PlateauTab[x][y]->info;
                vue->setDernierePieceJouee(DernierePieceJouee);

                listePiece.Get(listeArrivee.CopierLSCD());
                vue->setListeCourante(listePiece.Retourner());
                vue->setPlateauCourant(PlateauCourant.Retourner());
                vue->MettreSurbrillanceApresSelection(PlateauCourant.Retourner(), listePiece.Retourner());

                CoordonneesSelection.x = x;
                CoordonneesSelection.y = y;
            }
            else
            {
                vue->setListeCourante(listePiece.Retourner());
                vue->MettreSurbrillanceApresSelection(PlateauCourant.Retourner(), listePiece.CopierLSCD());
            }
        }
        /*
        else if(!depassement && vue->RetournerEtatSourisRelachee())
        {
            DernierePieceJouee = PlateauTab[x][y]->info;
        }*/
        // Clic non relaché
        else if(depassement && vue->RetournerEtatSourisPressed())
        {
            ReInitSouris();
        }
        else
        {
            vue->InitPlateau(PlateauCourant.Retourner());
        }
    }

    QString X = "x = ";
    QString Y = "y = ";
    X.append(QString::number(x));
    Y.append(QString::number(y));
    CoordonneesX->setText(X);
    CoordonneesY->setText(Y);
    update();
}

void mainwindow::creerDockElements()
{
    // Création du dock Eléments
    dockElements = new QDockWidget(tr("Informations diverses"), this);
    addDockWidget(Qt::RightDockWidgetArea, dockElements);
    dockElements->setMinimumWidth(250);

    tabElements = new QTabWidget;
    dockElements->setWidget(tabElements);

    plateauElements = new QWidget;
    piecesElements = new QWidget;

    plateauLayout = new QVBoxLayout;
    plateauElements->setLayout(plateauLayout);

    tabElements->addTab(plateauElements, tr("Informations"));
    pauseButton = new QPushButton;
    pauseButton->setText(tr("Commencer la partie"));
    pauseButton->setDisabled(true);
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(MettreEnPauseContinue()));
    plateauLayout->addWidget(pauseButton);

    melangeButton = new QPushButton;
    melangeButton->setText(tr("Mélanger le plateau"));
    melangeButton->setDisabled(true);
    connect(melangeButton, SIGNAL(clicked()), this, SLOT(Melanger()));
    plateauLayout->addWidget(melangeButton);

    EtatFinalButton = new QPushButton;
    EtatFinalButton->setText(tr("Afficher l'état but"));
    EtatFinalButton->setDisabled(true);
    connect(EtatFinalButton, SIGNAL(clicked()), this, SLOT(AfficherEtatFinal()));
    plateauLayout->addWidget(EtatFinalButton);

    timer = new QTimer();
    label = new QLabel();
    timer->stop();
    connect(timer, SIGNAL(timeout()), this, SLOT(chrono()));
    plateauLayout->addWidget(label, 1);

    nbDeplacements = new QLabel();
    plateauLayout->addWidget(nbDeplacements, 1);
}

// Mettre en pause - Continuer
void mainwindow::MettreEnPauseContinue()
{
    ReInitSouris();
    melangeButton->setDisabled(true);
    if(Pause)
    {
        pauseButton->setText(tr("Mettre en pause"));
        timer->start(1000); // Attention pas 100 = 0,1 seconde
    }
    else
    {
        pauseButton->setText(tr("Reprendre la partie"));
        timer->stop();
    }
    Pause = !Pause;
}

// Slot : Permet d'afficher l'état final en cours de partie
void mainwindow::AfficherEtatFinal()
{
    ReInitSouris();
    if(EtatFinalAffiche)
    {
        EtatFinalButton->setText(tr("Revenir au jeu"));
        pauseButton->setDisabled(true);
        vue->InitPlateau(ConfigFile.RetournerEtatFinal());
        timer->stop();
    }
    else
    {
        EtatFinalButton->setText(tr("Afficher l'état but"));
        pauseButton->setDisabled(false);
        vue->InitPlateau(PlateauCourant.Retourner());
        timer->start(1000);
    }
    EtatFinalAffiche = !EtatFinalAffiche;
}

// Réinitialise les paramètes par défaut de la souris
void mainwindow::ReInitSouris()
{
    vue->setSourisPressed(false);
    vue->setSourisSurbrillance(false);
    vue->setSourisReleased(true);
}

// Slot pour mélanger le plateau
void mainwindow::Melanger()
{
    MelangerPlateau(PlateauTab, LongueurPlateau, HauteurPlateau);
    vue->InitPlateau(PlateauCourant.Retourner());
}

void mainwindow::chrono()
{
    secondes++;

    if(secondes % 60 == 0)
    {
        minutes++;
    }
    if(minutes % 60 == 0 && minutes != 0)
    {
        heures++;
        minutes = minutes % 60;
    }
    label->setText(" Temps écoulé : "+ QString::number(heures)+ "h " + QString::number(minutes % 60)+ "m "+ QString::number(secondes % 60)+ "s ");
}

void mainwindow::AfficheNbDeplacements()
{
    int nb;
    nb = pile.RetournerHauteur() - 1;
    nbDeplacements->setText("Nombre de déplacements : " + QString::number(nb));
}

// Mise en pause de la partie
void mainwindow::MettrePause()
{
    pauseButton->setText(tr("Reprendre la partie"));
    Pause = true;
    timer->stop();
    ReInitSouris();
}

void mainwindow::OuvrirFichier()
{
    MettrePause();

    const QString fichier = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier de configuration"), "~/configuration.txt", tr("Fichiers texte (*.txt)"));

    if (!fichier.isEmpty())
    {
        if(ConfigFile.ChargementOK())
        {
            ConfigFile.Decharger();
            LongueurPlateau = 100;
            HauteurPlateau = 100;
            pileRetablir.Vider();
        }
        std::string FichierDeConfig = fichier.toStdString();
        if (ConfigFile.Charger(FichierDeConfig))
        {
            LongueurPlateau = ConfigFile.RetournerLongueur();
            HauteurPlateau = ConfigFile.RetournerHauteur();

            pile.Get(ConfigFile.RetournerPile());
            PlateauCourant.Get(pile.RetournerLSC());
            LSC listeT;
            listeT = PlateauCourant.CopierLSC();
            PlateauCourant.Get(listeT);
            PlateauTab = PlateauCourant.CopierVersTab(LongueurPlateau, HauteurPlateau);

            vue->setLimitePlateau(LongueurPlateau, HauteurPlateau);
            vue->centerOn(LongueurPlateau / 2., HauteurPlateau / 2.);
            vue->InitPlateau(PlateauCourant.Retourner());

            pauseButton->setText(tr("Commencer la partie"));
            pauseButton->setDisabled(false);
            EtatFinalButton->setDisabled(false);

            if(ConfigFile.RetournerMelange())
            {
                melangeButton->setDisabled(false);
            }
            else
            {
                melangeButton->setDisabled(true);
            }
            secondes = 0;
            minutes = 0;
            heures = 0;

            FichierOuvert = " - " + fichier;
            setWindowTitle("Puzzle Games" + FichierOuvert);
        }
        else
        {
            QMessageBox::warning(this, tr("Erreur dans l'ouverture du fichier"), tr("Le fichier de configuration n'a pas pu être ouvert. Vérifiez qu'il soit bien conforme."));
            vue->setLimitePlateau(100, 100);
        }
    }
}

void mainwindow::Enregistrer()
{
    MettrePause();

    const QString fichier(ConfigFile.RetournerURL().c_str());

    if(!fichier.isEmpty())
    {
        std::string FichierDeConfig = fichier.toStdString();
        if(!ConfigFile.Sauvegarder(FichierDeConfig, false))
        {
            QMessageBox::warning(this, tr("Erreur de sauvegarde"), tr("La sauvegarde a échoué, vérifiez que vous avez les permissions requises pour l'écriture du fichier."));
        }
        SauvegardeEffectue = true;
    }
}

void mainwindow::EnregistrerSous()
{
    MettrePause();

    const QString fichier = QFileDialog::getSaveFileName(this, tr("Sauvegarder un fichier de configuration"), "~/configuration.txt", tr("Fichiers texte (*.txt)"));

    if(!fichier.isEmpty())
    {
        std::string FichierDeConfig = fichier.toStdString();
        // Modifie le lien de sauvegarde
        ConfigFile.setURL(FichierDeConfig);

        if(!ConfigFile.Sauvegarder(FichierDeConfig, false))
        {
            QMessageBox::warning(this, tr("Erreur de sauvegarde"), tr("La sauvegarde a échoué, vérifiez que vous avez les permissions requises pour l'écriture du fichier."));
        }
        SauvegardeEffectue = true;
    }
}

void mainwindow::Annuler()
{
    if(!pile.EstVide() && pile.RetournerHauteur() > 1)
    {
        pileRetablir.Empiler(pile.Depiler());
        ConfigFile.GetPile(pile.Retourner());

        PlateauCourant.Get(pile.RetournerLSC());
        LSC listeT;
        listeT = PlateauCourant.CopierLSC();
        PlateauCourant.Get(listeT);

        PlateauTab = PlateauCourant.CopierVersTab(LongueurPlateau, HauteurPlateau);

        vue->setPlateauCourant(PlateauCourant.CopierLSC());
        vue->InitPlateau(PlateauCourant.Retourner());
    }
    ReInitSouris();
}

void mainwindow::Retablir()
{
    if(!pileRetablir.EstVide())
    {
        pile.Empiler(pileRetablir.Depiler());
        ConfigFile.GetPile(pile.Retourner());

        PlateauCourant.Get(pile.RetournerLSC());
        LSC listeT;
        listeT = PlateauCourant.CopierLSC();
        PlateauCourant.Get(listeT);

        PlateauTab = PlateauCourant.CopierVersTab(LongueurPlateau, HauteurPlateau);

        vue->InitPlateau(PlateauCourant.Retourner());
    }
    ReInitSouris();
}

// Quitter
void mainwindow::Quitter()
{
    MettrePause();

    if(!SauvegardeEffectue)
    {
        int reponse = QMessageBox::question(this, tr("Quitter"), tr("Voulez-vous vraiment quitter sans sauvegarder ?"), QMessageBox ::Yes | QMessageBox::No);

        if(reponse == QMessageBox::Yes)
        {
            qApp->quit();
        }
    }
}

// Modifie l'event sur la croix fermer
void mainwindow::closeEvent(QCloseEvent *Event)
{
    MettrePause();

    if(!SauvegardeEffectue)
    {
        int reponse = QMessageBox::question(this, tr("Quitter"), tr("Voulez-vous vraiment quitter sans sauvegarder ?"), QMessageBox ::Yes | QMessageBox::No);

        if(reponse == QMessageBox::Yes)
        {
            Event->accept();
        }
        else if (reponse == QMessageBox::No)
        {
            Event->ignore();
        }
    }
}

// Zoom Plus
void mainwindow::Zoom()
{
    vue->ZoomPlus();
}

// Zoom Moins
void mainwindow::Dezoom()
{
    vue->ZoomMoins();
}
