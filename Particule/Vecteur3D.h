#pragma once
#include <cmath>
#include <iostream>

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

// Définition de la classe Vecteur3D
class Vecteur3D {

private:
	// Attributs 
	double x;
	double y;
	double z;
	
public:
	// Constructeur
	explicit Vecteur3D(double x = 0, double y = 0, double z = 0)
	: x(x), 
	y(y), 
	z(z)
	{}
	
	// Méthodes de surcharge d'opérateurs (surcharge interne)
	// Opérateur d'affichage
	std::ostream& affiche(std::ostream& sortie) const;
	// Opérateurs arithmétiques
	bool operator ==(const Vecteur3D& v) const;
	Vecteur3D& operator +=(const Vecteur3D& autre);
	Vecteur3D& operator -=(const Vecteur3D& autre);
	double operator *(const Vecteur3D& autre) const; 
	Vecteur3D operator *(double n) const;
	Vecteur3D operator ^(const Vecteur3D& autre) const;
	Vecteur3D operator ~() const;
	
	// Getters
	double get_x() const;
	double get_y() const;
	double get_z() const;
	
	
	// Méthodes définies par une surcharge mais gardées
	Vecteur3D oppose() const;
	double prod_scal(Vecteur3D autre) const;
	Vecteur3D prod_vect(Vecteur3D autre) const;
	Vecteur3D unitaire() const;
	Vecteur3D mult(double n) const;
	
	// Méthodes non définies par une surcharge
	double norme() const;
	double norme2() const;
	double prod_mixte(Vecteur3D autre1, Vecteur3D autre2) const;
	void rotation (Vecteur3D a, double angle);
	
};


// Fonctions de surcharges d'opérateurs (surcharge externe)
// Opérateur d'affichage
std::ostream& operator<<(std::ostream& sortie, Vecteur3D const& v);
// Opérateurs arithmétiques
const Vecteur3D operator+(Vecteur3D v1, Vecteur3D const& v2);
const Vecteur3D operator-(Vecteur3D v1, Vecteur3D const& v2); 
const Vecteur3D operator-(Vecteur3D v);
const Vecteur3D operator*(double n, Vecteur3D autre);

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************
