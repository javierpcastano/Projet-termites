#include <iostream>
#include <stdexcept>



using namespace std;
#include "coord.hpp"


// *Coord::Coord() : coordenadas{} {}

Coord::Coord(int lig, int col){
	if(lig < 0 || lig >= tailleGrille) throw range_error("Indice de ligne invalide");
	if(col < 0 || col >= tailleGrille) throw range_error("Indice de colonne invalide");
	coordenadas[0] = lig;
	coordenadas[1] = col;
};


int Coord::getLig(){return coordenadas[0];}
int Coord::getCol(){return coordenadas[1];}


std::ostream& operator<<(std::ostream& out, Coord C){
	int Lig = C.getLig(); 
	int Col = C.getCol();
	out << "(" << Lig << "," << Col << ")" ;
	return out;
}


bool operator==(Coord A, Coord B){
    int LigA = A.getLig(), ColA = A.getCol(), LigB = B.getLig(), ColB = B.getCol(); 
    return ((LigA == LigB) && (ColA == ColB));
}

bool operator!=(Coord A, Coord B){
    return (not(A == B));
}


std::ostream& operator<<(std::ostream& out, Direction D){
    out << stringCardinaux[int(D)];
    return out;
}


Direction aGauche(Direction D){
    int idx = int(D);
    if(idx == 0) return Direction(7);
    return Direction(idx-1);
}


Direction aDroite(Direction D){
    int idx = (int(D)+1)%8;
    return Direction(idx);
}


Coord devantCoord(Coord C, Direction D){
    int idxY = C.getLig(), idxX = C.getCol();

    switch(D){
        case Direction::nordOuest : idxX --, idxY --; break;
        case Direction::nord : idxY --; break;
        case Direction::nordEst :  idxX ++, idxY --; break;
        case Direction::est : idxX ++; break;
        case Direction::sudEst : idxX ++, idxY ++; break;
        case Direction::sud : idxY ++; break;
        case Direction::sudOuest : idxX --, idxY ++; break;
        case Direction::ouest : idxX --; break;     
    }
    try{
        Coord res = Coord{idxY, idxX};
        return res;
    }catch(...) {
        return C;
    }

}
