#include <iostream>
#include "accelerateur.h"

using namespace std;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//----------------------------------------------------------------------
//------Fichier de test pour la classe Accelerateur de Faisceau---------
//----------------------------------------------------------------------

int main()

{
//----------------------------------------------------------------------

	//Initialisation de 2 Particules, particule et particule_1
    Vecteur3D position  (3.00984, -0.391837, 0);
    Vecteur3D axe (-0.000793945, -1, 0);
    Vecteur3D force (0.0,0.0,0.0);


    Vecteur3D position_1 (2.99016, -0.391837, 0);
    Vecteur3D axe_1(0.000793945, -1, 0 );
    Vecteur3D force_1(0.0,0.0,0.0);

    Particule reference( position,axe,force,0.938272, 1.60217653e-19,2);
    Particule reference_1(position_1,axe_1,force_1,0.938272, 1.60217653e-19,2);

//----------------------------------------------------------------------

	//Initialisation de notre faisceau
    Faisceau fais(reference, 100, 4000);
    Faisceau fais_1(reference_1,200, 2000);
//----------------------------------------------------------------------
	
	//Intilalisationde notre accélérateur;
    Accelerateur acc;
    
//----------------------------------------------------------------------
	
	// Affichage de l'accélérateur
    cout << endl;
    cout << acc << endl;;
//----------------------------------------------------------------------

	//On ajoute un faisceau
    acc.ajouteFaisceau(fais);

//----------------------------------------------------------------------

	// on affiche le contenu de l'accelerateur
    cout << acc << endl;

//----------------------------------------------------------------------

	// on ajoute particule_1
    acc.ajouteFaisceau(fais_1);

//----------------------------------------------------------------------

	// on affiche acc
    cout << acc << endl;

//----------------------------------------------------------------------

	// Initialisation d'un dipôle
    Vecteur3D pos_entree(1,0,0);
    Vecteur3D pos_sortie (0,-1,0);
    
//----------------------------------------------------------------------

	//on ajoute un dipole
    acc.ajouteElement( new Dipole  (pos_entree, pos_sortie, 0.1, 1, 0));

//----------------------------------------------------------------------
	
	// on affiche acc
    cout << acc << endl;

//----------------------------------------------------------------------
	
	// on supprime nos particules
    acc.supprimeFaisceau();

//----------------------------------------------------------------------

	// on affiche acc
    cout << acc << endl;

//----------------------------------------------------------------------
    return 0;
}

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************