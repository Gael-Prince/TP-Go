#include "gtest/gtest.h"
#include "classes.h"

// Les tests :

TEST_F(gobantest, enDehorsDuTableauTest)
{
    //test des limites du goban
    EXPECT_FALSE (goban_test.PlaceLibre(6,6,1));
    EXPECT_FALSE (goban_test.PlaceLibre(-1,-1,2));
    EXPECT_FALSE (goban_test.PlaceLibre(-1,4,1));
    EXPECT_TRUE (goban_test.PlaceLibre(1,1,1));

    // test de l'anti suicide dans le coin (coin)
    goban_test.PoserPierre (1,0,1);
    goban_test.PoserPierre (1,1,0);
    EXPECT_FALSE (goban_test.PlaceLibre(0,0,2));

    //test de l'anti suicide entre 4 pierres
    goban_test.PoserPierre (1,1,2);
    goban_test.PoserPierre (1,2,1);
    EXPECT_FALSE (goban_test.PlaceLibre(1,1,2));
}

// test permettant de vérifier que lorsqu'on on joue une pierre, elle est effectivement posée et que la couleur de cette pierre est bien la couleur du joueur


TEST_F(gobantest, PoseDePierreTest)
{
    goban_test.PoserPierre (1,2,2);
    EXPECT_FALSE (goban_test.PlaceLibre(2,2,2));
    EXPECT_EQ ('N', goban_test.plateau[2][2][0].getCouleur());
    goban_test.PoserPierre (2,3,3);
    EXPECT_FALSE (goban_test.PlaceLibre(3,3,1));
    EXPECT_EQ ('B', goban_test.plateau[3][3][0].getCouleur());
}


// test permettant de vérifier que la pierre se supprime si elle n'a plus de liberté (ce qui vérifie en même temps que le calcul de libertés est correct

TEST_F(gobantest, LibertePierreEncercle)
{
    // test de la prise d'une pierre encerclé par quatre pierres
    // la pierre du joueur 1
    goban_test.PoserPierre (1,2,2);
    //encercler par 4 pierres du joueur 2 : on pose toutes les pierres sauf une
    goban_test.PoserPierre (2,2,3);
    goban_test.PoserPierre (2,3,2);
    goban_test.PoserPierre (2,1,2);

    goban_test.LibertePierre();
    // on verifie que la pierre du joueur 1 est toujours présente sur le goban
    EXPECT_FALSE (goban_test.plateau[2][2].empty());

    // on pose la dernière pierre
    goban_test.PoserPierre (2,2,1);
    goban_test.LibertePierre();
    // on verifie que la pierre du joueur 1 n'est plus présente sur le goban
    EXPECT_TRUE (goban_test.plateau[2][2].empty());
}

TEST_F(gobantest, LibertePierreCoin)
{
    // test de prise de pierre dans un coin(coin)
    // la pierre du joueur 1
    goban_test.PoserPierre (1,0,0);
    //encercler par 2 pierres du joueur 2 et un coin(coin) : on pose la première pierre
    goban_test.PoserPierre (2,0,1);

    goban_test.LibertePierre();
    // on verifie que la pierre du joueur 1 est toujours présente sur le goban
    EXPECT_FALSE (goban_test.plateau[0][0].empty());

    // on pose la second epierre
    goban_test.PoserPierre (2,1,0);
    goban_test.LibertePierre();
    // on verifie que la pierre du joueur 1 n'est plus présente sur le goban
    EXPECT_TRUE (goban_test.plateau[0][0].empty());
}

TEST_F(gobantest, LiberteGroupeEncercle)
{
    // test de prise d'un groupe de 2 pierres encerclées
    // les pierres du joueur 1
    goban_test.PoserPierre (1,1,2);
    goban_test.PoserPierre (1,2,2);
    //encercler par 6 pierres du joueur 2 : on pose toutes les pierres sauf une
    goban_test.PoserPierre (2,0,2);
    goban_test.PoserPierre (2,1,1);
    goban_test.PoserPierre (2,2,1);
    goban_test.PoserPierre (2,1,3);
    goban_test.PoserPierre (2,2,3);
    //on verifie que les pierres du joueur 1 sont toujours présentes sur le goban
    goban_test.LibertePierre();
    EXPECT_FALSE (goban_test.plateau[1][2].empty());
    EXPECT_FALSE (goban_test.plateau[2][2].empty());

    //on pose la dernière pierre
    goban_test.PoserPierre (2,3,2);
    goban_test.LibertePierre();
    // on verifie que les pierres du joueur 1 ne sont plus présentes sur le goban
    EXPECT_TRUE (goban_test.plateau[1][2].empty());
    EXPECT_TRUE (goban_test.plateau[2][2].empty());
}

TEST_F(gobantest, LiberteGroupeCoin)
{
    // test de prise d'un groupe de 2 pierres encerclées et dans un coin(coin)
    // les pierres du joueur 1
    goban_test.PoserPierre (1,0,0);
    goban_test.PoserPierre (1,1,0);
    //encercler par 3 pierres du joueur 2 et un coin, on pose toutes les pierres sauf une
    goban_test.PoserPierre (2,0,1);
    goban_test.PoserPierre (2,1,1);

    goban_test.LibertePierre();
    // on verifie que les pierres du joueur 1 sont toujours présentes sur le goban
    EXPECT_FALSE (goban_test.plateau[0][0].empty());
    EXPECT_FALSE (goban_test.plateau[1][0].empty());

    // on pose la dernière pierre
    goban_test.PoserPierre (2,2,0);
    goban_test.LibertePierre();
    // on verifie que les pierres du joueur 1 ne sont plus présentes sur le goban
    EXPECT_TRUE (goban_test.plateau[0][0].empty());
    EXPECT_TRUE (goban_test.plateau[1][0].empty());
}

TEST_F(gobantest, LiberteGroupeTrois)
{
    // test de prise d'un groupe de 2 pierres encerclées
    // les pierres du joueur 1
    goban_test.PoserPierre (1,1,2);
    goban_test.PoserPierre (1,2,2);
    goban_test.PoserPierre (1,3,2);
    //encercler par 6 pierres du joueur 2 : on pose toutes les pierres sauf une
    goban_test.PoserPierre (2,0,2);
    goban_test.PoserPierre (2,1,1);
    goban_test.PoserPierre (2,2,1);
    goban_test.PoserPierre (2,1,3);
    goban_test.PoserPierre (2,2,3);
    goban_test.PoserPierre (2,3,1);
    goban_test.PoserPierre (2,3,3);
    //on verifie que les pierres du joueur 1 sont toujours présentes sur le goban
    goban_test.LibertePierre();
    EXPECT_FALSE (goban_test.plateau[1][2].empty());
    EXPECT_FALSE (goban_test.plateau[2][2].empty());
    EXPECT_FALSE (goban_test.plateau[3][2].empty());

    //on pose la dernière pierre
    goban_test.PoserPierre (2,4,2);
    goban_test.LibertePierre();
    // on verifie que les pierres du joueur 1 ne sont plus présentes sur le goban
    EXPECT_TRUE (goban_test.plateau[1][2].empty());
    EXPECT_TRUE (goban_test.plateau[2][2].empty());
    EXPECT_TRUE (goban_test.plateau[3][2].empty());
}







int main(int argc, char **argv)
{

    goban goban1 ;
    int joueur=1;
    int x,y;

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

// Au cas ou on veut jouer on commente la ligne précédente et ça marche
    while(1)
    {
        do
        {
            // on demande l'endroit où le joueur veut poser la pierre
            cin >> x >> y ;
        }


        while (!goban1.PlaceLibre(x, y, joueur));
        goban1.PoserPierre(joueur, x , y);

// lorsque le joueur propose une place libre, on pose la pierre
// alternance des tours

        if (joueur == 1)
            joueur =2;
        else
            joueur =1;

// on met à jour les libertés -> permet de supprimer la pierre si elle est encerclée (ne marche pas si un groupe de pierre est encerclé)
        goban1.LibertePierre();

// on affihe le goban
        goban1.AfficheGoban();
    }

}



