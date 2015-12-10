#include "vue.h"

Vue::Vue(QWidget *parent) : QGraphicsView(parent)
{
    // int x, y;
    LongueurPlateau = 100;
    HauteurPlateau = 100;
    SourisSurbrillance = false;
    SourisPressed = false;
    SourisReleased = true;
    scene = new QGraphicsScene();

    this->setScene(scene);
}

Vue::~Vue()
{
}

QPoint Vue::CoordScene(QMouseEvent *Event)
{
    int X(0), Y(0);
    QPointF point;
    QPoint normal;
    point = mapToScene(Event->x(), Event->y());

    point.setX(point.x() / 64);
    point.setY(point.y() / 64);

    X = point.x();
    Y = point.y();

    if(point.x() < 0.0) X = -1;
    if(point.y() < 0.0) Y = -1;

    if(X < 0) X = -1;
    if(Y < 0) Y = -1;
    if(X > (LongueurPlateau - 1)) X = LongueurPlateau;
    if(Y > (HauteurPlateau - 1)) Y = HauteurPlateau;

    normal.setX(X);
    normal.setY(Y);

    return normal;
}

void Vue::mouseMoveEvent(QMouseEvent *Event)
{
    emit sendCoord(CoordScene(Event));
}

void Vue::mousePressEvent(QMouseEvent *Event)
{
    if(SourisSurbrillance && Event->button() == Qt::LeftButton)
    {
        LSCD p;
        int x, y;

        scene->clear();
        InitPlateau(PlateauCourant);
        if(listeCourante != NULL)
        {
            p = listeCourante;
            while(p != NULL)
            {
                x = p->info.x;
                y = p->info.y;
                scene->addRect(QRectF(64 * x, 64 * y, 64, 64), QPen(QColor(255, 255, 255, 0), 0), QBrush(QColor(255, 255, 255, 100)));
                p = p->succ;
            }
        }
        SourisPressed = true;
        SourisReleased = false;
    }
}

void Vue::mouseReleaseEvent(QMouseEvent *Event)
{
    SourisReleased = true;
    if(SourisPressed)
    {
        SourisPressed = false;
        if(SourisSurbrillance)
        {
            MettreSurbrillanceAvantSelection(PlateauCourant, listeCourante);
        }
        else
        {
            InitPlateau(PlateauCourant);
        }
    }

    listeCourante = NULL;
    emit EnregistrerMouvement();
}

void Vue::MettreSurbrillanceAvantSelection(LSC Plateau, LSCD listePiece)
{
    LSCD p;
    int x, y;

    scene->clear();
    InitPlateau(Plateau);
    if(listePiece != NULL)
    {
        p = listePiece;
        while(p != NULL)
        {
            x = p->info.x;
            y = p->info.y;
            scene->addRect(QRectF(64 * x, 64 * y, 64, 64), QPen(QColor(36, 156, 206, 0), 0), QBrush(QColor(36, 156, 206, 100)));
            p = p->succ;
        }
        setListeCourante(listePiece);
        setPlateauCourant(Plateau);
    }
}

void Vue::setPlateauCourant(LSC Plateau)
{
    PlateauCourant = Plateau;
}

void Vue::setListeCourante(LSCD liste)
{
    listeCourante = liste;
}

LSC Vue::RetournerPlateauCourant()
{
    return PlateauCourant;
}

LSCD Vue::RetournerListeCourante()
{
    return listeCourante;
}

void Vue::MettreSurbrillanceApresSelection(LSC Plateau, LSCD listePiece)
{
    LSCD p;
    int x, y;

    scene->clear();
    InitPlateau(Plateau);
    if(listePiece != NULL)
    {
        p = listePiece;
        while(p != NULL)
        {
            x = p->info.x;
            y = p->info.y;
            scene->addRect(QRectF(64 * x, 64 * y, 64, 64), QPen(QColor(255, 255, 255, 0), 0), QBrush(QColor(255, 255, 255, 100)));
            p = p->succ;
        }
    }
}

bool Vue::RetournerEtatSourisPressed()
{
    return SourisPressed;
}

bool Vue::RetournerEtatSourisSurbrillance()
{
    return SourisSurbrillance;
}

bool Vue::RetournerEtatSourisRelachee()
{
    return SourisReleased;
}

void Vue::InitPlateau(LSC Plateau)
{
    LSC plateau(Plateau), pTemp;
    int x(0), y(0);

    if(plateau != NULL)
    {
        pTemp = plateau;

        scene->clear();

        while(pTemp != NULL)
        {
            grille[x][y] = scene->addPixmap(RetournerImage(pTemp->info));
            grille[x][y]->setPos(64*x,64*y);

            pTemp = pTemp->succ;
            x++;
            if(x % LongueurPlateau == 0)
            {
                y++;
                x = 0;
            }
        }
    }
}

// Définie les limites du plateau
void Vue::setLimitePlateau(int Longueur, int Hauteur)
{
    LongueurPlateau = Longueur;
    HauteurPlateau = Hauteur;
}

// Renvoie un QPixmap
QPixmap Vue::RetournerImage(char e)
{
    if(e != 'X' && e != '.' && e != '#')
    {
        std::stringstream ss;
        std::string s;
        ss << e;
        ss >> s;

        if(e >= 'a' && e <= 'z') s = ":" + s + "_.png";
        else s = ":" + s + ".png";

        QString image(s.c_str());

        return QPixmap(image);
    }
    else if(e == 'X')
    {
        return QPixmap(":indisponible.png");
    }
    else
    {
        return QPixmap(":vide.png");
    }
}

// Modifie la valeur qui désigne si une pièce est en survol de la souris
void Vue::setSourisSurbrillance(bool valeur)
{
    SourisSurbrillance = valeur;
}

// Modifie la valeur qui désigne la souris pressée (clic gauche)
void Vue::setSourisPressed(bool valeur)
{
    SourisPressed = valeur;
}

// Modifie la valeur qui désigne si le clic de la souris est relachée ou non
void Vue::setSourisReleased(bool valeur)
{
    SourisReleased = valeur;
}

// Effacer la scène
void Vue::EffacerScene()
{
    int x, y;

    for(x = 0; x < LongueurPlateau; x++)
    {
        for(y = 0; y < HauteurPlateau; y++)
        {
            grille[x][y]->setPos(0,0);
        }
    }

    scene->clear();
}

// Dézoomer
void Vue::ZoomMoins()
{
    this->scale(0.9, 0.9);
}

// Zoomer
void Vue::ZoomPlus()
{
    this->scale(1.10, 1.10);
}

// Modifie la dernière pièce jouée
void Vue::setDernierePieceJouee(char e)
{
    DernierePieceJouee = e;
}
