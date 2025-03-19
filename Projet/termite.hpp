#ifndef TERMITE_HPP
#define TERMITE_HPP

using namespace std;
#include <string>
#include <iomanip>

#include "grille.hpp"
#include "coord.hpp"


//extern vector<Termite> termiteVector; // variable globale pour stocké les Termites 

const float densiteBrindille = 0.20;
const int nbTermites = 64;
const int nbCases = tailleGrille * tailleGrille;
const int nbBrindilles = nbCases * densiteBrindille;



const array<float, 4> probaTourner = {.65, .90, .10, .35}; // ProbaTourner différentes pour chque groupe 
const array<int, 4> dureeSablier = {4, 2, 8, 6}; // dureeSablier différentes pour chque groupe 

//const int dureeSablier = 6;
const int nbNids = 4;


struct Brindille{
    //* Si -1 alors la brindille est neutre 
    int groupe; 
};


class Termite{
    
    public : 
    
    //* constructeurs :
    Termite(Coord cor, int idTerm);
    
    //* Méthodes : 
    void tourneSurPlace(Grille &G);
    
    int idTermite() const;
    
    //* convertit l'animal en chaîne de caractères pour l'affichage.
    string toString() const;
    
    //* renvoie la direction du Termite.
    Direction directionTermite() const;
    
    //* renvoie les coordonnées du termite
    Coord coordTermite() const; 
    
    //* renvoie les coordonnées de la case devant le termite
    Coord devant() const; 
    
    //* renvoie si le termite porte une brindille
    bool porteBrindille();

    //* fait tourner le termite à droite
    void tourneADroite();
    
    //* fait tourner le termite à gauche
    void tourneAGauche();
    
    //* fait tourner le termite dans un sens aléatoire
    void tourneAleat();
        
    //* renvoie le nombre de cases libre autour du termite
    int voisinsLibre(Grille G);
    
    //* avance le termite
    bool avance(Grille &G);
        
    //* déplace aléatoirement le termite
    void marcheAleatoire(Grille &G);
        
    //* le termite prend une brindille
    void chargeBrindille(Grille &G);
        
    //* le termite pose une brindille
    void dechargeBrindille(Grille &G);
      
    //* algorithme du termite
    void vieTermite(Grille &G, bool &girar);
    
    void afficherMonde(Grille G, vector<Termite> vT);

    int getSab(); 
    
    int getGroupe();
    
    int getPheromone();
    
    void setPheromone(int n);
    
    
        
    private : 
    
    //* atributs 
    int const idT;
    Coord C;
    Direction D;
    bool B;
    int Sablier;
    int groupe;
    int Pheromone; // Poser Brindille -> poner la feromona 
    
};


std::ostream& operator<<(std::ostream& out, Grille G);
std::ostream& operator<<(std::ostream& out, Termite T);



 //renvoie si la case devant le termite est libre
bool laVoieEstLibre(Grille G, Termite T);

 //renvoie si la case devant le termite  contient une brindille
bool brindilleEnFace(Grille G, Termite &T);

bool nidEnFace(Grille G, Termite &T);

void poseBrindilleNid(Grille &G, Coord c, Termite T);

#endif