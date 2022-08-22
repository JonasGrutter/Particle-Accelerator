#include <iostream>
#include "accelerateur.h"
#include "support_a_dessin.h"

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
    supprimeFaisceau();
    supprimeElement();
}

//----------------------------------------------------------------------

// Supression des faisceaux
void Accelerateur::supprimeFaisceau()
{
    collection_faisceau.clear();
    cout << "Les Faisceaux ont été suprimés" << endl;
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

// Ajout d'un faisceau
void Accelerateur::ajouteFaisceau(Faisceau const& fais)
{
    collection_faisceau.push_back(fais);
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
    for (auto& faisceau : collection_faisceau) {
        faisceau.evolue(dt);
        cout << faisceau << endl;
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

// Collection de faisceaux
Collection_F Accelerateur::get_collection_fais() const
{
    return collection_faisceau;
}

//----------------------------------------------------------------------

//-----------------------------Affichage--------------------------------

//----------------------------------------------------------------------

// Faisceaux


std::ostream& Accelerateur::affiche_collection_faisceau(std::ostream& sortie) const
{
// si l'accelerateur est vide on le specifie

    if((collection_el.size() ==0) and (collection_faisceau.size() ==0)) {
        sortie << "L'accélerateur est vide. " << endl;
        return sortie;
    }

//on affiche les potentiels particules
    if(collection_faisceau.size() > 0) {
        sortie <<  "L'accélerateur contient ";

        if(collection_faisceau.size() ==1) {
            sortie   << "le faisceau suivant : "<< endl;

        } else {
            sortie <<"les " << collection_faisceau.size() << " faisceaux suivants: " << endl;
        }

        sortie << endl;

        for ( auto const& f : collection_faisceau) {
            sortie << f << endl;
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
        sortie << "L'accélerateur est consititué ";
        if(collection_el.size() ==1)
        {
            sortie  << "de l'élément suivant :" << endl;
        } else {
            sortie <<"des " << collection_el.size()<< " éléments suivants : " << endl;
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

    affiche_collection_faisceau(sortie);
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

//Surcharge de l'operateur <<
std::ostream& operator <<(std::ostream& sortie, Accelerateur const& acc)
{
    return acc.affiche(sortie);
}

//----------------------------------------------------------------------
