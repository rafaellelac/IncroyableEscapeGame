#include <iostream>
#include <string>
#include <vector>
#include "Position.hh"

using namespace std;

class Personnage {
    string prenom;
    string temps;
    Position position;

    public : 
        Personnage(string prenom, string temps, Position position) : prenom(prenom), temps(temps), position(position) {}

        void deplacer(int x, int y) {
        }
        

};