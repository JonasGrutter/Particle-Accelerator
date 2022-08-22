#pragma once
#include <iostream>
#include "support_a_dessin.h"

// Forward Declaration
class Section_droite;
class Quadrupole;
class Dipole;
class Particule;
class Accelerateur;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Support_texte
class Support_texte : public SupportADessin
{

public :
	// Constructeur
    Support_texte(std::ostream& flot = std::cout) : flot(flot) {}
    virtual ~Support_texte()  override {
        std::cout << "suppression du support texte" << std::endl;
    }

    // les methodes dessine (mode texte)
    virtual void dessine (Dipole const& dipole) override;
    virtual void dessine (Section_droite const& droit) override;
    virtual void dessine (Quadrupole const& qua)override;
    virtual void dessine(Particule const& part) override;
    virtual void dessine(Accelerateur const&  acc) override;


private :
	// Attributs
    std::ostream& flot;
};

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************
