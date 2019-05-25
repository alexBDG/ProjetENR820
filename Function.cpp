#ifndef _FUNCTION_CPP

#include "Function.h"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;
using namespace Eigen;

Function::Function(string Carburant, double dt, double d0, double T0, double T_inf, double vitesse_ecoul, double vap_air, double pression_vapeur_inf) :
_Carburant(Carburant), _dt(dt), _d0(d0), _T0(T0), _T_inf(T_inf), _vitesse_ecoul(vitesse_ecoul), _vap_air(vap_air), _pression_vapeur_inf(pression_vapeur_inf)
{
  if (_Carburant == "Essence")
  {
    _D_ab = 5.7*1E-6;
    _rho_liq = 750;
    _mu_vap_carb = 5.0*1E-4;
    _h_fg = 339*1E3; //339 kJ/kg
    _Cp_liq_carb = 2.09*1E3; //2.09 kJ/kg-K
    _Cp_vap_carb = 0.76*1E3; //0.76 kJ/kg-K
    _MM_vap_carb = 114*1E-3; //114 kg/kmol
    _T_eb = 387.15; //114 °C
    _k_vap_carb = 0.018; //0.018 W/mK
  }
  else if (_Carburant == "Ethanol")
  {
    _D_ab = 1.*1E-5;
    _rho_liq = 789;
    _mu_vap_carb = 8.3*1E-4;
    _h_fg = 836*1E3; //836 kJ/kg
    _Cp_liq_carb = 2.438*1E3; //2.438 kJ/kg-K
    _Cp_vap_carb = 1.7*1E3; //1.7 kJ/kg-K
    _MM_vap_carb = 46*1E-3; //46 kg/kmol
    _T_eb = 351.15; //78 °C
    _k_vap_carb = 0.014; //0.014 W/mK
  }
  else
  {
    _D_ab = 1.*1E-5;
    _rho_liq = 684;
    _mu_vap_carb = 3.9*1E-4;
    _h_fg = 316*1E3; //316 kJ/kg
    _Cp_liq_carb = 2.24*1E3; //2.24 kJ/kg-K
    _Cp_vap_carb = 0.9*1E3; //0.9 kJ/kg-K
    _MM_vap_carb = 100*1E-3; //100 kg/kmol
    _T_eb = 371.15; //98 °C
    _k_vap_carb = 0.011; //0.011 W/mK
  }
  _pi = 3.14159265358979323846;
  _R_u = 8.314;
  _MM_air = 28.965338*1E-3;
  _k_air = 1.5207*1E-11*pow(_T_inf,3) - 4.857*1E-8*pow(_T_inf,2) + 1.0184*1E-4*_T_inf - 3.9333*1E-4;
  _mu_air = -1.363528*1E-14*pow(_T_inf,3) + 1.00881778*1E-10*pow(_T_inf,2) + 3.452139*1E-8*_T_inf - 3.400747*1E-6;
  _Cp_air = 1.9327*1E-10*pow(_T_inf,4) - 7.9999*1E-7*pow(_T_inf,3) + 1.1407*1E-3*pow(_T_inf,2) - 4.4890*1E-1*_T_inf + 1.0575*1E3;
}

////////////////////////////////////////////////////////////////////////////////
// Les fonctions intermédiaires utiles
////////////////////////////////////////////////////////////////////////////////

void Function::Coefficient_transfert()
{
  H_etoile();
  Petit_Z();
  Grand_Z();
  H_transf_conv();
}

void Function::H_transf_conv()
{
  _h = _k_moy / _d *(2 + 0.6*pow(_Re,1./2)*pow(_Pr,1./3)) * _grand_z;
}

void Function::Grand_Z()
{
  if (_petit_z == 0)
  {
    _grand_z = 1.;
  }
  else
  {
    _grand_z = _petit_z/(exp(_petit_z)-1);
  }
}

void Function::Petit_Z()
{
  _petit_z = -_dm * _Cp_moy / ( _h_etoile * _aire);
}

void Function::H_etoile()
{
  _h_etoile = _k_moy / _d * (2 + 0.6*pow(_Re,1./2)*pow(_Pr,1./3));

}

////////////////////////////////////////////////////////////////////////////////
// Les fonctions géométriques
////////////////////////////////////////////////////////////////////////////////

void Function::Geometrie()
{
  Aire();
  Volume();
}

void Function::Aire()
{
  _aire = _pi * pow(_d,2) / 4.;
}

void Function::Volume()
{
  _volume = _pi * pow(_d,3) / 6.;
}

////////////////////////////////////////////////////////////////////////////////
// Les fonctions de la masse
////////////////////////////////////////////////////////////////////////////////

void Function::Masse_point()
{
  _R_vapeur = _R_u / _MM_moy;
  double a = (_pi * _d * _D_ab * _pression_vapeur_inf / (_R_vapeur * _T_moy) );
  double b = log( (_pression_vapeur_inf - _pression_vapeur_inf*_vap_air/100.) / (_pression_vapeur_inf - _pression_vapeur_surf) );
  double c = 2. + 0.6 * pow(_Re,1./2) * pow(_Sc,1./3);
  _dm = - a * b * c;
}

void Function::Clausius_Clapeyron()
{
  _pression_vapeur_surf = _pression_vapeur_inf * _x_vap;
}

////////////////////////////////////////////////////////////////////////////////
// Les grandeurs adimentionnées
////////////////////////////////////////////////////////////////////////////////

void Function::Grandeurs_adimentionnees()
{
  Reynolds();
  Prandtl();
  Schmidt();
}

void Function::Reynolds()
{
  _Re = _rho_moy * _vitesse_ecoul * _d / _mu_moy;
}

void Function::Prandtl()
{
  _Pr = _mu_moy * _Cp_moy / _k_moy;
}

void Function::Schmidt()
{
  _Sc = _mu_moy / (_rho_moy * _D_ab);
}

////////////////////////////////////////////////////////////////////////////////
// Evaluation des valeurs moyennes
////////////////////////////////////////////////////////////////////////////////

void Function::Valeurs_moyennes()
{
  T_moyen();
  Fraction_molaire();
  MM_moyen();
  Rho_moyen();
  K_moyen();
  Mu_moyen();
  Cp_moyen();
}

void Function::T_moyen()
{
  _T_moy = (_T_inf + _T)/2.;
}

void Function::Fraction_molaire()
{
  _R_carb = _R_u / _MM_vap_carb;
  _x_vap = exp( - _h_fg / _R_carb * (1./_T - 1./_T_eb) );
}

void Function::MM_moyen()
{
  _MM_moy = (1 - _x_vap/2.)*_MM_air + _x_vap/2. * _MM_vap_carb;
}

void Function::Rho_moyen()
{
  _rho_moy = _pression_vapeur_inf * _MM_moy / (_R_u * _T_moy);
}

void Function::K_moyen()
{
  _k_moy = (1 - _x_vap/2.) * _k_air  + _x_vap/2. * _k_vap_carb;
}

void Function::Mu_moyen()
{
  _mu_moy = (1 - _x_vap/2.) * _mu_air  + _x_vap/2. * _mu_vap_carb;
}

void Function::Cp_moyen()
{
  _Cp_moy = (1 - _x_vap/2.) * _MM_air/_MM_moy * _Cp_air  + _x_vap/2. * _MM_vap_carb/_MM_moy * _Cp_vap_carb;
}

////////////////////////////////////////////////////////////////////////////////
// Les instructions (la bouble iterrative en temps est dans le main.cc)
////////////////////////////////////////////////////////////////////////////////

void Function::Initialisation()
{
  string name_file = "solution_dt_" + std::to_string(_dt) + "_Carburant_" + _Carburant + ".dat";

  //Création du fichier de résultat au nom voulu
  _solution.open(name_file, ios::out);
  _solution.precision(7);

  _T = _T0;
  _d = _d0;
  Geometrie();
  _m = _rho_liq * _volume;
  _dm = 0.;
}

void Function::Calcul()
{
  Valeurs_moyennes();
  Grandeurs_adimentionnees();
  Clausius_Clapeyron();
  Masse_point();

  // Calcul de la masse
  _m = _m + _dt*_dm;

  // Calcul du diamètre de la goutte
  _d = pow(6*_m/(_rho_liq*_pi),1./3);

  Geometrie();
  Grandeurs_adimentionnees();
  Coefficient_transfert();

  // Calcul de la température
  _T = _T + _dt/(_Cp_liq_carb * _m) * ( _h * _aire * (_T_inf - _T) + _dm * _h_fg);
}

void Function::Fin()
{
  _solution.close();
}

////////////////////////////////////////////////////////////////////////////////
// L'Enregistrement de la solution
////////////////////////////////////////////////////////////////////////////////

void Function::SaveSol(double tps)
{
  _solution << tps  << " " << float(_d) << " " << float(_T) << " " << float(_m) << " " << float(pow(_d,2)/pow(_d0,2)) << endl;
}



#define _FUNCTION_CPP
#endif
