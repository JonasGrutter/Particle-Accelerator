#include <iostream>
#include "element.h"
#include <iomanip>
#include "support_a_dessin.h"
#include "Case.h"

using namespace std;


//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Définition des Méthodes associées à la classe Element

// constrcucteurs

Element::Element(SupportADessin* sup, Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre,
                 Element* ptr, Element* ptr_)
    :Dessinable(sup), pos_entree(pos_entree), pos_sortie(pos_sortie), rayon_chambre(rayon_chambre), element_suivant(ptr), element_precedent(ptr_)
{}

Vecteur3D Element :: get_direction() const // Retourne la direction de l'élément
{
    Vecteur3D res;
    res = ((pos_sortie-pos_entree).unitaire());
    return res;
}

void Element::affiche_element() const
{

    cout <<std::setw(24) <<"entree : " << pos_entree;
    cout  <<std::setw(24) <<"sortie : " << pos_sortie;
    cout <<std::setw(24) <<"rayon de chambre : " << rayon_chambre << endl;
}

Element& Element :: get_Element_suivant() const
{
    return (*element_suivant);
}

Element& Element :: get_Element_precedent() const
{
    return (*element_precedent);
}

void Element::set_element_suivant(Element* el)
{
    element_suivant = el;
}

void Element::set_element_precedent(Element* el)
{
    element_precedent = el;
}



bool Element :: passe_au_suivant (Particule p) const // Retourne true si la particule dépassé la sortie de l'élément
{   
	cout << "Element :: depasseElement";
    bool comp =(constante::e3).prod_mixte(p.get_pos(), pos_sortie) > 0;

    if (comp) {
        cout << ": OUT! " << endl;
    } else {
        cout << " [ fin = " << pos_sortie << " direct =" << get_direction() << " ] : " << endl;
    }
    return comp;
}

std::vector<Case*> Element::get_Echelle() const
{
    return Echelle;
}

Vecteur3D Element :: get_pos_entree() const
{
	return pos_entree;
}
Vecteur3D Element :: get_pos_sortie() const
{
	return pos_sortie;
}



//----------------------------------------------------------------------

// Définition des Méthodes associées à la classe Element_droit


bool Element_droit :: heurte_bord(Particule p) const // Retourne true si la particule donnée a heurté ou dépassé le bord de la chambre à vide de l'élément
{
    Vecteur3D x = p.get_pos() - pos_entree;
    Vecteur3D comp = x - (x*get_direction())*get_direction();

    return (comp.norme() > rayon_chambre);
}

Vecteur3D Element_droit::get_u(Particule const& part) const
{
    return constante::e3^(pos_sortie-pos_entree);
}


// Constructeur
Element_droit::Element_droit(SupportADessin* sup, Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, Element* ptr, Element* ptr_)
    : Element ( sup, pos_entree, pos_sortie, rayon_chambre,ptr, ptr_)
{
    //P14
    double longueur_element = (pos_sortie-pos_entree).norme();
    int n(floor(longueur_element / constante::longueur_case));
    Echelle = std::vector<Case*> (n);

    for(Case*& p : Echelle) {
        p= new Case();
    }

}

//Destructeur P14 --> allocation dynamique
Element_droit::~Element_droit()
{
    for(auto& c : Echelle)
    {
        delete c;
        c = nullptr;
    }
}


double Element_droit::abscisse_curviligne(Particule p) const
{
    return (p.get_pos()-pos_entree).norme();
}


//-----------------------------

// Définition des Méthodes associées à la classe Section_droite

Vecteur3D Section_droite :: champ_magnetique(Particule& p)
{
    return constante :: vecteur_nul;
}


void Section_droite::affiche_element() const
{
    cout << constante::s_cyan <<  "Section droite : " << constante::fin << endl;
    Element::affiche_element();
    cout << endl;
}

void Section_droite::dessine()
{
    support->dessine(*this);
}

// constructeur
Section_droite::Section_droite(SupportADessin* sup,Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre,
                               Element* ptr, Element* ptr_)
    : Element_droit (sup, pos_entree, pos_sortie, rayon_chambre,ptr, ptr_)
{}
//----------------------------------------------------------------------

// Définition des Méthodes associées à la classe Quadrupole

Vecteur3D Quadrupole :: champ_magnetique(Particule& p)
{
    Vecteur3D res;

    Vecteur3D d = get_direction();
    Vecteur3D pos = p.get_pos();
    Vecteur3D X = (pos- pos_entree);
    Vecteur3D y = X - ((X*d)*d);
    Vecteur3D u = (constante :: e3)^d;

    res = intensite_aimant*(((y*u)*(constante :: e3))+(pos.get_z()*u));
    return res;
}

void Quadrupole::affiche_element() const
{
    cout.setf(ios:: left);
    cout << constante::s_cyan << "Quadrupole : " << constante::fin << endl;
    Element::affiche_element();
    cout <<std::setw(24) <<"champ magnetique : " << intensite_aimant*constante::e3 << endl;

}

void Quadrupole::dessine()
{
    support->dessine(*this);
}

// constructeurs

Quadrupole::Quadrupole (SupportADessin* sup,Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, const double intensite_aimant,
                        Element* ptr, Element* ptr_)
    : Element_droit (sup, pos_entree, pos_sortie, rayon_chambre,ptr, ptr_), intensite_aimant(intensite_aimant)
{}

//----------------------------------------------------------------------

// Définition des Méthodes associées à la classe Element_courbe

bool Element_courbe :: heurte_bord (Particule p) const // Retourne true si la particule donnée a heurté ou dépassé le bord de la chambre à vide de l'élément
{
    Vecteur3D x = p.get_pos() - pos_entree;
    Vecteur3D pos = p.get_pos();
    double x3 = pos.get_z();
    Vecteur3D comp = x-(abs(1/k))*(x- x3*constante::e3);

    return (comp.norme() > rayon_chambre);
}

// Methodes d'initialisation de la classe Element_courbe

Vecteur3D Element_courbe :: getpos_centre_courbure() const // Retourne la position du centre de courbure de l'élément
{
    Vecteur3D res(0,0,0);

    res += (0.5) *(pos_entree + pos_sortie);
    double racine = sqrt(1-(k*k)*(((pos_sortie-pos_entree).norme2())*0.25));
    res = res + (1/k)*racine*((get_direction())^(constante::e3));

    return res;
}


void Element_courbe::affiche_element() const
{
    cout.setf(ios:: left);
    cout << constante:: s_cyan << "Element courbe : " << constante::fin <<endl;
    Element::affiche_element();
    cout <<std::setw(24) <<"rayon de courbure "  << 1/k << endl;
    cout <<std::setw(24) <<"centre de courbure : " << pos_centre_courbure << endl;

}

Vecteur3D Element_courbe::get_u(Particule const& part) const
{
    Vecteur3D x = part.get_pos() - pos_entree;
    Vecteur3D pos = part.get_pos();
    double x3 = pos.get_z();
    return x- x3*constante::e3; // pk on ne peux pas mettre constante::e3??
}

//Constructeur

Element_courbe::Element_courbe(SupportADessin* sup,Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, double k, Element* ptr, Element* ptr_ )
    : Element(sup, pos_entree, pos_sortie, rayon_chambre,ptr,ptr_), k(k)
{
    //signe_k();
    pos_centre_courbure = getpos_centre_courbure();
    direction_element = get_direction();


    double longueur_element = calcul_arc();
    int n(floor(longueur_element / constante::longueur_case));
    Echelle = std::vector<Case*> (n);

    for(Case*& p : Echelle) {
        p= new Case();
    }

}

double Element_courbe::calcul_arc() const
{
    Vecteur3D a (pos_entree-getpos_centre_courbure());
    Vecteur3D b(pos_sortie-getpos_centre_courbure());

    double alpha = acos((a*b)/(a.norme()*b.norme()));
    double arc = a.norme()*alpha;
    return arc;
}


//Destructeur P14 --> allocation dynamique
Element_courbe::~Element_courbe()
{   for(auto& c : Echelle)
    {
        delete c;
        c = nullptr;
    }
}

//P14

double Element_courbe::abscisse_curviligne(Particule p) const
{
    Vecteur3D a (pos_entree-getpos_centre_courbure());
    Vecteur3D part_centre(p.get_pos()-getpos_centre_courbure());
    double alpha = acos((a*part_centre)/(a.norme()*part_centre.norme()));
    double abscisse_curviligne = a.norme()*alpha;
    return abscisse_curviligne;
}



//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Méthodes d'initialisation de la classe Dipole

Vecteur3D Dipole :: champ_magnetique(Particule& p)
{

    Vecteur3D res(0, 0, intensite );
    return res;
}

void Dipole::affiche_element() const
{
    cout.setf(ios:: left);
    cout << constante::s_cyan << "Dipole : " << constante::fin << endl;
    Element::affiche_element();
    cout  <<std::setw(24) << "rayon de courbure "  << 1/k << endl;
    cout  <<std::setw(24) << "centre de courbure : " << pos_centre_courbure;
    cout <<std::setw(24) <<"champ magnetique : " << intensite*constante::e3 << endl;

}

void Dipole::dessine()
{
    support->dessine(*this);
}

// constrcucteur


Dipole::Dipole (SupportADessin* sup,Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, double centre_courbure, double intensite ,Element* ptr, Element* ptr_)
    : Element_courbe ( sup, pos_entree, pos_sortie, rayon_chambre, centre_courbure, ptr,ptr_), intensite(intensite)
{}

//----------------------------------------------------------------------


//Méthode de la classe Maille fodo
double Maille_fodo :: longueur() const
{
	Vecteur3D temp = pos_entree - pos_sortie;
	return temp.norme();
}

Vecteur3D Maille_fodo :: add_longueur_vect(double longueur) const
{
	return longueur*get_direction();
}

void Maille_fodo :: set_maille(SupportADessin* sup,double b)
{
	Vecteur3D pos_entree1 = pos_entree;
	Vecteur3D pos_entree2 = pos_entree + add_longueur_vect(longueur_quad);
	Vecteur3D pos_entree3 = pos_entree + add_longueur_vect(longueur_quad + longueur_sec_droite);
	Vecteur3D pos_entree4 = pos_entree + add_longueur_vect(2*longueur_quad + longueur_sec_droite);
	
	Vecteur3D pos_sortie1 = pos_entree2;
	Vecteur3D pos_sortie2 = pos_entree3;
	Vecteur3D pos_sortie3 = pos_entree4;
	Vecteur3D pos_sortie4 = pos_sortie;

	quad_1 = new Quadrupole(sup, pos_entree1, pos_sortie1, rayon_chambre, b, sec_1);
	sec_1 = new Section_droite(sup, pos_entree2, pos_sortie2,rayon_chambre, quad_2);
	quad_2 = new Quadrupole(sup, pos_entree3, pos_sortie3, rayon_chambre, -b, sec_2);
	sec_2 = new Section_droite(sup, pos_entree4, pos_sortie4,rayon_chambre);
 
}

double Maille_fodo :: calcul_longueur_quad() const
{
	return (longueur() - 2*longueur_sec_droite)/2.0;
}

Vecteur3D Maille_fodo :: champ_magnetique(Particule& p)
{
	if ((p.get_pos()-pos_entree).norme() <= longueur_quad){
		return (*quad_1).champ_magnetique(p);
	}else if((p.get_pos()-pos_entree).norme() <= longueur_quad+longueur_sec_droite){
		return (*sec_1).champ_magnetique(p);
	} else if((p.get_pos()-pos_entree).norme() <= 2*longueur_quad+longueur_sec_droite){
		return (*quad_2).champ_magnetique(p);
	} else if((p.get_pos()-pos_entree).norme() <= (pos_sortie-pos_entree).norme()){
		return (*sec_2).champ_magnetique(p);
	} else{
		return Vecteur3D(0,0,0);
	}
}

void Maille_fodo :: affiche_element() const 
{
	cout << "Maille fodo: " << endl;
	Element::affiche_element();
	cout << "contenant:" << endl;
	cout << "1)" << endl;
	quad_1->affiche_element();
	cout << "2)" << endl;
	sec_1->affiche_element();
	cout << "3)" << endl;
	quad_2->affiche_element();
	cout << "4)" << endl;
	sec_2->affiche_element();
	
}

void Maille_fodo :: dessine()
{
	support->dessine(*this);
}
