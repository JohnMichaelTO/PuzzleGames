#ifndef VUE_H
#define VUE_H

#include <QtGui>
//#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <sstream>
#include "liste.h"
#include "listeD.h"
#include "pile.h"
#include "configParser.h"
#include "jeu.h"
#include "ClassListAStar.h"
#include "IA.h"
//#include <QHBoxLayout>

class Vue : public QGraphicsView
{
    Q_OBJECT
    public:
        Vue(QWidget *parent = 0);
        Vue(QGraphicsScene *scene, QWidget *parent = 0);
        QPoint CoordScene(QMouseEvent *Event);
        void MettreSurbrillanceAvantSelection(LSC Plateau, LSCD listePiece);
        void MettreSurbrillanceApresSelection(LSC Plateau, LSCD listePiece);
        void setPlateauCourant(LSC Plateau);
        void setListeCourante(LSCD liste);
        LSC RetournerPlateauCourant();
        LSCD RetournerListeCourante();
        bool RetournerEtatSourisPressed();
        bool RetournerEtatSourisSurbrillance();
        bool RetournerEtatSourisRelachee();
        void InitPlateau(LSC Plateau);
        void setLimitePlateau(int Longueur, int Hauteur);
        QPixmap RetournerImage(char e);
        // Modifie la valeur qui désigne si une pièce est en survol de la souris
        void setSourisSurbrillance(bool valeur);
        // Modifie la valeur qui désigne la souris pressée (clic gauche)
        void setSourisPressed(bool valeur);
        // Modifie la valeur qui désigne si le clic de la souris est relachée ou non
        void setSourisReleased(bool valeur);
        void EffacerScene();

        // Dézoomer
        void ZoomMoins();
        // Zoomer
        void ZoomPlus();

        // Modifie la dernière pièce jouée
        void setDernierePieceJouee(char e);
        ~Vue();

    signals:
        void sendCoord(QPointF);
        void EnregistrerMouvement();

    private:
        QGraphicsScene *scene;
        QGraphicsItem *grille[100][100];
        int LongueurPlateau;
        int HauteurPlateau;
        bool SourisSurbrillance;
        bool SourisPressed;
        bool SourisReleased;
        LSCD listeCourante;
        LSC PlateauCourant;
        char DernierePieceJouee;

    protected:
        virtual void mouseMoveEvent(QMouseEvent *Event);
        virtual void mousePressEvent(QMouseEvent *Event);
        virtual void mouseReleaseEvent(QMouseEvent *Event);

};

#endif // VUE_H
