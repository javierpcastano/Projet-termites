#ifndef COORD_HPP
#define COORD_HPP

#include <stdexcept>
#include <array> 
#include <vector>
#include <string>
#include <iostream>


const int tailleGrille = 20; 

class Coord{
	public :
	//*Constructeurs :

	//*Constructeur à partir d'un numéro de ligne et numéro de colonne
	//*@param lig : numéro de ligne 
	//*@param col : numero de colonne 
	//*@return paire de type Coord
	//*levant exception si les coordonnées sont invalides 
	Coord (int lig, int col);
	
	
	//Méthodes :
	
	int getLig();
	
	int getCol();
	
	private :
	
	std::array<int,2> coordenadas;
};

enum class Direction {nordOuest, nord, nordEst, est, sudEst, sud, sudOuest, ouest};
const array<string, 8> stringCardinaux {"nord-ouest", "nord", "nord-est", "est", "sud-est", "sud", "sud-ouest", "ouest"};


//* Fonctions qui retournent la direction située juste à sa gauche (respectivement a droite)
//* @param[in] D : La direction 
//* return la direction située juste à gauche (resp. droite) de la direction D 
Direction aGauche(Direction D);
Direction aDroite(Direction D);

//*retourne la coordonnée devant une coordonnée donnée dans une direction donnée
//*@param[in] C : coordonée de la grille
//*@param[in] D  : Direction 
//*@return : la coordonnée devant dans la direction donnée
Coord devantCoord(Coord C, Direction D);


//*surcharge d'operateurs 
std::ostream& operator<<(std::ostream& out, Coord C);

bool operator==(Coord A, Coord B);

bool operator!=(Coord A, Coord B);


std::ostream& operator<<(std::ostream& out, Direction D);

#endif