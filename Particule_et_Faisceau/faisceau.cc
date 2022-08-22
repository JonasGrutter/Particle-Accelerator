#include <iostream>
#include "faisceau.h"
#include "support_a_dessin.h"
#include <iomanip>
#include <cmath>

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//----------------------------------------------------------------------
//------------Méthodes associées à la classe faisceau-------------------
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Calcul : de l'emittance et des coefficient eliptiques(A11, A12, A22) selon l'axe z
void Faisceau::calcul_verticale()
{
    //1) Je parcours mon tableau et prend la coordonnée e2de ma position et vitesse, que je mets au carré puis on fait la moyenne
    // 	   en même temps  je prend à nouveau la coordonnée e2 de ma position et vitesse mais je les multiplie et fait la moyenne

    double v1(0.0);
    double p1(0.0);
    double v_p(0.0);


    if (not(faisceau.empty()))
    {
        for (auto part : faisceau)
        {
            p1 += (part.get_pos()*constante::e2)*(part.get_pos()*constante::e2);
            v1 +=  (part.get_vitesse()*constante::e2)*(part.get_vitesse()*constante::e2);
            v_p += (part.get_pos()*constante::e2)*(part.get_vitesse()*constante::e2);
        }

        p1 = (p1)/get_nombre_actuel();
        v1 = (v1)/get_nombre_actuel();
        v_p = (v_p)/get_nombre_actuel();

        //<r^2> <vr^2> - <r vr>^2
        emitance_verticale = (v1*p1)- ((v_p)*(v_p));
        emitance_verticale = sqrt(emitance_verticale);

        std::cout << "emitance_verticale" << emitance_verticale << std::endl;

        coeff_ellipse_verticale[0] =v1/emitance_verticale; //A11
        coeff_ellipse_verticale[1] = -v_p/emitance_verticale; //A12
        coeff_ellipse_verticale[2] = p1/emitance_verticale; //A22
    }
}

//----------------------------------------------------------------------

// Calcul : de l'emittance et des coefficient eliptiques(A11, A12, A22) selon l'axe horizontale
void Faisceau::calcul_horizontal()
{
    double v1(0.0);
    double p1(0.0);
    double v_p(0.0);


    for (auto part : faisceau)
    {
        p1 += ((part.get_pos()*(part.get_element().get_u(part)))*((part.get_pos()*(part.get_element().get_u(part)))));
        v1 += ((part.get_vitesse()*(part.get_element().get_u(part)))*(part.get_vitesse()*(part.get_element().get_u(part))));
        v_p += ((part.get_pos()*(part.get_element().get_u(part)))*(part.get_vitesse()*(part.get_element().get_u(part))));
    }

    p1 = (p1)/get_nombre_actuel();
    v1 = (v1)/get_nombre_actuel();
    v_p = (v_p)/get_nombre_actuel();

    //<r^2> <vr^2> - <r vr>^2
    emitance_horizontale = (v1*p1)- ((v_p)*(v_p));
    emitance_horizontale = sqrt(emitance_horizontale);

    std::cout << "emitance_horizontale" << emitance_horizontale << std::endl;

    coeff_ellipse_horizontal[0] =v1/emitance_horizontale; //A11
    coeff_ellipse_horizontal[1] = -v_p/emitance_horizontale; //A12
    coeff_ellipse_horizontal[2] = p1/emitance_horizontale; //A22
}

//----------------------------------------------------------------------

// Energie moyenne
double Faisceau::energie_moy() const
{
    double energie(0.0);
    if (not (faisceau.empty()))
    {
        for(auto part : faisceau)
        {
            energie+= part.get_energie();
        }
        energie =(energie)/get_nombre_actuel();
    }
    return energie;
}

//----------------------------------------------------------------------

// Création de Macro particules
Particule Faisceau::creation_macropart()
{
    Particule part(reference, landa);
    return part;
}

//----------------------------------------------------------------------

// Ajout de Macro part dans le faisceau
void Faisceau::ajoute_macropart()
{
    faisceau.push_back(creation_macropart());
}

//----------------------------------------------------------------------

// Evolution
void Faisceau :: evolue(double dt)
{
    if(not(faisceau.empty()))
    {
        for (auto& particule : faisceau) {

            if ((particule.get_element()).passe_au_suivant(particule))
            {
                particule.change_element(particule.get_element().get_Element_suivant());
            }

            Vecteur3D champ_mag = (particule.get_element()).champ_magnetique(particule);

            particule.ajouteForceMagnetique(champ_mag, dt );


            particule.bouger(dt);
            std::cout << particule << std::endl;
        }

        if(get_nombre_actuel()< nombre_macro())
        {   ajoute_macropart();
        }
    }
}

//----------------------------------------------------------------------

//-----------------------------Affichage--------------------------------

//----------------------------------------------------------------------

// Représentation
void Faisceau::dessine()
{
    support->dessine(*this);
}

//----------------------------------------------------------------------

std::ostream& Faisceau::affiche_faisceau(std::ostream& sortie) const
{
    sortie << "---------------------------------------------------"<< std::endl;
    sortie << "Les caractéristiques du faisceau : "  << std::endl;
    sortie << std::endl;
    sortie << std::setw(24) << "Particule de référence : "  << std::endl;
    sortie << reference;
    sortie << std::setw(24) <<"Landa : " << landa << std::endl;
    sortie <<std::setw(24) << "Energie moyenne : " << energie_moy() << std::endl;
    sortie <<std::setw(24) << "Nb microparticules : " << get_nombre_actuel()*landa<< std::endl;

    return sortie;
}

//----------------------------------------------------------------------

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Surcharche de l'operateur <<
std::ostream& operator <<(std::ostream& sortie, Faisceau const& fais)
{
    return fais.affiche_faisceau(sortie);
}

//----------------------------------------------------------------------
