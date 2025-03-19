#include <cstdlib>
#include <stdexcept>
using namespace std;

#include "termite.hpp"


Termite::Termite(Coord cor, int idTerm) : idT{idTerm}, C{cor}, D{Direction(rand()%8)}, B{false}, Sablier{0}, groupe{idTerm % nbNids}, Pheromone{0}{}


string Termite::toString() const {
    string s;
    switch(int(D)){
        case 0 : case 4 : s = " \\ "; break;
        case 1 : case 5 : s = " | "; break;
        case 2 : case 6 : s = " / "; break;
        case 3 : case 7 : s = " - "; break;
    }
    return s;
}


Direction Termite::directionTermite() const{
    return D;
}


Coord Termite::coordTermite() const{
    return C;    
} 


Coord Termite::devant() const{
    return devantCoord(C, D);
} 


bool Termite::porteBrindille(){
    return B;
}


void Termite::tourneADroite(){
    D = aDroite(D);
}


void Termite::tourneAGauche(){
    D = aGauche(D);
}


void Termite::tourneAleat(){
    int aleat = rand()%2;
    if(aleat) tourneADroite();
    else tourneAGauche();
}


int Termite::voisinsLibre(Grille G){
    int libre = 0;
    Direction direccion = D;
    for(int i = 0; i < 8; i++){
        Coord caseLibre = devantCoord(C, direccion);
        if(G.estVide(caseLibre)) libre++;
        direccion = aDroite(direccion);
    }
    return libre;
}


bool Termite::avance(Grille &G){
    if(laVoieEstLibre(G, *this)){
        Coord temp = C;
        C = devantCoord(C, D);
        G.poseTermite(C, idT);
        G.enleveTermite(temp);
        return true;
    }
    return false;
}

void Termite::marcheAleatoire(Grille &G){
    if(rand()%100 + 1 <=  probaTourner[groupe]*100){
        tourneAleat();
    }else if(laVoieEstLibre(G, *this)){
        avance(G);
    }else tourneAleat();

}


void Termite::chargeBrindille(Grille &G){
    if(brindilleEnFace(G, *this)){
        B = true;
        Sablier = dureeSablier[groupe];
        G.enleveBrindille(devantCoord(C, D));
    }

}


void Termite::dechargeBrindille(Grille &G){
    if(laVoieEstLibre(G, *this)){
        poseBrindilleNid(G, devantCoord(C, D), *this);
        B = false;
        Sablier = dureeSablier[groupe];
    }

}


void Termite::vieTermite(Grille &G, bool &girar) {
    // Termite con brindille : 
    if(porteBrindille()){
        if(girar){
            if(laVoieEstLibre(G, *this)){
                dechargeBrindille(G);
                girar = false;
                tourneAleat();
            }
        }
        
        //Si ya paso dureeSablier 
        if(Sablier <= 0){
            // Brindille NEUTRE en face (contrainte 1) ? 
            if(brindilleEnFace(G, *this) || nidEnFace(G, *this)) {
                girar = true;
                tourneAleat();
            }else{
                // si no girar o avanzar en busca de lugar libre
                marcheAleatoire(G);
            }
        }else{
            // O si Sablier no es suficiente 
            marcheAleatoire(G);
            Sablier--;
        }
    }
    
    // Termite sin brindille :
    if(!porteBrindille()){
        //Si hay brindille enfrente
        if(brindilleEnFace(G, *this)){
            // Se puede recoger la brindille ? 
            if(Sablier <= 0){
                chargeBrindille(G);
            }else{
                // si no ha dado suficientes pasos
                marcheAleatoire(G);
                Sablier--;
            }
        }else{
            // Si no tiene Brindille y no hay nada enfrente
            marcheAleatoire(G);
        }
    }


}

int Termite::idTermite() const{
    return idT;
}


int Termite::getSab() {
    return Sablier;
}

int Termite::getGroupe() {
    return groupe;
}

int Termite::getPheromone() {
    return Pheromone;
}


void Termite::setPheromone(int n){
    Pheromone = n;
}

bool laVoieEstLibre(Grille G, Termite T) {
    return G.estVide(devantCoord(T.coordTermite(), T.directionTermite()));
}


bool brindilleEnFace(Grille G, Termite &T) {
    int groupe = T.getGroupe();
    int cont = G.getObj(devantCoord(T.coordTermite(), T.directionTermite()));
    switch(cont){
        case -15: if(groupe == 0) T.setPheromone(-15); break;
        case -12: if(groupe == 1) T.setPheromone(-12); break;
        case -9: if(groupe == 2) T.setPheromone(-9); break;
        case -6: if(groupe == 3) T.setPheromone(-6); break;
        default : T.setPheromone(0); break;
    }
    return G.contientBrindille(devantCoord(T.coordTermite(), T.directionTermite()));
}

bool nidEnFace(Grille G, Termite &T) {
    bool ok = false;
    int groupe = T.getGroupe();
    int cont = G.getObj(devantCoord(T.coordTermite(), T.directionTermite()));
    switch(cont){
        case -5: if((groupe == 0) && T.porteBrindille()) T.setPheromone(-15); ok = true; break;
        case -4: if((groupe == 1) && T.porteBrindille()) T.setPheromone(-12); ok = true; break;
        case -3: if((groupe == 2) && T.porteBrindille()) T.setPheromone(-9); ok = true; break;
        case -2: if((groupe == 3) && T.porteBrindille()) T.setPheromone(-6); ok = true; break;
    }
    return ok;
}



void poseBrindilleNid(Grille &G, Coord C, Termite T){
	int Lig = C.getLig(), Col = C.getCol();
    Coord c{Lig, Col};
	if(G.estVide(c)){
    	G.poseCont(c, T.getPheromone());
    }
}



std::ostream& operator<<(std::ostream& out, Termite T){
    out << "ID : " << setw(2) << T.idTermite() << " | Coord : " << T.coordTermite() << " | Dir : " << T.directionTermite() << " | Brind : " << T.porteBrindille() << " | Sab : " << T.getSab() << " | Grp : " << T.getPheromone(); 
    return out;
}

