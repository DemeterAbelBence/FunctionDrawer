#include "Dnum.hpp"

Dnum _Sin(Dnum r) { return Dnum(glm::sin(r.val), glm::cos(r.val) * r.der); }
Dnum _Cos(Dnum r) { return Dnum(glm::cos(r.val), -glm::sin(r.val) * r.der); }
Dnum _Log(Dnum r) { return Dnum(glm::log(r.val), (float)1 / r.val * r.der); }
Dnum _Exp(Dnum r) { return Dnum(glm::exp(r.val), glm::exp(r.val) * r.der); }

Dnum Dnum::operator+(Dnum r) { return Dnum(val + r.val, der + r.der); }
Dnum Dnum::operator*(Dnum r) { return Dnum(val * r.val, val * r.der + der * r.val); }
Dnum Dnum::operator/(Dnum r) { return Dnum(val / r.val, (der * r.val - val * r.der) / r.val / r.val); }
