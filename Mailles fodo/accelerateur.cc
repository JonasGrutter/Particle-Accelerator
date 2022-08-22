#include <iostream>
#include "accelerateur.h"
#include "support_a_dessin.h"

using namespace std;

//----------------------------------------------------------------------

//Corps du destructeur d'un accélérateur : très important au niveau de la zone mémoire allouée par les pointeurs

Accelerateur::~ Accelerateur()
{
    supprimeFaisceau();
    supprimeElement();
}

void Accelerateur::supprimeFaisceau()
{
    collection_faisceau.clear();
    cout << "Les Faisceaux ont été suprimés" << endl;
}

void Accelerateur::supprimeElement()
{
    size_t sum(0);
    for(auto quidam : collection_el) {
        sum += quidam->get_Echelle().size();
        delete quidam;
        quidam = nullptr;
    }
    cerr << sum << endl;
    collection_el.clear();
    cout << "Les éléments ont été suprimés" << endl;
}

//----------------------------------------------------------------------

// Les methodes d'ajout

void Accelerateur::ajouteFaisceau(Faisceau const& fais)
{
    collection_faisceau.push_back(fais);
}

void Accelerateur::ajouteElement(Element* el)
{
    if(el!= nullptr) {
        collection_el.push_back(el);
    }
}

void Accelerateur::vis_element_suivant()																						//Pour le P14, nous rajoutons un pointeur sur l'élément précédent, nous devons donc faire le lien
{
    size_t n = collection_el.size();
    if(n > 1) {
        for(size_t i(0) ; i < n-1 ; ++i) {
            (*collection_el[i]).set_element_suivant(collection_el[i+1]);

        }

        (*collection_el[n-1]).set_element_suivant(collection_el[0]);
    }
}

void Accelerateur::vis_element_precedent()
{
    size_t n = collection_el.size();
    if(n > 1) {
        for(size_t i(1) ; i < n ; ++i) {
            (*collection_el[i]).set_element_suivant(collection_el[i-1]);

        }

        (*collection_el[0]).set_element_suivant(collection_el[n]);
    }

}


Collection_El Accelerateur::get_collection_el() const
{
    return collection_el;
}


void Accelerateur::dessine()
{
    support->dessine(*this);
}


void Accelerateur :: evolue_P13(double dt)
{
    for (auto& faisceau : collection_faisceau) {
        faisceau.evolue_P13(dt);
        cout << faisceau << endl;
    }
}


void Accelerateur :: evolue_P14(double dt)
{
    for (auto& faisceau : collection_faisceau) {
        faisceau.evolue_P14(dt);
        cout << faisceau << endl;
    }
}


//----------------------------------------------------------------------
// Affichage

std::ostream& Accelerateur::affiche_collection_faisceau(std::ostream& sortie) const
{
// si l'accelerateur est vide on le specifie

    if((collection_el.size() ==0) and (collection_faisceau.size() ==0)) {
        sortie << "L'accélerateur est vide. " << endl;
        return sortie;
    }

//on affiche les potentiels particules
    if(collection_faisceau.size() > 0) {
        sortie << constante::bold << "L'accélerateur contient " << constante::fin;

        if(collection_faisceau.size() ==1) {
            sortie  <<constante::bold << "le faisceau suivant : "<<constante::fin << endl;

        } else {
            sortie << constante::bold  << "les " << collection_faisceau.size() << " faisceaux suivants: " << constante::fin<< endl;
        }

        sortie << endl;

        for ( auto const& f : collection_faisceau) {
            sortie << f << endl;
        }
    }

    return sortie;
}


std::ostream& Accelerateur::affiche_collection_element(std::ostream& sortie) const
{

    // on affiche les potentiels éléments
    if(collection_el.size() > 0)
    {
        sortie << constante::bold  <<"L'accélerateur est consititué " << constante::fin;
        if(collection_el.size() ==1)
        {
            sortie <<constante::bold  << "de l'élément suivant :" <<constante::fin<< endl;
        } else {
            sortie <<constante::bold  <<"des " << collection_el.size()<< " éléments suivants : " <<constante::fin<< endl;
        }
        for (auto const& quidam : collection_el) {
            quidam -> affiche_element();

        }
    }

    return sortie;

}

std::ostream& Accelerateur::affiche(std::ostream& sortie) const
{
    affiche_collection_element(sortie);
    affiche_collection_faisceau(sortie);

    return sortie;
}
//----------------------------------------------------------------------



//surcharge externe  de l'operateur <<
std::ostream& operator <<(std::ostream& sortie, Accelerateur const& acc)
{
    return acc.affiche(sortie);
}



//----------------------------------------------------------------------


