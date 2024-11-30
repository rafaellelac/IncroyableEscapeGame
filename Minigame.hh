#include <iostream>
#include <string>
//une classe abstraite de laquelle les différents jeux de l'escape game héritent 
class Minigame {
public:
    virtual bool play() = 0; // Fonction virtuelle pure
};
