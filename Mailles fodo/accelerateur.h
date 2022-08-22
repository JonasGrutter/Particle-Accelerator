#pragma once
#include <iostream>
#include "element.h"
#include "faisceau.h"


typedef std::vector<Element*> Collection_El;
typedef std::vector<Faisceau> Collection_F;


//----------------------------------------------------------------------

class Accelerateur : public Dessinable
{
private :


    Collection_El collection_el;
    Collection_F collection_faisceau;



    Accelerateur(Accelerateur const& autre) = delete;

    Accelerateur& operator = (Accelerateur const& autre) = delete;


public :


    Accelerateur(SupportADessin* sup = nullptr) // ici mes vecteurs sont tous les deux initialisés à vide;
        : Dessinable(sup) {}



    ~ Accelerateur(); // on utilise un destructeur, utlisation de pointeur, zone memoire

    void supprimeFaisceau();
    void supprimeElement();

    void ajouteFaisceau(Faisceau const& part);
    void ajouteElement(Element* el);

    void evolue_P13(double dt);
    void evolue_P14(double dt);

    void vis_element_suivant();
    void vis_element_precedent();
    Collection_El get_collection_el() const;

    virtual void dessine() override;

    std::ostream& affiche_collection_element(std::ostream& sortie) const;
    std::ostream& affiche_collection_faisceau(std::ostream& sortie) const;
    std::ostream& affiche(std::ostream& sortie) const;
};

std::ostream& operator <<(std::ostream& sortie, Accelerateur const& acc);

//----------------------------------------------------------------------


