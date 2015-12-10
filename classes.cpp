#include "classes.h"

//Goban

void goban::AfficheGoban ()
{
    for (int i=0 ; i<5 ; i++)
    {
        for (int j=0; j<5 ; j++)
            {
                if (plateau[i][j].empty())
                cout << "." << '\t';
                else
                {
                if (plateau[i][j][0].getCouleur() == 'B')
                cout << "O" << '\t';
                if (plateau[i][j][0].getCouleur() == 'N')
                cout << "X" << '\t';
                }
            }

            cout << endl;

    }
}


void goban::PoserPierre (int joueur, int x, int y)
{
pierre P;
if (joueur == 1)
P.setCouleur('N');
if (joueur == 2)
P.setCouleur('B');


plateau[x][y].push_back(P);

}


bool goban::PlaceLibre (int x, int y){

if (plateau[x][y].empty() && x<5 && x>=0 && y<5 && y>=0)
return true;
else
{
cout << "impossible de placer pierre" << endl << endl;
return false;

}
}


void goban::LibertePierre ()
{

  for (int i=0 ; i<5 ; i++)
    {
        for (int j=0; j<5 ; j++)
            {
if (!plateau[i][j].empty())
{
            plateau[i][j][0].setLiberte(4);

            // case à droite
            if (j<4)
            {
                if (!plateau[i][j+1].empty())
                {
                    if (plateau[i][j+1][0].getCouleur() != plateau[i][j][0].getCouleur())
                    {

                        plateau[i][j][0].setLiberte(plateau[i][j][0].getLiberte()-1);
                    }
                }
            }
            else
                plateau[i][j][0].setLiberte(plateau[i][j][0].getLiberte()-1);

            // case à gauche
            if (j>0)
            {
                if (!plateau[i][j-1].empty())
                {
                    if (plateau[i][j-1][0].getCouleur() != plateau[i][j][0].getCouleur())
                    {
                      plateau[i][j][0].setLiberte(plateau[i][j][0].getLiberte()-1);
                    }
                }
            }
            else
                plateau[i][j][0].setLiberte(plateau[i][j][0].getLiberte()-1);

             // case en haut
             if (i>0)
             {
                if (!plateau[i-1][j].empty())
                {
                    if (plateau[i-1][j][0].getCouleur() != plateau[i][j][0].getCouleur())
                    {
                      plateau[i][j][0].setLiberte(plateau[i][j][0].getLiberte()-1);
                    }
                }
            }
            else
                plateau[i][j][0].setLiberte(plateau[i][j][0].getLiberte()-1);


             // case en bas
             if (i<4)
             {
                if (!plateau[i+1][j].empty())
                {
                    if (plateau[i+1][j][0].getCouleur() != plateau[i][j][0].getCouleur())
                    {
                        plateau[i][j][0].setLiberte(plateau[i][j][0].getLiberte()-1);
                    }
                }
            }
            else
                plateau[i][j][0].setLiberte(plateau[i][j][0].getLiberte()-1);


                if (plateau[i][j][0].getLiberte() == 0)
                {

                    plateau[i][j].clear();

                }
                }
            }
        }
}




