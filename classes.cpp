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


    for (int i=0 ; i<5 ; i++)
    {
        for (int j=0; j<5 ; j++)
        {
            if (!plateau[i][j].empty()) // pour chaque case non vide : on calcule le nombre de libertés
            {
                //on initialise la liberté à 4, et on la diminue si besoin après
                plateau[i][j][0].setLiberte(4);

                // case à droite
                if (j<4) // si il y a une case à droite
                {
                    if (!plateau[i][j+1].empty())
                    {
                        if (plateau[i][j+1][0].getCouleur() != plateau[i][j][0].getCouleur())
                        {
                            // on diminue la liberté de 1 si il y a une pierre de couleur adverse sur cette case

                            plateau[i][j][0].setLiberte(plateau[i][j][0].getLiberte()-1);
                        }
                    }
                }
                else
                    // si on est sur un bord, on perd automatiquement une liberté
                    plateau[i][j][0].setLiberte(plateau[i][j][0].getLiberte()-1);

                // case à gauche : même principe
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

                // case en haut : même principe
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


                // case en bas : même principe
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

// une fois le nombre de libertés calculé : si une pierre n'a plus de liberté, on la supprime






                if (plateau[i][j][0].getLiberte() == 0)
                {

                    plateau[i][j].clear();

                }

            }
        }
    }

}








