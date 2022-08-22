#pragma once
#include <iostream>

// Forward Declaration
class Dipole;
class Quadrupole;
class Section_droite;
class Particule;
class Accelerateur;


//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe SupportADessin
class SupportADessin
{
public :

	// Constructeur
    SupportADessin() {};

    //Constructeur de copie
    SupportADessin(SupportADessin const&) = delete;
    SupportADessin& operator=(SupportADessin const&) = delete;

	// Destructeur
    virtual ~SupportADessin() = default;

	// Méthodes de dessin
    virtual void dessine(Section_droite const&) = 0;
    virtual void dessine(Dipole const&) = 0 ;
    virtual void dessine(Quadrupole const&) = 0 ;
    virtual void dessine(Particule const&) = 0;
    virtual void dessine(Accelerateur const&) = 0;


};


//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************
