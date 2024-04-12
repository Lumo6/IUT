//Pour éviter les problèmes, ce fichier doit être enregistré au format UTF-8
//Grâce à ce commentaire qui contient des caractères accentués, c'est le cas.

#include "test.h"
#include "angle.h"
#include <sstream>
#include <iomanip>
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

int main()
{
#ifdef _WIN32
  SetConsoleOutputCP(65001);
#endif // _WIN32
  BEGIN_TESTS;
  //Pour simuler une programmation en mode TDD, vous devez décommenter le code suivant bloc de test par bloc de test.
  //Les débuts et fins des blocs de test sont repéré par les lignes vides.
  //A chaque bloc décommenté, vous devez vous assurer que le programme compile et s'exécute sans erreurs.
  
    NOTICE("Test de la classe CDoubleApprox");
    CDoubleApprox da(1.0);
    TEST("Construction depuis un double", da.to_double(), 1.0);

    //Pour que les prochains tests fonctionnent, vous devez rajouter dans le fichier DoubleApprox.h les deux
    //lignes suivantes, à la suite de la déclaration de la classe CDoubleApprox :
    //inline CDoubleApprox operator ""_da(long double val) { return CDoubleApprox((double)val); }
    //inline CDoubleApprox operator ""_da(unsigned long long val) { return CDoubleApprox((double)val); }

    TEST("Construction depuis un double - syntaxe literals", 1.0_da.to_double(), 1.0);
    TEST("Construction depuis un int - syntaxe literals", 1_da.to_double(), 1.0);

    TEST("Opérateur == (entre un CDoubleApprox et un CDoubleApprox)", 1_da == 1_da, true);
    TEST("Opérateur == (entre un CDoubleApprox et un CDoubleApprox)", 1_da == CDoubleApprox(1 + 9e-11), true);
    TEST("Opérateur == (entre un CDoubleApprox et un CDoubleApprox)", 1_da == CDoubleApprox(1 + 2e-10), false);

    TEST("Opérateur == (entre un CDoubleApprox et un double)", 1_da == 1.0, true);
    TEST("Opérateur == (entre un CDoubleApprox et un double)", 1_da == 1 + 9e-11, true);
    TEST("Opérateur == (entre un CDoubleApprox et un double)", 1_da == 1 + 2e-10, false);

    TEST("Opérateur == (entre un double et un CDoubleApprox)", 1.0 == 1_da, true);
    TEST("Opérateur == (entre un double et un CDoubleApprox)", 1.0 == CDoubleApprox(1 + 9e-11), true);
    TEST("Opérateur == (entre un double et un CDoubleApprox)", 1.0 == CDoubleApprox(1 + 2e-10), false);

    TEST("Opérateur != (entre un CDoubleApprox et un CDoubleApprox)", 1_da != 1_da, false);
    TEST("Opérateur != (entre un CDoubleApprox et un CDoubleApprox)", 1_da != CDoubleApprox(1 + 9e-11), false);
    TEST("Opérateur != (entre un CDoubleApprox et un CDoubleApprox)", 1_da != CDoubleApprox(1 + 2e-10), true);

    TEST("Opérateur != (entre un CDoubleApprox et un double)", 1_da != 1.0, false);
    TEST("Opérateur != (entre un CDoubleApprox et un double)", 1_da != 1 + 9e-11, false);
    TEST("Opérateur != (entre un CDoubleApprox et un double)", 1_da != 1 + 2e-10, true);

    TEST("Opérateur != (entre un double et un CDoubleApprox)", 1.0 != 1_da, false);
    TEST("Opérateur != (entre un double et un CDoubleApprox)", 1.0 != CDoubleApprox(1 + 9e-11), false);
    TEST("Opérateur != (entre un double et un CDoubleApprox)", 1.0 != CDoubleApprox(1 + 2e-10), true);

    TEST("Opérateur > (entre un CDoubleApprox et un CDoubleApprox)", 1_da > 1_da, false);
    TEST("Opérateur > (entre un CDoubleApprox et un CDoubleApprox)", 1_da > CDoubleApprox(1 + 9e-11), false);
    TEST("Opérateur > (entre un CDoubleApprox et un CDoubleApprox)", 1_da > CDoubleApprox(1 + 2e-10), false);
    TEST("Opérateur > (entre un CDoubleApprox et un CDoubleApprox)", 1_da > CDoubleApprox(1 - 2e-10), true);

    TEST("Opérateur > (entre un CDoubleApprox et un double)", 1_da > 1.0, false);
    TEST("Opérateur > (entre un CDoubleApprox et un double)", 1_da > 1 + 9e-11, false);
    TEST("Opérateur > (entre un CDoubleApprox et un double)", 1_da > 1 + 2e-10, false);
    TEST("Opérateur > (entre un CDoubleApprox et un double)", 1_da > 1 - 2e-10, true);

    TEST("Opérateur > (entre un double et un CDoubleApprox)", 1.0 > 1_da, false);
    TEST("Opérateur > (entre un double et un CDoubleApprox)", 1.0 > CDoubleApprox(1 + 9e-11), false);
    TEST("Opérateur > (entre un double et un CDoubleApprox)", 1.0 > CDoubleApprox(1 + 2e-10), false);
    TEST("Opérateur > (entre un double et un CDoubleApprox)", 1.0 > CDoubleApprox(1 - 2e-10), true);

    TEST("Opérateur < (entre un CDoubleApprox et un CDoubleApprox)", 1_da < 1_da, false);
    TEST("Opérateur < (entre un CDoubleApprox et un CDoubleApprox)", 1_da < CDoubleApprox(1 + 9e-11), false);
    TEST("Opérateur < (entre un CDoubleApprox et un CDoubleApprox)", 1_da < CDoubleApprox(1 + 2e-10), true);
    TEST("Opérateur < (entre un CDoubleApprox et un CDoubleApprox)", 1_da < CDoubleApprox(1 - 2e-10), false);

    TEST("Opérateur < (entre un CDoubleApprox et un double)", 1_da < 1.0, false);
    TEST("Opérateur < (entre un CDoubleApprox et un double)", 1_da < 1 + 9e-11, false);
    TEST("Opérateur < (entre un CDoubleApprox et un double)", 1_da < 1 + 2e-10, true);
    TEST("Opérateur < (entre un CDoubleApprox et un double)", 1_da < 1 - 2e-10, false);

    TEST("Opérateur < (entre un double et un CDoubleApprox)", 1.0 < 1_da, false);
    TEST("Opérateur < (entre un double et un CDoubleApprox)", 1.0 < CDoubleApprox(1 + 9e-11), false);
    TEST("Opérateur < (entre un double et un CDoubleApprox)", 1.0 < CDoubleApprox(1 + 2e-10), true);
    TEST("Opérateur < (entre un double et un CDoubleApprox)", 1.0 < CDoubleApprox(1 - 2e-10), false);

    TEST("Opérateur >= (entre un CDoubleApprox et un CDoubleApprox)", 1_da >= 1_da, true);
    TEST("Opérateur >= (entre un CDoubleApprox et un CDoubleApprox)", 1_da >= CDoubleApprox(1 + 9e-11), true);
    TEST("Opérateur >= (entre un CDoubleApprox et un CDoubleApprox)", 1_da >= CDoubleApprox(1 + 2e-10), false);
    TEST("Opérateur >= (entre un CDoubleApprox et un CDoubleApprox)", 1_da >= CDoubleApprox(1 - 2e-10), true);

    TEST("Opérateur >= (entre un CDoubleApprox et un double)", 1_da >= 1.0, true);
    TEST("Opérateur >= (entre un CDoubleApprox et un double)", 1_da >= 1 + 9e-11, true);
    TEST("Opérateur >= (entre un CDoubleApprox et un double)", 1_da >= 1 + 2e-10, false);
    TEST("Opérateur >= (entre un CDoubleApprox et un double)", 1_da >= 1 - 2e-10, true);

    TEST("Opérateur >= (entre un double et un CDoubleApprox)", 1.0 >= 1_da, true);
    TEST("Opérateur >= (entre un double et un CDoubleApprox)", 1.0 >= CDoubleApprox(1 + 9e-11), true);
    TEST("Opérateur >= (entre un double et un CDoubleApprox)", 1.0 >= CDoubleApprox(1 + 2e-10), false);
    TEST("Opérateur >= (entre un double et un CDoubleApprox)", 1.0 >= CDoubleApprox(1 - 2e-10), true);

    TEST("Opérateur <= (entre un CDoubleApprox et un CDoubleApprox)", 1_da <= 1_da, true);
    TEST("Opérateur <= (entre un CDoubleApprox et un CDoubleApprox)", 1_da <= CDoubleApprox(1 + 9e-11), true);
    TEST("Opérateur <= (entre un CDoubleApprox et un CDoubleApprox)", 1_da <= CDoubleApprox(1 + 2e-10), true);
    TEST("Opérateur <= (entre un CDoubleApprox et un CDoubleApprox)", 1_da <= CDoubleApprox(1 - 2e-10), false);

    TEST("Opérateur <= (entre un CDoubleApprox et un double)", 1_da <= 1.0, true);
    TEST("Opérateur <= (entre un CDoubleApprox et un double)", 1_da <= 1 + 9e-11, true);
    TEST("Opérateur <= (entre un CDoubleApprox et un double)", 1_da <= 1 + 2e-10, true);
    TEST("Opérateur <= (entre un CDoubleApprox et un double)", 1_da <= 1 - 2e-10, false);

    TEST("Opérateur <= (entre un double et un CDoubleApprox)", 1.0 <= 1_da, true);
    TEST("Opérateur <= (entre un double et un CDoubleApprox)", 1.0 <= CDoubleApprox(1 + 9e-11), true);
    TEST("Opérateur <= (entre un double et un CDoubleApprox)", 1.0 <= CDoubleApprox(1 + 2e-10), true);
    TEST("Opérateur <= (entre un double et un CDoubleApprox)", 1.0 <= CDoubleApprox(1 - 2e-10), false);

    TEST("Opérateur - (unaire)", (-1_da).to_double(), -1.0);
    TEST("Opérateur + (uniare)", (+1_da).to_double(), +1.0);

    TEST("Opérateur * (entre un CDoubleApprox et un CDoubleApprox)", 2_da * 3_da, 6);
    TEST("Opérateur * (entre un CDoubleApprox et un double)", 2_da * 3.0, 6);
    TEST("Opérateur * (entre un double et un CDoubleApprox)", 2.0 * 3_da, 6);

    TEST("Opérateur + (entre un CDoubleApprox et un CDoubleApprox)", 2_da + 3_da, 5);
    TEST("Opérateur + (entre un CDoubleApprox et un double)", 2_da + 3.0, 5);
    TEST("Opérateur + (entre un double et un CDoubleApprox)", 2.0 + 3_da, 5);

    TEST("Opérateur - (entre un CDoubleApprox et un CDoubleApprox)", 2_da - 3_da, -1);
    TEST("Opérateur - (entre un CDoubleApprox et un double)", 2_da - 3.0, -1);
    TEST("Opérateur - (entre un double et un CDoubleApprox)", 2.0 - 3_da, -1);

    TEST("Opérateur / (entre un CDoubleApprox et un CDoubleApprox)", 2_da / 3_da, 2.0 / 3.0);
    TEST("Opérateur / (entre un CDoubleApprox et un double)", 2_da / 3.0, 2.0 / 3.0);
    TEST("Opérateur / (entre un double et un CDoubleApprox)", 2.0 / 3_da, 2.0 / 3.0);

    da = 2;
    double d = 2;
    TEST("Opérateur *= (entre un CDoubleApprox et un CDoubleApprox)", da *= 3_da, 6);
    TEST("Opérateur *= (entre un CDoubleApprox et un double)", da *= 3.0, 18);
    TEST("Opérateur *= (entre un double et un CDoubleApprox)", d *= 3_da, 6);

    TEST("Opérateur += (entre un CDoubleApprox et un CDoubleApprox)", da += 3_da, 21);
    TEST("Opérateur += (entre un CDoubleApprox et un double)", da += 3.0, 24);
    TEST("Opérateur += (entre un double et un CDoubleApprox)", d += 3_da, 9);

    TEST("Opérateur -= (entre un CDoubleApprox et un CDoubleApprox)", da -= 3_da, 21);
    TEST("Opérateur -= (entre un CDoubleApprox et un double)", da -= 3.0, 18);
    TEST("Opérateur -= (entre un double et un CDoubleApprox)", d -= 3_da, 6);

    TEST("Opérateur /= (entre un CDoubleApprox et un CDoubleApprox)", da /= 3_da, 6.0);
    TEST("Opérateur /= (entre un CDoubleApprox et un double)", da /= 3.0, 2.0);
    TEST("Opérateur /= (entre un double et un CDoubleApprox)", d /= 3_da, 2.0);




   NOTICE("Test de la classe CAngle");
    CAngle angle1;
    TEST("Initialisation : CAngle angle1", angle1.Rad(), 0_da);
    CAngle angle2(1);
    TEST("Constructeur à 1 paramètre : CAngle angle2(1)", angle2.Rad(), 1_da);

    NOTICE("  S'assure que les angles sont compris dans l'intervalle [-pi, pi[");
    CAngle angle3(pi);
    TEST("Constructeur à 1 paramètre : CAngle angle3(pi)", angle3.Rad(), CDoubleApprox(-pi));
    CAngle angle4(10 * pi + 1);
    TEST("Constructeur à 1 paramètre : CAngle angle4(10 * pi + 1)", angle4.Rad(), 1_da);
    CAngle angle5(-pi);
    TEST("Constructeur à 1 paramètre : CAngle angle5(-pi)", angle5.Rad(), CDoubleApprox(-pi));
    CAngle angle6(-10 * pi + 1);
    TEST("Constructeur à 1 paramètre : CAngle angle6(-10 * pi + 1)", angle6.Rad(), 1_da);

    NOTICE("\nAccesseurs (écriture en radians, lecture en radians)");
    CAngle angle;
    angle.SetRad(0);
    TEST("SetRad(0)", angle.Rad(), 0_da);
    angle.SetRad(1);
    TEST("SetRad(1)", angle.Rad(), 1_da);
    NOTICE("  S'assure que les angles sont compris dans l'intervalle [-pi, pi[");
    angle.SetRad(pi);
    TEST("SetRad(pi)", angle.Rad(), CDoubleApprox(-pi));
    angle.SetRad(10 * pi + 1);
    TEST("SetRad(10 * pi + 1)", angle.Rad(), 1_da);
    angle.SetRad(-pi);
    TEST("SetRad(-pi)", angle.Rad(), CDoubleApprox(-pi));
    angle.SetRad(-10 * pi + 1);
    TEST("SetRad(-10 * pi + 1)", angle.Rad(), 1_da);

    NOTICE("\nAccesseurs (écriture en radians, lecture en degrés)");
    angle.SetRad(0);
    TEST("SetRad(0)", angle.Deg(), 0_da);
    angle.SetRad(1);
    TEST("SetRad(1)", angle.Deg(), 180_da / pi);
    NOTICE("  S'assure que les angles sont compris dans l'intervalle [-180, 180[");
    angle.SetRad(pi);
    TEST("SetRad(pi)", angle.Deg(), -180_da);
    angle.SetRad(10 * pi + 1);
    TEST("SetRad(10 * pi + 1)", angle.Deg(), 180_da / pi);
    angle.SetRad(-pi);
    TEST("SetRad(-pi)", angle.Deg(), -180_da);
    angle.SetRad(-10 * pi + 1);
    TEST("SetRad(-10 * pi + 1)", angle.Deg(), 180_da / pi);

    NOTICE("\nAccesseurs (écriture en degrés, lecture en radians)");
    angle.SetDeg(0);
    TEST("SetDeg(0)", angle.Rad(), 0_da);
    angle.SetDeg(1);
    TEST("SetDeg(1)", angle.Rad(), pi / 180_da);
    NOTICE("  S'assure que les angles sont compris dans l'intervalle [-pi, pi[");
    angle.SetDeg(180);
    TEST("SetDeg(180)", angle.Rad(), CDoubleApprox(-pi));
    angle.SetDeg(-180);
    TEST("SetDeg(-180)", angle.Rad(), CDoubleApprox(-pi));
    angle.SetDeg(360);
    TEST("SetDeg(360)", angle.Rad(), 0_da);
    angle.SetDeg(-360);
    TEST("SetDeg(-360)", angle.Rad(), 0_da);

    NOTICE("\nAccesseurs (écriture en degrés, lecture en degrés)");
    angle.SetDeg(0);
    TEST("SetDeg(0)", angle.Deg(), 0_da);
    angle.SetDeg(1);
    TEST("SetDeg(1)", angle.Deg(), 1_da);
    NOTICE("  S'assure que les angles sont compris dans l'intervalle [-180, 180[");
    angle.SetDeg(180);
    TEST("SetDeg(180)", angle.Deg(), -180_da);
    angle.SetDeg(-180);
    TEST("SetDeg(-180)", angle.Deg(), -180_da);
    angle.SetDeg(360);
    TEST("SetDeg(360)", angle.Deg(), 0_da);
    angle.SetDeg(-360);
    TEST("SetDeg(-360)", angle.Deg(), 0_da);

    NOTICE("\nAccesseurs (écriture en radians, lecture en gradians)");
    angle.SetRad(0);
    TEST("SetRad(0)", angle.Grad(), 0_da);
    angle.SetRad(1);
    TEST("SetRad(1)", angle.Grad(), 200_da / pi);
    NOTICE("  S'assure que les angles sont compris dans l'intervalle [-200, 200[");
    angle.SetRad(pi);
    TEST("SetRad(pi)", angle.Grad(), -200_da);
    angle.SetRad(10 * pi + 1);
    TEST("SetRad(10 * pi + 1)", angle.Grad(), 200_da / pi);
    angle.SetRad(-pi);
    TEST("SetRad(-pi)", angle.Grad(), -200_da);
    angle.SetRad(-10 * pi + 1);
    TEST("SetRad(-10 * pi + 1)", angle.Grad(), 200_da / pi);

    NOTICE("\nAccesseurs (écriture en gradians, lecture en gradians)");
    angle.SetGrad(0);
    TEST("SetGrad(0)", angle.Grad(), 0_da);
    angle.SetGrad(1);
    TEST("SetGrad(1)", angle.Grad(), 1_da);
    NOTICE("  S'assure que les angles sont compris dans l'intervalle [-200, 200[");
    angle.SetGrad(200);
    TEST("SetGrad(200)", angle.Grad(), -200_da);
    angle.SetGrad(-200);
    TEST("SetGrad(-200)", angle.Grad(), -200_da);
    angle.SetGrad(400);
    TEST("SetGrad(400)", angle.Grad(), 0_da);
    angle.SetGrad(-400);
    TEST("SetGrad(-400)", angle.Grad(), 0_da);

    NOTICE("\nOpérateur de sortie vers flux");
    std::stringstream sstr;
    sstr << CAngle(pi);
    TEST("sstr << CAngle(pi)", sstr.str(), "-3.14159 (-180° / -200 grad)");

    NOTICE("\nOpérateur d'affectation depuis un double (automatique grâce au constructeur depuis un double)");
    TEST("angle = pi", (angle = pi).Rad(), CDoubleApprox(-pi));
    TEST("angle = 10 * pi + 1", (angle = 10 * pi + 1).Rad(), 1_da);
    TEST("angle = -pi", (angle = -pi).Rad(), CDoubleApprox(-pi));
    TEST("angle = -10 * pi + 1", (angle = -10 * pi + 1).Rad(), 1_da);

    NOTICE("\nOpérateur == par rapport à autre angle");
    TEST("(angle = pi) == CAngle(-pi)", (angle = pi) == CAngle(-pi), true);
    TEST("(angle = pi) == CAngle(0)", (angle = pi) == CAngle(0), false);
    TEST("(angle = 10 * pi + 1) == CAngle(1)", (angle = 10 * pi + 1) == CAngle(1), true);
    TEST("(angle = 10 * pi + 1) == CAngle(0)", (angle = 10 * pi + 1) == CAngle(0), false);
    TEST("(angle = -pi) == CAngle(-pi)", (angle = -pi) == CAngle(-pi), true);
    TEST("(angle = -pi) == CAngle(0)", (angle = -pi) == CAngle(0), false);
    TEST("(angle = -10 * pi + 1) == CAngle(1)", (angle = -10 * pi + 1) == CAngle(1), true);
    TEST("(angle = -10 * pi + 1) == CAngle(0)", (angle = -10 * pi + 1) == CAngle(0), false);

    NOTICE("\nOpérateur != par rapport à autre angle");
    TEST("(angle = pi) != CAngle(-pi)", (angle = pi) != CAngle(-pi), false);
    TEST("(angle = pi) != CAngle(0)", (angle = pi) != CAngle(0), true);
    TEST("(angle = 10 * pi + 1) != CAngle(1)", (angle = 10 * pi + 1) != CAngle(1), false);
    TEST("(angle = 10 * pi + 1) != CAngle(0)", (angle = 10 * pi + 1) != CAngle(0), true);
    TEST("(angle = -pi) != CAngle(-pi)", (angle = -pi) != CAngle(-pi), false);
    TEST("(angle = -pi) != CAngle(0)", (angle = -pi) != CAngle(0), true);
    TEST("(angle = -10 * pi + 1) != CAngle(1)", (angle = -10 * pi + 1) != CAngle(1), false);
    TEST("(angle = -10 * pi + 1) != CAngle(0)", (angle = -10 * pi + 1) != CAngle(0), true);

    NOTICE("\nOpérateur == par rapport à un double");
    TEST("(angle = pi) == -pi", (angle = pi) == -pi, true);
    TEST("(angle = pi) == 0", (angle = pi) == 0, false);
    TEST("(angle = 10 * pi + 1) == 1", (angle = 10 * pi + 1) == 1, true);
    TEST("(angle = 10 * pi + 1) == 0", (angle = 10 * pi + 1) == 0, false);
    TEST("(angle = -pi) == -pi", (angle = -pi) == -pi, true);
    TEST("(angle = -pi) == 0", (angle = -pi) == 0, false);
    TEST("(angle = -10 * pi + 1) == 1", (angle = -10 * pi + 1) == 1, true);
    TEST("(angle = -10 * pi + 1) == 0", (angle = -10 * pi + 1) == 0, false);

    NOTICE("\nOpérateur != par rapport à un double");
    TEST("(angle = pi) != -pi", (angle = pi) != -pi, false);
    TEST("(angle = pi) != 0)", (angle = pi) != 0, true);
    TEST("(angle = 10 * pi + 1) != 1)", (angle = 10 * pi + 1) != 1, false);
    TEST("(angle = 10 * pi + 1) != 0)", (angle = 10 * pi + 1) != 0, true);
    TEST("(angle = -pi) != -pi)", (angle = -pi) != -pi, false);
    TEST("(angle = -pi) != 0)", (angle = -pi) != 0, true);
    TEST("(angle = -10 * pi + 1) != 1)", (angle = -10 * pi + 1) != 1, false);
    TEST("(angle = -10 * pi + 1) != 0)", (angle = -10 * pi + 1) != 0, true);

    NOTICE("\nOpérateur == d'un double par rapport à un angle");
    TEST("(angle = pi) == -pi", -pi == (angle = pi), true);
    TEST("(angle = pi) == 0", 0 == (angle = pi), false);
    TEST("(angle = 10 * pi + 1) == 1", 1 == (angle = 10 * pi + 1), true);
    TEST("(angle = 10 * pi + 1) == 0", 0 == (angle = 10 * pi + 1), false);
    TEST("(angle = -pi) == -pi", -pi == (angle = -pi), true);
    TEST("(angle = -pi) == 0", 0 == (angle = -pi), false);
    TEST("(angle = -10 * pi + 1) == 1", 1 == (angle = -10 * pi + 1), true);
    TEST("(angle = -10 * pi + 1) == 0", 0 == (angle = -10 * pi + 1), false);

    NOTICE("\nOpérateur != d'un double par rapport à un angle");
    TEST("(angle = pi) != -pi", -pi != (angle = pi), false);
    TEST("(angle = pi) != 0)",  0 != (angle = pi), true);
    TEST("(angle = 10 * pi + 1) != 1)", 1 != (angle = 10 * pi + 1), false);
    TEST("(angle = 10 * pi + 1) != 0)", 0 != (angle = 10 * pi + 1), true);
    TEST("(angle = -pi) != -pi)", -pi != (angle = -pi), false);
    TEST("(angle = -pi) != 0)", 0 != (angle = -pi), true);
    TEST("(angle = -10 * pi + 1) != 1)", 1 != (angle = -10 * pi + 1), false);
    TEST("(angle = -10 * pi + 1) != 0)", 0 != (angle = -10 * pi + 1), true);

    NOTICE("\nOpérateurs mathématiques angle vs angle");
    TEST("CAngle(pi) + CAngle(pi)", CAngle(pi) + CAngle(pi), CAngle(pi + pi));
    TEST("CAngle(1) + CAngle(2)", CAngle(1) + CAngle(2), CAngle(3));
    TEST("CAngle(pi) - CAngle(pi)", CAngle(pi) - CAngle(pi), CAngle(0));
    TEST("CAngle(1) - CAngle(2)", CAngle(1) - CAngle(2), CAngle(-1));

    NOTICE("\nOpérateurs mathématiques angle vs double");
    TEST("CAngle(pi) + CAngle(pi)", CAngle(pi) + pi, CAngle(pi + pi));
    TEST("CAngle(1) + CAngle(2)", CAngle(1) + 2, CAngle(3));
    TEST("CAngle(pi) - CAngle(pi)", CAngle(pi) - pi, CAngle(0));
    TEST("CAngle(1) - CAngle(2)", CAngle(1) - 2, CAngle(-1));

    NOTICE("\nOpérateurs mathématiques double vs angle");
    TEST("CAngle(pi) + CAngle(pi)", pi + CAngle(pi), CAngle(pi + pi));
    TEST("CAngle(1) + CAngle(2)", 1 + CAngle(2), CAngle(3));
    TEST("CAngle(pi) - CAngle(pi)", pi - CAngle(pi), CAngle(0));
    TEST("CAngle(1) - CAngle(2)", 1 - CAngle(2), CAngle(-1));
  
  END_TESTS;
}
