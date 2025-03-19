// -*- coding: utf-8 -*-
#include <iostream>
#include <stdexcept>

using namespace std;
#include <unistd.h>
#include "termite.hpp"


Grille grilleRandom(vector<Termite>&termiteVector){
    Grille G;
    
	int comptBrindille = 0, comptTermi = 1;
    
    Coord nid1{rand()%tailleGrille, 0};
    Coord nid2{rand()%tailleGrille, tailleGrille - 1};
    Coord nid3{0, rand()%tailleGrille};
    Coord nid4{tailleGrille - 1, rand()%tailleGrille};
    
    G.poseNid(nid1, -2);
    G.poseNid(nid2, -3);
    G.poseNid(nid3, -4);
    G.poseNid(nid4, -5);
    

    while(comptBrindille < nbBrindilles){
        int idxX = rand()%tailleGrille;
        int idxY = rand()%tailleGrille;
        Coord c{idxX, idxY};
        if (G.estVide(c)){
            G.poseBrindille(c);
            comptBrindille ++;
        }
    }
    
    while(comptTermi <= nbTermites){
    int idxX = rand()%tailleGrille;
    int idxY = rand()%tailleGrille;
    Coord c{idxX, idxY};
    if (G.estVide(c)){
        termiteVector.push_back(Termite(c, comptTermi));
        G.poseTermite(c, comptTermi);
        comptTermi++;
        }
    }
    
    
    
	return G;
}


void afficherMonde(Grille &G, vector<Termite> vT){
    for (int i = 0; i < tailleGrille; i++) {
        for (int j = 0; j < tailleGrille; j++) {
            int cont = G.getObj(Coord(i,j));
            switch(cont){
                //Nids
                case -5 : cout <<"\033[30;41m"<< " # "<<  "\033[0m"; break; // equipe rouge  
                case -4 : cout <<"\033[30;43m"<< " # "<<  "\033[0m"; break; // equipe jaune    
                case -3 : cout <<"\033[30;46m"<< " # "<<  "\033[0m"; break; // equipe cyan   
                case -2 : cout <<"\033[30;47m"<< " # "<<  "\033[0m"; break; //equipe gris 

                case -1 : cout <<"\033[40m"<< "   "<<  "\033[0m"; break;
               
                    //Brindilles 
                case 0 : cout <<"\033[32m"<< " * "<<  "\033[0m"; break;
                case -15 : cout <<"\033[31m"<< " * "<<  "\033[0m"; break; // equipe rouge
                case -12 : cout <<"\033[33m"<< " * "<<  "\033[0m"; break; // equipe jaune
                case -9 : cout <<"\033[36m"<< " * "<<  "\033[0m"; break; // equipe cyan
                case -6 : cout <<"\033[37m"<< " * "<<  "\033[0m"; break; //equipe gris 
                default : 
                    for (Termite termite : vT) {
                        if (termite.idTermite() == cont) {
                            int grp = termite.getGroupe();
                            switch(grp){
                                case 0: cout << "\033[31;1m" << termite.toString() << "\033[0m"; break; // groupe rouge 
                                case 1: cout << "\033[33;1m" << termite.toString() << "\033[0m"; break; // groupe jaune
                                case 2: cout << "\033[36;1m" << termite.toString() << "\033[0m"; break; // groupe cyan
                                case 3: cout << "\033[37;1m" << termite.toString() << "\033[0m"; break; // groupe gris
                            }break;
                            
                        }
                    };break;

            }
        }
        cout << endl;
    }
}

void countPoints(Grille G){
    int neutre = nbBrindilles, grRouge = 0, grJaune = 0, grCyan = 0, grGris = 0; 
    
    for (int i = 0; i < tailleGrille; i++) {
        for (int j = 0; j < tailleGrille; j++) {
            int cont = G.getObj(Coord(i,j));
            switch(cont){
                case -15 : grRouge++; break; // equipe rouge
                case -12 : grJaune++; break; // equipe jaune
                case -9 : grCyan++; break; // equipe cyan
                case -6 : grGris++; break; //equipe gris
            }
        }
    }
    
    neutre -= (grRouge + grJaune + grCyan + grGris);
    cout << "Points -> Neutre : " << neutre << " | Rouges : " << grRouge << " | Jaunes : " << grJaune << " | Cyans : " << grCyan << " | Gris : " << grGris << endl;
}


void Gagnant(Grille G){
    int grRouge = 0, grJaune = 0, grCyan = 0, grGris = 0; 
    for (int i = 0; i < tailleGrille; i++) {
        for (int j = 0; j < tailleGrille; j++) {
            int cont = G.getObj(Coord(i,j));
            switch(cont){
                case -15 : grRouge++; break; // equipe rouge
                case -12 : grJaune++; break; // equipe jaune
                case -9 : grCyan++; break; // equipe cyan
                case -6 : grGris++; break; //equipe gris
            }
        }
    }
   	if(grRouge > grJaune && grRouge > grCyan && grRouge > grGris) cout <<  " Les Rouges ont gagné ! " << endl;
    else if(grJaune > grRouge && grJaune > grCyan && grJaune > grGris) cout <<  " Les Jaunes ont gagné ! " << endl;
    else if(grCyan > grJaune && grCyan > grRouge && grCyan > grGris) cout <<  " Les Cyan ont gagné ! " << endl;
    else if(grGris > grJaune && grGris > grCyan && grGris > grRouge) cout <<  " Les Gris ont gagné ! " << endl;
    else cout <<  " Il y a une égalité ! " << endl;
}

int main(){
    srand((unsigned) time(NULL));
    
    vector<Termite> termiteVector;
    char c;
    int Tour = 0;
    bool girar = false;
    
    Grille G = grilleRandom(termiteVector);
    
    cout << "Appuyez \"m\" pour activer le mode manuel ou \"a\" pour le mode automatique. " << endl;
    c = getchar();
    if(c == 'm'){
        do{
            cout << "Appuyez \"Enter\" pour continuer ou une autre touche pour quitter ";
            c = getchar();
            cout << "Tour : " << Tour << endl;
            countPoints(G);
            afficherMonde(G,termiteVector);
            Tour++;
            for(long unsigned int i = 0; i < termiteVector.size(); i++){
                termiteVector[i].vieTermite(G, girar);

            }
        }while( c == '\n');
    }else if(c == 'a'){
        for(int i  = 0; i <= 15000; i ++){
            usleep(15000);
            countPoints(G);
            Tour = i;
            cout << "Tour : " << Tour << endl;
            afficherMonde(G,termiteVector);
            for(long unsigned int i = 0; i < termiteVector.size(); i++){
                termiteVector[i].vieTermite(G, girar);

            }
        }
    }else {
        cout << "Touche invalide !" << endl;
        return EXIT_SUCCESS;
    }
    
    
    
    
    
    
    
    Gagnant(G);
  	cout << "---------------------------------------------" << endl;
    cout << "Paramètres du groupe Rouge :  DureeSablier : " << dureeSablier[0] << " | ProbaTourner : " << probaTourner[0] <<endl;
    cout << "Paramètres du groupe Jaune :  DureeSablier : " << dureeSablier[1] << " | ProbaTourner : " << probaTourner[1] <<endl;
    cout << "Paramètres du groupe Cyan :  DureeSablier : "  << dureeSablier[2] << " | ProbaTourner : " << probaTourner[2] <<endl;
    cout << "Paramètres du groupe Gris :  DureeSablier : "  << dureeSablier[3] << " | ProbaTourner : " << probaTourner[3] <<endl;
    
    return EXIT_SUCCESS;
}
