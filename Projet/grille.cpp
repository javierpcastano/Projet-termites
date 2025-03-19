// -*- coding: utf-8 -*-
#include <iostream>
#include <stdexcept>

using namespace std;

#include "grille.hpp"


Case::Case() : contenu{-1} {};

bool Grille::estVide(Coord c) const{
    int Lig = c.getLig(), Col = c.getCol();
    int cont = tab2D[Lig][Col].contenu;
    if(cont == -1)return true;
    return false;
}

bool Grille::contientBrindille(Coord c) const{
    int Lig = c.getLig(), Col = c.getCol();
    return(!tab2D[Lig][Col].contenu);
}

void Grille::poseBrindille(Coord c){ //* vérifie q la case s vide
	int Lig = c.getLig(), Col = c.getCol();
	if(estVide(c)){
    	tab2D[Lig][Col].contenu = 0;
    }
}

void Grille::enleveBrindille(Coord c){
    int Lig = c.getLig(), Col = c.getCol();
    if(estVide(c)) throw runtime_error("Case vide");
    if(contientBrindille(c)){
        tab2D[Lig][Col].contenu = -1;
    }else throw runtime_error("Case avec termite");   
}

void Grille::poseNid(Coord c, int Groupe){ //* vérifie q la case s vide
	int Lig = c.getLig(), Col = c.getCol();
	if(estVide(c)){
    	tab2D[Lig][Col].contenu = Groupe;
    }
}


void Grille::poseCont(Coord c, int cont){ //* vérifie q la case s vide
	int Lig = c.getLig(), Col = c.getCol();
	if(estVide(c)){
    	tab2D[Lig][Col].contenu = cont;
    }
}


void Grille::poseTermite(Coord c, int idT){
    int Lig = c.getLig(), Col = c.getCol();
    if(!estVide(c)) throw runtime_error("Case non vide");
    tab2D[Lig][Col].contenu = idT;
}

void Grille::enleveTermite(Coord c){
    int Lig = c.getLig(), Col = c.getCol();
    if(estVide(c)) throw runtime_error("Case vide");
    if(contientBrindille(c)){
        throw runtime_error("Case avec brindille");   
    }else{
    	tab2D[Lig][Col].contenu = -1;
    }
} //* vérif case contient 

int Grille::numéroTermite(Coord c) const{
	int Lig = c.getLig(), Col = c.getCol();
    if(estVide(c)) throw runtime_error("Case vide");
    if(contientBrindille(c)) throw runtime_error("Case avec brindille");   
    
    return tab2D[Lig][Col].contenu;  
}

int Grille::getObj(Coord c) const{
    int Lig = c.getLig(), Col = c.getCol();
    int num = tab2D[Lig][Col].contenu;
    return num;
}



Grille::Grille() : tab2D{Case()}{}




