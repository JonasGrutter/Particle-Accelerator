#pragma once
#include <iostream>

class SupportADessin;


//----------------------------------------------------------------------
class Dessinable
{
protected :
    SupportADessin* support;

public :

    Dessinable(SupportADessin* sup)
        : support(sup) {}

    // Constructeur par defaut, pour pas devoir le mettre dans faisceau ??
    Dessinable() {}

    virtual ~Dessinable() {}
    virtual void dessine() = 0;

};



