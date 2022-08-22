#pragma once
#include <iostream>
#include "faisceau.h"
#include <vector>

// Forward Declaration
class Element;

// Définitions de type
typedef std::vector<Element*> Collection_El;
typedef std::vector<Faisceau> Collection_F;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Accelerateur
class Accelerateur : public Dessinable
{
private :
	// Attributs
    Collection_F collection_faisceau;
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
    void supprimeFaisceau();
    void supprimeElement();
    void ajouteFaisceau(Faisceau const& fais);
    void ajouteElement(Element* el);
    void evolue(double dt);
    void vis_element();

	// Getters
    Collection_El get_collection_el() const;
    Collection_F get_collection_fais() const;
    
    // Affichage
    std::ostream& affiche_collection_element(std::ostream& sortie) const;
    std::ostream& affiche_collection_faisceau(std::ostream& sortie) const;
    std::ostream& affiche(std::ostream& sortie) const;
    // Représentation
    virtual void dessine() override;

  
};
// Operateur <<
std::ostream& operator <<(std::ostream& sortie, Accelerateur const& acc);

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************


