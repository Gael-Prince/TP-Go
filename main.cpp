
#include "gtest/gtest.h"

#include "fonctions.h"
#include "classes.h"





TEST_F(gobantest, enDehorsDuTableauTest)
{
EXPECT_FALSE (goban_test.PlaceLibre(6,6));
EXPECT_FALSE (goban_test.PlaceLibre(-1,-1));
EXPECT_FALSE (goban_test.PlaceLibre(-1,4));
EXPECT_TRUE (goban_test.PlaceLibre(1,1));

}


TEST_F(gobantest, PoseDePierreTest)
{
goban_test.PoserPierre (1,2,2);
EXPECT_FALSE (goban_test.PlaceLibre(2,2));
EXPECT_EQ ('N', goban_test.plateau[2][2][0].getCouleur());
goban_test.PoserPierre (2,3,3);
EXPECT_FALSE (goban_test.PlaceLibre(3,3));
EXPECT_EQ ('B', goban_test.plateau[3][3][0].getCouleur());
}





int main(int argc, char **argv) {

goban goban1 ;
int joueur=1;
int x,y;


testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();


while(1)
{

do
{
cin >> x >> y ;

}
while (!goban1.PlaceLibre(x,y));

goban1.PoserPierre(joueur, x , y);


if (joueur == 1)
joueur =2;
else
joueur =1;

goban1.LibertePierre();

goban1.AfficheGoban();

}





}
