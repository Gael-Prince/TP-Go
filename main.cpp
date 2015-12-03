
#include "gtest/gtest.h"

#include "fonctions.h"
#include "classes.h"

//ceci est le main

/*int addition (int a, int b)
{
return a+b;
}

TEST(SquareRootTest, PositiveNos) {
    EXPECT_EQ (3, addition (1,2));

}*/


int main(int argc, char **argv) {

goban goban1;
int joueur=1;
int x,y;



while(1)
{

do
{
cin >> x >> y;
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

if (!goban1.plateau[2][2].empty())
 cout << goban1.plateau[2][2][0].liberte << endl;

 goban1.AfficheGoban();

}




  /*testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();*/
}
