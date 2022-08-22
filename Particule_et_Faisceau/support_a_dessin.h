#pragma once
#include <iostream>

class Element_courbe;
class Element_droit;
class Dipole;
class Quadrupole;
class Particule;
class Accelerateur;
class Faisceau;

//----------------------------------------------------------------------
class SupportADessin
{
private:

    //pas de constructeur de copie
    SupportADessin(SupportADessin const&) = delete;
    SupportADessin& operator=(SupportADessin const&) = delete;

public :

    virtual ~SupportADessin() = default;

    SupportADessin() {};

    virtual void dessine(Element_droit const&) = 0 ;
    virtual void dessine(Element_courbe const&) = 0 ;
    virtual void dessine(Dipole const&) = 0 ;
    virtual void dessine(Quadrupole const&) = 0 ;
    virtual void dessine(Particule const&) = 0;
    virtual void dessine(Accelerateur const&) = 0;
    virtual void dessine(Faisceau const&) = 0;

};
