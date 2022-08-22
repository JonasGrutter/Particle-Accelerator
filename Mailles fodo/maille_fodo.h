#include "element.h"
#include <array>

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Maille_fodo

class Maille_fodo : public Element_droit{
	
	private:
		Quadrupole el1;
		Section_droite el2;
		Quadrupole el3;
		Section_droite el4;
		
	public:
		// Constructeur
		// Position d'entrée: premier Quadrupole Position de sortie: dernière section_droite
		Maille_fodo (SupportADessin* sup, Vecteur3D pos_entree, Vecteur3D pos_sortie, double rayon_chambre,const double intensite_aimant,Element* ptr = nullptr)
		:Element_droit(sup, pos_entree, pos_sortie, rayon_chambre,ptr)
		{
			void set_maille(intensite_aimant);
		}
		
		double longueur_un_element() const;
		void set_maille(double b);
		virtual Vecteur3D champ_magnetique(Particule& p) override = 0;
		Vecteur3D add_longueur_vect() const;
	
};


