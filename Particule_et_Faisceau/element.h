#pragma once
#include <iostream>
#include "particules.h"



//----------------------------------------------------------------------

// Classe Element (Super classe) (abstrait)

class Element : public Dessinable {

protected:
    // Attributs de la classe Element

    Vecteur3D pos_entree; // Position d'entrée
    Vecteur3D pos_sortie; // Position de sortie
    double rayon_chambre; // Rayon de la chambre à vide
    Element* element_suivant; // pointeur sur l'élément suivant


public:
    // Constructeur
    Element(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre,
            Element* ptr = nullptr, SupportADessin* sup = nullptr);


    // Destructeur
    virtual ~Element()// inutile de delete element_suivant;
    {
        element_suivant = nullptr;
    }

    // Méthodes associées à la classe Element
    Vecteur3D get_direction() const;
    bool passe_au_suivant(Particule const& p) const;
    virtual bool heurte_bord(Particule p) const = 0;
    virtual void affiche_element() const;
    virtual Vecteur3D champ_magnetique(Particule& p) = 0 ;



    //pour le calcul dans faisseau
    virtual Vecteur3D get_u(Particule const& part) const = 0;

    //initilaiser l'argument, élément suivant, pointeur sur un element

    Element& get_Element_suivant() const;
    void set_element_suivant(Element* el);
};



//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Classe Element_droit (Sous-classe de Element) (abstrait)

class Element_droit : public Element {

public:
    // Constructeur
    Element_droit(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, Element* ptr = nullptr, SupportADessin* sup = nullptr);

    // Methodes associées à la classe Element_courbe

    bool heurte_bord(Particule p) const override;
    virtual Vecteur3D champ_magnetique(Particule& p) override = 0 ; //Expliciter que c est une classe abstraite
    virtual Vecteur3D get_u(Particule const& part) const override;

};


//----------------------------------------------------------------------
//----------------------------------------------------------------------

class Section_droite : public Element_droit {

public:

    // Constructeur
    Section_droite(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre,
                   Element* ptr = nullptr, SupportADessin* sup = nullptr);

    // Méthodes d'initialisation de la classe Section droite


    virtual Vecteur3D champ_magnetique(Particule& p) override;
    virtual void affiche_element()  const override;
    virtual void dessine() override;
};


//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Classe Quadrupole (Sous-classe de Element) (abstrait)

class Quadrupole : public Element_droit {

protected:
    const double intensite_aimant;

public:
    Quadrupole (Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, const double intensite_aimant,
                Element* ptr = nullptr, SupportADessin* sup =nullptr);

    // Méthodes d'initialisation de la classe Section droite

    virtual Vecteur3D champ_magnetique(Particule& p) override;
    virtual void affiche_element() const override;

    virtual void dessine() override;
};

//----------------------------------------------------------------------
//----------------------------------------------------------------------


// Classe Element_courbe (Sous-classe de Element)

class Element_courbe : public Element {

protected:
    Vecteur3D pos_centre_courbure; // Coordonnés du centre de courbure - définie indirectement
    Vecteur3D direction_element; // direction de l'élément - définie indirectement
    double k; // Inverse du rayon de courbure

    // Il faut encore rajouter le champ magnétique


public:
    // Constructeur
    Element_courbe(Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, double k, Element* ptr = nullptr, SupportADessin* sup = nullptr);

    // Methodes servant à définir les attributs

    virtual Vecteur3D champ_magnetique(Particule& p) override = 0 ; //Expliciter que c est une classe abstraite
    Vecteur3D getpos_centre_courbure() const;


    // Methodes associées à la classe Element_courbe
    bool heurte_bord(Particule p) const override;

    virtual  void affiche_element() const override ;
    //virtual void dessine() override;

    //pour le calcul dans faisseau
    virtual Vecteur3D get_u(Particule const& part) const override;

};


//----------------------------------------------------------------------




class Dipole : public Element_courbe {

protected:
    double intensite; // Composante verticale du champ magnetique

public:
    // Constructeur

    Dipole (Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, double centre_courbure, double intensite ,Element* ptr = nullptr, SupportADessin* sup =nullptr);

    // Méthodes d'initialisation de la classe Dipole


    virtual Vecteur3D champ_magnetique(Particule& p) override;

    virtual void affiche_element() const override ;
    virtual void dessine() override;
};

//----------------------------------------------------------------------

