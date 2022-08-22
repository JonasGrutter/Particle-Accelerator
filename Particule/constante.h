#pragma once
#include <string>
#include "Vecteur3D.h"

//----------------------------------------------------------------------
//--------------------Constantes de l'accélérateur----------------------
//----------------------------------------------------------------------

namespace constante {
const double c(299792458.0);
const double e(1.60217653e-19);
const Vecteur3D e3 (0,0,1);
const Vecteur3D e2 (0,1,0);
const Vecteur3D vecteur_nul(0, 0, 0);
const double kilo ((e/(c*c))*1e+9);
}

//----------------------------------------------------------------------
