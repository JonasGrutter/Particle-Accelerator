#include <iostream>
#include "element.h"
#include <iomanip>
#include "support_a_dessin.h"

using namespace std;


//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Définition des Méthodes associées à la classe Element

//Constructeur

Element::Element (Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre,
                  Element* ptr, SupportADessin* sup)
    :Dessinable(sup), pos_entree(pos_entree), pos_sortie(pos_sortie), rayon_chambre(rayon_chambre), element_suivant(ptr)
{}

Vecteur3D Element :: get_direction() const // Retourne la direction de l'élément
{
    Vecteur3D res;
    res = ((pos_sortie-pos_entree).unitaire());
    return res;
}

void Element::affiche_element() const
{

    cout <<std::setw(24) <<"entree : " << pos_entree << endl;
    cout  <<std::setw(24) <<"sortie : " << pos_sortie << endl;
    cout <<std::setw(24) <<"rayon de chambre : " << rayon_chambre << endl;
}

Element& Element :: get_Element_suivant() const
{
    return (*element_suivant);
}


void Element::set_element_suivant(Element* el)
{
    element_suivant = el;
}


bool Element :: passe_au_suivant (Particule const& p) const // Retourne true si la particule dépassé la sortie de l'élément
{   cout << "Depasse element ? ";
    bool comp =(constante::e3).prod_mixte(p.get_pos(), pos_sortie) > 0;

    if (comp) {
        cout << "Oui" << endl;
        cout << endl;
        p.get_element().affiche_element();
        cout << endl;
    } else {
        cout << "Non" <<endl;
        cout  << "Element courant : [entree = " << pos_entree << ", sortie = " << pos_sortie << "]" << endl;
        cout << endl;
    }
    return comp;
}

//----------------------------------------------------------------------

// Définition des Méthodes associées à la classe Element_droit

//Constructeur

Element_droit::Element_droit(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, Element* ptr, SupportADessin* sup)
    : Element (pos_entree, pos_sortie, rayon_chambre, ptr, sup)
{}


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

//----------------------------------------------------------------------

// Définition des Méthodes associées à la classe Section_droite

//Constructeur
Section_droite::Section_droite(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre,
                               Element* ptr, SupportADessin* sup)
    : Element_droit (pos_entree, pos_sortie, rayon_chambre,ptr,sup)
{}

Vecteur3D Section_droite :: champ_magnetique(Particule& p)
{
    return constante :: vecteur_nul;
}


void Section_droite::affiche_element() const
{
    cout  <<  "Section droite : " << endl;
    Element::affiche_element();
    cout << endl;
}

void Section_droite::dessine()
{
    support->dessine(*this);
}

//----------------------------------------------------------------------

// Définition des Méthodes associées à la classe Quadrupole

//Constructeur
Quadrupole::Quadrupole (Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, const double intensite_aimant,
                        Element* ptr, SupportADessin* sup)
    : Element_droit ( pos_entree, pos_sortie, rayon_chambre,ptr, sup), intensite_aimant(intensite_aimant)
{}

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
    cout << "Quadrupole : "  << endl;
    Element::affiche_element();
    cout <<std::setw(24) <<"champ magnetique : " << intensite_aimant*constante::e3 << endl;

}

void Quadrupole::dessine()
{
    support->dessine(*this);
}


//----------------------------------------------------------------------

// Définition des Méthodes associées à la classe Element_courbe

//Constructeur
Element_courbe::Element_courbe(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, double k, Element* ptr, SupportADessin* sup)
    : Element( pos_entree, pos_sortie, rayon_chambre,ptr,sup), k(k)
{
    //signe_k();
    pos_centre_courbure = getpos_centre_courbure();
    direction_element = get_direction();
}

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
    cout  << "Element courbe : " <<endl;
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

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Méthodes d'initialisation de la classe Dipole

//Constructeur

Dipole::Dipole(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, double centre_courbure, double intensite ,Element* ptr, SupportADessin* sup)
    : Element_courbe (pos_entree, pos_sortie, rayon_chambre, centre_courbure, ptr,sup), intensite(intensite)
{}

Vecteur3D Dipole :: champ_magnetique(Particule& p)
{

    Vecteur3D res(0, 0, intensite );
    return res;
}

void Dipole::affiche_element() const
{
    cout.setf(ios:: left);
    cout  << "Dipole : " << endl;
    Element::affiche_element();
    cout  <<std::setw(24) << "rayon de courbure "  << 1/k << endl;
    cout  <<std::setw(24) << "centre de courbure : " << pos_centre_courbure << endl;
    cout <<std::setw(24) <<"champ magnetique : " << intensite*constante::e3 << endl;

}

void Dipole::dessine()
{
    support->dessine(*this);
}

//----------------------------------------------------------------------
//surcharge externe


