#include <iostream>

#include "Case.h"
#include "particules.h"

void Case::supprimeParticule(Particule& p)
{
    for(size_t i (0); i <  collection_part.size(); ++i)
    {
        if (collection_part[i]-> get_pos() == p.get_pos())
        {   collection_part[i] = collection_part[collection_part.size()-1];
            collection_part[collection_part.size()-1] = nullptr;
            collection_part.pop_back();
            i = collection_part.size();
        }
    }

}

void Case::ajouteParticule(Particule& p)
{
    collection_part.push_back(&p);
}


