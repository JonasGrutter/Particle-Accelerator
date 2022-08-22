#include <iostream>
#include "text_viewer.h"


void Support_texte ::dessine(Element_courbe const& courbe)
{
    courbe.affiche_element();
}

void Support_texte::dessine(Element_droit const& droit)
{
    droit.affiche_element();
}

void Support_texte ::dessine(Dipole const& dipole)
{
    dipole.affiche_element();
}

void Support_texte ::dessine(Quadrupole const& qua)
{
    qua.affiche_element();
}

void Support_texte::dessine(Particule const& part)
{
    flot << part << std::endl;
}

void Support_texte::dessine(Accelerateur const& acc)
{
    flot << acc << std::endl;
}

void Support_texte::dessine(Faisceau const& f)
{
    flot<< f << std::endl;
}

void Support_texte :: dessine(Maille_fodo const& maille)
{
	flot << maille << std::endl;
}
