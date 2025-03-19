#ifndef GRILLE_HPP
#define GRILLE_HPP


#include <cstdlib>
#include <stdexcept>

#include "coord.hpp"



class Termite;

struct Case{
    //* attributs
    int contenu;
    
    //* contructeurs 
    Case();
};



class Grille{
    
    public :
    
    //* méthodes :
    
    void poseBrindille(Coord c);
    
    void poseNid(Coord c, int Groupe);
    
    void poseCont(Coord c, int cont);
    
    void enleveBrindille(Coord c);
    
    bool contientBrindille(Coord c) const;
    
    void poseTermite(Coord c, int idT);
    
    void enleveTermite(Coord c);
    
    int numéroTermite(Coord c) const;
    
    bool estVide(Coord c) const;
    
    int getObj(Coord c) const; 
    
    Grille();
    

    private : 
    //*attributs
    array<array<Case,tailleGrille>,tailleGrille> tab2D;
    
};


#endif