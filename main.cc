#include <fstream>
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include "Function.h"

using namespace std;
using namespace Eigen;

int main()
{
  double d0, T0, T_inf, vitesse_ecoul, vap_air, pression_vapeur_inf, dt, tps, masse;
  std::string Carburant;

  // Démarrage du chrono
  auto start = chrono::high_resolution_clock::now();

////////////////////////////////////////////////////////////////////////////////
// Entrée des valeurs
////////////////////////////////////////////////////////////////////////////////

  // Pas de temps
  dt = 1.E-6; // en s

  //Carburant
  Carburant = "Ethanol";

  //diamètre initiale de la goutte
  d0 = 45*1E-6; // en m

  //Température initiale de la goutte
  T0 = 295; // en K

  //Température extérieur de soufflage
  T_inf = 350; // en K

  //Vitesse d'écoulement
  vitesse_ecoul = 1.; // en m/s

  //Quantité de vapeur de Carburant dans l'air
  vap_air = 0; // en %

  //Pression à l'extérieur
  pression_vapeur_inf = 1E5; // en Pa

////////////////////////////////////////////////////////////////////////////////
// Calculs
////////////////////////////////////////////////////////////////////////////////

  // Conditions initiales
  Function* fct = new Function(Carburant, dt, d0, T0, T_inf, vitesse_ecoul, vap_air, pression_vapeur_inf);
  fct->Initialisation();
  tps = 0;
  int n =0;
  masse = fct->Get_masse();
  fct->SaveSol(tps);

  cout << "-------------------------------------------------" << endl;
  cout << "Calcul des solutions dans le temps : " << endl;

  // Boucle sur le temps
  while (masse > 1E-12)
  {
    //Avancement
    cout.flush();
    cout << "Masse = " << masse  << " %        \r";

    // Recalcule de la masse
    fct->Calcul();
    masse = fct->Get_masse();

    tps += dt;
    //Enregistrement de la solution
    fct->SaveSol(tps);
    n+=1;
  }

  //On referme le fichier solution
  fct->Fin();

  cout << "-------------------------------------------------" << endl;

  // Fin du chrono
  auto finish = chrono::high_resolution_clock::now();
  double chrono_temps = chrono::duration_cast<chrono::milliseconds>(finish-start).count();
  // Affichage du résultat
  cout << "Cela a pris "<< chrono_temps/1000. << " secondes" << endl;

  return 0;
}
