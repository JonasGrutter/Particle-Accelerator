#pragma once
#include <iostream>
#include <cmath>
#include "Vecteur3D.h"
#include "constante.h"
#include "dessinable.h"

// Forward declaration
class Element;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Particule
class Particule : public Dessinable {
    //Pour les unités nous utiliserons le GeV

private:
	// Attributs
    Vecteur3D position;
    Vecteur3D axe;
    Vecteur3D force;
    double masse;
    double charge;
    Vecteur3D vitesse;
    double gamma;
    double energie;
    double Angle;
    Element* element;


public:
    // Constructeur
    Particule(Vecteur3D x, Vecteur3D a,Vecteur3D f, double m, double q,  double E, Element* ptr = nullptr, SupportADessin* sup = nullptr);

	// Destructeur
    ~Particule() { element = nullptr; }

    // Setter
    void setVitesse() ;
    
    // Getters
    Vecteur3D get_pos() const;
    double get_energie() const;
    Vecteur3D get_vitesse() const;
    double get_charge() const;
    double get_masse() const;
    double get_gamma() const;
    double get_angle() const;
    Element& get_element() const;


	// Evolution de la particule
    void ajouteForceMagnetique(Vecteur3D B,  double dt);
    void bouger(double t);
    std::ostream& affiche(std::ostream& sortie) const;
	void change_element(Element& prochain);
	
   // Représentation 
    virtual void dessine() override;

};

// Opérateur d'affichage
std::ostream& operator <<(std::ostream& sortie, Particule const& part);

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

