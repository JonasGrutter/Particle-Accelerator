#pragma once
#include <iostream>
#include "particules.h"

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Element (Super classe) (abstraite)
class Element : public Dessinable {

protected:
    // Attributs
    Vecteur3D pos_entree; // Position d'entrée
    Vecteur3D pos_sortie; // Position de sortie
    double rayon_chambre; // Rayon de la chambre à vide
    Element* element_suivant; // pointeur sur l'élément suivant


public:
    // Constructeur
    Element(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre,
            Element* ptr = nullptr, SupportADessin* sup = nullptr);

    // Destructeur
    virtual ~Element(){element_suivant = nullptr;}

    // Méthodes 
    bool passe_au_suivant(Particule const& p) const;
    virtual bool heurte_bord(Particule p) const = 0;
    virtual Vecteur3D champ_magnetique(Particule& p) = 0 ;

	// Getter
	Vecteur3D get_direction() const;
	Element& get_Element_suivant() const;
	Vecteur3D get_pos_entree() const;
	Vecteur3D get_pos_sortie() const;
 
	// Setter
    void set_element_suivant(Element* el);
    
    // Affichage
    virtual std::ostream& affiche_element(std::ostream& flot = std::cout) const;

};


//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Element-Droit (Sous-classe de Element) (abstraite)
class Element_droit : public Element {

public:
    // Constructeur
    Element_droit(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, Element* ptr = nullptr, SupportADessin* sup = nullptr);

    // Methodes
    bool heurte_bord(Particule  p) const override;
    virtual Vecteur3D champ_magnetique(Particule& p) override = 0 ;

};

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Section_droite (Sous-classe de Element-droit)
class Section_droite : public Element_droit {

public:
    // Constructeur
    Section_droite(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre,
                   Element* ptr = nullptr, SupportADessin* sup = nullptr);

	// Méthodes
    virtual Vecteur3D champ_magnetique(Particule& p) override;
    
    // Affichage
    virtual std::ostream& affiche_element(std::ostream& flot = std::cout) const;
    // Représentation
    virtual void dessine() override;
};

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Quadrupole (Sous-classe de Element_droit)
class Quadrupole : public Element_droit {

protected:
	// Attribut
    const double intensite_aimant;

public:
	// Constructeur
    Quadrupole (Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, const double intensite_aimant,
                Element* ptr = nullptr, SupportADessin* sup =nullptr);


    // Méthode
    virtual Vecteur3D champ_magnetique(Particule& p) override;
    
    // Affichage
    virtual std::ostream& affiche_element(std::ostream& flot = std::cout) const;
    //Représentation
    virtual void dessine() override;
};

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Element_courbe-Droit (Sous-classe de Element) (abstraite)
class Element_courbe : public Element {

protected:
	// Attributs
    Vecteur3D pos_centre_courbure; 
    Vecteur3D direction_element; 
    double k; // Inverse du rayon de courbure


public:
    // Constructeur
    Element_courbe(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, double k, Element* ptr = nullptr, SupportADessin* sup = nullptr);
	
    // Methodes
    virtual Vecteur3D champ_magnetique(Particule& p) override = 0 ;
    bool heurte_bord(Particule p) const override;
     
     // Getter
    Vecteur3D getpos_centre_courbure() const;

	// Affichage
    virtual std::ostream& affiche_element(std::ostream& flot = std::cout) const;

};

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Dipole (Sous-classe de Element_courbe)
class Dipole : public Element_courbe {

protected:
	// Attribut
    double intensite; // Composante verticale du champ magnetique

public:
    // Constructeur
    Dipole (Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, double centre_courbure, double intensite ,Element* ptr = nullptr, SupportADessin* sup =nullptr);

	// Méthode
    virtual Vecteur3D champ_magnetique(Particule& p) override;

	// Affichage
    virtual std::ostream& affiche_element(std::ostream& flot = std::cout) const;
    // Représentation
    virtual void dessine() override;
};

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//surcharge externe
//std::ostream& operator <<(std::ostream& sortie, Element const& e);
