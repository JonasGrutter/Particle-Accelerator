#include <iostream>
#include "texte_viewer.h"
#include "accelerateur.h"
#include "particules.h"
#include "element.h"

using namespace std;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//----------------------------------------------------------------------
//---------------------------Exercice P9--------------------------------
//----------------------------------------------------------------------
int main()
{

// Initialisation du support à dessin
    SupportADessin* support(new Support_texte());

// Créaton d'un accélérateur
    Accelerateur acc (support);

//----------------------------------------------------------------------

// Initialisation Dipole
    Vecteur3D pos_entree(1,0,0);
    Vecteur3D pos_sortie (0,-1,0);
    Element* e = nullptr;

//on ajoute un dipole
    acc.ajouteElement( new Dipole  (pos_entree, pos_sortie, 0.1, 1, 0,  e,support));

//----------------------------------------------------------------------

// Initilisation Section_droite
    Vecteur3D pos_entree1(0,-1,0);
    Vecteur3D pos_sortie1(-1, -1, 0);

//on ajoute section droite
    acc.ajouteElement (new Section_droite( pos_entree1,  pos_sortie1, 0.1, e,support));

//----------------------------------------------------------------------

//initialisation Quadrupole
    Vecteur3D pos_entree2 = pos_sortie1;
    Vecteur3D pos_sortie2(-1,-1, 29);

//on ajoute un quadrupole
    acc.ajouteElement (new Quadrupole(pos_entree2,pos_sortie2, 0.1, 1.2, e,support));

//----------------------------------------------------------------------

//Initialisation de 2 particules
    Vecteur3D position (3.00984, -0.391837, 0);
    Vecteur3D axe(-0.000793945, -1, 0);
    Vecteur3D force(0.0,0.0,0.0);

    Vecteur3D position_1 (2.99016, -0.391837, 0);
    Vecteur3D axe_1(0.000793945, -1, 0 );
    Vecteur3D force_1(0.0,0.0,0.0);

    Particule particule(position,axe,force,0.938272, 1.60217653e-19,2, e,support);
    Particule particule_1(position_1,axe_1,force_1,0.938272, 1.60217653e-19, 2, e,support);

// Ajout des Particules dans l'accélérateur
    acc.ajouteParticule(particule);
    acc.ajouteParticule(particule_1);

//----------------------------------------------------------------------

// dessin d'un accelerateur (Texte ici)
    acc.dessine();

    delete support;
//----------------------------------------------------------------------

    return 0;

}

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************
