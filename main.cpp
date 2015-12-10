#include "gtest/gtest.h"


#include "classes.h"

// test permettant de vérifier qu'on ne peut placer une pierre en dehors du goban


TEST_F(gobantest, enDehorsDuTableauTest)
{
    EXPECT_FALSE (goban_test.PlaceLibre(6,6));
    EXPECT_FALSE (goban_test.PlaceLibre(-1,-1));
    EXPECT_FALSE (goban_test.PlaceLibre(-1,4));
    EXPECT_TRUE (goban_test.PlaceLibre(1,1));

}

// test permettant de vérifier que lorsqu'on on joue une pierre, elle est effectivement posée et que la couleur de cette pierre est bien la couleur du joueur


TEST_F(gobantest, PoseDePierreTest)
{
    goban_test.PoserPierre (1,2,2);
    EXPECT_FALSE (goban_test.PlaceLibre(2,2));
    EXPECT_EQ ('N', goban_test.plateau[2][2][0].getCouleur());
    goban_test.PoserPierre (2,3,3);
    EXPECT_FALSE (goban_test.PlaceLibre(3,3));
    EXPECT_EQ ('B', goban_test.plateau[3][3][0].getCouleur());
}


// test permettant de vérifier que la pierre se supprime si elle n'a plus de liberté (ce qui vérifie en même temps que le calcul de libertés est correct

TEST_F(gobantest, LibertePierreTest)
{
    goban_test.PoserPierre (1,2,2);
    goban_test.PoserPierre (2,2,3);
    goban_test.PoserPierre (2,3,2);
    goban_test.PoserPierre (2,1,2);
    goban_test.PoserPierre (2,2,1);

    goban_test.LibertePierre();

    EXPECT_TRUE (goban_test.plateau[2][2].empty());

}





int main(int argc, char **argv)
{

    goban goban1 ;
    int joueur=1;
    int x,y;

    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    while(1)
    {
        do
        {
            // on demande l'endroit où le joueur veut poser la pierre
            cin >> x >> y ;
        }


        while (!goban1.PlaceLibre(x, y));
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



