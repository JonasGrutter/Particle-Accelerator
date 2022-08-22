#include <iostream>
#include "element.h"

using namespace std;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//----------------------------------------------------------------------
//----------------Fichier de test pour les particules-------------------
//----------------------------------------------------------------------

int main()
{
//Initialisation de 2 Particules, particule et particule_1

    Vecteur3D position (3.00984, -0.391837, 0); //constructeur directe ?
    Vecteur3D axe(-0.000793945, -1, 0);
    Vecteur3D force(0.0,0.0,0.0);

    Vecteur3D position_1 (2.99016, -0.391837, 0);
    Vecteur3D axe_1(0.000793945, -1, 0 );
    Vecteur3D force_1(0.0,0.0,0.0);


    Particule particule( position,axe,force,0.938272, 1.60217653e-19,2);
    Particule particule_1( position_1,axe_1,force_1,0.938272, 1.60217653e-19, 2);

//----------------------------------------------------------------------

//Affichage des 2 particules
    cout << endl;
    cout << "Creation de deux particules :" << endl;
    cout << endl;
    cout << particule;
    cout << particule_1;
    
//----------------------------------------------------------------------

//Initialisation d'un champ magnetique et d'un pas de temps
    Vecteur3D B(0,0,7);
    double dt(1e-11);
    
//----------------------------------------------------------------------

//Ajout d'une force magnetique
    cout<< "Ajout d'une force magnetique, B = " << B << "(dt="<< dt<< ") : " << endl;
    cout << endl;
    cout << "A particule :" << endl;
    particule.ajouteForceMagnetique(B, dt);
    cout << endl;
    cout <<"A particule_1 : " << endl;
    particule_1.ajouteForceMagnetique(B, dt);
    cout << endl;
 
//----------------------------------------------------------------------

//On met les particules en mouvement
    cout << "Les particules bougent 1 fois :" << endl;
    cout << endl;
    particule.bouger(1e-11);
    cout << particule;
    particule_1.bouger(1e-11);
    cout << particule_1;

//----------------------------------------------------------------------
    return 0;
}

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************
