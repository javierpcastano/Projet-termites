// -*- coding: utf-8 -*-
#include <stdexcept>
#include <array>
#include <iostream>
using namespace std;

//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "coord.hpp"
#include "grille.hpp"
#include "termite.hpp"


TEST_CASE("Construction de coordonnées"){
    Coord A = Coord {1,2};
    CHECK(A.getLig() == 1);
    CHECK(A.getCol() == 2);
    CHECK_THROWS_AS(Coord(-1,5), range_error);
    CHECK_THROWS_AS(Coord(0,tailleGrille), range_error);
}

TEST_CASE("Egalité"){
    Coord A{0,0},  B{0,0};
    CHECK(A == B);
    
    A = Coord{1,2};
    B = Coord{2,1};
    CHECK_FALSE(A == B);
    
    A = Coord{0,0};
    B = Coord{0,0};
    CHECK(A == B);

}


TEST_CASE("Cardinaux Gauche Droite"){
    Direction A = Direction::nordOuest,  B = Direction::ouest;
    
    A = aGauche(A);
    A = aDroite(A);
    CHECK(A == Direction::nordOuest);
    
    B = aDroite(B);
    B = aGauche(B);
    CHECK(B == Direction::ouest);
    
    for(int i = 0 ; i < 8 ; i++){
        A = aGauche(A);
        B = aDroite(B);
    }
    CHECK(A == Direction::nordOuest);
    CHECK(B == Direction::ouest);
}


TEST_CASE("Changement de coordonée"){
    Coord A = Coord{0, 5}, B = Coord{5,tailleGrille - 1}, C = Coord{tailleGrille -1 ,0}, D = Coord{tailleGrille - 1, tailleGrille - 1}, E = Coord{4,4}, F = Coord{2,6};
    
    CHECK(devantCoord(F, Direction::est) == Coord{2,7});
    
    
    CHECK(devantCoord(A, Direction::est) == Coord{0,6});
    CHECK(devantCoord(A, Direction::nordOuest) == A);
    
    CHECK(devantCoord(B, Direction::est) == B);
    CHECK(devantCoord(B, Direction::sudEst) == B);
    
    CHECK(devantCoord(C, Direction::sudOuest) == C);
    CHECK(devantCoord(C, Direction::sud) == C);
    
    CHECK(devantCoord(D, Direction::est) == D);
    CHECK(devantCoord(D, Direction::nordEst) == D);
    
    Direction dir = Direction::nordOuest;
    E = devantCoord(E, dir);
    for (int i = 0; i < 4; i++) dir = aDroite(dir);
    E = devantCoord(E, dir);
    
    CHECK(E == Coord{4,4});


}


TEST_CASE("Brindille "){
    Grille G;
    Coord A = Coord{1,2};
    Coord B = Coord{6, 6};
    int nb1 = 1;
    G.poseTermite(B, nb1);
    CHECK(G.estVide(A));
    G.poseBrindille(A);
    CHECK(G.contientBrindille(A));
    G.enleveBrindille(A);
    CHECK(G.estVide(A));
    CHECK_THROWS_AS(G.enleveBrindille(A), runtime_error); //vide
    CHECK_THROWS_AS(G.enleveBrindille(B), runtime_error); //termite
}

TEST_CASE("Termite "){
    Grille G;
    int nb = 8;
    Coord A = Coord{3,2}, B = Coord{4,2};
    CHECK(G.estVide(A));
    G.poseTermite(A, nb);
    CHECK_FALSE(G.contientBrindille(A));
    CHECK_FALSE(G.estVide(A));
    CHECK(G.numéroTermite(A) == nb);
    G.enleveTermite(A);
    CHECK(G.estVide(A));  
    CHECK_THROWS_AS(G.enleveTermite(B), runtime_error); //vide
    CHECK_THROWS_AS(G.numéroTermite(B), runtime_error); //vide

}


TEST_CASE("Comportement termites"){
    srand((unsigned) time(NULL));

    Grille G;
    Coord A = Coord{3, 5};
    int idTer = 4;
    Termite T = Termite(A, idTer);
    Direction D = T.directionTermite();
    CHECK(T.idTermite() == idTer);
    int d = int(D)-1;
    
    Coord B = Coord{0, 0};
    int idTer1 = 6;
    Termite T1 = Termite(B, idTer1);
    
    int Nord = int(Direction(1));
    
    T.tourneAGauche();
    if (int(D) == 0)
        d = 7;
    CHECK(int(T.directionTermite()) == d);
    T.tourneADroite();
    CHECK(T.directionTermite() == D);
    CHECK_FALSE(T.porteBrindille());
    for(int i = 0 ; i < 8 ; i++){
        T.tourneADroite();
    }
    CHECK(T.directionTermite() == D);
    for(int i = 0 ; i < 8 ; i++){
        T.tourneAGauche();
    }
    CHECK(T.directionTermite() == D);
    
    T.tourneAleat();
    Direction D1 = T.directionTermite();
    CHECK(T.directionTermite() == D1);
    
    while (int(T1.directionTermite()) != Nord){
        T1.tourneADroite();
    }
    CHECK(int(T1.directionTermite()) == Nord);


}

TEST_CASE("voisins termites + charge brind"){
    Grille G;
    Coord A = Coord{4, 4}, B = Coord{6, 6}, C = Coord{5,5}, D = Coord{5, 4}, E = Coord{5, 6}, F = Coord{4, 5}, J = Coord{6, 5}, H = Coord{4, 6}, I = Coord{6, 4}, cbrindille = Coord{3, 4};
    
    int nb1 = 1;
    int nb2 = 2;
    int nb3 = 3;
    int nb4 = 4;
    int nb5 = 5;
    int nb6 = 6;
    int nb7 = 7;
    int nb8 = 8;
    int nb9 = 9;
    
    Termite T = Termite(C, nb3);
    Termite T1 = Termite(A, nb1);
    
    G.poseTermite(A, nb1);
    G.poseTermite(B, nb2);
    G.poseTermite(C, nb3);
    G.poseTermite(D, nb4);
    G.poseTermite(E, nb5);
    G.poseTermite(F, nb6);
    G.poseTermite(J, nb7);
    G.poseTermite(H, nb8);
    G.poseTermite(I, nb9);
    
    
    
    CHECK(T.voisinsLibre(G) == 0);
    //CHECK(T.voisinsLibre(G) == 5);
    
    int Nord = int(Direction(1));
    while (int(T1.directionTermite()) != Nord){
        T1.tourneADroite();
    }
    G.poseBrindille(cbrindille);
    T1.chargeBrindille(G);
    CHECK(T1.porteBrindille());
    T1.dechargeBrindille(G);
    CHECK_FALSE(T1.porteBrindille());


}



int main(int argc, const char **argv) {
    doctest::Context context(argc, argv);
    int test_result = context.run();
    if (context.shouldExit()) return test_result;

    Coord A = Coord{4,2};
    cout << A;
 
    return EXIT_SUCCESS;
}
