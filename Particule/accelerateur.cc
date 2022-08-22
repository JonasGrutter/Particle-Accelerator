#include <iostream>
#include "accelerateur.h"
#include "support_a_dessin.h"
#include "element.h"

using namespace std;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//----------------------------------------------------------------------
//------------Méthodes associées à la classe Accelerateur---------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------

//Destructeur
Accelerateur::~ Accelerateur() 
{
    cout << "Fin de la simulation" << endl;
    supprimeParticule();
    supprimeElement();
}

//----------------------------------------------------------------------

// Supression des particules
void Accelerateur::supprimeParticule()
{
    collection_part.clear();
    cout << "Les particules ont été suprimées" << endl;
}

//----------------------------------------------------------------------

// Suppression des Elements
void Accelerateur::supprimeElement()
{
    for(auto quidam : collection_el) {
        delete quidam;
        quidam = nullptr;
    }
    collection_el.clear();
    cout << "Les élément ont été suprimés" << endl;
}

//----------------------------------------------------------------------

// Ajout d'une particule
void Accelerateur::ajouteParticule(Particule const& part)
{
    collection_part.push_back(part);

}

//----------------------------------------------------------------------

// Ajout d'un Element
void Accelerateur::ajouteElement(Element* el)
{
    if(el!= nullptr)
    {
        collection_el.push_back(el);
    }
}

//----------------------------------------------------------------------

// Visse les Elements de l'accelerateur entre eux
void Accelerateur::vis_element()
{
    size_t n = collection_el.size();
    for(size_t i(0) ; i < n-1 ; ++i) {
        (collection_el[i])->set_element_suivant(collection_el[i+1]);
    }

    (collection_el[n-1])->set_element_suivant(collection_el[0]);

}

//----------------------------------------------------------------------

// Evolution (Sans interraction entre particules)
void Accelerateur :: evolue(double dt)
{
    for (auto& particule : collection_part) {

        if ((particule.get_element()).passe_au_suivant(particule))
        {
            particule.change_element(particule.get_element().get_Element_suivant());
        }

        Vecteur3D champ_mag = (particule.get_element()).champ_magnetique(particule);
        cout << champ_mag << endl;

        particule.ajouteForceMagnetique(champ_mag, dt );


        particule.bouger(dt);
        cout << particule << endl;

    }
}

//----------------------------------------------------------------------

//-------------------------------Getters--------------------------------

//----------------------------------------------------------------------

// Collection d'elements
Collection_El Accelerateur::get_collection_el() const
{
    return collection_el;
}

//----------------------------------------------------------------------

// Collection de particules
Collection_Part Accelerateur::get_collection_part() const
{
    return collection_part;
}

//----------------------------------------------------------------------

//-----------------------------Affichage--------------------------------

//----------------------------------------------------------------------

// Particules
std::ostream& Accelerateur::affiche_collection_particule(std::ostream& sortie) const
{
// si l'accelerateur est vide on le specifie

    if((collection_el.size() ==0) and (collection_part.size() ==0))
    {
        sortie << "L'accélerateur est vide. " << endl;
        return sortie;
    }

    //on affiche les potentiels particules
    if(collection_part.size() > 0)
    {
        sortie << "L'accélerateur est constitué de: " << endl;
        if(collection_part.size() ==1)
        {
            sortie  << "la particule suivante : "<< endl;
        } else {
            sortie  << "les " << collection_part.size() << " particules suivantes : " << endl;
        }
        sortie << endl;
        for ( auto const& quidam : collection_part) {
            sortie << quidam << endl;
        }
    }

    return sortie;
}

//----------------------------------------------------------------------


// Elements
std::ostream& Accelerateur::affiche_collection_element(std::ostream& sortie) const
{

    // on affiche les potentiels éléments
    if(collection_el.size() > 0)
    {
        sortie <<"L'accélerateur contient: ";
        if(collection_el.size() ==1)
        {
            sortie << " l'élément suivant :" << endl;
        } else {
            sortie <<"les " << collection_el.size()<< " éléments suivants : " << endl;
        }
        for (auto const& quidam : collection_el) {
            quidam -> affiche_element();

        }
    }

    return sortie;

}

//----------------------------------------------------------------------

// Accélérateur
std::ostream& Accelerateur::affiche(std::ostream& sortie) const
{

    affiche_collection_particule(sortie);
    affiche_collection_element(sortie);

    return sortie;
}

//----------------------------------------------------------------------

// Representation
void Accelerateur::dessine()
{
    support->dessine(*this);
}

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//surcharge externe  de l'operateur <<
std::ostream& operator <<(std::ostream& sortie, Accelerateur const& acc)
{
    return acc.affiche(sortie);
}

//----------------------------------------------------------------------
