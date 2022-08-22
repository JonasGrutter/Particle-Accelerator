#include <vector>
#include <array>
#include "element.h"


class Faisceau : public Dessinable
{
private :

    const Particule reference;
    std::vector<Particule> faisceau;
    double landa;
    double nombre_macro;
    const double pas_temps;

    //Axe verticale
    double emitance_verticale;
    std::array<double, 3> coeff_ellipse_verticale;

    //Axe horizontal
    double emitance_horizontale;
    std::array<double, 3> coeff_ellipse_horizontal;

public :
//----------------------------------------------------------------------
//CONSTRUCTEURS

    Faisceau(const Particule ref,  double landa_, double nombre_marco_, const double dt_)
        : reference(ref), landa(landa_), nombre_macro(nombre_marco_), pas_temps(dt_)
    {}

    virtual~Faisceau() {}
//----------------------------------------------------------------------
    void calcul_verticale();
    void calcul_horizontal();

//----------------------------------------------------------------------
    double nombre_micro() const {
        return ((landa)*get_nombre_actuel());
    }
    double get_nombre_actuel() const {
        return faisceau.size();
    }

    Particule creation_macropart();
    void ajoute_macropart();
    double energie_moy() const;

//----------------------------------------------------------------------
//EVOLUTION

    void evolue(double dt);
    void evolue_P13(double dt);
    void evolue_P14(double dt);
    void interagir(Particule& p, std::vector<Particule*> collection_part);
    void cases_voisines(Particule& p);
//----------------------------------------------------------------------

    virtual void dessine() override;

//----------------------------------------------------------------------

    std::ostream& affiche_faisceau(std::ostream& sortie) const;
};

//surcharge de l'operateur <<
std::ostream& operator <<(std::ostream& sortie, Faisceau const& fais);
