#pragma once
#include <iostream>
#include "particules.h"
#include <vector>

// Forward Declaration
class Element;

// Définitions de type
typedef std::vector<Element*> Collection_El;
typedef std::vector<Particule> Collection_Part;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Accelerateur
class Accelerateur : public Dessinable
{
private :
	// Attributs
    Collection_Part collection_part;
    Collection_El collection_el;

public :
	// Constructeur 
    Accelerateur(SupportADessin* sup = nullptr) 
        : Dessinable(sup) {}
	
	// Constructeur de copie
    Accelerateur(Accelerateur const& autre) = delete;
	// Operateur de comparaison
    Accelerateur& operator = (Accelerateur const& autre) = delete;
	
	// Destructeur
    ~ Accelerateur(); 

	// Méthodes
    void supprimeParticule();
    void supprimeElement();
    void ajouteParticule(Particule const& part);
    void ajouteElement(Element* el);
    void evolue(double dt);
    void vis_element();

	// Getters
    Collection_El get_collection_el() const;
    Collection_Part get_collection_part() const;
    
    // Affichage
    std::ostream& affiche_collection_element(std::ostream& sortie) const;
    std::ostream& affiche_collection_particule(std::ostream& sortie) const;
    std::ostream& affiche(std::ostream& sortie) const;
    // Représentation
    virtual void dessine() override;
};
// Surcharge de l'opérateur d'affichage
std::ostream& operator <<(std::ostream& sortie, Accelerateur const& acc);

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************


