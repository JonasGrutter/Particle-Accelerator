#include <iostream>
#include <cmath>
#include "Vecteur3D.h"
using namespace std;

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

//----------------------------------------------------------------------
//---------------Méthodes associées à la classe Vecteur3D---------------
//----------------------------------------------------------------------

//------------------Méthodes de surcharge d'opérateurs------------------

//----------------------------------------------------------------------

// Opérateur d'affichage (surcharge externe)
std::ostream& Vecteur3D :: affiche(std::ostream& sortie) const // Première servant à surcharger l'opérateur << par la suite
{
		sortie << x << " " << y << " " << z;
		return sortie;
}

//----------------------------------------------------------------------

// Opérateur de comparaison ==
bool Vecteur3D :: operator ==(const Vecteur3D& autre) const
{
	if ((x == autre.x) and (y == autre.y) and (z == autre.z)){
		return true;
	}
	return false;
}

//----------------------------------------------------------------------

// Opérateur +=
Vecteur3D& Vecteur3D :: operator +=(const Vecteur3D& autre)
{
	x += autre.x;
	y += autre.y;
	z += autre.z;
	
	return *this;
}

//----------------------------------------------------------------------

// Opérateur -=
Vecteur3D& Vecteur3D :: operator -=(const Vecteur3D& autre)
{
	x -= autre.x;
	y -= autre.y;
	z -= autre.z;
	
	return *this;
}

//----------------------------------------------------------------------

// Opérateur * (Produit scalaire)
double Vecteur3D :: operator*(const Vecteur3D& autre) const
{
	double res;
	res = ((x* autre.x) + (y * autre.y) + (z * autre.z));
	return res;
}

//----------------------------------------------------------------------

// Opérateur * (Multiplication d'un vecteur par un scalaire)
Vecteur3D Vecteur3D :: operator *(double n) const
{
	return Vecteur3D(n*x, n*y, n*z);
}

//----------------------------------------------------------------------

// Opérateur ^ (Produit vectoriel)
Vecteur3D Vecteur3D :: operator^(const Vecteur3D& autre) const
{
	return Vecteur3D(y*autre.z - z*autre.y, z*autre.x-x*autre.z, x*autre.y- y*autre.x);
}

//----------------------------------------------------------------------

// Opérateur ~ (Retourne un vecteur unitaire)
Vecteur3D Vecteur3D:: operator~() const
{
	return Vecteur3D(x / norme(), y / norme(), z / norme());
}

//----------------------------------------------------------------------

//-------------------------------Getters--------------------------------

//----------------------------------------------------------------------

// Coordonnée x
double Vecteur3D :: get_x() const
{
	return x;
}

//----------------------------------------------------------------------

// Coordonnée y
double Vecteur3D :: get_y() const
{
	return y;
}

//----------------------------------------------------------------------

// Coordonnée z
double Vecteur3D ::get_z() const
{
	return z;
}

//----------------------------------------------------------------------

//-----------Méthodes définies par une surcharge mais gardées-----------

//----------------------------------------------------------------------

// Créée un vecteur 3D Opposé à l'instance considérée
Vecteur3D Vecteur3D :: oppose() const
{ 
	double a, b, c;
	
	a = -x;
	b = -y;
	c = -z;
	
	Vecteur3D res(a, b, c);
	return res;
}

//----------------------------------------------------------------------

// Produit scalaire
double Vecteur3D :: prod_scal(Vecteur3D autre) const
{										
	double res;
	
	res = (x * autre.x) + (y * autre.y) + (z * autre.z);
	return res;
}

//----------------------------------------------------------------------

// Produit vectoriel
Vecteur3D Vecteur3D :: prod_vect(Vecteur3D autre) const 
{												
	double a, b, c;
	
	a = (y*autre.z - z*autre.y);
	b = (z*autre.x-x*autre.z);
	c = (x*autre.y- y*autre.x);
	
	Vecteur3D res(a, b, c);
	return res;
}

//----------------------------------------------------------------------

// Multiplication d'un vecteur par un scalaire
Vecteur3D Vecteur3D :: mult(double n) const 
{											
	double a, b, c;
	
	a = x*n;
	b = y*n;
	c = z*n;
	
	Vecteur3D res(a, b, c);
	return res; 
}

//----------------------------------------------------------------------

// Retourne un vecteur unitaire
Vecteur3D Vecteur3D :: unitaire() const //
{
	double a, b, c;
	a = x / norme();
	b = y / norme();
	c = z / norme();
	
	Vecteur3D res(a, b, c);
	return res;
	
}

//----------------------------------------------------------------------

//---------------Méthodes non définies par une surcharge----------------

//----------------------------------------------------------------------

// Norme
double Vecteur3D :: norme() const
{
	double res;
	
	res = sqrt(x*x+y*y+z*z);
	
	return res;
}

//----------------------------------------------------------------------

// Norme au carré
double Vecteur3D :: norme2() const 
{
	double res;
	
	res = (x*x+y*y+z*z);
	
	return res;
}

//----------------------------------------------------------------------

// Produit mixte
double Vecteur3D :: prod_mixte(Vecteur3D autre1, Vecteur3D autre2) const
																		
{
	double res;
	double precision = 1e-15;
	Vecteur3D temp;
	
	temp = prod_vect(autre1);
	res = temp * autre2;
	if (res < precision) {
		 res = 0;
		}
	
	return res;
}

// Rotation d'angle angle autoure de l'axe a
void Vecteur3D :: rotation(Vecteur3D a, double angle)
{
	if(not (abs(a.norme()-0) < 1e-15) ) {
		*this = cos(angle)*(*this) + (1-cos(angle)) * ((*this) * (~a)) *(~a) + (sin(angle)*((~a)^(*this)));
	}

}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//---------------Fonctions associées à la classe Vecteur3D--------------
//----------------------------------------------------------------------

//-----------------Fonctions de surcharge d'opérateurs------------------

//----------------------------------------------------------------------

// Sucharge de l'opérateur  <<
std::ostream& operator<<(std::ostream& sortie, Vecteur3D const& v)  
{
	return v.affiche(sortie);
}

//----------------------------------------------------------------------

// Opérateur +
const Vecteur3D operator +(Vecteur3D v1, Vecteur3D const& v2)
{
	v1 += v2;
	return v1;
}

//----------------------------------------------------------------------

// Opérateur - (Soustraction binaire)
const Vecteur3D operator -(Vecteur3D v1, Vecteur3D const& v2)
{
	v1 -= v2;
	return v1;
}

//----------------------------------------------------------------------

// Opérateur - (Soustraction unaire)
const Vecteur3D operator -(Vecteur3D v) //Soustraction unaire (opposé) (externe)
{	
	Vecteur3D zero;
	 v = zero - v;
	
	return v;
}

//----------------------------------------------------------------------

// Opérateur *(Commutativité de la multiplication d'un vecteur par un scalaire)
const Vecteur3D operator*(double n, Vecteur3D autre)
{
	return autre*n;
}

//**********************************************************************
//----------------------------------------------------------------------
//**********************************************************************

