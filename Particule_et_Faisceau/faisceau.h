#include <vector>
#include <array>
#include "element.h"

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Accelerateur
class Faisceau : public Dessinable
{
private :
	// Attributs
    const Particule reference;
    std::vector<Particule> faisceau;
    double landa;
    double nombre_micro;

    //Axe verticale
    double emitance_verticale;
    std::array<double, 3> coeff_ellipse_verticale;

    //Axe horizontal
    double emitance_horizontale;
    std::array<double, 3> coeff_ellipse_horizontal;

public :
	// Constructeur
    Faisceau(const Particule ref,  double landa_, double nombre_micro_)
        : reference(ref), landa(landa_), nombre_micro(nombre_micro_)
    {}

	// Méthode
    void calcul_verticale();
    void calcul_horizontal();
    double nombre_macro() const { return (nombre_micro/landa);}
	double get_nombre_actuel() const { return faisceau.size();}
    Particule creation_macropart();
    void ajoute_macropart();
    double energie_moy() const;
    void evolue(double dt);

	// Représentation
    virtual void dessine() override;
    // Affichage
    std::ostream& affiche_faisceau(std::ostream& sortie) const;
};

//surcharge de l'operateur <<
std::ostream& operator <<(std::ostream& sortie, Faisceau const& fais);

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************
