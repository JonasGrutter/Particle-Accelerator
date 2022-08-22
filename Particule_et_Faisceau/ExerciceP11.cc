#include <iostream>
#include "accelerateur.h"

using namespace std;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//----------------------------------------------------------------------
//--------------------------Exercice P11--------------------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Initialisation des positions d entrée
Vecteur3D 	entree1(3,2,0), entree2(3,1,0), entree3(3,0,0), entree4(3,-1,0), entree5(3,-2,0),
            entree6(2,-3,0), entree7(1,-3,0), entree8(0,-3,0), entree9(-1,-3,0), entree10(-2,-3,0),
            entree11(-3,-2,0), entree12(-3,-1,0), entree13(-3,0,0), entree14(-3,1,0), entree15(-3,2,0),
            entree16(-2,3,0), entree17(-1,3,0), entree18(0,3,0), entree19(1,3,0), entree20(2,3,0);

vector<Vecteur3D> entrees({entree1, entree2, entree3, entree4, entree5, entree6, entree7, entree8, entree9,
                           entree10, entree11, entree12, entree13, entree14, entree15, entree16, entree17,
                           entree18, entree19, entree20
                          });
                          
//----------------------------------------------------------------------
                          
// Initialisation des positions de sortie
Vecteur3D sortie1(3,1,0), sortie2(3,0,0), sortie3(3,-1,0), sortie4(3,-2,0), sortie5(2,-3,0),
          sortie6(1,-3,0), sortie7(0,-3,0), sortie8(-1,-3,0), sortie9(-2,-3,0), sortie10(-3,-2,0),
          sortie11(-3,-1,0), sortie12(-3,0,0), sortie13(-3,1,0), sortie14(-3,2,0), sortie15(-2,3,0),
          sortie16(-1,3,0), sortie17(0,3,0), sortie18(1,3,0), sortie19(2,3,0), sortie20(3,2,0);

vector<Vecteur3D> sorties({ sortie1, sortie2, sortie3, sortie4, sortie5, sortie6, sortie7, sortie8,
                            sortie9, sortie10, sortie11, sortie12, sortie13, sortie14, sortie15,
                            sortie16, sortie17, sortie18, sortie19, sortie20
                          });

//----------------------------------------------------------------------

// Initialisation de 2 Particules, particule1 et particule2
Vecteur3D position1 (3.01, 0, 0); 
Vecteur3D axe1(0, -0.999998, 0);
Vecteur3D force1(0.0,0.0,0.0);


Vecteur3D position2 (2.99, 0, 0);
Vecteur3D axe2(0, -0.999998, 0 );
Vecteur3D force2(0.0,0.0,0.0);

//----------------------------------------------------------------------

// Inititialisation des Eléments et de l'accélérateur

double b1(1.2); // Intenistés magnétiques pourles quadrupôles
double b2(-1.2);
double re(0.1); // Rayon des chambres de l'accelerateur
double k(1); // Inverse du rayon de courbure des dipôles
double b3(5.89158); // Intensité pourles dipoles


int main()
{

    Accelerateur acc;

    for(size_t i(0); i < 20; i+=5) {

        Quadrupole* q1(new Quadrupole(entrees[i], sorties[i], re, b1));
        Section_droite* s1(new Section_droite( entrees[i+1], sorties[i+1],re));
        Quadrupole* q2(new Quadrupole(entrees[i+2], sorties[i+2], re, b2));
        Section_droite* s2(new Section_droite(entrees[i+3], sorties[i+3],re));
        Dipole* d1(new Dipole(entrees[i+4],sorties[i+4], re, k,b3));

        acc.ajouteElement(q1);
        acc.ajouteElement(s1);
        acc.ajouteElement(q2);
        acc.ajouteElement(s2);
        acc.ajouteElement(d1);
    }
//----------------------------------------------------------------------
	
	// Assemblage des éléments
    acc.vis_element();

//----------------------------------------------------------------------

	// Création des faisceaux
    Particule reference1(position1,axe1,force1,0.938272, 1.60217653e-19,2, (acc.get_collection_el())[2]);
    Particule reference2(position2,axe2,force2,0.938272, 1.60217653e-19, 2, (acc.get_collection_el())[2]);

    Faisceau faisceau1(reference1, 100, 100);
    Faisceau faisceau2(reference2, 200, 200);

//----------------------------------------------------------------------

	// Ajout des faisceaux
    faisceau1.ajoute_macropart();
    acc.ajouteFaisceau(faisceau1);

    faisceau2.ajoute_macropart();
    acc.ajouteFaisceau(faisceau2);

//----------------------------------------------------------------------

	// Affichage
    cout << acc << endl;

//----------------------------------------------------------------------

	// Evolution
    for( size_t i(0); i< 4000; ++i)
    {
        acc.evolue(1e-11);
    }

//----------------------------------------------------------------------

    return 0;
}

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************
