#include <iostream>
#include <iomanip>
#include "particules.h"
#include "support_a_dessin.h"
#include "element.h"


using namespace std;

//----------------------------------------------------------------------
//CONSTRUCTEURS

//Corps du constructeur
Particule::Particule ( SupportADessin* sup, Vecteur3D x, Vecteur3D a,Vecteur3D f, double m,  double q,double E, Element* ptr = nullptr )
    : Dessinable(sup), position(x),  axe(a), force(f), masse(m), charge(q), energie(E), element(ptr)
{
    setVitesse();
    gamma = energie/masse;
}

Particule::Particule(Vecteur3D x, double m,  double q, Vecteur3D v, double g, double E, Element* ptr =nullptr) //pourquoi?
    :position(x), masse(m), charge(q),vitesse(v), gamma(g), energie(E), element(ptr)
{}

//un constructeur de copie nécessaire pour la creation des faisceaux
Particule::Particule( Particule const& autre, double x)
{
    position = autre.position;
    axe = autre.axe;
    force = autre.force;
    masse = x*autre.masse;
    charge = x*autre.charge;
    vitesse = autre.vitesse;
    gamma = autre.gamma;
    energie = x*autre.energie;
    element = autre.element;
}

//----------------------------------------------------------------------
//SETTEURS

//vitesse
void Particule::setVitesse()
{
    double scalaire;
    scalaire = (masse*masse)/(energie*energie);
    scalaire = constante::c * sqrt(1-scalaire);
    vitesse = axe*scalaire;
}

//force
void Particule::set_force( Vecteur3D F)
{
    force = F;

}
//----------------------------------------------------------------------
//GETTERS

// position

Vecteur3D Particule :: get_pos() const
{
    return position;
}

// energie
double Particule::get_energie() const
{
    return energie;
}

//vitesse
Vecteur3D Particule::get_vitesse() const
{
    return vitesse;
}

//masse
double Particule::get_masse() const
{
    return masse;
}

//charge
double Particule::get_charge() const
{
    return charge;
}

//gamma
double Particule::get_gamma() const
{
    return get_energie()/get_masse();
}

//element
Element& Particule :: get_element() const // par référence : on a empeché les copies d'éléments
{
    return (*element);
}
//force [P13]

Vecteur3D Particule::get_force() const
{
    return force;
}

//en utilisant l'abscisse curviligne, je trouve l'indice de la case de ma particule
size_t Particule::get_Case()
{   double curvi;
    curvi = element->abscisse_curviligne(*this);
    return floor(curvi/constante::longueur_case);
}

//----------------------------------------------------------------------
// METHODES RELATIVES A L'EVOLUTION

//ajout d'une force magnétique

void Particule::ajouteForceMagnetique(Vecteur3D  B,  double dt)
{
    if (dt == 0) {
        return;
    }

    double Angle;
    Vecteur3D F ((charge*vitesse)^B);

    cout << "F0 = " << F;

    Angle = asin(((dt*F).norme()) / (2*gamma*constante::kilo * masse *vitesse.norme()));
    Vecteur3D axe;
    axe = vitesse ^F;
    F.rotation(axe, Angle);

    cout << "F1 = " << F;
    cout << "Angle : " << Angle << endl;

    force = F;
}

//on fait bouger les particules
void Particule:: bouger(double t)
{
    Vecteur3D acc;
    double scalaire;

    scalaire = 1/(gamma*constante::kilo *masse);

    acc = force*scalaire;
    vitesse += (acc*t);
    position += (vitesse*t);

    force = constante::vecteur_nul;
}

// Utiliser dans la méthode évolue de l'accélérateur
void Particule :: change_element(Element& prochain)
{
    element = (&prochain);
}

//----------------------------------------------------------------------
// la méthode dessine, relative à toutes les sous_classes de dessinable

void Particule::dessine()
{
    support->dessine(*this);
}

//----------------------------------------------------------------------
//ADFFICHAGE

// une methode interne, utiliser pour la surcharche
std::ostream& Particule::affiche(ostream& sortie) const
{

    sortie.setf(ios:: left);
    sortie << constante::s_jaune << "Une particule :" << constante::fin << endl; // setw?
    sortie << std::setw(24) << "position : " << position;
    sortie << std::setw(24) << "vitesse : "<< vitesse;
    sortie << std::setw(24) << "gamma : " << gamma << endl;
    sortie << std::setw(24) << "energie (Gev) : " << energie << endl;
    sortie << std::setw(24) << "masse (Gev/ c^2) : " << masse << endl;
    sortie << std::setw(24) << "charge : " << charge << endl;
    sortie << std::setw(24) << "force : " << force << endl;

    return sortie;
}

//methode externe, surcharche de l'operateur <<
std::ostream& operator <<(std::ostream& sortie, Particule const& part)
{
    return part.affiche(sortie);
}

//----------------------------------------------------------------------


//----------------------------------------------------------------------
