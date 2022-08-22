#pragma once
#include <iostream>
#include "support_a_dessin.h"
#include "accelerateur.h"


class Support_texte : public SupportADessin
{
protected:

    std :: ostream& flot;

public :
    Support_texte(std :: ostream& flot)
        : flot(flot) {}

    virtual ~Support_texte()  override {
        std::cout << "suppression du support texte" << std::endl;
    }


    //Methodes dessine

    virtual void dessine(Element_courbe const& courbe)override;
    virtual void dessine (Dipole const& dipole) override;
    virtual void dessine (Element_droit const& droit) override;
    virtual void dessine (Quadrupole const& qua)override;

    virtual void dessine(Particule const& part) override;
    virtual void dessine(Accelerateur const&  acc) override;
    virtual void dessine(Faisceau const& fais) override;

};

