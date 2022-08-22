#include <iostream>
#include <cmath>
#include "Vecteur3D.h"
using namespace std;



//----------------------------------------------------------------------

// Fonctions/méthodes de surcharge d'opérateurs

// Opérateur d'affichage (surcharge externe)

std::ostream& Vecteur3D :: affiche(std::ostream& sortie) const // Première servant à surcharger l'opérateur << par la suite
{
    sortie << x << " " << y << " " << z << endl;
    return sortie;
}

std::ostream& operator<<(std::ostream& sortie, Vecteur3D const& v) // Sucharge de l'opérateur  <<
{
    return v.affiche(sortie);
}


// Opérateur de comparaison (surcharge interne)


bool Vecteur3D :: operator ==(const Vecteur3D& autre) const
{
    if ((x == autre.x) and (y == autre.y) and (z == autre.z)) {
        return true;
    }
    return false;
}

// Opérateurs arithmétiques

Vecteur3D& Vecteur3D :: operator+=(const Vecteur3D& autre) //+= (interne)
{
    x += autre.x;
    y += autre.y;
    z += autre.z;

    return *this;
}

const Vecteur3D operator+(Vecteur3D v1, Vecteur3D const& v2) //Addition (externe)
{
    v1 += v2;
    return v1;
}

Vecteur3D& Vecteur3D :: operator-=(const Vecteur3D& autre) //-= (interne)
{
    x -= autre.x;
    y -= autre.y;
    z -= autre.z;

    return *this;
}

const Vecteur3D operator-(Vecteur3D v1, Vecteur3D const& v2) //Soustraction binaire (externe)
{
    v1 -= v2;
    return v1;
}

const Vecteur3D operator-(Vecteur3D v) //Soustraction unaire (opposé) (externe)
{
    Vecteur3D zero;
    v = zero - v;

    return v;
}

Vecteur3D Vecteur3D :: operator*(double n) const// Multiplicaton d'un vecteur par un scalaire (interne)
{
    return Vecteur3D(n*x, n*y, n*z);
}

const Vecteur3D operator*(double n, Vecteur3D autre) // Commutativité de la multiplication
{   // d'un vecteur par un scalaire (externe)
    return autre*n;
}

double Vecteur3D :: operator*(const Vecteur3D& autre) const// Produit scalaire (interne)
{
    double res;
    res = ((x* autre.x) + (y * autre.y) + (z * autre.z));
    return res;
}

Vecteur3D Vecteur3D :: operator^(const Vecteur3D& autre) const// Produit Vectoriel (interne)
{
    return Vecteur3D(y*autre.z - z*autre.y, z*autre.x-x*autre.z, x*autre.y- y*autre.x);
}

Vecteur3D Vecteur3D:: operator~() const// Retourne un vecteur unitaire (interne)
{
    return Vecteur3D(x / norme(), y / norme(), z / norme());
}


//----------------------------------------------------------------------

// Méthodes définies par une surcharge mais gardées quand même

Vecteur3D Vecteur3D :: oppose() const // Créée un vecteur 3D Opposé à l'instance considérée
{
    double a, b, c;

    a = -x;
    b = -y;
    c = -z;

    Vecteur3D res(a, b, c);
    return res;
}


Vecteur3D Vecteur3D :: mult(double n) const // retourne un vecteurc définit comme
{   //l'instance considérée multipliée par un scalaire.
    double a, b, c;

    a = x*n;
    b = y*n;
    c = z*n;

    Vecteur3D res(a, b, c);
    return res;
}

double Vecteur3D :: prod_scal(Vecteur3D autre) const // Retourne le produit scalaire du vecteur
{   // considéré et du vecteur passé en paramètre.
    double res;

    res = (x * autre.x) + (y * autre.y) + (z * autre.z);
    return res;
}


Vecteur3D Vecteur3D :: prod_vect(Vecteur3D autre) const // Retourne un vecteur définit comme le prduit vectoriel entre
{   // le vecteur considéré et le vecteur passé en paramètre
    double a, b, c;

    a = (y*autre.z - z*autre.y);
    b = (z*autre.x-x*autre.z);
    c = (x*autre.y- y*autre.x);

    Vecteur3D res(a, b, c);
    return res;
}

Vecteur3D Vecteur3D :: unitaire() const // Retourne un vecteur unitaire
{
    double a, b, c;
    a = x / norme();
    b = y / norme();
    c = z / norme();

    Vecteur3D res(a, b, c);
    return res;

}

//----------------------------------------------------------------------

// Méthodes non définies par une surcharge

double Vecteur3D :: norme() const // Calcule la norme du vecteur considéré
{
    double res;

    res = sqrt(x*x+y*y+z*z);

    return res;
}

double Vecteur3D :: norme2() const // Calcule la norme au carré du vecteur considéré
{
    double res;

    res = (x*x+y*y+z*z);

    return res;
}

double Vecteur3D :: prod_mixte(Vecteur3D autre1, Vecteur3D autre2) const // Retourne le produit mixte entre le vecteur considéré
// et deux vecteurs
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

void Vecteur3D :: rotation(Vecteur3D a, double angle) //retourne le vecteur résultant de la rotation d'angle angle autoure de l'axe a
{
    if(not (abs(a.norme()-0) < 1e-15) )
    {
        *this = cos(angle)*(*this) + (1-cos(angle)) * ((*this) * (~a)) *(~a) + (sin(angle)*((~a)^(*this)));
    }

}
//----------------------------------------------------------------------

// getteur

double Vecteur3D :: get_x() const
{
    return x;
}

double Vecteur3D :: get_y() const
{
    return y;
}

double Vecteur3D ::get_z() const
{
    return z;
}
