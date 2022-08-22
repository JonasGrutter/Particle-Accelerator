#pragma once
#include <string>
#include "Vecteur3D.h"


namespace constante {
const double c(299792458.0);
const double e(1.60217653e-19);
const Vecteur3D e3 (0,0,1);
const Vecteur3D e2 (0,1,0);
const Vecteur3D vecteur_nul(0, 0, 0);
const std::string bold ("\x1B[1m");
const std:: string fin ("\x1B[0m");
const std:: string s_jaune("\x1B[103m");
const std:: string s_cyan("\x1B[46 m");
const double kilo ((e/(c*c))*1e+9);
}
