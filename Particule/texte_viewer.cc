#include <iostream>
#include "texte_viewer.h"
#include "element.h"
#include "accelerateur.h"

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//----------------------------------------------------------------------
//-------------Méthodes associées à la classe Support_texte-------------
//----------------------------------------------------------------------

// Dessin (texte) des objets dessinables

void Support_texte::dessine(Section_droite const& droit)
{
    droit.affiche_element(flot);
}

void Support_texte ::dessine(Dipole const& dipole)
{
    dipole.affiche_element(flot);
}

void Support_texte ::dessine(Quadrupole const& qua)
{
    qua.affiche_element(flot);
}

void Support_texte::dessine(Particule const& part)
{
    flot<< part << std::endl;
}

void Support_texte::dessine(Accelerateur const& acc)
{
    flot << acc << std::endl;
}


//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************


