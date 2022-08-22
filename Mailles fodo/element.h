#pragma once
#include <iostream>
#include "particules.h"
#include <vector>

//----------------------------------------------------------------------

// Classe Element (Super classe) (abstrait)

class Case;



class Element : public Dessinable {

protected:
    // Attributs de la classe Element

    Vecteur3D pos_entree; // Position d'entrée
    Vecteur3D pos_sortie; // Position de sortie
    double rayon_chambre; // Rayon de la chambre à vide
    Element* element_suivant; // pointeur sur l'élément suivant
    Element* element_precedent; // pour le P14

    std::vector<Case*> Echelle;


public:
    // Constructeur
    Element(SupportADessin* sup, Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre,
            Element* ptr = nullptr, Element* ptr_ = nullptr);



    // Destructeur
    virtual ~Element()// inutile de delete element_suivant;
    {
        element_suivant = nullptr;
    }

    // Méthodes associées à la classe Element
    Vecteur3D get_direction() const;
    bool passe_au_suivant(Particule p) const;
    virtual bool heurte_bord(Particule p) const = 0;
	virtual void affiche_element() const;
    virtual Vecteur3D champ_magnetique(Particule& p) = 0 ;



    //pour le calcul dans faisseau
    virtual Vecteur3D get_u(Particule const& part) const = 0;


    //initilaiser l'argument, élément suivant, pointeur sur un element

    Element& get_Element_suivant() const;
    Element& get_Element_precedent() const;
    Vecteur3D get_pos_entree() const;
    Vecteur3D get_pos_sortie() const;

    void set_element_suivant(Element* el);
    //P14
    void set_element_precedent(Element* el);

    //P14
    virtual double abscisse_curviligne(Particule p) const = 0;
    virtual std::vector<Case*>  get_Echelle() const;


};




//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Classe Element_droit (Sous-classe de Element) (abstrait)

class Element_droit : public Element {

public:
    // Constructeur
    Element_droit(SupportADessin* sup, Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, Element* ptr = nullptr, Element* ptr_ = nullptr);

    //P14 Destructeurs
    virtual ~Element_droit();

    // Methodes associées à la classe Element_courbe

    bool heurte_bord(Particule p) const override;
    virtual Vecteur3D champ_magnetique(Particule& p) override = 0 ; //Expliciter que c est une classe abstraite
    virtual Vecteur3D get_u(Particule const& part) const override;
    virtual double abscisse_curviligne(Particule p) const  override;


};


//----------------------------------------------------------------------
//----------------------------------------------------------------------

class Section_droite : public Element_droit {

public:

    // Constructeur
    Section_droite(SupportADessin* sup,Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre,
                   Element* ptr = nullptr, Element* ptr_ = nullptr);

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
    Quadrupole (SupportADessin* sup,Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, const double intensite_aimant,
                Element* ptr = nullptr, Element* ptr_ = nullptr);

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




public:
    // Constructeur
    Element_courbe(SupportADessin* sup,Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, double k, Element* ptr = nullptr,  Element* ptr_ = nullptr);

    //DestructeurP14
    virtual ~Element_courbe();

    // Methodes servant à définir les attributs
    //void signe_k();
    virtual Vecteur3D champ_magnetique(Particule& p) override = 0 ; //Expliciter que c est une classe abstraite
    Vecteur3D getpos_centre_courbure() const;


    // Methodes associées à la classe Element_courbe
    bool heurte_bord(Particule p) const override;

    virtual  void affiche_element() const override ;
    //virtual void dessine() override;

    //pour le calcul dans faisseau
    virtual Vecteur3D get_u(Particule const& part) const override;

    // calcul arc P14;
    double calcul_arc() const;
    virtual double abscisse_curviligne(Particule p) const  override;


};


//----------------------------------------------------------------------




class Dipole : public Element_courbe {

protected:
    double intensite; // Composante verticale du champ magnetique

public:
    // Constructeur

    Dipole (SupportADessin* sup,Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, double centre_courbure, double intensite ,Element* ptr = nullptr, Element* ptr_ = nullptr);



    // Méthodes d'initialisation de la classe Dipole


    virtual Vecteur3D champ_magnetique(Particule& p) override;

    virtual void affiche_element() const override;
    virtual void dessine() override;

};


//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Maille_fodo

class Maille_fodo : public Element_droit{
	
	private:
		Quadrupole* quad_1;
		Section_droite* sec_1;
		Quadrupole* quad_2;
		Section_droite* sec_2;
		
		double longueur_sec_droite;
		double longueur_quad;
		
	public:
		// Constructeur
		Maille_fodo (SupportADessin* sup, Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre, double longueur_sec_droite ,const double intensite_aimant,Element* ptr = nullptr)
		:Element_droit(sup, pos_entree, pos_sortie, rayon_chambre,ptr), longueur_sec_droite(longueur_sec_droite)
		{
				longueur_quad = calcul_longueur_quad();
				set_maille(sup, intensite_aimant);
		}
		
		void set_maille(SupportADessin* sup,double b);
		
		double longueur() const;
		double calcul_longueur_quad() const;
		virtual Vecteur3D champ_magnetique(Particule& p) override ;
		Vecteur3D add_longueur_vect(double longueur) const;
	
		//Affichage
		virtual void affiche_element() const override;
		virtual void dessine() override;
};

//----------------------------------------------------------------------
//surcharge externe

//std::ostream& operator <<(std::ostream& sortie, Element const& e);

