#pragma once
#include <iostream>

// Forward Declaration
class SupportADessin;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Dessinable
class Dessinable
{
protected :
    SupportADessin* support;

public :
	// Constructeur
    Dessinable(SupportADessin* sup)
        : support(sup) {}
	// Constructeur        
    //Dessinable() {}
    
    // Destructeur
    virtual ~Dessinable() {}
    
    // Représentation
    virtual void dessine() = 0;

};

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************
