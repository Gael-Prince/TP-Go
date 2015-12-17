#include "classes.h"

//Goban

void goban::AfficheGoban ()
{

    // pour chaque emplacement :
    for (int i=0 ; i<5 ; i++)
    {
        for (int j=0; j<5 ; j++)
        {
            // si la place est vide : on affiche un point
            if (plateau[i][j].empty())
                cout << "." << '\t';
            else
            {
                // si ce n'est pas vide, on regarde la couleur de la pierre et on affiche soit un 0 soit un X
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
// il faut juste définir la couleur de la pierre posée...
    if (joueur == 1)
        P.setCouleur('N');
    if (joueur == 2)
        P.setCouleur('B');

//... et la mettre dans le vecteur contenant l'ensemble des pierres du jeu
    plateau[x][y].push_back(P);



}





bool goban::PlaceLibre (int x, int y, int joueur)
{
    // Si la case dans laquelle on souhaite se placer est vide et dans le plateau
    if (plateau[x][y].empty() && x<5 && x>=0 && y<5 && y>=0)
    {
        // On va ici checker si la pièce se suicide en se posant sur cette case
        // On va vérifier en une seule boucle les 4 cases adjacentes [x][y+1], [x][y-1], [x+1][y], [x-1][y]
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2; j++)
            {
                // Si la case vérifiée est bien dans le tableau
                if ((((1-i)*x + i*(x-1+2*j))<5) && (((1-i)*x + i*(x-1+2*j))>=0) && ((i*y + (1-i)*(y+1-2*j))<5) && ((i*y + (1-i)*(y+1-2*j)))>=0)
                {
                    // Si la case vérifiée est vide ou si elle contient un jeton de la même couleur, alors on peut jouer
                    if (plateau[(1-i)*x + i*(x-1+2*j)][i*y + (1-i)*(y+1-2*j)].empty() ||
                       (joueur == 1 && plateau[(1-i)*x + i*(x-1+2*j)][i*y + (1-i)*(y+1-2*j)][0].getCouleur() == 'N') ||
                       (joueur == 2 && plateau[(1-i)*x + i*(x-1+2*j)][i*y + (1-i)*(y+1-2*j)][0].getCouleur() == 'B'))
                            return true;
                }
            }
        }
    }
    // Sinon on ne peut pas jouer dans cette case
    cout << "Impossible de placer pierre" << endl << endl;
    return false;
}





void goban::LibertePierre ()
{
    // On parcourt le goban
    for (int x=0 ; x<5 ; x++)
    {
        for (int y=0; y<5 ; y++)
        {
            // Si la case principale n'est pas vide
            if (!plateau[x][y].empty())
            {
                //On initialise la liberté à 4
                plateau[x][y][0].setLiberte(4);
                plateau[x][y][0].setCaseLibreAdjacente(false);
                plateau[x][y][0].setDeces(false);

                // On va vérifier en une seule boucle les 4 cases adjacentes [x][y+1], [x][y-1], [x+1][y], [x-1][y]
                for (int i=0; i<2; i++)
                {
                    for (int j=0; j<2; j++)
                    {
                        // Si la case vérifiée est bien dans le tableau
                        if ((((1-i)*x + i*(x-1+2*j))<5) && (((1-i)*x + i*(x-1+2*j))>=0) && ((i*y + (1-i)*(y+1-2*j))<5) && ((i*y + (1-i)*(y+1-2*j)))>=0)
                        {
                            // Si la case vérifiée n'est pas vide
                            if (!plateau[(1-i)*x + i*(x-1+2*j)][i*y + (1-i)*(y+1-2*j)].empty())
                            {
                                // Si la couleur du jeton sur la case vérifiée est différente de celle du jeton sur la case principale
                                if (plateau[(1-i)*x + i*(x-1+2*j)][i*y + (1-i)*(y+1-2*j)][0].getCouleur() != plateau[x][y][0].getCouleur())
                                    // On diminue la liberté de 1
                                    plateau[x][y][0].setLiberte(plateau[x][y][0].getLiberte()-1);
                            }
                            else
                                plateau[x][y][0].setCaseLibreAdjacente(true);
                        }
                        else
                            // Si on est sur un bord, on perd automatiquement une liberté
                            plateau[x][y][0].setLiberte(plateau[x][y][0].getLiberte()-1);
                    }
                }
                // Si le jeton ne possède aucune liberté, il est supprimé
                if (plateau[x][y][0].getLiberte() == 0)
                    plateau[x][y].clear();
            }
        }
    }

    for (int x=0 ; x<5 ; x++)
    {
        for (int y=0; y<5 ; y++)
        {
            if (!plateau[x][y].empty())
            {
                //cout << "Cases libres adjacentes de la case [" << x << "][" << y << "] : " << plateau[x][y][0].getCaseLibreAdjacente() << endl;
                if (plateau[x][y][0].getCaseLibreAdjacente() == false)
                {
                    bool mort = true;

                    for (int i=0; i<2; i++)
                    {
                        for (int j=0; j<2; j++)
                        {
                            // Si la case vérifiée est bien dans le tableau
                            if ((((1-i)*x + i*(x-1+2*j))<5) && (((1-i)*x + i*(x-1+2*j))>=0) && ((i*y + (1-i)*(y+1-2*j))<5) && ((i*y + (1-i)*(y+1-2*j)))>=0)
                            {
                                if (plateau[(1-i)*x + i*(x-1+2*j)][i*y + (1-i)*(y+1-2*j)][0].getCouleur() == plateau[x][y][0].getCouleur() &&
                                   (plateau[(1-i)*x + i*(x-1+2*j)][i*y + (1-i)*(y+1-2*j)][0].getCaseLibreAdjacente() == true))
                                    mort = false;
                            }
                        }
                    }

                    if (mort == true)
                        plateau[x][y][0].setDeces(true);

                    cout << "Deces de la case [" << x << "][" << y << "] : " << plateau[x][y][0].getDeces() << endl;
                }
            }
        }
    }

    for (int x=0 ; x<5 ; x++)
    {
        for (int y=0; y<5 ; y++)
        {
            if (!plateau[x][y].empty())
            {
                if (plateau[x][y][0].getDeces() == true)
                    plateau[x][y].clear();
            }
        }
    }
}







