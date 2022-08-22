#include <iostream>
#include "faisceau.h"
#include "support_a_dessin.h"
#include <iomanip>
#include <cmath>
#include "Case.h"

//----------------------------------------------------------------------
//CALCUL : de l'emittance et des coefficient eliptiques(A11, A12, A22) selon l'axe z

void Faisceau::calcul_verticale()
{

    //1) Je parcours mon tableau et prend la coordonnée e2de ma position et vitesse, que je mets au carré puis on fait la moyenne
    // 	   en même temps  je prend à nouveau la coordée e2 de ma position et vitesse mais je les multiplie et fait la moyenne

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


//CALCUL : de l'emittance et des coefficient eliptiques(A11, A12, A22) selon l'axe horizontale
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
//ENERGIE

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

// Je créer des macro_particules et les ajoutent dans mon faisceau

Particule Faisceau::creation_macropart()
{
    Particule part(reference, landa);
    return part;
}

void Faisceau::ajoute_macropart()
{
    Particule part = creation_macropart();
    faisceau.push_back(part);

    int pos_case = part.get_Case();
    part.get_element().get_Echelle()[pos_case]->ajouteParticule(part);
}

//----------------------------------------------------------------------
//EVOLUE

void Faisceau :: evolue_P13(double dt)
{
    if(faisceau.empty()) return;

    for (size_t i(0); i < faisceau.size(); ++i) {

        if ((faisceau[i].get_element()).passe_au_suivant(faisceau[i]))
        {
            faisceau[i].change_element(faisceau[i].get_element().get_Element_suivant());
        }


        Vecteur3D champ_mag = (faisceau[i].get_element()).champ_magnetique(faisceau[i]);
        std::cout << champ_mag << std::endl;


        faisceau[i].ajouteForceMagnetique(champ_mag, dt );


        for (size_t j(i+1); j< faisceau.size(); ++j) {

            Vecteur3D distance;
            distance = ((faisceau[j].get_pos())-(faisceau[i].get_pos()));

            double scalaire;
            scalaire = constante::epsilon_4pi * ((faisceau[j].get_gamma())*(faisceau[j].get_gamma()));
            scalaire = scalaire * ((distance.norme())*(distance.norme())*(distance.norme()));
            scalaire = scalaire / (faisceau[j].get_charge()) *(faisceau[j].get_charge());

            Vecteur3D F;
            F = scalaire*distance;
            F += faisceau[i].get_force();

            faisceau[i].set_force(F);
            faisceau[j].set_force(-F);

        }

        faisceau[i].bouger(dt);
        std::cout << faisceau[i]<< std::endl;

    }

    if(get_nombre_actuel()< nombre_macro)
    {   ajoute_macropart();
    }


}



void Faisceau :: evolue_P14(double dt)
{
    if(faisceau.empty()) return;


    for (size_t i(0); i < faisceau.size(); ++i) {

        if ((faisceau[i].get_element()).passe_au_suivant(faisceau[i]))
        {
            faisceau[i].change_element(faisceau[i].get_element().get_Element_suivant());
        }


        Vecteur3D champ_mag = (faisceau[i].get_element()).champ_magnetique(faisceau[i]);
        std::cout << champ_mag << std::endl;


        faisceau[i].ajouteForceMagnetique(champ_mag, dt);

        int pos_case = faisceau[i].get_Case();
        cases_voisines(faisceau[i]);

        faisceau[i].bouger(dt);
        std::cout << faisceau[i]<< std::endl;


        int newpos_case = faisceau[i].get_Case();
        if(pos_case!=newpos_case)
            faisceau[i].get_element().get_Echelle()[newpos_case]->ajouteParticule(faisceau[i]);
        faisceau[i].get_element().get_Echelle()[pos_case]->supprimeParticule(faisceau[i]);

    }
    if(get_nombre_actuel()< nombre_macro)
    {   ajoute_macropart();
    }

}

void Faisceau::cases_voisines(Particule& part)
{
    int pos_case = part.get_Case();
    interagir(part,part.get_element().get_Echelle()[pos_case]->get_Particule() );

    int taille_Echelle = part.get_element().get_Echelle().size();

    if((pos_case!= 0) and(pos_case!=taille_Echelle-1))
    {
        for(size_t j(-1); j <=2; ++j)
        {
            interagir(part,part.get_element().get_Echelle()[pos_case+j]->get_Particule() );
        }

    } else if(pos_case == 0)
    {
        interagir(part,part.get_element().get_Echelle()[pos_case+1]->get_Particule() );

        int derniere_case = part.get_element().get_Element_precedent().get_Echelle().size()-1;

        interagir(part,part.get_element().get_Element_precedent().get_Echelle()[derniere_case]->get_Particule());


    } else if (pos_case == taille_Echelle-1)
    {
        interagir(part,part.get_element().get_Echelle()[pos_case-1]->get_Particule() );
        interagir(part,part.get_element().get_Element_suivant().get_Echelle()[0]->get_Particule());
    }
}


void Faisceau::interagir(Particule& p, std::vector<Particule*> collection_part)
{
    for (auto& part : collection_part)
    {
        Vecteur3D distance;
        distance = ((part->get_pos())-(p.get_pos()));
        if((distance.norme() <= 1e-7) and(distance.norme() != 0.0))
        {
            double scalaire;
            scalaire = constante::epsilon_4pi *((part->get_gamma())*(part->get_gamma()));
            scalaire = ((distance.norme())*(distance.norme())*(distance.norme()));
            scalaire = scalaire / (part->get_charge() * part->get_charge());

            Vecteur3D F;
            F = scalaire*distance;
            F += p.get_force();

            p.set_force(F);
            part->set_force(-F);
        }
    }
}


//----------------------------------------------------------------------
// la méthode dessine, relative à toutes les sous_classes de dessinable
void Faisceau::dessine()
{
    support->dessine(*this);
}

//----------------------------------------------------------------------
//AFFICHAGE

// une methode interne, utiliser pour la surcharche
std::ostream& Faisceau::affiche_faisceau(std::ostream& sortie) const
{
    sortie << constante::bold <<  "Les caractéristiques du faisceau : " << constante::fin << std::endl;
    sortie << std::setw(24) << "Particule de référence : "  << std::endl;
    sortie << reference;
    sortie << std::setw(24) <<"Landa : " << landa << std::endl;
    sortie <<std::setw(24) << "Energie moyenne : " << energie_moy() << std::endl;
    sortie <<std::setw(24) << "Nb microparticules : " << nombre_micro()<< std::endl;

    return sortie;
}

//methode externe, surcharche de l'operateur <<
std::ostream& operator <<(std::ostream& sortie, Faisceau const& fais)
{
    return fais.affiche_faisceau(sortie);
}
