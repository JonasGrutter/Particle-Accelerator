#include <iostream>
#include <vector>

class Particule;

class Case
{
protected :

    std::vector <Particule*> collection_part;

public :

    Case(std::vector <Particule*> collection_part = std::vector <Particule*> ()) {}
    void supprimeParticule(Particule& p);

    void ajouteParticule(Particule& p);

    std::vector<Particule*> get_Particule() const {
        return collection_part;
    }
};


