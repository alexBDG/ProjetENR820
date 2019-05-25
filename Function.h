#ifndef _FUNCTION_H
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include "Dense"
#include "Sparse"

class Function {
  private:
    //fichier de résultats
    std::ofstream _solution;
    //ENTREES
    std::string _Carburant;
    double _dt, _d0, _T0, _T_inf, _vitesse_ecoul, _vap_air, pression_vapeur_inf;
    //DONNEES CARBURANT
    double _D_ab, _rho_liq, _mu_vap_carb, _h_fg, _Cp_liq_carb, _Cp_vap_carb, _MM_vap_carb, _T_eb, _k_vap_carb, _pression_vapeur_inf;
    //DONNEES AIR
    double _MM_air, _k_air, _mu_air, _Cp_air;
    //CONSTANTE
    double _pi;

    //COEFFICIENT DE TRANSFERT
    double _h;
    double _grand_z;
    double _petit_z;
    double _h_etoile;

    //MASSE
    double _dm;
    double _pression_vapeur_surf;
    double _R_carb;

    //GEOMETRIE
    double _aire;
    double _volume;

    //VALEURS MOYENNES
    double _T_moy;
    double _MM_moy;
    double _rho_moy;
    double _k_moy;
    double _mu_moy;
    double _Cp_moy;

    //GRANDEURS ADIMENTIONNEES
    double _Re;
    double _Pr;
    double _Sc;

    //VARIABLES A RECALCULER
    double _m;
    double _T;
    double _d;

    double _x_vap;
    double _R_u;
    double _R_vapeur;


	public: // Méthodes et opérateurs de la classe
    Function(std::string Carburant, double dt, double d0, double T0, double T_inf, double vitesse_ecoul, double vap_air, double pression_vapeur_inf);

    void Coefficient_transfert(); //Appelle les suivantes
    void H_transf_conv();
    void H_etoile();
    void Petit_Z();
    void Grand_Z();

    void Geometrie(); //Appelle les suivantes
    void Aire();
    void Volume();

    void Masse_point();
    void Clausius_Clapeyron();
    double Get_masse() {return _m;};

    void Grandeurs_adimentionnees(); //Appelle les suivantes
    void Reynolds();
    void Prandtl();
    void Schmidt();

    void Valeurs_moyennes(); //Appelle les suivantes
    void T_moyen();
    void Fraction_molaire();
    void MM_moyen();
    void Rho_moyen();
    void K_moyen();
    void Mu_moyen();
    void Cp_moyen();

    //Les trois fonctions de la boucle temporelle
    void Initialisation();
    void Calcul();
    void Fin();

    void SaveSol(double tps);
};

#define _FUNCTION_H
#endif
