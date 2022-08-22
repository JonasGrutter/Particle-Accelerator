#pragma once
#include <iostream>
#include <cmath>
#include "Vecteur3D.h"
#include "constante.h"
#include "dessinable.h"


class Element;

//----------------------------------------------------------------------


// DEFINITION DE LA CLASSE PARTICULE

class Particule : public Dessinable {
    // unité : GEV

private:
    Vecteur3D position;
    Vecteur3D axe;
    Vecteur3D force;
    double masse;
    double charge;
    Vecteur3D vitesse;
    double gamma;
    double energie;
    Element* element;

public:

//----------------------------------------------------------------------
//CONSTRUCTEURS
    Particule( SupportADessin* sup, Vecteur3D x, Vecteur3D a,Vecteur3D f, double m, double q,  double E, Element* ptr);
    Particule(Vecteur3D x, double m,  double q, Vecteur3D v, double g, double E, Element* ptr);

    ~Particule()
    {
        element = nullptr;   //nous devons mettre un deconstructeur.
    }

    Particule(Particule const& autre, double x);

//----------------------------------------------------------------------
//SETTERS

    void setVitesse() ;
    void set_force(Vecteur3D F);

//----------------------------------------------------------------------
//GETTERS

    Vecteur3D get_pos() const;
    Vecteur3D get_vitesse() const;
    Vecteur3D get_force() const;

    double get_energie() const;
    double get_charge() const;
    double get_masse() const;
    double get_gamma() const;

    Element& get_element() const;

//----------------------------------------------------------------------
// METHODES RELATIVES A L'EVOLUTION


    void ajouteForceMagnetique(Vecteur3D B,  double dt);
    void bouger(double t);
    void change_element(Element& prochain);

//----------------------------------------------------------------------
    virtual void dessine() override;

//----------------------------------------------------------------------
    std::ostream& affiche(std::ostream& sortie) const;
//----------------------------------------------------------------------


//P14
    size_t get_Case();

};

// surcharge externe de l'operateur <<
std::ostream& operator <<(std::ostream& sortie, Particule const& part);

//----------------------------------------------------------------------
