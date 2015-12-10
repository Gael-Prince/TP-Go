
#include "gtest/gtest.h"

#include "fonctions.h"
#include "classes.h"


/*int addition (int a, int b)
{
return a+b;
}

TEST(SquareRootTest, PositiveNos) {
    EXPECT_EQ (3, addition (1,2));

}
*/




TEST_F(gobantest, enDehorsDuTableauTest)
{
EXPECT_EQ (false,goban_test.PlaceLibre(6,6));
EXPECT_EQ (false,goban_test.PlaceLibre(-1,-1));
EXPECT_EQ (false,goban_test.PlaceLibre(-1,4));
EXPECT_EQ (true,goban_test.PlaceLibre(1,1));
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
x-= 1;
y-= 1;
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
