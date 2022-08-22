#include <iostream>
#include "faisceau.h"
using namespace std;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//----------------------------------------------------------------------
//-----------Fichier de test pour la classe Faisceau--------------------
//----------------------------------------------------------------------

int main()

{
//----------------------------------------------------------------------
    //on initialise une particule de référence
    Vecteur3D position1 (3.00984, -0.391837, 0); //constructeur directe ?
    Vecteur3D axe1(-0.000793945, -1, 0);
    Vecteur3D force1(0.0,0.0,0.0);
    SupportADessin* sup = nullptr;
//----------------------------------------------------------------------
	
	// Initialisation d'un Dipole
    Vecteur3D pos_entree(1,0,0);
    Vecteur3D pos_sortie (0,-1,0);
    Element* e = nullptr;

//----------------------------------------------------------------------
	
	// Création d'un faisceau
    Particule reference(sup, position1,axe1,force1,0.938272, 1.60217653e-19,2, new Dipole (sup, pos_entree, pos_sortie, 0.1, 1, 0,  e));
    Faisceau fais(reference, 100, 1, 1e-11);

//----------------------------------------------------------------------

	// Ajout d'une macroparticule dans le faisceau
    fais.ajoute_macropart();

//----------------------------------------------------------------------
	
	// Affichage
    cout << fais << endl,

//----------------------------------------------------------------------

	// Evolution
	fais.evolue(1e-11);

//----------------------------------------------------------------------

	// Affichage
    cout << fais << endl;

//----------------------------------------------------------------------

    return 0;
}
