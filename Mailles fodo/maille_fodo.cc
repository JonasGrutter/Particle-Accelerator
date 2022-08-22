#include "element.h"
#include "maille_fodo.h"
#include <iostream>
#include <iomanip>
#include "support_a_dessin.h"


void Maille_fodo :: set_maille(double b)
{
	el1 = Quadrupole (sup,pos_entree, pos_entree+add_longueur_vect(), rayon_chambre, b, *el2)
	el2 = Section_droite(sup, pos_entree+add_longueur_vect(), pos_entree+2*add_longueur_vect(), rayon_chambre,*el3);
	el3 = Quadrupole (sup,pos_entree+2*add_longueur_vect(), pos_entree+3*add_longueur_vect(), rayon_chambre, -b, *el4)
	el4 = Section_droite(sup, pos_entree+3*add_longueur_vect(), pos_sortie, rayon_chambre,ptr);
}

double Maille_fodo :: longueur_un_element() const
{
	Vecteur3D temp = pos_entree - pos_sortie;
	return temp.norme()/4.0;
}

Vecteur3D Maille_fodo :: add_longueur_vect() const
{
	return longueur_un_element() * get_direction();
}
