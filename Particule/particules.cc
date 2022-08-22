#include <iostream>
#include <iomanip>
#include "particules.h"
#include "support_a_dessin.h"

using namespace std;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//----------------------------------------------------------------------
//---------------Méthodes associées à la classe Particule---------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Constructeur
Particule::Particule (Vecteur3D x, Vecteur3D a,Vecteur3D f, double m,  double q,double E, Element* ptr, SupportADessin* sup )
    : Dessinable(sup), position(x),  axe(a), force(f), masse(m), charge(q), energie(E), element(ptr)
{
    setVitesse();
    gamma = energie/masse;

}

//----------------------------------------------------------------------

//-------------------------------Setters--------------------------------

//----------------------------------------------------------------------

// Vitesse
void Particule::setVitesse()
{
    double scalaire;
    scalaire = (masse*masse)/(energie*energie);
    scalaire = constante::c * sqrt(1-scalaire);
    vitesse = axe*scalaire;
}

//----------------------------------------------------------------------

//-------------------------------Getters--------------------------------

//----------------------------------------------------------------------

// Position
Vecteur3D Particule :: get_pos() const
{
	return position;
}

//----------------------------------------------------------------------

// Energie
double Particule::get_energie() const
{
	return energie;
}

//----------------------------------------------------------------------

// Vitesse
Vecteur3D Particule::get_vitesse() const
{
	return vitesse;
}

//----------------------------------------------------------------------

// Masse
double Particule::get_masse() const
{
	return masse;
}

//----------------------------------------------------------------------

// Charge
double Particule::get_charge() const
{
	return charge;
}

//----------------------------------------------------------------------

// Gamma
double Particule::get_gamma() const
{
	return get_energie()/get_masse();
}

//----------------------------------------------------------------------

// Element
Element& Particule :: get_element() const // par référence : on a empeché les copies d'éléments
{
	return (*element);
}

//----------------------------------------------------------------------

//------------------------------Evolution-------------------------------

//----------------------------------------------------------------------

// Ajout d'une force magnétique
void Particule::ajouteForceMagnetique(Vecteur3D  B,  double dt)
{
    if (dt == 0) {
        return;
    }

    double Angle;
    Vecteur3D F ((charge*vitesse)^B);

    cout << "F0 = " << F << endl;

    Angle = asin(((dt*F).norme()) / (2*gamma*constante::kilo * masse *vitesse.norme()));
    Vecteur3D axe;
    axe = vitesse ^F;
    F.rotation(axe, Angle);

    cout << "F1 = " << F << endl;
    cout << "Angle : " << Angle << endl;
    cout << endl;

    force = F;
}

//----------------------------------------------------------------------

// Bouger 
void Particule:: bouger(double t)
{
    Vecteur3D acc;
    double scalaire;

    scalaire = 1/(gamma*constante::kilo *masse);
    cout << force << endl;
    acc = force*scalaire;
    vitesse += (acc*t);
    position += (vitesse*t);
    force = constante::vecteur_nul;
}

//----------------------------------------------------------------------

// Change l'élément dans lequel se trouve la particule 
void Particule :: change_element(Element& prochain)
{
    element = (&prochain);
}

//----------------------------------------------------------------------

//----------------------------Représentation----------------------------

//----------------------------------------------------------------------

// dessine
void Particule::dessine()
{
    support->dessine(*this);
}

//----------------------------------------------------------------------

// Affichage
std::ostream& Particule::affiche(ostream& sortie) const
{

    sortie.setf(ios:: left);
    sortie  << "Une particule :" << endl;
    sortie << std::setw(24) << "position : " << position << endl;
    sortie << std::setw(24) << "vitesse : "<< vitesse << endl;
    sortie << std::setw(24) << "gamma : " << gamma << endl;
    sortie << std::setw(24) << "energie (Gev) : " << energie << endl;
    sortie << std::setw(24) << "masse (Gev/ c^2) : " << masse << endl;
    sortie << std::setw(24) << "charge : " << charge << endl;
    sortie << std::setw(24) << "force : " << force << endl;

    return sortie;
}

//----------------------------------------------------------------------

// Operateur <<
std::ostream& operator <<(std::ostream& sortie, Particule const& part)
{
    return part.affiche(sortie);
}

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************
