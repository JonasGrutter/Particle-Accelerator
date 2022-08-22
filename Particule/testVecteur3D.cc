#include <iostream>
#include <cmath>
#include "Vecteur3D.h"
using namespace std;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//----------------------------------------------------------------------
//----------------Fichier de test pour les Vecteur3D--------------------
//----------------------------------------------------------------------


int main()
{

//----------------------------------------------------------------------

	// Initialisation de 3 vecteurs
    Vecteur3D v1 (1.0,2.0,-0.1);
    Vecteur3D v2(2.6, 3.5, 4.1);
    Vecteur3D v3(3.9,3.8,3.7);
    cout << "Vecteur v1 : " << v1 << endl;
    cout << "Vecteur v2 : " << v2 << endl;
    cout << "Vecteur v3 : " << v3 << endl;
    
//----------------------------------------------------------------------
	// Copie d'un vecteur
    Vecteur3D c(v1);
    cout <<"Vecteur copié: " << c << endl;
    
//----------------------------------------------------------------------
	
	// Vecteur Par défaut
    Vecteur3D defaut;
    cout <<"Vecteur par défaut: " << defaut << endl;

//----------------------------------------------------------------------
    
	// Addition:
	cout << "Addition de v1 et v2 :" << v1 + v2 << endl;
	
//----------------------------------------------------------------------	

	// Soustraction
	cout << "la soustraction d'un vecteur à lui-même donne le vecteur nul :"
		<< v1 << " - " << v1 << " = " << v1-v1 << endl;
		
//----------------------------------------------------------------------
	
	// Opposé
	cout << "l'opposé de " << v1 << " est " << -v1 << endl;
	
//----------------------------------------------------------------------

	// Addition de l'opposé = Soustraction
	cout << "Addition de l'opposé = Soustraction" << v1 + (-v1) << endl;
	
//----------------------------------------------------------------------

	// Multiplication par un scalaire
	cout << 3 << " * " << v1 << " = " << 3 * v1 << endl;
	cout << "Commutativité: " << v1 << " * " << 3 << " = " << v1*3 << endl;
	
//----------------------------------------------------------------------

	// Produit scalaire
	cout << " Produit scalaire de v1 et v2 : " << v1*v2 << endl;

//----------------------------------------------------------------------

	// Produit Vectoriel
	Vecteur3D temp = v1^v2;
	cout << " Produit vectoriel de v1 et v2 : " << temp << endl;

//----------------------------------------------------------------------

	// Norme
	cout << " Norme au carré de v1: " << v1.norme2() << endl;
	cout << " Norme au carré de v2: " << v2.norme2() << endl;
	
//----------------------------------------------------------------------

	// Unitaire
	cout << "le vecteur unitaire colinéaire et de même sens que " << v2 
		<< " est " << ~v2 << endl;
		
//----------------------------------------------------------------------

	// Produit mixte
	cout << "Le produit mixte de " << v1 << ", " << v2 << ", " << v3
		<<", vaut : " << v1.prod_mixte(v2, v3) << endl;
	cout << "Un produit mixte contenant deux fois le même vecteur est nul:"
		<< v1.prod_mixte(v1, v3) << endl;

//----------------------------------------------------------------------
	
	// Rotation
	Vecteur3D axe(0, 1, 0);
	double angle = 90;
	v1.rotation(axe, angle);
	cout << "Rotation de v1 d'angle " << angle << " autour de l'axe " 
		<< axe << " :" << v1 << endl;
	
    return 0;
}

//----------------------------------------------------------------------
