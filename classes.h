#include <iostream>
#include <vector>
using namespace std;


#ifndef MesClassesDuJeuDeGo_h
#define MesClassesDuJeuDeGo_h

class pierre
{
public :
char couleur;
int liberte;

public :

char getCouleur (){return couleur;}
void setCouleur (char col) {couleur = col;}
int getLiberte (){return liberte;}
void setLiberte (int lib){liberte = lib;}


};


class goban
{
public :
vector<pierre> plateau [5][5];

public :
void PoserPierre (int joueur, int x, int y);
void LibertePierre ();
void AfficheGoban ();
bool PlaceLibre (int x, int y);



};

#endif // MesClassesDuJeuDeGo_h
