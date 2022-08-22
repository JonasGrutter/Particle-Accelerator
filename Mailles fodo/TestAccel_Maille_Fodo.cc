#include <iostream>
#include "accelerateur.h"

using namespace std;

//Création des positions d entrée
Vecteur3D 	entree1(3,2,0), entree2(3,-2,0), entree3(2,-3,0), entree4(-2,-3,0), entree5(-3,-2,0), entree6(-3,2,0), entree7(-2,3,0), entree8(2,3,0);

vector<Vecteur3D> entrees({entree1, entree2, entree3, entree4, entree5, entree6, entree7, entree8});
                          
//Création des positions de sortie
Vecteur3D sortie1(3,-2,0), sortie2(2,-3,0), sortie3(-2,-3,0), sortie4(-3,-2,0), sortie5(-3,2,0), sortie6(-2,3,0), sortie7(2,3,0), sortie8(3,2,0);

vector<Vecteur3D> sorties({ sortie1, sortie2, sortie3, sortie4, sortie5, sortie6, sortie7, sortie8});

// Initialisation de 2 Particules, particule1 et particule2

Vecteur3D position1 (3.01, 0, 0);
Vecteur3D axe1(0, -0.999998, 0);
Vecteur3D force1(0.0,0.0,0.0);
SupportADessin* sup = nullptr;
Element* ptr = nullptr;

Vecteur3D position2 (2.99, 0, 0);
Vecteur3D axe2(0, -0.999998, 0 );
Vecteur3D force2(0.0,0.0,0.0);




// Inititialisation des Eléments et de l'accélérateur

double b(1.2);
double re(0.1); // Rayon des cghambres de l'accelerateu
double k(1);
double b3(5.89158); // Intensité pourles dipoles
double longueur_section_droite(1);




int main()
{

    Accelerateur acc;

    for(size_t i(0); i < 4; i+=2) {

		Maille_fodo* m(new Maille_fodo(sup,entrees[i], sorties[i], re, longueur_section_droite , b));
        Dipole* d(new Dipole(sup, entrees[i+1],sorties[i+1], re, k,b3));
        
        acc.ajouteElement(m);
        acc.ajouteElement(d);
    }
	cout << "yo" << endl;
    acc.vis_element_suivant();
	cout << "yop" << endl;
    Particule reference1( sup, position1,axe1,force1,0.938272, 1.60217653e-19,2, (acc.get_collection_el())[0]);
    Particule reference2( sup, position2,axe2,force2,0.938272, 1.60217653e-19, 2, (acc.get_collection_el())[0]);

    Faisceau faisceau1(reference1, 100, 8, 1);
    Faisceau faisceau2(reference2, 200, 20, 1e-11);
	cout << "yopi" << endl;
    faisceau1.ajoute_macropart();
    cout << "yopiou" << endl;
    acc.ajouteFaisceau(faisceau1);

    faisceau2.ajoute_macropart();
    acc.ajouteFaisceau(faisceau2);
	cout << "yopioulou" << endl;
	
    cout << acc << endl;


    for( size_t i(0); i< 400; ++i)
    {
        acc.evolue_P13(1e-11);
    }



    return 0;
}
