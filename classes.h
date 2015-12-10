#include <iostream>
#include <vector>
#include "gtest/gtest.h"
using namespace std;

// fichier contenant toutes les classes : pierre, goban et une classe de test sur le goban (pas de tests nécessaires sur le goban)


#ifndef MesClassesDuJeuDeGo_h
#define MesClassesDuJeuDeGo_h

class pierre

{
    // une pierre possède une couleur et un nombre de libertés, que l'on peut récupérer et initialiser



protected :
    char couleur;
    int liberte;

public :

    char getCouleur ()
    {
        return couleur;
    }
    void setCouleur (char col)
    {
        couleur = col;
    }
    int getLiberte ()
    {
        return liberte;
    }
    void setLiberte (int lib)
    {
        liberte = lib;
    }


//~pierre ();


};


class goban

{
    // le plateau est un tableau de vecteur de pierres car cela permet d'avoir des cases vides



public :
    vector<pierre> plateau [5][5];

public :

    void PoserPierre (int joueur, int x, int y); // pose une pierre au coordonnées x et y de la couleur du joueur
    void LibertePierre (); // calcule le nombre de libertés de la pierre et la supprime si plus de liberté

    void PoserPierre (int joueur, int x, int y);
    void LibertePierre ();

    void AfficheGoban ();
    bool PlaceLibre (int x, int y);

};


// classe pour faire des test sur le goban (pose de pierre, calcule de libertés, place libre)

class gobantest : public ::testing::Test
{

protected :
    goban goban_test;

    virtual void setUp() {}
    virtual void TearDown() {}

};


#endif // MesClassesDuJeuDeGo_h
